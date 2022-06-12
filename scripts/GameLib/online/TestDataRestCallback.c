class TestDataRestCallback : RestCallback {
	
	override void OnSuccess( string data, int dataSize )
	{
		// Print(data);
		// --> SCR_CampaignStruct

		TestDataDto json = new TestDataDto;
		json.ExpandFromRAW(data);
		
		Print("1 string-value");
		Print(json.stringValue);
		
		Print("2.1 string-value");
		Print(json.nestedDataList);
	};
	
	override void OnError( int errorCode )
	{
		Print(" !!! OnError() ");
	};
	
}