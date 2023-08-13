[EntityEditorProps(category: "RECOM", description: "RECOM")]
class RECOM_TestBootstrapperClass: SCR_BaseTriggerEntityClass {};

class RECOM_TestBootstrapper: SCR_BaseTriggerEntity {
	
	protected ref RECOM_AuthenticationController authenticationController;
	protected ref RECOM_MapScanner mapScanner;
	protected ref RECOM_MapRendererController mapRendererController;

	void ~RECOM_TestBootstrapper() {
		GetGame().GetCallqueue().Clear();
		delete authenticationController;
		delete mapScanner;
		delete mapRendererController;
	}
	
	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		
		if (GetGame().InPlayMode()) {
			authenticationController = new RECOM_AuthenticationController();
			authenticationController.authenticate();
		}
		
		//if (GetGame().InPlayMode()) {
		if (false) {					
			mapScanner = new RECOM_MapScanner(new RECOM_MapScannerEntitiesShippingService(500), 150); //RECOM_MapScannerEntitiesShippingService da muss der authenticationBuffer rein!
			GetGame().GetCallqueue().CallLater(mapScanner.produce, 0, true);
			GetGame().GetCallqueue().CallLater(mapScanner.consume, 0, true);
		}
		
		if (GetGame().InPlayMode()) {
		//if (false) {
			mapRendererController = new RECOM_MapRendererController(authenticationController.getAuthenticationBuffer());
			GetGame().GetCallqueue().CallLater(mapRendererController.renderClusterList, 1000, true);
		}
	}
	
};