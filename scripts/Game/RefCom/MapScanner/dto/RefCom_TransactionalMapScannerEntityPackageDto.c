class RefCom_TransactionalMapScannerEntityPackageDto : JsonApiStruct {

	string sessionIdentifier;
	float packageOrder;
	ref array<ref RefCom_MapScannerEntityDto> entities = {};

	void RefCom_TransactionalMapScannerEntityPackageDto() {
		RegV("sessionIdentifier");
		RegV("packageOrder");
		RegV("entities");
	}

	void ~RefCom_TransactionalMapScannerEntityPackageDto() {
		entities.Clear();
	}

}