class RECOM_MapRendererRESTGateway {
	
	protected ref RECOM_MapRendererResponseRESTCallback mapRendererResponseRESTCallback;

	void RECOM_MapRendererRESTGateway(RECOM_MapRendererResponseBuffer buffer) {
		mapRendererResponseRESTCallback = new RECOM_MapRendererResponseRESTCallback(buffer);
	}

	void ~RECOM_MapRendererRESTGateway() {
		delete mapRendererResponseRESTCallback;
	}
	
	void provideRenderData(string mapName) {
		if (RECOM_AuthenticationInjector.getInstance().isAuthenticated()) {
			RECOM_MapRendererRequestDto requestDto = new RECOM_MapRendererRequestDto();
			requestDto.Authorization = RECOM_AuthenticationInjector.getInstance().getBearerToken();
			requestDto.mapName = mapName;
			requestDto.Pack();
		
			GetGame().GetRestApi().GetContext(RECOMAPIs.host).POST(mapRendererResponseRESTCallback, RECOMAPIs.POST_MAP_RENDERER, requestDto.AsString());
		}
	}

}