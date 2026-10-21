#ifndef GUARD_SHINY_VICE_FX_H
#define GUARD_SHINY_VICE_FX_H

// Shiny Vice persistent shiny visuals: a gold star icon (supplied artwork, reduced to 11x12) and periodic thin twinkles in
// four shapes (small, medium, large, 8-point burst). Twinkle colour is derived from the
// Pokémon's own (shiny) sprite palette.
// Uses its own RNG so the game/battle RNG sequence is never advanced.

// 11x12 gold star icon (supplied artwork, reduced) centred on (x, y). While visible it also emits twinkles at random
// points inside the box centred on (areaX, areaY) with half-extents halfW/halfH.
// Twinkles are tinted from the palette of the sprite whose id is stored at *monSpriteIdPtr
// (re-read on every twinkle, so it follows the mon when the screen changes Pokémon).
// monSpriteIdPtr may be NULL (gold twinkles); otherwise it must stay valid for as long as
// the star exists. Hide the star with sprite->invisible (no twinkles while hidden).
u8 ShinyViceFx_CreateEmitterStar(s16 x, s16 y, s16 areaX, s16 areaY, u8 halfW, u8 halfH,
                                 u8 oamPriority, const u8 *monSpriteIdPtr);

// Battle: keeps twinkling over a shiny battler's sprite. Safe to call repeatedly.
void ShinyViceFx_StartBattleSparkle(u32 battler);
void ShinyViceFx_StopBattleSparkle(void);

#endif // GUARD_SHINY_VICE_FX_H
