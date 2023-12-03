class RECOM {
	
	protected ref static RECOM context;
	protected bool contextStarted = false;
		
	protected ref RECOM_PropertiesModule properties;
	protected ref SLF4R slf4r;
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
		mapExistence = null;
		mapRenderer = null;
		mapScanner = null;
		mapTopographyScanner = null;

		// test purpose
		observer = null;
		messageBus = null;

		authentication = null;
		//slf4r = null;
		properties = null;

		context = null;
	}
	
	bool isContextStarted() {
		return contextStarted;
	}

	void init() {
		// DI here? would make sense here!
		properties = RECOM_PropertiesModule.getModule();
		slf4r = SLF4R.getModule();
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
			slf4r.startModule();
			authentication.startModule();
			
			messageBus.startModule();
			
			mapTopographyScanner.startModule();
			mapScanner.startModule();
			//mapRenderer.startModule();
			mapExistence.startModule();
			
			
			// just here for test
			observer = new RECOM_MB_Observer();
			observer.observe(messageBus.getSubject());
			
			
			contextStarted = true;
		} else if (false) {
			// ...
		}
		
		SLF4R.spam(string.Format("spam %1", ClassName()));
		SLF4R.debugging(string.Format("debbuging %1", ClassName()));
		SLF4R.error(string.Format("error %1", ClassName()));
		SLF4R.fatal(string.Format("fatal %1", ClassName()));
		SLF4R.normal(string.Format("normal %1", ClassName()));
		SLF4R.warning(string.Format("warning %1", ClassName()));
		SLF4R.verbose(string.Format("verbose %1", ClassName()));
	}
	
	void dispose() {
		properties.disposeModule();
		authentication.disposeModule();
		
		messageBus.disposeModule();
		
		mapScanner.disposeModule();
		mapRenderer.disposeModule();
		mapExistence.disposeModule();
		
		observer.dispose();
		
		contextStarted = false;
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