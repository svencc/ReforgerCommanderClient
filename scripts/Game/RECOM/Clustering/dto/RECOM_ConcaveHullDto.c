class RECOM_ConcaveHullDto : JsonApiStruct {

    ref array<ref RECOM_Point2DDto> vertices = {};

	void RECOM_ConcaveHullDto() {
		RegV("vertices");
	}

	void ~RECOM_ConcaveHullDto() {
		vertices.Clear();
	}

}