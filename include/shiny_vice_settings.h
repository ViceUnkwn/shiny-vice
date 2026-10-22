#ifndef GUARD_SHINY_VICE_SETTINGS_H
#define GUARD_SHINY_VICE_SETTINGS_H

#include "gba/types.h"

// Shiny Vice game settings. These are chosen once, on the New Game settings screen, and are fixed
// for the whole save (there is no in-game way to change them). The struct lives in SaveBlock3.

#define SV_SETTINGS_VERSION 1

// This chooses the starter trio offered by Professor Birch; it never changes the game region.
enum SvStarterRegion
{
    SV_REGION_HOENN,
    SV_REGION_KANTO,
    SV_REGION_JOHTO,
    SV_REGION_SINNOH,
    SV_REGION_UNOVA,
    SV_REGION_KALOS,
    SV_REGION_ALOLA,
    SV_REGION_GALAR,
    SV_REGION_PALDEA,
    SV_REGION_COUNT,
};

enum SvDifficulty
{
    SV_DIFFICULTY_NORMAL, // default; already a hard game
    SV_DIFFICULTY_HARD,   // challenge-run difficulty
    SV_DIFFICULTY_COUNT,
};

enum SvLevelCap
{
    SV_LEVEL_CAP_OFF,
    SV_LEVEL_CAP_SOFT, // heavily reduced EXP past the cap
    SV_LEVEL_CAP_HARD, // no EXP past the cap
    SV_LEVEL_CAP_COUNT,
};

struct ShinyViceSettings
{
    u8 version;       // SV_SETTINGS_VERSION; 0 means the save predates the settings (use defaults)
    u8 starterRegion; // enum SvStarterRegion; which trio Birch offers
    u8 difficulty;    // enum SvDifficulty
    u8 levelCap;      // enum SvLevelCap
    u8 grindMode:1;   // minimal grind: stats computed with 31 IVs, no EV gain (stored values untouched)
    u8 nuzlocke:1;    // stored, not enforced yet
    u8 randomizer:1;  // stored, not enforced yet
    u8 unused:5;
    u32 randomizerSeed; // reserved for the randomizer; unused until it exists
};

void ShinyViceSettings_SetDefaults(struct ShinyViceSettings *settings);

// The settings the current save is using. Saves that predate the settings return the defaults.
const struct ShinyViceSettings *ShinyViceSettings_Get(void);

// New Game flow: the settings screen stages its choices here. They are copied into the save by
// ShinyViceSettings_CommitPending, which NewGameInitData calls after it clears SaveBlock3.
// If nothing was staged (for example the Quickstart path), the defaults are committed.
void ShinyViceSettings_StagePending(const struct ShinyViceSettings *settings);
void ShinyViceSettings_CommitPending(void);

#endif // GUARD_SHINY_VICE_SETTINGS_H
