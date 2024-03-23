class RECOM_MapMetaProvider {

	
	protected void RECOM_MapMetaProvider() {
	}

	protected void ~RECOM_MapMetaProvider() {
	}
	
	
	static RECOM_MapMeta provide() {
		vector mins, maxs;
		GetGame().GetWorldEntity().GetWorldBounds(mins, maxs);
		
		RECOM_MapMeta mapMeta = new RECOM_MapMeta();
		mapMeta.mapName = GetGame().GetWorldFile();
		mapMeta.dimensionXInMeter = maxs[0] - mins[0];
		mapMeta.dimensionYInMeter = maxs[1] - mins[1];
		mapMeta.dimensionZInMeter = maxs[2] - mins[2];
		mapMeta.oceanBaseHeight = GetGame().GetWorld().GetOceanBaseHeight();
		
		return mapMeta;
	}

}