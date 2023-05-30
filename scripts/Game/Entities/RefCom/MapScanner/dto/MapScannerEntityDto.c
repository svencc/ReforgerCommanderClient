class MapScannerEntityDto : JsonApiStruct {

	string entityId;
	string name;
	string className;
	string resourceName;
	vector rotationX;
	vector rotationY;
	vector rotationZ;
	vector coordinates;


	void MapScannerEntityDto() {
		RegV("entityId");
		RegV("name");
		RegV("className");
		RegV("resourceName");
		RegV("rotationX");
		RegV("rotationY");
		RegV("rotationZ");
		RegV("coordinates");
	}

	void ~MapScannerEntityDto() {

	}

}