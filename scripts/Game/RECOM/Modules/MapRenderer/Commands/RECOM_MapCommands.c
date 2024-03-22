class RECOM_MapCommands {

	
	
	
	
	// POLYGON
	static RECOM_MapDrawPolygonCommand drawPolygon(
		array<vector> points, 
		int color
	) {
		RECOM_MapDrawPolygonCommand rectangleCommand = new RECOM_MapDrawPolygonCommand();
		rectangleCommand.points = points;
		rectangleCommand.color = color;
		
		return rectangleCommand;

	}
	static RECOM_MapDrawPolygonOutlinedCommand drawPolygonOutlined(
		array<vector> points, 
		int color, 
		float outlineWidth, 
		int outlineColor
	) {
		RECOM_MapDrawPolygonOutlinedCommand rectangleCommand = new RECOM_MapDrawPolygonOutlinedCommand();
		rectangleCommand.points = points;
		rectangleCommand.color = color;
		rectangleCommand.outlineWidth = outlineWidth;
		rectangleCommand.outlineColor = outlineColor;
		
		return rectangleCommand;

	}

	
	

	
	// RECTANGLE
	static RECOM_MapDrawRectangleCommand drawRectangle(
		vector start, 
		vector end, 
		int color
	) {
		RECOM_MapDrawRectangleCommand rectangleCommand = new RECOM_MapDrawRectangleCommand();
		rectangleCommand.start = start;
		rectangleCommand.end = end;
		rectangleCommand.color = color;
		
		return rectangleCommand;

	}
	static RECOM_MapDrawRectangleOutlinedCommand drawRectangleOutlined(
		vector start, 
		vector end, 
		int color, 
		float outlineWidth, 
		int outlineColor
	) {
		RECOM_MapDrawRectangleOutlinedCommand rectangleCommand = new RECOM_MapDrawRectangleOutlinedCommand();
		rectangleCommand.start = start;
		rectangleCommand.end = end;
		rectangleCommand.color = color;
		rectangleCommand.outlineWidth = outlineWidth;
		rectangleCommand.outlineColor = outlineColor;
		
		return rectangleCommand;
	}
	

	
	
	
	// CIRCLE
	static RECOM_MapDrawCircleCommand drawCircle(
		vector center, 
		float radius, 
		int color, 
		int resolution = 36
	) {
		RECOM_MapDrawCircleCommand circleCommand = new RECOM_MapDrawCircleCommand();
		circleCommand.center = center;
		circleCommand.radius = radius;
		circleCommand.color = color;
		circleCommand.resolution = resolution;
		
		return circleCommand;
	}
	static RECOM_MapDrawCircleOutlinedCommand drawCircleOutlined(
		vector center, 
		float radius, 
		int color, 
		float outlineWidth, 
		int outlineColor, 
		int resolution = 36
	) {
		RECOM_MapDrawCircleOutlinedCommand circleCommand = new RECOM_MapDrawCircleOutlinedCommand();
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
	//  LINE
    //...
    //...
    //...
	//  RECTANGULAR LINE
    //...
    //...
    //...
	// CIRCULAR LINE
	static RECOM_MapDrawLineCircledCommand drawLineCircled(
		vector center, 
		float radius, 
		float width, 
		int color,  
		int resolution = 36
	) {
		RECOM_MapDrawLineCircledCommand lineCommand = new RECOM_MapDrawLineCircledCommand();
		lineCommand.center = center;
		lineCommand.radius = radius;
		lineCommand.width = width;
		lineCommand.color = color;
		lineCommand.resolution = resolution;
		
		return lineCommand;
	}
	static RECOM_MapDrawCircleOutlinedCommand drawLineCircledOutlined(
		vector center, 
		float radius, 
		float width, 
		int color, 
		float outlineWidth, 
		int outlineColor, 
		int resolution = 36
	) {
		RECOM_MapDrawCircleOutlinedCommand lineCommand = new RECOM_MapDrawCircleOutlinedCommand();
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