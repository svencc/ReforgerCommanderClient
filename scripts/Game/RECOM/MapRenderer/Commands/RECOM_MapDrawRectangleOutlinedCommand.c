class RECOM_MapDrawRectangleOutlinedCommand : RECOM_MapDrawCommandBase {

	vector start;
	vector end;
	int color;
	float outlineWidth;
	int outlineColor;
	
	override void drawTo(RECOM_MapModule mapModule) {
		mapModule.renderRectangleOutlined(start, end, color, outlineWidth, outlineColor);
	}
		
}