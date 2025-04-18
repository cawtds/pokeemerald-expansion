#include "global.h"
#include "move.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Compound Eyes increasese accuracy by 1.3x")
{
    u32 move = MOVE_ZAP_CANNON;
    PASSES_RANDOMLY(65, 100, RNG_ACCURACY);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_COMPOUND_EYES); Moves(move); }
        OPPONENT(SPECIES_WOBBUFFET) {  };
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Compound Eyes does not affect OHKO moves")
{
    PASSES_RANDOMLY(30, 100, RNG_ACCURACY);
    GIVEN {
        ASSUME(gMoveInfo[MOVE_FISSURE].accuracy == 30);
        ASSUME(gMoveInfo[MOVE_FISSURE].effect == EFFECT_OHKO);
        PLAYER(SPECIES_BUTTERFREE) { Ability(ABILITY_COMPOUND_EYES); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FISSURE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FISSURE, player);
        HP_BAR(opponent, hp: 0);
    }
}
