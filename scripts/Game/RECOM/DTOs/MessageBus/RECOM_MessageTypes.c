class RECOM_MessageTypes {

	/*
	 * Types: 
	 * TEST, FETCH_MAP_RENDER_DATA, REQUEST_MAP_CHUNK
	 */
	private static string TEST = "TEST";
	private static string FETCH_MAP_RENDER_DATA = "FETCH_MAP_RENDER_DATA";
	private static string REQUEST_MAP_CHUNK = "REQUEST_MAP_CHUNK";
	

	static string TEST() {
		return TEST;
	}
	static bool isTEST(string type) {
		return type == TEST;
	}
	

	static string FETCH_MAP_RENDER_DATA() {
		return FETCH_MAP_RENDER_DATA;
	}
	static bool isFETCH_MAP_RENDER_DATA(string type) {
		return type == FETCH_MAP_RENDER_DATA;
	}
	

	static string REQUEST_MAP_CHUNK() {
		return FETCH_MAP_RENDER_DATA;
	}
	static bool isREQUEST_MAP_CHUNK(string type) {
		return type == REQUEST_MAP_CHUNK;
	}
	
}