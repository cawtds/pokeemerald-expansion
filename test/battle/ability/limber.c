
#include "global.h"
#include "move.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Limber prevents paralysis")
{
    u32 move = MOVE_THUNDER_WAVE;
    GIVEN {
        ASSUME(GetMoveEffect(move) == EFFECT_PARALYZE);
        PLAYER(SPECIES_PIDGEY) { Ability(ABILITY_LIMBER); }
        OPPONENT(SPECIES_PIDGEY) { Moves(move); }
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        NONE_OF {
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, player);
            STATUS_ICON(player, paralysis: TRUE);
        }
    }
}
