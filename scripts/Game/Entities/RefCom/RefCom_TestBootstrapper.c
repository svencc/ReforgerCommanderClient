[EntityEditorProps(category: "ReforgerCommander", description: "Reforger Commander")]
class RefCom_TestBootstrapperClass: SCR_BaseTriggerEntityClass
{
};

class RefCom_TestBootstrapper: SCR_BaseTriggerEntity
{

	private ref JSONRestDemonstration jsonRestDemonstration;
	private ref MapScanner mapScanner;
	private ref MapScannerIterative mapScannerIterative;
	
	void ~RefCom_TestBootstrapper() {
		GetGame().GetCallqueue().Clear();
		PrintFormat("%1 Destructor called", "RefCom_TestBootstrapper");
	}
	
	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		PrintFormat("%1 EOnInit called", "RefCom_TestBootstrapper");
		if (GetGame().InPlayMode()) {
			PrintFormat("%1 EOnInit called in GameMode", "RefCom_TestBootstrapper");
			jsonRestDemonstration = new JSONRestDemonstration;
			mapScanner = new MapScanner();
			mapScannerIterative = new MapScannerIterative(150);
			

			//GetGame().GetCallqueue().CallLater(jsonRestDemonstration.demonstrate, 100, false);
			// GetGame().GetCallqueue().CallLater(mapScanner.scanMap, 1000, false, 150);
			// mapScanner.scanMap(150);
			

			GetGame().GetCallqueue().CallLater(mapScannerIterative.produce, 0, true);
			GetGame().GetCallqueue().CallLater(mapScannerIterative.consume, 0, true);
		}
	}
	
};