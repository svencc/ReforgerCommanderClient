class RefCom_MapScannerEntityDto : JsonApiStruct {

	string entityId;
	string name;
	string className;
	string prefabName;
	string resourceName;
	string mapDescriptorType;
	vector rotationX;
	vector rotationY;
	vector rotationZ;
	vector coordinates;


	void RefCom_MapScannerEntityDto() {
		RegV("entityId");
		RegV("name");
		RegV("className");
		RegV("prefabName");
		RegV("resourceName");
		RegV("mapDescriptorType");
		RegV("rotationX");
		RegV("rotationY");
		RegV("rotationZ");
		RegV("coordinates");
	}

	void ~RefCom_MapScannerEntityDto() {

	}

}