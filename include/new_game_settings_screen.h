#ifndef GUARD_NEW_GAME_SETTINGS_SCREEN_H
#define GUARD_NEW_GAME_SETTINGS_SCREEN_H

// Shiny Vice: the screen shown after choosing NEW GAME on the main menu. It lets the player pick the
// starter trio Birch offers and the save-level Off/Soft/Hard cap rule. Difficulty is fixed to Normal
// while other profiles are unavailable; minimal grinding, Nuzlocke, and randomizer remain unavailable.
// These choices are staged with ShinyViceSettings_StagePending and are fixed for the save.
//
// A on the START GAME row confirms and continues into the Birch speech; B returns to the main menu.
void CB2_InitNewGameSettings(void);

#endif // GUARD_NEW_GAME_SETTINGS_SCREEN_H
