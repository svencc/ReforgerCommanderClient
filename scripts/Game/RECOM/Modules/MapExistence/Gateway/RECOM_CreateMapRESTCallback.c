class RECOM_CreateMapRESTCallback : RestCallback {

	ref RECOM_CreateMap_Gateway gateway;
	
	void RECOM_CreateMapRESTCallback(RECOM_CreateMap_Gateway gateway) {
		this.gateway = gateway;
	}
	
	void ~RECOM_CreateMapRESTCallback() {
		gateway = null;
	}
	
	override void OnSuccess(string data, int dataSize) {
		SLF4R.debugging(string.Format("%1 OnSuccess called ", ClassName()));

		if (dataSize > 0) {
			RECOM_MapExistenceResponseDto response = new RECOM_MapExistenceResponseDto;
			response.ExpandFromRAW(data);
			
			if (response.mapExists) {
				RECOM_MapExistenceModule.getModule().triggerWhenMapCreated();
			} else {
				RECOM_MapExistenceModule.getModule().triggerWhenMapNotExists();
			}
		} else {
			reschedule();
		}
	};

	override void OnTimeout() {
		SLF4R.debugging(string.Format(" ! ! ! %1 OnTimeout called", ClassName()));
		reschedule();
	};


	override void OnError(int errorCode) {
		SLF4R.debugging(string.Format("! ! ! %1 OnError called with errorCode %2", ClassName()));
		reschedule();
	};
	
	private void reschedule() {
		GetGame().GetCallqueue().CallLater(gateway.createMap, 1000);
	}

}