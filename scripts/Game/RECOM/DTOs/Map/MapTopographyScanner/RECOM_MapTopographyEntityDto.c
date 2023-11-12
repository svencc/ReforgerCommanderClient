class RECOM_MapTopographyEntityDto : JsonApiStruct {

	float oceanHeight;
	float oceanBaseHeight;
	vector coordinates;


	void RECOM_MapTopographyEntityDto() {
		RegV("oceanHeight");
		RegV("oceanBaseHeight");
		RegV("coordinates");
	}

	void ~RECOM_MapTopographyEntityDto() {

	}

}