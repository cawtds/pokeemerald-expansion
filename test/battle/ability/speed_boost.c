#include "global.h"
#include "test/battle.h"
#include "move.h"
#include "item.h"

SINGLE_BATTLE_TEST("Speed Boost triggers at the end of the turn")
{
    GIVEN {
        PLAYER(SPECIES_PIDGEY) { Ability(ABILITY_SPEED_BOOST); Speed(99); }
        OPPONENT(SPECIES_PIDGEY) { Ability(ABILITY_BLAZE); Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_SPLASH); MOVE(opponent, MOVE_SPLASH); }
        TURN { MOVE(player, MOVE_SPLASH); MOVE(opponent, MOVE_SPLASH); }
    } SCENE {
        MESSAGE("Foe PIDGEY used SPLASH!");
        MESSAGE("PIDGEY used SPLASH!");
        MESSAGE("PIDGEY's SPEED BOOST raised its SPEED!");
        MESSAGE("PIDGEY used SPLASH!");
        MESSAGE("Foe PIDGEY used SPLASH!");
    }
}
