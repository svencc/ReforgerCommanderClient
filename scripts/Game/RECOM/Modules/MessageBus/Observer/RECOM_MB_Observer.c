class RECOM_MB_Observer {
	
	protected ref array<RECOM_MB_Subject> subjects = {};

	
	void observe(RECOM_MB_Subject subject) {
        subject.beObservedBy(this);
        subjects.Insert(subject);
    }

    void takeNotice(RECOM_MB_Subject subject, RECOM_MessageBus_ResponseDto notification) {

	}

	void takeDeathNoticeFrom(RECOM_MB_Subject subject) {
        subjects.RemoveItem(subject);
    }

	void close() {
		foreach(RECOM_MB_Subject subject : subjects) {
			subject.observationStoppedThrough(this)
		}
    }

}