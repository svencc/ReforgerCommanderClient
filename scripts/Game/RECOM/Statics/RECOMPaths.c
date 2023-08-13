class RECOMPaths {

	static string RECOM_BASE = "$profile:RECOM";
	static string RECOM_AUTHENTICATION_PROPERTY = "$profile:RECOM/authentication_properties.json";

	static bool baseExists() {
		return FileIO.FileExists(RECOMPaths.RECOM_BASE);
	}
	
	static void ensureBaseDirectoryExists() {
		if(!baseExists()) {
			FileIO.MakeDirectory("$profile:RECOM");
		}
	}
	
	static bool fileExists(string pathToFile) {
		return FileIO.FileExists(pathToFile);
	}
	
}