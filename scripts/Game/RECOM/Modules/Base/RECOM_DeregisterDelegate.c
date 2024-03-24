class RECOM_BaseDeregisterDelegate<Class REGISTRY_TYPE> {

	protected ref array<ref REGISTRY_TYPE> registry;
	
	
	void RECOM_BaseDeregisterDelegate(notnull array<ref REGISTRY_TYPE> registry) {
		this.registry = registry;
	}

	void ~RECOM_BaseDeregisterDelegate() {
		registry = null;
	}
	
	void deregister(notnull REGISTRY_TYPE entry ) {
		SLF4R.normal(string.Format("%1: deregister() ...", ClassName()));
		registry.RemoveItem(entry)
	}
	
}