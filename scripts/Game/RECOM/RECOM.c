class RECOM {
	
	protected ref static RECOM context;
		
	protected ref RECOM_PropertiesModule properties;
	protected ref RECOM_AuthenticationModule authentication;
	
	protected ref RECOM_MessageBusModule messageBus;
	
	protected ref RECOM_MapStructureScannerModule mapScanner;
	protected ref RECOM_MapTopographyScannerModule mapTopographyScanner;
	protected ref RECOM_MapRendererModule mapRenderer;
	protected ref RECOM_MapExistenceModule mapExistence;
	
	protected ref RECOM_MB_Observer observer;

	
	static RECOM getContext() {
        if (!RECOM.context) {
            RECOM.context = new RECOM();
        }
        return RECOM.context;
    }
	
	private void RECOM() {
		init();
	}
	
	void ~RECOM() {
		properties = null;
		authentication = null;
		
		messageBus = null;
		
		mapExistence = null;
		mapTopographyScanner = null;
		mapScanner = null;
		mapRenderer = null;
		
		context = null;
		
		// test purpose
		observer = null;
	}
	
	void init() {
		// DI here? would make sense here!
		properties = RECOM_PropertiesModule.getModule();
		authentication = RECOM_AuthenticationModule.getModule();
		
		messageBus = RECOM_MessageBusModule.getModule();
		
		mapTopographyScanner = RECOM_MapTopographyScannerModule.getModule();
		mapScanner = RECOM_MapStructureScannerModule.getModule();
		mapRenderer = RECOM_MapRendererModule.getModule();
		mapExistence = RECOM_MapExistenceModule.getModule();
	}
	
	void start() {
		if (GetGame().InPlayMode()) {
			properties.startModule();
			authentication.startModule();
			
			messageBus.startModule();
			
			mapTopographyScanner.startModule();
			mapScanner.startModule();
			//mapRenderer.startModule();
			mapExistence.startModule();
			
			
			// just here for test
			observer = new RECOM_MB_Observer();
			observer.observe(messageBus.getSubject());
			
		} else if (false) {
			// ...
		}
	}
	
	void dispose() {
		properties.disposeModule();
		authentication.disposeModule();
		
		messageBus.disposeModule();
		
		mapScanner.disposeModule();
		mapRenderer.disposeModule();
		mapExistence.disposeModule();
		
		observer.dispose();
		
		RECOM.context = null;
	}
	
	
	RECOM_PropertiesModule properties() {
		return properties;
	}
	RECOM_AuthenticationModule authentication() {
		return authentication;
	}
	
	
	RECOM_MessageBusModule messageBus() {
		return messageBus;
	}
	
	
	RECOM_MapExistenceModule mapExistence() {
		return mapExistence;
	}
	RECOM_MapStructureScannerModule mapScanner() {
		return mapScanner;
	}
	RECOM_MapTopographyScannerModule mapTopographyScanner() {
		return mapTopographyScanner;
	}
	RECOM_MapRendererModule mapRenderer() {
		return mapRenderer;
	}

}