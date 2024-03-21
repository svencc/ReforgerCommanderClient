class RECOM_MessageBus_Subject {

	protected ref array<ref RECOM_MessageBus_Observer> observersWatchingMe = {};

	
	void ~RECOM_MessageBus_Subject() {
		reportMyDeath();
		observersWatchingMe.Clear();
		observersWatchingMe = null;
	}

	void beObservedBy(notnull RECOM_MessageBus_Observer observer) {
        observersWatchingMe.Insert(observer);
    }

	void observationStoppedThrough(notnull RECOM_MessageBus_Observer observer) {
        observersWatchingMe.RemoveItem(observer);
    }

	void notifyObserversWith(notnull RECOM_MessageBus_ResponseDto notification) {
		foreach(RECOM_MessageBus_Observer observer : observersWatchingMe) {
			observer.takeNotice(this, notification);
		}
    }

    void reportMyDeath() {
		foreach(RECOM_MessageBus_Observer observer : observersWatchingMe) {
			observer.takeDeathNoticeFrom(this);
		}
    }
	
}