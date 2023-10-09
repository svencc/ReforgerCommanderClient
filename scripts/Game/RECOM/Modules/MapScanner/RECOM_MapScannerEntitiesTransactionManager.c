class RECOM_MapScannerEntitiesTransactionManager {

	protected ref RECOM_TransactionIdentifierDto transactionIdentifier;

	void RECOM_MapScannerEntitiesTransactionManager(string sessionIdentifier) {
		transactionIdentifier = new RECOM_TransactionIdentifierDto();
		transactionIdentifier.sessionIdentifier = sessionIdentifier;
	}

	void ~RECOM_MapScannerEntitiesTransactionManager() {
		delete transactionIdentifier;
	}

	void openTransaction() {
	    transactionIdentifier.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
		transactionIdentifier.packageOrder = 0;
		transactionIdentifier.Pack();
		GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST_now(RECOMAPIs.POST_MAP_SCANNER_TRANSACTION_OPEN, transactionIdentifier.AsString());
	}

	void commitTransaction(int packagesSent) {
		transactionIdentifier.Authorization = RECOM_AuthenticationModule.getModule().getBearerToken();
		transactionIdentifier.packageOrder = (packagesSent + 1);
		transactionIdentifier.Pack();
		GetGame().GetRestApi().GetContext(RECOM.getContext().properties().getProperties().host).POST_now(RECOMAPIs.POST_MAP_SCANNER_TRANSACTION_COMMIT, transactionIdentifier.AsString());
	}

}