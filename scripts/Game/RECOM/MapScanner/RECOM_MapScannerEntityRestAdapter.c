class RECOM_MapScannerEntityRestAdapter {

	protected ref RestContext postContext;

	void RECOM_MapScannerEntityRestAdapter() {
		postContext = GetGame().GetRestApi().GetContext(RECOMAPIs.host);
	}

	void ~RECOM_MapScannerEntityRestAdapter() {

	}
	
	void post(RECOM_MapScannerEntityDto entity) {
		entity.Pack();
		postContext.POST_now(RECOMAPIs.POST_MAP_SCANNER_TRANSACTION_ENTITIES, entity.AsString());
	}

}