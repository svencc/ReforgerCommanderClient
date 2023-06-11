class RefCom_ConvexHullDto : JsonApiStruct {

    ref array<ref RefCom_Point2DDto> lines = {};

	void RefCom_ConvexHullDto() {
		RegV("lines");
	}

	void ~RefCom_ConvexHullDto() {
		lines.Clear();
	}

}