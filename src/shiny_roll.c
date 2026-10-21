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

unsigned int ShinyVice_PerfectIvMask(unsigned int count, unsigned int random)
{
    unsigned int mask = 0;
    unsigned int i, remaining, pick, stat;

    if (count > SHINY_VICE_NUM_STATS)
        count = SHINY_VICE_NUM_STATS;

    for (i = 0; i < count; i++)
    {
        remaining = SHINY_VICE_NUM_STATS - i;
        pick = random % remaining;
        random /= remaining;

        // Walk to the pick-th stat that has not been chosen yet.
        for (stat = 0; stat < SHINY_VICE_NUM_STATS; stat++)
        {
            if (mask & (1u << stat))
                continue;
            if (pick == 0)
            {
                mask |= 1u << stat;
                break;
            }
            pick--;
        }
    }
    return mask;
}

// Natures are laid out as nature = up * 5 + down, with both indices in the order Atk, Def, Speed, SpAtk, SpDef.
#define NATURE_STAT_ATK     0
#define NATURE_STAT_DEF     1
#define NATURE_STAT_SPEED   2
#define NATURE_STAT_SPATK   3
#define NATURE_STAT_SPDEF   4

#define NATURE_BIT(up, down) (1u << ((up) * 5 + (down)))

unsigned int ShinyVice_GoodNatureMask(unsigned int baseAttack, unsigned int baseSpAttack)
{
    if (baseAttack >= baseSpAttack + SHINY_VICE_MIXED_ATTACKER_MARGIN)
    {
        // Physical: Adamant (+Atk -SpAtk) and Jolly (+Speed -SpAtk).
        return NATURE_BIT(NATURE_STAT_ATK, NATURE_STAT_SPATK) | NATURE_BIT(NATURE_STAT_SPEED, NATURE_STAT_SPATK);
    }
    if (baseSpAttack >= baseAttack + SHINY_VICE_MIXED_ATTACKER_MARGIN)
    {
        // Special: Modest (+SpAtk -Atk) and Timid (+Speed -Atk).
        return NATURE_BIT(NATURE_STAT_SPATK, NATURE_STAT_ATK) | NATURE_BIT(NATURE_STAT_SPEED, NATURE_STAT_ATK);
    }
    // Mixed: raise Atk, SpAtk or Speed, lower Def or SpDef.
    return NATURE_BIT(NATURE_STAT_ATK, NATURE_STAT_DEF)   | NATURE_BIT(NATURE_STAT_ATK, NATURE_STAT_SPDEF)
         | NATURE_BIT(NATURE_STAT_SPATK, NATURE_STAT_DEF) | NATURE_BIT(NATURE_STAT_SPATK, NATURE_STAT_SPDEF)
         | NATURE_BIT(NATURE_STAT_SPEED, NATURE_STAT_DEF) | NATURE_BIT(NATURE_STAT_SPEED, NATURE_STAT_SPDEF);
}

unsigned int ShinyVice_ThresholdFromDenominator(unsigned int denominator)
{
    unsigned int threshold;

    if (denominator < 1)
        denominator = 1;
    threshold = 65536u / denominator;
    return threshold < 1 ? 1 : threshold;
}
