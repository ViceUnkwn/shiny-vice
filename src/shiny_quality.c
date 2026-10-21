#include "global.h"
#include "pokemon.h"
#include "random.h"
#include "shiny_quality.h"
#include "shiny_roll.h"
#include "constants/abilities.h"

// 0 means "use SHINY_ODDS". EWRAM is zeroed at boot, so no initializer is needed (or honoured).
EWRAM_DATA static u32 sRollThreshold = 0;

u32 ShinyVice_GetRollThreshold(void)
{
    return sRollThreshold != 0 ? sRollThreshold : SHINY_ODDS;
}

u32 ShinyVice_GetRollDenominator(void)
{
    return 65536 / ShinyVice_GetRollThreshold();
}

void ShinyVice_SetRollDenominator(u32 denominator)
{
    sRollThreshold = ShinyVice_ThresholdFromDenominator(denominator);
}

u32 ShinyVice_ImproveShinyPersonality(enum Species species, u32 personality)
{
    u32 goodMask, count, pick, nature, i;
    u8 gender, letter;

    if (Random() % 100 >= SHINY_VICE_GOOD_NATURE_CHANCE)
        return personality;

    goodMask = ShinyVice_GoodNatureMask(GetSpeciesBaseAttack(species), GetSpeciesBaseSpAttack(species));
    if (goodMask & (1u << GetNatureFromPersonality(personality)))
        return personality; // already a good one

    count = 0;
    for (i = 0; i < NUM_NATURES; i++)
        count += (goodMask >> i) & 1;
    if (count == 0)
        return personality;

    pick = Random() % count;
    nature = 0;
    for (i = 0; i < NUM_NATURES; i++)
    {
        if (!((goodMask >> i) & 1))
            continue;
        if (pick == 0)
        {
            nature = i;
            break;
        }
        pick--;
    }

    gender = GetGenderFromSpeciesAndPersonality(species, personality);
    letter = (species == SPECIES_UNOWN) ? GET_UNOWN_LETTER(personality) + 1 : RANDOM_UNOWN_LETTER;
    return GetMonPersonality(species, gender, nature, letter);
}

void ShinyVice_ApplyShinyIvBonus(struct BoxPokemon *boxMon)
{
    u32 perfectMask = ShinyVice_PerfectIvMask(SHINY_VICE_SHINY_PERFECT_IVS, Random32());
    u32 stat, roll, iv, extra;

    for (stat = 0; stat < NUM_STATS; stat++)
    {
        iv = GetBoxMonData(boxMon, MON_DATA_HP_IV + stat);
        if (perfectMask & (1u << stat))
        {
            iv = MAX_PER_STAT_IVS;
        }
        else
        {
            for (roll = 1; roll < SHINY_VICE_SHINY_IV_ROLLS; roll++)
            {
                extra = Random() & MAX_IV_MASK;
                if (extra > iv)
                    iv = extra;
            }
        }
        SetBoxMonData(boxMon, MON_DATA_HP_IV + stat, &iv);
    }
}

void ShinyVice_RollShinyAbility(struct BoxPokemon *boxMon)
{
    enum Species species = GetBoxMonData(boxMon, MON_DATA_SPECIES);
    u32 slot = GetBoxMonData(boxMon, MON_DATA_PERSONALITY) & 1;

    if (GetSpeciesAbility(species, 1) == ABILITY_NONE)
        slot = 0;
    if (GetSpeciesAbility(species, 2) != ABILITY_NONE && Random() % 100 < SHINY_VICE_HIDDEN_ABILITY_CHANCE)
        slot = 2;
    SetBoxMonData(boxMon, MON_DATA_ABILITY_NUM, &slot);
}
