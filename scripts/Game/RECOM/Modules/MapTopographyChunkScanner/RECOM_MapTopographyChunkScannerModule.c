class RECOM_MapTopographyChunkScanner {

	//private static ref RECOM_MapTopographyChunkScannerModule instance;
	
	protected bool startedProduction = false;
	protected bool finishedProduction = false;
	
	protected bool startedConsumption = false;
	protected bool finishedConsumption = false;
	
	protected int iterationX;
	protected int iterationZ;
	
	protected int chunkX; 
	protected int chunkZ;
	protected int predictedScanIterations;
	protected int finishedScanLines;
	
	protected string worldFileName

	protected ref array<ref RECOM_MapTopographyEntityDto> producedEntitiesQueue = {};
	protected ref RECOM_MapTopographypScannerEntitiesShippingService shippingService;
	protected ref RECOM_MapTopographyScannerEntitiesTransactionManager transactionManager

	
	/*
	static RECOM_MapTopographyChunkScannerModule getModule() {
		SLF4R.normal(string.Format("RECOM_MapTopographyChunkScannerModule: getModule() ..."));
        if (!RECOM_MapTopographyChunkScannerModule.instance) {
            RECOM_MapTopographyChunkScannerModule.instance = new RECOM_MapTopographyChunkScannerModule(new RECOM_MapTopographypScannerEntitiesShippingService(500));
        }
		
        return RECOM_MapTopographyChunkScannerModule.instance;
    }
	*/
	
	
	protected void dispose() {
		startedProduction = false;
		finishedProduction = false;
	
		startedConsumption = false;
		finishedConsumption = false;
	}
	
	void runScanner() {
		SLF4R.normal(string.Format("%1: runScanner() ...", ClassName()));
		initProduction();
		GetGame().GetCallqueue().CallLater(produce, 5, false);
		GetGame().GetCallqueue().CallLater(consume, 200, false);
	}
	
	void RECOM_MapTopographyChunkScanner(
		int chunkX, 
		int chunkZ
	) {
		shippingService = new RECOM_MapTopographypScannerEntitiesShippingService(500);
		this.chunkX = chunkX;
		this.chunkZ = chunkZ;
	}

	void ~RECOM_MapTopographyChunkScanner() {
		dispose();
		producedEntitiesQueue.Clear();
		producedEntitiesQueue = null;
		shippingService = null;
		transactionManager = null;
		//RECOM_MapTopographyChunkScannerModule.instance = null;
	}

	protected void initProduction() {
        worldFileName = GetGame().GetWorldFile();  	// <<<<< das muss man noch prüfen
		predictedScanIterations = 1000; // das ist die feste Chunk Size
		iterationX = 0;
		iterationZ = 0;
		finishedScanLines = 0;
		
		string sessionIdentifier = worldFileName + "#####" + chunkX + "," + chunkZ;
        transactionManager = new RECOM_MapTopographyScannerEntitiesTransactionManager(sessionIdentifier);
        shippingService.setSessionIdentifier(sessionIdentifier);
	}

	void produce() {
		if (finishedProduction) {
			SLF4R.normal(string.Format("%1: end production!", ClassName()));
			return;
		}
			

		if (!startedProduction) {
			startedProduction = true;
			SLF4R.normal(string.Format("%1: start production of %2 ...", ClassName(), worldFileName));
		}
	
		int scanRowSize = 500;
		int maxIterationsX = iterationX + scanRowSize;
		if (iterationZ < predictedScanIterations) {
			for (int localIterationX = iterationX; localIterationX <= maxIterationsX && localIterationX <= predictedScanIterations; localIterationX++) {
				scanMapHeight(iterationX, iterationZ);
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
	
	protected void scanMapHeight(
		int coordinateX, 
		int coordinateZ
	) {	
		float heightY = GetGame().GetWorld().GetSurfaceY(coordinateX, coordinateZ);
		
		RECOM_MapTopographyEntityDto entityToSend = new RECOM_MapTopographyEntityDto();
		entityToSend.coordinates = {coordinateX, heightY, coordinateZ};
		
		producedEntitiesQueue.Insert(entityToSend);
	}
	
	protected int determineMapSize() {
		vector min, max;
		GetGame().GetWorldEntity().GetWorldBounds(min, max);
		return Math.Max(max[0] - min[0], max[2] - min[2]);
	}
	
	protected void package(notnull RECOM_MapTopographyEntityDto entityDto) {
		shippingService.assemblePackage(entityDto);
	}

}