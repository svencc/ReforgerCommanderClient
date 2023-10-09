class RECOM_AuthenticationResponseBuffer {

	ref RECOM_AuthenticationResponseDto bufferedValue;


	void RECOM_AuthenticationResponseBuffer() {
	}

	void ~RECOM_AuthenticationResponseBuffer() {
		delete bufferedValue;
	}


	bool hasData() {
		return !(bufferedValue == null);
	}
	
	RECOM_AuthenticationResponseDto read() {
		return bufferedValue;
	}
	
	void update(RECOM_AuthenticationResponseDto authentication) {
		bufferedValue = authentication;
	}

}