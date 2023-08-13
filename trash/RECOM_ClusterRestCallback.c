class RECOM_ClusterRestCallback : RestCallback {

	override void OnSuccess( string data, int dataSize )
	{
		PrintFormat("%1 OnSuccess called ", "RECOM_ClusterRestCallback");

		RECOM_ClusterListDto clusterList = new RECOM_ClusterListDto();
		clusterList.ExpandFromRAW(data);
		
		RECOM_TestDataDto json = new RECOM_TestDataDto;
		json.ExpandFromRAW(data);

		Print("xxx");
	}

	override void OnError( int errorCode )
	{
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", "RECOM_ClusterRestCallback", errorCode);
	};

}