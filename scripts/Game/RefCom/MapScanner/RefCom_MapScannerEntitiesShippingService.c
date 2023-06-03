class RefCom_MapScannerEntitiesShippingService {

	string url = "/api/v1/map-scanner/map-entities";

	private int packagesSent;
	private int maxPackageSizeBeforeTransmission;
	private ref RestContext postContext;
	private ref RefCom_TransactionalMapScannerEntityPackageDto entitiesPackage;

	void RefCom_MapScannerEntitiesShippingService(int maxPackageSize) {
		resetSendPackagesCounter();
		maxPackageSizeBeforeTransmission = maxPackageSize;
		entitiesPackage = new RefCom_TransactionalMapScannerEntityPackageDto();
		postContext = GetGame().GetRestApi().GetContext("localhost:8080");
	}
	

	void ~RefCom_MapScannerEntitiesShippingService() {
	}
	
	private void resetSendPackagesCounter() {
		packagesSent = 0;
	}
	
	int getPackagesSent() {
		return packagesSent;
	}
	
	private int provideIncreasedPackageCount() {
		packagesSent++;
		
		return packagesSent;
	}
	
	int getMaxPackageSizeBeforeTransmission() {
		return maxPackageSizeBeforeTransmission;
	}
	
	void preparePackage(string worldName) {
		entitiesPackage.sessionIdentifier = worldName;
	}

	void assemblePackage(RefCom_MapScannerEntityDto entity) {
		entitiesPackage.entities.Insert(entity);
		if (entitiesPackage.entities.Count() > maxPackageSizeBeforeTransmission) {
			flush();
		}
	}

	void flush() {
		if (entitiesPackage.entities.IsEmpty() == false) {
			entitiesPackage.packageOrder = provideIncreasedPackageCount();
			entitiesPackage.Pack();
			postContext.POST_now(url, entitiesPackage.AsString());	
			entitiesPackage.entities.Clear();
		}
	}

}