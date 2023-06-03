class RefCom_TestDataDto : JsonApiStruct {

	string stringValue;
	ref array<ref RefCom_NestedTestDataDto> nestedDataList = {};

	string getStringValue() {
		return stringValue;
	}
	void setStringValue(string newValue) {
		stringValue = newValue;
	}

	array<ref RefCom_NestedTestDataDto> getNestedDataList() {
		return nestedDataList;
	}
	void setNestedDataList(array<ref RefCom_NestedTestDataDto> newValue) {
		nestedDataList = newValue;
	}
	void addNestedDataList(RefCom_NestedTestDataDto newValue) {
		nestedDataList.Insert(newValue);
	}



	override void OnSuccess( int errorCode )
	{
		Print("On Success TestDataDto " + errorCode);
	}

	// You need to configure (de-)serializer here in constructor via RegV(...)
	void RefCom_TestDataDto() {
		RegV("stringValue");
		RegV("nestedDataList");
	}

}