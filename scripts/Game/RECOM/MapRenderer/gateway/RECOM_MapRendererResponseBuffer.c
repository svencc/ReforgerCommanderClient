class RECOM_MapRendererResponseBuffer {

	ref RECOM_MapRendererResponseDto bufferedValue;


	void RECOM_MapRendererResponseBuffer() {
	}

	void ~RECOM_MapRendererResponseBuffer() {
	}


	bool hasData() {
		return !(bufferedValue == null);
	}
	
	RECOM_MapRendererResponseDto read() {
		return bufferedValue;
	}
	
	void update(RECOM_MapRendererResponseDto response) {
		bufferedValue = response;
	}

}