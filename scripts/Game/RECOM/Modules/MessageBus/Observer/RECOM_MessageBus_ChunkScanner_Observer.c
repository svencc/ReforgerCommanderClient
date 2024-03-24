class RECOM_MessageBus_ChunkScanner_Observer : RECOM_MessageBus_Observer {
	
	protected ref array<ref RECOM_MapTopographyChunkScanner> scanners =  {}; // deregister
	
	override void takeNotice(
		notnull RECOM_MessageBus_Subject subject, 
		notnull RECOM_MessageBus_ResponseDto notification
	) {
		foreach(RECOM_MessageBus_MessageDto message: notification.messages) {
			if (RECOM_MessageTypes.isREQUEST_MAP_CHUNK(message.messageType)) {
				RECOM_MessageBus_MapTopographyChunkScanRequestDto chunkRequest = new RECOM_MessageBus_MapTopographyChunkScanRequestDto();
				chunkRequest.ExpandFromRAW(message.payload);
				
				SLF4R.normal(string.Format("%1: Request Chunk generation for %2 : x%3,y%4", ClassName(), chunkRequest.mapName, chunkRequest.chunkCoordinateX, chunkRequest.chunkCoordinateY));
				
				ref RECOM_MapTopographyChunkScanner scanner = new RECOM_MapTopographyChunkScanner(chunkRequest.chunkCoordinateX, chunkRequest.chunkCoordinateY);
				scanners.Insert(scanner);
				
				RECOM_BaseDeregisterDelegate<RECOM_MapTopographyChunkScanner> deregisterDelegate = new RECOM_BaseDeregisterDelegate<RECOM_MapTopographyChunkScanner>(scanners);
				scanner.runScanner(deregisterDelegate);
			}
		}
	}

}