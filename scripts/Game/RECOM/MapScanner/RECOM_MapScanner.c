class RECOM_MapScanner {

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

	protected ref array<IEntity> producedEntitiesQueue = {};
	protected ref RECOM_MapScannerEntitiesShippingService shippingService;
	protected ref RECOM_MapScannerEntitiesTransactionManager transactionManager

	void RECOM_MapScanner(
		RECOM_MapScannerEntitiesShippingService shippingService,
		int boxScanSize
	) {
		this.shippingService = shippingService;
		this.boxScanSize = boxScanSize;
		init(boxScanSize);
	}

	void ~RECOM_MapScanner() {
		producedEntitiesQueue.Clear()
	}

	protected void init(int boxScanSize) {
		worldSize = determineMapSize();
        worldFileName = GetGame().GetWorldFile();
		predictedScanIterations = Math.Floor(worldSize/boxScanSize);
		iterationX = 0;
		iterationY = 0;
		
        transactionManager = new RECOM_MapScannerEntitiesTransactionManager(worldFileName);
        shippingService.setSessionIdentifier(worldFileName);
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
				PrintFormat("... x:%1 y:%2", iterationX, iterationY);
				vector min = scanBoxMinForThisIteration(iterationX, iterationY);
				vector max = scanBoxMaxForThisIteration(iterationX, iterationY);		
				scanPartitionBoxical(min, max);
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

		if (producedEntitiesQueue.IsEmpty() && finishedProduction) {
			finishedConsumption = true;
			shippingService.flush();
			PrintFormat("... %1: consumption completed.", "MapScannerProducerConsumer");
			transactionManager.commitTransaction(shippingService.getPackagesSent());
			PrintFormat("%1: committed transaction.", "MapScannerProducerConsumer");
		} else if(producedEntitiesQueue.IsEmpty() == false) {
			
			int elementsToConsume = Math.Min(
				producedEntitiesQueue.Count(), 
				shippingService.getMaxPackageSizeBeforeFlush()
			);
			
			for (int i = 0; i < elementsToConsume; i++) {
				IEntity entityToSend = producedEntitiesQueue.Get(0);
				package(entityToSend);
				producedEntitiesQueue.RemoveItemOrdered(entityToSend);
				//producedEntitiesQueue.RemoveOrdered(0);
			}
			
			PrintFormat("... %1: remaining entities to consume.", producedEntitiesQueue.Count());
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

	protected int determineMapSize() {
		vector min, max;
		GetGame().GetWorldEntity().GetWorldBounds(min, max);
		return Math.Max(max[0] - min[0], max[2] - min[2]);
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
			producedEntitiesQueue.Insert(ent);
		}

		return true;
	}
	
	protected void package(IEntity ent) {
		vector transformation[4];
		ent.GetTransform(transformation);

		RECOM_MapScannerEntityDto entityDto = new RECOM_MapScannerEntityDto;

		entityDto.entityId =  ent.GetID().ToString();
		entityDto.name =  ent.GetName();

		entityDto.className =  ent.ClassName();
		entityDto.rotationX = transformation[0];
		entityDto.rotationY = transformation[1];
		entityDto.rotationZ = transformation[2];
		entityDto.coordinates = transformation[3];
		
		BaseResourceObject mesh = ent.GetVObject();
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