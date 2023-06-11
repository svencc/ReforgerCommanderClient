class RefCom_Line2DDto : JsonApiStruct {

	ref RefCom_Point2DDto start;
	ref RefCom_Point2DDto end;


	void RefCom_Line2DDto() {
		RegV("start");
		RegV("end");
	}

	void ~RefCom_Line2DDto() {

	}

}