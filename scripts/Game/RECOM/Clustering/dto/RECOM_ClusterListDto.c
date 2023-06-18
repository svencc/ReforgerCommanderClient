class RECOM_ClusterListDto : JsonApiStruct {

	ref array<ref RECOM_ClusterDto> clusterList = {};

	void RECOM_ClusterListDto() {
		RegV("clusterList");
	}

	void ~RECOM_ClusterListDto() {
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

	override void OnBufferReady()
	{
		Print("OnBufferReady");
		// this is called after successfull JSON pakc process
		// if you want the buffer's finalised string for any purpose
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