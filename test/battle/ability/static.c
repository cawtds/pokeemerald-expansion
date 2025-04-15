#include "global.h"
#include "test/battle.h"
#include "move.h"

SINGLE_BATTLE_TEST("Static inflicts paralysis on contact")
{
    u32 move;
    PARAMETRIZE { move = MOVE_TACKLE; }
    PARAMETRIZE { move = MOVE_SWIFT; }
    GIVEN {
        ASSUME(IsContactMove(MOVE_TACKLE));
        ASSUME(!IsContactMove(MOVE_SWIFT));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIKACHU) { Ability(ABILITY_STATIC); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        if (IsContactMove(move)) {
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, player);
            MESSAGE("Foe PIKACHU's STATIC paralyzed WOBBUFFET! It may be unable to move!");
            STATUS_ICON(player, paralysis: TRUE);
        } else {
            NONE_OF {
                ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, player);
                MESSAGE("Foe PIKACHU's STATIC paralyzed WOBBUFFET! It may be unable to move!");
                STATUS_ICON(player, paralysis: TRUE);
            }
        }
    }
}

SINGLE_BATTLE_TEST("Static triggers 30% of the time")
{
    PASSES_RANDOMLY(3, 9, RNG_STATIC);
    GIVEN {
        ASSUME(IsContactMove(MOVE_TACKLE));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIKACHU) { Ability(ABILITY_STATIC); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, player);
        MESSAGE("Foe PIKACHU's STATIC paralyzed WOBBUFFET! It may be unable to move!");
        STATUS_ICON(player, paralysis: TRUE);
    }
}
