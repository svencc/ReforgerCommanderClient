[EntityEditorProps(category: "ReforgerCommander", description: "Reforger Commander")]
class RefCom_TestBootstrapperClass: SCR_BaseTriggerEntityClass
{
};

class RefCom_TestBootstrapper: SCR_BaseTriggerEntity
{
	private ref RefCom_MapScanner mapScanner;

	void ~RefCom_TestBootstrapper() {
		GetGame().GetCallqueue().Clear();
	}
	
	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		PrintFormat("%1 initialized", "RefCom_TestBootstrapper");
		if (false) {
		// if (GetGame().InPlayMode()) {
			PrintFormat("%1 run %2", "RefCom_TestBootstrapper", "MapScanner");
			mapScanner = new RefCom_MapScanner(new RefCom_MapScannerEntitiesShippingService(500), 150);
					
			GetGame().GetCallqueue().CallLater(mapScanner.produce, 0, true);
			GetGame().GetCallqueue().CallLater(mapScanner.consume, 0, true);
		}
	}
	
};