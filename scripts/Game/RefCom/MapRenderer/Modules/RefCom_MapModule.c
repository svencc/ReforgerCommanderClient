[BaseContainerProps()]
class RefCom_MapModule  : SCR_MapModuleBase {
	
	protected Widget layoutWidget;
	protected CanvasWidget canvas;
	protected ref array<ref CanvasWidgetCommand> renderCommands;
	protected ResourceName layout = "{5D8727C1F109D98D}UI/Layouts/Map/CanvasLayer.layout";
	
	void RefCom_MapModule() {
	}
	
	void ~RefCom_MapModule()	{
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

		renderCircle("1000 0 1000", 50.0, ARGB(255, 255, 0, 0) );
		renderCircle("1100 0 1100", 100.0, ARGB(255, 0, 255, 0) );
		renderCircle("1200 0 1200", 75.0, ARGB(255, 0, 0, 255) );
		renderCircle("2000 0 2000", 400.0, ARGB(255, 0, 0, 255), 6);
		renderCircleOutlined("2000 0 3000", 400.0, ARGB(255, 0, 0, 255), 4.0, ARGB(255, 0, 255, 0));
		
		renderLineCircled("3000 0 3000", 400, ARGB(255, 0, 0, 255), 20, 16);
		renderLineCircledOutlined("4000 0 3000", 400.0, 20.0, ARGB(255, 0, 0, 255), 2.0, ARGB(255, 0, 255, 0), 8);
		
		renderLine("800 0 800", "1500 0 1500", 2.0, ARGB(255, 0, 0, 0));
		renderLineOutlined("1200 0 800", "1900 0 1500", 20.0, ARGB(255, 0, 0, 0), 2.0, ARGB(255, 0, 255, 0));
		
		renderRectangle("2000 0 1000", "3000 0 2000", ARGB(255, 0, 0, 255));
		renderRectangleOutlined("3150 0 1150", "3850 0 1850", ARGB(255, 0, 0, 255), 2.0, ARGB(255, 255, 0, 0));
		
		//renderLineRectangled("450 0 450", "650 0 650", 2.0, ARGB(255, 0, 0, 255));
		//renderLineRectangledOutlined("150 0 1150", "850 0 850", 10.0, ARGB(255, 0, 0, 255), 2.0, ARGB(255, 255, 0, 0));		
		

		//renderText("800 0 1000", "Das ist mein Text", ARGB(255, 0, 0, 0), 50);
	}
	
	override void Update(float timeSlice) {	
		Render();
		if (renderCommands.Count() > 0) {						
			canvas.SetDrawCommands(renderCommands);			
		}
	}
	
	

	// LINE
	void renderLine(vector start, vector end, float width, int color) {
		array<vector> points = new array<vector>;
		points.Insert(start);
		points.Insert(end);
		array<vector> translatedPoints = translatePoints(points);
		renderRawLine(translatedPoints[0], translatedPoints[1], width, color);
	}
	void renderLineOutlined(vector start, vector end, float width, int color, float outlineWidth, int outlineColor) {
		array<vector> points = new array<vector>;
		points.Insert(start);
		points.Insert(end);
		array<vector> translatedPoints = translatePoints(points);
		renderRawLineOutlined(translatedPoints[0], translatedPoints[1], width, color, outlineWidth, outlineColor);
	}
	
	
	
	// POLYGON
	void renderPolygon(array<vector> points, int color) {
		array<vector> translatedPoints = translatePoints(points);
		renderGenericPolygon(translatedPoints, color);
	}
	void renderPolygonOutlined(array<vector> points, int color, float outlineWidth, int outlineColor) {
		array<vector> translatedPoints = translatePoints(points);
		renderGenericPolygon(translatedPoints, color);
		renderGenericPolygonToLines(translatedPoints, outlineWidth, outlineColor);
	}
	
	
	
	// RECTANGLE
	void renderRectangle(vector start, vector end, int color) {
		array<vector> points = generateRectangularPolygon(start, end);
		array<vector> translatedPoints = translatePoints(points);
		renderGenericPolygon(translatedPoints, color);
	}
	void renderRectangleOutlined(vector start, vector end, int color, float outlineWidth, int outlineColor) {
		array<vector> points = generateRectangularPolygon(start, end);
		array<vector> translatedPoints = translatePoints(points);
		renderGenericPolygon(translatedPoints, color);
		renderGenericPolygonToLines(translatedPoints, outlineWidth, outlineColor);
	}
	array<vector> generateRectangularPolygon(vector start, vector end) {
		array<vector> rectangularPoints = new array<vector>;
		rectangularPoints.Insert(start);
		
		vector second = {end[0],0,start[2]};
		rectangularPoints.Insert(second);
		
		rectangularPoints.Insert(end);
		
		vector last = {start[0],0,end[2]};
		rectangularPoints.Insert(last);
		
		return rectangularPoints;
	}
	
	
	
