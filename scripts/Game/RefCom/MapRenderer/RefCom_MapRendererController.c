class RefCom_MapRendererController {
	
	protected ref RefCom_ClusteringRestAdapter restAdapter;
	protected ref RefCom_MapModule mapModule;
	protected ref RefCom_ClusterListDto clusterList
	
	void RefCom_MapRendererController() {
		mapModule = RefCom_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RefCom_MapModule));
		restAdapter = new RefCom_ClusteringRestAdapter();
		clusterList = restAdapter.provideClusterData(GetGame().GetWorldFile());
	}
	
	void ~RefCom_MapRendererController()	{
		delete restAdapter;
		delete mapModule;
		delete clusterList;
	}
	
	void renderClusterList() {
		if(mapModule) {
			Print("renderClusterList to mapModule ...");
		} else {
			// Establish controller connection to mapModule as soon it is available!
			mapModule = RefCom_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RefCom_MapModule));
		}

	}
	
	
}
