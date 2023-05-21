class TestDataDto : JsonApiStruct {

	string stringValue;
	ref array<ref NestedTestDataDto> nestedDataList = {};

	string getStringValue() {
		return stringValue;
	}
	void setStringValue(string newValue) {
		stringValue = newValue;
	}

	array<ref NestedTestDataDto> getNestedDataList() {
		return nestedDataList;
	}
	void setNestedDataList(array<ref NestedTestDataDto> newValue) {
		nestedDataList = newValue;
	}
	void addNestedDataList(NestedTestDataDto newValue) {
		nestedDataList.Insert(newValue);
	}



	override void OnSuccess( int errorCode )
	{
		Print("On Success TestDataDto " + errorCode);
	}

	// You need to configure (de-)serializer here in constructor via RegV(...)
	void TestDataDto() {
		RegV("stringValue");
		RegV("nestedDataList");
	}

}