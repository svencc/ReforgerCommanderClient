class RECOM_MapRenderCommandDto : JsonApiStruct {

    RECOM_Enum_MapRenderCommandType mapRenderCommandType;
    // string mapRenderCommandType;
    string id;
    ref array<ref RECOM_Point2DDto > geometryVertices = {};
    RECOM_Point2DDto coordinates
    string text;
    int color;
    int colorOutline;
    int zIndex;
    ref array<ref string > tags = {};


	void RECOM_MapRenderCommandDto() {
		RegV("mapRenderCommandType");
		RegV("id");
		RegV("geometryVertices");
		RegV("coordinates");
		RegV("text");
		RegV("color");
		RegV("colorOutline");
		RegV("zIndex");
		RegV("tags");
	}

	void ~RECOM_MapRenderCommandDto() {
		geometryVertices.Clear();
		tags.Clear();
	}

}