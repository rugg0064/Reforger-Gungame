//------------------------------------------------------------------------------------------------
class RespawnWeaponProviderClass : SCR_RespawnSystemComponentClass
{
};

//! Scripted implementation that handles spawning and respawning of players.
//! Should be attached to a GameMode entity.
[ComponentEditorProps(icon: HYBRID_COMPONENT_ICON)]
class RespawnWeaponProvider : SCR_RespawnSystemComponent
{
	override void OnPlayerSpawnFinalize_S(SCR_SpawnRequestComponent requestComponent, SCR_SpawnHandlerComponent handlerComponent, SCR_SpawnData data, IEntity entity)
	{
		super.OnPlayerSpawnFinalize_S(requestComponent, handlerComponent, data, entity);
		Print("Spawn was finalized!");
		Print(entity);
		
		GunGameUtils.SetPlayerWeapon(ChimeraCharacter.Cast(entity), requestComponent.GetPlayerId());
	}
}