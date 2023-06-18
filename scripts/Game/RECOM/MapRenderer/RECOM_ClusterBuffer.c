class RECOM_ClusterBuffer {

	ref RECOM_ClusterListDto buffer;;
	
	
	
	void RECOM_ClusterBuffer() {
	}

	void ~RECOM_ClusterBuffer() {
	}
	
	
	bool hasData() {
		return !(buffer == null);
	}
	
	RECOM_ClusterListDto read() {
		return buffer;
	}
	
	void write(RECOM_ClusterListDto cluster) {
		buffer = cluster;
	}

}