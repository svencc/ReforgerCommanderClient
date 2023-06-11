class RefCom_MapClusterRequestDto : JsonApiStruct {

    string mapName;
    float maximumRadiusOfTheNeighborhoodEpsilon;
    int minimumNumberOfPointsNeededForCluster;


	void RefCom_MapClusterRequestDto() {
		RegV("mapName");
		RegV("maximumRadiusOfTheNeighborhoodEpsilon");
		RegV("minimumNumberOfPointsNeededForCluster");
	}

	void ~RefCom_MapClusterRequestDto() {
	}

}