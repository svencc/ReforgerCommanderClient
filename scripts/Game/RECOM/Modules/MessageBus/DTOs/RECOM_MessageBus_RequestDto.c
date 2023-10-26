class RECOM_MessageBus_RequestDto : JsonApiStruct {
	
	string Authorization;
    string mapName;
	string sinceEpochMilliseconds


	void RECOM_MessageBus_RequestDto() {
		RegV("Authorization");
		RegV("mapName");
		RegV("sinceEpochMilliseconds");
	}

	void ~RECOM_MessageBus_RequestDto() {
	}

}