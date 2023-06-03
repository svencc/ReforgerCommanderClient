class RefCom_TransactionIdentifierDto : JsonApiStruct {

	int packageOrder;
	string sessionIdentifier;

	void RefCom_TransactionIdentifierDto() {
		RegV("packageOrder");
		RegV("sessionIdentifier");
	}

	void ~RefCom_TransactionIdentifierDto() {
	}

}