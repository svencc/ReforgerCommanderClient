class RECOM_AuthenticationResponseRESTCallback : RestCallback {

	ref RECOM_AuthenticationResponseBuffer authenticationResponseBuffer;
	
	void RECOM_AuthenticationResponseRESTCallback(RECOM_AuthenticationResponseBuffer authenticationResponseBuffer) {
		this.authenticationResponseBuffer = authenticationResponseBuffer
	}
	
	
	override void OnSuccess( string data, int dataSize ) {
		RECOM_AuthenticationResponseDto authenticationResponseDto = new RECOM_AuthenticationResponseDto;
		authenticationResponseDto.ExpandFromRAW(data);
		authenticationResponseBuffer.update(authenticationResponseDto);
	};

	override void OnError( int errorCode ) {
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", "RECOM_AuthenticationResponseRESTCallback", errorCode);
	};

}