#include "global.h"
#include "move.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Oblivious prevents attraction before same gender check")
{
    u32 move = MOVE_ATTRACT;
    GIVEN {
        ASSUME(GetMoveEffect(move) == EFFECT_ATTRACT);
        PLAYER(SPECIES_PIDGEY) { Ability(ABILITY_OBLIVIOUS); Gender(MON_FEMALE); }
        OPPONENT(SPECIES_PIDGEY) { Moves(move); Gender(MON_FEMALE); }
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        MESSAGE("PIDGEY's OBLIVIOUS prevents romance!");
    }
}

SINGLE_BATTLE_TEST("Oblivious prevents Cute Charm from activating")
{
    u32 move = MOVE_POUND;
    PASSES_RANDOMLY(3, 3, RNG_CUTE_CHARM);
    GIVEN {
        ASSUME(IsContactMove(move));
        PLAYER(SPECIES_PIDGEY) { Ability(ABILITY_OBLIVIOUS); Gender(MON_FEMALE); }
        OPPONENT(SPECIES_PIDGEY) { Ability(ABILITY_CUTE_CHARM); Gender(MON_MALE); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        MESSAGE("PIDGEY used POUND!");
        NONE_OF {
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_INFATUATION);
            MESSAGE("Foe PIDGEY's CUTE CHARM infatuated PIDGEY!");
        }
    }
}
