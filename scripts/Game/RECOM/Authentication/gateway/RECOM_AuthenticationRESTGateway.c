class RECOM_AuthenticationRESTGateway {
	
	ref RECOM_AuthenticationResponseRESTCallback authenticationResponseRESTCallback;

	void RECOM_AuthenticationRESTGateway(RECOM_AuthenticationResponseBuffer authenticationResponseBuffer) {
		this.authenticationResponseRESTCallback = new RECOM_AuthenticationResponseRESTCallback(authenticationResponseBuffer);
	}

	void ~RECOM_AuthenticationRESTGateway() {
		delete authenticationResponseRESTCallback;
	}
	
	
	void authenticateWith(RECOM_AuthenticationProperties properties) {
		if (properties.enableAuthentication) {
			RECOM_AuthenticationRequestDto requestDto = new RECOM_AuthenticationRequestDto();
			requestDto.accountUUID = properties.accountUUID;
	        requestDto.accessKey = properties.accessKey;
			requestDto.Pack();
			
			GetGame().GetRestApi().GetContext(RECOMAPIs.host).POST(authenticationResponseRESTCallback, RECOMAPIs.POST_AUTHENTICATE, requestDto.AsString());
		}
	}

}