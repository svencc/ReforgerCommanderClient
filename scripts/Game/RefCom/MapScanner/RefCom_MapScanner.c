class RefCom_MapScanner {

	protected bool startedProduction = false;
	protected bool finishedProduction = false;
	
	protected bool startedConsumption = false;
	protected bool finishedConsumption = false;
	
	protected int worldSize;
	protected int boxScanSize;
	
	protected int predictedScanIterations;
	protected int iterationX;
	protected int iterationY;
	
	protected string worldFileName

	protected ref array<IEntity> entitiesQueue = {};
	protected ref RefCom_MapScannerEntitiesShippingService shippingService;
	protected ref RefCom_MapScannerEntitiesTransactionManager transactionManager

	void RefCom_MapScanner(
		RefCom_MapScannerEntitiesShippingService shippingService,
		int boxScanSize
	) {
		this.shippingService = shippingService;
		this.boxScanSize = boxScanSize;
		
		init(boxScanSize);
	}

	void ~RefCom_MapScanner() {
		entitiesQueue.Clear()
	}

	protected void init(int boxScanSize) {
		determineMapSize();
        worldFileName = GetGame().GetWorldFile();
		predictedScanIterations = Math.Floor(worldSize/boxScanSize);
		iterationX = 0;
		iterationY = 0;
		
        transactionManager = new RefCom_MapScannerEntitiesTransactionManager(worldFileName);
        shippingService.preparePackage(worldFileName);
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

		if (entitiesQueue.IsEmpty() && finishedProduction) {
			finishedConsumption = true;
			shippingService.flush();
			transactionManager.commitTransaction(shippingService.getPackagesSent());
			PrintFormat("%1: consumption completed.", "MapScannerProducerConsumer");
		} else if(entitiesQueue.IsEmpty() == false) {
			
			int elementsToConsume = Math.Min(
				entitiesQueue.Count(), 
				shippingService.getMaxPackageSizeBeforeTransmission()
			);
			
			for (int i = 0; i < elementsToConsume; i++) {
				IEntity entity = entitiesQueue.Get(0);
				transmit(entity);
				entitiesQueue.RemoveOrdered(0);
			}
			
			PrintFormat("... %1: remaining entities to consume.", entitiesQueue.Count());
		}
	}
	
	protected void scanPartitionBoxical(
		vector mins, 
		vector maxs
	) {
		GetGame().GetWorld().QueryEntitiesByAABB(
			mins,
			maxs,
			queryHitAddEntityToQueue,
			null,
			EQueryEntitiesFlags.ALL
		);
	}

	protected void determineMapSize() {
		vector min, max;
		GetGame().GetWorldEntity().GetWorldBounds(min, max);
		worldSize = Math.Max(max[0] - min[0], max[2] - min[2]);
	}
	
	protected vector scanBoxMaxForThisIteration(int iterationX, int iterationY ) {
		return {
			boxScanSize + (iterationX * boxScanSize),
			0,
			boxScanSize + (iterationY * boxScanSize)
		};
	}	
	
	protected vector scanBoxMinForThisIteration(int iterationX, int iterationY ) {
		return {
			(iterationX * boxScanSize),
			0,
			(iterationY * boxScanSize)
		};
	}
	
	protected bool queryHitAddEntityToQueue(IEntity ent) {
		if (ent != null) {
			entitiesQueue.Insert(ent);
		}

		return true;
	}
	
	protected void transmit(IEntity ent) {
		vector transformation[4];
		ent.GetTransform(transformation);

		RefCom_MapScannerEntityDto entityDto = new RefCom_MapScannerEntityDto;

		entityDto.entityId =  ent.GetID().ToString();
		entityDto.name =  ent.GetName();

		entityDto.className =  ent.ClassName();
		entityDto.rotationX = transformation[0];
		entityDto.rotationY = transformation[1];
		entityDto.rotationZ = transformation[2];
		entityDto.coordinates = transformation[3];
		
		VObject mesh = ent.GetVObject();
		if (mesh) {
			entityDto.resourceName = mesh.GetResourceName();
		}
		
		EntityPrefabData prefab = ent.GetPrefabData();
		if (prefab) {
			ResourceName prefabName = prefab.GetPrefabName();
			if (prefabName) {
				entityDto.prefabName = prefabName.GetPath();
			}
		}
		
		MapDescriptorComponent mapdesc = MapDescriptorComponent.Cast(ent.FindComponent(MapDescriptorComponent));
		if (mapdesc) {	
			entityDto.mapDescriptorType = typename.EnumToString(EMapDescriptorType, mapdesc.GetBaseType());;
		}
		

		shippingService.assemblePackage(entityDto);
	}

}