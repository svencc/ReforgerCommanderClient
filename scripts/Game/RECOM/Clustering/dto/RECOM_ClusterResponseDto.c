class RECOM_ClusterResponseDto : JsonApiStruct {

	ref array<ref RECOM_ClusterDto> clusterList = {};

	void RECOM_ClusterResponseDto() {
		RegV("clusterList");
	}

	void ~RECOM_ClusterResponseDto() {
		clusterList.Clear();
	}


	array<ref RECOM_ClusterDto> getClusterList() {
		return clusterList;
	}
	
	
	override void OnExpand()
	{
		Print("OnExpand");
		// Event when expand (unpack) process starts
		// if you want to handle something before process starts (init/clear variables for example)
	}

	
	override void OnSuccess(int errorCode)
	{
		Print("OnSuccess %1", errorCode);
		// errorCode is EJsonApiError
		// Event called when pending store operation is finished - callback when all went as expected
	}

	override void OnError(int errorCode)
	{
		Print("OnError %1", errorCode);
		// errorCode is EJsonApiError
		// Event called when pending store operation is finished - callback when error happened
	}

}