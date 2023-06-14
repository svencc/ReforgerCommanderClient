class RefCom_MapScannerEntitiesShippingService {

	protected int packagesSent;
	protected int maxPackageSizeBeforeFlush;
	protected ref RefCom_TransactionalMapScannerEntityPackageDto entitiesPackage;

	void RefCom_MapScannerEntitiesShippingService(int maxPackageSize) {
		resetSendPackagesCounter();
		maxPackageSizeBeforeFlush = maxPackageSize;
		entitiesPackage = new RefCom_TransactionalMapScannerEntityPackageDto();
	}
	

	void ~RefCom_MapScannerEntitiesShippingService() {
	}
	
	protected void resetSendPackagesCounter() {
		packagesSent = 0;
	}
	
	int getPackagesSent() {
		return packagesSent;
	}
	
	protected int provideIncreasedPackageCount() {
		packagesSent++;
		
		return packagesSent;
	}
	
	int getMaxPackageSizeBeforeFlush() {
		return maxPackageSizeBeforeFlush;
	}
	
	void setSessionIdentifier(string worldName) {
		entitiesPackage.sessionIdentifier = worldName;
	}

	void assemblePackage(RefCom_MapScannerEntityDto entity) {
		entitiesPackage.entities.Insert(entity);
		if (entitiesPackage.entities.Count() > maxPackageSizeBeforeFlush) {
			flush();
		}
	}

	void flush() {
		if (entitiesPackage.entities.IsEmpty() == false) {
			entitiesPackage.packageOrder = provideIncreasedPackageCount();
			entitiesPackage.Pack();
			GetGame().GetRestApi().GetContext(APIs.host).POST_now(APIs.POST_MAP_SCANNER_TRANSACTION_ENTITIES, entitiesPackage.AsString());	
			entitiesPackage.entities.Clear();
		}
	}

}