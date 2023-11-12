class RECOM_MapTopographyScannerModule : RECOM_BaseModule {

	private static ref RECOM_MapTopographyScannerModule instance;
	
	protected bool startedProduction = false;
	protected bool finishedProduction = false;
	
	protected bool startedConsumption = false;
	protected bool finishedConsumption = false;
	
	protected int worldSize;
	protected float stepSize;
	protected int iterationX;
	protected int iterationZ;
	
	protected int predictedScanIterations;
	protected int finishedScanLines;
	
	protected string worldFileName

	protected ref array<ref RECOM_MapTopographyEntityDto> producedEntitiesQueue = {};
	protected ref RECOM_MapTopographypScannerEntitiesShippingService shippingService;
	protected ref RECOM_MapTopographyScannerEntitiesTransactionManager transactionManager

	
	static RECOM_MapTopographyScannerModule getModule() {
        if (!RECOM_MapTopographyScannerModule.instance) {
            RECOM_MapTopographyScannerModule.instance = new RECOM_MapTopographyScannerModule(new RECOM_MapTopographypScannerEntitiesShippingService(1000), 10.0);
        }
		
        return RECOM_MapTopographyScannerModule.instance;
    }
	
	override void startModule() {
		super.startModule();
	}
	
	override void disposeModule() {
		super.disposeModule();
		RECOM_MapTopographyScannerModule.instance = null;
	}
	
	void runScanner() {
		initProduction(stepSize);
		GetGame().GetCallqueue().CallLater(produce, 0, false);
		GetGame().GetCallqueue().CallLater(consume, 200, false);
	}
	
	private void RECOM_MapTopographyScannerModule(
		RECOM_MapTopographypScannerEntitiesShippingService service,
		int stepSize
	) {
		shippingService = service;
		this.stepSize = stepSize;
	}

	void ~RECOM_MapTopographyScannerModule() {
		producedEntitiesQueue.Clear();
		producedEntitiesQueue = null;
		shippingService = null;
		transactionManager = null;
		RECOM_MapTopographyScannerModule.instance = null;
	}

	protected void initProduction(float stepSize) {
		worldSize = determineMapSize();
        worldFileName = GetGame().GetWorldFile();
		predictedScanIterations = Math.Floor(worldSize/stepSize);
		iterationX = 0;
		iterationZ = 0;
		finishedScanLines = 0;
		
        transactionManager = new RECOM_MapTopographyScannerEntitiesTransactionManager(worldFileName);
        shippingService.setSessionIdentifier(worldFileName);
	}

	void produce() {
		if (finishedProduction) {
			return;
		}
			

		if (!startedProduction) {
			startedProduction = true;
			PrintFormat("%1: start production of %2 ...", ClassName(), worldFileName);
		}
	
		int scanSize = 1000;
		int maxIterationsX = iterationX + scanSize;
		if (iterationZ < predictedScanIterations) {
			for (int localIterationX = iterationX; localIterationX <= maxIterationsX && localIterationX <= predictedScanIterations; localIterationX++) {
				scanMapHeight(iterationX, iterationZ);
				iterationX = localIterationX;
			}
			if (iterationX == predictedScanIterations) {
				PrintFormat("...%1 x:%2 z:%3", ClassName(), iterationX, iterationZ);	
				iterationZ++;
				iterationX = 0;
			}
			GetGame().GetCallqueue().CallLater(produce, 5, false);
		} else {
			finishedProduction = true;
			PrintFormat("... %1: production completed.", ClassName());
		}
	}
	
	
	void consume() {
		if (finishedConsumption) {
			return;
		}
		
		if (!startedConsumption && RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			startedConsumption = true;
			transactionManager.openTransaction();
			PrintFormat("%1: start consumption ...", ClassName());
		}

		if (producedEntitiesQueue.IsEmpty() && finishedProduction && RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			finishedConsumption = true;
			shippingService.flush();
			PrintFormat("... %1: consumption completed.", ClassName());
			transactionManager.commitTransaction(shippingService.getPackagesSent());
			PrintFormat("%1: committed transaction.", ClassName());
		} else if (producedEntitiesQueue.IsEmpty() == false && RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			int elementsToConsume = Math.Min(
				producedEntitiesQueue.Count(), 
				shippingService.getMaxPackageSizeBeforeFlush()
			);
			
			//PrintFormat("... %1: entities to consume.", elementsToConsume);
			for (int i = 0; i < elementsToConsume; i++) {
				RECOM_MapTopographyEntityDto entityToSend = producedEntitiesQueue.Get(0);
				package(entityToSend);
				producedEntitiesQueue.RemoveItemOrdered(entityToSend);
			}
			//PrintFormat("... %1: remaining entities to consume.", producedEntitiesQueue.Count());
		}
		
		GetGame().GetCallqueue().CallLater(consume, 0, false);
	}
	
	protected void scanMapHeight(
		int iterationX, 
		int iterationZ
	) {	
		float centerX = (iterationX * stepSize) + (stepSize / 2);
		float centerZ = (iterationZ * stepSize) + (stepSize / 2);
		float height = GetGame().GetWorld().GetSurfaceY(centerX, centerZ);
		
		RECOM_MapTopographyEntityDto entityToSend = new RECOM_MapTopographyEntityDto();
		entityToSend.oceanHeight = GetGame().GetWorld().GetOceanHeight(centerX, centerZ);
		entityToSend.oceanBaseHeight = GetGame().GetWorld().GetOceanBaseHeight();
		entityToSend.coordinates = {centerX, height, centerZ}; // 2d map coordinates
		
		producedEntitiesQueue.Insert(entityToSend);
	}
	
	protected int determineMapSize() {
		vector min, max;
		GetGame().GetWorldEntity().GetWorldBounds(min, max);
		return Math.Max(max[0] - min[0], max[2] - min[2]);
	}
	
	protected void package(RECOM_MapTopographyEntityDto entityDto) {
		shippingService.assemblePackage(entityDto);
	}

}