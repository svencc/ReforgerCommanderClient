class RefCom_ClusterListDto : JsonApiStruct {

	ref array<ref RefCom_ClusterDto> clusterList = {};

	void RefCom_ClusterListDto() {
		RegV("clusterList");
	}

	void ~RefCom_ClusterListDto() {
		clusterList.Clear();
	}

}