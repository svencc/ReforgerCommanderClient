class RefCom_MapScannerEntityRestAdapter {

	protected ref RestContext postContext;

	void RefCom_MapScannerEntityRestAdapter() {
		postContext = GetGame().GetRestApi().GetContext(APIs.host);
	}

	void ~RefCom_MapScannerEntityRestAdapter() {

	}
	
	void post(RefCom_MapScannerEntityDto entity) {
		entity.Pack();
		postContext.POST_now(APIs.POST_MAP_SCANNER_TRANSACTION_ENTITIES, entity.AsString());
	}

}