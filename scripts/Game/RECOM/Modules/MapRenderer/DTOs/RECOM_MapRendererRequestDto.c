class RECOM_MapRendererRequestDto : JsonApiStruct {

	string Authorization;
    string mapName;


	void RECOM_MapRendererRequestDto() {
		RegV("Authorization");
		RegV("mapName");
	}

	void ~RECOM_MapRendererRequestDto() {
	}

}