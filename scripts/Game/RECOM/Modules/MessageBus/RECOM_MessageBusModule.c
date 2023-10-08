class RECOM_MessageBusModule {
	
	protected ref RECOM_BaseBuffer<RECOM_MessageBus_ResponseDto> buffer;
	protected ref RECOM_MessageBus_Gateway gateway;
	
	
	void RECOM_MessageBusModule() {
		this.buffer = new RECOM_BaseBuffer<RECOM_MessageBus_ResponseDto>();
		this.gateway = new RECOM_MessageBus_Gateway(buffer);
	}
	
	void ~RECOM_MessageBusModule() {
		delete gateway;
		delete buffer;
	}
	
	void startLongPoll() {
		// GetGame().GetWorldFile()
		string mapName = "x";
		// GetGame().GetCallqueue().CallLater(gateway.provideData, 1000, true, mapName);
		GetGame().GetCallqueue().CallLater(gateway.provideData, 1000, true);
	}
	
}