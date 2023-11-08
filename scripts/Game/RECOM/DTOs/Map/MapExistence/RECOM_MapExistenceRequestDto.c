class RECOM_MapExistenceRequestDto : JsonApiStruct {

	string Authorization;
    string mapName;


	void RECOM_MapExistenceRequestDto() {
		RegV("Authorization");
		RegV("mapName");
	}

	void ~RECOM_MapExistenceRequestDto() {
	}

}