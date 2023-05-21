class MapScanner {

	private int worldSize;
	private int scanRadius;
	private float halfScanRadius;
	private int predictedScanIterations;
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
		PrintFormat("%1: GetWorldSize called - return %2", "MapScanner", worldSize);
		return worldSize;
	}

	void scanMap(int scanRadiusParameter) {
		scanRadius = scanRadiusParameter;
		halfScanRadius = scanRadius/2;
		predictedScanIterations = Math.Floor(worldSize/scanRadius);
		
		for (int iterationY = 0; iterationY < predictedScanIterations; iterationY++) 
		{
			for (int iterationX = 0; iterationX < predictedScanIterations; iterationX++)
			{
				PrintFormat("iterY %1 iterX %2 centre %3", iterationY, iterationX, scanCentreForThisIteration(iterationX, iterationY));
				
				GetGame().GetWorld().QueryEntitiesBySphere(
					scanCentreForThisIteration(iterationX, iterationY),
					scanRadius,
					null, // hit-callback // we do not need that here
					filterEntity, // filter callback
					EQueryEntitiesFlags.STATIC
				);
			}					
		}				
		
		PrintFormat("%1: scanMap processed", "MapScanner");
	}

	private void determineMapSize() {
		PrintFormat("%1: determineMapSize called", "MapScanner");
		vector min, max;
		GetGame().GetWorldEntity().GetWorldBounds(min, max);
		worldSize = Math.Max(max[0] - min[0], max[2] - min[2]);
		PrintFormat("%1: determineMapSize processed - result %2", "MapScanner", worldSize);
	}
	
	private vector scanCentreForThisIteration(int iterationX, int iterationY ) {
		return {
			halfScanRadius+(iterationX * scanRadius),
			0,
			halfScanRadius+(iterationY * scanRadius)
		};
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