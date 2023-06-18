class RECOM_NestedTestDataDto : JsonApiStruct {

	string stringValue;
	float numberValue;

	string getStringValue()	{
		return stringValue;
	}
	void setStringValue(string newValue) {
		stringValue = newValue;
	}

	float getNumberValue() {
		return numberValue;
	}
	void setNumberValue(float newValue)	{
		numberValue = newValue;
	}



	override void OnSuccess(int errorCode) {
		Print("On Success NestedTestDataDto " + errorCode);
	}

	// You need to configure (de-)serializer here in constructor via RegV(...)
	void RECOM_NestedTestDataDto()
	{
		RegV("stringValue");
		RegV("numberValue");
	}

}