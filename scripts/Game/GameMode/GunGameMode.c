// The instance of GunGameMode should closely reflect GameMode_Deathmatch_Automatic
[EntityEditorProps(category: "Gun Game", description: "Game Mode Manager", color: "0 255 0 0")]
class GunGameModeClass: SCR_BaseGameModeClass
{
};

/// @ingroup GameMode
class GunGameMode : SCR_BaseGameMode
{
	// Singleton
	static GunGameMode gunGameMode;
	
	[Attribute("", UIWidgets.Object, category: "Weapon List")]
	ref array<ref GunGameWeaponSelection> PlayerLoadouts;
	
	ref map<int, int> playerScoreMap = new map<int, int>();
	
	void GunGameMode(IEntitySource src,IEntity parent )
	{
		if(gunGameMode)
		{
			Print("Only one GameMode can exist at a time");
			delete this;
			return;
		}
		gunGameMode = this;
	}
	
	int clampScore(int score)
	{
		if(score < 0)
		{
			return 0;
		}
		if(score >= PlayerLoadouts.Count())
		{
			return PlayerLoadouts.Count()-1;
		}
		return score;
	}
	
	GunGameWeaponSelection getWeaponForPlayer(int playerId)
	{
		return PlayerLoadouts[playerScoreMap[playerId]];
	}
	
	override void OnGameStart()
	{
		
	}
	
	override void OnPlayerConnected(int playerId)
	{
		playerScoreMap.Set(playerId, 0);
	}
	
	private void handleWin(int winnerId)
	{
		bool didIWin = GetGame().GetPlayerController().GetPlayerId() == winnerId;
		EGameOverTypes reason;
		if(didIWin)
		{
			reason = EGameOverTypes.DEATHMATCH_VICTORY_SCORE;
		}
		else
		{
			reason = EGameOverTypes.ENDREASON_SCORELIMIT;
		}
		
		EndGameMode(SCR_GameModeEndData.CreateSimple(
			reason: EGameOverTypes.ENDREASON_SCORELIMIT,
			winnerId: winnerId
		));
		//GameStateTransitions.RequestScenarioChangeTransition()
	}
	
	override void OnGameEnd()
	{
		Print("The game is ending!");
	}
	
	protected override void OnPlayerKilled(int playerId, IEntity playerEntity, IEntity killerEntity, notnull Instigator killer)
	{
		super.OnPlayerKilled(playerId, playerEntity, killerEntity, killer);
		// Killer was not an entity, do nothing
		if(!ChimeraCharacter.Cast(killerEntity))
		{
			return;
		}
		ChimeraCharacter killerCharacter = ChimeraCharacter.Cast(killerEntity);
		if(killerCharacter.FindComponent(SCR_AchievementsHandler) && SCR_AchievementsHandler.Cast(killerCharacter.FindComponent(SCR_AchievementsHandler)))
		{
			SCR_AchievementsHandler achievementHandler = SCR_AchievementsHandler.Cast(killerCharacter.FindComponent(SCR_AchievementsHandler));
			achievementHandler.UnlockAchievement(AchievementId.ONE_TO_WATCH);
		}

		
		
		int killerId = killer.GetInstigatorPlayerID();
		bool suicide = playerId == killerId;
		if(suicide)
		{
			playerScoreMap.Set(playerId, clampScore(playerScoreMap[playerId] - 1));
		}
		else
		{
			if(playerScoreMap[killerId] == PlayerLoadouts.Count() - 1)
			{
				handleWin(killerId);
			}
			playerScoreMap.Set(killerId, clampScore(playerScoreMap[killerId] + 1));
			GunGameUtils.SetPlayerWeapon(ChimeraCharacter.Cast(killerEntity), killerId);
		}
	}
}