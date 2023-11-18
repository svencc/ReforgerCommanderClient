class RECOMAPIs {

	// static string host = "localhost:8080";
	
	// /health
	static string GET_HEALTH = "/health";

	// /time
	static string GET_TIME = "/api/v1/time";

	// /authenticate
	static string POST_AUTHENTICATE = "/api/v1/authenticate/form";

	// /map
    // static string GET_MAP_META_MAPS = "/api/v1/map/meta/maps";
    static string POST_MAP_EXISTS = "/api/v1/map/exists/form";
    static string POST_CREATE_MAP= "/api/v1/map/create/form";
	
	static string POST_MAP_SCANNER_TRANSACTION_OPEN = "/api/v1/scanner/structure/transaction/open";
	static string POST_MAP_SCANNER_TRANSACTION_ENTITIES = "/api/v1/scanner/structure/transaction/entities";
	static string POST_MAP_SCANNER_TRANSACTION_COMMIT = "/api/v1/scanner/structure/transaction/commit";
	
	static string POST_MAP_SCANNER_TOPOGRAPHY_TRANSACTION_OPEN = "/api/v1/scanner/topography/topography/transaction/open";
	static string POST_MAP_SCANNER_TOPOGRAPHY_TRANSACTION_ENTITIES = "/api/v1/scanner/topography/topography/transaction/entities";
	static string POST_MAP_SCANNER_TOPOGRAPHY_TRANSACTION_COMMIT = "/api/v1/scanner/topography/topography/transaction/commit";
	
	static string POST_MAP_CLUSTERS = "/api/v1/map/clusters/form";
	
	static string POST_MAP_RENDERER = "/api/v1/map/renderer/form";
	
	// /message-bus
	static string POST_MESSAGE_BUS = "/api/v1/message-bus/form";


		
}