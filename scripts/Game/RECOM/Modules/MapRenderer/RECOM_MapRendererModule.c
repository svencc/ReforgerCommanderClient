class RECOM_MapRendererModule {
	
	private static ref RECOM_MapRendererModule instance;
	
	protected ref RECOM_MapRendererRESTGateway rendererGateway
	protected ref RECOM_BaseBuffer<RECOM_MapRendererResponseDto> buffer;
	protected ref RECOM_MapModule mapModule;
	
	static RECOM_MapRendererModule getModule() {
        if (!RECOM_MapRendererModule.instance) {
            RECOM_MapRendererModule.instance = new RECOM_MapRendererModule();
        }
        return RECOM_MapRendererModule.instance;
    }
	
	
	void RECOM_MapRendererModule() {
		this.buffer = new RECOM_BaseBuffer<RECOM_MapRendererResponseDto>();
		this.rendererGateway = new RECOM_MapRendererRESTGateway(buffer);

		this.mapModule = RECOM_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RECOM_MapModule));
	}
	
	void ~RECOM_MapRendererModule()	{
		delete rendererGateway;
		delete buffer;
		delete mapModule;
	}
	
	void renderClusterList() {
		if (mapModule) {
			mapModule.clearDrawCommands();
			rendererGateway.provideRenderData(GetGame().GetWorldFile());

			if (buffer.hasData()) {
				RECOM_MapRendererResponseDto response = buffer.read();
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
