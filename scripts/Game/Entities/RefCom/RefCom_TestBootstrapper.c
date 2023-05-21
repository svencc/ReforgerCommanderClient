[EntityEditorProps(category: "ReforgerCommander", description: "Reforger Commander")]
class RefCom_TestBootstrapperClass: SCR_BaseTriggerEntityClass
{
};

class RefCom_TestBootstrapper: SCR_BaseTriggerEntity
{

	private ref JSONRestDemonstration jsonRestDemonstration;
	
	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		PrintFormat("%1 EOnInit called", "RefCom_TestBootstrapper");
		jsonRestDemonstration = new JSONRestDemonstration;
 		// jsonRestDemonstration.demonstrate();
		
 		GetGame().GetCallqueue().CallLater(jsonRestDemonstration.demonstrate, 100, false);
	}
	
};