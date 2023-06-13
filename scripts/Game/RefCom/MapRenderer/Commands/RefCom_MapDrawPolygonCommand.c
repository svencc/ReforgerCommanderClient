class RefCom_MapDrawPolygonCommand : RefCom_MapDrawCommandBase {
	
	ref array<vector> points; 
	int color;
	
	override void drawTo(RefCom_MapModule mapModule) {
		mapModule.renderPolygon(points, color);
	}
		
}