class RECOM_MessageBus_Callback : RestCallback {

	private ref RECOM_BaseBuffer<RECOM_MessageBus_ResponseDto> buffer;
	private ref RECOM_MessageBus_Gateway gateway;
	
	void RECOM_MessageBus_Callback(
		RECOM_BaseBuffer<RECOM_MessageBus_ResponseDto> buffer,
		RECOM_MessageBus_Gateway gateway
	) {
		this.buffer = buffer;
		this.gateway = gateway;
	}
	
	void ~RECOM_MessageBus_Callback() {
		delete buffer;
		delete gateway;
	}
	
	override void OnSuccess(string data, int dataSize) {
		reschedule(5);
		if (dataSize > 0){
			RECOM_MessageBus_ResponseDto response = new RECOM_MessageBus_ResponseDto;
			response.ExpandFromRAW(data);
			buffer.update(response);
		}
		Print("OnSuccess()");
	};

	override void OnError(int errorCode) {
		reschedule(1000);
		Print("OnError()");
	}
	
	override void OnTimeout() {
		reschedule(5);
		Print("OnTimeout()");
	}
	
	private void reschedule(int in) {
		GetGame().GetCallqueue().CallLater(gateway.provideData, in);
	}
	
	private void reschedule() {
		GetGame().GetCallqueue().CallLater(gateway.provideData);
	}

}