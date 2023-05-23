class MapScannerIterative {

	protected bool finishedProduction = false;
	protected bool finishedConsumption = false;
	protected int worldSize;
	protected int scanRadius;
	protected float halfScanRadius;
	protected int predictedScanIterations;
	protected int iterationX;
	protected int iterationY;

	protected ref TManagedArray entities = new TManagedArray();
	protected ref MapScannerEntityRestAdapter adapter;

	void MapScannerIterative(int scanRadius) {
		PrintFormat("%1 Constructor called", "MapScannerIterative");
		init(scanRadius);

	}

	void ~MapScannerIterative() {
		PrintFormat("%1 Destructor called", "MapScannerIterative");
	}

	private void init(int scanRadius) {
		this.scanRadius = scanRadius;
		halfScanRadius = scanRadius/2;
		determineMapSize();
		predictedScanIterations = Math.Floor(worldSize/scanRadius);
		iterationX = 0;
		iterationY = 0;
		adapter = new MapScannerEntityRestAdapter;
	}

	void produce() {
		if (finishedProduction) {
			return;
		} else {
			if (iterationY < predictedScanIterations) {
				if (iterationX < predictedScanIterations) {
					vector scanCenter = scanCentreForThisIteration(iterationX, iterationY);
					PrintFormat("y:%1 x:%2 center:%3", iterationY, iterationX, scanCenter);
					scanPartition(scanCenter, scanRadius);
					iterationX++;
				} else {
					iterationY++;
					iterationX = 0;
				}
			} else {
				finishedProduction = true;
			}
		}

		// PrintFormat("%1: produce processed", "MapScannerProducerConsumer");
	}
	
	void consume() {
		if (finishedConsumption) {
			return;
		} else {
			if (entities.IsEmpty() && finishedProduction) {
				finishedConsumption = true;
			} else if(entities.IsEmpty() == false) {
				Managed managedEntity = entities.Get(0);
				IEntity entity = IEntity.Cast(managedEntity);
				transmit(entity);
				entities.RemoveItem(managedEntity);
				PrintFormat("%1: consumed", "MapScannerProducerConsumer");
			}
		}
	}

	private void scanPartition(vector scanCenterParam, int scanRadiusParam) {
		GetGame().GetWorld().QueryEntitiesBySphere(
			scanCenterParam,
			scanRadiusParam,
			queryHitAddEntity,
			null,
			EQueryEntitiesFlags.STATIC
		);
	}

	private void determineMapSize() {
		vector min, max;
		GetGame().GetWorldEntity().GetWorldBounds(min, max);
		worldSize = Math.Max(max[0] - min[0], max[2] - min[2]);
	}
	
	private vector scanCentreForThisIteration(int iterationX, int iterationY ) {
		return {
			halfScanRadius+(iterationX * scanRadius),
			0,
			halfScanRadius+(iterationY * scanRadius)
		};
	}
	
	

	private bool queryHitAddEntity(IEntity ent) {
		if (ent != null) {
			entities.Insert(ent);
		}

		return true;
	}
	
	private bool transmit(IEntity ent) {
		vector transformation[4];
		ent.GetTransform(transformation);

		MapEntityDto mapEntityDto = new MapEntityDto;

		mapEntityDto.className = ent.ClassName();
		mapEntityDto.rotationX = transformation[0];
		mapEntityDto.rotationY = transformation[1];
		mapEntityDto.rotationZ = transformation[2];
		mapEntityDto.coords = transformation[3];
		
		VObject mesh = ent.GetVObject();
		if (mesh) {
			mapEntityDto.resourceName = mesh.GetResourceName();
		}

		adapter.post(mapEntityDto);

		return true;
	}

}