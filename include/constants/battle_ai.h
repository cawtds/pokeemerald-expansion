#ifndef GUARD_CONSTANTS_BATTLE_AI_H
#define GUARD_CONSTANTS_BATTLE_AI_H

// battlers
#define AI_TARGET 0
#define AI_USER 1
#define AI_TARGET_PARTNER 2
#define AI_USER_PARTNER 3

// get_type command
#define AI_TYPE1_TARGET 0
#define AI_TYPE1_USER 1
#define AI_TYPE2_TARGET 2
#define AI_TYPE2_USER 3
#define AI_TYPE_MOVE 4

// type effectiveness
#define AI_EFFECTIVENESS_x4     160
#define AI_EFFECTIVENESS_x2     80
#define AI_EFFECTIVENESS_x1     40
#define AI_EFFECTIVENESS_x0_5   20
#define AI_EFFECTIVENESS_x0_25  10
#define AI_EFFECTIVENESS_x0     0

// ai weather
#define AI_WEATHER_SUN 0
#define AI_WEATHER_RAIN 1
#define AI_WEATHER_SANDSTORM 2
#define AI_WEATHER_HAIL 3

// get_how_powerful_move_is
#define MOVE_POWER_OTHER        0
#define MOVE_NOT_MOST_POWERFUL  1
#define MOVE_MOST_POWERFUL      2

// script's table id to bit
#define AI_FLAG_CHECK_BAD_MOVE        (1 << 0)
#define AI_FLAG_TRY_TO_FAINT          (1 << 1)
#define AI_FLAG_CHECK_VIABILITY       (1 << 2)
#define AI_FLAG_SETUP_FIRST_TURN      (1 << 3)
#define AI_FLAG_RISKY                 (1 << 4)
#define AI_FLAG_PREFER_POWER_EXTREMES (1 << 5)
#define AI_FLAG_PREFER_BATON_PASS     (1 << 6)
#define AI_FLAG_DOUBLE_BATTLE         (1 << 7)
#define AI_FLAG_HP_AWARE              (1 << 8)
#define AI_FLAG_TRY_SUNNY_DAY_START   (1 << 9)
// 10 - 28 are not used
#define AI_FLAG_ROAMING               (1 << 29)
#define AI_FLAG_SAFARI                (1 << 30)
#define AI_FLAG_FIRST_BATTLE          (1 << 31)

#endif // GUARD_CONSTANTS_BATTLE_AI_H
