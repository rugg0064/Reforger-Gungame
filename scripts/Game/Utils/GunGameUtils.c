class GunGameUtils
{
	static void SetPlayerWeapon(ChimeraCharacter player, int playerId)
	{
		Print("Trying to provide weapon");
		ArmaReforgerScripted game = GetGame();
		GunGameMode gameMode = GunGameMode.gunGameMode;
		
		GunGameWeaponSelection weaponSelection = gameMode.getWeaponForPlayer(playerId);
		Print(weaponSelection);
		IEntity weapon = game.SpawnEntityPrefab(Resource.Load(weaponSelection.getResourceName()), null, null);
		
		if(weaponSelection.getType() == "GUN")
		{
			CharacterWeaponSlotComponent weaponSlotComponent = CharacterWeaponSlotComponent.Cast(player.FindComponent(CharacterWeaponSlotComponent));
			weaponSlotComponent.SetWeapon(weapon);
			SCR_CharacterControllerComponent component = SCR_CharacterControllerComponent.Cast(player.FindComponent(SCR_CharacterControllerComponent));
			component.TryEquipRightHandItem(null, EEquipItemType.EEquipTypeUnarmedContextual, true, null);
			component.TryEquipRightHandItem(weapon, EEquipItemType.EEquipTypeWeapon, false, null);
		}
		else if(weaponSelection.getType() == "GRENADE")
		{
			CharacterGrenadeSlotComponent grenadeSlotComponent = CharacterGrenadeSlotComponent.Cast(player.FindComponent(CharacterGrenadeSlotComponent));
			grenadeSlotComponent.SetWeapon(weapon);
			SCR_CharacterControllerComponent component = SCR_CharacterControllerComponent.Cast(player.FindComponent(SCR_CharacterControllerComponent));
			component.TryEquipRightHandItem(null, EEquipItemType.EEquipTypeUnarmedContextual, true, null);
			component.TryEquipRightHandItem(weapon, EEquipItemType.EEquipTypeWeapon, false, null);	

		}
		
	}
}