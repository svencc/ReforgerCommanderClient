class RECOM_MessageBus_MapTopographyChunkScanRequestDto : JsonApiStruct {

	string mapName;
	int chunkCoordinateX;
	int chunkCoordinateY;


	void RECOM_MessageBus_MapTopographyChunkScanRequestDto() {
		RegV("mapName");
		RegV("chunkCoordinateX");
		RegV("chunkCoordinateY");
	}

	void ~RECOM_MessageBus_MapTopographyChunkScanRequestDto() {

	}

}