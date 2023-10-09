class RECOM_MapRendererRESTGateway {
	
	protected ref RECOM_MapRendererResponseRESTCallback mapRendererResponseRESTCallback;

	void RECOM_MapRendererRESTGateway(RECOM_BaseBuffer<RECOM_MapRendererResponseDto> buffer) {
		mapRendererResponseRESTCallback = new RECOM_MapRendererResponseRESTCallback(buffer);
	}

	void ~RECOM_MapRendererRESTGateway() {
		delete mapRendererResponseRESTCallback;
	}
	
	void provideRenderData(string mapName) {
		if (RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			RECOM_MapRendererRequestDto requestDto = new RECOM_MapRendererRequestDto();
			requestDto.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
			requestDto.mapName = mapName;
			requestDto.Pack();
		
			GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST(mapRendererResponseRESTCallback, RECOMAPIs.POST_MAP_RENDERER, requestDto.AsString());
		}
	}

}