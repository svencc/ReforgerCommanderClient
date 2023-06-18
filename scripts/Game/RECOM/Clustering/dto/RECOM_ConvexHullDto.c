class RECOM_ConvexHullDto : JsonApiStruct {

    ref array<ref RECOM_Point2DDto> vertices = {};

	void RECOM_ConvexHullDto() {
		RegV("vertices");
	}

	void ~RECOM_ConvexHullDto() {
		vertices.Clear();
	}

}