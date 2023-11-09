class RECOM_MapExistenceRESTCallback : RestCallback {

	ref RECOM_BaseBuffer<RECOM_MapExistenceResponseDto> buffer;
	ref RECOM_MapExistence_Gateway gateway;
	
	void RECOM_MapExistenceRESTCallback(
		RECOM_BaseBuffer<RECOM_MapExistenceResponseDto> buffer, 
		RECOM_MapExistence_Gateway gateway
	) {
		this.buffer = buffer;
		this.gateway = gateway;
	}
	
	void ~RECOM_MapExistenceRESTCallback() {
		buffer = null;
	}
	
	override void OnSuccess(string data, int dataSize) {
		PrintFormat("%1 OnSuccess called ", ClassName());

		if (dataSize > 0) {
			RECOM_MapExistenceResponseDto response = new RECOM_MapExistenceResponseDto;
			response.ExpandFromRAW(data);
			
			if (response.mapExists) {
				RECOM_MapExistenceModule.getModule().triggerWhenMapExists();
			} else {
				RECOM_MapExistenceModule.getModule().triggerWhenMapNotExists();
			}

			buffer.update(response);
		} else {
			reschedule();
		}
	};

	override void OnTimeout() {
		PrintFormat(" ! ! ! %1 OnTimeout called", ClassName());
		reschedule();
	};


	override void OnError(int errorCode) {
		PrintFormat(" ! ! ! %1 OnError called with errorCode %2", ClassName(), errorCode);
		reschedule();
	};
	
	private void reschedule() {
		GetGame().GetCallqueue().CallLater(gateway.provideData, 1000);
	}

}