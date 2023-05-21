class MapScannerEntityRestAdapter {

	string url = "/api/v1/map-scanner/map-entity";

	void MapScannerEntityRestAdapter() {
	}

	void ~MapScannerEntityRestAdapter() {
	}

	void post(MapEntityDto entity) {
        PrintFormat("%1: GetWorldSize post called", "MapScannerEntityRestAdapter");
		MapScannerEntityRestCallback postCallback = new MapScannerEntityRestCallback;
		entity.Pack();


		RestContext postContext = g_Game.GetRestApi().GetContext("localhost:8080");
		postContext.POST(postCallback, url, entity.AsString());
		PrintFormat("%1: GetWorldSize post processed", "MapScannerEntityRestAdapter");
	}

}