#ifndef GUARD_CONSTANTS_POKEMON_H
#define GUARD_CONSTANTS_POKEMON_H

// Pokémon egg groups
#define EGG_GROUPS_PER_MON            2

enum EggGroup
{
    EGG_GROUP_NONE,
    EGG_GROUP_MONSTER,
    EGG_GROUP_WATER_1,
    EGG_GROUP_BUG,
    EGG_GROUP_FLYING,
    EGG_GROUP_FIELD,
    EGG_GROUP_FAIRY,
    EGG_GROUP_GRASS,
    EGG_GROUP_HUMAN_LIKE,
    EGG_GROUP_WATER_3,
    EGG_GROUP_MINERAL,
    EGG_GROUP_AMORPHOUS,
    EGG_GROUP_WATER_2,
    EGG_GROUP_DITTO,
    EGG_GROUP_DRAGON,
    EGG_GROUP_NO_EGGS_DISCOVERED,
};

// Pokémon natures
enum Nature
{
    NATURE_HARDY,
    NATURE_LONELY,
    NATURE_BRAVE,
    NATURE_ADAMANT,
    NATURE_NAUGHTY,
    NATURE_BOLD,
    NATURE_DOCILE,
    NATURE_RELAXED,
    NATURE_IMPISH,
    NATURE_LAX,
    NATURE_TIMID,
    NATURE_HASTY,
    NATURE_SERIOUS,
    NATURE_JOLLY,
    NATURE_NAIVE,
    NATURE_MODEST,
    NATURE_MILD,
    NATURE_QUIET,
    NATURE_BASHFUL,
    NATURE_RASH,
    NATURE_CALM,
    NATURE_GENTLE,
    NATURE_SASSY,
    NATURE_CAREFUL,
    NATURE_QUIRKY,

    NUM_NATURES
};

// Pokémon Stats
enum Stat
{
    STAT_HP,
    STAT_ATK,
    STAT_DEF,
    STAT_SPEED,
    STAT_SPATK,
    STAT_SPDEF,

    NUM_STATS,
    
    STAT_ACC = NUM_STATS,   // Only in battles.
    STAT_EVASION,           // Only in battles.

    NUM_BATTLE_STATS        // includes Accuracy and Evasion
};

#define NUM_NATURE_STATS (NUM_STATS - 1) // excludes HP

#define MIN_STAT_STAGE     0
#define DEFAULT_STAT_STAGE 6
#define MAX_STAT_STAGE    12

// Shiny odds
#define SHINY_ODDS 8 // Actual probability is SHINY_ODDS/65536

// Ribbon IDs used by TV and Pokénav
enum Ribbon
{
    CHAMPION_RIBBON,
    COOL_RIBBON_NORMAL,
    COOL_RIBBON_SUPER,
    COOL_RIBBON_HYPER,
    COOL_RIBBON_MASTER,
    BEAUTY_RIBBON_NORMAL,
    BEAUTY_RIBBON_SUPER,
    BEAUTY_RIBBON_HYPER,
    BEAUTY_RIBBON_MASTER,
    CUTE_RIBBON_NORMAL,
    CUTE_RIBBON_SUPER,
    CUTE_RIBBON_HYPER,
    CUTE_RIBBON_MASTER,
    SMART_RIBBON_NORMAL,
    SMART_RIBBON_SUPER,
    SMART_RIBBON_HYPER,
    SMART_RIBBON_MASTER,
    TOUGH_RIBBON_NORMAL,
    TOUGH_RIBBON_SUPER,
    TOUGH_RIBBON_HYPER,
    TOUGH_RIBBON_MASTER,
    WINNING_RIBBON,
    VICTORY_RIBBON,
    ARTIST_RIBBON,
    EFFORT_RIBBON,
    MARINE_RIBBON,
    LAND_RIBBON,
    SKY_RIBBON,
    COUNTRY_RIBBON,
    NATIONAL_RIBBON,
    EARTH_RIBBON,
    WORLD_RIBBON,
};


#define FIRST_GIFT_RIBBON MARINE_RIBBON
#define LAST_GIFT_RIBBON  WORLD_RIBBON
#define NUM_GIFT_RIBBONS  (1 + LAST_GIFT_RIBBON - FIRST_GIFT_RIBBON)

