class RECOM_MapDrawPolygonCommand : RECOM_MapDrawCommandBase {
	
	ref array<vector> points; 
	int color;
	
	override void drawTo(RECOM_MapModule mapModule) {
		mapModule.renderPolygon(points, color);
	}
		
}