class RECOM_MessageBus_ChunkScanner_Observer : RECOM_MessageBus_Observer {
	
	protected ref array<ref RECOM_MapTopographyChunkScanner> scanners =  {};
	
	override void takeNotice(
		notnull RECOM_MessageBus_Subject subject, 
		notnull RECOM_MessageBus_ResponseDto notification
	) {
		foreach(RECOM_MessageBus_MessageDto message: notification.messages) {
			if (RECOM_MessageTypes.isREQUEST_MAP_CHUNK(message.messageType)) {
				RECOM_MessageBus_MapTopographyChunkScanRequestDto chunkRequest = new RECOM_MessageBus_MapTopographyChunkScanRequestDto();
				chunkRequest.ExpandFromRAW(message.payload);
				
				ref RECOM_MapTopographyChunkScanner scanner = new RECOM_MapTopographyChunkScanner(chunkRequest.chunkCoordinateX, chunkRequest.chunkCoordinateY);
				scanners.Insert(scanner);
				scanner.runScanner();
				
				// todo; der muss sich nach Abschluss wieder abmelden aus dem array!
			}
		}
	}

}