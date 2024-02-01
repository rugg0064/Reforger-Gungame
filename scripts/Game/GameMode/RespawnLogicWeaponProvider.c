[BaseContainerProps(category: "Respawn")]
class RespawnWeaponProviderLogic : SCR_AutoSpawnLogic
{
	override void OnPlayerKilled_S (int playerId, IEntity playerEntity, IEntity killerEntity, notnull Instigator killer)
	{
		GunGameMode gameModeInstance = GunGameMode.gunGameMode;
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
			// Suicide reduces score by 1
			gameModeInstance.playerScoreMap.Set(playerId, gameModeInstance.clampScore(gameModeInstance.playerScoreMap[playerId] - 1));
		}
		else
		{
			// Win condition
			if(gameModeInstance.playerScoreMap[killerId] == gameModeInstance.PlayerLoadouts.Count() - 1)
			{
				gameModeInstance.handleWin(killerId);
			}
			// Increase score, set new weapon
			gameModeInstance.playerScoreMap.Set(killerId, gameModeInstance.clampScore(gameModeInstance.playerScoreMap[killerId] + 1));
			GunGameUtils.SetPlayerWeapon(killerEntity, killerId);
		}
	}
	
	override void OnPlayerSpawned_S(int playerId, IEntity entity)
	{
		super.OnPlayerSpawned_S(playerId, entity);
		GunGameUtils.SetPlayerWeapon(ChimeraCharacter.Cast(entity), playerId);
	}
}