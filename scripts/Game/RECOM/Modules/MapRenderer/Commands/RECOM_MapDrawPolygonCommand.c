class RECOM_MapDrawPolygonCommand : RECOM_MapDrawCommandBase {
	
	ref array<vector> points; 
	int color;
	
	override void drawTo(notnull RECOM_MapModule mapModule) {
		mapModule.renderPolygon(points, color);
	}
		
}