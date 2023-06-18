class RECOM_JSONRestDemonstration {

	void RECOM_JSONRestDemonstration() {
		PrintFormat("%1 Constructor called", "JSONRestDemonstration");
	}

	void ~RECOM_JSONRestDemonstration() {
		PrintFormat("%1 Destructor called", "JSONRestDemonstration");
	}

	void demonstrate() {
		// #GET CALL:
		// create GET RESTCallback
		RECOM_DemonstrationDataRestCallback getCallback = new RECOM_DemonstrationDataRestCallback;

		// Get REST Context
		RestContext getContext = GetGame().GetRestApi().GetContext("127.0.0.1:8080");
		getContext.GET(getCallback,"/api/v1/test/json-test-data");

		// #POST CALL:
		// create POST RESTCallback
		RECOM_DemonstrationDataRestCallback postCallback = new RECOM_DemonstrationDataRestCallback;

		RECOM_TestDataDto td = new RECOM_TestDataDto;
		td.setStringValue("new-string-value");

		RECOM_NestedTestDataDto ntd1 = new RECOM_NestedTestDataDto;
		RECOM_NestedTestDataDto ntd2 = new RECOM_NestedTestDataDto;
		ntd1.setStringValue("first-string-value");
		ntd1.setNumberValue(42);

		ntd2.setStringValue("second-string-value");
		ntd2.setNumberValue(84);

		td.addNestedDataList(ntd1);
		td.addNestedDataList(ntd2);

		td.Pack();

		// Get REST Context
		RestContext postContext = GetGame().GetRestApi().GetContext("127.0.0.1:8080");
		postContext.POST(postCallback,"/api/v1/test/json-test-data", td.AsString());
	}

}