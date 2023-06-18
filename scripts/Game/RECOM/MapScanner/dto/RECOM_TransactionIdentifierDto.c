class RECOM_TransactionIdentifierDto : JsonApiStruct {

	int packageOrder;
	string sessionIdentifier;

	void RECOM_TransactionIdentifierDto() {
		RegV("packageOrder");
		RegV("sessionIdentifier");
	}

	void ~RECOM_TransactionIdentifierDto() {
	}

}