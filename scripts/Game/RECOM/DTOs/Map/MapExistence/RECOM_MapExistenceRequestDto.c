class RECOM_MapExistenceRequestDto : JsonApiStruct {

	string Authorization;
    string mapName;
    float dimensionXInMeter;
	float dimensionYInMeter;
	float dimensionZInMeter;
	float oceanBaseHeight;


	void RECOM_MapExistenceRequestDto() {
		RegV("Authorization");
		RegV("mapName");
		RegV("dimensionXInMeter");
		RegV("dimensionYInMeter");
		RegV("dimensionZInMeter");
		RegV("oceanBaseHeight");
	}

	void ~RECOM_MapExistenceRequestDto() {
	}

}