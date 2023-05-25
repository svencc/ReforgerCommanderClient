class MapScannerProducerConsumer {

	protected bool startedProduction = false;
	protected bool finishedProduction = false;
	protected bool startedConsumption = false;
	protected bool finishedConsumption = false;
	protected int worldSize;
	protected int scanRadius;
	protected float halfScanRadius;
	protected int predictedScanIterations;
	protected int iterationX;
	protected int iterationY;
	protected string worldFileName

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
		if (finishedProduction) {
			return;
		}
			
		if (!startedProduction) {
			startedProduction = true;
			PrintFormat("%1: start production of %2 ...", "MapScannerProducerConsumer", worldFileName);
		}
	
		if (iterationY < predictedScanIterations) {
			if (iterationX < predictedScanIterations) {
				PrintFormat("y:%1 x:%2", iterationY, iterationX);
				scanPartitionBoxical(
					scanBoxMinForThisIteration(iterationX, iterationY),
					scanBoxMaxForThisIteration(iterationX, iterationY),
				);
				iterationX++;
			} else {
				iterationY++;
				iterationX = 0;
			}
		} else {
			finishedProduction = true;
			PrintFormat("... %1: production completed.", "MapScannerProducerConsumer");
		}

	}
	
	void consume() {
		if (finishedConsumption) {
			return;
		}
		
		if (!startedConsumption) {
			startedConsumption = true;
			PrintFormat("%1: start consumtion ...", "MapScannerProducerConsumer");
		}

		if (entities.IsEmpty() && finishedProduction) {
			finishedConsumption = true;
			transactionManager.commitTransaction();
		} else if(entities.IsEmpty() == false) {
			
			int elementsToConsume = Math.Max(
				entities.Count(), 
				shippingService.getMaxPackageSizeBeforeTransmission()
			);
			
			//for (int i = 0; i < elementsToConsume; i++) {
				IEntity entity = entities.Get(0);
				transmit(entity);
				entities.RemoveOrdered(0);
				//entities.RemoveItemOrdered(entity);
			//}
			
			PrintFormat("... %1: remaining entities to consume.", entities.Count());
		}

		shippingService.flush();
	}

	
	private void scanPartitionBoxical(
		vector mins, 
		vector maxs
	) {
		GetGame().GetWorld().QueryEntitiesByAABB(
			mins,
			maxs,
			queryHitAddEntity,
			null,
			EQueryEntitiesFlags.ALL
		);
	}

	private void determineMapSize() {
		vector min, max;
		GetGame().GetWorldEntity().GetWorldBounds(min, max);
		worldSize = Math.Max(max[0] - min[0], max[2] - min[2]);
	}
	
	
	private vector scanBoxMaxForThisIteration(int iterationX, int iterationY ) {
		return {
			scanRadius + (iterationX * scanRadius),
			0,
			scanRadius + (iterationY * scanRadius)
		};
	}	
	private vector scanBoxMinForThisIteration(int iterationX, int iterationY ) {
		return {
			(iterationX * scanRadius),
			0,
			(iterationY * scanRadius)
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