#ifndef GUARD_SHINY_QUALITY_H
#define GUARD_SHINY_QUALITY_H

// Shiny Vice: what makes a shiny a *good* Pokemon (IVs, nature, hidden ability), and the shiny
// roll threshold the debug menu can change at runtime. Tunables and the pure logic live in
// shiny_roll.h / shiny_roll.c.

// Roll threshold (out of 65536) used when deciding whether a newly created Pokemon is shiny.
// Defaults to SHINY_ODDS; the debug menu can override it. It never affects Pokemon that already
// exist: their shininess is stored with them, not recomputed from this value.
u32 ShinyVice_GetRollThreshold(void);
u32 ShinyVice_GetRollDenominator(void); // the same setting as "1 in N"
void ShinyVice_SetRollDenominator(u32 denominator);

// Possibly swaps a shiny's personality for one with a nature that suits the species. Gender and
// Unown letter are kept. Call it before the personality is stored on the mon.
u32 ShinyVice_ImproveShinyPersonality(enum Species species, u32 personality);

// Forces ShinyVice's perfect IVs and best-of-N rolls on the IVs already set on the mon.
// Only ever raises an IV, so calling it again cannot hurt, but it will keep raising them.
void ShinyVice_ApplyShinyIvBonus(struct BoxPokemon *boxMon);

// Re-picks the ability slot: normal slot from personality, or the hidden ability on a lucky roll.
void ShinyVice_RollShinyAbility(struct BoxPokemon *boxMon);

#endif // GUARD_SHINY_QUALITY_H
