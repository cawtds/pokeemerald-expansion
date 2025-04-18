#include "global.h"
#include "move.h"
#include "test/battle.h"
#include "constants/types.h"

SINGLE_BATTLE_TEST("Volt Absorb recovers 25% HP when hit by electric type damaging move")
{
    u32 move = MOVE_THUNDER_SHOCK;
    GIVEN {
        ASSUME(GetMoveType(move) == TYPE_ELECTRIC);
        ASSUME(GetMovePower(move) != 0);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_VOLT_ABSORB); HP(50); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(move); };
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        HP_BAR(player, damage: -25);
    }
}

SINGLE_BATTLE_TEST("Volt Absorb does not prevent non-damaging electric type moves")
{
    u32 move = MOVE_THUNDER_WAVE;
    GIVEN {
        ASSUME(GetMoveType(move) == TYPE_ELECTRIC);
        ASSUME(GetMovePower(move) == 0);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_VOLT_ABSORB); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(move); };
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ);
        STATUS_ICON(player, paralysis: TRUE);
    }
}
