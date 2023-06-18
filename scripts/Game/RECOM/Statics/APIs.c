class APIs {

	static string host = "localhost:8080";
	
	// /health
	static string GET_HEALTH = "/health";
	
	// /map
	static string GET_MAP_META_MAPS = "/api/v1/map/meta/maps";
	
	static string POST_MAP_SCANNER_TRANSACTION_OPEN = "/api/v1/map/scanner/transaction/open";
	static string POST_MAP_SCANNER_TRANSACTION_ENTITIES = "/api/v1/map/scanner/transaction/entities";
	static string POST_MAP_SCANNER_TRANSACTION_COMMIT = "/api/v1/map/scanner/transaction/commit";
	
	static string POST_MAP_CLUSTERS = "/api/v1/map/clusters";
		
}