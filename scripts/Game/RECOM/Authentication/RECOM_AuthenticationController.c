class RECOM_AuthenticationController {
	
	protected ref RECOM_AuthenticationProperties properties;
	protected ref RECOM_AuthenticationRESTGateway restGateway;
	protected ref RECOM_AuthenticationResponseBuffer buffer;
	
	void RECOM_AuthenticationController() {
		init();
		loadProperties();
		buffer = new RECOM_AuthenticationResponseBuffer();
		restGateway = new RECOM_AuthenticationRESTGateway(buffer);
	}
	
	void ~RECOM_AuthenticationController()	{
		delete properties;
		delete restGateway;
		delete buffer;
	}
	
	void authenticate() {
		if (properties.enableAuthentication) {
			restGateway.authenticateWith(this.properties);
		} else {
			Print("AUTHENTICATION is disabled", LogLevel.ERROR);
		}
	}
	
	RECOM_AuthenticationResponseBuffer getAuthenticationBuffer() {
		return this.buffer;
	}

	void loadProperties() {
        RECOM_AuthenticationProperties properties = new RECOM_AuthenticationProperties();
    	properties.LoadFromFile(RECOMPaths.RECOM_AUTHENTICATION_PROPERTY);
    	this.properties = properties;
    }

	protected void init() {
		RECOMPaths.ensureBaseDirectoryExists();
		if (!RECOMPaths.fileExists(RECOMPaths.RECOM_AUTHENTICATION_PROPERTY)) {
			RECOM_AuthenticationProperties properties = new RECOM_AuthenticationProperties();
        	properties.enableAuthentication = false;
        	properties.accountUUID = "uuid";
        	properties.accessKey = "access-key";
			
	    	properties.PackToFile(RECOMPaths.RECOM_AUTHENTICATION_PROPERTY);
		}
    }
	
	
}
