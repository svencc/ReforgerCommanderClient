class RECOM_MessageBusModule : RECOM_BaseModule {
	
	private static ref RECOM_MessageBusModule instance;
	protected ref RECOM_BaseBuffer<RECOM_MessageBus_ResponseDto> buffer;
	protected ref RECOM_MessageBus_Gateway gateway;
	
	
	static RECOM_MessageBusModule getModule() {
        if (!RECOM_MessageBusModule.instance) {
            RECOM_MessageBusModule.instance = new RECOM_MessageBusModule();
        }
        return RECOM_MessageBusModule.instance;
    }
	
	private void RECOM_MessageBusModule() {
		buffer = new RECOM_BaseBuffer<RECOM_MessageBus_ResponseDto>();
		gateway = new RECOM_MessageBus_Gateway(buffer);
	}
	
	void ~RECOM_MessageBusModule() {
		delete gateway;
		delete buffer;
		delete RECOM_MessageBusModule.instance;
	}
	
	override void start() {
		super.start();
		GetGame().GetCallqueue().CallLater(gateway.provideData);
	}
	
	override void stop() {
		super.stop();
	}
	
}