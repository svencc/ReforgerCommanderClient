class RECOM_MapDrawPolygonOutlinedCommand : RECOM_MapDrawCommandBase {
	
	ref array<vector> points;
	int color; 
	float outlineWidth; 
	int outlineColor;
	
	override void drawTo(RECOM_MapModule mapModule) {
		mapModule.renderPolygonOutlined(points, color, outlineWidth, outlineColor);
	}
		
}