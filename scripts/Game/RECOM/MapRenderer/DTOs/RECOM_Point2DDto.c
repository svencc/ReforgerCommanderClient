class RECOM_Point2DDto : JsonApiStruct {

	float x;
	float y;


	void RECOM_Point2DDto() {
		RegV("x");
		RegV("y");
	}

	void ~RECOM_Point2DDto() {

	}

}