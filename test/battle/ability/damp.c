#include "global.h"
#include "move.h"
#include "test/battle.h"


SINGLE_BATTLE_TEST("Damp prevents explosion")
{
    u32 ability;
    u32 move = MOVE_EXPLOSION;
    PARAMETRIZE { ability = ABILITY_DAMP; }
    PARAMETRIZE { ability = ABILITY_NONE; }

    GIVEN {
        ASSUME(GetMoveEffect(move) == EFFECT_EXPLOSION);
        PLAYER(SPECIES_PIDGEY);
        OPPONENT(SPECIES_PIDGEY) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("PIDGEY used EXPLOSION!");
        if (ability == ABILITY_DAMP)
            MESSAGE("Foe PIDGEY's DAMP prevents PIDGEY from using EXPLOSION!");
        else
            NOT MESSAGE("Foe PIDGEY's DAMP prevents PIDGEY from using EXPLOSION!");
    }
}
