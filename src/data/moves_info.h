const struct MoveInfo gMoveInfo[MOVES_COUNT] =
{
    [MOVE_NONE] =
    {
        .name = COMPOUND_STRING("-"),
        .description = COMPOUND_STRING("-"),
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 0,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .battleAnimScript = gBattleAnimMove_None,
    },

    [MOVE_POUND] =
    {
        .name = COMPOUND_STRING("POUND"),
        .description = COMPOUND_STRING(
            "Pounds the foe with\n"
            "forelegs or tail."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_POUND,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Pound,
    },

    [MOVE_KARATE_CHOP] =
    {
        .name = COMPOUND_STRING("KARATE CHOP"),
        .description = COMPOUND_STRING(
            "A chopping attack with a\n"
            "high critical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 50,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 25,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_KarateChop,
    },

    [MOVE_DOUBLE_SLAP] =
    {
        .name = COMPOUND_STRING("DOUBLESLAP"),
        .description = COMPOUND_STRING(
            "Repeatedly slaps the foe\n"
            "2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_POUND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DoubleSlap,
    },

    [MOVE_COMET_PUNCH] =
    {
        .name = COMPOUND_STRING("COMET PUNCH"),
        .description = COMPOUND_STRING(
            "Repeatedly punches the foe\n"
            "2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 18,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CometPunch,
    },

    [MOVE_MEGA_PUNCH] =
    {
        .name = COMPOUND_STRING("MEGA PUNCH"),
        .description = COMPOUND_STRING(
            "A strong punch thrown with\n"
            "incredible power."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MegaPunch,
    },

    [MOVE_PAY_DAY] =
    {
        .name = COMPOUND_STRING("PAY DAY"),
        .description = COMPOUND_STRING(
            "Throws coins at the foe.\n"
            "Money is recovered after."),
        .effect = EFFECT_PAY_DAY,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PayDay,
    },

    [MOVE_FIRE_PUNCH] =
    {
        .name = COMPOUND_STRING("FIRE PUNCH"),
        .description = COMPOUND_STRING(
            "A fiery punch that may burn\n"
            "the foe."),
        .effect = EFFECT_BURN_HIT,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_FIRE_PUNCH,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY, COMBO_STARTER_THUNDER_PUNCH, COMBO_STARTER_ICE_PUNCH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FirePunch,
    },

    [MOVE_ICE_PUNCH] =
    {
        .name = COMPOUND_STRING("ICE PUNCH"),
        .description = COMPOUND_STRING(
            "An icy punch that may\n"
            "freeze the foe."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 75,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_ICE_PUNCH,
        .contestComboMoves = {COMBO_STARTER_THUNDER_PUNCH, COMBO_STARTER_FIRE_PUNCH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_IcePunch,
    },

    [MOVE_THUNDER_PUNCH] =
    {
        .name = COMPOUND_STRING("THUNDERPUNCH"),
        .description = COMPOUND_STRING(
            "An electrified punch that\n"
            "may paralyze the foe."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 75,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_THUNDER_PUNCH,
        .contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_FIRE_PUNCH, COMBO_STARTER_ICE_PUNCH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_ThunderPunch,
    },

    [MOVE_SCRATCH] =
    {
        .name = COMPOUND_STRING("SCRATCH"),
        .description = COMPOUND_STRING(
            "Scratches the foe with\n"
            "sharp claws."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SCRATCH,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_Scratch,
    },

    [MOVE_VICE_GRIP] =
    {
        .name = COMPOUND_STRING("VICEGRIP"),
        .description = COMPOUND_STRING(
            "Grips the foe with large and\n"
            "powerful pincers."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_VICE_GRIP,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ViceGrip,
    },

    [MOVE_GUILLOTINE] =
    {
        .name = COMPOUND_STRING("GUILLOTINE"),
        .description = COMPOUND_STRING(
            "A powerful pincer attack\n"
            "that may cause fainting."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 30,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_VICE_GRIP},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Guillotine,
    },

    [MOVE_RAZOR_WIND] =
    {
        .name = COMPOUND_STRING("RAZOR WIND"),
        .description = COMPOUND_STRING(
            "A 2-turn move that strikes\n"
            "the foe on the 2nd turn."),
        .effect = EFFECT_RAZOR_WIND,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RazorWind,
    },

    [MOVE_SWORDS_DANCE] =
    {
        .name = COMPOUND_STRING("SWORDS DANCE"),
        .description = COMPOUND_STRING(
            "A fighting dance that\n"
            "sharply raises ATTACK."),
        .effect = EFFECT_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SWORDS_DANCE,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SwordsDance,
    },

    [MOVE_CUT] =
    {
        .name = COMPOUND_STRING("CUT"),
        .description = COMPOUND_STRING(
            "Cuts the foe with sharp\n"
            "scythes, claws, etc."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_Cut,
    },

    [MOVE_GUST] =
    {
        .name = COMPOUND_STRING("GUST"),
        .description = COMPOUND_STRING(
            "Strikes the foe with a gust\n"
            "of wind whipped up by wings."),
        .effect = EFFECT_GUST,
        .power = 40,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Gust,
    },

    [MOVE_WING_ATTACK] =
    {
        .name = COMPOUND_STRING("WING ATTACK"),
        .description = COMPOUND_STRING(
            "Strikes the foe with wings\n"
            "spread wide."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WingAttack,
    },

    [MOVE_WHIRLWIND] =
    {
        .name = COMPOUND_STRING("WHIRLWIND"),
        .description = COMPOUND_STRING(
            "Blows away the foe with\n"
            "wind and ends the battle."),
        .effect = EFFECT_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Whirlwind,
    },

    [MOVE_FLY] =
    {
        .name = COMPOUND_STRING("FLY"),
        .description = COMPOUND_STRING(
            "Flies up on the first turn,\n"
            "then strikes the next turn."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 70,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Fly,
    },

    [MOVE_BIND] =
    {
        .name = COMPOUND_STRING("BIND"),
        .description = COMPOUND_STRING(
            "Binds and squeezes the foe\n"
            "for 2 to 5 turns."),
        .effect = EFFECT_TRAP,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 20,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_VICE_GRIP},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Bind,
    },

    [MOVE_SLAM] =
    {
        .name = COMPOUND_STRING("SLAM"),
        .description = COMPOUND_STRING(
            "Slams the foe with a long\n"
            "tail, vine, etc."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_POUND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Slam,
    },

    [MOVE_VINE_WHIP] =
    {
        .name = COMPOUND_STRING("VINE WHIP"),
        .description = COMPOUND_STRING(
            "Strikes the foe with\n"
            "slender, whiplike vines."),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_VineWhip,
    },

    [MOVE_STOMP] =
    {
        .name = COMPOUND_STRING("STOMP"),
        .description = COMPOUND_STRING(
            "Stomps the enemy with a big\n"
            "foot. May cause flinching."),
        .effect = EFFECT_FLINCH_MINIMIZE_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,{0, COMBO_STARTER_LEER},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Stomp,
    },

    [MOVE_DOUBLE_KICK] =
    {
        .name = COMPOUND_STRING("DOUBLE KICK"),
        .description = COMPOUND_STRING(
            "A double-kicking attack\n"
            "that strikes the foe twice."),
        .effect = EFFECT_DOUBLE_HIT,
        .power = 30,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DoubleKick,
    },

    [MOVE_MEGA_KICK] =
    {
        .name = COMPOUND_STRING("MEGA KICK"),
        .description = COMPOUND_STRING(
            "An extremely powerful kick\n"
            "with intense force."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MegaKick,
    },

    [MOVE_JUMP_KICK] =
    {
        .name = COMPOUND_STRING("JUMP KICK"),
        .description = COMPOUND_STRING(
            "A strong jumping kick. May\n"
            "miss and hurt the kicker."),
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 70,
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .pp = 25,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MIND_READER},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_JumpKick,
    },

    [MOVE_ROLLING_KICK] =
    {
        .name = COMPOUND_STRING("ROLLING KICK"),
        .description = COMPOUND_STRING(
            "A fast kick delivered from\n"
            "a rapid spin."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 85,
        .pp = 15,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_RollingKick,
    },

    [MOVE_SAND_ATTACK] =
    {
        .name = COMPOUND_STRING("SAND-ATTACK"),
        .description = COMPOUND_STRING(
            "Reduces the foe's accuracy\n"
            "by hurling sand in its face."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_SAND_ATTACK,
        .contestComboMoves = {COMBO_STARTER_MUD_SLAP, COMBO_STARTER_SANDSTORM},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SandAttack,
    },

    [MOVE_HEADBUTT] =
    {
        .name = COMPOUND_STRING("HEADBUTT"),
        .description = COMPOUND_STRING(
            "A ramming attack that may\n"
            "cause flinching."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Headbutt,
    },

    [MOVE_HORN_ATTACK] =
    {
        .name = COMPOUND_STRING("HORN ATTACK"),
        .description = COMPOUND_STRING(
            "Jabs the foe with sharp\n"
            "horns."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 25,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_HORN_ATTACK,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_HornAttack,
    },

    [MOVE_FURY_ATTACK] =
    {
        .name = COMPOUND_STRING("FURY ATTACK"),
        .description = COMPOUND_STRING(
            "Jabs the foe 2 to 5 times\n"
            "with sharp horns, etc."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HORN_ATTACK, COMBO_STARTER_PECK},
        .battleAnimScript = gBattleAnimMove_FuryAttack,
    },

    [MOVE_HORN_DRILL] =
    {
        .name = COMPOUND_STRING("HORN DRILL"),
        .description = COMPOUND_STRING(
            "A one-hit KO attack that\n"
            "uses a horn like a drill."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 30,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HORN_ATTACK},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HornDrill,
    },

    [MOVE_TACKLE] =
    {
        .name = COMPOUND_STRING("TACKLE"),
        .description = COMPOUND_STRING(
            "Charges the foe with a full-\n"
            "body tackle."),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 35,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DEFENSE_CURL, COMBO_STARTER_LEER, COMBO_STARTER_HARDEN},
        .battleAnimScript = gBattleAnimMove_Tackle,
    },

    [MOVE_BODY_SLAM] =
    {
        .name = COMPOUND_STRING("BODY SLAM"),
        .description = COMPOUND_STRING(
            "A full-body slam that may\n"
            "cause paralysis."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 85,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_BodySlam,
    },

    [MOVE_WRAP] =
    {
        .name = COMPOUND_STRING("WRAP"),
        .description = COMPOUND_STRING(
            "Wraps and squeezes the foe\n"
            "2 to 5 times with vines, etc."),
        .effect = EFFECT_TRAP,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Wrap,
    },

    [MOVE_TAKE_DOWN] =
    {
        .name = COMPOUND_STRING("TAKE DOWN"),
        .description = COMPOUND_STRING(
            "A reckless charge attack\n"
            "that also hurts the user."),
        .effect = EFFECT_RECOIL,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_HARDEN},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_TakeDown,
    },

    [MOVE_THRASH] =
    {
        .name = COMPOUND_STRING("THRASH"),
        .description = COMPOUND_STRING(
            "A rampage of 2 to 3 turns\n"
            "that confuses the user."),
        .effect = EFFECT_RAMPAGE,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAGE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Thrash,
    },

    [MOVE_DOUBLE_EDGE] =
    {
        .name = COMPOUND_STRING("DOUBLE-EDGE"),
        .description = COMPOUND_STRING(
            "A life-risking tackle that\n"
            "also hurts the user."),
        .effect = EFFECT_DOUBLE_EDGE,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_HARDEN},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DoubleEdge,
    },

    [MOVE_TAIL_WHIP] =
    {
        .name = COMPOUND_STRING("TAIL WHIP"),
        .description = COMPOUND_STRING(
            "Wags the tail to lower the\n"
            "foe's DEFENSE."),
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_TailWhip,
    },

    [MOVE_POISON_STING] =
    {
        .name = COMPOUND_STRING("POISON STING"),
        .description = COMPOUND_STRING(
            "A toxic attack with barbs,\n"
            "etc., that may poison."),
        .effect = EFFECT_POISON_HIT,
        .power = 15,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 35,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonSting,
    },

    [MOVE_TWINEEDLE] =
    {
        .name = COMPOUND_STRING("TWINEEDLE"),
        .description = COMPOUND_STRING(
            "Stingers on the forelegs\n"
            "jab the foe twice."),
        .effect = EFFECT_TWINEEDLE,
        .power = 25,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Twineedle,
    },

    [MOVE_PIN_MISSILE] =
    {
        .name = COMPOUND_STRING("PIN MISSILE"),
        .description = COMPOUND_STRING(
            "Sharp pins are fired to\n"
            "strike 2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 14,
        .type = TYPE_BUG,
        .accuracy = 85,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PinMissile,
    },

    [MOVE_LEER] =
    {
        .name = COMPOUND_STRING("LEER"),
        .description = COMPOUND_STRING(
            "Frightens the foe with a\n"
            "leer to lower DEFENSE."),
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_LEER,
        .contestComboMoves = {COMBO_STARTER_RAGE, COMBO_STARTER_SCARY_FACE},
        .battleAnimScript = gBattleAnimMove_Leer,
    },

    [MOVE_BITE] =
    {
        .name = COMPOUND_STRING("BITE"),
        .description = COMPOUND_STRING(
            "Bites with vicious fangs.\n"
            "May cause flinching."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 25,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LEER, COMBO_STARTER_SCARY_FACE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Bite,
    },

    [MOVE_GROWL] =
    {
        .name = COMPOUND_STRING("GROWL"),
        .description = COMPOUND_STRING(
            "Growls cutely to reduce the\n"
            "foe's ATTACK."),
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_Growl,
    },

    [MOVE_ROAR] =
    {
        .name = COMPOUND_STRING("ROAR"),
        .description = COMPOUND_STRING(
            "Makes the foe flee to end\n"
            "the battle."),
        .effect = EFFECT_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Roar,
    },

    [MOVE_SING] =
    {
        .name = COMPOUND_STRING("SING"),
        .description = COMPOUND_STRING(
            "A soothing song lulls the\n"
            "foe into a deep slumber."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_SING,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Sing,
    },

    [MOVE_SUPERSONIC] =
    {
        .name = COMPOUND_STRING("SUPERSONIC"),
        .description = COMPOUND_STRING(
            "Emits bizarre sound waves\n"
            "that may confuse the foe."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Supersonic,
    },

    [MOVE_SONIC_BOOM] =
    {
        .name = COMPOUND_STRING("SONICBOOM"),
        .description = COMPOUND_STRING(
            "Launches shock waves that\n"
            "always inflict 20 HP damage."),
        .effect = EFFECT_SONICBOOM,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SonicBoom,
    },

    [MOVE_DISABLE] =
    {
        .name = COMPOUND_STRING("DISABLE"),
        .description = COMPOUND_STRING(
            "Psychically disables one of\n"
            "the foe's moves."),
        .effect = EFFECT_DISABLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Disable,
    },

    [MOVE_ACID] =
    {
        .name = COMPOUND_STRING("ACID"),
        .description = COMPOUND_STRING(
            "Sprays a hide-melting acid.\n"
            "May lower DEFENSE."),
        .effect = EFFECT_DEFENSE_DOWN_HIT,
        .power = 40,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Acid,
    },

    [MOVE_EMBER] =
    {
        .name = COMPOUND_STRING("EMBER"),
        .description = COMPOUND_STRING(
            "A weak fire attack that may\n"
            "inflict a burn."),
        .effect = EFFECT_BURN_HIT,
        .power = 40,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Ember,
    },

    [MOVE_FLAMETHROWER] =
    {
        .name = COMPOUND_STRING("FLAMETHROWER"),
        .description = COMPOUND_STRING(
            "A powerful fire attack that\n"
            "may inflict a burn."),
        .effect = EFFECT_BURN_HIT,
        .power = 95,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Flamethrower,
    },

    [MOVE_MIST] =
    {
        .name = COMPOUND_STRING("MIST"),
        .description = COMPOUND_STRING(
            "Creates a mist that stops\n"
            "reduction of abilities."),
        .effect = EFFECT_MIST,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Mist,
    },

    [MOVE_WATER_GUN] =
    {
        .name = COMPOUND_STRING("WATER GUN"),
        .description = COMPOUND_STRING(
            "Squirts water to attack\n"
            "the foe."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 25,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_WATER_SPORT, COMBO_STARTER_MUD_SPORT},
        .battleAnimScript = gBattleAnimMove_WaterGun,
    },

    [MOVE_HYDRO_PUMP] =
    {
        .name = COMPOUND_STRING("HYDRO PUMP"),
        .description = COMPOUND_STRING(
            "Blasts water at high power\n"
            "to strike the foe."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_WATER,
        .accuracy = 80,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HydroPump,
    },

    [MOVE_SURF] =
    {
        .name = COMPOUND_STRING("SURF"),
        .description = COMPOUND_STRING(
            "Creates a huge wave, then\n"
            "crashes it down on the foe."),
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SURF,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_DIVE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Surf,
    },

    [MOVE_ICE_BEAM] =
    {
        .name = COMPOUND_STRING("ICE BEAM"),
        .description = COMPOUND_STRING(
            "Blasts the foe with an icy\n"
            "beam that may freeze it."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 95,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_IceBeam,
    },

    [MOVE_BLIZZARD] =
    {
        .name = COMPOUND_STRING("BLIZZARD"),
        .description = COMPOUND_STRING(
            "Hits the foe with an icy\n"
            "storm that may freeze it."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 120,
        .type = TYPE_ICE,
        .accuracy = 70,
        .pp = 5,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_POWDER_SNOW, COMBO_STARTER_HAIL},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Blizzard,
    },

    [MOVE_PSYBEAM] =
    {
        .name = COMPOUND_STRING("PSYBEAM"),
        .description = COMPOUND_STRING(
            "Fires a peculiar ray that\n"
            "may confuse the foe."),
        .effect = EFFECT_CONFUSE_HIT,
        .power = 65,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Psybeam,
    },

    [MOVE_BUBBLE_BEAM] =
    {
        .name = COMPOUND_STRING("BUBBLEBEAM"),
        .description = COMPOUND_STRING(
            "Forcefully sprays bubbles\n"
            "that may lower SPEED."),
        .effect = EFFECT_SPEED_DOWN_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_BubbleBeam,
    },

    [MOVE_AURORA_BEAM] =
    {
        .name = COMPOUND_STRING("AURORA BEAM"),
        .description = COMPOUND_STRING(
            "Fires a rainbow-colored\n"
            "beam that may lower ATTACK."),
        .effect = EFFECT_ATTACK_DOWN_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AuroraBeam,
    },

    [MOVE_HYPER_BEAM] =
    {
        .name = COMPOUND_STRING("HYPER BEAM"),
        .description = COMPOUND_STRING(
            "Powerful, but leaves the\n"
            "user immobile the next turn."),
        .effect = EFFECT_RECHARGE,
        .power = 150,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HyperBeam,
    },

    [MOVE_PECK] =
    {
        .name = COMPOUND_STRING("PECK"),
        .description = COMPOUND_STRING(
            "Attacks the foe with a\n"
            "jabbing beak, etc."),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_PECK,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Peck,
    },

    [MOVE_DRILL_PECK] =
    {
        .name = COMPOUND_STRING("DRILL PECK"),
        .description = COMPOUND_STRING(
            "A corkscrewing attack with\n"
            "the beak acting as a drill."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_PECK},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DrillPeck,
    },

    [MOVE_SUBMISSION] =
    {
        .name = COMPOUND_STRING("SUBMISSION"),
        .description = COMPOUND_STRING(
            "A reckless body slam that\n"
            "also hurts the user."),
        .effect = EFFECT_RECOIL,
        .power = 80,
        .type = TYPE_FIGHTING,
        .accuracy = 80,
        .pp = 25,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MIND_READER},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Submission,
    },

    [MOVE_LOW_KICK] =
    {
        .name = COMPOUND_STRING("LOW KICK"),
        .description = COMPOUND_STRING(
            "A kick that inflicts more\n"
            "damage on heavier foes."),
        .effect = EFFECT_LOW_KICK,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_LowKick,
    },

    [MOVE_COUNTER] =
    {
        .name = COMPOUND_STRING("COUNTER"),
        .description = COMPOUND_STRING(
            "Retaliates any physical hit\n"
            "with double the power."),
        .effect = EFFECT_COUNTER,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .makesContact = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TAUNT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Counter,
    },

    [MOVE_SEISMIC_TOSS] =
    {
        .name = COMPOUND_STRING("SEISMIC TOSS"),
        .description = COMPOUND_STRING(
            "Inflicts damage identical\n"
            "to the user's level."),
        .effect = EFFECT_LEVEL_DAMAGE,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SeismicToss,
    },

    [MOVE_STRENGTH] =
    {
        .name = COMPOUND_STRING("STRENGTH"),
        .description = COMPOUND_STRING(
            "Builds enormous power,\n"
            "then slams the foe."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Strength,
    },

    [MOVE_ABSORB] =
    {
        .name = COMPOUND_STRING("ABSORB"),
        .description = COMPOUND_STRING(
            "An attack that absorbs\n"
            "half the damage inflicted."),
        .effect = EFFECT_ABSORB,
        .power = 20,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_Absorb,
    },

    [MOVE_MEGA_DRAIN] =
    {
        .name = COMPOUND_STRING("MEGA DRAIN"),
        .description = COMPOUND_STRING(
            "An attack that absorbs\n"
            "half the damage inflicted."),
        .effect = EFFECT_ABSORB,
        .power = 40,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_MegaDrain,
    },

    [MOVE_LEECH_SEED] =
    {
        .name = COMPOUND_STRING("LEECH SEED"),
        .description = COMPOUND_STRING(
            "Plants a seed on the foe to\n"
            "steal HP on every turn."),
        .effect = EFFECT_LEECH_SEED,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_LeechSeed,
    },

    [MOVE_GROWTH] =
    {
        .name = COMPOUND_STRING("GROWTH"),
        .description = COMPOUND_STRING(
            "Forces the body to grow\n"
            "and heightens SP. ATK."),
        .effect = EFFECT_SPECIAL_ATTACK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_GROWTH,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Growth,
    },

    [MOVE_RAZOR_LEAF] =
    {
        .name = COMPOUND_STRING("RAZOR LEAF"),
        .description = COMPOUND_STRING(
            "Cuts the enemy with leaves.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 55,
        .type = TYPE_GRASS,
        .accuracy = 95,
        .pp = 25,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_RazorLeaf,
    },

    [MOVE_SOLAR_BEAM] =
    {
        .name = COMPOUND_STRING("SOLARBEAM"),
        .description = COMPOUND_STRING(
            "Absorbs light in one turn,\n"
            "then attacks next turn."),
        .effect = EFFECT_SOLAR_BEAM,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY, COMBO_STARTER_GROWTH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SolarBeam,
    },

    [MOVE_POISON_POWDER] =
    {
        .name = COMPOUND_STRING("POISONPOWDER"),
        .description = COMPOUND_STRING(
            "Scatters a toxic powder\n"
            "that may poison the foe."),
        .effect = EFFECT_POISON,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 75,
        .pp = 35,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_PoisonPowder,
    },

    [MOVE_STUN_SPORE] =
    {
        .name = COMPOUND_STRING("STUN SPORE"),
        .description = COMPOUND_STRING(
            "Scatters a powder that may\n"
            "paralyze the foe."),
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_StunSpore,
    },

    [MOVE_SLEEP_POWDER] =
    {
        .name = COMPOUND_STRING("SLEEP POWDER"),
        .description = COMPOUND_STRING(
            "Scatters a powder that may\n"
            "cause the foe to sleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SleepPowder,
    },

    [MOVE_PETAL_DANCE] =
    {
        .name = COMPOUND_STRING("PETAL DANCE"),
        .description = COMPOUND_STRING(
            "A rampage of 2 to 3 turns\n"
            "that confuses the user."),
        .effect = EFFECT_RAMPAGE,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_PetalDance,
    },

    [MOVE_STRING_SHOT] =
    {
        .name = COMPOUND_STRING("STRING SHOT"),
        .description = COMPOUND_STRING(
            "Binds the foe with string\n"
            "to reduce its SPEED."),
        .effect = EFFECT_SPEED_DOWN,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_STRING_SHOT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StringShot,
    },

    [MOVE_DRAGON_RAGE] =
    {
        .name = COMPOUND_STRING("DRAGON RAGE"),
        .description = COMPOUND_STRING(
            "Launches shock waves that\n"
            "always inflict 40 HP damage."),
        .effect = EFFECT_DRAGON_RAGE,
        .power = 1,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DRAGON_RAGE,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DragonRage,
    },

    [MOVE_FIRE_SPIN] =
    {
        .name = COMPOUND_STRING("FIRE SPIN"),
        .description = COMPOUND_STRING(
            "Traps the foe in a ring of\n"
            "fire for 2 to 5 turns."),
        .effect = EFFECT_TRAP,
        .power = 15,
        .type = TYPE_FIRE,
        .accuracy = 70,
        .pp = 15,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FireSpin,
    },

    [MOVE_THUNDER_SHOCK] =
    {
        .name = COMPOUND_STRING("THUNDERSHOCK"),
        .description = COMPOUND_STRING(
            "An electrical attack that\n"
            "may paralyze the foe."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 40,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_ThunderShock,
    },

    [MOVE_THUNDERBOLT] =
    {
        .name = COMPOUND_STRING("THUNDERBOLT"),
        .description = COMPOUND_STRING(
            "A strong electrical attack\n"
            "that may paralyze the foe."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 95,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Thunderbolt,
    },

    [MOVE_THUNDER_WAVE] =
    {
        .name = COMPOUND_STRING("THUNDER WAVE"),
        .description = COMPOUND_STRING(
            "A weak jolt of electricity\n"
            "that paralyzes the foe."),
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_ThunderWave,
    },

    [MOVE_THUNDER] =
    {
        .name = COMPOUND_STRING("THUNDER"),
        .description = COMPOUND_STRING(
            "A lightning attack that may\n"
            "cause paralysis."),
        .effect = EFFECT_THUNDER,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 70,
        .pp = 10,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_LOCK_ON},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Thunder,
    },

    [MOVE_ROCK_THROW] =
    {
        .name = COMPOUND_STRING("ROCK THROW"),
        .description = COMPOUND_STRING(
            "Throws small rocks to\n"
            "strike the foe."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_ROCK_THROW,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockThrow,
    },

    [MOVE_EARTHQUAKE] =
    {
        .name = COMPOUND_STRING("EARTHQUAKE"),
        .description = COMPOUND_STRING(
            "A powerful quake, but has\n"
            "no effect on flying foes."),
        .effect = EFFECT_EARTHQUAKE,
        .power = 100,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_EARTHQUAKE,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Earthquake,
    },

    [MOVE_FISSURE] =
    {
        .name = COMPOUND_STRING("FISSURE"),
        .description = COMPOUND_STRING(
            "A one-hit KO move that\n"
            "drops the foe in a fissure."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 30,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_EARTHQUAKE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Fissure,
    },

    [MOVE_DIG] =
    {
        .name = COMPOUND_STRING("DIG"),
        .description = COMPOUND_STRING(
            "Digs underground the first\n"
            "turn and strikes next turn."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 60,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Dig,
    },

    [MOVE_TOXIC] =
    {
        .name = COMPOUND_STRING("TOXIC"),
        .description = COMPOUND_STRING(
            "Poisons the foe with an\n"
            "intensifying toxin."),
        .effect = EFFECT_TOXIC,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 85,
        .pp = 10,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Toxic,
    },

    [MOVE_CONFUSION] =
    {
        .name = COMPOUND_STRING("CONFUSION"),
        .description = COMPOUND_STRING(
            "A psychic attack that may\n"
            "cause confusion."),
        .effect = EFFECT_CONFUSE_HIT,
        .power = 50,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 25,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_CONFUSION,
        .contestComboMoves = {COMBO_STARTER_PSYCHIC, COMBO_STARTER_KINESIS, COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_Confusion,
    },

    [MOVE_PSYCHIC] =
    {
        .name = COMPOUND_STRING("PSYCHIC"),
        .description = COMPOUND_STRING(
            "A powerful psychic attack\n"
            "that may lower SP. DEF."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_HIT,
        .power = 90,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_PSYCHIC,
        .contestComboMoves = {COMBO_STARTER_KINESIS, COMBO_STARTER_CONFUSION, COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Psychic,
    },

    [MOVE_HYPNOSIS] =
    {
        .name = COMPOUND_STRING("HYPNOSIS"),
        .description = COMPOUND_STRING(
            "A hypnotizing move that\n"
            "may induce sleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 60,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_HYPNOSIS,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Hypnosis,
    },

    [MOVE_MEDITATE] =
    {
        .name = COMPOUND_STRING("MEDITATE"),
        .description = COMPOUND_STRING(
            "Meditates in a peaceful\n"
            "fashion to raise ATTACK."),
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Meditate,
    },

    [MOVE_AGILITY] =
    {
        .name = COMPOUND_STRING("AGILITY"),
        .description = COMPOUND_STRING(
            "Relaxes the body to sharply\n"
            "boost SPEED."),
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DOUBLE_TEAM},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Agility,
    },

    [MOVE_QUICK_ATTACK] =
    {
        .name = COMPOUND_STRING("QUICK ATTACK"),
        .description = COMPOUND_STRING(
            "An extremely fast attack\n"
            "that always strikes first."),
        .effect = EFFECT_QUICK_ATTACK,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DOUBLE_TEAM},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_QuickAttack,
    },

    [MOVE_RAGE] =
    {
        .name = COMPOUND_STRING("RAGE"),
        .description = COMPOUND_STRING(
            "Raises the user's ATTACK\n"
            "every time it is hit."),
        .effect = EFFECT_RAGE,
        .power = 20,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_RAGE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Rage,
    },

    [MOVE_TELEPORT] =
    {
        .name = COMPOUND_STRING("TELEPORT"),
        .description = COMPOUND_STRING(
            "A psychic move for fleeing\n"
            "from battle instantly."),
        .effect = EFFECT_TELEPORT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DOUBLE_TEAM, COMBO_STARTER_PSYCHIC, COMBO_STARTER_KINESIS, COMBO_STARTER_CONFUSION},
        .battleAnimScript = gBattleAnimMove_Teleport,
    },

    [MOVE_NIGHT_SHADE] =
    {
        .name = COMPOUND_STRING("NIGHT SHADE"),
        .description = COMPOUND_STRING(
            "Inflicts damage identical\n"
            "to the user's level."),
        .effect = EFFECT_LEVEL_DAMAGE,
        .power = 1,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_NightShade,
    },

    [MOVE_MIMIC] =
    {
        .name = COMPOUND_STRING("MIMIC"),
        .description = COMPOUND_STRING(
            "Copies a move used by the\n"
            "foe during one battle."),
        .effect = EFFECT_MIMIC,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Mimic,
    },

    [MOVE_SCREECH] =
    {
        .name = COMPOUND_STRING("SCREECH"),
        .description = COMPOUND_STRING(
            "Emits a screech to sharply\n"
            "reduce the foe's DEFENSE."),
        .effect = EFFECT_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Screech,
    },

    [MOVE_DOUBLE_TEAM] =
    {
        .name = COMPOUND_STRING("DOUBLE TEAM"),
        .description = COMPOUND_STRING(
            "Creates illusory copies to\n"
            "raise evasiveness."),
        .effect = EFFECT_EVASION_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DOUBLE_TEAM,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DoubleTeam,
    },

    [MOVE_RECOVER] =
    {
        .name = COMPOUND_STRING("RECOVER"),
        .description = COMPOUND_STRING(
            "Recovers up to half the\n"
            "user's maximum HP."),
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Recover,
    },

    [MOVE_HARDEN] =
    {
        .name = COMPOUND_STRING("HARDEN"),
        .description = COMPOUND_STRING(
            "Stiffens the body's \n"
            "muscles to raise DEFENSE."),
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_HARDEN,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Harden,
    },

    [MOVE_MINIMIZE] =
    {
        .name = COMPOUND_STRING("MINIMIZE"),
        .description = COMPOUND_STRING(
            "Minimizes the user's size\n"
            "to raise evasiveness."),
        .effect = EFFECT_MINIMIZE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Minimize,
    },

    [MOVE_SMOKESCREEN] =
    {
        .name = COMPOUND_STRING("SMOKESCREEN"),
        .description = COMPOUND_STRING(
            "Lowers the foe's accuracy\n"
            "using smoke, ink, etc."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SMOG},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Smokescreen,
    },

    [MOVE_CONFUSE_RAY] =
    {
        .name = COMPOUND_STRING("CONFUSE RAY"),
        .description = COMPOUND_STRING(
            "A sinister ray that\n"
            "confuses the foe."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_ConfuseRay,
    },

    [MOVE_WITHDRAW] =
    {
        .name = COMPOUND_STRING("WITHDRAW"),
        .description = COMPOUND_STRING(
            "Withdraws the body into its\n"
            "hard shell to raise DEFENSE."),
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Withdraw,
    },

    [MOVE_DEFENSE_CURL] =
    {
        .name = COMPOUND_STRING("DEFENSE CURL"),
        .description = COMPOUND_STRING(
            "Curls up to conceal weak\n"
            "spots and raise DEFENSE."),
        .effect = EFFECT_DEFENSE_CURL,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_DEFENSE_CURL,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DefenseCurl,
    },

    [MOVE_BARRIER] =
    {
        .name = COMPOUND_STRING("BARRIER"),
        .description = COMPOUND_STRING(
            "Creates a barrier that\n"
            "sharply raises DEFENSE."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Barrier,
    },

    [MOVE_LIGHT_SCREEN] =
    {
        .name = COMPOUND_STRING("LIGHT SCREEN"),
        .description = COMPOUND_STRING(
            "Creates a wall of light that\n"
            "lowers SP. ATK damage."),
        .effect = EFFECT_LIGHT_SCREEN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_LightScreen,
    },

    [MOVE_HAZE] =
    {
        .name = COMPOUND_STRING("HAZE"),
        .description = COMPOUND_STRING(
            "Creates a black haze that\n"
            "eliminates all stat changes."),
        .effect = EFFECT_HAZE,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .protectAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Haze,
    },

    [MOVE_REFLECT] =
    {
        .name = COMPOUND_STRING("REFLECT"),
        .description = COMPOUND_STRING(
            "Creates a wall of light that\n"
            "weakens physical attacks."),
        .effect = EFFECT_REFLECT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Reflect,
    },

    [MOVE_FOCUS_ENERGY] =
    {
        .name = COMPOUND_STRING("FOCUS ENERGY"),
        .description = COMPOUND_STRING(
            "Focuses power to raise the\n"
            "critical-hit ratio."),
        .effect = EFFECT_FOCUS_ENERGY,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_FOCUS_ENERGY,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FocusEnergy,
    },

    [MOVE_BIDE] =
    {
        .name = COMPOUND_STRING("BIDE"),
        .description = COMPOUND_STRING(
            "Endures attack for 2\n"
            "turns to retaliate double."),
        .effect = EFFECT_BIDE,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Bide,
    },

    [MOVE_METRONOME] =
    {
        .name = COMPOUND_STRING("METRONOME"),
        .description = COMPOUND_STRING(
            "Waggles a finger to use any\n"
            "POKéMON move at random."),
        .effect = EFFECT_METRONOME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Metronome,
    },

    [MOVE_MIRROR_MOVE] =
    {
        .name = COMPOUND_STRING("MIRROR MOVE"),
        .description = COMPOUND_STRING(
            "Counters the foe's attack\n"
            "with the same move."),
        .effect = EFFECT_MIRROR_MOVE,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MirrorMove,
    },

    [MOVE_SELF_DESTRUCT] =
    {
        .name = COMPOUND_STRING("SELFDESTRUCT"),
        .description = COMPOUND_STRING(
            "Inflicts severe damage but\n"
            "makes the user faint."),
        .effect = EFFECT_EXPLOSION,
        .power = 200,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SelfDestruct,
    },

    [MOVE_EGG_BOMB] =
    {
        .name = COMPOUND_STRING("EGG BOMB"),
        .description = COMPOUND_STRING(
            "An egg is forcibly hurled at\n"
            "the foe."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SOFT_BOILED},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_EggBomb,
    },

    [MOVE_LICK] =
    {
        .name = COMPOUND_STRING("LICK"),
        .description = COMPOUND_STRING(
            "Licks with a long tongue to\n"
            "injure. May also paralyze."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 20,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Lick,
    },

    [MOVE_SMOG] =
    {
        .name = COMPOUND_STRING("SMOG"),
        .description = COMPOUND_STRING(
            "An exhaust-gas attack\n"
            "that may also poison."),
        .effect = EFFECT_POISON_HIT,
        .power = 20,
        .type = TYPE_POISON,
        .accuracy = 70,
        .pp = 20,
        .secondaryEffectChance = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SMOG,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Smog,
    },

    [MOVE_SLUDGE] =
    {
        .name = COMPOUND_STRING("SLUDGE"),
        .description = COMPOUND_STRING(
            "Sludge is hurled to inflict\n"
            "damage. May also poison."),
        .effect = EFFECT_POISON_HIT,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SLUDGE,
        .contestComboMoves = {COMBO_STARTER_SLUDGE_BOMB},
        .battleAnimScript = gBattleAnimMove_Sludge,
    },

    [MOVE_BONE_CLUB] =
    {
        .name = COMPOUND_STRING("BONE CLUB"),
        .description = COMPOUND_STRING(
            "Clubs the foe with a bone.\n"
            "May cause flinching."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 65,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 20,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_BONE_CLUB,
        .contestComboMoves = {COMBO_STARTER_BONEMERANG, COMBO_STARTER_BONE_RUSH},
        .battleAnimScript = gBattleAnimMove_BoneClub,
    },

    [MOVE_FIRE_BLAST] =
    {
        .name = COMPOUND_STRING("FIRE BLAST"),
        .description = COMPOUND_STRING(
            "Incinerates everything it\n"
            "strikes. May cause a burn."),
        .effect = EFFECT_BURN_HIT,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 5,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FireBlast,
    },

    [MOVE_WATERFALL] =
    {
        .name = COMPOUND_STRING("WATERFALL"),
        .description = COMPOUND_STRING(
            "Charges the foe with speed\n"
            "to climb waterfalls."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Waterfall,
    },

    [MOVE_CLAMP] =
    {
        .name = COMPOUND_STRING("CLAMP"),
        .description = COMPOUND_STRING(
            "Traps and squeezes the\n"
            "foe for 2 to 5 turns."),
        .effect = EFFECT_TRAP,
        .power = 35,
        .type = TYPE_WATER,
        .accuracy = 75,
        .pp = 10,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Clamp,
    },

    [MOVE_SWIFT] =
    {
        .name = COMPOUND_STRING("SWIFT"),
        .description = COMPOUND_STRING(
            "Sprays star-shaped rays\n"
            "that never miss."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Swift,
    },

    [MOVE_SKULL_BASH] =
    {
        .name = COMPOUND_STRING("SKULL BASH"),
        .description = COMPOUND_STRING(
            "Tucks in the head, then\n"
            "attacks on the next turn."),
        .effect = EFFECT_SKULL_BASH,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SkullBash,
    },

    [MOVE_SPIKE_CANNON] =
    {
        .name = COMPOUND_STRING("SPIKE CANNON"),
        .description = COMPOUND_STRING(
            "Launches sharp spikes that\n"
            "strike 2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 20,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SpikeCannon,
    },

    [MOVE_CONSTRICT] =
    {
        .name = COMPOUND_STRING("CONSTRICT"),
        .description = COMPOUND_STRING(
            "Constricts to inflict pain.\n"
            "May lower SPEED."),
        .effect = EFFECT_SPEED_DOWN_HIT,
        .power = 10,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Constrict,
    },

    [MOVE_AMNESIA] =
    {
        .name = COMPOUND_STRING("AMNESIA"),
        .description = COMPOUND_STRING(
            "Forgets about something\n"
            "and sharply raises SP. DEF."),
        .effect = EFFECT_SPECIAL_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Amnesia,
    },

    [MOVE_KINESIS] =
    {
        .name = COMPOUND_STRING("KINESIS"),
        .description = COMPOUND_STRING(
            "Distracts the foe.\n"
            "May lower accuracy."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 80,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_KINESIS,
        .contestComboMoves = {COMBO_STARTER_PSYCHIC, COMBO_STARTER_CONFUSION},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Kinesis,
    },

    [MOVE_SOFT_BOILED] =
    {
        .name = COMPOUND_STRING("SOFTBOILED"),
        .description = COMPOUND_STRING(
            "Recovers up to half the\n"
            "user's maximum HP."),
        .effect = EFFECT_SOFTBOILED,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SOFT_BOILED,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SoftBoiled,
    },

    [MOVE_HI_JUMP_KICK] =
    {
        .name = COMPOUND_STRING("HI JUMP KICK"),
        .description = COMPOUND_STRING(
            "A jumping knee kick. If it\n"
            "misses, the user is hurt."),
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 85,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MIND_READER},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HiJumpKick,
    },

    [MOVE_GLARE] =
    {
        .name = COMPOUND_STRING("GLARE"),
        .description = COMPOUND_STRING(
            "Intimidates and frightens\n"
            "the foe into paralysis."),
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Glare,
    },

    [MOVE_DREAM_EATER] =
    {
        .name = COMPOUND_STRING("DREAM EATER"),
        .description = COMPOUND_STRING(
            "Takes one half the damage\n"
            "inflicted on a sleeping foe."),
        .effect = EFFECT_DREAM_EATER,
        .power = 100,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HYPNOSIS, COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DreamEater,
    },

    [MOVE_POISON_GAS] =
    {
        .name = COMPOUND_STRING("POISON GAS"),
        .description = COMPOUND_STRING(
            "Envelops the foe in a toxic\n"
            "gas that may poison."),
        .effect = EFFECT_POISON,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 55,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonGas,
    },

    [MOVE_BARRAGE] =
    {
        .name = COMPOUND_STRING("BARRAGE"),
        .description = COMPOUND_STRING(
            "Hurls round objects at the\n"
            "foe 2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Barrage,
    },

    [MOVE_LEECH_LIFE] =
    {
        .name = COMPOUND_STRING("LEECH LIFE"),
        .description = COMPOUND_STRING(
            "An attack that steals half\n"
            "the damage inflicted."),
        .effect = EFFECT_ABSORB,
        .power = 20,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LeechLife,
    },

    [MOVE_LOVELY_KISS] =
    {
        .name = COMPOUND_STRING("LOVELY KISS"),
        .description = COMPOUND_STRING(
            "Demands a kiss with a scary\n"
            "face that induces sleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_LovelyKiss,
    },

    [MOVE_SKY_ATTACK] =
    {
        .name = COMPOUND_STRING("SKY ATTACK"),
        .description = COMPOUND_STRING(
            "Searches out weak spots,\n"
            "then strikes the next turn."),
        .effect = EFFECT_SKY_ATTACK,
        .power = 140,
        .type = TYPE_FLYING,
        .accuracy = 90,
        .pp = 5,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SkyAttack,
    },

    [MOVE_TRANSFORM] =
    {
        .name = COMPOUND_STRING("TRANSFORM"),
        .description = COMPOUND_STRING(
            "Alters the user's cells to\n"
            "become a copy of the foe."),
        .effect = EFFECT_TRANSFORM,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Transform,
    },

    [MOVE_BUBBLE] =
    {
        .name = COMPOUND_STRING("BUBBLE"),
        .description = COMPOUND_STRING(
            "An attack using bubbles.\n"
            "May lower the foe's SPEED."),
        .effect = EFFECT_SPEED_DOWN_HIT,
        .power = 20,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Bubble,
    },

    [MOVE_DIZZY_PUNCH] =
    {
        .name = COMPOUND_STRING("DIZZY PUNCH"),
        .description = COMPOUND_STRING(
            "A rhythmic punch that may\n"
            "confuse the foe."),
        .effect = EFFECT_CONFUSE_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DizzyPunch,
    },

    [MOVE_SPORE] =
    {
        .name = COMPOUND_STRING("SPORE"),
        .description = COMPOUND_STRING(
            "Scatters a cloud of spores\n"
            "that always induce sleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Spore,
    },

    [MOVE_FLASH] =
    {
        .name = COMPOUND_STRING("FLASH"),
        .description = COMPOUND_STRING(
            "Looses a powerful blast of\n"
            "light that cuts accuracy."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 70,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Flash,
    },

    [MOVE_PSYWAVE] =
    {
        .name = COMPOUND_STRING("PSYWAVE"),
        .description = COMPOUND_STRING(
            "Attacks with a psychic\n"
            "wave of varying intensity."),
        .effect = EFFECT_PSYWAVE,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = 80,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Psywave,
    },

    [MOVE_SPLASH] =
    {
        .name = COMPOUND_STRING("SPLASH"),
        .description = COMPOUND_STRING(
            "It's just a splash...\n"
            "Has no effect whatsoever."),
        .effect = EFFECT_SPLASH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Splash,
    },

    [MOVE_ACID_ARMOR] =
    {
        .name = COMPOUND_STRING("ACID ARMOR"),
        .description = COMPOUND_STRING(
            "Liquifies the user's body\n"
            "to sharply raise DEFENSE."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_AcidArmor,
    },

    [MOVE_CRABHAMMER] =
    {
        .name = COMPOUND_STRING("CRABHAMMER"),
        .description = COMPOUND_STRING(
            "Hammers with a pincer. Has a\n"
            "high critical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SWORDS_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Crabhammer,
    },

    [MOVE_EXPLOSION] =
    {
        .name = COMPOUND_STRING("EXPLOSION"),
        .description = COMPOUND_STRING(
            "Inflicts severe damage but\n"
            "makes the user faint."),
        .effect = EFFECT_EXPLOSION,
        .power = 250,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Explosion,
    },

    [MOVE_FURY_SWIPES] =
    {
        .name = COMPOUND_STRING("FURY SWIPES"),
        .description = COMPOUND_STRING(
            "Rakes the foe with sharp\n"
            "claws, etc., 2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 18,
        .type = TYPE_NORMAL,
        .accuracy = 80,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCRATCH},
        .battleAnimScript = gBattleAnimMove_FurySwipes,
    },

    [MOVE_BONEMERANG] =
    {
        .name = COMPOUND_STRING("BONEMERANG"),
        .description = COMPOUND_STRING(
            "Throws a bone boomerang\n"
            "that strikes twice."),
        .effect = EFFECT_DOUBLE_HIT,
        .power = 50,
        .type = TYPE_GROUND,
        .accuracy = 90,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_BONEMERANG,
        .contestComboMoves = {COMBO_STARTER_BONE_CLUB, COMBO_STARTER_BONE_RUSH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Bonemerang,
    },

    [MOVE_REST] =
    {
        .name = COMPOUND_STRING("REST"),
        .description = COMPOUND_STRING(
            "The user sleeps for 2 turns,\n"
            "restoring HP and status."),
        .effect = EFFECT_REST,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_REST,
        .contestComboMoves = {COMBO_STARTER_BELLY_DRUM, COMBO_STARTER_CHARM, COMBO_STARTER_YAWN},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Rest,
    },

    [MOVE_ROCK_SLIDE] =
    {
        .name = COMPOUND_STRING("ROCK SLIDE"),
        .description = COMPOUND_STRING(
            "Large boulders are hurled.\n"
            "May cause flinching."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 75,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 10,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ROCK_THROW},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_RockSlide,
    },

    [MOVE_HYPER_FANG] =
    {
        .name = COMPOUND_STRING("HYPER FANG"),
        .description = COMPOUND_STRING(
            "Attacks with sharp fangs.\n"
            "May cause flinching."),
        .effect = EFFECT_FLINCH_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HyperFang,
    },

    [MOVE_SHARPEN] =
    {
        .name = COMPOUND_STRING("SHARPEN"),
        .description = COMPOUND_STRING(
            "Reduces the polygon count\n"
            "and raises ATTACK."),
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Sharpen,
    },

    [MOVE_CONVERSION] =
    {
        .name = COMPOUND_STRING("CONVERSION"),
        .description = COMPOUND_STRING(
            "Changes the user's type\n"
            "into a known move's type."),
        .effect = EFFECT_CONVERSION,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Conversion,
    },

    [MOVE_TRI_ATTACK] =
    {
        .name = COMPOUND_STRING("TRI ATTACK"),
        .description = COMPOUND_STRING(
            "Fires three types of beams\n"
            "at the same time."),
        .effect = EFFECT_TRI_ATTACK,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOCK_ON},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_TriAttack,
    },

    [MOVE_SUPER_FANG] =
    {
        .name = COMPOUND_STRING("SUPER FANG"),
        .description = COMPOUND_STRING(
            "Attacks with sharp fangs\n"
            "and cuts half the foe's HP."),
        .effect = EFFECT_SUPER_FANG,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCARY_FACE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SuperFang,
    },

    [MOVE_SLASH] =
    {
        .name = COMPOUND_STRING("SLASH"),
        .description = COMPOUND_STRING(
            "Slashes with claws, etc. Has\n"
            "a high critical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE, COMBO_STARTER_SCRATCH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Slash,
    },

    [MOVE_SUBSTITUTE] =
    {
        .name = COMPOUND_STRING("SUBSTITUTE"),
        .description = COMPOUND_STRING(
            "Creates a decoy using 1/4\n"
            "of the user's maximum HP."),
        .effect = EFFECT_SUBSTITUTE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Substitute,
    },

    [MOVE_STRUGGLE] =
    {
        .name = COMPOUND_STRING("STRUGGLE"),
        .description = COMPOUND_STRING(
            "Used only if all PP are gone.\n"
            "Also hurts the user a little."),
        .effect = EFFECT_RECOIL,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 1,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Struggle,
    },

    [MOVE_SKETCH] =
    {
        .name = COMPOUND_STRING("SKETCH"),
        .description = COMPOUND_STRING(
            "Copies the foe's last move\n"
            "permanently."),
        .effect = EFFECT_SKETCH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Sketch,
    },

    [MOVE_TRIPLE_KICK] =
    {
        .name = COMPOUND_STRING("TRIPLE KICK"),
        .description = COMPOUND_STRING(
            "Kicks the foe 3 times in a\n"
            "row with rising intensity."),
        .effect = EFFECT_TRIPLE_KICK,
        .power = 10,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_TripleKick,
    },

    [MOVE_THIEF] =
    {
        .name = COMPOUND_STRING("THIEF"),
        .description = COMPOUND_STRING(
            "While attacking, it may\n"
            "steal the foe's held item."),
        .effect = EFFECT_THIEF,
        .power = 40,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Thief,
    },

    [MOVE_SPIDER_WEB] =
    {
        .name = COMPOUND_STRING("SPIDER WEB"),
        .description = COMPOUND_STRING(
            "Ensnares the foe to stop it\n"
            "from fleeing or switching."),
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STRING_SHOT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SpiderWeb,
    },

    [MOVE_MIND_READER] =
    {
        .name = COMPOUND_STRING("MIND READER"),
        .description = COMPOUND_STRING(
            "Senses the foe's action to\n"
            "ensure the next move's hit."),
        .effect = EFFECT_LOCK_ON,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_MIND_READER,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MindReader,
    },

    [MOVE_NIGHTMARE] =
    {
        .name = COMPOUND_STRING("NIGHTMARE"),
        .description = COMPOUND_STRING(
            "Inflicts 1/4 damage on a\n"
            "sleeping foe every turn."),
        .effect = EFFECT_NIGHTMARE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HYPNOSIS},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Nightmare,
    },

    [MOVE_FLAME_WHEEL] =
    {
        .name = COMPOUND_STRING("FLAME WHEEL"),
        .description = COMPOUND_STRING(
            "A fiery charge attack that\n"
            "may inflict a burn."),
        .effect = EFFECT_THAW_HIT,
        .power = 60,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_FlameWheel,
    },

    [MOVE_SNORE] =
    {
        .name = COMPOUND_STRING("SNORE"),
        .description = COMPOUND_STRING(
            "A loud attack that can be\n"
            "used only while asleep."),
        .effect = EFFECT_SNORE,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_REST},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Snore,
    },

    [MOVE_CURSE] =
    {
        .name = COMPOUND_STRING("CURSE"),
        .description = COMPOUND_STRING(
            "A move that functions\n"
            "differently for GHOSTS."),
        .effect = EFFECT_CURSE,
        .power = 0,
        .type = TYPE_MYSTERY,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_CURSE,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Curse,
    },

    [MOVE_FLAIL] =
    {
        .name = COMPOUND_STRING("FLAIL"),
        .description = COMPOUND_STRING(
            "Inflicts more damage when\n"
            "the user's HP is down."),
        .effect = EFFECT_FLAIL,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Flail,
    },

    [MOVE_CONVERSION_2] =
    {
        .name = COMPOUND_STRING("CONVERSION 2"),
        .description = COMPOUND_STRING(
            "Makes the user resistant\n"
            "to the last attack's type."),
        .effect = EFFECT_CONVERSION_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Conversion2,
    },

    [MOVE_AEROBLAST] =
    {
        .name = COMPOUND_STRING("AEROBLAST"),
        .description = COMPOUND_STRING(
            "Launches a vacuumed blast.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 100,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Aeroblast,
    },

    [MOVE_COTTON_SPORE] =
    {
        .name = COMPOUND_STRING("COTTON SPORE"),
        .description = COMPOUND_STRING(
            "Spores cling to the foe,\n"
            "sharply reducing SPEED."),
        .effect = EFFECT_SPEED_DOWN_2,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 85,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_CottonSpore,
    },

    [MOVE_REVERSAL] =
    {
        .name = COMPOUND_STRING("REVERSAL"),
        .description = COMPOUND_STRING(
            "Inflicts more damage when\n"
            "the user's HP is down."),
        .effect = EFFECT_FLAIL,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Reversal,
    },

    [MOVE_SPITE] =
    {
        .name = COMPOUND_STRING("SPITE"),
        .description = COMPOUND_STRING(
            "Spitefully cuts the PP\n"
            "of the foe's last move."),
        .effect = EFFECT_SPITE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CURSE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Spite,
    },

    [MOVE_POWDER_SNOW] =
    {
        .name = COMPOUND_STRING("POWDER SNOW"),
        .description = COMPOUND_STRING(
            "Blasts the foe with a snowy\n"
            "gust. May cause freezing."),
        .effect = EFFECT_FREEZE_HIT,
        .power = 40,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 25,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_POWDER_SNOW,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_PowderSnow,
    },

    [MOVE_PROTECT] =
    {
        .name = COMPOUND_STRING("PROTECT"),
        .description = COMPOUND_STRING(
            "Evades attack, but may fail\n"
            "if used in succession."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HARDEN},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Protect,
    },

    [MOVE_MACH_PUNCH] =
    {
        .name = COMPOUND_STRING("MACH PUNCH"),
        .description = COMPOUND_STRING(
            "A punch is thrown at wicked\n"
            "speed to strike first."),
        .effect = EFFECT_QUICK_ATTACK,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MachPunch,
    },

    [MOVE_SCARY_FACE] =
    {
        .name = COMPOUND_STRING("SCARY FACE"),
        .description = COMPOUND_STRING(
            "Frightens with a scary face\n"
            "to sharply reduce SPEED."),
        .effect = EFFECT_SPEED_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SCARY_FACE,
        .contestComboMoves = {COMBO_STARTER_RAGE, COMBO_STARTER_LEER},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_ScaryFace,
    },

    [MOVE_FAINT_ATTACK] =
    {
        .name = COMPOUND_STRING("FAINT ATTACK"),
        .description = COMPOUND_STRING(
            "Draws the foe close, then\n"
            "strikes without fail."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT, COMBO_STARTER_LEER, COMBO_STARTER_POUND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FaintAttack,
    },

    [MOVE_SWEET_KISS] =
    {
        .name = COMPOUND_STRING("SWEET KISS"),
        .description = COMPOUND_STRING(
            "Demands a kiss with a cute\n"
            "look. May cause confusion."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SweetKiss,
    },

    [MOVE_BELLY_DRUM] =
    {
        .name = COMPOUND_STRING("BELLY DRUM"),
        .description = COMPOUND_STRING(
            "Maximizes ATTACK while\n"
            "sacrificing HP."),
        .effect = EFFECT_BELLY_DRUM,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_BELLY_DRUM,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_BellyDrum,
    },

    [MOVE_SLUDGE_BOMB] =
    {
        .name = COMPOUND_STRING("SLUDGE BOMB"),
        .description = COMPOUND_STRING(
            "Sludge is hurled to inflict\n"
            "damage. May also poison."),
        .effect = EFFECT_POISON_HIT,
        .power = 90,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SLUDGE_BOMB,
        .contestComboMoves = {COMBO_STARTER_SLUDGE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SludgeBomb,
    },

    [MOVE_MUD_SLAP] =
    {
        .name = COMPOUND_STRING("MUD-SLAP"),
        .description = COMPOUND_STRING(
            "Hurls mud in the foe's face\n"
            "to reduce its accuracy."),
        .effect = EFFECT_ACCURACY_DOWN_HIT,
        .power = 20,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_MUD_SLAP,
        .contestComboMoves = {COMBO_STARTER_SAND_ATTACK, COMBO_STARTER_MUD_SPORT, COMBO_STARTER_SANDSTORM},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MudSlap,
    },

    [MOVE_OCTAZOOKA] =
    {
        .name = COMPOUND_STRING("OCTAZOOKA"),
        .description = COMPOUND_STRING(
            "Fires a lump of ink to\n"
            "damage and cut accuracy."),
        .effect = EFFECT_ACCURACY_DOWN_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .secondaryEffectChance = 50,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_LOCK_ON},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Octazooka,
    },

    [MOVE_SPIKES] =
    {
        .name = COMPOUND_STRING("SPIKES"),
        .description = COMPOUND_STRING(
            "Sets spikes that hurt a \n"
            "foe switching in."),
        .effect = EFFECT_SPIKES,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Spikes,
    },

    [MOVE_ZAP_CANNON] =
    {
        .name = COMPOUND_STRING("ZAP CANNON"),
        .description = COMPOUND_STRING(
            "Powerful and sure to cause\n"
            "paralysis, but inaccurate."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 50,
        .pp = 5,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOCK_ON},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_ZapCannon,
    },

    [MOVE_FORESIGHT] =
    {
        .name = COMPOUND_STRING("FORESIGHT"),
        .description = COMPOUND_STRING(
            "Negates the foe's efforts\n"
            "to heighten evasiveness."),
        .effect = EFFECT_FORESIGHT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Foresight,
    },

    [MOVE_DESTINY_BOND] =
    {
        .name = COMPOUND_STRING("DESTINY BOND"),
        .description = COMPOUND_STRING(
            "If the user faints, the foe\n"
            "is also made to faint."),
        .effect = EFFECT_DESTINY_BOND,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MEAN_LOOK, COMBO_STARTER_CURSE, COMBO_STARTER_ENDURE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DestinyBond,
    },

    [MOVE_PERISH_SONG] =
    {
        .name = COMPOUND_STRING("PERISH SONG"),
        .description = COMPOUND_STRING(
            "Any POKéMON hearing this\n"
            "song faints in 3 turns."),
        .effect = EFFECT_PERISH_SONG,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MEAN_LOOK, COMBO_STARTER_SING},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_PerishSong,
    },

    [MOVE_ICY_WIND] =
    {
        .name = COMPOUND_STRING("ICY WIND"),
        .description = COMPOUND_STRING(
            "A chilling attack that\n"
            "lowers the foe's SPEED."),
        .effect = EFFECT_SPEED_DOWN_HIT,
        .power = 55,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 15,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_IcyWind,
    },

    [MOVE_DETECT] =
    {
        .name = COMPOUND_STRING("DETECT"),
        .description = COMPOUND_STRING(
            "Evades attack, but may fail\n"
            "if used in succession."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TAUNT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Detect,
    },

    [MOVE_BONE_RUSH] =
    {
        .name = COMPOUND_STRING("BONE RUSH"),
        .description = COMPOUND_STRING(
            "Strikes the foe with a bone\n"
            "in hand 2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_GROUND,
        .accuracy = 80,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_BONE_RUSH,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_BONE_CLUB, COMBO_STARTER_BONEMERANG},
        .battleAnimScript = gBattleAnimMove_BoneRush,
    },

    [MOVE_LOCK_ON] =
    {
        .name = COMPOUND_STRING("LOCK-ON"),
        .description = COMPOUND_STRING(
            "Locks on to the foe to\n"
            "ensure the next move hits."),
        .effect = EFFECT_LOCK_ON,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_LOCK_ON,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_LockOn,
    },

    [MOVE_OUTRAGE] =
    {
        .name = COMPOUND_STRING("OUTRAGE"),
        .description = COMPOUND_STRING(
            "A rampage of 2 to 3 turns\n"
            "that confuses the user."),
        .effect = EFFECT_RAMPAGE,
        .power = 90,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Outrage,
    },

    [MOVE_SANDSTORM] =
    {
        .name = COMPOUND_STRING("SANDSTORM"),
        .description = COMPOUND_STRING(
            "Causes a sandstorm that\n"
            "rages for several turns."),
        .effect = EFFECT_SANDSTORM,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SANDSTORM,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Sandstorm,
    },

    [MOVE_GIGA_DRAIN] =
    {
        .name = COMPOUND_STRING("GIGA DRAIN"),
        .description = COMPOUND_STRING(
            "An attack that steals half\n"
            "the damage inflicted."),
        .effect = EFFECT_ABSORB,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_GigaDrain,
    },

    [MOVE_ENDURE] =
    {
        .name = COMPOUND_STRING("ENDURE"),
        .description = COMPOUND_STRING(
            "Endures any attack for\n"
            "1 turn, leaving at least 1HP."),
        .effect = EFFECT_ENDURE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_ENDURE,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Endure,
    },

    [MOVE_CHARM] =
    {
        .name = COMPOUND_STRING("CHARM"),
        .description = COMPOUND_STRING(
            "Charms the foe and sharply\n"
            "reduces its ATTACK."),
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_CHARM,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Charm,
    },

    [MOVE_ROLLOUT] =
    {
        .name = COMPOUND_STRING("ROLLOUT"),
        .description = COMPOUND_STRING(
            "An attack lasting 5 turns\n"
            "with rising intensity."),
        .effect = EFFECT_ROLLOUT,
        .power = 30,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DEFENSE_CURL, COMBO_STARTER_HARDEN},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Rollout,
    },

    [MOVE_FALSE_SWIPE] =
    {
        .name = COMPOUND_STRING("FALSE SWIPE"),
        .description = COMPOUND_STRING(
            "An attack that leaves the\n"
            "foe with at least 1 HP."),
        .effect = EFFECT_FALSE_SWIPE,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FalseSwipe,
    },

    [MOVE_SWAGGER] =
    {
        .name = COMPOUND_STRING("SWAGGER"),
        .description = COMPOUND_STRING(
            "Confuses the foe, but also\n"
            "sharply raises ATTACK."),
        .effect = EFFECT_SWAGGER,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Swagger,
    },

    [MOVE_MILK_DRINK] =
    {
        .name = COMPOUND_STRING("MILK DRINK"),
        .description = COMPOUND_STRING(
            "Recovers up to half the\n"
            "user's maximum HP."),
        .effect = EFFECT_SOFTBOILED,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .protectAffected = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MilkDrink,
    },

    [MOVE_SPARK] =
    {
        .name = COMPOUND_STRING("SPARK"),
        .description = COMPOUND_STRING(
            "An electrified tackle that\n"
            "may paralyze the foe."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_Spark,
    },

    [MOVE_FURY_CUTTER] =
    {
        .name = COMPOUND_STRING("FURY CUTTER"),
        .description = COMPOUND_STRING(
            "An attack that intensifies\n"
            "on each successive hit."),
        .effect = EFFECT_FURY_CUTTER,
        .power = 10,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FuryCutter,
    },

    [MOVE_STEEL_WING] =
    {
        .name = COMPOUND_STRING("STEEL WING"),
        .description = COMPOUND_STRING(
            "Strikes the foe with hard\n"
            "wings spread wide."),
        .effect = EFFECT_DEFENSE_UP_HIT,
        .power = 70,
        .type = TYPE_STEEL,
        .accuracy = 90,
        .pp = 25,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SteelWing,
    },

    [MOVE_MEAN_LOOK] =
    {
        .name = COMPOUND_STRING("MEAN LOOK"),
        .description = COMPOUND_STRING(
            "Fixes the foe with a mean\n"
            "look that prevents escape."),
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_MEAN_LOOK,
        .contestComboMoves = {COMBO_STARTER_CURSE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MeanLook,
    },

    [MOVE_ATTRACT] =
    {
        .name = COMPOUND_STRING("ATTRACT"),
        .description = COMPOUND_STRING(
            "Makes the opposite gender\n"
            "less likely to attack."),
        .effect = EFFECT_ATTRACT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Attract,
    },

    [MOVE_SLEEP_TALK] =
    {
        .name = COMPOUND_STRING("SLEEP TALK"),
        .description = COMPOUND_STRING(
            "Uses an available move\n"
            "randomly while asleep."),
        .effect = EFFECT_SLEEP_TALK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_REST},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SleepTalk,
    },

    [MOVE_HEAL_BELL] =
    {
        .name = COMPOUND_STRING("HEAL BELL"),
        .description = COMPOUND_STRING(
            "Chimes soothingly to heal\n"
            "all status abnormalities."),
        .effect = EFFECT_HEAL_BELL,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HealBell,
    },

    [MOVE_RETURN] =
    {
        .name = COMPOUND_STRING("RETURN"),
        .description = COMPOUND_STRING(
            "An attack that increases\n"
            "in power with friendship."),
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Return,
    },

    [MOVE_PRESENT] =
    {
        .name = COMPOUND_STRING("PRESENT"),
        .description = COMPOUND_STRING(
            "A gift in the form of a\n"
            "bomb. May restore HP."),
        .effect = EFFECT_PRESENT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Present,
    },

    [MOVE_FRUSTRATION] =
    {
        .name = COMPOUND_STRING("FRUSTRATION"),
        .description = COMPOUND_STRING(
            "An attack that is stronger\n"
            "if the TRAINER is disliked."),
        .effect = EFFECT_FRUSTRATION,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Frustration,
    },

    [MOVE_SAFEGUARD] =
    {
        .name = COMPOUND_STRING("SAFEGUARD"),
        .description = COMPOUND_STRING(
            "A mystical force prevents\n"
            "all status problems."),
        .effect = EFFECT_SAFEGUARD,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 25,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Safeguard,
    },

    [MOVE_PAIN_SPLIT] =
    {
        .name = COMPOUND_STRING("PAIN SPLIT"),
        .description = COMPOUND_STRING(
            "Adds the user and foe's HP,\n"
            "then shares them equally."),
        .effect = EFFECT_PAIN_SPLIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_PainSplit,
    },

    [MOVE_SACRED_FIRE] =
    {
        .name = COMPOUND_STRING("SACRED FIRE"),
        .description = COMPOUND_STRING(
            "A mystical fire attack that\n"
            "may inflict a burn."),
        .effect = EFFECT_THAW_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 5,
        .secondaryEffectChance = 50,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SacredFire,
    },

    [MOVE_MAGNITUDE] =
    {
        .name = COMPOUND_STRING("MAGNITUDE"),
        .description = COMPOUND_STRING(
            "A ground-shaking attack\n"
            "of random intensity."),
        .effect = EFFECT_MAGNITUDE,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Magnitude,
    },

    [MOVE_DYNAMIC_PUNCH] =
    {
        .name = COMPOUND_STRING("DYNAMICPUNCH"),
        .description = COMPOUND_STRING(
            "Powerful and sure to cause\n"
            "confusion, but inaccurate."),
        .effect = EFFECT_CONFUSE_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 50,
        .pp = 5,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DynamicPunch,
    },

    [MOVE_MEGAHORN] =
    {
        .name = COMPOUND_STRING("MEGAHORN"),
        .description = COMPOUND_STRING(
            "A brutal ramming attack\n"
            "using out-thrust horns."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_BUG,
        .accuracy = 85,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Megahorn,
    },

    [MOVE_DRAGON_BREATH] =
    {
        .name = COMPOUND_STRING("DRAGONBREATH"),
        .description = COMPOUND_STRING(
            "Strikes the foe with an\n"
            "incredible blast of breath."),
        .effect = EFFECT_PARALYZE_HIT,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DRAGON_BREATH,
        .contestComboMoves = {COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DragonBreath,
    },

    [MOVE_BATON_PASS] =
    {
        .name = COMPOUND_STRING("BATON PASS"),
        .description = COMPOUND_STRING(
            "Switches out the user while\n"
            "keeping effects in play."),
        .effect = EFFECT_BATON_PASS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_BatonPass,
    },

    [MOVE_ENCORE] =
    {
        .name = COMPOUND_STRING("ENCORE"),
        .description = COMPOUND_STRING(
            "Makes the foe repeat its\n"
            "last move over 2 to 6 turns."),
        .effect = EFFECT_ENCORE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Encore,
    },

    [MOVE_PURSUIT] =
    {
        .name = COMPOUND_STRING("PURSUIT"),
        .description = COMPOUND_STRING(
            "Inflicts bad damage if used\n"
            "on a foe switching out."),
        .effect = EFFECT_PURSUIT,
        .power = 40,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Pursuit,
    },

    [MOVE_RAPID_SPIN] =
    {
        .name = COMPOUND_STRING("RAPID SPIN"),
        .description = COMPOUND_STRING(
            "Spins the body at high\n"
            "speed to strike the foe."),
        .effect = EFFECT_RAPID_SPIN,
        .power = 20,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_RapidSpin,
    },

    [MOVE_SWEET_SCENT] =
    {
        .name = COMPOUND_STRING("SWEET SCENT"),
        .description = COMPOUND_STRING(
            "Allures the foe to reduce\n"
            "evasiveness."),
        .effect = EFFECT_EVASION_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_SWEET_SCENT,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SweetScent,
    },

    [MOVE_IRON_TAIL] =
    {
        .name = COMPOUND_STRING("IRON TAIL"),
        .description = COMPOUND_STRING(
            "Attacks with a rock-hard\n"
            "tail. May lower DEFENSE."),
        .effect = EFFECT_DEFENSE_DOWN_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 75,
        .pp = 15,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_IronTail,
    },

    [MOVE_METAL_CLAW] =
    {
        .name = COMPOUND_STRING("METAL CLAW"),
        .description = COMPOUND_STRING(
            "A claw attack that may\n"
            "raise the user's ATTACK."),
        .effect = EFFECT_ATTACK_UP_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 95,
        .pp = 35,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_METAL_SOUND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MetalClaw,
    },

    [MOVE_VITAL_THROW] =
    {
        .name = COMPOUND_STRING("VITAL THROW"),
        .description = COMPOUND_STRING(
            "Makes the user's move last,\n"
            "but it never misses."),
        .effect = EFFECT_VITAL_THROW,
        .power = 70,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = -1,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_VitalThrow,
    },

    [MOVE_MORNING_SUN] =
    {
        .name = COMPOUND_STRING("MORNING SUN"),
        .description = COMPOUND_STRING(
            "Restores HP. The amount\n"
            "varies with the weather."),
        .effect = EFFECT_MORNING_SUN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MorningSun,
    },

    [MOVE_SYNTHESIS] =
    {
        .name = COMPOUND_STRING("SYNTHESIS"),
        .description = COMPOUND_STRING(
            "Restores HP. The amount\n"
            "varies with the weather."),
        .effect = EFFECT_SYNTHESIS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Synthesis,
    },

    [MOVE_MOONLIGHT] =
    {
        .name = COMPOUND_STRING("MOONLIGHT"),
        .description = COMPOUND_STRING(
            "Restores HP. The amount\n"
            "varies with the weather."),
        .effect = EFFECT_MOONLIGHT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Moonlight,
    },

    [MOVE_HIDDEN_POWER] =
    {
        .name = COMPOUND_STRING("HIDDEN POWER"),
        .description = COMPOUND_STRING(
            "The effectiveness varies\n"
            "with the user."),
        .effect = EFFECT_HIDDEN_POWER,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HiddenPower,
    },

    [MOVE_CROSS_CHOP] =
    {
        .name = COMPOUND_STRING("CROSS CHOP"),
        .description = COMPOUND_STRING(
            "A double-chopping attack.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 80,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_CrossChop,
    },

    [MOVE_TWISTER] =
    {
        .name = COMPOUND_STRING("TWISTER"),
        .description = COMPOUND_STRING(
            "Whips up a vicious twister\n"
            "to tear at the foe."),
        .effect = EFFECT_TWISTER,
        .power = 40,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Twister,
    },

    [MOVE_RAIN_DANCE] =
    {
        .name = COMPOUND_STRING("RAIN DANCE"),
        .description = COMPOUND_STRING(
            "Boosts the power of WATER-\n"
            "type moves for 5 turns."),
        .effect = EFFECT_RAIN_DANCE,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_RAIN_DANCE,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_RainDance,
    },

    [MOVE_SUNNY_DAY] =
    {
        .name = COMPOUND_STRING("SUNNY DAY"),
        .description = COMPOUND_STRING(
            "Boosts the power of FIRE-\n"
            "type moves for 5 turns."),
        .effect = EFFECT_SUNNY_DAY,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SUNNY_DAY,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SunnyDay,
    },

    [MOVE_CRUNCH] =
    {
        .name = COMPOUND_STRING("CRUNCH"),
        .description = COMPOUND_STRING(
            "Crunches with sharp fangs.\n"
            "May lower SP. DEF."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCARY_FACE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Crunch,
    },

    [MOVE_MIRROR_COAT] =
    {
        .name = COMPOUND_STRING("MIRROR COAT"),
        .description = COMPOUND_STRING(
            "Counters the foe's special\n"
            "attack at double the power."),
        .effect = EFFECT_MIRROR_COAT,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TAUNT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MirrorCoat,
    },

    [MOVE_PSYCH_UP] =
    {
        .name = COMPOUND_STRING("PSYCH UP"),
        .description = COMPOUND_STRING(
            "Copies the foe's effect(s)\n"
            "and gives to the user."),
        .effect = EFFECT_PSYCH_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_PsychUp,
    },

    [MOVE_EXTREME_SPEED] =
    {
        .name = COMPOUND_STRING("EXTREMESPEED"),
        .description = COMPOUND_STRING(
            "An extremely fast and\n"
            "powerful attack."),
        .effect = EFFECT_QUICK_ATTACK,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_ExtremeSpeed,
    },

    [MOVE_ANCIENT_POWER] =
    {
        .name = COMPOUND_STRING("ANCIENTPOWER"),
        .description = COMPOUND_STRING(
            "An attack that may raise\n"
            "all stats."),
        .effect = EFFECT_ALL_STATS_UP_HIT,
        .power = 60,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_AncientPower,
    },

    [MOVE_SHADOW_BALL] =
    {
        .name = COMPOUND_STRING("SHADOW BALL"),
        .description = COMPOUND_STRING(
            "Hurls a black blob that may\n"
            "lower the foe's SP. DEF."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_HIT,
        .power = 80,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_ShadowBall,
    },

    [MOVE_FUTURE_SIGHT] =
    {
        .name = COMPOUND_STRING("FUTURE SIGHT"),
        .description = COMPOUND_STRING(
            "Heightens inner power to\n"
            "strike 2 turns later."),
        .effect = EFFECT_FUTURE_SIGHT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_PSYCHIC, COMBO_STARTER_KINESIS, COMBO_STARTER_CONFUSION, COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FutureSight,
    },

    [MOVE_ROCK_SMASH] =
    {
        .name = COMPOUND_STRING("ROCK SMASH"),
        .description = COMPOUND_STRING(
            "A rock-crushing attack\n"
            "that may lower DEFENSE."),
        .effect = EFFECT_DEFENSE_DOWN_HIT,
        .power = 20,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 50,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_RockSmash,
    },

    [MOVE_WHIRLPOOL] =
    {
        .name = COMPOUND_STRING("WHIRLPOOL"),
        .description = COMPOUND_STRING(
            "Traps and hurts the foe in\n"
            "a whirlpool for 2 to 5 turns."),
        .effect = EFFECT_TRAP,
        .power = 15,
        .type = TYPE_WATER,
        .accuracy = 70,
        .pp = 15,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Whirlpool,
    },

    [MOVE_BEAT_UP] =
    {
        .name = COMPOUND_STRING("BEAT UP"),
        .description = COMPOUND_STRING(
            "Summons party POKéMON to\n"
            "join in the attack."),
        .effect = EFFECT_BEAT_UP,
        .power = 10,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_BeatUp,
    },

    [MOVE_FAKE_OUT] =
    {
        .name = COMPOUND_STRING("FAKE OUT"),
        .description = COMPOUND_STRING(
            "A 1st-turn, 1st-strike move\n"
            "that causes flinching."),
        .effect = EFFECT_FAKE_OUT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_FAKE_OUT,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FakeOut,
    },

    [MOVE_UPROAR] =
    {
        .name = COMPOUND_STRING("UPROAR"),
        .description = COMPOUND_STRING(
            "Causes an uproar for 2 to 5\n"
            "turns and prevents sleep."),
        .effect = EFFECT_UPROAR,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Uproar,
    },

    [MOVE_STOCKPILE] =
    {
        .name = COMPOUND_STRING("STOCKPILE"),
        .description = COMPOUND_STRING(
            "Charges up power for up to\n"
            "3 turns."),
        .effect = EFFECT_STOCKPILE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_STOCKPILE,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Stockpile,
    },

    [MOVE_SPIT_UP] =
    {
        .name = COMPOUND_STRING("SPIT UP"),
        .description = COMPOUND_STRING(
            "Releases stockpiled power\n"
            "(the more the better)."),
        .effect = EFFECT_SPIT_UP,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STOCKPILE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SpitUp,
    },

    [MOVE_SWALLOW] =
    {
        .name = COMPOUND_STRING("SWALLOW"),
        .description = COMPOUND_STRING(
            "Absorbs stockpiled power\n"
            "and restores HP."),
        .effect = EFFECT_SWALLOW,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STOCKPILE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Swallow,
    },

    [MOVE_HEAT_WAVE] =
    {
        .name = COMPOUND_STRING("HEAT WAVE"),
        .description = COMPOUND_STRING(
            "Exhales a hot breath on the\n"
            "foe. May inflict a burn."),
        .effect = EFFECT_BURN_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 10,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HeatWave,
    },

    [MOVE_HAIL] =
    {
        .name = COMPOUND_STRING("HAIL"),
        .description = COMPOUND_STRING(
            "Summons a hailstorm that\n"
            "strikes every turn."),
        .effect = EFFECT_HAIL,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .protectAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_HAIL,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Hail,
    },

    [MOVE_TORMENT] =
    {
        .name = COMPOUND_STRING("TORMENT"),
        .description = COMPOUND_STRING(
            "Torments the foe and stops\n"
            "successive use of a move."),
        .effect = EFFECT_TORMENT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Torment,
    },

    [MOVE_FLATTER] =
    {
        .name = COMPOUND_STRING("FLATTER"),
        .description = COMPOUND_STRING(
            "Confuses the foe, but\n"
            "raises its SP. ATK."),
        .effect = EFFECT_FLATTER,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Flatter,
    },

    [MOVE_WILL_O_WISP] =
    {
        .name = COMPOUND_STRING("WILL-O-WISP"),
        .description = COMPOUND_STRING(
            "Inflicts a burn on the foe\n"
            "with intense fire."),
        .effect = EFFECT_WILL_O_WISP,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 75,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_WillOWisp,
    },

    [MOVE_MEMENTO] =
    {
        .name = COMPOUND_STRING("MEMENTO"),
        .description = COMPOUND_STRING(
            "The user faints and lowers\n"
            "the foe's abilities."),
        .effect = EFFECT_MEMENTO,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Memento,
    },

    [MOVE_FACADE] =
    {
        .name = COMPOUND_STRING("FACADE"),
        .description = COMPOUND_STRING(
            "Boosts ATTACK when burned,\n"
            "paralyzed, or poisoned."),
        .effect = EFFECT_FACADE,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Facade,
    },

    [MOVE_FOCUS_PUNCH] =
    {
        .name = COMPOUND_STRING("FOCUS PUNCH"),
        .description = COMPOUND_STRING(
            "A powerful loyalty attack.\n"
            "The user flinches if hit."),
        .effect = EFFECT_FOCUS_PUNCH,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = -3,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FocusPunch,
    },

    [MOVE_SMELLING_SALT] =
    {
        .name = COMPOUND_STRING("SMELLINGSALT"),
        .description = COMPOUND_STRING(
            "Powerful against paralyzed\n"
            "foes, but also heals them."),
        .effect = EFFECT_SMELLINGSALT,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SmellingSalt,
    },

    [MOVE_FOLLOW_ME] =
    {
        .name = COMPOUND_STRING("FOLLOW ME"),
        .description = COMPOUND_STRING(
            "Draws attention to make\n"
            "foes attack only the user."),
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FollowMe,
    },

    [MOVE_NATURE_POWER] =
    {
        .name = COMPOUND_STRING("NATURE POWER"),
        .description = COMPOUND_STRING(
            "The type of attack varies\n"
            "depending on the location."),
        .effect = EFFECT_NATURE_POWER,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_NaturePower,
    },

    [MOVE_CHARGE] =
    {
        .name = COMPOUND_STRING("CHARGE"),
        .description = COMPOUND_STRING(
            "Charges power to boost the\n"
            "electric move used next."),
        .effect = EFFECT_CHARGE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_CHARGE,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Charge,
    },

    [MOVE_TAUNT] =
    {
        .name = COMPOUND_STRING("TAUNT"),
        .description = COMPOUND_STRING(
            "Taunts the foe into only\n"
            "using attack moves."),
        .effect = EFFECT_TAUNT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_TAUNT,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Taunt,
    },

    [MOVE_HELPING_HAND] =
    {
        .name = COMPOUND_STRING("HELPING HAND"),
        .description = COMPOUND_STRING(
            "Boosts the power of the\n"
            "recipient's moves."),
        .effect = EFFECT_HELPING_HAND,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 5,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HelpingHand,
    },

    [MOVE_TRICK] =
    {
        .name = COMPOUND_STRING("TRICK"),
        .description = COMPOUND_STRING(
            "Tricks the foe into trading\n"
            "held items."),
        .effect = EFFECT_TRICK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Trick,
    },

    [MOVE_ROLE_PLAY] =
    {
        .name = COMPOUND_STRING("ROLE PLAY"),
        .description = COMPOUND_STRING(
            "Mimics the target and\n"
            "copies its special ability."),
        .effect = EFFECT_ROLE_PLAY,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_RolePlay,
    },

    [MOVE_WISH] =
    {
        .name = COMPOUND_STRING("WISH"),
        .description = COMPOUND_STRING(
            "A wish that restores HP.\n"
            "It takes time to work."),
        .effect = EFFECT_WISH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .protectAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Wish,
    },

    [MOVE_ASSIST] =
    {
        .name = COMPOUND_STRING("ASSIST"),
        .description = COMPOUND_STRING(
            "Attacks randomly with one\n"
            "of the partner's moves."),
        .effect = EFFECT_ASSIST,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Assist,
    },

    [MOVE_INGRAIN] =
    {
        .name = COMPOUND_STRING("INGRAIN"),
        .description = COMPOUND_STRING(
            "Lays roots that restore HP.\n"
            "The user can't switch out."),
        .effect = EFFECT_INGRAIN,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Ingrain,
    },

    [MOVE_SUPERPOWER] =
    {
        .name = COMPOUND_STRING("SUPERPOWER"),
        .description = COMPOUND_STRING(
            "Boosts strength sharply,\n"
            "but lowers abilities."),
        .effect = EFFECT_SUPERPOWER,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOCK_ON},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Superpower,
    },

    [MOVE_MAGIC_COAT] =
    {
        .name = COMPOUND_STRING("MAGIC COAT"),
        .description = COMPOUND_STRING(
            "Reflects special effects\n"
            "back to the attacker."),
        .effect = EFFECT_MAGIC_COAT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 4,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MagicCoat,
    },

    [MOVE_RECYCLE] =
    {
        .name = COMPOUND_STRING("RECYCLE"),
        .description = COMPOUND_STRING(
            "Recycles a used item for\n"
            "one more use."),
        .effect = EFFECT_RECYCLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Recycle,
    },

    [MOVE_REVENGE] =
    {
        .name = COMPOUND_STRING("REVENGE"),
        .description = COMPOUND_STRING(
            "An attack that gains power\n"
            "if injured by the foe."),
        .effect = EFFECT_REVENGE,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = -4,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Revenge,
    },

    [MOVE_BRICK_BREAK] =
    {
        .name = COMPOUND_STRING("BRICK BREAK"),
        .description = COMPOUND_STRING(
            "Destroys barriers such as\n"
            "REFLECT and causes damage."),
        .effect = EFFECT_BRICK_BREAK,
        .power = 75,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_BrickBreak,
    },

    [MOVE_YAWN] =
    {
        .name = COMPOUND_STRING("YAWN"),
        .description = COMPOUND_STRING(
            "Lulls the foe into yawning,\n"
            "then sleeping next turn."),
        .effect = EFFECT_YAWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_YAWN,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Yawn,
    },

    [MOVE_KNOCK_OFF] =
    {
        .name = COMPOUND_STRING("KNOCK OFF"),
        .description = COMPOUND_STRING(
            "Knocks down the foe's held\n"
            "item to prevent its use."),
        .effect = EFFECT_KNOCK_OFF,
        .power = 20,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_KnockOff,
    },

    [MOVE_ENDEAVOR] =
    {
        .name = COMPOUND_STRING("ENDEAVOR"),
        .description = COMPOUND_STRING(
            "Gains power if the user's HP\n"
            "is lower than the foe's HP."),
        .effect = EFFECT_ENDEAVOR,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Endeavor,
    },

    [MOVE_ERUPTION] =
    {
        .name = COMPOUND_STRING("ERUPTION"),
        .description = COMPOUND_STRING(
            "The higher the user's HP,\n"
            "the more damage caused."),
        .effect = EFFECT_ERUPTION,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE, COMBO_STARTER_EARTHQUAKE, COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Eruption,
    },

    [MOVE_SKILL_SWAP] =
    {
        .name = COMPOUND_STRING("SKILL SWAP"),
        .description = COMPOUND_STRING(
            "The user swaps special\n"
            "abilities with the target."),
        .effect = EFFECT_SKILL_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SkillSwap,
    },

    [MOVE_IMPRISON] =
    {
        .name = COMPOUND_STRING("IMPRISON"),
        .description = COMPOUND_STRING(
            "Prevents foes from using\n"
            "moves known by the user."),
        .effect = EFFECT_IMPRISON,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .protectAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Imprison,
    },

    [MOVE_REFRESH] =
    {
        .name = COMPOUND_STRING("REFRESH"),
        .description = COMPOUND_STRING(
            "Heals poisoning, paralysis,\n"
            "or a burn."),
        .effect = EFFECT_REFRESH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_WATER_SPORT, COMBO_STARTER_SING},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Refresh,
    },

    [MOVE_GRUDGE] =
    {
        .name = COMPOUND_STRING("GRUDGE"),
        .description = COMPOUND_STRING(
            "If the user faints, deletes\n"
            "all PP of foe's last move."),
        .effect = EFFECT_GRUDGE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CURSE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Grudge,
    },

    [MOVE_SNATCH] =
    {
        .name = COMPOUND_STRING("SNATCH"),
        .description = COMPOUND_STRING(
            "Steals the effects of the\n"
            "move the target uses next."),
        .effect = EFFECT_SNATCH,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 4,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Snatch,
    },

    [MOVE_SECRET_POWER] =
    {
        .name = COMPOUND_STRING("SECRET POWER"),
        .description = COMPOUND_STRING(
            "An attack with effects\n"
            "that vary by location."),
        .effect = EFFECT_SECRET_POWER,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SecretPower,
    },

    [MOVE_DIVE] =
    {
        .name = COMPOUND_STRING("DIVE"),
        .description = COMPOUND_STRING(
            "Dives underwater the first\n"
            "turn and strikes next turn."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_DIVE,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SURF},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Dive,
    },

    [MOVE_ARM_THRUST] =
    {
        .name = COMPOUND_STRING("ARM THRUST"),
        .description = COMPOUND_STRING(
            "Straight-arm punches that\n"
            "strike the foe 2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_FAKE_OUT},
        .battleAnimScript = gBattleAnimMove_ArmThrust,
    },

    [MOVE_CAMOUFLAGE] =
    {
        .name = COMPOUND_STRING("CAMOUFLAGE"),
        .description = COMPOUND_STRING(
            "Alters the POKéMON's type\n"
            "depending on the location."),
        .effect = EFFECT_CAMOUFLAGE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Camouflage,
    },

    [MOVE_TAIL_GLOW] =
    {
        .name = COMPOUND_STRING("TAIL GLOW"),
        .description = COMPOUND_STRING(
            "Flashes a light that sharply\n"
            "raises SP. ATK."),
        .effect = EFFECT_SPECIAL_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_TailGlow,
    },

    [MOVE_LUSTER_PURGE] =
    {
        .name = COMPOUND_STRING("LUSTER PURGE"),
        .description = COMPOUND_STRING(
            "Attacks with a burst of\n"
            "light. May lower SP. DEF."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_HIT,
        .power = 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 50,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_LusterPurge,
    },

    [MOVE_MIST_BALL] =
    {
        .name = COMPOUND_STRING("MIST BALL"),
        .description = COMPOUND_STRING(
            "Attacks with a flurry of\n"
            "down. May lower SP. ATK."),
        .effect = EFFECT_SPECIAL_ATTACK_DOWN_HIT,
        .power = 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 50,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MistBall,
    },

    [MOVE_FEATHER_DANCE] =
    {
        .name = COMPOUND_STRING("FEATHERDANCE"),
        .description = COMPOUND_STRING(
            "Envelops the foe with down\n"
            "to sharply reduce ATTACK."),
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FeatherDance,
    },

    [MOVE_TEETER_DANCE] =
    {
        .name = COMPOUND_STRING("TEETER DANCE"),
        .description = COMPOUND_STRING(
            "Confuses all POKéMON on\n"
            "the scene."),
        .effect = EFFECT_TEETER_DANCE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .protectAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_TeeterDance,
    },

    [MOVE_BLAZE_KICK] =
    {
        .name = COMPOUND_STRING("BLAZE KICK"),
        .description = COMPOUND_STRING(
            "A kick with a high critical-\n"
            "hit ratio. May cause a burn."),
        .effect = EFFECT_BLAZE_KICK,
        .power = 85,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 10,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_BlazeKick,
    },

    [MOVE_MUD_SPORT] =
    {
        .name = COMPOUND_STRING("MUD SPORT"),
        .description = COMPOUND_STRING(
            "Covers the user in mud to\n"
            "raise electrical resistance."),
        .effect = EFFECT_MUD_SPORT,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_MUD_SPORT,
        .contestComboMoves = {COMBO_STARTER_MUD_SLAP, COMBO_STARTER_WATER_SPORT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MudSport,
    },

    [MOVE_ICE_BALL] =
    {
        .name = COMPOUND_STRING("ICE BALL"),
        .description = COMPOUND_STRING(
            "A 5-turn attack that gains\n"
            "power on successive hits."),
        .effect = EFFECT_ROLLOUT,
        .power = 30,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IceBall,
    },

    [MOVE_NEEDLE_ARM] =
    {
        .name = COMPOUND_STRING("NEEDLE ARM"),
        .description = COMPOUND_STRING(
            "Attacks with thorny arms.\n"
            "May cause flinching."),
        .effect = EFFECT_FLINCH_MINIMIZE_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_NeedleArm,
    },

    [MOVE_SLACK_OFF] =
    {
        .name = COMPOUND_STRING("SLACK OFF"),
        .description = COMPOUND_STRING(
            "Slacks off and restores\n"
            "half the maximum HP."),
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_YAWN},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SlackOff,
    },

    [MOVE_HYPER_VOICE] =
    {
        .name = COMPOUND_STRING("HYPER VOICE"),
        .description = COMPOUND_STRING(
            "A loud attack that uses\n"
            "sound waves to injure."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HyperVoice,
    },

    [MOVE_POISON_FANG] =
    {
        .name = COMPOUND_STRING("POISON FANG"),
        .description = COMPOUND_STRING(
            "A sharp-fanged attack.\n"
            "May badly poison the foe."),
        .effect = EFFECT_POISON_FANG,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonFang,
    },

    [MOVE_CRUSH_CLAW] =
    {
        .name = COMPOUND_STRING("CRUSH CLAW"),
        .description = COMPOUND_STRING(
            "Tears at the foe with sharp\n"
            "claws. May lower DEFENSE."),
        .effect = EFFECT_DEFENSE_DOWN_HIT,
        .power = 75,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 10,
        .secondaryEffectChance = 50,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_CrushClaw,
    },

    [MOVE_BLAST_BURN] =
    {
        .name = COMPOUND_STRING("BLAST BURN"),
        .description = COMPOUND_STRING(
            "Powerful, but leaves the\n"
            "user immobile the next turn."),
        .effect = EFFECT_RECHARGE,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_BlastBurn,
    },

    [MOVE_HYDRO_CANNON] =
    {
        .name = COMPOUND_STRING("HYDRO CANNON"),
        .description = COMPOUND_STRING(
            "Powerful, but leaves the\n"
            "user immobile the next turn."),
        .effect = EFFECT_RECHARGE,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_HydroCannon,
    },

    [MOVE_METEOR_MASH] =
    {
        .name = COMPOUND_STRING("METEOR MASH"),
        .description = COMPOUND_STRING(
            "Fires a meteor-like punch.\n"
            "May raise ATTACK."),
        .effect = EFFECT_ATTACK_UP_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 10,
        .secondaryEffectChance = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MeteorMash,
    },

    [MOVE_ASTONISH] =
    {
        .name = COMPOUND_STRING("ASTONISH"),
        .description = COMPOUND_STRING(
            "An attack that may shock\n"
            "the foe into flinching."),
        .effect = EFFECT_FLINCH_MINIMIZE_HIT,
        .power = 30,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Astonish,
    },

    [MOVE_WEATHER_BALL] =
    {
        .name = COMPOUND_STRING("WEATHER BALL"),
        .description = COMPOUND_STRING(
            "The move's type and power\n"
            "change with the weather."),
        .effect = EFFECT_WEATHER_BALL,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SUNNY_DAY, COMBO_STARTER_HAIL, COMBO_STARTER_SANDSTORM},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_WeatherBall,
    },

    [MOVE_AROMATHERAPY] =
    {
        .name = COMPOUND_STRING("AROMATHERAPY"),
        .description = COMPOUND_STRING(
            "Heals all status problems\n"
            "with a soothing scent."),
        .effect = EFFECT_HEAL_BELL,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Aromatherapy,
    },

    [MOVE_FAKE_TEARS] =
    {
        .name = COMPOUND_STRING("FAKE TEARS"),
        .description = COMPOUND_STRING(
            "Feigns crying to sharply\n"
            "lower the foe's SP. DEF."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FakeTears,
    },

    [MOVE_AIR_CUTTER] =
    {
        .name = COMPOUND_STRING("AIR CUTTER"),
        .description = COMPOUND_STRING(
            "Hacks with razorlike wind.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 55,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 25,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_AirCutter,
    },

    [MOVE_OVERHEAT] =
    {
        .name = COMPOUND_STRING("OVERHEAT"),
        .description = COMPOUND_STRING(
            "Allows a full-power attack,\n"
            "but sharply lowers SP. ATK."),
        .effect = EFFECT_OVERHEAT,
        .power = 140,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Overheat,
    },

    [MOVE_ODOR_SLEUTH] =
    {
        .name = COMPOUND_STRING("ODOR SLEUTH"),
        .description = COMPOUND_STRING(
            "Negates the foe's efforts\n"
            "to heighten evasiveness."),
        .effect = EFFECT_FORESIGHT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_OdorSleuth,
    },

    [MOVE_ROCK_TOMB] =
    {
        .name = COMPOUND_STRING("ROCK TOMB"),
        .description = COMPOUND_STRING(
            "Stops the foe from moving\n"
            "with rocks and cuts SPEED."),
        .effect = EFFECT_SPEED_DOWN_HIT,
        .power = 50,
        .type = TYPE_ROCK,
        .accuracy = 80,
        .pp = 10,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ROCK_THROW},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_RockTomb,
    },

    [MOVE_SILVER_WIND] =
    {
        .name = COMPOUND_STRING("SILVER WIND"),
        .description = COMPOUND_STRING(
            "A powdery attack that may\n"
            "raise abilities."),
        .effect = EFFECT_ALL_STATS_UP_HIT,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SilverWind,
    },

    [MOVE_METAL_SOUND] =
    {
        .name = COMPOUND_STRING("METAL SOUND"),
        .description = COMPOUND_STRING(
            "Emits a horrible screech\n"
            "that sharply lowers SP. DEF."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_METAL_SOUND,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MetalSound,
    },

    [MOVE_GRASS_WHISTLE] =
    {
        .name = COMPOUND_STRING("GRASSWHISTLE"),
        .description = COMPOUND_STRING(
            "Lulls the foe into sleep\n"
            "with a pleasant melody."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 55,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_GrassWhistle,
    },

    [MOVE_TICKLE] =
    {
        .name = COMPOUND_STRING("TICKLE"),
        .description = COMPOUND_STRING(
            "Makes the foe laugh to\n"
            "lower ATTACK and DEFENSE."),
        .effect = EFFECT_TICKLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Tickle,
    },

    [MOVE_COSMIC_POWER] =
    {
        .name = COMPOUND_STRING("COSMIC POWER"),
        .description = COMPOUND_STRING(
            "Raises DEFENSE and SP. DEF\n"
            "with a mystic power."),
        .effect = EFFECT_COSMIC_POWER,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_CosmicPower,
    },

    [MOVE_WATER_SPOUT] =
    {
        .name = COMPOUND_STRING("WATER SPOUT"),
        .description = COMPOUND_STRING(
            "Inflicts more damage if the\n"
            "user's HP is high."),
        .effect = EFFECT_ERUPTION,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_WaterSpout,
    },

    [MOVE_SIGNAL_BEAM] =
    {
        .name = COMPOUND_STRING("SIGNAL BEAM"),
        .description = COMPOUND_STRING(
            "A strange beam attack that\n"
            "may confuse the foe."),
        .effect = EFFECT_CONFUSE_HIT,
        .power = 75,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SignalBeam,
    },

    [MOVE_SHADOW_PUNCH] =
    {
        .name = COMPOUND_STRING("SHADOW PUNCH"),
        .description = COMPOUND_STRING(
            "An unavoidable punch that\n"
            "is thrown from shadows."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_ShadowPunch,
    },

    [MOVE_EXTRASENSORY] =
    {
        .name = COMPOUND_STRING("EXTRASENSORY"),
        .description = COMPOUND_STRING(
            "Attacks with a peculiar\n"
            "power. May cause flinching."),
        .effect = EFFECT_FLINCH_MINIMIZE_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Extrasensory,
    },

    [MOVE_SKY_UPPERCUT] =
    {
        .name = COMPOUND_STRING("SKY UPPERCUT"),
        .description = COMPOUND_STRING(
            "An uppercut thrown as if\n"
            "leaping into the sky."),
        .effect = EFFECT_SKY_UPPERCUT,
        .power = 85,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SkyUppercut,
    },

    [MOVE_SAND_TOMB] =
    {
        .name = COMPOUND_STRING("SAND TOMB"),
        .description = COMPOUND_STRING(
            "Traps and hurts the foe in\n"
            "quicksand for 2 to 5 turns."),
        .effect = EFFECT_TRAP,
        .power = 15,
        .type = TYPE_GROUND,
        .accuracy = 70,
        .pp = 15,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SANDSTORM},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SandTomb,
    },

    [MOVE_SHEER_COLD] =
    {
        .name = COMPOUND_STRING("SHEER COLD"),
        .description = COMPOUND_STRING(
            "A chilling attack that\n"
            "causes fainting if it hits."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_ICE,
        .accuracy = 30,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_SheerCold,
    },

    [MOVE_MUDDY_WATER] =
    {
        .name = COMPOUND_STRING("MUDDY WATER"),
        .description = COMPOUND_STRING(
            "Attacks with muddy water.\n"
            "May lower accuracy."),
        .effect = EFFECT_ACCURACY_DOWN_HIT,
        .power = 95,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MuddyWater,
    },

    [MOVE_BULLET_SEED] =
    {
        .name = COMPOUND_STRING("BULLET SEED"),
        .description = COMPOUND_STRING(
            "Shoots 2 to 5 seeds in a row\n"
            "to strike the foe."),
        .effect = EFFECT_MULTI_HIT,
        .power = 10,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_BulletSeed,
    },

    [MOVE_AERIAL_ACE] =
    {
        .name = COMPOUND_STRING("AERIAL ACE"),
        .description = COMPOUND_STRING(
            "An extremely speedy and\n"
            "unavoidable attack."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_AerialAce,
    },

    [MOVE_ICICLE_SPEAR] =
    {
        .name = COMPOUND_STRING("ICICLE SPEAR"),
        .description = COMPOUND_STRING(
            "Attacks the foe by firing\n"
            "2 to 5 icicles in a row."),
        .effect = EFFECT_MULTI_HIT,
        .power = 10,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 30,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IcicleSpear,
    },

    [MOVE_IRON_DEFENSE] =
    {
        .name = COMPOUND_STRING("IRON DEFENSE"),
        .description = COMPOUND_STRING(
            "Hardens the body's surface\n"
            "to sharply raise DEFENSE."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_IronDefense,
    },

    [MOVE_BLOCK] =
    {
        .name = COMPOUND_STRING("BLOCK"),
        .description = COMPOUND_STRING(
            "Blocks the foe's way to\n"
            "prevent escape."),
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .magicCoatAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Block,
    },

    [MOVE_HOWL] =
    {
        .name = COMPOUND_STRING("HOWL"),
        .description = COMPOUND_STRING(
            "Howls to raise the spirit\n"
            "and boosts ATTACK."),
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Howl,
    },

    [MOVE_DRAGON_CLAW] =
    {
        .name = COMPOUND_STRING("DRAGON CLAW"),
        .description = COMPOUND_STRING(
            "Slashes the foe with sharp\n"
            "claws."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DragonClaw,
    },

    [MOVE_FRENZY_PLANT] =
    {
        .name = COMPOUND_STRING("FRENZY PLANT"),
        .description = COMPOUND_STRING(
            "Powerful, but leaves the\n"
            "user immobile the next turn."),
        .effect = EFFECT_RECHARGE,
        .power = 150,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_FrenzyPlant,
    },

    [MOVE_BULK_UP] =
    {
        .name = COMPOUND_STRING("BULK UP"),
        .description = COMPOUND_STRING(
            "Bulks up the body to boost\n"
            "both ATTACK and DEFENSE."),
        .effect = EFFECT_BULK_UP,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_BulkUp,
    },

    [MOVE_BOUNCE] =
    {
        .name = COMPOUND_STRING("BOUNCE"),
        .description = COMPOUND_STRING(
            "Bounces up, then down the\n"
            "next turn. May paralyze."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 85,
        .type = TYPE_FLYING,
        .accuracy = 85,
        .pp = 5,
        .secondaryEffectChance = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Bounce,
    },

    [MOVE_MUD_SHOT] =
    {
        .name = COMPOUND_STRING("MUD SHOT"),
        .description = COMPOUND_STRING(
            "Hurls mud at the foe and\n"
            "reduces SPEED."),
        .effect = EFFECT_SPEED_DOWN_HIT,
        .power = 55,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 15,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MudShot,
    },

    [MOVE_POISON_TAIL] =
    {
        .name = COMPOUND_STRING("POISON TAIL"),
        .description = COMPOUND_STRING(
            "Has a high critical-hit\n"
            "ratio. May also poison."),
        .effect = EFFECT_POISON_TAIL,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 25,
        .secondaryEffectChance = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_PoisonTail,
    },

    [MOVE_COVET] =
    {
        .name = COMPOUND_STRING("COVET"),
        .description = COMPOUND_STRING(
            "Cutely begs to obtain an\n"
            "item held by the foe."),
        .effect = EFFECT_THIEF,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Covet,
    },

    [MOVE_VOLT_TACKLE] =
    {
        .name = COMPOUND_STRING("VOLT TACKLE"),
        .description = COMPOUND_STRING(
            "A life-risking tackle that\n"
            "slightly hurts the user."),
        .effect = EFFECT_DOUBLE_EDGE,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_VoltTackle,
    },

    [MOVE_MAGICAL_LEAF] =
    {
        .name = COMPOUND_STRING("MAGICAL LEAF"),
        .description = COMPOUND_STRING(
            "Attacks with a strange leaf\n"
            "that cannot be evaded."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MagicalLeaf,
    },

    [MOVE_WATER_SPORT] =
    {
        .name = COMPOUND_STRING("WATER SPORT"),
        .description = COMPOUND_STRING(
            "The user becomes soaked to\n"
            "raise resistance to fire."),
        .effect = EFFECT_WATER_SPORT,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_WATER_SPORT,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_MUD_SPORT},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_WaterSport,
    },

    [MOVE_CALM_MIND] =
    {
        .name = COMPOUND_STRING("CALM MIND"),
        .description = COMPOUND_STRING(
            "Raises SP. ATK and SP. DEF\n"
            "by focusing the mind."),
        .effect = EFFECT_CALM_MIND,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_CALM_MIND,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_CalmMind,
    },

    [MOVE_LEAF_BLADE] =
    {
        .name = COMPOUND_STRING("LEAF BLADE"),
        .description = COMPOUND_STRING(
            "Slashes with a sharp leaf.\n"
            "High critical-hit ratio."),
        .effect = EFFECT_HIGH_CRITICAL,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .makesContact = TRUE,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_LeafBlade,
    },

    [MOVE_DRAGON_DANCE] =
    {
        .name = COMPOUND_STRING("DRAGON DANCE"),
        .description = COMPOUND_STRING(
            "A mystical dance that ups\n"
            "ATTACK and SPEED."),
        .effect = EFFECT_DRAGON_DANCE,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DRAGON_DANCE,
        .contestComboMoves = {COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_BREATH},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DragonDance,
    },

    [MOVE_ROCK_BLAST] =
    {
        .name = COMPOUND_STRING("ROCK BLAST"),
        .description = COMPOUND_STRING(
            "Hurls boulders at the foe\n"
            "2 to 5 times in a row."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_ROCK,
        .accuracy = 80,
        .pp = 10,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockBlast,
    },

    [MOVE_SHOCK_WAVE] =
    {
        .name = COMPOUND_STRING("SHOCK WAVE"),
        .description = COMPOUND_STRING(
            "A fast and unavoidable\n"
            "electric attack."),
        .effect = EFFECT_ALWAYS_HIT,
        .power = 60,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_ShockWave,
    },

    [MOVE_WATER_PULSE] =
    {
        .name = COMPOUND_STRING("WATER PULSE"),
        .description = COMPOUND_STRING(
            "Attacks with ultrasonic\n"
            "waves. May confuse the foe."),
        .effect = EFFECT_CONFUSE_HIT,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .secondaryEffectChance = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_WaterPulse,
    },

    [MOVE_DOOM_DESIRE] =
    {
        .name = COMPOUND_STRING("DOOM DESIRE"),
        .description = COMPOUND_STRING(
            "Summons strong sunlight to\n"
            "attack 2 turns later."),
        .effect = EFFECT_FUTURE_SIGHT,
        .power = 120,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 5,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_DoomDesire,
    },

    [MOVE_PSYCHO_BOOST] =
    {
        .name = COMPOUND_STRING("PSYCHO BOOST"),
        .description = COMPOUND_STRING(
            "Allows a full-power attack,\n"
            "but sharply lowers SP. ATK."),
        .effect = EFFECT_OVERHEAT,
        .power = 140,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 5,
        .secondaryEffectChance = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .protectAffected = TRUE,
        .mirrorMoveAffected = TRUE,
        .kingsRockAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .validApprenticeMove = TRUE,
        .battleAnimScript = gBattleAnimMove_PsychoBoost,
    },

};

