class DemonstrationDataRestCallback : RestCallback {

	override void OnSuccess( string data, int dataSize )
	{
		PrintFormat("%1 OnSuccess called ", "DemonstrationDataRestCallback");
		// Print(data);

		TestDataDto json = new TestDataDto;
		json.ExpandFromRAW(data);

		Print("1 string-value");
		Print(json.getStringValue());

		Print("2.1 string-value");
		Print(json.getNestedDataList());
	};

	override void OnError( int errorCode )
	{
		PrintFormat(" ! ! ! %1 OnError called", "DemonstrationDataRestCallback");
	};

}