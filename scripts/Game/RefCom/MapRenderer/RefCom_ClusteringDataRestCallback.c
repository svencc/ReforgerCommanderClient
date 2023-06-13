class RefCom_ClusteringDataRestCallback : RestCallback {

	ref RefCom_ClusterBuffer clusterBuffer;
	
	void RefCom_ClusteringDataRestCallback(RefCom_ClusterBuffer clusterBuffer) {
		this.clusterBuffer = clusterBuffer
	}
	
	
	override void OnSuccess( string data, int dataSize )
	{
		PrintFormat("%1 OnSuccess called ", "RefCom_ClusteringDataRestCallback");

		RefCom_ClusterListDto clusterListDto = new RefCom_ClusterListDto;
		clusterListDto.ExpandFromRAW(data);

		clusterBuffer.write(clusterListDto);
	};

	override void OnError( int errorCode )
	{
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", "DemonstrationDataRestCallback", errorCode);
	};

}