#include "global.h"
#include "nature.h"
#include "strings.h"
#include "constants/battle_palace.h"
#include "constants/battle_string_ids.h"
#include "constants/natures.h"

// In Battle Palace, moves are chosen based on the pokemons nature rather than by the player
// Moves are grouped into "Attack", "Defense", or "Support" (see PALACE_MOVE_GROUP_*)
// Each nature has a certain percent chance of selecting a move from a particular group
// and a separate percent chance for each group when at or below 50% HP
// The table below doesn't list percentages for Support because you can subtract the other two
// Support percentages are listed in comments off to the side instead
#define PALACE_STYLE(atk, def, atkLow, defLow) {atk, atk + def, atkLow, atkLow + defLow}


const struct NatureInfo gNatureInfo[NUM_NATURES] =
{
    [NATURE_HARDY] =
    {
        .name = COMPOUND_STRING("HARDY"),
        .statUp = STAT_HP,
        .statDown = STAT_HP,
        .backAnim = 0,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlHardy,
        .pokeBlockAnim = { ANIM_HARDY,   AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(61,  7, 61,  7), // 32% support >= 50% HP, 32% support < 50% HP,
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_LONELY] =
    {
        .name = COMPOUND_STRING("LONELY"),
        .statUp = STAT_ATK,
        .statDown = STAT_DEF,
        .backAnim = 2,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlLonely,
        .pokeBlockAnim = { ANIM_LONELY,  AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(20, 25, 84,  8), // 55%,  8%,
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_BRAVE] =
    {
        .name = COMPOUND_STRING("BRAVE"),
        .statUp = STAT_ATK,
        .statDown = STAT_SPEED,
        .backAnim = 0,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlBrave,
        .pokeBlockAnim = { ANIM_BRAVE,   AFFINE_TURN_UP },
        .battlePalacePercents = PALACE_STYLE(70, 15, 32, 60), // 15%,  8%,
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_ADAMANT] =
    {
        .name = COMPOUND_STRING("ADAMANT"),
        .statUp = STAT_ATK,
        .statDown = STAT_SPATK,
        .backAnim = 0,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAdamant,
        .pokeBlockAnim = { ANIM_ADAMANT, AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(38, 31, 70, 15), // 31%, 15%,
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_NAUGHTY] =
    {
        .name = COMPOUND_STRING("NAUGHTY"),
        .statUp = STAT_ATK,
        .statDown = STAT_SPDEF,
        .backAnim = 0,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlNaughty,
        .pokeBlockAnim = { ANIM_NAUGHTY, AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(20, 70, 70, 22), // 10%,  8%,
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_BOLD] =
    {
        .name = COMPOUND_STRING("BOLD"),
        .statUp = STAT_DEF,
        .statDown = STAT_ATK,
        .backAnim = 1,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlBold,
        .pokeBlockAnim = { ANIM_BOLD,    AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(30, 20, 32, 58), // 50%, 10%,
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_DOCILE] =
    {
        .name = COMPOUND_STRING("DOCILE"),
        .statUp = STAT_HP,
        .statDown = STAT_HP,
        .backAnim = 1,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDocileNaiveQuietQuirky,
        .pokeBlockAnim = { ANIM_DOCILE,  AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), // 22%, 22%,
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_RANDOM,
    },

    [NATURE_RELAXED] =
    {
        .name = COMPOUND_STRING("RELAXED"),
        .statUp = STAT_DEF,
        .statDown = STAT_SPEED,
        .backAnim = 1,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlRelaxed,
        .pokeBlockAnim = { ANIM_RELAXED, AFFINE_TURN_UP_AND_DOWN },
        .battlePalacePercents = PALACE_STYLE(25, 15, 75, 15), // 60%, 10%,
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_IMPISH] =
    {
        .name = COMPOUND_STRING("IMPISH"),
        .statUp = STAT_DEF,
        .statDown = STAT_SPATK,
        .backAnim = 0,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlImpish,
        .pokeBlockAnim = { ANIM_IMPISH,  AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(69,  6, 28, 55), // 25%, 17%,
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_LAX] =
    {
        .name = COMPOUND_STRING("LAX"),
        .statUp = STAT_DEF,
        .statDown = STAT_SPDEF,
        .backAnim = 1,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlLax,
        .pokeBlockAnim = { ANIM_LAX,     AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(35, 10, 29,  6), // 55%, 65%,
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_TIMID] =
    {
        .name = COMPOUND_STRING("TIMID"),
        .statUp = STAT_SPEED,
        .statDown = STAT_ATK,
        .backAnim = 2,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlTimid,
        .pokeBlockAnim = { ANIM_TIMID,   AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(62, 10, 30, 20), // 28%, 50%,
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_HASTY] =
    {
        .name = COMPOUND_STRING("HASTY"),
        .statUp = STAT_SPEED,
        .statDown = STAT_DEF,
        .backAnim = 0,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlHasty,
        .pokeBlockAnim = { ANIM_HASTY,   AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(58, 37, 88,  6), //  5%,  6%,
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_SERIOUS] =
    {
        .name = COMPOUND_STRING("SERIOUS"),
        .statUp = STAT_HP,
        .statDown = STAT_HP,
        .backAnim = 1,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSerious,
        .pokeBlockAnim = { ANIM_SERIOUS, AFFINE_TURN_DOWN },
        .battlePalacePercents = PALACE_STYLE(34, 11, 29, 11), // 55%, 60%,
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_JOLLY] =
    {
        .name = COMPOUND_STRING("JOLLY"),
        .statUp = STAT_SPEED,
        .statDown = STAT_SPATK,
        .backAnim = 0,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlJolly,
        .pokeBlockAnim = { ANIM_JOLLY,   AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(35,  5, 35, 60), // 60%,  5%,
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_NAIVE] =
    {
        .name = COMPOUND_STRING("NAIVE"),
        .statUp = STAT_SPEED,
        .statDown = STAT_SPDEF,
        .backAnim = 0,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDocileNaiveQuietQuirky,
        .pokeBlockAnim = { ANIM_NAIVE,   AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), // 22%, 22%,
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_RANDOM,
    },

    [NATURE_MODEST] =
    {
        .name = COMPOUND_STRING("MODEST"),
        .statUp = STAT_SPATK,
        .statDown = STAT_ATK,
        .backAnim = 2,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlModest,
        .pokeBlockAnim = { ANIM_MODEST,  AFFINE_TURN_DOWN_SLOW },
        .battlePalacePercents = PALACE_STYLE(35, 45, 34, 60), // 20%,  6%,
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_MILD] =
    {
        .name = COMPOUND_STRING("MILD"),
        .statUp = STAT_SPATK,
        .statDown = STAT_DEF,
        .backAnim = 2,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlMild,
        .pokeBlockAnim = { ANIM_MILD,    AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(44, 50, 34,  6), //  6%, 60%,
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_QUIET] =
    {
        .name = COMPOUND_STRING("QUIET"),
        .statUp = STAT_SPATK,
        .statDown = STAT_SPEED,
        .backAnim = 2,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDocileNaiveQuietQuirky,
        .pokeBlockAnim = { ANIM_QUIET,   AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), // 22%, 22%,
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_BASHFUL] =
    {
        .name = COMPOUND_STRING("BASHFUL"),
        .statUp = STAT_HP,
        .statDown = STAT_HP,
        .backAnim = 2,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlBashful,
        .pokeBlockAnim = { ANIM_BASHFUL, AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(30, 58, 30, 58), // 12%, 12%,
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_RASH] =
    {
        .name = COMPOUND_STRING("RASH"),
        .statUp = STAT_SPATK,
        .statDown = STAT_SPDEF,
        .backAnim = 1,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlRash,
        .pokeBlockAnim = { ANIM_RASH,    AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(30, 13, 27,  6), // 57%, 67%,
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_CALM] =
    {
        .name = COMPOUND_STRING("CALM"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_ATK,
        .backAnim = 1,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlCalm,
        .pokeBlockAnim = { ANIM_CALM,    AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(40, 50, 25, 62), // 10%, 13%,
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_GENTLE] =
    {
        .name = COMPOUND_STRING("GENTLE"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_DEF,
        .backAnim = 2,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlGentle,
        .pokeBlockAnim = { ANIM_GENTLE,  AFFINE_TURN_DOWN_SLIGHT },
        .battlePalacePercents = PALACE_STYLE(18, 70, 90,  5), // 12%,  5%,
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

    [NATURE_SASSY] =
    {
        .name = COMPOUND_STRING("SASSY"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_SPEED,
        .backAnim = 1,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSassy,
        .pokeBlockAnim = { ANIM_SASSY,   AFFINE_TURN_UP_HIGH },
        .battlePalacePercents = PALACE_STYLE(88,  6, 22, 20), //  6%, 58%,
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_CAREFUL] =
    {
        .name = COMPOUND_STRING("CAREFUL"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_SPATK,
        .backAnim = 2,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlCareful,
        .pokeBlockAnim = { ANIM_CAREFUL, AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(42, 50, 42,  5), //  8%, 53%,
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },

    [NATURE_QUIRKY] =
    {
        .name = COMPOUND_STRING("QUIRKY"),
        .statUp = STAT_HP,
        .statDown = STAT_HP,
        .backAnim = 1,
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDocileNaiveQuietQuirky,
        .pokeBlockAnim = { ANIM_QUIRKY,  AFFINE_NONE },
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), // 22%, 22%,
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },

};
