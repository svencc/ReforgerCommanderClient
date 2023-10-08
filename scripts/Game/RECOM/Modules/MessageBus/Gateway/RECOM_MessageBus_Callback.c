class RECOM_MessageBus_Callback : RestCallback {

	ref RECOM_BaseBuffer<RECOM_MessageBus_ResponseDto> buffer;
	
	void RECOM_MessageBus_Callback(RECOM_BaseBuffer<RECOM_MessageBus_ResponseDto> buffer) {
		this.buffer = buffer
	}
	
	
	override void OnSuccess(string data, int dataSize) {
		if (dataSize > 0){
			RECOM_MessageBus_ResponseDto response = new RECOM_MessageBus_ResponseDto;
			response.ExpandFromRAW(data);
			buffer.update(response);
		}
	};

	override void OnError(int errorCode) {
		Print("OnError()");
	}
	
	override void OnTimeout() {
		Print("OnTimeout()");
	}
	

}