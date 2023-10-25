class RECOM_MapRendererRequestDto : JsonApiStruct {

	string Authorization;
    string mapName;
    int timestampEpochMilliseconds;


	void RECOM_MapRendererRequestDto() {
		RegV("Authorization");
		RegV("mapName");
		RegV("timestampEpochMilliseconds");
	}

	void ~RECOM_MapRendererRequestDto() {
	}

}