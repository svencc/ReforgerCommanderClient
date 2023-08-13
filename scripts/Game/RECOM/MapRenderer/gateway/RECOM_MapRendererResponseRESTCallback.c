class RECOM_MapRendererResponseRESTCallback : RestCallback {

	ref RECOM_MapRendererResponseBuffer mapRendererResponseBuffer;
	
	void RECOM_MapRendererResponseRESTCallback(RECOM_MapRendererResponseBuffer mapRendererResponseBuffer) {
		this.mapRendererResponseBuffer = mapRendererResponseBuffer
	}
	
	
	override void OnSuccess( string data, int dataSize ) {
		PrintFormat("%1 OnSuccess called ", "RECOM_MapRendererRestCallback");

		RECOM_MapRendererResponseDto mapRendererResponseDto = new RECOM_MapRendererResponseDto;
		mapRendererResponseDto.ExpandFromRAW(data);

		mapRendererResponseBuffer.write(mapRendererResponseDto);
	};

	override void OnError( int errorCode ) {
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", "RECOM_MapRendererRestCallback", errorCode);
	};

}