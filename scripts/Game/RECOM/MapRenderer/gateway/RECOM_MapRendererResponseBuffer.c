class RECOM_MapRendererResponseBuffer {

	ref RECOM_MapRendererResponseDto buffer;;


	void RECOM_MapRendererResponseBuffer() {
	}

	void ~RECOM_MapRendererResponseBuffer() {
	}


	bool hasData() {
		return !(buffer == null);
	}
	
	RECOM_MapRendererResponseDto read() {
		return buffer;
	}
	
	void write(RECOM_MapRendererResponseDto mapRendererResponse) {
		buffer = mapRendererResponse;
	}

}