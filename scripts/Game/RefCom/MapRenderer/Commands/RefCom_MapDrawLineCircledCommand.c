class RefCom_MapDrawLineCircledCommand : RefCom_MapDrawCommandBase {

	vector center; 
	float radius;
	int color;
	float width;
	int resolution;
	
	override void drawTo(RefCom_MapModule mapModule) {
		mapModule.renderLineCircled(center, radius, width, color, resolution);
	}
		
}