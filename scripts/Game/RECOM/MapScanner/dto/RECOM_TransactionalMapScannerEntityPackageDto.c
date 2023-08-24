class RECOM_TransactionalMapScannerEntityPackageDto : JsonApiStruct {

    string Authorization;
	string sessionIdentifier;
	float packageOrder;
	ref array<ref RECOM_MapScannerEntityDto> entities = {};

	void RECOM_TransactionalMapScannerEntityPackageDto() {
		RegV("Authorization");
		RegV("sessionIdentifier");
		RegV("packageOrder");
		RegV("entities");
	}

	void ~RECOM_TransactionalMapScannerEntityPackageDto() {
		entities.Clear();
	}

}