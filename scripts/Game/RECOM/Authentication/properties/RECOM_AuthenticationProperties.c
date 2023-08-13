class RECOM_AuthenticationProperties : JsonApiStruct {

    bool enableAuthentication;
    string accountUUID;
    string accessKey;


	void RECOM_AuthenticationProperties() {
		RegV("enableAuthentication");
		RegV("accountUUID");
		RegV("accessKey");
	}

	void ~RECOM_AuthenticationProperties() {
	}

}