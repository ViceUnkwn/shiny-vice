#ifndef GUARD_NEW_GAME_SETTINGS_SCREEN_H
#define GUARD_NEW_GAME_SETTINGS_SCREEN_H

// Shiny Vice: the screen shown after choosing NEW GAME on the main menu. It lets the player pick the
// starter trio Birch offers. Difficulty is fixed to Normal while other profiles are unavailable;
// level caps, minimal grinding, Nuzlocke, and randomizer are shown as unavailable. The starter choice
// is staged with ShinyViceSettings_StagePending and is fixed for the save.
//
// A on the START GAME row confirms and continues into the Birch speech; B returns to the main menu.
void CB2_InitNewGameSettings(void);

#endif // GUARD_NEW_GAME_SETTINGS_SCREEN_H
