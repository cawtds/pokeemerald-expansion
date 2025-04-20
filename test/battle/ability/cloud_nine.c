#include "global.h"
#include "move.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Cloud Nine negates rain damage buff", s16 damage)
{
    u32 atkMove, ability;
    u32 weatherMove = MOVE_RAIN_DANCE;

    PARAMETRIZE{ atkMove = MOVE_WATER_GUN; ability = ABILITY_NONE; };
    PARAMETRIZE{ atkMove = MOVE_WATER_GUN; ability = ABILITY_CLOUD_NINE; };
    PARAMETRIZE{ atkMove = MOVE_WATER_GUN; ability = ABILITY_AIR_LOCK; };

    GIVEN {
        PLAYER(SPECIES_PIDGEY) { Ability(ability); Moves(weatherMove); }
        OPPONENT(SPECIES_PIDGEY) { Moves(atkMove);  }
    } WHEN {
        TURN { MOVE(player, weatherMove); MOVE(opponent, atkMove); }
    } SCENE {
        MESSAGE("It started to rain!");
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[i].damage, Q_4_12(1.5), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Cloud Nine/Air Lock prevent accuracy check bypass of Thunder in Rain")
{
    u32 passes = 0, ability;
    u32 move = MOVE_THUNDER;

    PARAMETRIZE{ passes = 100; ability = ABILITY_NONE; };
    PARAMETRIZE{ passes = GetMoveAccuracy(move); ability = ABILITY_CLOUD_NINE; };
    PARAMETRIZE{ passes = GetMoveAccuracy(move); ability = ABILITY_AIR_LOCK; };

    PASSES_RANDOMLY(passes, 100, RNG_ACCURACY);
    GIVEN {
        ASSUME(GetMoveEffect(move) == EFFECT_THUNDER);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); };
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_RAIN_DANCE); MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        NONE_OF { MESSAGE("Wobbuffet's attack missed!"); }
    }
}

SINGLE_BATTLE_TEST("Cloud Nine negates sun damage buff", s16 damage)
{
    u32 atkMove, ability;
    u32 weatherMove = MOVE_SUNNY_DAY;

    PARAMETRIZE{ atkMove = MOVE_EMBER; ability = ABILITY_NONE; };
    PARAMETRIZE{ atkMove = MOVE_EMBER; ability = ABILITY_CLOUD_NINE; };
    PARAMETRIZE{ atkMove = MOVE_EMBER; ability = ABILITY_AIR_LOCK; };

    GIVEN {
        PLAYER(SPECIES_PIDGEY) { Ability(ability); Moves(weatherMove); }
        OPPONENT(SPECIES_PIDGEY) { Moves(atkMove);  }
    } WHEN {
        TURN { MOVE(player, weatherMove); MOVE(opponent, atkMove); }
    } SCENE {
        MESSAGE("The sunlight got bright!");
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[i].damage, Q_4_12(1.5), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Cloud Nine prevents instants Solarbeam", s16 damage)
{
    u32 ability;
    u32 atkMove = MOVE_SOLAR_BEAM;
    u32 weatherMove = MOVE_SUNNY_DAY;

    PARAMETRIZE{ ability = ABILITY_NONE; };
    PARAMETRIZE{ ability = ABILITY_CLOUD_NINE; };
    PARAMETRIZE{ ability = ABILITY_AIR_LOCK; };

    GIVEN {
        PLAYER(SPECIES_PIDGEY) { Ability(ability); }
        OPPONENT(SPECIES_PIDGEY);
    } WHEN {
        TURN { MOVE(player, weatherMove); MOVE(opponent, atkMove); }
        if (ability != ABILITY_NONE)
            TURN { SKIP_TURN(opponent); }
    } SCENE {
        MESSAGE("The sunlight got bright!");
        if (ability != ABILITY_NONE)
        {
            MESSAGE("Foe PIDGEY took in sunlight!");
        }
        else
            NOT MESSAGE("Foe PIDGEY took in sunlight!");
        MESSAGE("Foe PIDGEY used SOLARBEAM!");
    }
}

SINGLE_BATTLE_TEST("Cloud Nine/Air Lock prevent Sandstorm damage")
{
    u32 ability = 0;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_CLOUD_NINE; }
    PARAMETRIZE { ability = ABILITY_AIR_LOCK; }
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_SANDSTORM) == EFFECT_SANDSTORM);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SANDSTORM); }
    } SCENE {
        MESSAGE("Foe WOBBUFFET used SANDSTORM!");
        MESSAGE("A sandstorm brewed!");
        MESSAGE("The sandstorm rages.");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_SANDSTORM_CONTINUES);
        if (ability != ABILITY_NONE)
        {
            NONE_OF {
                HP_BAR(player);
                MESSAGE("Foe WOBBUFFET is buffeted by the sandstorm!");
                HP_BAR(opponent);
            }
        }
        else
        {
            HP_BAR(player);
            MESSAGE("Foe WOBBUFFET is buffeted by the sandstorm!");
            HP_BAR(opponent);
        }
    }
}
