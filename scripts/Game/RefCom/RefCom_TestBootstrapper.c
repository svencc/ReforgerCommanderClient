[EntityEditorProps(category: "ReforgerCommander", description: "Reforger Commander")]
class RefCom_TestBootstrapperClass: SCR_BaseTriggerEntityClass
{
};

class RefCom_TestBootstrapper: SCR_BaseTriggerEntity
{
	protected ref RefCom_MapScanner mapScanner;
	protected ref RefCom_MapRendererController mapRendererController;

	void ~RefCom_TestBootstrapper() {
		GetGame().GetCallqueue().Clear();
		delete mapScanner;
		delete mapRendererController;
	}
	
	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		PrintFormat("%1 initialized", "RefCom_TestBootstrapper");
		
		//if (GetGame().InPlayMode()) {
		if (false) {
			PrintFormat("%1 run %2", "RefCom_TestBootstrapper", "RefCom_MapScanner");
			mapScanner = new RefCom_MapScanner(new RefCom_MapScannerEntitiesShippingService(500), 150);
					
			GetGame().GetCallqueue().CallLater(mapScanner.produce, 0, true);
			GetGame().GetCallqueue().CallLater(mapScanner.consume, 0, true);
		}
		
		if (GetGame().InPlayMode()) {
			PrintFormat("%1 run %2", "RefCom_TestBootstrapper", "RefCom_MapRendererController");
			mapRendererController = new RefCom_MapRendererController();
			
			GetGame().GetCallqueue().CallLater(mapRendererController.renderClusterList, 1000, true);
		}

	}
	
};