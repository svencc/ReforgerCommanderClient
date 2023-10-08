class RECOM_MessageBus_MessageDto : JsonApiStruct {
	
	string uuid;
	RECOM_MessageBus_MessageType messageType;
	int timestampEpochMilliseconds;
	int timestampConfirmationEpochMilliseconds;
	string payload;
	
	
	
	void RECOM_MessageBus_MessageDto() {
		RegV("uuid");
		RegV("messageType");
		RegV("timestampEpochMilliseconds");
		RegV("timestampConfirmationEpochMilliseconds");
		RegV("payload");
	}

	void ~RECOM_MessageBus_MessageDto() {
	}

}