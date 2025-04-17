#include "global.h"
#include "test/battle.h"
#include "move.h"
#include "constants/battle_ai.h"

SINGLE_BATTLE_TEST("Static inflicts paralysis on contact")
{
    u32 move;
    PARAMETRIZE { move = MOVE_POUND; }
    PARAMETRIZE { move = MOVE_SWIFT; }
    GIVEN {
        ASSUME(IsContactMove(MOVE_POUND));
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

SINGLE_BATTLE_TEST("Static has a 1/3 chance to trigger")
{
    PASSES_RANDOMLY(1, 3, RNG_STATIC);
    GIVEN {
        ASSUME(IsContactMove(MOVE_POUND));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIKACHU) { Ability(ABILITY_STATIC); }
    } WHEN {
        TURN { MOVE(player, MOVE_POUND); }
    } SCENE {
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, player);
        MESSAGE("Foe PIKACHU's STATIC paralyzed WOBBUFFET! It may be unable to move!");
        STATUS_ICON(player, paralysis: TRUE);
    }
}
