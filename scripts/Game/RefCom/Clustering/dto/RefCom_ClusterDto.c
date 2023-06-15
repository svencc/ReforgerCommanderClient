class RefCom_ClusterDto : JsonApiStruct {

    ref array<ref RefCom_Point2DDto> points = {};
	ref RefCom_ConvexHullDto convexHull;
	ref RefCom_ConcaveHullDto concaveHull;


	void RefCom_ClusterDto() {
		RegV("points");
		RegV("convexHull");
		RegV("concaveHull");
	}

	void ~RefCom_ClusterDto() {
		points.Clear();
	}

}