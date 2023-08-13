class RECOM_MapRendererResponseRESTCallback : RestCallback {

	ref RECOM_MapRendererResponseBuffer buffer;
	
	void RECOM_MapRendererResponseRESTCallback(RECOM_MapRendererResponseBuffer buffer) {
		this.buffer = buffer
	}
	
	
	override void OnSuccess( string data, int dataSize ) {
		PrintFormat("%1 OnSuccess called ", "RECOM_MapRendererRestCallback");

		RECOM_MapRendererResponseDto response = new RECOM_MapRendererResponseDto;
		response.ExpandFromRAW(data);

		buffer.write(response);
	};

	override void OnError( int errorCode ) {
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", "RECOM_MapRendererRestCallback", errorCode);
	};

}