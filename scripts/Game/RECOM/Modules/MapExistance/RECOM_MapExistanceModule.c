class RECOM_MapExistanceModule : RECOM_BaseModule {
	
	private static ref RECOM_MapExistanceModule instance;
	protected ref RECOM_MapExistence_Gateway gateway;
	protected ref RECOM_BaseBuffer<RECOM_MapExistenceResponseDto> buffer;
	
	
	static RECOM_MapExistanceModule getModule() {
        if (!RECOM_MapExistanceModule.instance) {
            RECOM_MapExistanceModule.instance = new RECOM_MapExistanceModule();
        }
        return RECOM_MapExistanceModule.instance;
    }
	
	private void RECOM_MapExistanceModule() {
		buffer = new RECOM_BaseBuffer<RECOM_MapExistenceResponseDto>();
		gateway = new RECOM_MapExistence_Gateway(buffer);
	}
	
	void ~RECOM_MapExistanceModule() {
		buffer = null;
		gateway = null;
		RECOM_MapExistanceModule.instance = null;
	}
	
	override void start() {
		super.start();
		GetGame().GetCallqueue().CallLater(gateway.provideData, 1000); // trigger the first run after x seconds (give authentication some time)
	}
	
	override void dispose() {
		super.dispose();
		RECOM_MapExistanceModule.instance = null;
	}
	
	void triggerWhenMapExists() {
		PrintFormat(" ! ! ! %1 triggerWhenMapExists called", ClassName());
	}
	
	void triggerWhenMapNotExists() {
		PrintFormat(" ! ! ! %1 triggerWhenMapNotExists called", ClassName());
	}
	
}