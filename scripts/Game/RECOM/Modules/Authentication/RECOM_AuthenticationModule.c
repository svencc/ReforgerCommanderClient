class RECOM_AuthenticationModule : RECOM_BaseModule {
	
	private static ref RECOM_AuthenticationModule instance;
	protected ref RECOM_AuthenticationRESTGateway restGateway;
	protected ref RECOM_AuthenticationResponseBuffer buffer;

	static RECOM_AuthenticationModule getModule() {
        if (!RECOM_AuthenticationModule.instance) {
            RECOM_AuthenticationModule.instance = new RECOM_AuthenticationModule();
        }
        return RECOM_AuthenticationModule.instance;
    }
	
	private void RECOM_AuthenticationModule() {
		buffer = new RECOM_AuthenticationResponseBuffer();
		restGateway = new RECOM_AuthenticationRESTGateway(buffer);
	}

	void ~RECOM_AuthenticationModule() {
		restGateway = null;
		buffer = null;
		RECOM_AuthenticationModule.instance = null;
	}	
	
	override void start() {
		super.start();
		authenticate();
	}
	
	override void dispose() {
		super.dispose();
		RECOM_AuthenticationModule.instance = null;
	}
	
	protected void authenticate() {
		if (RECOM.getContext().properties().getProperties().enableAuthentication) {
			restGateway.authenticateWith(RECOM.getContext().properties().getProperties());
		} else {
			Print("AUTHENTICATION is disabled", LogLevel.ERROR);
		}
	}

	protected RECOM_AuthenticationResponseBuffer getAuthenticationBuffer() {
		return this.buffer;
	}


    protected bool isAuthenticationEnabled() {
		return RECOM.getContext().properties().getProperties().enableAuthentication;
	}
	
    bool isAuthenticated() {
		if(!RECOM.getContext().properties().getProperties().enableAuthentication) {
			return false;
		} else {
			if (buffer.hasData()) {
				RECOM_AuthenticationResponseDto authentication = buffer.read();
				if (willExpireSoon(authentication)) {
					authenticate();
				}
					
				return !isExpired(authentication);
			}
			
			return false;
		}
    }
	
    string getBearerToken() {
        // @TODO:   implement timer on basis of System.GetUnixTime(),
        //          fetch servertime only once, calculate diff and then use timer (+diff) to check if token is expired
        //	int epochTime = System.GetUnixTime();
		reauthenticate();
        return buffer.read().getBearerToken();
    }
	
	void reauthenticate() {
		RECOM_AuthenticationResponseDto authentication = buffer.read();
		if (willExpireSoon(authentication)) {
			PrintFormat(" ----- Trigger Re-Authentication ----- ");
			authenticate();
		}
	}
	
	private bool willExpireSoon(RECOM_AuthenticationResponseDto authentication) {
		if (authentication == null) {
			return true;
		} else {
			return System.GetUnixTime() > (authentication.expiresAtEpoch - RECOM.getContext().properties().getProperties().preExpirationTimeInSeconds);
		}
	}
	
	private bool isExpired(RECOM_AuthenticationResponseDto authentication) {
	    if (authentication == null) {
            return true;
        } else {
		    return System.GetUnixTime() > authentication.expiresAtEpoch;
        }
	}

}