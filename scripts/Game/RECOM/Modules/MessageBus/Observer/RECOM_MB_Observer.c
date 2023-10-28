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
			PrintFormat("uuid: %1", message.uuid);
			PrintFormat("messageType: %1", message.messageType);
			PrintFormat("timestampEpochMilliseconds: %1", message.timestampEpochMilliseconds);
			PrintFormat("payload: %1", message.payload);
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