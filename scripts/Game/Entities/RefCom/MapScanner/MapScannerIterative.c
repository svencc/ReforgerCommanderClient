class MapScannerIterative {

	protected bool finished = false;
	protected int worldSize;
	protected int scanRadius;
	protected float halfScanRadius;
	protected int predictedScanIterations;
	protected int iterationX;
	protected int iterationY;
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
		PrintFormat("%1: produce called", "MapScannerProducerConsumer");
		
		if (finished) {
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
			}
		}

		PrintFormat("%1: produce processed", "MapScannerProducerConsumer");
	}

	private void scanPartition(vector scanCenterParam, int scanRadiusParam) {
		GetGame().GetWorld().QueryEntitiesBySphere(
			scanCenterParam,
			scanRadiusParam,
			queryHitREST,
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

				adapter.post(mapEntityDto);
			}
		}

		return true;
	}

}