class TransactionIdentifierDto : JsonApiStruct {

	int packageOrder;
	string sessionIdentifier;

	void TransactionIdentifierDto() {
		RegV("packageOrder");
		RegV("sessionIdentifier");
	}

	void ~TransactionIdentifierDto() {
	}

}