[EntityEditorProps(category: "ReforgerCommander", description: "Reforger Commander")]
class RefCom_TestBootstrapperClass: SCR_BaseTriggerEntityClass
{
};

class RefCom_TestBootstrapper: SCR_BaseTriggerEntity
{
	private ref MapScanner mapScanner;
	
	void ~RefCom_TestBootstrapper() {
		GetGame().GetCallqueue().Clear();
	}
	
	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		PrintFormat("%1 initialized", "RefCom_TestBootstrapper");
		if (GetGame().InPlayMode()) {
			mapScanner = new MapScanner(new MapScannerEntitiesShippingService(1000), 150);
					
			GetGame().GetCallqueue().CallLater(mapScanner.produce, 0, true);
			GetGame().GetCallqueue().CallLater(mapScanner.consume, 0, true);
		}
	}
	
};