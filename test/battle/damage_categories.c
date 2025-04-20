#include "global.h"
#include "type.h"
#include "move.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Damage Categories: Sp. Attack boosts special moves", s16 damage)
{
    u32 boostMove;
    u32 dmgMove = MOVE_EMBER;
    PARAMETRIZE { boostMove = MOVE_SPLASH; }
    PARAMETRIZE { boostMove = MOVE_TAIL_GLOW; }

    GIVEN {
        ASSUME(GetTypeDamageCategory(GetMoveType(dmgMove)) == DAMAGE_CATEGORY_SPECIAL);
        ASSUME(GetMoveEffect(MOVE_TAIL_GLOW) == EFFECT_SPECIAL_ATTACK_UP_2);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, boostMove); }
        TURN { MOVE(player, dmgMove); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Damage Categories: Attack boosts physical moves", s16 damage)
{
    u32 boostMove;
    u32 dmgMove = MOVE_POUND;
    PARAMETRIZE { boostMove = MOVE_SPLASH; }
    PARAMETRIZE { boostMove = MOVE_SWORDS_DANCE; }

    GIVEN {
        ASSUME(GetTypeDamageCategory(GetMoveType(dmgMove)) == DAMAGE_CATEGORY_PHYSICAL);
        ASSUME(GetMoveEffect(MOVE_SWORDS_DANCE) == EFFECT_ATTACK_UP_2);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, boostMove); }
        TURN { MOVE(player, dmgMove); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
    }
}
