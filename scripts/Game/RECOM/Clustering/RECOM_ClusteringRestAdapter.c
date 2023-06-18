class RECOM_ClusteringRestAdapter {
	
	ref RECOM_ClusteringDataRestCallback clustersCallback;

	void RECOM_ClusteringRestAdapter(RECOM_ClusterBuffer clusterBuffer) {
		clustersCallback = new RECOM_ClusteringDataRestCallback(clusterBuffer);
	}

	void ~RECOM_ClusteringRestAdapter() {
		delete clustersCallback;
	}
	
	void provideClusterData(string mapName) {
		RECOM_MapClusterRequestDto requestDto = new RECOM_MapClusterRequestDto();
		requestDto.mapName = mapName;
		requestDto.Pack();
		
		GetGame().GetRestApi().GetContext(APIs.host).POST(clustersCallback, APIs.POST_MAP_CLUSTERS, requestDto.AsString());
	}

}