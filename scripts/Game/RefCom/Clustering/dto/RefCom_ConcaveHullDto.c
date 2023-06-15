class RefCom_ConcaveHullDto : JsonApiStruct {

    ref array<ref RefCom_Point2DDto> vertices = {};

	void RefCom_ConcaveHullDto() {
		RegV("vertices");
	}

	void ~RefCom_ConcaveHullDto() {
		vertices.Clear();
	}

}