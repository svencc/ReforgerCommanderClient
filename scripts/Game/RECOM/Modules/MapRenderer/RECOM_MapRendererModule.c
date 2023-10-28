class RECOM_MapRendererModule : RECOM_BaseModule {
	
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
	
	
	private void RECOM_MapRendererModule() {
		buffer = new RECOM_BaseBuffer<RECOM_MapRendererResponseDto>();
		rendererGateway = new RECOM_MapRendererRESTGateway(buffer);
		mapModule = RECOM_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RECOM_MapModule));
	}
	
	void ~RECOM_MapRendererModule()	{
		rendererGateway = null;
		buffer = null;
		mapModule = null;
	}
	
	protected void renderClusterList() {
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
	
	override void start() {
		super.start();
		GetGame().GetCallqueue().CallLater(renderClusterList, 1000, true);
	}
	
	override void dispose() {
		super.dispose();
		RECOM_MapRendererModule.instance = null;
	}
	
}
