class RECOM_MessageBus_Gateway {
	
	int epochMillisecondsLastMessage = 0;
	protected ref RECOM_MessageBus_Callback callback;

	void RECOM_MessageBus_Gateway(RECOM_MB_Subject subject) {
		callback = new RECOM_MessageBus_Callback(subject, this);
	}

	void ~RECOM_MessageBus_Gateway() {
		delete callback;
	}
	
	void provideData(int epochMillisecondsLastMessage) {
		if (epochMillisecondsLastMessage > this.epochMillisecondsLastMessage) {
			this.epochMillisecondsLastMessage = epochMillisecondsLastMessage;
		}	
		if (RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			RECOM_MapRendererRequestDto requestDto = new RECOM_MapRendererRequestDto();
			requestDto.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
			requestDto.mapName = GetGame().GetWorldFile();
			if (this.epochMillisecondsLastMessage > 0) {
				requestDto.timestampEpochMilliseconds = this.epochMillisecondsLastMessage;
			}
			requestDto.Pack();
		
			GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST(callback, RECOMAPIs.POST_MESSAGE_BUS, requestDto.AsString());
		} else {
			// try again until we are authenticated
			GetGame().GetCallqueue().CallLater(provideData, 1000, false, this.epochMillisecondsLastMessage);
		}
	}
	
}

