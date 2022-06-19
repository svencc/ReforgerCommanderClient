class MapScanner {
		
	private int worldSize;
	private ref MapScannerEntityRestAdapter adapter;
	
	void MapScanner() {
		PrintFormat("%1 Constructor called", "MapScanner");
		init();
		
	}
	
	void ~MapScanner() {
		PrintFormat("%1 Destructor called", "MapScanner");
	}
	
	private void init() {
		determineMapSize();
		adapter = new MapScannerEntityRestAdapter;
	}
	
	int GetWorldSize() {
		return worldSize;
	}
	
	void scanMap() {
		Print("scanMap");
		g_Game.GetWorld().QueryEntitiesBySphere(
			mapCentre(),
			//worldSize,
			150,
			null, // hit-callback
			filterEntity, // filter callback
			EQueryEntitiesFlags.STATIC
		);
	}

	private void determineMapSize() {
		vector min, max;
		g_Game.GetWorldEntity().GetWorldBounds(min, max);
		worldSize = Math.Max(max[0] - min[0], max[2] - min[2]);
	}
	
	private vector mapCentre() {
		return {worldSize/2, 0, worldSize/2};
	}

	/*! 
		loops for every found entity
	*/
	/*
	private bool queryHit(IEntity ent) {
		if (ent != null) {
			Print("ENT NAME " + ent.GetName());
			vector position[4];
			ent.GetTransform(position);
			PrintFormat("COORDINATE %1", position);
		}
		
		return true;
	}
	*/
	
	/*! 
		loops for every found entity and decides if it is passed to hit-callback
	*/
	private bool filterEntity(IEntity ent) {
		if (ent != null) {
			VObject mesh = ent.GetVObject();
			if (mesh) {
				//Print("CLASS " + ent.ClassName());
				//Print("RESOURCE " + mesh.GetResourceName());
			
				vector transformation[4];
				ent.GetTransform(transformation);
				PrintFormat("COORDINATE %1", transformation);
				
				MapEntityDto mapEntityDto = new MapEntityDto;
				
				mapEntityDto.className = ent.ClassName();
				mapEntityDto.resourceName = mesh.GetResourceName();
				
				mapEntityDto.rotationX = transformation[0];
				mapEntityDto.rotationY = transformation[1];
				mapEntityDto.rotationZ = transformation[2];
				mapEntityDto.coords = transformation[3];
				
				adapter.post(mapEntityDto);
			}
		}
		
		return false;
	}
	
	
	
	
	
	/*
	override void OnActivate(IEntity ent) {
		RplComponent rplComponent = RplComponent.Cast(FindComponent(RplComponent));
		if (rplComponent) {
			rplComponent.InsertItem(this);
		}
		
		Print(Replication.FindId(this));

		if (rplComponent && !rplComponent.IsProxy()) {
			GetWorld().QueryEntitiesBySphere(GetOrigin(), 10000, QueryHit, QueryFilter, EQueryEntitiesFlags.ALL);
		}
    }
    
	bool QueryFilter(IEntity ent) {
		SCR_IdentifierComponent idComponent = SCR_IdentifierComponent.Cast(ent.FindComponent(SCR_IdentifierComponent));

    	if (!idComponent) {
     		return false;
		}

    	return idComponent.GetIdentifier() == "apc";
	}
    
	bool QueryHit(IEntity ent) {
   		SCR_SpawnPoint spawnPoint = SCR_SpawnPoint.Cast(GetWorld().FindEntityByName("spawnPoint_apc"));
        
        // If we can find the spawnpoint and target vehicle (ent)
        if (spawnPoint) {
			// Unlock it
        	spawnPoint.SetFactionKey("US");

    		// Keep moving it
    		RplComponent rplComponent = RplComponent.Cast(FindComponent(RplComponent));
    		if (rplComponent && !rplComponent.IsProxy()) {
        		GetGame().GetCallqueue().CallLater(UpdateAPCSpawnPosition, 1000, true, spawnPoint, ent);
			}
 		}

 		// Ends further queries as we will use the first match found
		return false;
	}
	*/

}