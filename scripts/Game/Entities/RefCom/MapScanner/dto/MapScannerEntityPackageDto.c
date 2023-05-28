class MapScannerEntityPackageDto : JsonApiStruct {

	float packageOrder;
	ref array<ref MapScannerEntityDto> entities = {};

	void MapScannerEntityPackageDto() {
		RegV("packageOrder");
		RegV("entities");
	}

	void ~MapScannerEntityPackageDto() {
		entities.Clear();
	}

}