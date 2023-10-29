class RECOM_MapExistenceResponseDto : JsonApiStruct {

    string mapName;
    bool mapExists;


	void RECOM_MapExistenceResponseDto() {
		RegV("mapName");
		RegV("mapExists");
	}

	void ~RECOM_MapExistenceResponseDto() {
	}

}