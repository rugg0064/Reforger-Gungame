class GunGameUtils
{
	static void SetPlayerWeapon(IEntity player, int playerId)
    {
        Print("Trying to provide weapon");
        ArmaReforgerScripted game = GetGame();
        GunGameMode gameMode = GunGameMode.gunGameMode;
        GunGameWeaponSelection weaponSelection = gameMode.getWeaponForPlayer(playerId);
        IEntity weapon = game.SpawnEntityPrefab(Resource.Load(weaponSelection.getResourceName()), null, null);
        Print(weapon);
		if(!weapon)
		{
			Print("Weapon failed to load!");
			return;
		}
		Print(weapon.GetID().ToString());
        switch(weaponSelection.getType())
        {
            case "GUN": {
				array<Managed> cwscs = new array<Managed>();
				player.FindComponents(CharacterWeaponSlotComponent, cwscs);
				CharacterWeaponSlotComponent cwsc = CharacterWeaponSlotComponent.Cast(cwscs[0]);
				
				CharacterWeaponManagerComponent cwmc = CharacterWeaponManagerComponent.Cast(player.FindComponent(CharacterWeaponManagerComponent));
                SCR_CharacterControllerComponent ccc = SCR_CharacterControllerComponent.Cast(player.FindComponent(SCR_CharacterControllerComponent));
                
				cwsc.SetWeapon(weapon);
				Print(cwmc.SetSlotWeapon(cwsc, weapon));
                bool equipped = ccc.TryEquipRightHandItem(weapon, EEquipItemType.EEquipTypeWeapon, true, null);
            	Print(equipped);
			}
                break;
				
            case "GRENADE":
                break;
        }
    }
	
	static void SetPlayerWeaponSpawn (ChimeraCharacter player, int playerId)
	{
		Print("Trying to provide weapon");
		ArmaReforgerScripted game = GetGame();
		GunGameMode gameMode = GunGameMode.gunGameMode;
		GunGameWeaponSelection weaponSelection = gameMode.getWeaponForPlayer(playerId);
		IEntity weapon = game.SpawnEntityPrefab(Resource.Load(weaponSelection.getResourceName()), null, null);
		
		if(weaponSelection.getType() == "GUN")
		{
			// ** This is the important block **
		
			SCR_CharacterControllerComponent ccc = SCR_CharacterControllerComponent.Cast(player.FindComponent(SCR_CharacterControllerComponent));
			CharacterWeaponManagerComponent cwmc = CharacterWeaponManagerComponent.Cast(player.FindComponent(CharacterWeaponManagerComponent));
			//CharacterHandWeaponSlotComponent chwsc = CharacterHandWeaponSlotComponent.Cast(player.FindComponent(CharacterHandWeaponSlotComponent));
			
			array<Managed> cwscs = new array<Managed>();
			player.FindComponents(CharacterWeaponSlotComponent, cwscs);
			Print(cwscs);
			CharacterWeaponSlotComponent cwsc = CharacterWeaponSlotComponent.Cast(cwscs[2]);
			cwsc.SetWeapon(weapon);
			ccc.TryEquipRightHandItem(null, EEquipItemType.EEquipTypeUnarmedContextual, true, null);
			ccc.TryEquipRightHandItem(weapon, EEquipItemType.EEquipTypeWeapon, false, null);	
			//cwmc.SetSlotWeapon(cwsc, weapon);
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