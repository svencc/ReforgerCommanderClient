class RECOM_AuthenticationInjector {
	
	private static ref RECOM_AuthenticationInjector instance;
	ref RECOM_AuthenticationController authenticationController;

	void RECOM_AuthenticationInjector() {
		this.authenticationController = new RECOM_AuthenticationController();
	}

	void ~RECOM_AuthenticationInjector() {
		delete authenticationController;
		delete RECOM_AuthenticationInjector.instance;
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
        	return authenticationController.getAuthenticationBuffer().hasData();
		}
    }
	
    string getBearerToken() {
		RECOM_AuthenticationResponseDto authetication = authenticationController.getAuthenticationBuffer().read();
		if(RECOM_Clock.getInstance().time().epochSeconds > (authetication.expiresAt - 10)) {
			PrintFormat("Trigger Re-Authentication");	
			authenticationController.authenticate();
		}
        return authenticationController.getAuthenticationBuffer().read().getBearerToken();
    }
	
	void authenticate() {
		this.authenticationController.authenticate();
	}

}