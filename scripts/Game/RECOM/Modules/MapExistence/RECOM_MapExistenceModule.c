class RECOM_MapExistenceModule : RECOM_BaseModule {
	
	private static ref RECOM_MapExistenceModule instance;
	
	protected ref RECOM_MapExistence_Gateway mapExistenceGateway;
	protected ref RECOM_BaseBuffer<RECOM_MapExistenceResponseDto> buffer;
	
	protected ref RECOM_CreateMap_Gateway createMapGateway;
	
	
	
	static RECOM_MapExistenceModule getModule() {
        if (!RECOM_MapExistenceModule.instance) {
            RECOM_MapExistenceModule.instance = new RECOM_MapExistenceModule();
        }
		
        return RECOM_MapExistenceModule.instance;
    }
	
	private void RECOM_MapExistenceModule() {
		buffer = new RECOM_BaseBuffer<RECOM_MapExistenceResponseDto>();
		mapExistenceGateway = new RECOM_MapExistence_Gateway(buffer);
		
		createMapGateway = new RECOM_CreateMap_Gateway();
	}
	
	void ~RECOM_MapExistenceModule() {
		buffer = null;
		mapExistenceGateway = null;
		RECOM_MapExistenceModule.instance = null;
	}
	
	override void startModule() {
		super.startModule();
		SLF4R.debugging(string.Format(" ! ! ! %1 startModule()", ClassName()));
		GetGame().GetCallqueue().CallLater(mapExistenceGateway.provideData, 5000);
	}
	
	override void disposeModule() {
		super.disposeModule();
		RECOM_MapExistenceModule.instance = null;
	}
	
	void triggerWhenMapExists() {
		SLF4R.normal(string.Format(" ! ! ! %1 triggerWhenMapExists called", ClassName()));
	}
	
	void triggerWhenMapNotExists() {
		SLF4R.normal(string.Format(" ! ! ! %1 triggerWhenMapNotExists called", ClassName()));
		createMapGateway.createMap();
	}
	
	void triggerWhenMapCreated() {
		SLF4R.normal(string.Format(" ! ! ! %1 triggerWhenMapCreated called", ClassName()));
		GetGame().GetCallqueue().CallLater(mapExistenceGateway.provideData, 5); // update module state
		RECOM_MapStructureScannerModule.getModule().runScanner();
		RECOM_MapTopographyScannerModule.getModule().runScanner();
	}
	
}