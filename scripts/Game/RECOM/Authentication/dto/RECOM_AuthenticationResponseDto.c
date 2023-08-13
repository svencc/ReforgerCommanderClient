class RECOM_AuthenticationResponseDto : JsonApiStruct {

    string token;
    string issuedAt;
    int expiresAt;
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