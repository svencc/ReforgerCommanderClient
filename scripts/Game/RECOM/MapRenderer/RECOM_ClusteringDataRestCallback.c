class RECOM_ClusteringDataRestCallback : RestCallback {

	ref RECOM_ClusterBuffer clusterBuffer;
	
	void RECOM_ClusteringDataRestCallback(RECOM_ClusterBuffer clusterBuffer) {
		this.clusterBuffer = clusterBuffer
	}
	
	
	override void OnSuccess( string data, int dataSize )
	{
		PrintFormat("%1 OnSuccess called ", "RECOM_ClusteringDataRestCallback");

		RECOM_ClusterListDto clusterListDto = new RECOM_ClusterListDto;
		clusterListDto.ExpandFromRAW(data);

		clusterBuffer.write(clusterListDto);
	};

	override void OnError( int errorCode )
	{
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", "DemonstrationDataRestCallback", errorCode);
	};

}