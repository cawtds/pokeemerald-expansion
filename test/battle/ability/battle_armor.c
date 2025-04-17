#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Battle Armor and Shell Armor block critical hits")
{
    u32 ability;

    PARAMETRIZE { ability = ABILITY_SHELL_ARMOR; }
    PARAMETRIZE { ability = ABILITY_BATTLE_ARMOR; }
    PARAMETRIZE { ability = ABILITY_NONE; }

    GIVEN {
        PLAYER(SPECIES_PIDGEY);
        OPPONENT(SPECIES_PIDGEY) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_POUND, criticalHit: TRUE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, player);
        if (ability == ABILITY_SHELL_ARMOR || ability == ABILITY_BATTLE_ARMOR)
            NOT MESSAGE("A critical hit!");
        else
            MESSAGE("A critical hit!");
    }
}