	// CIRCLE
	void renderCircleOutlined(vector center, float radius, int color, float outlineWidth, int outlineColor, int resolution = 36) {
		array<vector> points = generateCircularPolygon(center, radius, resolution);
		array<vector> translatedPoints = translatePoints(points);
		renderGenericPolygon(translatedPoints, color);
		renderGenericPolygonToLines(translatedPoints, outlineWidth, outlineColor);
	}
	void renderCircle(vector center, float radius, int color, int resolution = 36) {
		array<vector> points = generateCircularPolygon(center, radius, resolution);
		array<vector> translatedPoints = translatePoints(points);
		renderGenericPolygon(translatedPoints, color);
	}
	array<vector> generateCircularPolygon(vector center, float radius, int resolution = 36) {
		array<vector> circularPolygon = new array<vector>;
		for (int i = 0; i < resolution; i++) {
			float theta = i * (2 * Math.PI / resolution);
			float pointPosX = (int) (center[0] + (radius * Math.Cos(theta)));
			float pointPosY = (int) (center[2] + (radius * Math.Sin(theta)));
			vector point = {pointPosX, 0, pointPosY};
			circularPolygon.Insert(point);
		}
		
		return circularPolygon;
	}
	
	

	// CIRCULAR LINE
	void renderLineCircled(vector center, float radius, float width, int color, int resolution = 36) {
		array<vector> points = generateCircularPolygon(center, radius, resolution);
		array<vector> translatedPoints = translatePoints(points);
		renderGenericPolygonToLines(translatedPoints, width, color);
	}
	void renderLineCircledOutlined(vector center, float radius, float width, int color, float outlineWidth, int outlineColor, int resolution = 36) {
		array<vector> points = generateCircularPolygon(center, radius, resolution);
		array<vector> translatedPoints = translatePoints(points);
		renderGenericPolygonToLinesOutlined(translatedPoints, width, color, outlineWidth, outlineColor);
	}
	
	
	

	// RECTANGULAR LINE 
	void renderLineRectangled(vector start, vector end, float width, int color) {
		array<vector> points = generateRectangularPolygon(start, end);
		array<vector> translatedPoints = translatePoints(points);
		renderGenericPolygonToLines(translatedPoints, width, color);
	}
	void renderLineRectangledOutlined(vector start, vector end, float width, int color, float outlineWidth, int outlineColor) {
		array<vector> points = generateRectangularPolygon(start, end);
		array<vector> translatedPoints = translatePoints(points);
		renderGenericPolygonToLinesOutlined(translatedPoints, width, color, outlineWidth, outlineColor);
	}

	

	
	// TRANSLATE MAP-COORDINATE TO TRANSLATED-SCREEN-COORDINATE
	array<vector> translatePoints(array<vector> points) {
		array<vector> translatedPoints = new array<vector>;

		foreach (int currentIndex, vector currentPoint : points) {
			int translatedPosX;
			int translatedPosY;
			m_MapEntity.WorldToScreen(currentPoint[0], currentPoint[2], translatedPosX, translatedPosY, true);
			vector translatedPoint = {translatedPosX, 0, translatedPosY};
			translatedPoints.Insert(translatedPoint);
		}
		
		return translatedPoints;
	}	
	
	
	
	// RENDER GENERIC POLYGON
	protected void renderGenericPolygon(array<vector> translatedPoints, int color) {
		PolygonDrawCommand drawCommand = new PolygonDrawCommand();		
		drawCommand.m_iColor = color;
		drawCommand.m_Vertices = new array<float>;
		
		foreach (int currentIndex, vector currentPoint : translatedPoints) {
			drawCommand.m_Vertices.Insert(currentPoint[0]);
			drawCommand.m_Vertices.Insert(currentPoint[2]);
		}
		renderCommands.Insert(drawCommand);
	}	

	
	
	// RENDER GENERIC POLYGON -> LINE
	protected void renderGenericPolygonToLines(array<vector> translatedPoints, float width, int color) {
		vector firstPoint;
		vector lastPoint;
		foreach (int currentIndex, vector currentPoint : translatedPoints) {
			if (!lastPoint) {
				firstPoint = currentPoint;
				lastPoint = currentPoint;
			} else {
				renderRawLine(lastPoint, currentPoint, width, color);
				lastPoint = currentPoint;
			}
		}
		
		// close line
		renderRawLine(firstPoint, lastPoint, width, color);
	}
	protected void renderGenericPolygonToLinesOutlined(array<vector> translatedPoints, float width, int color, float widthOutline, int colorOutline) {
		vector firstPoint;
		vector lastPoint;
		foreach (int currentIndex, vector currentPoint : translatedPoints) {
			if (!lastPoint) {
				firstPoint = currentPoint;
				lastPoint = currentPoint;
			} else {
				renderRawLineOutlined(lastPoint, currentPoint, width, color, widthOutline, colorOutline);
				lastPoint = currentPoint;
			}
		}
		
		// close line
		renderRawLineOutlined(firstPoint, lastPoint, width, color, widthOutline, colorOutline);
	}
	
	
	
	// RAW LINES WITH TRANSLATED COORDINATES
	protected void renderRawLine(vector start, vector end, float width, int color) {
		renderRawLineOutlined(start, end , width, color, 0, 0.0);
	}
	protected void renderRawLineOutlined(vector start, vector end, float width, int color, float outlineWidth, int outlineColor) {
		LineDrawCommand drawCommand = new LineDrawCommand();		
		drawCommand.m_fWidth = width;
		drawCommand.m_iColor = color;
		drawCommand.m_fOutlineWidth = outlineWidth;
		drawCommand.m_iOutlineColor = outlineColor;		
		drawCommand.m_Vertices = new array<float>;

		drawCommand.m_Vertices.Insert(start[0]);
		drawCommand.m_Vertices.Insert(start[2]);
		drawCommand.m_Vertices.Insert(end[0]);
		drawCommand.m_Vertices.Insert(end[2]);

		renderCommands.Insert(drawCommand);
	}

};
