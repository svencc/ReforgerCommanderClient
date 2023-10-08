class RECOM_TimeResponseBuffer {

	ref RECOM_EpochTimeDto bufferedValue;


	void RECOM_TimeResponseBuffer() {
		init()
	}

	void ~RECOM_TimeResponseBuffer() {
	}

		
	private void init() {
		bufferedValue = new RECOM_EpochTimeDto();
		bufferedValue.epochSeconds = 0;
		bufferedValue.epochMilliseconds = 0;
	}
	
	RECOM_EpochTimeDto read() {
		return bufferedValue;
	}
	
	void update(RECOM_EpochTimeDto value) {
		bufferedValue = value;
	}

}