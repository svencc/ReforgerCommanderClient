class RECOM_MapTopographyEntityDto : JsonApiStruct {

	float surfaceHeight;
	float oceanHeight;
	float oceanBaseHeight;
	vector coordinates;


	void RECOM_MapTopographyEntityDto() {
		RegV("surfaceHeight");
		RegV("oceanHeight");
		RegV("oceanBaseHeight");
		RegV("coordinates");
	}

	void ~RECOM_MapTopographyEntityDto() {

	}

}