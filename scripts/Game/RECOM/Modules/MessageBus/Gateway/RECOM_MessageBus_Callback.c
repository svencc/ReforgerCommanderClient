class RECOM_MessageBus_Callback : RestCallback {

	private string latestMessageEpoch;
	private ref RECOM_MB_Subject subject;
	private ref RECOM_MessageBus_Gateway gateway;
	
	void RECOM_MessageBus_Callback(
		RECOM_MB_Subject subject,
		RECOM_MessageBus_Gateway gateway
	) {
		this.subject = subject;
		this.gateway = gateway;
	}
	
	void ~RECOM_MessageBus_Callback() {
		subject = null;
		gateway = null;
	}
	
	override void OnSuccess(string data, int dataSize) {
		if (dataSize > 0){
			RECOM_MessageBus_ResponseDto response = new RECOM_MessageBus_ResponseDto;
			response.ExpandFromRAW(data);
 			subject.notifyObserversWith(response);
			if (response.epochMillisecondsLastMessage) {
				latestMessageEpoch = response.epochMillisecondsLastMessage;
			}
		}
		reschedule(5);
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
		GetGame().GetCallqueue().CallLater(gateway.provideData, in, false, this.latestMessageEpoch);
	}
	

}