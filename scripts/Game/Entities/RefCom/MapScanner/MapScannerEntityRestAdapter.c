class MapScannerEntityRestAdapter {

	string url = "/api/v1/map-scanner/map-entity";
	
	private ref RestContext postContext;

	void MapScannerEntityRestAdapter() {
		postContext = GetGame().GetRestApi().GetContext("localhost:8080");
	}

	void ~MapScannerEntityRestAdapter() {

	}
	
	void post(MapScannerEntityDto entity) {
		entity.Pack();
		postContext.POST_now(url, entity.AsString());
	}

}