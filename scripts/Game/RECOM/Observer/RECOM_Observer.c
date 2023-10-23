class RECOM_Observer<Class T> {
	
	protected ref array<RECOM_Subject<T>> subject = {};

	
	void observe(RECOM_Subject<T> subject) {
        subject.beObservedBy(this);
        subjects.add(subject);
    }

    void takeNotice(RECOM_Subject<T> subject, RECOM_Notification<T> notification) {

	}

	void takeDeathNoticeFrom(RECOM_Subject<T> subject) {
        subjects.Remove(subject);
    }

	void close() {
        subjects.forEach(subject -> subject.observationStoppedThrough(this));
    }

}