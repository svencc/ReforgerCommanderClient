class RECOM_MapDrawLineCircledCommand : RECOM_MapDrawCommandBase {

	vector center; 
	float radius;
	int color;
	float width;
	int resolution;
	
	override void drawTo(RECOM_MapModule mapModule) {
		mapModule.renderLineCircled(center, radius, width, color, resolution);
	}
		
}