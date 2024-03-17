class RECOM_MapTopographyEntityDto : JsonApiStruct {

	int chunkSizeX;
	int chunkSizeZ;
	int chunkCoordinateX;
	int chunkCoordinateZ;
	vector coordinates;


	void RECOM_MapTopographyEntityDto() {
		RegV("chunkSizeX");
		RegV("chunkSizeZ");
		RegV("chunkCoordinateX");
		RegV("chunkCoordinateZ");
		RegV("coordinates");
	}

	void ~RECOM_MapTopographyEntityDto() {

	}

}