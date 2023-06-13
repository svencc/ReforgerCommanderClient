class RefCom_ConvexHullDto : JsonApiStruct {

    ref array<ref RefCom_Point2DDto> points = {};

	void RefCom_ConvexHullDto() {
		RegV("points");
	}

	void ~RefCom_ConvexHullDto() {
		points.Clear();
	}

}