class RECOM_BaseBuffer<Class t> {

	protected ref t bufferedValue;
	
	void RECOM_BaseBuffer() {}
	void ~RECOM_BaseBuffer() {}


	bool hasData() {
		return !(bufferedValue == null);
	}
	
	t read() {
		return bufferedValue;
	}
	
	void update(notnull t value) {
		bufferedValue = value;
	}

}