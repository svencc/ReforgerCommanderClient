[BaseContainerProps()]
class RefCom_CanvasLayer  : SCR_MapModuleBase {
	
	protected Widget layoutWidget;
	protected CanvasWidget canvas;
	protected ref array<ref CanvasWidgetCommand> drawCommands;
	protected ResourceName layout = "{5D8727C1F109D98D}UI/Layouts/Map/CanvasLayer.layout";
	
	void RefCom_CanvasLayer() {
		Print("I am being constructed!");
	}
	
	void ~RefCom_CanvasLayer()	{
		Print("I am being destroyed!");
	}
	
	override void Init() {
		drawCommands = new array<ref CanvasWidgetCommand>();
	}
	
	void Draw()	{		
		drawCommands.Clear();
		DrawCircle("1000 0 1000", 50, ARGB(75, 255, 0, 0) );
		DrawCircle("1100 0 1100", 100, ARGB(75, 0, 255, 0) );
		DrawCircle("1200 0 1200", 75, ARGB(75, 0, 0, 255) );
	}
	
	override void Update(float timeSlice) {	
		if (drawCommands.Count() > 0) {						
			canvas.SetDrawCommands(drawCommands);			
		}
		Draw()
	}
	
	void DrawCircle(vector center, float radius, int color, int resolution = 36) {
		PolygonDrawCommand drawCommand = new PolygonDrawCommand();		
		drawCommand.m_iColor = color;
		drawCommand.m_Vertices = new array<float>;
		
		int mapPosX;
		int mapPosY;
		m_MapEntity.WorldToScreen(center[0], center[2], mapPosX, mapPosY, true);
		
		float scaledRadius = radius * m_MapEntity.GetCurrentZoom();
		
		for (int i = 0; i < resolution; i++) {
			float theta = i * (2 * Math.PI / resolution);
			float screenPosX = (int) (mapPosX + scaledRadius * Math.Cos(theta));
			float screenPosY = (int) (mapPosY + scaledRadius * Math.Sin(theta));
			drawCommand.m_Vertices.Insert(screenPosX);
			drawCommand.m_Vertices.Insert(screenPosY);
		}
		
		drawCommands.Insert(drawCommand);
	}
	
	override void OnMapOpen(MapConfiguration config) {
		super.OnMapOpen(config);
		layoutWidget = GetGame().GetWorkspace().CreateWidgets(layout);
		canvas = CanvasWidget.Cast(layoutWidget.FindAnyWidget("Canvas"));
	}
	
	override void OnMapClose(MapConfiguration config) {
		super.OnMapClose(config);
		layoutWidget.RemoveFromHierarchy();
	}

};
