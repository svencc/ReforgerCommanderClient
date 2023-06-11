class RefCom_MapDrawRectangleCommand : RefCom_MapDrawCommandBase {
	
	vector start;
	vector end;
	int color;
	
	override void drawTo(RefCom_MapModule mapModule) {
		mapModule.renderRectangle(start, end, color);
	}
		
}