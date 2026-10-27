#include "global.h"
#include "test/battle.h"

AI_SINGLE_BATTLE_TEST("Roxanne's Geodude prioritizes Bulldoze against Aron")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES);
        PLAYER(SPECIES_ARON) { Level(15); }
        OPPONENT(SPECIES_GEODUDE) {
            Level(13);
            Ability(ABILITY_STURDY);
            Moves(MOVE_ROCK_TOMB, MOVE_BULLDOZE, MOVE_DEFENSE_CURL, MOVE_TACKLE);
        }
    } WHEN {
        TURN { SCORE_GT(opponent, MOVE_BULLDOZE, MOVE_ROCK_TOMB); }
    }
}

AI_SINGLE_BATTLE_TEST("Roxanne's Aron scores stronger STAB Rock Tomb above Metal Claw")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES);
        PLAYER(SPECIES_SEEDOT) { Level(15); }
        OPPONENT(SPECIES_ARON) {
            Level(14);
            Ability(ABILITY_ROCK_HEAD);
            Moves(MOVE_METAL_CLAW, MOVE_ROCK_TOMB, MOVE_ROAR, MOVE_HARDEN);
        }
    } WHEN {
        TURN { SCORE_GT(opponent, MOVE_ROCK_TOMB, MOVE_METAL_CLAW); }
    }
}

AI_SINGLE_BATTLE_TEST("Roxanne's Lileep scores Rock Tomb above super-effective Acid")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES);
        PLAYER(SPECIES_SEEDOT) { Level(15); }
        OPPONENT(SPECIES_LILEEP) {
            Level(14);
            Ability(ABILITY_STORM_DRAIN);
            Item(ITEM_ORAN_BERRY);
            Moves(MOVE_ROCK_TOMB, MOVE_ACID, MOVE_CONFUSE_RAY, MOVE_INGRAIN);
        }
    } WHEN {
        TURN { SCORE_GT(opponent, MOVE_ROCK_TOMB, MOVE_ACID); }
    }
}

AI_SINGLE_BATTLE_TEST("Roxanne's Nosepass values Thunder Wave against a healthy Fire type")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES);
        PLAYER(SPECIES_TORCHIC) { Level(15); }
        OPPONENT(SPECIES_NOSEPASS) {
            Level(15);
            Ability(ABILITY_STURDY);
            Item(ITEM_BERRY_JUICE);
            Moves(MOVE_ROCK_THROW, MOVE_THUNDER_WAVE, MOVE_BLOCK, MOVE_HARDEN);
        }
    } WHEN {
        TURN { SCORE_GT(opponent, MOVE_THUNDER_WAVE, MOVE_ROCK_THROW); }
    }
}
AI_SINGLE_BATTLE_TEST("Roxanne's Nosepass chooses Rock Throw over status when it can finish a Fire type")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES);
        PLAYER(SPECIES_TORCHIC) { Level(15); HP(1); }
        OPPONENT(SPECIES_NOSEPASS) {
            Level(15);
            Ability(ABILITY_STURDY);
            Item(ITEM_BERRY_JUICE);
            Moves(MOVE_ROCK_THROW, MOVE_THUNDER_WAVE, MOVE_BLOCK, MOVE_HARDEN);
        }
    } WHEN {
        TURN { SCORE_GT(opponent, MOVE_ROCK_THROW, MOVE_THUNDER_WAVE); }
    }
}
SINGLE_BATTLE_TEST("Roxanne's Lileep absorbs Water attacks with Storm Drain")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_WATER_GUN) == TYPE_WATER);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_WATER_GUN); }
        OPPONENT(SPECIES_LILEEP) { Ability(ABILITY_STORM_DRAIN); }
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } THEN {
        EXPECT_EQ(opponent->hp, opponent->maxHP);
        EXPECT_EQ(opponent->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Roxanne's Nosepass survives a full-health hit, then Berry Juice restores 20 HP")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(40); Moves(MOVE_SEISMIC_TOSS); }
        OPPONENT(SPECIES_NOSEPASS) {
            Level(15);
            Ability(ABILITY_STURDY);
            Item(ITEM_BERRY_JUICE);
            MaxHP(37);
            HP(37);
        }
    } WHEN {
        TURN { MOVE(player, MOVE_SEISMIC_TOSS); }
    } THEN {
        EXPECT_EQ(opponent->hp, 21);
        EXPECT_EQ(opponent->item, ITEM_NONE);
    }
}