// The above gift ribbons (Marine - World) are
// special distribution ribbons that correspond to
// 1 bit each in the Pokémon struct. Gen 4 hard-codes
// each of these to the given name. In Gen 3 they're
// used to get an index into giftRibbons in the save block,
// which can have a value 0-64 (0 is 'no ribbon') that
// corresponds to one of the special ribbons listed
// in gGiftRibbonDescriptionPointers. Most of these were
// never distributed
#define MAX_GIFT_RIBBON 64

#define MIN_LEVEL 1
#define MAX_LEVEL 100

#define OT_ID_PLAYER_ID       0
#define OT_ID_PRESET          1
#define OT_ID_RANDOM_NO_SHINY 2

#define MON_GIVEN_TO_PARTY      0
#define MON_GIVEN_TO_PC         1
#define MON_CANT_GIVE           2

#define PLAYER_HAS_TWO_USABLE_MONS     0
#define PLAYER_HAS_ONE_MON             1
#define PLAYER_HAS_ONE_USABLE_MON      2

#define MON_ALREADY_KNOWS_MOVE  0xFFFE
#define MON_HAS_MAX_MOVES       0xFFFF

#define LEVEL_UP_MOVE_END       0xFFFF

#define MAX_LEVEL_UP_MOVES       20

#define MON_MALE       0x00
#define MON_FEMALE     0xFE
#define MON_GENDERLESS 0xFF

// Constants for AdjustFriendship
enum FriendshipEvent
{
    FRIENDSHIP_EVENT_GROW_LEVEL,
    FRIENDSHIP_EVENT_VITAMIN,           // unused, handled by PokemonUseItemEffects
    FRIENDSHIP_EVENT_BATTLE_ITEM,       // unused, handled by PokemonUseItemEffects
    FRIENDSHIP_EVENT_LEAGUE_BATTLE,
    FRIENDSHIP_EVENT_LEARN_TMHM,
    FRIENDSHIP_EVENT_WALKING,
    FRIENDSHIP_EVENT_FAINT_SMALL,
    FRIENDSHIP_EVENT_FAINT_FIELD_PSN,
    FRIENDSHIP_EVENT_FAINT_LARGE,       // If opponent was >= 30 levels higher. See AdjustFriendshipOnBattleFaint
};

// Constants for GetLeadMonFriendshipScore
enum FriendshipScore
{
    FRIENDSHIP_NONE,
    FRIENDSHIP_1_TO_49,
    FRIENDSHIP_50_TO_99,
    FRIENDSHIP_100_TO_149,
    FRIENDSHIP_150_TO_199,
    FRIENDSHIP_200_TO_254,
    FRIENDSHIP_MAX,
};

// Friendship value that the majority of species use. This was changed in Generation 8 to 50.
#define STANDARD_FRIENDSHIP 70

#define MAX_FRIENDSHIP  255
#define MAX_SHEEN       255
#define MAX_CONDITION   255

#define MAX_PER_STAT_IVS 31
#define MAX_IV_MASK 31
#define USE_RANDOM_IVS (MAX_PER_STAT_IVS + 1)
#define MAX_PER_STAT_EVS 255
#define MAX_TOTAL_EVS 510
#define EV_ITEM_RAISE_LIMIT 100

// Growth rates
enum GrowthRate
{
    GROWTH_MEDIUM_FAST,
    GROWTH_ERRATIC,
    GROWTH_FLUCTUATING,
    GROWTH_MEDIUM_SLOW,
    GROWTH_FAST,
    GROWTH_SLOW,
};

// Body colors for Pokédex search
enum BodyColor
{
    BODY_COLOR_RED,
    BODY_COLOR_BLUE,
    BODY_COLOR_YELLOW,
    BODY_COLOR_GREEN,
    BODY_COLOR_BLACK,
    BODY_COLOR_BROWN,
    BODY_COLOR_PURPLE,
    BODY_COLOR_GRAY,
    BODY_COLOR_WHITE,
    BODY_COLOR_PINK,
};

#define F_SUMMARY_SCREEN_FLIP_SPRITE 0x80

