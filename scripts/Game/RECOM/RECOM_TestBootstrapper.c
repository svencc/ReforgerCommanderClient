[EntityEditorProps(category: "RECOM", description: "RECOM")]
class RECOM_TestBootstrapperClass: SCR_BaseTriggerEntityClass
{
};

class RECOM_TestBootstrapper: SCR_BaseTriggerEntity
{
	protected ref RECOM_MapScanner mapScanner;
	protected ref RECOM_MapRendererController mapRendererController;

	void ~RECOM_TestBootstrapper() {
		GetGame().GetCallqueue().Clear();
		delete mapScanner;
		delete mapRendererController;
	}
	
	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		PrintFormat("%1 initialized", "RECOM_TestBootstrapper");
		
		//if (GetGame().InPlayMode()) {
		if (false) {
			PrintFormat("%1 run %2", "RECOM_TestBootstrapper", "RECOM_MapScanner");
			mapScanner = new RECOM_MapScanner(new RECOM_MapScannerEntitiesShippingService(500), 150);
					
			GetGame().GetCallqueue().CallLater(mapScanner.produce, 0, true);
			GetGame().GetCallqueue().CallLater(mapScanner.consume, 0, true);
		}
		
		//if (false) {
		if (GetGame().InPlayMode()) {
			PrintFormat("%1 run %2", "RECOM_TestBootstrapper", "RECOM_MapRendererController");
			mapRendererController = new RECOM_MapRendererController();
			
			GetGame().GetCallqueue().CallLater(mapRendererController.renderClusterList, 1000, true);
		}

	}
	
};