class TransactionalMapScannerEntityPackageDto : JsonApiStruct {

	string sessionIdentifier;
	float packageOrder;
	ref array<ref MapScannerEntityDto> entities = {};

	void TransactionalMapScannerEntityPackageDto() {
		RegV("sessionIdentifier");
		RegV("packageOrder");
		RegV("entities");
	}

	void ~TransactionalMapScannerEntityPackageDto() {
		entities.Clear();
	}

}