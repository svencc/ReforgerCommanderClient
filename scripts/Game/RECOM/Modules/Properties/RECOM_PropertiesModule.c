class RECOM_PropertiesModule {

	private static ref RECOM_PropertiesModule instance;
	protected ref RECOM_PropertiesDto properties;
	
	static RECOM_PropertiesModule getModule() {
        if (!RECOM_PropertiesModule.instance) {
            RECOM_PropertiesModule.instance = new RECOM_PropertiesModule();
        }
        return RECOM_PropertiesModule.instance;
    }
	
	void RECOM_PropertiesModule() {
		init();
		loadProperties();
	}


	protected void loadProperties() {
        RECOM_PropertiesDto properties = new RECOM_PropertiesDto();
    	properties.LoadFromFile(RECOMPaths.RECOM_AUTHENTICATION_PROPERTY);
    	this.properties = properties; 
    }

	protected void init() {
		RECOMPaths.ensureBaseDirectoryExists();
		if (!RECOMPaths.fileExists(RECOMPaths.RECOM_AUTHENTICATION_PROPERTY)) {
			RECOM_PropertiesDto properties = new RECOM_PropertiesDto();
        	properties.enableAuthentication = false;
        	properties.preExpirationTimeInSeconds = 10;
        	properties.host = "localhost:8080";
        	properties.accountUUID = "uuid";
        	properties.accessKey = "access-key";
			
	    	properties.PackToFile(RECOMPaths.RECOM_AUTHENTICATION_PROPERTY);
		}
    }

	RECOM_PropertiesDto getProperties() {
		return properties;
	}

}