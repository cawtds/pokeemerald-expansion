#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Drizzle summons rain", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_DRIZZLE; }
    PARAMETRIZE { ability = ABILITY_NONE; }

    GIVEN {
        PLAYER(SPECIES_PIDGEY);
        OPPONENT(SPECIES_PIDGEY) { Ability(ability); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_BUBBLE); }
    } SCENE {
        if (ability == ABILITY_DRIZZLE) {
            MESSAGE("Foe PIDGEY's DRIZZLE made it rain!");
        }
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(1.5), results[0].damage);
    }
}
