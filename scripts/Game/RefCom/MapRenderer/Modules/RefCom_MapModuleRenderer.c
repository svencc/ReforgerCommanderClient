[BaseContainerProps()]
class RefCom_MapModuleRenderer  : SCR_MapModuleBase {
	
	protected Widget layoutWidget;
	protected CanvasWidget canvas;
	protected ref array<ref CanvasWidgetCommand> renderCommands;
	protected ResourceName layout = "{5D8727C1F109D98D}UI/Layouts/Map/CanvasLayer.layout";
	
	void RefCom_MapModuleRenderer() {
		Print("I am being constructed!");
	}
	
	void ~RefCom_MapModuleRenderer()	{
		Print("I am being destroyed!");
	}
	
	override void Init() {
		renderCommands = new array<ref CanvasWidgetCommand>();
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
	
	void Render()	{		
		renderCommands.Clear();
		renderCircle("1000 0 1000", 50, ARGB(255, 255, 0, 0) );
		renderCircle("1100 0 1100", 100, ARGB(255, 0, 255, 0) );
		renderCircle("1200 0 1200", 75, ARGB(255, 0, 0, 255) );
		
		renderCircleOutlined("2000 0 2000", 400, ARGB(255, 0, 0, 255), ARGB(255, 0, 255, 0), 4);
		
		renderLine("800 0 800", "1500 0 1500", ARGB(255, 0, 0, 0), 2);
		renderLineOutlined("1200 0 800", "1900 0 1500", ARGB(255, 0, 255, 0), 10, ARGB(255, 0, 0, 0), 2);
		
		//renderRectangle("2000 0 1000", "3000 0 2000", ARGB(255, 0, 0, 255));
		renderRectangleOutlined("3150 0 1150", "3850 0 1850", ARGB(255, 0, 0, 255),  ARGB(255, 255, 0, 0), 2);
		
		//renderText("800 0 1000", "Das ist mein Text", ARGB(255, 0, 0, 0), 50);
	}
	
	override void Update(float timeSlice) {	
		if (renderCommands.Count() > 0) {						
			canvas.SetDrawCommands(renderCommands);			
		}
		Render()
	}
	
	array<vector> renderCircle(vector center, float radius, int color, int resolution = 36) {
		PolygonDrawCommand drawCommand = new PolygonDrawCommand();		
		drawCommand.m_iColor = color;
		drawCommand.m_Vertices = new array<float>;
		
		array<vector> points = new array<vector>;
		
		int mapPosX;
		int mapPosY;
		m_MapEntity.WorldToScreen(center[0], center[2], mapPosX, mapPosY, true);
		
		float scaledRadius = radius * m_MapEntity.GetCurrentZoom();
		for (int i = 0; i < resolution; i++) {
			float theta = i * (2 * Math.PI / resolution);
			float screenPointPosX = (int) (mapPosX + scaledRadius * Math.Cos(theta));
			float screenPointPosY = (int) (mapPosY + scaledRadius * Math.Sin(theta));
			vector point = {screenPointPosX, 0, screenPointPosY};
			points.Insert(point);
		}
		
		foreach (int currentIndex, vector currentPoint : points) {
			drawCommand.m_Vertices.Insert(currentPoint[0]);
			drawCommand.m_Vertices.Insert(currentPoint[2]);
		}
		renderCommands.Insert(drawCommand);
		
		return points;
	}	
	
	void renderCircleOutlined(vector center, float radius, int color, int outlineColor,  float outlineWidth, int resolution = 36) {
		array<vector> points = renderCircle(center, radius, color, resolution);
			
		vector firstPoint;
		vector lastPoint;
		foreach (int currentIndex, vector currentPoint : points) {
			if (!lastPoint) {
				firstPoint = currentPoint;
				lastPoint = currentPoint;
			} else {
				renderRawLine(lastPoint, currentPoint, outlineColor, outlineWidth);
				lastPoint = currentPoint;
			}
		}
		
		// close renderLine
		renderLine(firstPoint, lastPoint, outlineColor, outlineWidth);
	}	
	
	void renderLine(vector start, vector end, int color, float width) {
		renderLineOutlined(start, end, color, width, 0, 0.0);
	}
	void renderLineOutlined(vector start, vector end, int color, float width, int outlineColor,  float outlineWidth) {
		LineDrawCommand drawCommand = new LineDrawCommand();		
		drawCommand.m_iColor = color;
		drawCommand.m_fWidth = width;
		drawCommand.m_iOutlineColor = outlineColor;
		drawCommand.m_fOutlineWidth = outlineWidth;
		drawCommand.m_Vertices = new array<float>;
		
		int mapPosStartX;
		int mapPosStartY;
		m_MapEntity.WorldToScreen(start[0], start[2], mapPosStartX, mapPosStartY, true);
		
		int mapPosEndX;
		int mapPosEndY;
		m_MapEntity.WorldToScreen(end[0], end[2], mapPosEndX, mapPosEndY, true);

		drawCommand.m_Vertices.Insert(mapPosStartX);
		drawCommand.m_Vertices.Insert(mapPosStartY);
		drawCommand.m_Vertices.Insert(mapPosEndX);
		drawCommand.m_Vertices.Insert(mapPosEndY);

		renderCommands.Insert(drawCommand);
	}
	
	private void renderRawLine(vector start, vector end, int color, float width) {
		renderRawLineOutlined(start, end, color, width, 0, 0.0);
	}
	private void renderRawLineOutlined(vector start, vector end, int color, float width, int outlineColor,  float outlineWidth) {
		LineDrawCommand drawCommand = new LineDrawCommand();		
		drawCommand.m_iColor = color;
		drawCommand.m_fWidth = width;
		drawCommand.m_iOutlineColor = outlineColor;
		drawCommand.m_fOutlineWidth = outlineWidth;
		drawCommand.m_Vertices = new array<float>;
		
		drawCommand.m_Vertices.Insert(start[0]);
		drawCommand.m_Vertices.Insert(start[2]);
		drawCommand.m_Vertices.Insert(end[0]);
		drawCommand.m_Vertices.Insert(end[2]);

		renderCommands.Insert(drawCommand);
	}
	
	void renderRectangle(vector start, vector end, int color) {
		PolygonDrawCommand drawCommand = new PolygonDrawCommand();		
		drawCommand.m_iColor = color;
		drawCommand.m_Vertices = new array<float>;
		
		int mapPosStartCornerX;
		int mapPosStartCornerY;
		m_MapEntity.WorldToScreen(start[0], start[2], mapPosStartCornerX, mapPosStartCornerY, true);
		
		int mapPosEndCornerX;
		int mapPosEndCornerY;
		m_MapEntity.WorldToScreen(end[0], end[2], mapPosEndCornerX, mapPosEndCornerY, true);

		drawCommand.m_Vertices.Insert(mapPosStartCornerX);
		drawCommand.m_Vertices.Insert(mapPosStartCornerY);
		
		drawCommand.m_Vertices.Insert(mapPosEndCornerX);
		drawCommand.m_Vertices.Insert(mapPosStartCornerY);
		
		drawCommand.m_Vertices.Insert(mapPosEndCornerX);
		drawCommand.m_Vertices.Insert(mapPosEndCornerY);
		
		drawCommand.m_Vertices.Insert(mapPosStartCornerX);
		drawCommand.m_Vertices.Insert(mapPosEndCornerY);

		renderCommands.Insert(drawCommand);
	}
	void renderRectangleOutlined(vector start, vector end, int color, int outlineColor,  float outlineWidth) {
		renderRectangle(start, end, color);
		
		vector end1 = {end[0],0,start[2]};
		renderLine(start, end1, outlineColor, outlineWidth);
		
		vector start2 = end1;
		renderLine(start2, end, outlineColor, outlineWidth);
		
		vector end3 = {start[0],0,end[2]};
		renderLine(end, end3, outlineColor, outlineWidth);
		
		vector start4 = end3;
		renderLine(start4, start, outlineColor, outlineWidth);
	}

	/*
	// does not work now; maybe due to missing drawCommand.m_iFontPropertiesId.
	// spec for this is missing :-(
	void renderText(vector start, string text, int color, float size, float rotation = 0) {
		TextDrawCommand drawCommand = new TextDrawCommand();
		drawCommand.m_iColor = color;
		drawCommand.m_Position = start;
		drawCommand.m_sText = text;
		drawCommand.m_fSize = size;
		drawCommand.m_fRotation = rotation;
		
		renderCommands.Insert(drawCommand);
	}
	*/

};
