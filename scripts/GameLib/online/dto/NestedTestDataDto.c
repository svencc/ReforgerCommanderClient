class NestedTestDataDto : JsonApiStruct {

	string stringValue;
	float numberValue;
	
	override void OnSuccess( int errorCode )
	{
		Print("On Success NestedTestDataDto " + errorCode);
	}
	
	void NestedTestDataDto() {
		RegV("stringValue");
		RegV("numberValue");
	}

}