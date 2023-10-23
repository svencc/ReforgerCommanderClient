class RECOM_Subject<Class T> {

	protected ref array<RECOM_Observer<T>> observersWatchingMe = {};



	void beObservedBy(RECOM_Observer<T> observer) {
        observersWatchingMe.add(observer);
    }

	void observationStoppedThrough(RECOM_Observer<T> observer) {
        observersWatchingMe.remove(observer);
    }

	void notifyObserversWith(RECOM_Notification<T> notification) {
		foreach(RECOM_Observer<T> observer : observersWatchingMe) {
			observer.takeNotice(this, notification);
		}
    }

    void reportMyDeath() {
		foreach(RECOM_Observer<T> observer : observersWatchingMe) {
			observer.takeDeathNoticeFrom(this);
		}
    }
	
}