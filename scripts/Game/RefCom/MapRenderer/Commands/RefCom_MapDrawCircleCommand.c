class RefCom_MapDrawCircleCommand : RefCom_MapDrawCommandBase {

	vector center; 
	float radius;
	int color;
	int resolution;
	
	override void drawTo(RefCom_MapModule mapModule) {
		mapModule.renderCircle(center, radius, color, resolution);
	}
	
}