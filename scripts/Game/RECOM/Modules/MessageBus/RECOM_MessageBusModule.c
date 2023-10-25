class RECOM_MessageBusModule : RECOM_BaseModule {
	
	private static ref RECOM_MessageBusModule instance;
	protected ref RECOM_MessageBus_Gateway gateway;
	protected ref RECOM_MB_Subject subject;
	
	
	static RECOM_MessageBusModule getModule() {
        if (!RECOM_MessageBusModule.instance) {
            RECOM_MessageBusModule.instance = new RECOM_MessageBusModule();
        }
        return RECOM_MessageBusModule.instance;
    }
	
	private void RECOM_MessageBusModule() {
		subject = new RECOM_MB_Subject();
		gateway = new RECOM_MessageBus_Gateway(subject);
	}
	
	void ~RECOM_MessageBusModule() {
		delete gateway;
		delete subject;
		delete RECOM_MessageBusModule.instance;
	}
	
	override void start() {
		super.start();
		Print("RECOM_MessageBusModule start");
		GetGame().GetCallqueue().CallLater(gateway.provideData, 1000, false, 0);
	}
	
	override void stop() {
		super.stop();
	}
	
}