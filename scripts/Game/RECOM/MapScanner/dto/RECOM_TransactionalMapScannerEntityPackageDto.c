class RECOM_TransactionalMapScannerEntityPackageDto : JsonApiStruct {

	string sessionIdentifier;
	float packageOrder;
	ref array<ref RECOM_MapScannerEntityDto> entities = {};

	void RECOM_TransactionalMapScannerEntityPackageDto() {
		RegV("sessionIdentifier");
		RegV("packageOrder");
		RegV("entities");
	}

	void ~RECOM_TransactionalMapScannerEntityPackageDto() {
		entities.Clear();
	}

}