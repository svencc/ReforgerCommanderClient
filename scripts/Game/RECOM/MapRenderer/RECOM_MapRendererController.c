class RECOM_MapRendererController {
	
	protected ref RECOM_ClusteringRestAdapter restAdapter;
	protected ref RECOM_MapModule mapModule;
	protected ref RECOM_ClusterBuffer clusterBuffer
	
	void RECOM_MapRendererController() {
		mapModule = RECOM_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RECOM_MapModule));
		clusterBuffer = new RECOM_ClusterBuffer();
		restAdapter = new RECOM_ClusteringRestAdapter(clusterBuffer);
	}
	
	void ~RECOM_MapRendererController()	{
		delete restAdapter;
		delete mapModule;
		delete clusterBuffer;
	}
	
	void renderClusterList() {
		if(mapModule) {
			Print("renderClusterList to mapModule ...");
			mapModule.clearDrawCommands();
			
			restAdapter.provideClusterData(GetGame().GetWorldFile());
			
			
			if (clusterBuffer.hasData()) {
				RECOM_ClusterListDto listDto = clusterBuffer.read();
				foreach(RECOM_ClusterDto cluster : listDto.clusterList) {
					
					if (cluster.convexHull) {
						array<vector> polygon = {};
						foreach(RECOM_Point2DDto edge : cluster.convexHull.vertices) {
							vector point = {edge.x, 0, edge.y};
							polygon.Insert(point);
						}
						
						mapModule.addDrawCommand(
							RECOM_MapCommands.drawPolygon(polygon, ARGB(127, 255, 0 , 0) )
						);
					}
					
					if (cluster.concaveHull) {
						array<vector> polygon = {};
						foreach(RECOM_Point2DDto edge : cluster.concaveHull.vertices) {
							vector point = {edge.x, 0, edge.y};
							polygon.Insert(point);
						}
						
						mapModule.addDrawCommand(
							RECOM_MapCommands.drawPolygon(polygon, ARGB(127, 0, 255, 0) )
						);
					}
					
					/*
					if (cluster.points) {
						foreach( RECOM_Point2DDto point : cluster.points) {					
							vector center = {point.x, 0, point.y};
							mapModule.addDrawCommand(
								RECOM_MapCommands.drawCircle(center, 2.0, ARGB(255, 255, 0, 0), 3)
							);
						}
					}
					*/
					

				}					
			}
			

			/*
			auto c1 = RECOM_MapCommands.drawCircle("1000 0 1000", 50.0, ARGB(255, 255, 0, 0) );
			auto c2 = RECOM_MapCommands.drawCircle("1100 0 1100", 100.0, ARGB(255, 0, 255, 0) );
			auto c3 = RECOM_MapCommands.drawCircle("1200 0 1200", 75.0, ARGB(255, 0, 0, 255) );
			auto c4 = RECOM_MapCommands.drawCircle("2000 0 2000", 400.0, ARGB(255, 0, 0, 255), 6);
			
			auto c5 = RECOM_MapCommands.drawCircleOutlined("2000 0 3000", 400.0, ARGB(255, 0, 0, 255), 4.0, ARGB(255, 0, 255, 0));
			
			auto c6 = RECOM_MapCommands.drawLineCircled("3000 0 3000", 400, ARGB(255, 0, 0, 255), 20, 16);
			auto c7 = RECOM_MapCommands.drawLineCircledOutlined("4000 0 3000", 400.0, 20.0, ARGB(255, 0, 0, 255), 2.0, ARGB(255, 0, 255, 0), 8);
			
			
            //auto l1 = RECOM_MapCommands.drawLine("800 0 800", "1500 0 1500", 2.0, ARGB(255, 0, 0, 0));
            //auto l2 = RECOM_MapCommands.drawLineOutlined("1200 0 800", "1900 0 1500", 20.0, ARGB(255, 0, 0, 0), 2.0, ARGB(255, 0, 255, 0));

            auto r1 = RECOM_MapCommands.drawRectangle("2000 0 1000", "3000 0 2000", ARGB(255, 0, 0, 255));
            auto r2 = RECOM_MapCommands.drawRectangleOutlined("3150 0 1150", "3850 0 1850", ARGB(255, 0, 0, 255), 2.0, ARGB(255, 255, 0, 0));
			
			
			mapModule.addDrawCommand(c1);
			mapModule.addDrawCommand(c2);
			mapModule.addDrawCommand(c3);
			mapModule.addDrawCommand(c4);
			mapModule.addDrawCommand(c5);
			mapModule.addDrawCommand(c6);
			mapModule.addDrawCommand(c7);
			mapModule.addDrawCommand(r1);
			mapModule.addDrawCommand(r2);
			*/

		} else {
			// Establish controller connection to mapModule as soon it is available!
			mapModule = RECOM_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RECOM_MapModule));
		}

	}
	
	
}
