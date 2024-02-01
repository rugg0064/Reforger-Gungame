class GunGameUtils
{
	static void SetPlayerWeapon(IEntity player, int playerId)
    {
		// Find/Create required entities and components
        ArmaReforgerScripted game = GetGame();
        GunGameMode gameMode = GunGameMode.gunGameMode;
		GunGameWeaponSelection weaponSelection = gameMode.getWeaponForPlayer(playerId);
        IEntity weapon = game.SpawnEntityPrefab(Resource.Load(weaponSelection.getResourceName()), null, null);
		SCR_CharacterControllerComponent characterController = SCR_CharacterControllerComponent.Cast(player.FindComponent(SCR_CharacterControllerComponent));
		InventoryStorageManagerComponent inventoryStorageManager = characterController.GetInventoryStorageManager();
		
		// Clear out all equipped weapons
		array<Managed> cwscs = new array<Managed>();
		player.FindComponents(CharacterWeaponSlotComponent, cwscs);
		foreach(Managed cwscManaged : cwscs)
		{
			CharacterWeaponSlotComponent cwsc = CharacterWeaponSlotComponent.Cast(cwscManaged);
			BaseInventoryStorageComponent inventory = cwsc.GetSlotInfo().GetStorage();
			array<IEntity > entities = new array<IEntity >();
			inventory.GetAll(entities);
			foreach(IEntity entity : entities)
			{
				inventoryStorageManager.TryRemoveItemFromStorage(entity, inventory);
			}
		}
		// Why does this need to be a delayed call! 250ms seems to work every time, but 0 or 1 doesn't.
		GetGame().GetCallqueue().CallLater(setPlayerWeapon2, 250, false, player, weapon, weaponSelection);
    }
	
	static void setPlayerWeapon2(IEntity player, IEntity weapon, GunGameWeaponSelection weaponSelection)
	{
		// Get components back
		SCR_CharacterControllerComponent characterController = SCR_CharacterControllerComponent.Cast(player.FindComponent(SCR_CharacterControllerComponent));
		InventoryStorageManagerComponent inventoryStorageManager = characterController.GetInventoryStorageManager();
		inventoryStorageManager.TryInsertItemInStorage(weapon, inventoryStorageManager.FindStorageForItem(weapon, EStoragePurpose.PURPOSE_WEAPON_PROXY));
		// Send an RPC to the client to equip the new weapon
		WeaponEquipComponent wec = WeaponEquipComponent.Cast(player.FindComponent(WeaponEquipComponent));
		GetGame().GetCallqueue().CallLater(wec.setWeapon, 0, false, player, weapon);
	}
}