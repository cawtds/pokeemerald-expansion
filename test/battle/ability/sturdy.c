#include "global.h"
#include "test/battle.h"
#include "move.h"

SINGLE_BATTLE_TEST("Sturdy prevents OHKO moves")
{
    u32 moveId = MOVE_FISSURE;
    GIVEN {
        ASSUME(GetMoveEffect(moveId) == EFFECT_OHKO);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_GEODUDE) { Ability(ABILITY_STURDY); }
    } WHEN {
        TURN { MOVE(player, moveId); }
    } SCENE {
        MESSAGE("WOBBUFFET used FISSURE!");
        MESSAGE("Foe GEODUDE was protected by STURDY!");
    }
}

SINGLE_BATTLE_TEST("Sturdy does not prevent OHKOs")
{
    u32 moveId = MOVE_SURF;
    GIVEN {
        ASSUME(GetMoveEffect(moveId) != EFFECT_OHKO);
        PLAYER(SPECIES_SQUIRTLE) { SpAttack(200); };
        OPPONENT(SPECIES_GEODUDE) { Ability(ABILITY_STURDY); HP(50); MaxHP(50); }
    } WHEN {
        TURN { MOVE(player, moveId); }
    } SCENE {
        MESSAGE("SQUIRTLE used SURF!");
        MESSAGE("Foe GEODUDE fainted!");
    }
}
