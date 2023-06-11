class RefCom_Point2DDto : JsonApiStruct {

	float x;
	float y;


	void RefCom_Point2DDto() {
		RegV("x");
		RegV("y");
	}

	void ~RefCom_Point2DDto() {

	}

}