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

#endif // GUARD_SHINY_ROLL_H