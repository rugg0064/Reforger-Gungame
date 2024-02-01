[EntityEditorProps(category: "GunGame/Components", description: "Out of bounds display")]
class WeaponEquipComponentClass: GameComponentClass
{
}

// This class exists to provide a function to force a player to equip a weapon.
class WeaponEquipComponent: GameComponent
{
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void setWeaponRPC(RplId playerId, RplId weaponId)
	{
		RplComponent playerRplComponent = RplComponent.Cast(Replication.FindItem(playerId));
		IEntity player = playerRplComponent.GetEntity();
		RplComponent weaponRplComponent = RplComponent.Cast(Replication.FindItem(weaponId));
		IEntity weaponEntity = weaponRplComponent.GetEntity();
		SCR_CharacterControllerComponent characterController = SCR_CharacterControllerComponent.Cast(player.FindComponent(SCR_CharacterControllerComponent));
		bool equipped = characterController.TryEquipRightHandItem(weaponEntity, EEquipItemType.EEquipTypeWeapon, true, null);
	}
	
	void setWeapon(IEntity player, IEntity weapon)
	{
		Rpc(setWeaponRPC, RplComponent.Cast(player.FindComponent(RplComponent)).Id(), RplComponent.Cast(weapon.FindComponent(RplComponent)).Id());
	}
}