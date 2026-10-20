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

    printf("shiny_roll: all tests passed\n");
    return 0;
}