class RefCom_MapDrawPolygonOutlinedCommand : RefCom_MapDrawCommandBase {
	
	array<vector> points;
	int color; 
	float outlineWidth; 
	int outlineColor;
	
	override void drawTo(RefCom_MapModule mapModule) {
		mapModule.renderPolygonOutlined(points, color, outlineWidth, outlineColor);
	}
		
}