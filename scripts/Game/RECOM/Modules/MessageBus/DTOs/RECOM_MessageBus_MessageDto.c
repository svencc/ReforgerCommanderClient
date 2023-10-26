class RECOM_MessageBus_MessageDto : JsonApiStruct {
	
	string uuid;
	string messageType;
	string timestampEpochMilliseconds;
	string payload;
	
	
	
	void RECOM_MessageBus_MessageDto() {
		RegV("uuid");
		RegV("messageType");
		RegV("timestampEpochMilliseconds");
		RegV("payload");
	}

	void ~RECOM_MessageBus_MessageDto() {
	}

}