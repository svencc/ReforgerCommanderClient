[EntityEditorProps(category: "RECOM", description: "RECOM")]
class RECOM_StarterClass: SCR_BaseTriggerEntityClass {};

class RECOM_Starter: SCR_BaseTriggerEntity {

	void ~RECOM_Starter() {
		RECOM.getContext().stop();
	}

	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		RECOM.getContext().start();
	}

};