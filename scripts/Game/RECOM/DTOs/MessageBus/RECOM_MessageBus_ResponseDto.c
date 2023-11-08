class RECOM_MessageBus_ResponseDto : JsonApiStruct {
	
	string mapName;
	string epochMillisecondsLastMessage;
	ref array<ref RECOM_MessageBus_MessageDto> messages = {};
	
	
	void RECOM_MessageBus_ResponseDto() {
		RegV("mapName");
		RegV("epochMillisecondsLastMessage");
		RegV("messages");
	}

	void ~RECOM_MessageBus_ResponseDto() {
		messages.Clear();
	}

}