#include "global.h"
#include "move.h"
#include "test/battle.h"
#include "constants/types.h"

SINGLE_BATTLE_TEST("Forecast changes Castforms type")
{
    u32 move1 = MOVE_RAIN_DANCE;
    u32 move2 = MOVE_SUNNY_DAY;
    u32 move3 = MOVE_HAIL;
    u32 move4 = MOVE_SANDSTORM;
    u32 move5 = MOVE_THUNDER_SHOCK;
    u32 move6 = MOVE_WATER_GUN;
    u32 move7 = MOVE_EMBER;
    u32 move8 = MOVE_SHADOW_BALL;
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); Moves(move1, move2, move3, move4); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(move5, move6, move7, move8); };
    } WHEN {
        TURN { MOVE(player, move1); MOVE(opponent, move5); }
        TURN { MOVE(player, move2); MOVE(opponent, move6); }
        TURN { MOVE(player, move3); MOVE(opponent, move7); }
        TURN { MOVE(player, move4); MOVE(opponent, move8); }
    } SCENE {
        MESSAGE("CASTFORM used RAIN DANCE!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CASTFORM_CHANGE);
        MESSAGE("Foe WOBBUFFET used THUNDERSHOCK!");
        MESSAGE("It's super effective!");

        MESSAGE("CASTFORM used SUNNY DAY!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CASTFORM_CHANGE);
        MESSAGE("Foe WOBBUFFET used WATER GUN!");
        MESSAGE("It's super effective!");

        MESSAGE("CASTFORM used HAIL!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CASTFORM_CHANGE);
        MESSAGE("Foe WOBBUFFET used EMBER!");
        MESSAGE("It's super effective!");

        MESSAGE("CASTFORM used SANDSTORM!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CASTFORM_CHANGE);
        MESSAGE("Foe WOBBUFFET used SHADOW BALL!");
        MESSAGE("It doesn't affect CASTFORM…");
    }
}

DOUBLE_BATTLE_TEST("Forecast transforms all Castforms present in weather")
{
    u32 move;
    PARAMETRIZE { move = MOVE_SUNNY_DAY; }
    PARAMETRIZE { move = MOVE_RAIN_DANCE; }
    PARAMETRIZE { move = MOVE_HAIL; }
    GIVEN {
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); }
        PLAYER(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); }
        OPPONENT(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); }
        OPPONENT(SPECIES_CASTFORM) { Ability(ABILITY_FORECAST); }
    } WHEN {
        TURN { MOVE(playerRight, move); }
    } SCENE {
        ABILITY_POPUP(playerLeft, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CASTFORM_CHANGE, playerLeft);
        MESSAGE("CASTFORM transformed!");
        ABILITY_POPUP(opponentLeft, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CASTFORM_CHANGE, opponentLeft);
        MESSAGE("Foe CASTFORM transformed!");
        ABILITY_POPUP(playerRight, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CASTFORM_CHANGE, playerRight);
        MESSAGE("CASTFORM transformed!");
        ABILITY_POPUP(opponentRight, ABILITY_FORECAST);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_CASTFORM_CHANGE, opponentRight);
        MESSAGE("Foe CASTFORM transformed!");
    }
}