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
            RECOM_MapTopographyScannerModule.instance = new RECOM_MapTopographyScannerModule(new RECOM_MapTopographypScannerEntitiesShippingService(500), 10.0);
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
			
		/*
		if (!startedProduction) {
			//initProduction(stepSize);
			startedProduction = true;
			for (int iterationZ = 0; iterationZ < predictedScanIterations; iterationZ++) {
				//GetGame().GetCallqueue().CallLater(scanLine, iterationZ * predictedScanIterations/2, false, iterationZ); 
			}
			PrintFormat("%1: start production of %2 ...", ClassName(), worldFileName);
		}
		*/
	
	
		if (iterationZ < predictedScanIterations) {
			/*
			for (int iterationX = 0; iterationX < predictedScanIterations; iterationX++) {
				PrintFormat("... x:%1 y:%2", iterationX, iterationZ);		
				scanMapHeight(iterationX, iterationZ);
			}
			*/
			if (iterationX < predictedScanIterations) {
				PrintFormat("... x:%1 y:%2", iterationX, iterationZ);		
				scanMapHeight(iterationX, iterationZ);
				iterationX++;
			} else {
				iterationZ++;
				iterationX = 0;
			}
			iterationZ++;
			iterationX = 0;
			GetGame().GetCallqueue().CallLater(produce, 0, false);
		} else {
			finishedProduction = true;
			PrintFormat("... %1: production completed.", ClassName());
		}
		
	}
	
	/*
	void scanLine(int iterationZ) {
		for (int iterationX = 0; iterationX < predictedScanIterations; iterationX++) {
			scanMapHeight(iterationX, iterationZ);
		}
		finishedScanLines++;
		finishedProduction = (finishedScanLines == (predictedScanIterations - 1));
	}
	*/
	
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
			
			PrintFormat("... %1: entities to consume.", elementsToConsume);
			
			for (int i = 0; i < elementsToConsume; i++) {
				RECOM_MapTopographyEntityDto entityToSend = producedEntitiesQueue.Get(0);
				package(entityToSend);
				producedEntitiesQueue.RemoveItemOrdered(entityToSend);
			}
			
			PrintFormat("... %1: remaining entities to consume.", producedEntitiesQueue.Count());
		}
		
		GetGame().GetCallqueue().CallLater(consume, 0, false);
	}
	
	protected void scanMapHeight(
		int iterationX, 
		int iterationZ
	) {
		// PrintFormat("... x:%1 y:%2", iterationX, iterationZ);		
		float centerX = (iterationX * stepSize) + (stepSize / 2);
		float centerZ = (iterationZ * stepSize) + (stepSize / 2);
		
		RECOM_MapTopographyEntityDto entityToSend = new RECOM_MapTopographyEntityDto();
		entityToSend.surfaceHeight = GetGame().GetWorld().GetSurfaceY(centerX, centerZ);
		entityToSend.oceanHeight = GetGame().GetWorld().GetOceanHeight(centerX, centerZ);
		entityToSend.oceanBaseHeight = GetGame().GetWorld().GetOceanBaseHeight();
		entityToSend.coordinates = {centerZ, centerX}; // 2d map coordinates
		
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