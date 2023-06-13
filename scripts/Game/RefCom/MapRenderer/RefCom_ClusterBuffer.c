class RefCom_ClusterBuffer {

	ref RefCom_ClusterListDto buffer;;
	
	
	
	void RefCom_ClusterBuffer() {
	}

	void ~RefCom_ClusterBuffer() {
	}
	
	
	bool hasData() {
		return !(buffer == null);
	}
	
	RefCom_ClusterListDto read() {
		return buffer;
	}
	
	void write(RefCom_ClusterListDto cluster) {
		buffer = cluster;
	}

}