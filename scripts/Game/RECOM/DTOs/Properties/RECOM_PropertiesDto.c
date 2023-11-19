class RECOM_PropertiesDto : JsonApiStruct {

	string host;
    bool enableAuthentication;
    int preExpirationTimeInSeconds;
    string accountUUID;
    string accessKey;
    int synchronizeClockIntervalInSeconds;
    string loggingLevel;


	void RECOM_PropertiesDto() {
		RegV("host");
		RegV("enableAuthentication");
		RegV("preExpirationTimeInSeconds");
		RegV("accountUUID");
		RegV("accessKey");
		RegV("synchronizeClockIntervalInSeconds");
		RegV("loggingLevel");
	}

	void ~RECOM_PropertiesDto() {
	}

}