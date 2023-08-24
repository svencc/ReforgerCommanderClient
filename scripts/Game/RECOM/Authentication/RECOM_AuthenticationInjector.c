class RECOM_AuthenticationInjector {
	
	private static ref RECOM_AuthenticationInjector instance;
	ref RECOM_AuthenticationController authenticationController;

	void RECOM_AuthenticationInjector() {
		this.authenticationController = new RECOM_AuthenticationController();
	}

	void ~RECOM_AuthenticationInjector() {
		delete authenticationController;
		// delete RECOM_AuthenticationInjector.instance;
	}	
	
	static RECOM_AuthenticationInjector getInstance() {
        if (!RECOM_AuthenticationInjector.instance) {
            RECOM_AuthenticationInjector.instance = new RECOM_AuthenticationInjector();
        }
        return RECOM_AuthenticationInjector.instance;
    }
	
	
    bool isAuthenticationEnabled() {
		return authenticationController.getProperties().enableAuthentication;
	}
	
	
    bool isAuthenticated() {
		if(!authenticationController.getProperties().enableAuthentication) {
			return false;
		} else {
			if (authenticationController.getAuthenticationBuffer().hasData()) {
				RECOM_AuthenticationResponseDto authentication = authenticationController.getAuthenticationBuffer().read();
				if (willExpireSoon(authentication)) {
					authenticationController.authenticate();
				}
					
				bool isExpired = isExpired(authentication);
				return !isExpired;
			}
			
			return false;
		}
    }
	
    string getBearerToken() {
//		int epochTime = System.GetUnixTime();
		reauthenticate();
        return authenticationController.getAuthenticationBuffer().read().getBearerToken();
    }
	
	
	void authenticate() {
		this.authenticationController.authenticate();
	}
	
	void reauthenticate() {
		RECOM_AuthenticationResponseDto authentication = authenticationController.getAuthenticationBuffer().read();
		if (willExpireSoon(authentication)) {
			PrintFormat(" ----- Trigger Re-Authentication ----- ");
			authenticationController.authenticate();
		}
	}
	
	private bool willExpireSoon(RECOM_AuthenticationResponseDto authentication) {
		return RECOM_Clock.getInstance().time().epochSeconds > (authentication.expiresAtEpoch - authenticationController.getProperties().preExpirationTimeInSeconds);
	}
	
	private bool isExpired(RECOM_AuthenticationResponseDto authentication) {
		return RECOM_Clock.getInstance().time().epochSeconds > authentication.expiresAtEpoch;
	}

}