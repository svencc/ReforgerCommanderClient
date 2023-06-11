class RefCom_MapDrawPolygonCommand : RefCom_MapDrawCommandBase {
	
	array<vector> points; 
	int color;
	
	override void drawTo(RefCom_MapModule mapModule) {
		mapModule.renderPolygon(points, color);
	}
		
}