class RECOM_TimeRESTGateway {
	
	ref RECOM_TimeRESTCallback callback;

	void RECOM_TimeRESTGateway(RECOM_TimeResponseBuffer buffer) {
		callback = new RECOM_TimeRESTCallback(buffer);
	}

	void ~RECOM_TimeRESTGateway() {
		delete callback;
	}
	
	void requestTime() {
		GetGame().GetRestApi().GetContext(RECOMAPIs.host).GET(callback, RECOMAPIs.GET_TIME);
	}

}