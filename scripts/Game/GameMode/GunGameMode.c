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
	
	ref map<int, int> playerScoreMap;
	
	string GetPlayerScoreMapString()
	{
		string returnString = "";
		foreach(int i, int j: playerScoreMap)
		{
			returnString += "" + i + " - " + j + "\n";
		}
		return returnString;
	}
	
	void GunGameMode(IEntitySource src, IEntity parent )
	{
		playerScoreMap = new map<int, int>();
		if(gunGameMode)
		{
			return;
		}
		gunGameMode = this;
		StartGameMode();
	}
	
	int clampScore(int score)
	{
		if(score < 0)
		{
			return 0;
		}
		if(score >= PlayerLoadouts.Count())
		{
			return PlayerLoadouts.Count() - 1;
		}
		return score;
	}
	
	GunGameWeaponSelection getWeaponForPlayer(int playerId)
	{
		return PlayerLoadouts[playerScoreMap[playerId]];
	}
	
	override void OnGameStart()
	{
		super.OnGameStart();
		// Uncomment to test game end scenario
		//GetGame().GetCallqueue().CallLater(handleWin, 5000, false, 1);
	}
	
	override void OnPlayerConnected(int playerId)
	{
		super.OnPlayerConnected(playerId);
		playerScoreMap.Set(playerId, 0);
	}

	// TODO: BUG: This doesn't work for peertool clients, only hosting editor client.
	void handleWin(int winnerId)
	{
        EndGameMode(SCR_GameModeEndData.CreateSimple(
            reason: EGameOverTypes.ENDREASON_SCORELIMIT,
            winnerId: winnerId
        ));
		// Move to different scenario?
		//GameStateTransitions.RequestScenarioChangeTransition("{2E8461FFAB4BCCD5}Worlds/Minimal_World/RUGG_Minimal_World.ent", "GungameImplementationMinimal")
	}
}