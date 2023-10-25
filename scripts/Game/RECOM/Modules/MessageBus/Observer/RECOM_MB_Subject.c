class RECOM_MB_Subject {

	protected ref array<RECOM_MB_Observer> observersWatchingMe = {};


	void beObservedBy(RECOM_MB_Observer observer) {
        observersWatchingMe.Insert(observer);
    }

	void observationStoppedThrough(RECOM_MB_Observer observer) {
        observersWatchingMe.RemoveItem(observer);
    }

	void notifyObserversWith(RECOM_MessageBus_ResponseDto notification) {
		foreach(RECOM_MB_Observer observer : observersWatchingMe) {
			observer.takeNotice(this, notification);
		}
    }

    void reportMyDeath() {
		foreach(RECOM_MB_Observer observer : observersWatchingMe) {
			observer.takeDeathNoticeFrom(this);
		}
    }
	
}