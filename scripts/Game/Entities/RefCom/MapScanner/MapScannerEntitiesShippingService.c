class MapScannerEntitiesShippingService {

	string url = "/api/v1/map-scanner/map-entities";

	private int sendPackages;
	private int maxPackageSizeBeforeTransmission;
	private ref RestContext postContext;
	private ref MapScannerEntityPackageDto entitiesPackage;

	void MapScannerEntitiesShippingService(int maxPackageSize) {
		resetSendPackagesCounter();
		maxPackageSizeBeforeTransmission = maxPackageSize;
		entitiesPackage = new MapScannerEntityPackageDto();
		postContext = GetGame().GetRestApi().GetContext("localhost:8080");
	}
	

	void ~MapScannerEntitiesShippingService() {
	}
	
	void resetSendPackagesCounter() {
		sendPackages = 0;
	}
	
	int getSendPackages() {
		return sendPackages;
	}
	
	int provideIncreasedPackageCount() {
		return (sendPackages + 1);
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
		if (entitiesPackage.entities.IsEmpty() == false) {
			entitiesPackage.packageOrder = provideIncreasedPackageCount();
			entitiesPackage.Pack();
			postContext.POST_now(url, entitiesPackage.AsString());	
		}
	}

}