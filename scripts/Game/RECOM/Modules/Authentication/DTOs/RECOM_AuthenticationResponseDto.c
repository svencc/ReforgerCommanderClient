class RECOM_AuthenticationResponseDto : JsonApiStruct {

    string token;
    string issuedAt;
    string expiresAt;
    int expiresAtEpoch;
    int expiresInSeconds;

	void RECOM_AuthenticationResponseDto() {
		RegV("token");
		RegV("issuedAt");
		RegV("expiresAt");
		RegV("expiresInSeconds");
	}

	void ~RECOM_AuthenticationResponseDto() {
	}
	
	string getBearerToken() {
		return "Bearer " + token;
	}

}