class RECOM_ClusterBuffer {

	ref RECOM_ClusterResponseDto bufferedValue;
	
	
	void RECOM_ClusterBuffer() {
	}

	void ~RECOM_ClusterBuffer() {
	}
	
	
	bool hasData() {
		return !(bufferedValue == null);
	}
	
	RECOM_ClusterResponseDto read() {
		return bufferedValue;
	}
	
	void update(RECOM_ClusterResponseDto cluster) {
		bufferedValue = cluster;
	}

}