class RECOM_MapDrawCircleCommand : RECOM_MapDrawCommandBase {

	vector center; 
	float radius;
	int color;
	int resolution;
	
	override void drawTo(notnull RECOM_MapModule mapModule) {
		mapModule.renderCircle(center, radius, color, resolution);
	}
	
}