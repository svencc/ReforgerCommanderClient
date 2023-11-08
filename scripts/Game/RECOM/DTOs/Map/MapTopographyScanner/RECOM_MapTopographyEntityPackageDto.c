class RECOM_MapTopographyEntityPackageDto : JsonApiStruct {

    string Authorization;
	string sessionIdentifier;
	float packageOrder;
	ref array<ref RECOM_MapTopographyEntityDto> entities = {};

	void RECOM_MapTopographyEntityPackageDto() {
		RegV("Authorization");
		RegV("sessionIdentifier");
		RegV("packageOrder");
		RegV("entities");
	}

	void ~RECOM_MapTopographyEntityPackageDto() {
		entities.Clear();
		entities = null;
	}

}