class RECOM_MapTopographyScannerEntitiesTransactionManager {
	
	protected ref RECOM_TransactionIdentifierDto transactionIdentifier;

	void RECOM_MapTopographyScannerEntitiesTransactionManager(string sessionIdentifier) {
		transactionIdentifier = new RECOM_TransactionIdentifierDto();
		transactionIdentifier.sessionIdentifier = sessionIdentifier;
	}

	void ~RECOM_MapTopographyScannerEntitiesTransactionManager() {
		transactionIdentifier = null;
	}

	void openTransaction() {
	    transactionIdentifier.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
		transactionIdentifier.packageOrder = 0;
		transactionIdentifier.Pack();
		GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST_now(RECOMAPIs.POST_MAP_SCANNER_TOPOGRAPHY_TRANSACTION_OPEN, transactionIdentifier.AsString());
	}

	void commitTransaction(int packagesSent) {
		transactionIdentifier.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
		transactionIdentifier.packageOrder = (packagesSent + 1);
		transactionIdentifier.Pack();
		GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST_now(RECOMAPIs.POST_MAP_SCANNER_TOPOGRAPHY_TRANSACTION_COMMIT, transactionIdentifier.AsString());
	}

}