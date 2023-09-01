class RECOM_MapRendererController {
	
	protected ref RECOM_MapRendererRESTGateway rendererGateway
	protected ref RECOM_MapRendererResponseBuffer rendererBuffer;
	
	protected ref RECOM_MapModule mapModule;
	
	void RECOM_MapRendererController() {
		this.rendererBuffer = new RECOM_MapRendererResponseBuffer();
		this.rendererGateway = new RECOM_MapRendererRESTGateway(rendererBuffer);

		this.mapModule = RECOM_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RECOM_MapModule));
	}
	
	void ~RECOM_MapRendererController()	{
		delete rendererGateway;
		delete rendererBuffer;
		delete mapModule;
	}
	
	void renderClusterList() {
		if (mapModule) {
			mapModule.clearDrawCommands();
			rendererGateway.provideRenderData(GetGame().GetWorldFile());

			if (rendererBuffer.hasData()) {
				RECOM_MapRendererResponseDto response = rendererBuffer.read();
				foreach(RECOM_MapRenderCommandDto command : response.renderCommands) {
					switch(command.mapRenderCommandType) {
						case RECOM_Enum_MapRenderCommandType.POLYGON: { 						
							array<vector> polygon = {};
							foreach(RECOM_Point2DDto edge : command.geometryVertices) {
								vector point = {edge.x, 0, edge.y};
								polygon.Insert(point);
							}							
							mapModule.addDrawCommand(RECOM_MapCommands.drawPolygon(polygon, command.color ));
							break; 
						}
						default: {}
					}
				}
			}
		} else {
			// Establish controller connection to mapModule as soon it is available!
			mapModule = RECOM_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RECOM_MapModule));
		}

	}
	
	
}
