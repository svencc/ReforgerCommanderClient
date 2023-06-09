class RefCom_MapRendererController {
	
	protected RefCom_MapModule mapModule;
	protected SCR_MapEntity mapEntity;
	
	void RefCom_MapRendererController() {
		init();
	}
	
	void ~RefCom_MapRendererController()	{
	}
	
	private void init() {
		mapEntity = SCR_MapEntity.GetMapInstance();
		mapModule = RefCom_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RefCom_MapModule));
	}
	
	void render() {
		Print("render");
	}
	
	
}
