class MapScannerProducerConsumer {

	protected bool finishedProduction = false;
	protected bool finishedConsumption = false;
	protected int worldSize;
	protected int scanRadius;
	protected float halfScanRadius;
	protected int predictedScanIterations;
	protected int iterationX;
	protected int iterationY;
	protected string worldFileName

	//protected ref TManagedArray entities = new TManagedArray();
	protected ref array<IEntity> entities = {};
	protected ref MapScannerEntitiesShippingServiceProvider shippingService;
	protected ref MapScannerEntitiesTransactionManager transactionManager

	void MapScannerProducerConsumer(
		MapScannerEntitiesShippingServiceProvider shippingServiceParameter,
		int scanRadius
	) {
		this.shippingService = shippingServiceParameter;
		init(scanRadius);
	}

	void ~MapScannerProducerConsumer() {
	}

	private void init(int scanRadius) {
		this.scanRadius = scanRadius;
		halfScanRadius = scanRadius/2;
		determineMapSize();
        worldFileName = GetGame().GetWorldFile();
		predictedScanIterations = Math.Floor(worldSize/scanRadius);
		iterationX = 0;
		iterationY = 0;

        transactionManager = new MapScannerEntitiesTransactionManager(worldFileName);
        transactionManager.openTransaction();
	}

	void produce() {
		PrintFormat("%1: start production of %2 ...", "MapScannerProducerConsumer", worldFileName);

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

		PrintFormat("... %1: production completed.", "MapScannerProducerConsumer");
	}
	
	void consume() {
		PrintFormat("%1: start consumtion ...", "MapScannerProducerConsumer");
		
		if (finishedConsumption) {
			return;
		} else {
			if (entities.IsEmpty() && finishedProduction) {
				finishedConsumption = true;
				transactionManager.commitTransaction();
			} else if(entities.IsEmpty() == false) {
				IEntity entity = entities.Get(0);
				transmit(entity);
				entities.RemoveItemOrdered(entity);
				PrintFormat("... %1: remaining entities to consume.", entities.Count());
			}
		}
		
		shippingService.flush();
		PrintFormat("... %1: consumption completed.", "MapScannerProducerConsumer");
	}

	private void scanPartition(
		vector scanCenterParam, 
		int scanRadiusParam
	) {
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
	
	private void transmit(IEntity ent) {
		vector transformation[4];
		ent.GetTransform(transformation);

		MapScannerEntityDto entityDto = new MapScannerEntityDto;

		entityDto.entityId =  ent.GetID().ToString();
		entityDto.className =  ent.ClassName();
		entityDto.rotationX = transformation[0];
		entityDto.rotationY = transformation[1];
		entityDto.rotationZ = transformation[2];
		entityDto.coords = transformation[3];
		
		VObject mesh = ent.GetVObject();
		if (mesh) {
			entityDto.resourceName = mesh.GetResourceName();
		}

		shippingService.assemblePackage(entityDto);
	}

}