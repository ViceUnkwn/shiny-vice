#include "shiny_roll.h"

unsigned int ShinyVice_ChainBonus(unsigned int chainCount)
{
    unsigned int bonus = chainCount / SHINY_VICE_CHAIN_STEP;

    if (bonus > SHINY_VICE_CHAIN_MAX_BONUS)
        bonus = SHINY_VICE_CHAIN_MAX_BONUS;
    return bonus;
}

// Returns the number of EXTRA rolls (total rolls minus the 1 base roll), clamped to the global cap.
unsigned int ShinyVice_ComputeExtraRolls(const struct ShinyRollSources *sources)
{
    unsigned int extra = sources->charm + sources->chain + sources->lure + sources->fishing;
    unsigned int maxExtra = SHINY_VICE_MAX_TOTAL_ROLLS - 1;

    return extra > maxExtra ? maxExtra : extra;
}