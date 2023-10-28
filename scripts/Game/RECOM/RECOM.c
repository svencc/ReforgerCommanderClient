class RECOM {
	
	protected ref static RECOM context;
		
	protected ref RECOM_PropertiesModule properties;
	protected ref RECOM_AuthenticationModule authentication;
	
	protected ref RECOM_MessageBusModule messageBus;
	protected ref RECOM_MapScannerModule mapScanner;
	protected ref RECOM_MapRendererModule mapRenderer;
	
	protected ref RECOM_MB_Observer obs;

	
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
		delete properties;
		delete authentication;
		delete messageBus;
		delete mapScanner;
		delete mapRenderer;
		delete context;
	}
	
	void init() {
		properties = RECOM_PropertiesModule.getModule();
		authentication = RECOM_AuthenticationModule.getModule();
		
		messageBus = RECOM_MessageBusModule.getModule();
		mapScanner = RECOM_MapScannerModule.getModule();
		mapRenderer = RECOM_MapRendererModule.getModule();
	}
	
	void start() {
		if (GetGame().InPlayMode()) {
			properties.start();
			// clock.start();
			authentication.start();
			
			messageBus.start();
			mapRenderer.start();
			
			obs = new RECOM_MB_Observer();
			obs.observe(messageBus.getSubject());
			
		} else if (false) {
			mapScanner.start();
		}
	}
	
	void stop() {
		messageBus.stop();
		GetGame().GetCallqueue().Clear();
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
	
	RECOM_MapScannerModule mapScanner() {
		return mapScanner;
	}
	
	RECOM_MapRendererModule mapRenderer() {
		return mapRenderer;
	}

}