class RECOM_CreateMap_Gateway {
	
	protected ref RECOM_CreateMapRESTCallback callback;


	void RECOM_CreateMap_Gateway() {
		callback = new RECOM_CreateMapRESTCallback(this);
	}

	void ~RECOM_CreateMap_Gateway() {
		callback = null;
	}
	
	void createMap() {
		if (RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			RECOM_MapExistenceRequestDto requestDto = new RECOM_MapExistenceRequestDto();
			
			RECOM_MapMeta mapMeta = RECOM_MapMetaProvider.provide();
			requestDto.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
			requestDto.mapName = mapMeta.mapName;
			requestDto.dimensionXInMeter = mapMeta.dimensionXInMeter;
			requestDto.dimensionYInMeter = mapMeta.dimensionYInMeter;
			requestDto.dimensionZInMeter = mapMeta.dimensionZInMeter;
			requestDto.oceanBaseHeight = mapMeta.oceanBaseHeight;

			requestDto.Pack();
			SLF4R.debugging(string.Format(" ! ! ! %1 provideData()", ClassName()));
			GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST(callback, RECOMAPIs.POST_CREATE_MAP, requestDto.AsString());
		} else {
			// try again until we are authenticated
			SLF4R.debugging(string.Format(" ! ! ! %1 reschedule", ClassName()));
			GetGame().GetCallqueue().CallLater(createMap, 1000, false);
		}
	}
	
}

