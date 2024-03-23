class RECOM_MapTopographyChunkScanner {
	
	protected bool startedProduction = false;
	protected bool finishedProduction = false;
	
	protected bool startedConsumption = false;
	protected bool finishedConsumption = false;
	
	protected int iterationX = 0;
	protected int iterationZ = 0;
	protected int finishedScanLines = 0;
	
	protected int predictedScanIterations = 1000;
	
	protected int chunkX; 
	protected int chunkZ;
	protected int baseOffsetX;
	protected int baseOffsetZ;
	RECOM_MapMeta mapMeta;
	string sessionIdentifier;

	protected ref array<ref RECOM_MapTopographyEntityDto> producedEntitiesQueue = {};
	protected ref RECOM_MapTopographypScannerEntitiesShippingService shippingService;
	protected ref RECOM_MapTopographyScannerEntitiesTransactionManager transactionManager
	
	
	
	void RECOM_MapTopographyChunkScanner(
		int chunkX, 
		int chunkZ
	) {
		shippingService = new RECOM_MapTopographypScannerEntitiesShippingService(500);
		this.chunkX = chunkX;
		this.chunkZ = chunkZ;
	}

	void ~RECOM_MapTopographyChunkScanner() {
		producedEntitiesQueue.Clear();
		producedEntitiesQueue = null;
		shippingService = null;
		transactionManager = null;
	}
	
	void runScanner() {
		SLF4R.normal(string.Format("%1: runScanner() ...", ClassName()));
		initProduction();
		GetGame().GetCallqueue().CallLater(produce, 5, false);
		GetGame().GetCallqueue().CallLater(consume, 200, false);
	}

	protected void initProduction() {
		baseOffsetX = chunkX * 1000;
		baseOffsetZ = chunkZ * 1000;
		
		RECOM_MapMeta mapMeta = RECOM_MapMetaProvider.provide();
		sessionIdentifier = string.Format("%1#####%2,%3", mapMeta.mapName, chunkX, chunkZ);
		
        transactionManager = new RECOM_MapTopographyScannerEntitiesTransactionManager(sessionIdentifier);
        shippingService.setSessionIdentifier(sessionIdentifier);
	}

	void produce() {
		if (finishedProduction) {
			SLF4R.normal(string.Format("%1: end production of %2", ClassName(), sessionIdentifier));
			return;
		}

		if (!startedProduction) {
			startedProduction = true;
			SLF4R.normal(string.Format("%1: start production of %2 ...", ClassName(), sessionIdentifier));
		}
	
		int scanRowSize = 500;
		int maxIterationsX = iterationX + scanRowSize;
		if (iterationZ < predictedScanIterations) {
			for (int localIterationX = iterationX; localIterationX <= maxIterationsX && localIterationX <= predictedScanIterations; localIterationX++) {
				scanHeightY(baseOffsetX + iterationX, baseOffsetZ + iterationZ);
				iterationX = localIterationX;
			}
			if (iterationX == predictedScanIterations) {
				SLF4R.normal(string.Format("...%1 x:%2 z:%3", ClassName(), iterationX, iterationZ));
				iterationZ++;
				iterationX = 0;
			}
			GetGame().GetCallqueue().CallLater(produce, 0, false);
		} else {
			finishedProduction = true;
			SLF4R.normal(string.Format("... %1: production completed.", ClassName()));
		}
	}
	
	
	void consume() {
		if (finishedConsumption) {
			SLF4R.normal(string.Format("%1: end consumption!", ClassName()));
			return;
		}
		
		if (!startedConsumption && RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			startedConsumption = true;
			transactionManager.openTransaction();
			SLF4R.normal(string.Format("%1: start consumption ...", ClassName()));
		}

		if (producedEntitiesQueue.IsEmpty() && finishedProduction && RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			finishedConsumption = true;
			shippingService.flush();
			SLF4R.normal(string.Format("... %1: consumption completed.", ClassName()));
			transactionManager.commitTransaction(shippingService.getPackagesSent());
			SLF4R.normal(string.Format("%1: committed transaction.", ClassName()));
		} else if (producedEntitiesQueue.IsEmpty() == false && RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			int elementsToConsume = Math.Min(
				producedEntitiesQueue.Count(), 
				shippingService.getMaxPackageSizeBeforeFlush()
			);

			SLF4R.debugging(string.Format("... %1: entities to consume.", elementsToConsume));
			for (int i = 0; i < elementsToConsume; i++) {
				RECOM_MapTopographyEntityDto entityToSend = producedEntitiesQueue.Get(0);
				package(entityToSend);
				producedEntitiesQueue.RemoveItemOrdered(entityToSend);
			}
			SLF4R.debugging(string.Format("... %1: remaining entities to consume.", producedEntitiesQueue.Count()));
		}
		
		GetGame().GetCallqueue().CallLater(consume, 0, false);
	}
	
	protected void scanHeightY(
		int coordinateX, 
		int coordinateZ
	) {	
		float heightY = GetGame().GetWorld().GetSurfaceY(coordinateX, coordinateZ);
		
		RECOM_MapTopographyEntityDto entityToSend = new RECOM_MapTopographyEntityDto();
		entityToSend.coordinates = {coordinateX, heightY, coordinateZ};
		
		producedEntitiesQueue.Insert(entityToSend);
	}
	
	protected void package(notnull RECOM_MapTopographyEntityDto entityDto) {
		shippingService.assemblePackage(entityDto);
	}

}