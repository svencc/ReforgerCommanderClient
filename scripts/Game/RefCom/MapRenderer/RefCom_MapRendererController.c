class RefCom_MapRendererController {
	
	protected ref RefCom_ClusteringRestAdapter restAdapter;
	protected ref RefCom_MapModule mapModule;
	protected ref RefCom_ClusterBuffer clusterBuffer
	
	void RefCom_MapRendererController() {
		mapModule = RefCom_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RefCom_MapModule));
		clusterBuffer = new RefCom_ClusterBuffer();
		restAdapter = new RefCom_ClusteringRestAdapter(clusterBuffer);
	}
	
	void ~RefCom_MapRendererController()	{
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
				RefCom_ClusterListDto listDto = clusterBuffer.read();
				foreach(RefCom_ClusterDto cluster : listDto.clusterList) {
					
					if (cluster.convexHull) {
						array<vector> polygon = {};
						foreach(RefCom_Point2DDto edge : cluster.convexHull.vertices) {
							vector point = {edge.x, 0, edge.y};
							polygon.Insert(point);
						}
						
						mapModule.addDrawCommand(
							RefCom_Map.drawPolygon(polygon, ARGB(127, 255, 0 , 0) )
						);
					}
					
					if (cluster.concaveHull) {
						array<vector> polygon = {};
						foreach(RefCom_Point2DDto edge : cluster.concaveHull.vertices) {
							vector point = {edge.x, 0, edge.y};
							polygon.Insert(point);
						}
						
						mapModule.addDrawCommand(
							RefCom_Map.drawPolygon(polygon, ARGB(127, 0, 255, 0) )
						);
					}
					
					/*
					if (cluster.points) {
						foreach( RefCom_Point2DDto point : cluster.points) {					
							vector center = {point.x, 0, point.y};
							mapModule.addDrawCommand(
								RefCom_Map.drawCircle(center, 2.0, ARGB(255, 255, 0, 0), 3)
							);
						}
					}
					*/
					

				}					
			}
			

			/*
			auto c1 = RefCom_Map.drawCircle("1000 0 1000", 50.0, ARGB(255, 255, 0, 0) );
			auto c2 = RefCom_Map.drawCircle("1100 0 1100", 100.0, ARGB(255, 0, 255, 0) );
			auto c3 = RefCom_Map.drawCircle("1200 0 1200", 75.0, ARGB(255, 0, 0, 255) );
			auto c4 = RefCom_Map.drawCircle("2000 0 2000", 400.0, ARGB(255, 0, 0, 255), 6);
			
			auto c5 = RefCom_Map.drawCircleOutlined("2000 0 3000", 400.0, ARGB(255, 0, 0, 255), 4.0, ARGB(255, 0, 255, 0));
			
			auto c6 = RefCom_Map.drawLineCircled("3000 0 3000", 400, ARGB(255, 0, 0, 255), 20, 16);
			auto c7 = RefCom_Map.drawLineCircledOutlined("4000 0 3000", 400.0, 20.0, ARGB(255, 0, 0, 255), 2.0, ARGB(255, 0, 255, 0), 8);
			
			
            //auto l1 = RefCom_Map.drawLine("800 0 800", "1500 0 1500", 2.0, ARGB(255, 0, 0, 0));
            //auto l2 = RefCom_Map.drawLineOutlined("1200 0 800", "1900 0 1500", 20.0, ARGB(255, 0, 0, 0), 2.0, ARGB(255, 0, 255, 0));

            auto r1 = RefCom_Map.drawRectangle("2000 0 1000", "3000 0 2000", ARGB(255, 0, 0, 255));
            auto r2 = RefCom_Map.drawRectangleOutlined("3150 0 1150", "3850 0 1850", ARGB(255, 0, 0, 255), 2.0, ARGB(255, 255, 0, 0));
			
			
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
			mapModule = RefCom_MapModule.Cast(SCR_MapEntity.GetMapInstance().GetMapModule(RefCom_MapModule));
		}

	}
	
	
}
