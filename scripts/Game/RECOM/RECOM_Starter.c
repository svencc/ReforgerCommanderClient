[EntityEditorProps(category: "RECOM", description: "RECOM")]
class RECOM_StarterClass: SCR_BaseTriggerEntityClass {};

class RECOM_Starter: SCR_BaseTriggerEntity {

	void ~RECOM_Starter() {
		if (RECOM.getContext().isContextStarted()) {
			GetGame().GetCallqueue().Clear();
			RECOM.getContext().dispose();
		}
	}

	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		if (GetGame().InPlayMode()) {
			GetGame().GetCallqueue().CallLater(RECOM.getContext().start, 0, false);
		}
	}

};