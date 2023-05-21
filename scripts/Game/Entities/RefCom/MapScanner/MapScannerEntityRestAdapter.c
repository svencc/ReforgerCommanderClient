//class MapScannerEntityRestAdapter {
//
//	string url = "/api/v1/map-scanner/map-entity";
//
//	void MapScannerEntityRestAdapter() {
//	}
//
//	void ~MapScannerEntityRestAdapter() {
//	}
//
//	void post(MapEntityDto entity) {
//		MapScannerEntityRestCallback postCallback = new MapScannerEntityRestCallback;
//		entity.InstantPack();
//
//		Print("post2");
//		RestContext postContext = g_Game.GetRestApi().GetContext("rcb:8080");
//		postContext.POST(postCallback, url, entity.AsString());
//	}
//
//}