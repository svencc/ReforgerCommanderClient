class RECOM_MapRendererResponseRESTCallback : RestCallback {

	ref RECOM_BaseBuffer<RECOM_MapRendererResponseDto> buffer;
	
	void RECOM_MapRendererResponseRESTCallback(notnull RECOM_BaseBuffer<RECOM_MapRendererResponseDto> buffer) {
		this.buffer = buffer
	}
	
	void ~RECOM_MapRendererResponseRESTCallback() {
		buffer = null;
	}
	
	override void OnSuccess(
		string data, 
		int dataSize
	) {
		SLF4R.debugging(string.Format("%1 OnSuccess called ", ClassName()));

		RECOM_MapRendererResponseDto response = new RECOM_MapRendererResponseDto;
		response.ExpandFromRAW(data);

		buffer.update(response);
	};

	override void OnError(int errorCode) {
		SLF4R.debugging(string.Format(" ! ! ! %1 OnError called with errorCode %2", ClassName(), errorCode));
	};

}