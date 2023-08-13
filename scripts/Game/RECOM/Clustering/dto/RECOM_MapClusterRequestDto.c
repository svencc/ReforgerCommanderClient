class RECOM_MapClusterRequestDto : JsonApiStruct {

    string Authorization;
    string mapName;


	void RECOM_MapClusterRequestDto() {
		RegV("Authorization");
		RegV("mapName");
	}

	void ~RECOM_MapClusterRequestDto() {
	}

}