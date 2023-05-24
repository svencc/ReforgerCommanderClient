class TransactionIdentifierDto : JsonApiStruct {

	string sessionIdentifier;

	void TransactionIdentifierDto() {
		RegV("sessionIdentifier");
	}

	void ~TransactionIdentifierDto() {
	}

}