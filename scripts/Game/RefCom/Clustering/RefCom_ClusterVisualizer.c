[BaseContainerProps()]
class RefCom_ClusterVisualizer : SCR_MapModuleBase {
	
	protected Widget widget;
	protected CanvasWidget canvas;
	protected ResourceName layout = "{5D68C6A8E8235705}UI/Layouts/Map/MapCanvasLayer.layout";
	
	void RefCom_ClusterVisualizer() {
	
	}
	
	void ~RefCom_ClusterVisualizer() {
	
	}
	
	override void OnMapOpen(MapConfiguration config) {
		super.OnMapOpen(config);
		widget = GetGame().GetWorkspace().CreateWidgets(layout);
		canvas = CanvasWidget.Cast(widget.FindAnyWidget("Canvas"));
	}
	
	override void OnMapClose(MapConfiguration config) {
		super.OnMapClose(config);
		widget.RemoveFromHierarchy();

	}
	
}