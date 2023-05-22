class MapScanner {

	protected int worldSize;
	protected int scanRadius;
	protected float halfScanRadius;
	protected int predictedScanIterations;
	protected ref MapScannerEntityRestAdapter adapter;
	//protected ref TManagedArray entities = new TManagedArray();
	protected ref array<ref EntityID> entities = new array<ref EntityID>;

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
		
		//scanPartition(mapCentre(), scanRadiusParameter);
		
		for (int iterationY = 0; iterationY < predictedScanIterations; iterationY++) {
			for (int iterationX = 0; iterationX < predictedScanIterations; iterationX++) {
				vector scanCenter = scanCentreForThisIteration(iterationX, iterationY);
				PrintFormat("iterY %1 iterX %2 centre %3", iterationY, iterationX, scanCenter);
				scanPartition(scanCenter, scanRadius);
			}					
		}				

		PrintFormat("%1: scanMap processed", "MapScanner");
	}

	private void scanPartition(vector scanCenterParam, int scanRadiusParam) {
		GetGame().GetWorld().QueryEntitiesBySphere(
			scanCenterParam,
			scanRadiusParam,
			queryHit,
			null,
			EQueryEntitiesFlags.ALL
		);
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



	private bool queryHit(IEntity ent) {
		if (ent != null) {
			Print("ENT NAME " + ent.GetName());
			vector position[4];
			ent.GetTransform(position);
			PrintFormat("COORDINATE %1", position);
			entities.Insert(ent.GetID());
		}

		return true;
	}

	private bool queryHitREST(IEntity ent) {
		if (ent != null) {
			VObject mesh = ent.GetVObject();
			if (mesh) {
				//Print("CLASS " + ent.ClassName());
				//Print("RESOURCE " + mesh.GetResourceName());

				vector transformation[4];
				ent.GetTransform(transformation);
				//PrintFormat("COORDINATE %1", transformation);

				MapEntityDto mapEntityDto = new MapEntityDto;

				mapEntityDto.className = ent.ClassName();
				mapEntityDto.resourceName = mesh.GetResourceName();

				mapEntityDto.rotationX = transformation[0];
				mapEntityDto.rotationY = transformation[1];
				mapEntityDto.rotationZ = transformation[2];
				mapEntityDto.coords = transformation[3];

				// adapter.post(mapEntityDto);
				MapScannerEntityRestAdapter localAdapter = new MapScannerEntityRestAdapter;
				localAdapter.post(mapEntityDto);
			}
		}

		return true;
	}
	
	
	/*!
		loops for every found entity and decides if it is passed to hit-callback
	*/
	private bool filterEntity(IEntity ent) {
		return true;
		if (ent != null) {
			VObject mesh = ent.GetVObject();
			if (mesh) {
				return true;
			}
		} 

		return false;
	}

// https://github.com/ArmaOverthrow/Overthrow.Arma4/blob/f7e86e3bac17498adde069ba9829cbe37293ccc8/Scripts/Game/GameMode/Components/OVT_TownManagerComponent.c#L67
	//		return GetGame().GetWorld().FindEntityByID(m_Houses.GetRandomElement());




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
	
	
	
	
		void scanMapSimple() {
		Print("scanMapSimple");
		g_Game.GetWorld().QueryEntitiesBySphere(
			mapCentre(),
			//worldSize,
			150,
			queryHit, // hit-callback
			null, // filter callback
			EQueryEntitiesFlags.STATIC
		);
	}
	
	private vector mapCentre() {
		return {worldSize/2, 0, worldSize/2};
	}

}