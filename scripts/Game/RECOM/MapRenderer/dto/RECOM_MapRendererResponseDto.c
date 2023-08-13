class RECOM_MapRendererResponseDto : JsonApiStruct {

	ref array<ref RECOM_MapRenderCommandDto> renderCommands = {};


	void RECOM_MapRendererResponseDto() {
		RegV("renderCommands");
	}

	void ~RECOM_MapRendererResponseDto() {
		renderCommands.Clear();
	}

}