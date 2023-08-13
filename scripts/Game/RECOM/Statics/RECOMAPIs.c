class RECOMAPIs {

	static string host = "localhost:8080";
	
	// /health
	static string GET_HEALTH = "/health";

	// /authenticate
	static string POST_AUTHENTICATE = "/api/v1/authenticate/form";

	// /map
    // static string GET_MAP_META_MAPS = "/api/v1/map/meta/maps";
	
	static string POST_MAP_SCANNER_TRANSACTION_OPEN = "/api/v1/map/scanner/transaction/open";
	static string POST_MAP_SCANNER_TRANSACTION_ENTITIES = "/api/v1/map/scanner/transaction/entities";
	static string POST_MAP_SCANNER_TRANSACTION_COMMIT = "/api/v1/map/scanner/transaction/commit";
	
	static string POST_MAP_CLUSTERS = "/api/v1/map/clusters/form";
	static string POST_MAP_RENDERER = "/api/v1/map/renderer/form";
		
}