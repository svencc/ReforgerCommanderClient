class RECOM_ClusteringRestAdapter {
	
	ref RECOM_ClusteringDataRestCallback clustersCallback;
	ref RECOM_AuthenticationResponseBuffer authenticationBuffer;
	
	void RECOM_ClusteringRestAdapter(
		RECOM_ClusterBuffer clusterBuffer, 
		RECOM_AuthenticationResponseBuffer authenticationBuffer
	) {
		clustersCallback = new RECOM_ClusteringDataRestCallback(clusterBuffer);
		this.authenticationBuffer = authenticationBuffer;
	}

	void ~RECOM_ClusteringRestAdapter() {
		delete clustersCallback;
		delete authenticationBuffer;
	}
	
	void provideClusterData(string mapName) {
		if (authenticationBuffer.isAuthenticated()) {			
			RECOM_MapClusterRequestDto requestDto = new RECOM_MapClusterRequestDto();
			requestDto.Authorization = authenticationBuffer.read().getBearerToken();
			requestDto.mapName = mapName;
			requestDto.Pack();
		
			GetGame().GetRestApi().GetContext(RECOMAPIs.host).POST(clustersCallback, RECOMAPIs.POST_MAP_CLUSTERS, requestDto.AsString());
		}
	}

}