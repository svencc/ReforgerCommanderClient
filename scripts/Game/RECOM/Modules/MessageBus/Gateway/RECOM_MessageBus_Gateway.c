class RECOM_MessageBus_Gateway {
	
	string epochMillisecondsLastMessage;
	protected ref RECOM_MessageBus_Callback callback;

	void RECOM_MessageBus_Gateway(notnull RECOM_MessageBus_Subject subject) {
		callback = new RECOM_MessageBus_Callback(subject, this);
	}

	void ~RECOM_MessageBus_Gateway() {
		callback = null;
	}
	
	void provideData(string epochMillisecondsLastMessage) {
		if (epochMillisecondsLastMessage) {
			this.epochMillisecondsLastMessage = epochMillisecondsLastMessage;
		}	
		if (RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			RECOM_MessageBus_RequestDto requestDto = new RECOM_MessageBus_RequestDto();
			requestDto.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
			requestDto.mapName = GetGame().GetWorldFile();
			if (this.epochMillisecondsLastMessage) {
				requestDto.sinceEpochMilliseconds = this.epochMillisecondsLastMessage;
			}
			requestDto.Pack();
		
			GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST(callback, RECOMAPIs.POST_MESSAGE_BUS, requestDto.AsString());
		} else {
			// try again until we are authenticated
			GetGame().GetCallqueue().CallLater(provideData, 1000, false, this.epochMillisecondsLastMessage);
		}
	}
	
}

