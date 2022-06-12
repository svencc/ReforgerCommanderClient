class TestDataDto : JsonApiStruct {

	string stringValue;
	ref array<ref NestedTestDataDto> nestedDataList;
	

	override void OnSuccess( int errorCode )
	{
		Print("On Success TestDataDto " + errorCode);
	}
	
	void TestDataDto() {
		RegV("stringValue");
		RegV("nestedDataList");
	}

}