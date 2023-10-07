class RECOM_Line2DDto : JsonApiStruct {

	ref RECOM_Point2DDto start;
	ref RECOM_Point2DDto end;


	void RECOM_Line2DDto() {
		RegV("start");
		RegV("end");
	}

	void ~RECOM_Line2DDto() {

	}

}