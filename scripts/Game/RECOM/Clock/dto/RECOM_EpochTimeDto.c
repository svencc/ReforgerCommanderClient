class RECOM_EpochTimeDto : JsonApiStruct {

    int epochSeconds;
    int epochMilliseconds;

	void RECOM_EpochTimeDto() {
		RegV("epochSeconds");
		RegV("epochMilliseconds");
	}

	void ~RECOM_EpochTimeDto() {}

}