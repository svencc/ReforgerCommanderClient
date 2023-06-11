class RefCom_MapScannerEntitiesTransactionManager {

	protected ref RefCom_TransactionIdentifierDto transactionIdentifier;

	void RefCom_MapScannerEntitiesTransactionManager(string sessionIdentifier) {
		transactionIdentifier = new RefCom_TransactionIdentifierDto();
		transactionIdentifier.sessionIdentifier = sessionIdentifier;
	}

	void ~RefCom_MapScannerEntitiesTransactionManager() {
	}

	void openTransaction() {
		transactionIdentifier.packageOrder = 0;
		transactionIdentifier.Pack();
		GetGame().GetRestApi().GetContext(APIs.host).POST_now(APIs.POST_MAP_SCANNER_TRANSACTION_OPEN, transactionIdentifier.AsString());
	}

	void commitTransaction(int packagesSent) {
		transactionIdentifier.packageOrder = (packagesSent + 1);
		transactionIdentifier.Pack();
		GetGame().GetRestApi().GetContext(APIs.host).POST_now(APIs.POST_MAP_SCANNER_TRANSACTION_COMMIT, transactionIdentifier.AsString());
	}

}