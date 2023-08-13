class RECOM_AuthenticationResponseDto : JsonApiStruct {

    string bearerToken;
    string issuedAt;
    string expiresAt;
    int expiresInSeconds;

	void RECOM_AuthenticationResponseDto() {
		RegV("bearerToken");
		RegV("issuedAt");
		RegV("expiresAt");
		RegV("expiresInSeconds");
	}

	void ~RECOM_AuthenticationResponseDto() {
	}
	
	string getBearerToken() {
		return "Bearer " + bearerToken;
	}

}