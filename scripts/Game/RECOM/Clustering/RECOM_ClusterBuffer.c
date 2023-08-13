class RECOM_ClusterBuffer {

	ref RECOM_ClusterResponseDto buffer;;
	
	
	
	void RECOM_ClusterBuffer() {
	}

	void ~RECOM_ClusterBuffer() {
	}
	
	
	bool hasData() {
		return !(buffer == null);
	}
	
	RECOM_ClusterResponseDto read() {
		return buffer;
	}
	
	void write(RECOM_ClusterResponseDto cluster) {
		buffer = cluster;
	}

}