// Evolution types
enum EvolutionType
{
    EVO_NONE,
    EVO_FRIENDSHIP,         // Pokémon levels up with friendship ≥ 220
    EVO_FRIENDSHIP_DAY,     // Pokémon levels up during the day with friendship ≥ 220
    EVO_FRIENDSHIP_NIGHT,   // Pokémon levels up at night with friendship ≥ 220
    EVO_LEVEL,              // Pokémon reaches the specified level
    EVO_TRADE,              // Pokémon is traded
    EVO_TRADE_ITEM,         // Pokémon is traded while it's holding the specified item
    EVO_ITEM,               // specified item is used on Pokémon
    EVO_LEVEL_ATK_GT_DEF,   // Pokémon reaches the specified level with attack > defense
    EVO_LEVEL_ATK_EQ_DEF,   // Pokémon reaches the specified level with attack = defense
    EVO_LEVEL_ATK_LT_DEF,   // Pokémon reaches the specified level with attack < defense
    EVO_LEVEL_SILCOON,      // Pokémon reaches the specified level with a Silcoon personality value
    EVO_LEVEL_CASCOON,      // Pokémon reaches the specified level with a Cascoon personality value
    EVO_LEVEL_NINJASK,      // Pokémon reaches the specified level (special value for Ninjask)
    EVO_LEVEL_SHEDINJA,     // Pokémon reaches the specified level (special value for Shedinja)
    EVO_BEAUTY,             // Pokémon levels up with beauty ≥ specified value
};

#define EVOS_PER_MON 5

// Evolution 'modes,' for GetEvolutionTargetSpecies
enum EvolutionMode
{
    EVO_MODE_NORMAL,
    EVO_MODE_TRADE,
    EVO_MODE_ITEM_USE,
    EVO_MODE_ITEM_CHECK,    // If an Everstone is being held, still want to show that the stone *could* be used on that Pokémon to evolve
};

#define MON_PIC_WIDTH 64
#define MON_PIC_HEIGHT 64
#define MON_PIC_SIZE (MON_PIC_WIDTH * MON_PIC_HEIGHT / 2)

// Most Pokémon have 2 frames (a default and an alternate for their animation).
// There are 4 exceptions:
// - Castform has 4 frames, 1 for each form
// - Deoxys has 2 frames, 1 for each form
// - Spinda has 1 frame, presumably to avoid the work of animating its spots
// - Unown has 1 frame, presumably to avoid the work of animating all 28 of its forms
#define MAX_MON_PIC_FRAMES 4

#define BATTLE_ALIVE_EXCEPT_ACTIVE  0
#define BATTLE_ALIVE_ATK_SIDE       1
#define BATTLE_ALIVE_DEF_SIDE       2

#define SKIP_FRONT_ANIM (1 << 7)

#define NUM_ABILITY_SLOTS 2

enum PokemonJumpType
{
    PKMN_JUMP_TYPE_NONE,
    PKMN_JUMP_TYPE_NORMAL,
    PKMN_JUMP_TYPE_FAST,
    PKMN_JUMP_TYPE_SLOW,
};

