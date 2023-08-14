class RECOM_AuthenticationProperties : JsonApiStruct {

    bool enableAuthentication;
    int preExpirationTimeInSeconds;
    string accountUUID;
    string accessKey;


	void RECOM_AuthenticationProperties() {
		RegV("enableAuthentication");
		RegV("preExpirationTimeInSeconds");
		RegV("accountUUID");
		RegV("accessKey");
	}

	void ~RECOM_AuthenticationProperties() {
	}

}