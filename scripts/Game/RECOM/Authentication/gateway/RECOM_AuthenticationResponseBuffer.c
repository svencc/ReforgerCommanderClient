class RECOM_AuthenticationResponseBuffer {

	ref RECOM_AuthenticationResponseDto buffer;;


	void RECOM_AuthenticationResponseBuffer() {
	}

	void ~RECOM_AuthenticationResponseBuffer() {
	}


	bool isAuthenticated() {
		return !(buffer == null);
	}
	
	RECOM_AuthenticationResponseDto read() {
		return buffer;
	}
	
	void update(RECOM_AuthenticationResponseDto authentication) {
		buffer = authentication;
	}

}