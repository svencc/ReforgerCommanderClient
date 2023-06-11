class RefCom_ClusteringRestAdapter {

	void RefCom_ClusteringRestAdapter() {
	}

	void ~RefCom_ClusteringRestAdapter() {
	}
	
	RefCom_ClusterListDto provideClusterData(string mapName) {
		RefCom_MapClusterRequestDto requestDto = new RefCom_MapClusterRequestDto();
		requestDto.mapName = mapName;
		requestDto.maximumRadiusOfTheNeighborhoodEpsilon = 50.0;
		requestDto.minimumNumberOfPointsNeededForCluster = 6;
		
		requestDto.Pack();
		string response =  GetGame().GetRestApi().GetContext(APIs.host).POST_now(APIs.POST_MAP_CLUSTERS, requestDto.AsString());
		
		RefCom_ClusterListDto clusterList = new RefCom_ClusterListDto();
		clusterList.ExpandFromRAW(response);
		
		return clusterList;
	}

}