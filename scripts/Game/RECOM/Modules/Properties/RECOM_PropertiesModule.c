class RECOM_PropertiesModule : RECOM_BaseModule {

	private static ref RECOM_PropertiesModule instance;
	protected ref RECOM_PropertiesDto properties;
	
	static RECOM_PropertiesModule getModule() {
        if (!RECOM_PropertiesModule.instance) {
            RECOM_PropertiesModule.instance = new RECOM_PropertiesModule();
        }
        return RECOM_PropertiesModule.instance;
    }
	
	override void start() {
		super.start();
		init();
		loadProperties();
	}
	
	override void dispose() {
		super.dispose();
		RECOM_PropertiesModule.instance = null;
	}
	
	void ~RECOM_PropertiesModule()	{
		properties = null;
	}
	
	protected void loadProperties() {
        RECOM_PropertiesDto props = new RECOM_PropertiesDto();
    	props.LoadFromFile(RECOMPaths.RECOM_AUTHENTICATION_PROPERTY);
    	properties = props; 
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
        	properties.synchronizeClockIntervalInSeconds = 600; // 10 Minutes;
			
	    	properties.PackToFile(RECOMPaths.RECOM_AUTHENTICATION_PROPERTY);
		}
    }

	RECOM_PropertiesDto getProperties() {
		return properties;
	}

}