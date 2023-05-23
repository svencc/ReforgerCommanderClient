class MapScannerEntityRestAdapter {

	string url = "/api/v1/map-scanner/map-entity";
	
	private ref RestContext postContext;

	void MapScannerEntityRestAdapter() {
		postContext = GetGame().GetRestApi().GetContext("localhost:8080");
	}

	void ~MapScannerEntityRestAdapter() {
	}

	void post(MapEntityDto entity) {
        PrintFormat("%1: GetWorldSize post called", "MapScannerEntityRestAdapter");
		MapScannerEntityRestCallback postCallback = new MapScannerEntityRestCallback;
		entity.Pack();


		RestContext postContext = GetGame().GetRestApi().GetContext("localhost:8080");
		postContext.POST(postCallback, url, entity.AsString());
		//postContext.POST_now(url, entity.AsString());
		PrintFormat("%1: GetWorldSize post processed", "MapScannerEntityRestAdapter");
	}
	
	void postNow(MapEntityDto entity) {
		entity.Pack();
		postContext.POST_now(url, entity.AsString());
	}

}