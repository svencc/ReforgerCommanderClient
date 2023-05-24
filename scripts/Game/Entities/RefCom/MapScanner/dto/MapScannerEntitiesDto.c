class MapScannerEntitiesDto : JsonApiStruct {

	ref array<MapScannerEntityDto> entities = {};

	void MapScannerEntitiesDto() {
		RegV("entities");
	}

	void ~MapScannerEntitiesDto() {
		//entities.Clear();
	}

}