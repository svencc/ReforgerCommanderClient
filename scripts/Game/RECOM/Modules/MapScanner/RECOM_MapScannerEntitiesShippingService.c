class RECOM_MapScannerEntitiesShippingService {

	protected int packagesSent;
	protected int maxPackageSizeBeforeFlush;
	protected ref RECOM_TransactionalMapScannerEntityPackageDto entitiesPackage;

	void RECOM_MapScannerEntitiesShippingService(int maxPackageSize) {
		resetSendPackagesCounter();
		maxPackageSizeBeforeFlush = maxPackageSize;
		entitiesPackage = new RECOM_TransactionalMapScannerEntityPackageDto();
	}
	

	void ~RECOM_MapScannerEntitiesShippingService() {
		delete entitiesPackage;
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

	void assemblePackage(RECOM_MapScannerEntityDto entity) {
		entitiesPackage.entities.Insert(entity);
		if (entitiesPackage.entities.Count() > maxPackageSizeBeforeFlush) {
			flush();
		}
	}

	void flush() {
		if (entitiesPackage.entities.IsEmpty() == false) {
			entitiesPackage.packageOrder = provideIncreasedPackageCount();
			entitiesPackage.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
			entitiesPackage.Pack();
			GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST_now(RECOMAPIs.POST_MAP_SCANNER_TRANSACTION_ENTITIES, entitiesPackage.AsString());
			entitiesPackage.entities.Clear();
		}
	}

}