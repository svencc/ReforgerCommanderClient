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
		properties = null;
		authentication = null;
		messageBus = null;
		mapScanner = null;
		mapRenderer = null;
		context = null;
		
		
		
		obs = null;
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
	
	void dispose() {
		// GetGame().GetCallqueue().Clear();
		properties.dispose();
		authentication.dispose();
		messageBus.dispose();
		mapScanner.dispose();
		mapRenderer.dispose();
		
		obs.dispose();
		
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
	
	RECOM_MapScannerModule mapScanner() {
		return mapScanner;
	}
	
	RECOM_MapRendererModule mapRenderer() {
		return mapRenderer;
	}

}