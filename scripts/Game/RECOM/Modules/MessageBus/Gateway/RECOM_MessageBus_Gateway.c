class RECOM_MessageBus_Gateway {
	
	protected ref RECOM_MessageBus_Callback callback;

	void RECOM_MessageBus_Gateway(RECOM_BaseBuffer<RECOM_MessageBus_ResponseDto> buffer) {
		callback = new RECOM_MessageBus_Callback(buffer);
	}

	void ~RECOM_MessageBus_Gateway() {
		delete callback;
	}
	
	//void provideData(string mapName) {
	void provideData() {
		if (RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			RECOM_MapRendererRequestDto requestDto = new RECOM_MapRendererRequestDto();
			requestDto.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
			//requestDto.mapName = mapName;
			requestDto.mapName = "x";
			requestDto.Pack();
		
			GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST(callback, RECOMAPIs.POST_MESSAGE_BUS, requestDto.AsString());
		}
	}
	
}

