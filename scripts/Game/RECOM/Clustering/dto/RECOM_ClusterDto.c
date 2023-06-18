class RECOM_ClusterDto : JsonApiStruct {

    ref array<ref RECOM_Point2DDto> points = {};
	ref RECOM_ConvexHullDto convexHull;
	ref RECOM_ConcaveHullDto concaveHull;


	void RECOM_ClusterDto() {
		RegV("points");
		RegV("convexHull");
		RegV("concaveHull");
	}

	void ~RECOM_ClusterDto() {
		points.Clear();
	}

}