class RECOM_MapTopographyEntityDto : JsonApiStruct {

	// META DATA
	float stepSize;
	int scanIterationsX;
	int scanIterationsZ;
	float oceanHeight;
	float oceanBaseHeight;
		
	// PACKAGE SPECIFIC DATA
	int iterationX;
	int iterationZ;
	vector coordinates;


	void RECOM_MapTopographyEntityDto() {
		RegV("stepSize");
		RegV("scanIterationsX");
		RegV("scanIterationsZ");
		RegV("oceanHeight");
		RegV("oceanBaseHeight");
		
		RegV("iterationX");
		RegV("iterationZ");
		RegV("coordinates");
	}

	void ~RECOM_MapTopographyEntityDto() {

	}

}