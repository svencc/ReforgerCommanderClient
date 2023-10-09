class RECOM_ClockModule : RECOM_BaseModule {

	private static ref RECOM_ClockModule instance;
	protected ref RECOM_TimeResponseBuffer buffer;
	protected ref RECOM_TimeRESTGateway restGateway;
	
	static RECOM_ClockModule getModule() {
        if (!RECOM_ClockModule.instance) {
            RECOM_ClockModule.instance = new RECOM_ClockModule();
        }
		return RECOM_ClockModule.instance;
    }
	
	override void start() {
		super.start();
		GetGame().GetCallqueue().CallLater(restGateway.requestTime, 500, true);
	}
	
	override void stop() {
		super.stop();
	}
	
	private void RECOM_ClockModule() {
		buffer = new RECOM_TimeResponseBuffer();
		restGateway = new RECOM_TimeRESTGateway(buffer);
	}
	
	void ~RECOM_ClockModule()	{
		delete buffer;
		delete restGateway;
		delete RECOM_ClockModule.instance;
	}
	
	RECOM_EpochTimeDto time() {
		return buffer.read();
	}
		
}
