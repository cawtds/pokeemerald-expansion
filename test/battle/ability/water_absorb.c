#include "global.h"
#include "move.h"
#include "test/battle.h"
#include "constants/types.h"

SINGLE_BATTLE_TEST("Water Absorb recovers 25% HP when hit by water type move")
{
    u32 move = MOVE_WATER_GUN;
    GIVEN {
        ASSUME(GetMoveType(move) == TYPE_WATER);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_WATER_ABSORB); HP(50); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(move); };
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        HP_BAR(player, damage: -25);
    }
}
