class RefCom_ClusterRestCallback : RestCallback {

	override void OnSuccess( string data, int dataSize )
	{
		PrintFormat("%1 OnSuccess called ", "RefCom_ClusterRestCallback");

		RefCom_ClusterListDto clusterList = new RefCom_ClusterListDto();
		clusterList.ExpandFromRAW(data);
		
		RefCom_TestDataDto json = new RefCom_TestDataDto;
		json.ExpandFromRAW(data);

		Print("xxx");
	}

	override void OnError( int errorCode )
	{
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", "RefCom_ClusterRestCallback", errorCode);
	};

}