class MapScannerEntityDto : JsonApiStruct {

	string entityId;
	string className;
	string resourceName;
	vector rotationX;
	vector rotationY;
	vector rotationZ;
	vector coords;


	void MapScannerEntityDto() {
		RegV("entityId");
		RegV("className");
		RegV("resourceName");
		RegV("rotationX");
		RegV("rotationY");
		RegV("rotationZ");
		RegV("coords");
	}

	void ~MapScannerEntityDto() {

	}

}