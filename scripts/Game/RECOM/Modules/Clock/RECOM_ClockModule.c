class RECOM_ClockModule {

	private static ref RECOM_ClockModule instance;
	protected ref RECOM_TimeResponseBuffer buffer;
	protected ref RECOM_TimeRESTGateway restGateway;
	
	static RECOM_ClockModule getModule() {
        if (!RECOM_ClockModule.instance) {
            RECOM_ClockModule.instance = new RECOM_ClockModule();
        }
    
		return RECOM_ClockModule.instance;
    }
	
	void RECOM_ClockModule() {
		buffer = new RECOM_TimeResponseBuffer();
		restGateway = new RECOM_TimeRESTGateway(buffer);
		init();
	}
	
	private void init() {
		GetGame().GetCallqueue().CallLater(restGateway.requestTime, 500, true);
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
