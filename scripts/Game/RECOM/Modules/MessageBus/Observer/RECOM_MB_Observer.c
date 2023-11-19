class RECOM_MB_Observer {
	
	protected ref array<RECOM_MB_Subject> subjects = {};
	
	
	void ~RECOM_MB_Observer() {
		subjects.Clear();
		subjects = null;
	}

	
	void observe(RECOM_MB_Subject subject) {
        subject.beObservedBy(this);
        subjects.Insert(subject);
    }

    void takeNotice(RECOM_MB_Subject subject, RECOM_MessageBus_ResponseDto notification) {
		foreach(RECOM_MessageBus_MessageDto message: notification.messages) {
			SLF4R.debugging(string.Format("uuid: %1", message.uuid));
			SLF4R.debugging(string.Format("messageType: %1", message.messageType));
			SLF4R.debugging(string.Format("timestampEpochMilliseconds: %1", message.timestampEpochMilliseconds));
			SLF4R.debugging(string.Format("payload: %1", message.payload));
		}
	}

	void takeDeathNoticeFrom(RECOM_MB_Subject subject) {
        subjects.RemoveItem(subject);
    }

	void dispose() {
		foreach(RECOM_MB_Subject subject : subjects) {
			subject.observationStoppedThrough(this)
		}
    }

}