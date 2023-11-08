class RECOM_MapTopographyEntityDto : JsonApiStruct {

	float surfaceHeight;
	float oceanHeight;
	vector oceanHeightDisplacement;
	float oceanBaseHeight;
	vector coordinates;


	void RECOM_MapTopographyEntityDto() {
		RegV("surfaceHeight");
		RegV("oceanHeight");
		RegV("oceanHeightDisplacement");
		RegV("oceanBaseHeight");
		RegV("coordinates");
	}

	void ~RECOM_MapTopographyEntityDto() {

	}

}