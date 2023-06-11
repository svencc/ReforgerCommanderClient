class RefCom_MapRendererController {
	
	protected ref RefCom_ClusteringRestAdapter restAdapter;
	protected ref RefCom_MapModule mapModule;
	protected ref RefCom_ClusterListDto clusterList
	
	void RefCom_MapRendererController() {
		init();
	}
	
	void ~RefCom_MapRendererController()	{
		delete restAdapter;
		delete mapModule;
		delete clusterList;
	}
	
	private void init() {
		Print("init");
		mapModule = RefCom_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RefCom_MapModule));
		restAdapter = new RefCom_ClusteringRestAdapter();
		clusterList = restAdapter.provideClusterData(GetGame().GetWorldFile());
	}
	
	void renderClusterList() {
		Print("render");
	}
	
	
}
