class RECOM_ClusteringDataRestCallback : RestCallback {

	ref RECOM_ClusterBuffer clusterBuffer;
	
	void RECOM_ClusteringDataRestCallback(RECOM_ClusterBuffer clusterBuffer) {
		this.clusterBuffer = clusterBuffer
	}
	
	
	override void OnSuccess( string data, int dataSize )
	{
		PrintFormat("%1 OnSuccess called ", "RECOM_ClusteringDataRestCallback");

		RECOM_ClusterResponseDto clusterListDto = new RECOM_ClusterResponseDto;
		clusterListDto.ExpandFromRAW(data);

		clusterBuffer.update(clusterListDto);
	};

	override void OnError( int errorCode )
	{
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", "DemonstrationDataRestCallback", errorCode);
	};

}