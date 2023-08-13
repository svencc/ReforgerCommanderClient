class RECOM_Clock {

	private static ref RECOM_Clock instance;
	protected ref RECOM_TimeResponseBuffer buffer;
	protected ref RECOM_TimeRESTGateway restGateway;
	
	void RECOM_Clock() {
		buffer = new RECOM_TimeResponseBuffer();
		restGateway = new RECOM_TimeRESTGateway(buffer);
		GetGame().GetCallqueue().CallLater(restGateway.requestTime, 500, true);

	}
	
	void ~RECOM_Clock()	{
		delete buffer;
		delete restGateway;
		delete RECOM_Clock.instance;
	}

	
	static RECOM_Clock getInstance() {
        if (!RECOM_Clock.instance) {
            RECOM_Clock.instance = new RECOM_Clock();
        }
        return RECOM_Clock.instance;
    }
	
	RECOM_EpochTimeDto time() {
		return buffer.read();
	}
		
}
