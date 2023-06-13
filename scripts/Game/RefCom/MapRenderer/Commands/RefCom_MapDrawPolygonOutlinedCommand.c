class RefCom_MapDrawPolygonOutlinedCommand : RefCom_MapDrawCommandBase {
	
	ref array<vector> points;
	int color; 
	float outlineWidth; 
	int outlineColor;
	
	override void drawTo(RefCom_MapModule mapModule) {
		mapModule.renderPolygonOutlined(points, color, outlineWidth, outlineColor);
	}
		
}