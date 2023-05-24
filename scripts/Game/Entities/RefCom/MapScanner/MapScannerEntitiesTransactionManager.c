class MapScannerEntitiesTransactionManager {

	string urlOpenTransaction = "/api/v1/map-scanner/transaction/open";
	string urlCommitTransaction = "/api/v1/map-scanner/transaction/commit";

	private ref RestContext postContext;;
	private ref TransactionIdentifierDto transactionIdentifier;

	void MapScannerEntitiesTransactionManager(string sessionIdentifier) {
		transactionIdentifier = new TransactionIdentifierDto();
		transactionIdentifier.sessionIdentifier = sessionIdentifier;
		
		postContext = GetGame().GetRestApi().GetContext("localhost:8080");
	}

	void ~MapScannerEntitiesTransactionManager() {
	}

	void openTransaction() {
		transactionIdentifier.Pack();
		postContext.POST_now(urlOpenTransaction, transactionIdentifier.AsString());
	}

	void commitTransaction() {
		transactionIdentifier.Pack();
		postContext.POST_now(urlCommitTransaction, transactionIdentifier.AsString());
	}
	
}