[BaseContainerProps()]
class CanvasLayer  : SCR_MapModuleBase {
	
	protected Widget m_wTaskListFrame;
	const string TASK_LIST_FRAME = "MapTaskList";
	
	protected Widget widget;
	protected CanvasWidget canvas;
	protected ref array<ref CanvasWidgetCommand> drawCommands;
	protected ResourceName layout = "{5D8727C1F109D98D}UI/Layouts/Map/CanvasLayer.layout";
	
	void CanvasLayer() {
		Print("I am being constructed!");
	}
	
	void ~CanvasLayer()	{
		Print("I am being destroyed!");
	}
	
	override void Init() {
		drawCommands = new array<ref CanvasWidgetCommand>();

	}
	
	void Draw()	{		
		Print("draw .....");
		drawCommands.Clear();
		DrawCircle("1000 0 1000", 50, ARGB(75, 255, 0, 0) );
		DrawCircle("1100 0 1100", 100, ARGB(75, 0, 255, 0) );
		DrawCircle("1200 0 1200", 75, ARGB(75, 0, 0, 255) );
	}
	
	override void Update(float timeSlice) {	
		Draw();
		if (drawCommands.Count() > 0) {						
			canvas.SetDrawCommands(drawCommands);			
		}
	}
	
	void DrawCircle(vector center, float range, int color, int n = 36) {
		PolygonDrawCommand cmd = new PolygonDrawCommand();		
		cmd.m_iColor = color;
		cmd.m_Vertices = new array<float>;
		
		int xcp, ycp;
		
		m_MapEntity.WorldToScreen(center[0], center[2], xcp, ycp, true);
		float r = range * m_MapEntity.GetCurrentZoom();
		
		for(int i = 0; i < n; i++) {
			float theta = i*(2*Math.PI/n);
			float x = (int)(xcp + r*Math.Cos(theta));
			float y = (int)(ycp + r*Math.Sin(theta));
			cmd.m_Vertices.Insert(x);
			cmd.m_Vertices.Insert(y);
		}
		
		drawCommands.Insert(cmd);
	}
	
	override void OnMapOpen(MapConfiguration config) {
		super.OnMapOpen(config);
		
		//drawCommands = new array<ref CanvasWidgetCommand>();
		widget = GetGame().GetWorkspace().CreateWidgets(layout);
		canvas = CanvasWidget.Cast(widget.FindAnyWidget("Canvas"));
	}
	
	override void OnMapClose(MapConfiguration config) {
		super.OnMapClose(config);
		widget.RemoveFromHierarchy();
	}

};
