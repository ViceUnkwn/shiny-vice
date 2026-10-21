#ifndef GUARD_SHINY_VICE_FX_H
#define GUARD_SHINY_VICE_FX_H

// Shiny Vice persistent shiny visuals: a gold star icon and periodic twinkles.
// Uses its own RNG so the game/battle RNG sequence is never advanced.

// One-shot twinkle at a screen position. Destroys itself when the animation ends.
void ShinyViceFx_SpawnSparkle(s16 x, s16 y, u8 oamPriority, u8 subpriority);

// Gold star icon at (x, y). While visible it also emits twinkles at random points
// inside the box centred on (areaX, areaY) with half-extents halfW/halfH.
// Hide it with sprite->invisible (no twinkles are emitted while hidden).
u8 ShinyViceFx_CreateEmitterStar(s16 x, s16 y, s16 areaX, s16 areaY, u8 halfW, u8 halfH, u8 oamPriority);

// Battle: keeps twinkling over a shiny battler's sprite. Safe to call repeatedly.
void ShinyViceFx_StartBattleSparkle(u32 battler);

#endif // GUARD_SHINY_VICE_FX_H
