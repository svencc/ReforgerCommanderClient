class RECOM_MessageBus_ResponseDto : JsonApiStruct {
	
	ref array<ref RECOM_MessageBus_MessageDto> messages = {};
	
	
	void RECOM_MessageBus_ResponseDto() {
		RegV("messages");
	}

	void ~RECOM_MessageBus_ResponseDto() {
		messages.Clear();
	}

}