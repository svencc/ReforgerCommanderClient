class RefCom_MapDrawCircleOutlinedCommand : RefCom_MapDrawCommandBase {

	vector center; 
	float radius;
	float width;
	int color;
	float outlineWidth;
	int outlineColor;
	int resolution;
	
	override void drawTo(RefCom_MapModule mapModule) {
		mapModule.renderLineCircledOutlined(center, radius, width, color, outlineWidth, outlineColor, resolution);
	}
	
}