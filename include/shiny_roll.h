#ifndef GUARD_SHINY_ROLL_H
#define GUARD_SHINY_ROLL_H

// Shiny Vice roll budget. Plain C types only so the host-side test can build it with gcc.

// Total rolls per Pokemon, including the 1 base roll (8 total = 8/4096 = 1/512 at SHINY_ODDS 16).
#define SHINY_VICE_MAX_TOTAL_ROLLS   8

// Placeholder chain curve: +1 roll per 25 links, up to +3.
#define SHINY_VICE_CHAIN_STEP        25
#define SHINY_VICE_CHAIN_MAX_BONUS   3

// Extra rolls from each source, before the cap is applied.
struct ShinyRollSources
{
    unsigned int charm;
    unsigned int chain;
    unsigned int lure;
    unsigned int fishing;
};

unsigned int ShinyVice_ChainBonus(unsigned int chainCount);
unsigned int ShinyVice_ComputeExtraRolls(const struct ShinyRollSources *sources);

// ---------------------------------------------------------------------------------------------
// Shiny quality: every shiny gets better-than-normal IVs, a good nature and a shot at its hidden
// ability. All tunables live here so balance changes are one-line edits.
// ---------------------------------------------------------------------------------------------

// IVs: this many (randomly chosen) stats are forced to 31.
#define SHINY_VICE_SHINY_PERFECT_IVS        2
// IVs: every other stat is the best of this many ordinary 0-31 rolls (1 = no bonus; 2 averages about 21).
#define SHINY_VICE_SHINY_IV_ROLLS           2
// Percent chance that a shiny's nature is replaced by one that suits the species (see GoodNatureMask).
#define SHINY_VICE_GOOD_NATURE_CHANCE       60
// Percent chance that a shiny gets its hidden ability (only for species that have one).
#define SHINY_VICE_HIDDEN_ABILITY_CHANCE    35
// A species counts as a mixed attacker when its base Atk and Sp. Atk are within this many points.
#define SHINY_VICE_MIXED_ATTACKER_MARGIN    15

#define SHINY_VICE_NUM_STATS                6

// Picks `count` distinct stats out of 6 using `random`. Returns a bitmask, bit 0 = HP, bit 1 = Atk,
// bit 2 = Def, bit 3 = Speed, bit 4 = Sp. Atk, bit 5 = Sp. Def (the same order as MON_DATA_HP_IV + n).
unsigned int ShinyVice_PerfectIvMask(unsigned int count, unsigned int random);

// Returns a bitmask over the 25 natures (bit n = nature n) that are "good" for a species with these
// base stats: raise its main attacking stat or Speed while lowering the attack it does not use.
// Mixed attackers raise Atk, Sp. Atk or Speed while lowering a defensive stat instead.
unsigned int ShinyVice_GoodNatureMask(unsigned int baseAttack, unsigned int baseSpAttack);

// Turns a "1 in N" shiny rate into the SHINY_ODDS-style threshold (out of 65536). N = 4096 gives 16.
unsigned int ShinyVice_ThresholdFromDenominator(unsigned int denominator);

#endif // GUARD_SHINY_ROLL_H