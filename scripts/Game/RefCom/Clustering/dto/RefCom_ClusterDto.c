class RefCom_ClusterDto : JsonApiStruct {

    ref array<ref RefCom_Point2DDto> points = {};
	ref RefCom_ConvexHullDto convexHull;


	void RefCom_ClusterDto() {
		RegV("points");
		RegV("convexHull");
	}

	void ~RefCom_ClusterDto() {
		points.Clear();
	}

}