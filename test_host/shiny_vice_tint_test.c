// Host-side test for include/shiny_vice_tint.h.
// Build and run from the repo root:
//   gcc -Wall -Wextra -I include -o /tmp/shiny_vice_tint_test test_host/shiny_vice_tint_test.c && /tmp/shiny_vice_tint_test
#include <stdio.h>
#include <stdint.h>

typedef uint16_t u16;
typedef uint32_t u32;

#include "shiny_vice_tint.h"

static int sFailures;

#define CHECK(cond, msg) do { if (!(cond)) { printf("FAIL: %s\n", msg); sFailures++; } } while (0)

static void Fill(u16 *pal, u16 value)
{
    int i;
    for (i = 0; i < 16; i++)
        pal[i] = value;
}

int main(void)
{
    u16 pal[16];
    u16 tint;

    // Greys / black / white only -> default gold.
    Fill(pal, SVT_RGB(0, 0, 0));
    pal[1] = SVT_RGB(31, 31, 31);
    pal[2] = SVT_RGB(12, 12, 12);
    CHECK(ShinyViceTint_Pick(pal) == SVT_DEFAULT_TINT, "greys fall back to default");

    // Vivid orange beats a pale cream and a dark brown.
    Fill(pal, SVT_RGB(0, 0, 0));
    pal[1] = SVT_RGB(31, 28, 22);   // cream: chroma 9, but orange scores higher
    pal[2] = SVT_RGB(31, 16, 2);    // orange
    pal[3] = SVT_RGB(8, 4, 0);      // dark brown: too dark
    tint = ShinyViceTint_Pick(pal);
    CHECK(SVT_R(tint) == 31, "picked tint is normalised to peak 31");
    CHECK(SVT_G(tint) >= 15 && SVT_G(tint) <= 17, "orange picked (green channel ~16)");
    CHECK(SVT_B(tint) <= 3, "orange picked (blue channel low)");

    // A dim but saturated colour is lifted to full brightness.
    Fill(pal, SVT_RGB(0, 0, 0));
    pal[5] = SVT_RGB(4, 12, 16);
    tint = ShinyViceTint_Pick(pal);
    CHECK(SVT_B(tint) == 31, "dim blue lifted to 31");
    CHECK(SVT_R(tint) < SVT_G(tint) && SVT_G(tint) < SVT_B(tint), "hue order preserved");

    // Index 0 (transparent) is ignored even if vivid.
    Fill(pal, SVT_RGB(0, 0, 0));
    pal[0] = SVT_RGB(0, 31, 0);
    CHECK(ShinyViceTint_Pick(pal) == SVT_DEFAULT_TINT, "index 0 ignored");

    // Ramp ordering: outline < mid < base < light in brightness, white core untouched.
    {
        u16 out[16];
        u16 t = SVT_RGB(6, 18, 31);
        int i;
        for (i = 0; i < 16; i++) out[i] = SVT_RGB(31, 31, 31);
        ShinyViceTint_Apply(out, t);
        CHECK(SVT_B(out[1]) < SVT_B(out[2]), "outline darker than mid");
        CHECK(SVT_B(out[2]) < SVT_B(out[3]), "mid darker than base");
        CHECK(out[3] == t, "base is the tint");
        CHECK(SVT_R(out[4]) > SVT_R(t), "light lifts red toward white");
        CHECK(out[5] == SVT_RGB(31, 31, 31) && out[6] == SVT_RGB(31, 31, 31), "indices 5+ untouched");
        printf("blue ramp: outline %u,%u,%u mid %u,%u,%u base %u,%u,%u light %u,%u,%u\n",
               SVT_R(out[1]), SVT_G(out[1]), SVT_B(out[1]), SVT_R(out[2]), SVT_G(out[2]), SVT_B(out[2]),
               SVT_R(out[3]), SVT_G(out[3]), SVT_B(out[3]), SVT_R(out[4]), SVT_G(out[4]), SVT_B(out[4]));
    }

    // Values never leave 5 bits.
    {
        u16 out[16];
        u32 c;
        for (c = 0; c < 0x8000; c += 37)
        {
            Fill(out, 0);
            ShinyViceTint_Apply(out, (u16)c);
            CHECK((out[1] | out[2] | out[3] | out[4]) < 0x8000, "stays RGB555");
        }
    }

    if (sFailures == 0)
        printf("shiny_vice_tint: all tests passed\n");
    return sFailures != 0;
}
