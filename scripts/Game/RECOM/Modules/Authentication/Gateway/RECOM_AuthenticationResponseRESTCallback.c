class RECOM_AuthenticationResponseRESTCallback : RestCallback {

	ref RECOM_AuthenticationResponseBuffer buffer;
	
	void RECOM_AuthenticationResponseRESTCallback(RECOM_AuthenticationResponseBuffer buffer) {
		this.buffer = buffer
	}
	
	void ~RECOM_AuthenticationResponseRESTCallback() {
		buffer = null;
	}
	
	override void OnSuccess( string data, int dataSize ) {
		PrintFormat("%1 OnSuccess called ", ClassName());
		PrintFormat("Re-Authenticate");

		RECOM_AuthenticationResponseDto response = new RECOM_AuthenticationResponseDto;
		response.ExpandFromRAW(data);
		buffer.update(response);
	};

	override void OnError( int errorCode ) {
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", ClassName(), errorCode);
	};

}