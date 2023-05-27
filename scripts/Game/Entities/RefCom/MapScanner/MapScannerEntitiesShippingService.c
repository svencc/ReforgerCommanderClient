class MapScannerEntitiesShippingService {

	string url = "/api/v1/map-scanner/map-entities";

	private int maxPackageSizeBeforeTransmission;
	private ref RestContext postContext;
	private ref MapScannerEntityPackageDto entitiesPackage;

	void MapScannerEntitiesShippingService(int maxPackageSize) {
		maxPackageSizeBeforeTransmission = maxPackageSize;
		entitiesPackage = new MapScannerEntityPackageDto();
		postContext = GetGame().GetRestApi().GetContext("localhost:8080");
	}

	void ~MapScannerEntitiesShippingService() {
	}
	
	int getMaxPackageSizeBeforeTransmission() {
		return maxPackageSizeBeforeTransmission;
	}

	void assemblePackage(MapScannerEntityDto entity) {
		entitiesPackage.entities.Insert(entity);
		if (entitiesPackage.entities.Count() > maxPackageSizeBeforeTransmission) {
			flush();
			entitiesPackage.entities.Clear();
		}

	}

	void flush() {
		if(entitiesPackage.entities.IsEmpty() == false) {
			entitiesPackage.Pack();
			postContext.POST_now(url, entitiesPackage.AsString());	
		}
	}

}