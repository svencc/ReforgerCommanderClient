class RECOM_MessageBus_RequestDto : JsonApiStruct {
	
	string Authorization;
    string mapName;


	void RECOM_MessageBus_RequestDto() {
		RegV("Authorization");
		RegV("mapName");
	}

	void ~RECOM_MessageBus_RequestDto() {
	}

}