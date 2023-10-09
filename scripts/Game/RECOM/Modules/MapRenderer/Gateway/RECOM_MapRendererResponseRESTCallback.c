class RECOM_MapRendererResponseRESTCallback : RestCallback {

	ref RECOM_BaseBuffer<RECOM_MapRendererResponseDto> buffer;
	
	void RECOM_MapRendererResponseRESTCallback(RECOM_BaseBuffer<RECOM_MapRendererResponseDto> buffer) {
		this.buffer = buffer
	}
	
	void ~RECOM_MapRendererResponseRESTCallback() {
		delete buffer;
	}
	
	override void OnSuccess( string data, int dataSize ) {
		PrintFormat("%1 OnSuccess called ", "RECOM_MapRendererRestCallback");

		RECOM_MapRendererResponseDto response = new RECOM_MapRendererResponseDto;
		response.ExpandFromRAW(data);

		buffer.update(response);
	};

	override void OnError( int errorCode ) {
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", "RECOM_MapRendererRestCallback", errorCode);
	};

}