class RECOM_MessageBus_Observer {
	
	protected ref array<RECOM_MessageBus_Subject> subjects = {};
	
	
	void ~RECOM_MessageBus_Observer() {
		dispose();
		subjects.Clear();
		subjects = null;
	}

	
	void observe(notnull RECOM_MessageBus_Subject subject) {
        subject.beObservedBy(this);
        subjects.Insert(subject);
    }

    void takeNotice(notnull RECOM_MessageBus_Subject subject, notnull RECOM_MessageBus_ResponseDto notification) {
		foreach(RECOM_MessageBus_MessageDto message: notification.messages) {
			SLF4R.debugging(string.Format("uuid: %1", message.uuid));
			SLF4R.debugging(string.Format("messageType: %1", message.messageType));
			SLF4R.debugging(string.Format("timestampEpochMilliseconds: %1", message.timestampEpochMilliseconds));
			SLF4R.debugging(string.Format("payload: %1", message.payload));
		}
	}

	void takeDeathNoticeFrom(notnull RECOM_MessageBus_Subject subject) {
        subjects.RemoveItem(subject);
    }

	void dispose() {
		foreach(RECOM_MessageBus_Subject subject : subjects) {
			subject.observationStoppedThrough(this)
		}
    }

}