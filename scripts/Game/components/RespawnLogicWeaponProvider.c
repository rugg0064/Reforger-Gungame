[BaseContainerProps(category: "Respawn")]
class RespawnWeaponProviderLogic : SCR_AutoSpawnLogic
{
	override void OnPlayerKilled_S (int playerId, IEntity playerEntity, IEntity killerEntity, notnull Instigator killer)
	{
		Print("OnPlayerKilled_S on RespawnWeaponProviderComponent.c");
		Print("Kill results = " + playerId + " | " + playerEntity.GetID() + " | " + killerEntity.GetID());
		GunGameMode gameModeInstance = GunGameMode.gunGameMode;
		Print(gameModeInstance.GetPlayerScoreMapString());
		
		super.OnPlayerKilled_S(playerId, playerEntity, killerEntity, killer);
		// Killer was not an entity, do nothing
		if(!ChimeraCharacter.Cast(killerEntity))
		{
			return;
		}
		int killerId = killer.GetInstigatorPlayerID();
		bool suicide = playerId == killerId;
		if(suicide)
		{
			gameModeInstance.playerScoreMap.Set(playerId, gameModeInstance.clampScore(gameModeInstance.playerScoreMap[playerId] - 1));
			// Their weapon will be set on respawn
		}
		else
		{
			if(gameModeInstance.playerScoreMap[killerId] == gameModeInstance.PlayerLoadouts.Count() - 1)
			{
				gameModeInstance.handleWin(killerId);
			}
			gameModeInstance.playerScoreMap.Set(killerId, gameModeInstance.clampScore(gameModeInstance.playerScoreMap[killerId] + 1));
			GunGameUtils.SetPlayerWeapon(killerEntity, killerId);
		}
	}
	
	override void OnPlayerSpawned_S(int playerId, IEntity entity)
	{
		super.OnPlayerSpawned_S(playerId, entity);
		Print("Spawn was finalized!");
		Print(entity);
		
		GunGameUtils.SetPlayerWeaponSpawn(ChimeraCharacter.Cast(entity), playerId);
	}
}