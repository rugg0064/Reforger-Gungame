# Reforger-Gungame

Gungame gamemode mod for ArmA Reforger.

Gun Game is a classic shooter game mode where you shoot your way through a series of weapons. Each kill progresses to the next weapon until someone scores a kill with the final weapon, then they are the winner and the game is over.

## How to set up

As this addon is only the gamemode files, there is no map or mission included. You will need to use a separate addon which depends on this one and provides a configured map and mission. An example of this is [https://github.com/rugg0064/Reforger-Gungame-Minimal-Implementation](https://github.com/rugg0064/Reforger-Gungame-Minimal-Implementation).

## Making a gungame implementation

You can make your own Gun Game implementation using this base addon by creating a new addon that depends on this one. This new addon will need to provide or depend on a map that has the following entities:

- GameMode_GunGame.et, you can override or duplicate it to configure the weapon list within this prefab.
- Spawn points, use SpawnPoint_GunGame.et to avoid future incompatibilities
- LoadoutManager_GunGame.et
- FactionManager_FFA.et
- (Optional) an ArenaManager.et to ensure players don't leave the play area

To turn this into a scenario that can be played, see [example](https://github.com/rugg0064/Reforger-Gungame-Minimal-Implementation/blob/main/Missions/GungameMinimal.conf).

# Issues

If you encounter any issues or have suggestions for improvements, please open an issue on the Issues page. Provide as much detail as possible, including steps to reproduce the issue.

# License

This mod is open-source and distributed under the MIT License.
