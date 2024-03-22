class RECOM_MessageBus_ChunkScanner_Observer : RECOM_MessageBus_Observer {
	
	override void takeNotice(
		notnull RECOM_MessageBus_Subject subject, 
		notnull RECOM_MessageBus_ResponseDto notification
	) {
		foreach(RECOM_MessageBus_MessageDto message: notification.messages) {
			if (RECOM_MessageTypes.isREQUEST_MAP_CHUNK(message.messageType)) {

				message.payload;
				
				RECOM_MapTopographyChunkRequestDto request = new RECOM_MessageBus_ResponseDto();
				request.ExpandFromRAW(data);
				
				int chunkX = 0; // request.chunkX
				int chunkZ = 0; // request.chunkZ
				
				RECOM_MapTopographyChunkScanner scanner = new RECOM_MapTopographyChunkScanner(chunkX, chunkZ);
			}
		}
	}

}