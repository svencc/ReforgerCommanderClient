class RefCom_ClusteringRestAdapter {
	
	ref RefCom_ClusteringDataRestCallback clustersCallback;

	void RefCom_ClusteringRestAdapter(RefCom_ClusterBuffer clusterBuffer) {
		clustersCallback = new RefCom_ClusteringDataRestCallback(clusterBuffer);
	}

	void ~RefCom_ClusteringRestAdapter() {
		delete clustersCallback;
	}
	
	void provideClusterData(string mapName) {
		RefCom_MapClusterRequestDto requestDto = new RefCom_MapClusterRequestDto();
		requestDto.mapName = mapName;
		requestDto.maximumRadiusOfTheNeighborhoodEpsilon = 100.0;
		requestDto.minimumNumberOfPointsNeededForCluster = 6;
		requestDto.Pack();
		
		GetGame().GetRestApi().GetContext(APIs.host).POST(clustersCallback, APIs.POST_MAP_CLUSTERS, requestDto.AsString());
	}

}