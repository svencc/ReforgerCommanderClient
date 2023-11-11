class RECOM_MapExistence_Gateway {
	
	protected ref RECOM_MapExistenceRESTCallback callback;
	protected ref RECOM_BaseBuffer<RECOM_MapExistenceResponseDto> buffer;


	void RECOM_MapExistence_Gateway(RECOM_BaseBuffer<RECOM_MapExistenceResponseDto> buffer) {
		this.buffer = buffer;
		callback = new RECOM_MapExistenceRESTCallback(buffer, this);
	}

	void ~RECOM_MapExistence_Gateway() {
		buffer = null;
		callback = null;
	}
	
	void provideData() {
		if (RECOM_AuthenticationModule.getModule().isAuthenticated() && !buffer.hasData()) {
			RECOM_MapExistenceRequestDto requestDto = new RECOM_MapExistenceRequestDto();
			requestDto.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
			requestDto.mapName = GetGame().GetWorldFile();

			requestDto.Pack();
			PrintFormat(" ! ! ! %1 provideData()", ClassName());
			GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST(callback, RECOMAPIs.POST_MAP_EXISTS, requestDto.AsString());
		} else {
			// try again until we are authenticated
			GetGame().GetCallqueue().CallLater(provideData, 1000, false);
		}
	}
	
}

