#include "global.h"
#include "shiny_vice_settings.h"

// Zero-initialized on purpose: this project's linker script discards non-zero initialized statics.
EWRAM_DATA static struct ShinyViceSettings sPendingSettings = {0};
EWRAM_DATA static struct ShinyViceSettings sDefaultSettings = {0};
EWRAM_DATA static bool8 sHasPendingSettings = FALSE;

void ShinyViceSettings_SetDefaults(struct ShinyViceSettings *settings)
{
    memset(settings, 0, sizeof(*settings));
    settings->version = SV_SETTINGS_VERSION;
    settings->starterRegion = SV_REGION_HOENN;
    settings->difficulty = SV_DIFFICULTY_NORMAL;
    settings->levelCap = SV_LEVEL_CAP_SOFT;
}

const struct ShinyViceSettings *ShinyViceSettings_Get(void)
{
    // A save from before the settings existed has zeroed SaveBlock3 here, so its version is 0.
    if (gSaveBlock3Ptr->svSettings.version != SV_SETTINGS_VERSION
     || gSaveBlock3Ptr->svSettings.starterRegion >= SV_REGION_COUNT
     || gSaveBlock3Ptr->svSettings.difficulty >= SV_DIFFICULTY_COUNT
     || gSaveBlock3Ptr->svSettings.levelCap >= SV_LEVEL_CAP_COUNT)
    {
        ShinyViceSettings_SetDefaults(&sDefaultSettings);
        return &sDefaultSettings;
    }
    return &gSaveBlock3Ptr->svSettings;
}

void ShinyViceSettings_StagePending(const struct ShinyViceSettings *settings)
{
    sPendingSettings = *settings;
    sPendingSettings.version = SV_SETTINGS_VERSION;
    if (sPendingSettings.starterRegion >= SV_REGION_COUNT)
        sPendingSettings.starterRegion = SV_REGION_HOENN;
    if (sPendingSettings.levelCap >= SV_LEVEL_CAP_COUNT)
        sPendingSettings.levelCap = SV_LEVEL_CAP_SOFT;
    sHasPendingSettings = TRUE;
}

void ShinyViceSettings_CommitPending(void)
{
    if (!sHasPendingSettings)
        ShinyViceSettings_SetDefaults(&sPendingSettings);

    gSaveBlock3Ptr->svSettings = sPendingSettings;
    sHasPendingSettings = FALSE; // the next New Game starts from a clean slate
}
