class RECOM_MapDrawRectangleCommand : RECOM_MapDrawCommandBase {
	
	vector start;
	vector end;
	int color;
	
	override void drawTo(RECOM_MapModule mapModule) {
		mapModule.renderRectangle(start, end, color);
	}
		
}