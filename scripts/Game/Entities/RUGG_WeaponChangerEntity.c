[EntityEditorProps(category: "Tutorial Entities", description: "Prints player's position regularly", color: "0 255 0 0")]
class RUGG_WeaponChangerEntityClass : GenericEntityClass
{
}

class RUGG_WeaponChangerEntity : GenericEntity
{
	[Attribute(defvalue: "1", desc: "Print player position")]
	protected bool m_bPrintPlayerPosition;

	[Attribute(defvalue: "1", desc: "Print a message when player is null")]
	protected bool m_bPrintWhenPlayerIsNull;

	[Attribute(defvalue: "1", uiwidget: UIWidgets.Slider, desc: "Print cycle period (in seconds)", params: "1 30 1")]
	protected int m_iCycleDuration;

	protected float timeLeft = m_iCycleDuration; // trigger Print on start

	protected static RUGG_WeaponChangerEntity s_Instance;

	[Attribute(defvalue: "1", desc: "Weapon")]
	protected ref array<ref ResourceName> weaponResourceNameList;
	
	int i = 0;
	
	bool flag = false;
	
	protected void HandlePlayerInterval()
	{
		if(flag)
		{
			return;
		}
		
		
		flag = true;
		ChimeraCharacter player = ChimeraCharacter.Cast(GetGame().GetPlayerController().GetControlledEntity());
		IEntity weapon = GetGame().SpawnEntityPrefab(Resource.Load(weaponResourceNameList[i]), null, null);

		CharacterWeaponSlotComponent weaponSlotComponent = CharacterWeaponSlotComponent.Cast(player.FindComponent(CharacterWeaponSlotComponent));
		weaponSlotComponent.SetWeapon(weapon);
		SCR_CharacterControllerComponent component = SCR_CharacterControllerComponent.Cast(player.FindComponent(SCR_CharacterControllerComponent));
		component.TryEquipRightHandItem(null, EEquipItemType.EEquipTypeUnarmedContextual, true, null);
		component.TryEquipRightHandItem(weapon, EEquipItemType.EEquipTypeWeapon, false, null);
		
		i++;
		i = i % weaponResourceNameList.Count();
		
		#ifdef asdihasdf
		SCR_BaseGameMode gamemode = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		gamemode.EndGameMode(SCR_GameModeEndData.CreateSimple(
			EGameOverTypes.DEATHMATCH_VICTORY_SCORE, 
			1,
			-1));
		#endif

	}

	override void EOnFrame(IEntity owner, float timeSlice)
	{
		timeLeft -= timeSlice;
		if (timeLeft > 0)
			return;
		Print("Hit the time!");
		timeLeft = m_iCycleDuration;
		HandlePlayerInterval();
	}

	//------------------------------------------------------------------------------------------------
	void RUGG_WeaponChangerEntity(IEntitySource src, IEntity parent)
	{
		SetFlags(EntityFlags.ACTIVE | EntityFlags.NO_LINK, false);
		SetEventMask( EntityEvent.FRAME);
	}
}