class RECOM_CreateMapRequestDto : JsonApiStruct {

	string Authorization;
    string mapName;


	void RECOM_CreateMapRequestDto() {
		RegV("Authorization");
		RegV("mapName");
	}

	void ~RECOM_CreateMapRequestDto() {
	}

}