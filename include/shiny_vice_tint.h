#ifndef GUARD_SHINY_VICE_TINT_H
#define GUARD_SHINY_VICE_TINT_H

// Shiny Vice sparkle tinting: pure RGB555 colour math, no game dependencies so it can be
// unit-tested on the host (see test_host/shiny_vice_tint_test.c).
// The includer must already have u16/u32 defined (global.h in-game).
//
// Palette contract with graphics/shiny_vice/shiny_fx.png:
//   index 0      transparent
//   index 1..4   tintable ramp: drop shadow, tip, base, light
//   index 5      white core (never tinted)
//   index 6..10  gold star icon (never tinted)
// (dev_scripts/gen_shiny_fx.py generates the sheet that follows this contract)

#define SVT_R(c)        ((c) & 0x1F)
#define SVT_G(c)        (((c) >> 5) & 0x1F)
#define SVT_B(c)        (((c) >> 10) & 0x1F)
#define SVT_RGB(r, g, b) ((u16)((r) | ((g) << 5) | ((b) << 10)))

#define SVT_DEFAULT_TINT    SVT_RGB(31, 25, 6) // gold: used when a palette has no vivid colour
#define SVT_MIN_BRIGHTNESS  10                 // ignore outline-dark colours
#define SVT_MIN_CHROMA      5                  // ignore greys, whites and near-greys

// Most vivid colour in a 16-entry sprite palette (index 0 is skipped), normalised so its
// brightest channel is 31. Returns SVT_DEFAULT_TINT if nothing qualifies.
static inline u16 ShinyViceTint_Pick(const u16 *pal16)
{
    u32 i;
    u32 bestScore = 0;
    u16 best = 0;

    for (i = 1; i < 16; i++)
    {
        u32 r = SVT_R(pal16[i]);
        u32 g = SVT_G(pal16[i]);
        u32 b = SVT_B(pal16[i]);
        u32 mx = r;
        u32 mn = r;
        u32 chroma, score;

        if (g > mx) mx = g;
        if (b > mx) mx = b;
        if (g < mn) mn = g;
        if (b < mn) mn = b;
        chroma = mx - mn;
        if (mx < SVT_MIN_BRIGHTNESS || chroma < SVT_MIN_CHROMA)
            continue;

        score = chroma * 4 + mx; // favour saturation, break ties on brightness
        if (score > bestScore)
        {
            bestScore = score;
            // Normalise to full brightness so every tint reads clearly.
            best = SVT_RGB((r * 31 + mx / 2) / mx, (g * 31 + mx / 2) / mx, (b * 31 + mx / 2) / mx);
        }
    }
    return bestScore != 0 ? best : SVT_DEFAULT_TINT;
}

// Each channel multiplied by num/den (rounded).
static inline u16 ShinyViceTint_Scale(u16 c, u32 num, u32 den)
{
    return SVT_RGB((SVT_R(c) * num + den / 2) / den,
                   (SVT_G(c) * num + den / 2) / den,
                   (SVT_B(c) * num + den / 2) / den);
}

// Each channel moved num/den of the way towards white.
static inline u16 ShinyViceTint_Lighten(u16 c, u32 num, u32 den)
{
    return SVT_RGB(SVT_R(c) + (31 - SVT_R(c)) * num / den,
                   SVT_G(c) + (31 - SVT_G(c)) * num / den,
                   SVT_B(c) + (31 - SVT_B(c)) * num / den);
}

// Overwrites the tintable ramp (indices 1..4) of a 16-entry sprite palette.
static inline void ShinyViceTint_Apply(u16 *pal16, u16 tint)
{
    pal16[1] = ShinyViceTint_Scale(tint, 4, 10); // outline
    pal16[2] = ShinyViceTint_Scale(tint, 7, 10); // mid
    pal16[3] = tint;                             // base
    pal16[4] = ShinyViceTint_Lighten(tint, 1, 2); // light
}

// Second sparkle colour: the most vivid palette colour whose hue is clearly different from
// `primary` (e.g. a yellow body with an orange flame -> orange). Returns 0 if there is none.
#define SVT_MIN_HUE_GAP 10 // summed per-channel distance, both colours normalised to peak 31

static inline u16 ShinyViceTint_PickSecondary(const u16 *pal16, u16 primary)
{
    u32 i;
    u32 bestScore = 0;
    u16 best = 0;

    for (i = 1; i < 16; i++)
    {
        u32 r = SVT_R(pal16[i]);
        u32 g = SVT_G(pal16[i]);
        u32 b = SVT_B(pal16[i]);
        u32 mx = r;
        u32 mn = r;
        u32 chroma, score, nr, ng, nb, gap;

        if (g > mx) mx = g;
        if (b > mx) mx = b;
        if (g < mn) mn = g;
        if (b < mn) mn = b;
        chroma = mx - mn;
        if (mx < SVT_MIN_BRIGHTNESS || chroma < SVT_MIN_CHROMA)
            continue;
        nr = (r * 31 + mx / 2) / mx;
        ng = (g * 31 + mx / 2) / mx;
        nb = (b * 31 + mx / 2) / mx;
        gap = (nr > SVT_R(primary) ? nr - SVT_R(primary) : SVT_R(primary) - nr)
            + (ng > SVT_G(primary) ? ng - SVT_G(primary) : SVT_G(primary) - ng)
            + (nb > SVT_B(primary) ? nb - SVT_B(primary) : SVT_B(primary) - nb);
        if (gap < SVT_MIN_HUE_GAP)
            continue;
        score = chroma * 4 + mx;
        if (score > bestScore)
        {
            bestScore = score;
            best = SVT_RGB(nr, ng, nb);
        }
    }
    return best;
}

// Two-tone ramp: shadow = dark primary, tip = secondary (or a mid primary if 0), base = primary,
// light = pale primary. Index 5 (white core) stays white.
static inline void ShinyViceTint_Apply2(u16 *pal16, u16 primary, u16 secondary)
{
    pal16[1] = ShinyViceTint_Scale(secondary != 0 ? secondary : primary, 4, 10);
    pal16[2] = secondary != 0 ? secondary : ShinyViceTint_Scale(primary, 7, 10);
    pal16[3] = primary;
    pal16[4] = ShinyViceTint_Lighten(primary, 1, 2);
}

#endif // GUARD_SHINY_VICE_TINT_H
