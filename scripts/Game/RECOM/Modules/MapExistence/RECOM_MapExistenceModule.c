class RECOM_MapExistenceModule : RECOM_BaseModule {
	
	private static ref RECOM_MapExistenceModule instance;
	protected ref RECOM_MapExistence_Gateway gateway;
	protected ref RECOM_BaseBuffer<RECOM_MapExistenceResponseDto> buffer;
	
	
	static RECOM_MapExistenceModule getModule() {
        if (!RECOM_MapExistenceModule.instance) {
            RECOM_MapExistenceModule.instance = new RECOM_MapExistenceModule();
        }
        return RECOM_MapExistenceModule.instance;
    }
	
	private void RECOM_MapExistenceModule() {
		buffer = new RECOM_BaseBuffer<RECOM_MapExistenceResponseDto>();
		gateway = new RECOM_MapExistence_Gateway(buffer);
	}
	
	void ~RECOM_MapExistenceModule() {
		buffer = null;
		gateway = null;
		RECOM_MapExistenceModule.instance = null;
	}
	
	override void startModule() {
		super.startModule();
		GetGame().GetCallqueue().CallLater(gateway.provideData, 2000); // trigger the first run after x seconds (give authentication some time)
	}
	
	override void disposeModule() {
		super.disposeModule();
		RECOM_MapExistenceModule.instance = null;
	}
	
	void triggerWhenMapExists() {
		PrintFormat(" ! ! ! %1 triggerWhenMapExists called", ClassName());
		RECOM_MapTopographyScannerModule.getModule().runScanner(); // TODO retrigger MapExistance when scanner is done
	}
	
	void triggerWhenMapNotExists() {
		PrintFormat(" ! ! ! %1 triggerWhenMapNotExists called", ClassName());
		//RECOM_MapScannerModule.getModule().runScanner(); // TODO retrigger MapExistance when scanner is done
		//RECOM_MapTopographyScannerModule.getModule().runScanner(); // TODO retrigger MapExistance when scanner is done
	}
	
}