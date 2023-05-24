class MapScannerEntityDto : JsonApiStruct {

	string className;
	string resourceName;
	vector rotationX;
	vector rotationY;
	vector rotationZ;
	vector coords;


	void MapScannerEntityDto() {
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