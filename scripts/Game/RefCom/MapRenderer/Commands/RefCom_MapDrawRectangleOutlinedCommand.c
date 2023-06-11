class RefCom_MapDrawRectangleOutlinedCommand : RefCom_MapDrawCommandBase {

	vector start;
	vector end;
	int color;
	float outlineWidth;
	int outlineColor;
	
	override void drawTo(RefCom_MapModule mapModule) {
		mapModule.renderRectangleOutlined(start, end, color, outlineWidth, outlineColor);
	}
		
}