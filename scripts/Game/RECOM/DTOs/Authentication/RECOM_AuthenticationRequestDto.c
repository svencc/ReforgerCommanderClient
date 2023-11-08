class RECOM_AuthenticationRequestDto : JsonApiStruct {

    string accountUUID;
    string accessKey;


	void RECOM_AuthenticationRequestDto() {
		RegV("accountUUID");
		RegV("accessKey");
	}

	void ~RECOM_AuthenticationRequestDto() {
	}

}