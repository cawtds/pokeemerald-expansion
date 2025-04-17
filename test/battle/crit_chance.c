#include "global.h"
#include "test/battle.h"
#include "move.h"
#include "item.h"

SINGLE_BATTLE_TEST("Crit Chance stage 0: 1/16 crit chance")
{
    PASSES_RANDOMLY(1, 16, RNG_CRITICAL_HIT);
    GIVEN {
        PLAYER(SPECIES_FARFETCHD) { Ability(ABILITY_NONE); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_POUND); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Crit Chance stage 1: 1/8 crit chance")
{
    PASSES_RANDOMLY(1, 8, RNG_CRITICAL_HIT);
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_SLASH) == EFFECT_HIGH_CRITICAL);
        PLAYER(SPECIES_FARFETCHD) { Ability(ABILITY_NONE); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SLASH, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Crit Chance stage 2: 1/4 crit chance")
{
    PASSES_RANDOMLY(1, 4, RNG_CRITICAL_HIT);
    GIVEN {
        ASSUME(gItemInfo[ITEM_SCOPE_LENS].holdEffect == HOLD_EFFECT_SCOPE_LENS);
        ASSUME(GetMoveEffect(MOVE_SLASH) == EFFECT_HIGH_CRITICAL);
        PLAYER(SPECIES_FARFETCHD) { Ability(ABILITY_NONE); Item(ITEM_SCOPE_LENS); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SLASH, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Crit Chance stage 3: 1/3 crit chance")
{
    PASSES_RANDOMLY(1, 3, RNG_CRITICAL_HIT);
    GIVEN {
        ASSUME(gItemInfo[ITEM_STICK].holdEffect == HOLD_EFFECT_STICK);
        PLAYER(SPECIES_FARFETCHD) { Ability(ABILITY_NONE); Item(ITEM_STICK); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SLASH, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Crit Chance stage 4: 1/2 crit chance")
{
    PASSES_RANDOMLY(1, 2, RNG_CRITICAL_HIT);
    GIVEN {
        ASSUME(gItemInfo[ITEM_STICK].holdEffect == HOLD_EFFECT_STICK);
        PLAYER(SPECIES_FARFETCHD) { Ability(ABILITY_NONE); Item(ITEM_STICK); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FOCUS_ENERGY); }
        TURN { MOVE(player, MOVE_POUND); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FOCUS_ENERGY, player);
        MESSAGE("FARFETCH'D is getting pumped!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Crit Chance stage 5+: 1/2 crit chance")
{
    PASSES_RANDOMLY(1, 2, RNG_CRITICAL_HIT);
    GIVEN {
        ASSUME(gItemInfo[ITEM_STICK].holdEffect == HOLD_EFFECT_STICK);
        PLAYER(SPECIES_FARFETCHD) { Ability(ABILITY_NONE); Item(ITEM_STICK); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FOCUS_ENERGY); }
        TURN { MOVE(player, MOVE_SLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FOCUS_ENERGY, player);
        MESSAGE("FARFETCH'D is getting pumped!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SLASH, player);
        MESSAGE("A critical hit!");
    }
}
