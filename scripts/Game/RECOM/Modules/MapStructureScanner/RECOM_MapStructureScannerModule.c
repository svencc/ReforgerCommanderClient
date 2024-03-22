class RECOM_MapStructureScannerModule : RECOM_BaseModule {

	private static ref RECOM_MapStructureScannerModule instance;
	
	protected bool startedProduction = false;
	protected bool finishedProduction = false;
	
	protected bool startedConsumption = false;
	protected bool finishedConsumption = false;
	
	protected int worldSize;
	protected int boxScanSize;
	
	protected int predictedScanIterations;
	protected int iterationX;
	protected int iterationZ;
	
	protected string worldFileName

	protected ref array<IEntity> producedEntitiesQueue = {};
	protected ref RECOM_MapStructureScannerEntitiesShippingService shippingService;
	protected ref RECOM_MapStructureScannerEntitiesTransactionManager transactionManager

	
	static RECOM_MapStructureScannerModule getModule() {
		SLF4R.normal(string.Format("RECOM_MapStructureScannerModule: getModule() ..."));
        if (!RECOM_MapStructureScannerModule.instance) {
            RECOM_MapStructureScannerModule.instance = new RECOM_MapStructureScannerModule(new RECOM_MapStructureScannerEntitiesShippingService(500), 150);
        }
		
        return RECOM_MapStructureScannerModule.instance;
    }
	
	override void startModule() {
		super.startModule();
	}
	
	override void disposeModule() {
		super.disposeModule();
		RECOM_MapStructureScannerModule.instance = null;
		
		startedProduction = false;
		finishedProduction = false;
	
		startedConsumption = false;
		finishedConsumption = false;
	}
	
	void runScanner() {
		SLF4R.normal(string.Format("%1: runScanner() ...", ClassName()));
		initProduction(boxScanSize);
		GetGame().GetCallqueue().CallLater(produce, 5, false);
		GetGame().GetCallqueue().CallLater(consume, 200, false);
	}
	
	private void RECOM_MapStructureScannerModule(
		RECOM_MapStructureScannerEntitiesShippingService service,
		int scanSize
	) {
		shippingService = service;
		boxScanSize = scanSize;
	}

	void ~RECOM_MapStructureScannerModule() {
		producedEntitiesQueue.Clear();
		producedEntitiesQueue = null;
		shippingService = null;
		transactionManager = null;
		RECOM_MapStructureScannerModule.instance = null;
	}

	protected void initProduction(int boxScanSize) {
		worldSize = determineMapSize();
        worldFileName = GetGame().GetWorldFile();
		predictedScanIterations = Math.Floor(worldSize/boxScanSize);
		iterationX = 0;
		iterationZ = 0;
		
        transactionManager = new RECOM_MapStructureScannerEntitiesTransactionManager(worldFileName);
        shippingService.setSessionIdentifier(worldFileName);
	}

	void produce() {
		if (finishedProduction) {
			SLF4R.normal(string.Format("%1: end production!", ClassName()));
			return;
		}
			
		if (!startedProduction) {
			startedProduction = true;
			SLF4R.normal(string.Format("%1: start production of %2 ...", ClassName(), worldFileName));
		}
	
		if (iterationZ < predictedScanIterations) {
			if (iterationX < predictedScanIterations) {	
				// scanPartitionBoxical(iterationX, iterationZ);
				scanPartitionSpherical(iterationX, iterationZ);
				iterationX++;
			} else {
				SLF4R.normal(string.Format("...%1 x:%2 z:%3", ClassName(), iterationX, iterationZ));
				iterationZ++;
				iterationX = 0;
			}
			GetGame().GetCallqueue().CallLater(produce, 0, false);
		} else {
			finishedProduction = true;
			SLF4R.normal(string.Format("... %1: production completed.", ClassName()));
		}

	}
	
	void consume() {
		if (finishedConsumption) {
			SLF4R.normal(string.Format("%1: end consumption!", ClassName()));
			return;
		}
		
		if (!startedConsumption && RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			startedConsumption = true;
			transactionManager.openTransaction();
			SLF4R.normal(string.Format("%1: start consumption ...", ClassName()));
		}

		if (producedEntitiesQueue.IsEmpty() && finishedProduction && RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			finishedConsumption = true;
			shippingService.flush();
			SLF4R.normal(string.Format("... %1: consumption completed.", ClassName()));
			transactionManager.commitTransaction(shippingService.getPackagesSent());
			SLF4R.normal(string.Format("%1: committed transaction.", ClassName()));
		} else if(producedEntitiesQueue.IsEmpty() == false && RECOM_AuthenticationModule.getModule().isAuthenticated()) {
			int elementsToConsume = Math.Min(
				producedEntitiesQueue.Count(), 
				shippingService.getMaxPackageSizeBeforeFlush()
			);
			
			SLF4R.debugging(string.Format("... %1: entities to consume.", elementsToConsume));
			for (int i = 0; i < elementsToConsume; i++) {
				if (producedEntitiesQueue.Count() == 0) {
					break; // strange ARMA issue since 1.0 ...
				}

				IEntity entityToSend = producedEntitiesQueue.Get(0); // <<<< oho; SCRIPT    (E): Virtual Machine E SCRIPT    reason: Index out of bounds.
				if (entityToSend) {
					packageEntity(entityToSend);
				 	producedEntitiesQueue.RemoveItemOrdered(entityToSend);
				}
			}
			SLF4R.debugging(string.Format("... %1: remaining entities to consume.", producedEntitiesQueue.Count()));
		}
		
		GetGame().GetCallqueue().CallLater(consume, 0, false);
	}
	
	protected void scanPartitionSpherical(
		int iterationX, 
		int iterationZ
	) {
		float radius = (boxScanSize * Math.Sqrt(2)) / 2;
		
		float centerX = (iterationX * boxScanSize) + (boxScanSize / 2);
		float centerZ = (iterationZ * boxScanSize) + (boxScanSize / 2);
		float centerY = GetGame().GetWorld().GetSurfaceY(centerX, centerZ);
		
		vector center = {
			centerX,
			centerY,
			centerZ
		};
		
		GetGame().GetWorld().QueryEntitiesBySphere(
			center,
			radius,
			queryHitAddEntityToQueue,
			null,
			EQueryEntitiesFlags.ALL
		);
	}
	
	protected void scanPartitionBoxical(
		int iterationX, 
		int iterationZ
	) {
		vector mins = scanBoxMinForThisIteration(iterationX, iterationZ);
		vector maxs = scanBoxMaxForThisIteration(iterationX, iterationZ);
		
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
	
	protected vector scanBoxMaxForThisIteration(
		int iterationX, 
		int iterationZ
	) {
		return {
			boxScanSize + (iterationX * boxScanSize),
			0,
			boxScanSize + (iterationZ * boxScanSize)
		};
	}	
	
	protected vector scanBoxMinForThisIteration(
		int iterationX, 
		int iterationZ
	) {
		return {
			(iterationX * boxScanSize),
			0,
			(iterationZ * boxScanSize)
		};
	}
	
	protected bool queryHitAddEntityToQueue(IEntity ent) {
		if (ent != null) {
			producedEntitiesQueue.Insert(ent);
		}

		return true;
	}
	
	protected void packageEntity(IEntity ent) {
		if(ent == null) {
			return;
		}
		vector transformation[4];
		ent.GetTransform(transformation);

		RECOM_MapStructureEntityDto entityDto = new RECOM_MapStructureEntityDto;

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
				string path = prefabName.GetPath();
				if (path) {
					entityDto.prefabName = path;
				}
			}
		}
		
		MapDescriptorComponent mapdesc = MapDescriptorComponent.Cast(ent.FindComponent(MapDescriptorComponent));
		if (mapdesc) {	
			entityDto.mapDescriptorType = typename.EnumToString(EMapDescriptorType, mapdesc.GetBaseType());;
		}
		
		shippingService.assemblePackage(entityDto);
	}

}