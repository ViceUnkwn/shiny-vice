#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "pokemon.h"
#include "shiny_vice_settings.h"


u32 GetCurrentLevelCap(void)
{
    static const u32 sShinyViceLevelCapFlagMap[][2] =
    {
        {FLAG_IS_CHAMPION, 78},
        {FLAG_BADGE08_GET, 58},
        {FLAG_BADGE07_GET, 48},
        {FLAG_BADGE06_GET, 42},
        {FLAG_BADGE05_GET, 33},
        {FLAG_BADGE04_GET, 31},
        {FLAG_BADGE03_GET, 29},
        {FLAG_BADGE02_GET, 24},
        // The Slateport museum story milestone keeps the main path viable if
        // the player skips Brawly, whose badge is not required to leave Dewford.
        {FLAG_DELIVERED_DEVON_GOODS, 24},
        {FLAG_BADGE01_GET, 19},
    };

    u32 i;

    if (ShinyViceSettings_Get()->levelCap == SV_LEVEL_CAP_OFF)
        return MAX_LEVEL;

    for (i = 0; i < ARRAY_COUNT(sShinyViceLevelCapFlagMap); i++)
    {
        if (FlagGet(sShinyViceLevelCapFlagMap[i][0]))
            return sShinyViceLevelCapFlagMap[i][1];
    }

    // The first cap applies until the first Gym Badge is earned.
    if (ShinyViceSettings_Get()->levelCap == SV_LEVEL_CAP_SOFT
     || ShinyViceSettings_Get()->levelCap == SV_LEVEL_CAP_HARD)
        return 15;

    return MAX_LEVEL;
}

bool32 IsHardLevelCapEnabled(void)
{
    return ShinyViceSettings_Get()->levelCap == SV_LEVEL_CAP_HARD;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();
    u8 capMode = ShinyViceSettings_Get()->levelCap;

    if (capMode == SV_LEVEL_CAP_OFF)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
        }
        else
        {
            return expValue;
        }
    }
    else if (capMode == SV_LEVEL_CAP_HARD)
    {
        return 0;
    }
    else if (capMode == SV_LEVEL_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetCurrentEVCap(void)
{
    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, MAX_TOTAL_EVS *  1 / 17},
        {FLAG_BADGE02_GET, MAX_TOTAL_EVS *  3 / 17},
        {FLAG_BADGE03_GET, MAX_TOTAL_EVS *  5 / 17},
        {FLAG_BADGE04_GET, MAX_TOTAL_EVS *  7 / 17},
        {FLAG_BADGE05_GET, MAX_TOTAL_EVS *  9 / 17},
        {FLAG_BADGE06_GET, MAX_TOTAL_EVS * 11 / 17},
        {FLAG_BADGE07_GET, MAX_TOTAL_EVS * 13 / 17},
        {FLAG_BADGE08_GET, MAX_TOTAL_EVS * 15 / 17},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}