// Pokémon animation function ids (for front and back)
// Each front anim uses 1, and each back anim uses a set of 3
enum Animation
{
    ANIM_V_SQUISH_AND_BOUNCE,
    ANIM_CIRCULAR_STRETCH_TWICE,
    ANIM_H_VIBRATE,
    ANIM_H_SLIDE,
    ANIM_V_SLIDE,
    ANIM_BOUNCE_ROTATE_TO_SIDES,
    ANIM_V_JUMPS_H_JUMPS,
    ANIM_ROTATE_TO_SIDES,
    ANIM_ROTATE_TO_SIDES_TWICE,
    ANIM_GROW_VIBRATE,
    ANIM_ZIGZAG_FAST,
    ANIM_SWING_CONCAVE,
    ANIM_SWING_CONCAVE_FAST,
    ANIM_SWING_CONVEX,
    ANIM_SWING_CONVEX_FAST,
    ANIM_H_SHAKE,
    ANIM_V_SHAKE,
    ANIM_CIRCULAR_VIBRATE,
    ANIM_TWIST,
    ANIM_SHRINK_GROW,
    ANIM_CIRCLE_C_CLOCKWISE,
    ANIM_GLOW_BLACK,
    ANIM_H_STRETCH,
    ANIM_V_STRETCH,
    ANIM_RISING_WOBBLE,
    ANIM_V_SHAKE_TWICE,
    ANIM_TIP_MOVE_FORWARD,
    ANIM_H_PIVOT,
    ANIM_V_SLIDE_WOBBLE,
    ANIM_H_SLIDE_WOBBLE,
    ANIM_V_JUMPS_BIG,
    ANIM_SPIN_LONG,
    ANIM_GLOW_ORANGE,
    ANIM_GLOW_RED,
    ANIM_GLOW_BLUE,
    ANIM_GLOW_YELLOW,
    ANIM_GLOW_PURPLE,
    ANIM_BACK_AND_LUNGE,
    ANIM_BACK_FLIP,
    ANIM_FLICKER,
    ANIM_BACK_FLIP_BIG,
    ANIM_FRONT_FLIP,
    ANIM_TUMBLING_FRONT_FLIP,
    ANIM_FIGURE_8,
    ANIM_FLASH_YELLOW,
    ANIM_SWING_CONCAVE_FAST_SHORT,
    ANIM_SWING_CONVEX_FAST_SHORT,
    ANIM_ROTATE_UP_SLAM_DOWN,
    ANIM_DEEP_V_SQUISH_AND_BOUNCE,
    ANIM_H_JUMPS,
    ANIM_H_JUMPS_V_STRETCH,
    ANIM_ROTATE_TO_SIDES_FAST,
    ANIM_ROTATE_UP_TO_SIDES,
    ANIM_FLICKER_INCREASING,
    ANIM_TIP_HOP_FORWARD,
    ANIM_PIVOT_SHAKE,
    ANIM_TIP_AND_SHAKE,
    ANIM_VIBRATE_TO_CORNERS,
    ANIM_GROW_IN_STAGES,
    ANIM_V_SPRING,
    ANIM_V_REPEATED_SPRING,
    ANIM_SPRING_RISING,
    ANIM_H_SPRING,
    ANIM_H_REPEATED_SPRING_SLOW,
    ANIM_H_SLIDE_SHRINK,
    ANIM_LUNGE_GROW,
    ANIM_CIRCLE_INTO_BG,
    ANIM_RAPID_H_HOPS,
    ANIM_FOUR_PETAL,
    ANIM_V_SQUISH_AND_BOUNCE_SLOW,
    ANIM_H_SLIDE_SLOW,
    ANIM_V_SLIDE_SLOW,
    ANIM_BOUNCE_ROTATE_TO_SIDES_SMALL,
    ANIM_BOUNCE_ROTATE_TO_SIDES_SLOW,
    ANIM_BOUNCE_ROTATE_TO_SIDES_SMALL_SLOW,
    ANIM_ZIGZAG_SLOW,
    ANIM_H_SHAKE_SLOW,
    ANIM_V_SHAKE_SLOW,
    ANIM_TWIST_TWICE,
    ANIM_CIRCLE_C_CLOCKWISE_SLOW,
    ANIM_V_SHAKE_TWICE_SLOW,
    ANIM_V_SLIDE_WOBBLE_SMALL,
    ANIM_V_JUMPS_SMALL,
    ANIM_SPIN,
    ANIM_TUMBLING_FRONT_FLIP_TWICE,
    ANIM_DEEP_V_SQUISH_AND_BOUNCE_TWICE,
    ANIM_H_JUMPS_V_STRETCH_TWICE,
    ANIM_V_SHAKE_BACK,
    ANIM_V_SHAKE_BACK_SLOW,
    ANIM_V_SHAKE_H_SLIDE_SLOW,
    ANIM_V_STRETCH_BOTH_ENDS_SLOW,
    ANIM_H_STRETCH_FAR_SLOW,
    ANIM_V_SHAKE_LOW_TWICE,
    ANIM_H_SHAKE_FAST,
    ANIM_H_SLIDE_FAST,
    ANIM_H_VIBRATE_FAST,
    ANIM_H_VIBRATE_FASTEST,
    ANIM_V_SHAKE_BACK_FAST,
    ANIM_V_SHAKE_LOW_TWICE_SLOW,
    ANIM_V_SHAKE_LOW_TWICE_FAST,
    ANIM_CIRCLE_C_CLOCKWISE_LONG,
    ANIM_GROW_STUTTER_SLOW,
    ANIM_V_SHAKE_H_SLIDE,
    ANIM_V_SHAKE_H_SLIDE_FAST,
    ANIM_TRIANGLE_DOWN_SLOW,
    ANIM_TRIANGLE_DOWN,
    ANIM_TRIANGLE_DOWN_TWICE,
    ANIM_GROW,
    ANIM_GROW_TWICE,
    ANIM_H_SPRING_FAST,
    ANIM_H_SPRING_SLOW,
    ANIM_H_REPEATED_SPRING_FAST,
    ANIM_H_REPEATED_SPRING,
    ANIM_SHRINK_GROW_FAST,
    ANIM_SHRINK_GROW_SLOW,
    ANIM_V_STRETCH_BOTH_ENDS,
    ANIM_V_STRETCH_BOTH_ENDS_TWICE,
    ANIM_H_STRETCH_FAR_TWICE,
    ANIM_H_STRETCH_FAR,
    ANIM_GROW_STUTTER_TWICE,
    ANIM_GROW_STUTTER,
    ANIM_CONCAVE_ARC_LARGE_SLOW,
    ANIM_CONCAVE_ARC_LARGE,
    ANIM_CONCAVE_ARC_LARGE_TWICE,
    ANIM_CONVEX_DOUBLE_ARC_SLOW,
    ANIM_CONVEX_DOUBLE_ARC,
    ANIM_CONVEX_DOUBLE_ARC_TWICE,
    ANIM_CONCAVE_ARC_SMALL_SLOW,
    ANIM_CONCAVE_ARC_SMALL,
    ANIM_CONCAVE_ARC_SMALL_TWICE,
    ANIM_H_DIP,
    ANIM_H_DIP_FAST,
    ANIM_H_DIP_TWICE,
    ANIM_SHRINK_GROW_VIBRATE_FAST,
    ANIM_SHRINK_GROW_VIBRATE,
    ANIM_SHRINK_GROW_VIBRATE_SLOW,
    ANIM_JOLT_RIGHT_FAST,
    ANIM_JOLT_RIGHT,
    ANIM_JOLT_RIGHT_SLOW,
    ANIM_SHAKE_FLASH_YELLOW_FAST,
    ANIM_SHAKE_FLASH_YELLOW,
    ANIM_SHAKE_FLASH_YELLOW_SLOW,
    ANIM_SHAKE_GLOW_RED_FAST,
    ANIM_SHAKE_GLOW_RED,
    ANIM_SHAKE_GLOW_RED_SLOW,
    ANIM_SHAKE_GLOW_GREEN_FAST,
    ANIM_SHAKE_GLOW_GREEN,
    ANIM_SHAKE_GLOW_GREEN_SLOW,
    ANIM_SHAKE_GLOW_BLUE_FAST,
    ANIM_SHAKE_GLOW_BLUE,
    ANIM_SHAKE_GLOW_BLUE_SLOW,
};

