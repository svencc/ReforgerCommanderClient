class RECOM_MapRendererRESTGateway {
	
	ref RECOM_MapRendererResponseRESTCallback mapRendererResponseRESTCallback;

	void RECOM_MapRendererRESTGateway(RECOM_MapRendererResponseBuffer mapRendererResponseBuffer) {
		mapRendererResponseRESTCallback = new RECOM_MapRendererResponseRESTCallback(mapRendererResponseBuffer);
	}

	void ~RECOM_MapRendererRESTGateway() {
		delete mapRendererResponseRESTCallback;
	}
	
	void requestMapRendererData(string mapName) {
		RECOM_MapRendererRequestDto requestDto = new RECOM_MapRendererRequestDto();
		requestDto.mapName = mapName;
		requestDto.Pack();
		
		GetGame().GetRestApi().GetContext(REAPIs.host).POST(mapRendererResponseRESTCallback, REAPIs.POST_MAP_RENDERER, requestDto.AsString());
	}

}