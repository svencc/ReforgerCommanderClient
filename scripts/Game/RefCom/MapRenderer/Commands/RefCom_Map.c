class RefCom_Map {

	
	
	
	
	// POLYGON
	static RefCom_MapDrawPolygonCommand drawPolygon(array<vector> points, int color) {
		RefCom_MapDrawPolygonCommand rectangleCommand = new RefCom_MapDrawPolygonCommand();
		rectangleCommand.points = points;
		rectangleCommand.color = color;
		
		return rectangleCommand;

	}
	static RefCom_MapDrawPolygonOutlinedCommand drawPolygonOutlined(array<vector> points, int color, float outlineWidth, int outlineColor) {
		RefCom_MapDrawPolygonOutlinedCommand rectangleCommand = new RefCom_MapDrawPolygonOutlinedCommand();
		rectangleCommand.points = points;
		rectangleCommand.color = color;
		rectangleCommand.outlineWidth = outlineWidth;
		rectangleCommand.outlineColor = outlineColor;
		
		return rectangleCommand;

	}

	
	

	
	// RECTANGLE
	static RefCom_MapDrawRectangleCommand drawRectangle(vector start, vector end, int color) {
		RefCom_MapDrawRectangleCommand rectangleCommand = new RefCom_MapDrawRectangleCommand();
		rectangleCommand.start = start;
		rectangleCommand.end = end;
		rectangleCommand.color = color;
		
		return rectangleCommand;

	}
	static RefCom_MapDrawRectangleOutlinedCommand drawRectangleOutlined(vector start, vector end, int color, float outlineWidth, int outlineColor) {
		RefCom_MapDrawRectangleOutlinedCommand rectangleCommand = new RefCom_MapDrawRectangleOutlinedCommand();
		rectangleCommand.start = start;
		rectangleCommand.end = end;
		rectangleCommand.color = color;
		rectangleCommand.outlineWidth = outlineWidth;
		rectangleCommand.outlineColor = outlineColor;
		
		return rectangleCommand;
	}
	

	
	
	
	// CIRCLE
	static RefCom_MapDrawCircleCommand drawCircle(vector center, float radius, int color, int resolution = 36) {
		RefCom_MapDrawCircleCommand circleCommand = new RefCom_MapDrawCircleCommand();
		circleCommand.center = center;
		circleCommand.radius = radius;
		circleCommand.color = color;
		circleCommand.resolution = resolution;
		
		return circleCommand;
	}
	static RefCom_MapDrawCircleOutlinedCommand drawCircleOutlined(vector center, float radius, int color, float outlineWidth, int outlineColor, int resolution = 36) {
		RefCom_MapDrawCircleOutlinedCommand circleCommand = new RefCom_MapDrawCircleOutlinedCommand();
		circleCommand.center = center;
		circleCommand.radius = radius;
		circleCommand.color = color;
		circleCommand.outlineWidth = outlineWidth;
		circleCommand.outlineColor = outlineColor;
		circleCommand.resolution = resolution;
		
		return circleCommand;
	}
	
	
	
	// LINE
	//...
	//...
	//...
	// CIRCULAR LINE
	static RefCom_MapDrawLineCircledCommand drawLineCircled(vector center, float radius, float width, int color,  int resolution = 36) {
		RefCom_MapDrawLineCircledCommand lineCommand = new RefCom_MapDrawLineCircledCommand();
		lineCommand.center = center;
		lineCommand.radius = radius;
		lineCommand.width = width;
		lineCommand.color = color;
		lineCommand.resolution = resolution;
		
		return lineCommand;
	}
	static RefCom_MapDrawCircleOutlinedCommand drawLineCircledOutlined(vector center, float radius, float width, int color, float outlineWidth, int outlineColor, int resolution = 36) {
		RefCom_MapDrawCircleOutlinedCommand lineCommand = new RefCom_MapDrawCircleOutlinedCommand();
		lineCommand.center = center;
		lineCommand.radius = radius;
		lineCommand.width = width;
		lineCommand.color = color;
		lineCommand.outlineWidth = outlineWidth;
		lineCommand.outlineColor = outlineColor;
		lineCommand.resolution = resolution;
		
		return lineCommand;
	}
		

	
	
	
	

	

}