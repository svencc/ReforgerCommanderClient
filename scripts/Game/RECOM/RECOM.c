class RECOM {
	
	protected ref static RECOM context;
	
	protected ref RECOM_PropertiesModule properties;
	protected ref RECOM_ClockModule clock;
	protected ref RECOM_AuthenticationModule authentication;
	
	protected ref RECOM_MessageBusModule messageBus;
	protected ref RECOM_MapScanner mapScanner;
	protected ref RECOM_MapRendererModule mapRenderer;

	
	static RECOM getContext() {
        if (!RECOM.context) {
            RECOM.context = new RECOM();
        }
		
        return RECOM.context;
    }
	
	void RECOM() {
		init();
	}
	
	void ~RECOM() {}
	
	void init() {
		this.properties = RECOM_PropertiesModule.getModule();
		
		this.clock = RECOM_ClockModule.getModule();
		this.authentication = RECOM_AuthenticationModule.getModule();
		
		this.messageBus = new RECOM_MessageBusModule();
		this.mapScanner = new RECOM_MapScanner(new RECOM_MapScannerEntitiesShippingService(500), 150);
		this.mapRenderer = RECOM_MapRendererModule.getModule();
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
	
	RECOM_MapScanner mapScanner() {
		return mapScanner;
	}
	
	RECOM_MapRendererModule mapRenderer() {
		return mapRenderer;
	}

}