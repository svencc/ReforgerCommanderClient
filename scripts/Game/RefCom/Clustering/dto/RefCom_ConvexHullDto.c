class RefCom_ConvexHullDto : JsonApiStruct {

    ref array<ref RefCom_Point2DDto> vertices = {};

	void RefCom_ConvexHullDto() {
		RegV("vertices");
	}

	void ~RefCom_ConvexHullDto() {
		vertices.Clear();
	}

}