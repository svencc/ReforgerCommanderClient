class RECOM {
	
	protected ref static RECOM context;
		
	protected ref RECOM_PropertiesModule properties;
	protected ref RECOM_ClockModule clock;
	protected ref RECOM_AuthenticationModule authentication;
	
	protected ref RECOM_MessageBusModule messageBus;
	protected ref RECOM_MapScannerModule mapScanner;
	protected ref RECOM_MapRendererModule mapRenderer;

	
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
		delete clock;
		delete authentication;
		delete messageBus;
		delete mapScanner;
		delete mapRenderer;
		delete context;
	}
	
	void init() {
		properties = RECOM_PropertiesModule.getModule();
		clock = RECOM_ClockModule.getModule();
		authentication = RECOM_AuthenticationModule.getModule();
		
		messageBus = RECOM_MessageBusModule.getModule();
		mapScanner = RECOM_MapScannerModule.getModule();
		mapRenderer = RECOM_MapRendererModule.getModule();
	}
	
	void start() {
		if (GetGame().InPlayMode()) {
			properties.start();
			clock.start();
			authentication.start();
			
			messageBus.start();
			mapRenderer.start();
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
	
	RECOM_ClockModule clock() {
		return clock;
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