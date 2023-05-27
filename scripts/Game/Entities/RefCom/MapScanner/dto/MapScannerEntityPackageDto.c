class MapScannerEntityPackageDto : JsonApiStruct {

	ref array<ref MapScannerEntityDto> entities = {};

	void MapScannerEntityPackageDto() {
		RegV("entities");
	}

	void ~MapScannerEntityPackageDto() {
		entities.Clear();
	}

}