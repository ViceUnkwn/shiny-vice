#include <assert.h>
#include <stdio.h>
#include "shiny_roll.h"

int main(void)
{
    struct ShinyRollSources s = {0};

    assert(ShinyVice_ComputeExtraRolls(&s) == 0);

    s.charm = 1;
    assert(ShinyVice_ComputeExtraRolls(&s) == 1);

    assert(ShinyVice_ChainBonus(0) == 0);
    assert(ShinyVice_ChainBonus(24) == 0);
    assert(ShinyVice_ChainBonus(25) == 1);
    assert(ShinyVice_ChainBonus(99) == 3);
    assert(ShinyVice_ChainBonus(255) == 3);

    s.chain = 3;
    assert(ShinyVice_ComputeExtraRolls(&s) == 4);

    // Everything stacked must never exceed 7 extra rolls (8 total).
    s.charm = 5; s.chain = 10; s.lure = 1; s.fishing = 20;
    assert(ShinyVice_ComputeExtraRolls(&s) == 7);

    // ---- Shiny quality ----
    {
        unsigned int count, seed, mask, bits, i;
        unsigned int adamantJolly = (1u << 3) | (1u << 13);
        unsigned int modestTimid = (1u << 15) | (1u << 10);

        // Perfect IV picks: always exactly `count` distinct stats, for every possible random value.
        for (count = 0; count <= 6; count++)
        {
            for (seed = 0; seed < 720; seed++)
            {
                mask = ShinyVice_PerfectIvMask(count, seed);
                for (bits = 0, i = 0; i < 6; i++)
                    bits += (mask >> i) & 1;
                assert(bits == count);
                assert((mask & ~0x3Fu) == 0);
            }
        }
        assert(ShinyVice_PerfectIvMask(9, 12345) == 0x3F); // clamps to all six
        // Over many seeds every stat gets picked (no stat is unreachable).
        mask = 0;
        for (seed = 0; seed < 720; seed++)
            mask |= ShinyVice_PerfectIvMask(2, seed);
        assert(mask == 0x3F);

        // Good natures by role.
        assert(ShinyVice_GoodNatureMask(130, 70) == adamantJolly);   // physical
        assert(ShinyVice_GoodNatureMask(60, 120) == modestTimid);    // special
        assert(ShinyVice_GoodNatureMask(100, 100) != adamantJolly);  // mixed
        assert(ShinyVice_GoodNatureMask(100, 100) != modestTimid);
        assert(ShinyVice_GoodNatureMask(100, 100) == ((1u << 1) | (1u << 4) | (1u << 11) | (1u << 14) | (1u << 16) | (1u << 19)));
        assert(ShinyVice_GoodNatureMask(100, 86) == ShinyVice_GoodNatureMask(100, 100)); // inside the margin
        assert(ShinyVice_GoodNatureMask(100, 85) == adamantJolly);                     // outside the margin
        // No good nature is neutral (neutral natures are 0, 6, 12, 18, 24).
        for (i = 0; i < 25; i += 6)
        {
            assert(!(ShinyVice_GoodNatureMask(130, 70) & (1u << i)));
            assert(!(ShinyVice_GoodNatureMask(70, 130) & (1u << i)));
            assert(!(ShinyVice_GoodNatureMask(100, 100) & (1u << i)));
        }

        // Debug-menu odds: 1/N -> threshold out of 65536.
        assert(ShinyVice_ThresholdFromDenominator(4096) == 16);   // the real base rate
        assert(ShinyVice_ThresholdFromDenominator(8192) == 8);
        assert(ShinyVice_ThresholdFromDenominator(2) == 32768);
        assert(ShinyVice_ThresholdFromDenominator(1) == 65536);   // always shiny
        assert(ShinyVice_ThresholdFromDenominator(0) == 65536);   // 0 treated as 1
        assert(ShinyVice_ThresholdFromDenominator(65535) == 1);   // never rounds down to 0
    }

    printf("shiny_roll: all tests passed\n");
    return 0;
}