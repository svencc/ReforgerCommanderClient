class RECOM_MapDrawCircleOutlinedCommand : RECOM_MapDrawCommandBase {

	vector center; 
	float radius;
	float width;
	int color;
	float outlineWidth;
	int outlineColor;
	int resolution;
	
	override void drawTo(notnull RECOM_MapModule mapModule) {
		mapModule.renderLineCircledOutlined(center, radius, width, color, outlineWidth, outlineColor, resolution);
	}
	
}