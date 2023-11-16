class RECOM_TransactionalMapStructureEntityPackageDto : JsonApiStruct {

    string Authorization;
	string sessionIdentifier;
	float packageOrder;
	ref array<ref RECOM_MapStructureEntityDto> entities = {};

	void RECOM_TransactionalMapStructureEntityPackageDto() {
		RegV("Authorization");
		RegV("sessionIdentifier");
		RegV("packageOrder");
		RegV("entities");
	}

	void ~RECOM_TransactionalMapStructureEntityPackageDto() {
		entities.Clear();
		entities = null;
	}

}