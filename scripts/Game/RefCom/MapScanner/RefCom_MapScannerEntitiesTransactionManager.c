class RefCom_MapScannerEntitiesTransactionManager {

	string urlOpenTransaction = "/api/v1/map-scanner/transaction/open";
	string urlCommitTransaction = "/api/v1/map-scanner/transaction/commit";

	private ref RestContext postContext;;
	private ref RefCom_TransactionIdentifierDto transactionIdentifier;

	void RefCom_MapScannerEntitiesTransactionManager(string sessionIdentifier) {
		transactionIdentifier = new RefCom_TransactionIdentifierDto();
		transactionIdentifier.sessionIdentifier = sessionIdentifier;
		
		postContext = GetGame().GetRestApi().GetContext("localhost:8080");
	}

	void ~RefCom_MapScannerEntitiesTransactionManager() {
	}

	void openTransaction() {
		transactionIdentifier.packageOrder = 0;
		transactionIdentifier.Pack();
		postContext.POST_now(urlOpenTransaction, transactionIdentifier.AsString());
	}

	void commitTransaction(int packagesSent) {
		transactionIdentifier.packageOrder = (packagesSent + 1);
		transactionIdentifier.Pack();
		postContext.POST_now(urlCommitTransaction, transactionIdentifier.AsString());
	}
	
}