class RECOM_TimeRESTCallback : RestCallback {

    private ref RECOM_TimeResponseBuffer buffer;

	void RECOM_TimeRESTCallback(RECOM_TimeResponseBuffer buffer) {
        this.buffer = buffer;
	}
	
	void ~RECOM_TimeRESTCallback() {
		delete buffer;
	}
	
	override void OnSuccess( string data, int dataSize ) {
		PrintFormat("%1 OnSuccess called ", "RECOM_TimeRESTCallback");

		RECOM_EpochTimeDto response = new RECOM_EpochTimeDto();
		response.ExpandFromRAW(data);

		buffer.update(response);
	};

	override void OnError( int errorCode ) {
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", "RECOM_TimeRESTCallback", errorCode);
	};

}