// Pokémon back animation sets
enum BackAnimation
{
    BACK_ANIM_NONE,
    BACK_ANIM_H_VIBRATE,
    BACK_ANIM_H_SLIDE,
    BACK_ANIM_H_SPRING,
    BACK_ANIM_H_SPRING_REPEATED,
    BACK_ANIM_SHRINK_GROW,
    BACK_ANIM_GROW,
    BACK_ANIM_CIRCLE_COUNTERCLOCKWISE,
    BACK_ANIM_H_SHAKE,
    BACK_ANIM_V_SHAKE,
    BACK_ANIM_V_SHAKE_H_SLIDE,
    BACK_ANIM_V_STRETCH,
    BACK_ANIM_H_STRETCH,
    BACK_ANIM_GROW_STUTTER,
    BACK_ANIM_V_SHAKE_LOW,
    BACK_ANIM_TRIANGLE_DOWN,
    BACK_ANIM_CONCAVE_ARC_LARGE,
    BACK_ANIM_CONVEX_DOUBLE_ARC,
    BACK_ANIM_CONCAVE_ARC_SMALL,
    BACK_ANIM_DIP_RIGHT_SIDE,
    BACK_ANIM_SHRINK_GROW_VIBRATE,
    BACK_ANIM_JOLT_RIGHT,
    BACK_ANIM_SHAKE_FLASH_YELLOW,
    BACK_ANIM_SHAKE_GLOW_RED,
    BACK_ANIM_SHAKE_GLOW_GREEN,
    BACK_ANIM_SHAKE_GLOW_BLUE,
};

#endif // GUARD_CONSTANTS_POKEMON_H
