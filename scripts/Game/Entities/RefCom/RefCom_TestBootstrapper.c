[EntityEditorProps(category: "ReforgerCommander", description: "Reforger Commander")]
class RefCom_TestBootstrapperClass: SCR_BaseTriggerEntityClass
{
};

class RefCom_TestBootstrapper: SCR_BaseTriggerEntity
{
	private ref MapScannerProducerConsumer mapScannerProducerConsumer;
	
	void ~RefCom_TestBootstrapper() {
		GetGame().GetCallqueue().Clear();
	}
	
	override void EOnInit(IEntity owner) {
		super.EOnInit(owner);
		PrintFormat("%1 initialized", "RefCom_TestBootstrapper");
		if (GetGame().InPlayMode()) {
			mapScannerProducerConsumer = new MapScannerProducerConsumer(new MapScannerEntitiesShippingServiceProvider(1000), 150);		

			GetGame().GetCallqueue().CallLater(mapScannerProducerConsumer.produce, 0, true);
			GetGame().GetCallqueue().CallLater(mapScannerProducerConsumer.consume, 0, true);
		}
	}
	
};