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
		//GetGame().GetCallqueue().CallLater(restGateway.requestTime, 500, true);
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
	
	int time() {
		 return System.GetUnixTime();
		/*
		// in the past we fetched the time from server; but now I found out that I am able to get the unixTimestamp epco utc from Reforger API directly
		// So no there is no need to fetch it from server.
		// as server / unix timestamp is normed to UTC, I do not expect any timing issues or need to sync time (difference)
		int localTime = System.GetUnixTime();
		PrintFormat("Time local %1 - remote %2",localTime, buffer.read().epochSeconds, LogLevel.ERROR);
		return buffer.read();
		*/
	}
		
}
