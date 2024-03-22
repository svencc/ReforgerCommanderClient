class RECOM_MessageBus_Callback : RestCallback {

	private string latestMessageEpoch;
	private ref RECOM_MessageBus_Subject subject;
	private ref RECOM_MessageBus_Gateway gateway;
	
	void RECOM_MessageBus_Callback(
		notnull RECOM_MessageBus_Subject subject,
		notnull RECOM_MessageBus_Gateway gateway
	) {
		this.subject = subject;
		this.gateway = gateway;
	}
	
	void ~RECOM_MessageBus_Callback() {
		subject = null;
		gateway = null;
	}
	
	override void OnSuccess(
		string data, 
		int dataSize
	) {
		if (dataSize > 0){
			RECOM_MessageBus_ResponseDto response = new RECOM_MessageBus_ResponseDto;
			response.ExpandFromRAW(data);
 			subject.notifyObserversWith(response);
			if (response.epochMillisecondsLastMessage) {
				latestMessageEpoch = response.epochMillisecondsLastMessage;
			}
		}
		reschedule(5);
		SLF4R.debugging(string.Format(" ! ! ! %1 OnSuccess called with errorCode %2", ClassName()));
	};

	override void OnError(int errorCode) {
		reschedule(1000);
		SLF4R.debugging(string.Format(" ! ! ! %1 OnError called with errorCode %2", ClassName(), errorCode));
	}
	
	override void OnTimeout() {
		reschedule(5);
		SLF4R.debugging(string.Format(" ! ! ! %1 OnTimeout called with errorCode %2", ClassName()));
	}
	
	private void reschedule(int in) {
		GetGame().GetCallqueue().CallLater(gateway.provideData, in, false, this.latestMessageEpoch);
	}
	

}