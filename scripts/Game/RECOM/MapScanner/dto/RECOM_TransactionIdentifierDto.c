class RECOM_TransactionIdentifierDto : JsonApiStruct {

    string Authorization;
	int packageOrder;
	string sessionIdentifier;

	void RECOM_TransactionIdentifierDto() {
		RegV("Authorization");
		RegV("packageOrder");
		RegV("sessionIdentifier");
	}

	void ~RECOM_TransactionIdentifierDto() {
	}

}