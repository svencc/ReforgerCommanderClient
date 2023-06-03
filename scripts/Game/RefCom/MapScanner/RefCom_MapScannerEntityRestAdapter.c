class RefCom_MapScannerEntityRestAdapter {

	string url = "/api/v1/map-scanner/map-entity";
	
	private ref RestContext postContext;

	void RefCom_MapScannerEntityRestAdapter() {
		postContext = GetGame().GetRestApi().GetContext("localhost:8080");
	}

	void ~RefCom_MapScannerEntityRestAdapter() {

	}
	
	void post(RefCom_MapScannerEntityDto entity) {
		entity.Pack();
		postContext.POST_now(url, entity.AsString());
	}

}