[EntityEditorProps(category: "RECOM", description: "RECOM")]
class RECOM_TestBootstrapperClass: SCR_BaseTriggerEntityClass {};

class RECOM_TestBootstrapper: SCR_BaseTriggerEntity {

	void ~RECOM_TestBootstrapper() {
		GetGame().GetCallqueue().Clear();
	}

	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		
		if (GetGame().InPlayMode()) {
			RECOM.getContext().authentication().authenticate();
		}
			
		if (GetGame().InPlayMode()) {
			GetGame().GetCallqueue().CallLater(RECOM.getContext().authentication().reauthenticate, 1000, true); // <<<< TODO define value && hide behind injector facade
		}

		//if (GetGame().InPlayMode()) {
		if (false) {					
			GetGame().GetCallqueue().CallLater(RECOM.getContext().mapScanner().produce, 0, true);
			GetGame().GetCallqueue().CallLater(RECOM.getContext().mapScanner().consume, 0, true);
		}
		
		if (GetGame().InPlayMode()) {
		// if (false) {
			GetGame().GetCallqueue().CallLater(RECOM.getContext().mapRenderer().renderClusterList, 1000, true);
		}
		
		if (GetGame().InPlayMode()) {
		//if (false) {
			RECOM_MessageBusModule messageBus = new RECOM_MessageBusModule();
			messageBus.startLongPoll();
		}
	}

};