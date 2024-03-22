class RECOM_MapDrawLineCircledCommand : RECOM_MapDrawCommandBase {

	vector center; 
	float radius;
	int color;
	float width;
	int resolution;
	
	override void drawTo(notnull RECOM_MapModule mapModule) {
		mapModule.renderLineCircled(center, radius, width, color, resolution);
	}
		
}