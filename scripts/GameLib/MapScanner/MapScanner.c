class MapScanner {
		
	private int worldSize;
	
	void MapScanner() {
		PrintFormat("%1 Constructor called", "MapScanner");
		determineMapSize();
	}
	
	void ~MapScanner() {
		PrintFormat("%1 Destructor called", "MapScanner");
	}
	
	int GetWorldSize() {
		return worldSize;
	}
	
	void scanMap() {
		g_Game.GetWorld().QueryEntitiesBySphere(
			GetOrigin(), // centre
			10000, // radius
			addEntity, // addEntity
			filterEntity, // filterEntity
			EQueryEntitiesFlags.ALL //queryFlags
		);
			
		/*
		g_Game.GetWorld().QueryEntitiesBySphere(
			(vector) {GetWorldSize()/2, 0, GetWorldSize()/2},
			GetWorldSize(),
			null,null,null
		);
		*/
	}

	private void determineMapSize() {
		vector min, max;
		g_Game.GetWorldEntity().GetWorldBounds(min, max);
		worldSize = Math.Max(max[0] - min[0], max[2] - min[2]);
	}

	bool filterEntity(IEntity ent) {
		return true
	}
	
	
	
	
	
	
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

}