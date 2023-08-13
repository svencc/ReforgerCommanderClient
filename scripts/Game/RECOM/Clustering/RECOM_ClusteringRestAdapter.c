class RECOM_ClusteringRestAdapter {
	
	ref RECOM_ClusteringDataRestCallback clustersCallback;
	
	void RECOM_ClusteringRestAdapter(RECOM_ClusterBuffer clusterBuffer) {
		clustersCallback = new RECOM_ClusteringDataRestCallback(clusterBuffer);
	}

	void ~RECOM_ClusteringRestAdapter() {
		delete clustersCallback;
	}
	
	void provideClusterData(string mapName) {
		if (RECOM_AuthenticationInjector.getInstance().isAuthenticated()) {
			RECOM_MapClusterRequestDto requestDto = new RECOM_MapClusterRequestDto();
			requestDto.Authorization = RECOM_AuthenticationInjector.getInstance().getBearerToken();
			requestDto.mapName = mapName;
			requestDto.Pack();
		
			GetGame().GetRestApi().GetContext(RECOMAPIs.host).POST(clustersCallback, RECOMAPIs.POST_MAP_CLUSTERS, requestDto.AsString());
		}
	}

}