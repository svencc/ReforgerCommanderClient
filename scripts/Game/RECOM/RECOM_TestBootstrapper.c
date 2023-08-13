[EntityEditorProps(category: "RECOM", description: "RECOM")]
class RECOM_TestBootstrapperClass: SCR_BaseTriggerEntityClass {};

class RECOM_TestBootstrapper: SCR_BaseTriggerEntity {
	
	protected ref RECOM_MapScanner mapScanner;
	protected ref RECOM_MapRendererController mapRendererController;
	protected ref RECOM_Clock clock;
	protected ref RECOM_AuthenticationInjector authenticationInjector;

	void ~RECOM_TestBootstrapper() {
		GetGame().GetCallqueue().Clear();
		delete mapScanner;
		delete mapRendererController;
		delete clock;
	}
	
	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		
		if (GetGame().InPlayMode()) {
			clock = RECOM_Clock.getInstance();
			RECOM_AuthenticationInjector.getInstance().authenticate();
		}
		
		//if (GetGame().InPlayMode()) {
		if (false) {					
			mapScanner = new RECOM_MapScanner(new RECOM_MapScannerEntitiesShippingService(500), 150);
			GetGame().GetCallqueue().CallLater(mapScanner.produce, 0, true);
			GetGame().GetCallqueue().CallLater(mapScanner.consume, 0, true);
		}
		
		if (GetGame().InPlayMode()) {
		//if (false) {
			mapRendererController = new RECOM_MapRendererController();
			GetGame().GetCallqueue().CallLater(mapRendererController.renderClusterList, 1000, true);
		}
		
		
	}
	
};