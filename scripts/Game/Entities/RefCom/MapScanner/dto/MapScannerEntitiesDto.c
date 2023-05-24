class MapScannerEntitiesDto : JsonApiStruct {

	ref array<ref MapScannerEntityDto> entities = {};

	void MapScannerEntitiesDto() {
		RegV("entities");
	}

	void ~MapScannerEntitiesDto() {
		//entities.Clear();
	}

}