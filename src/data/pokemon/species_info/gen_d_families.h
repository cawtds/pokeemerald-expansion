#ifdef __INTELLISENSE__
const struct SpeciesInfo gSpeciesInfoGenD[] =
{
#endif


[SPECIES_AGUNITE] =
    {
       .baseHP        = 106,
       .baseAttack    = 150,
       .baseDefense   = 70,
       .baseSpeed     = 140,
       .baseSpAttack  = 194,
       .baseSpDefense = 120,
       .types = MON_TYPES(TYPE_DRAGON),
       .catchRate = 3,
       .expYield = 255,
       .evYield_SpAttack  = 3,
       .genderRatio = PERCENT_FEMALE(12.5),
       .eggCycles = 120,
       .friendship = 0,
       .growthRate = GROWTH_MEDIUM_SLOW,
       .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
       .abilities = { ABILITY_INSOMNIA, ABILITY_NONE, ABILITY_NONE },
       .bodyColor = BODY_COLOR_PURPLE,
       .speciesName = _("Agunite"),
       .natDexNum = NATIONAL_DEX_AGUNITE,
       .categoryName = _("New Species"),
       .height = 15,
       .weight = 330,
       .description = COMPOUND_STRING(
           "The rumors became true.\n"
           "This is Mew's final form.\n"
           "Its power level is over 9000.\n"
           "Has science gone too far?"),
       .pokemonScale = 256,
       .pokemonOffset = 0,
       .trainerScale = 290,
       .trainerOffset = 2,
       .frontPic = gMonFrontPic_Agunite,
       .frontPicSize = MON_COORDS_SIZE(64, 64),
       .frontPicYOffset = 0,
       .frontAnimFrames = ANIM_FRAMES(
           ANIMCMD_FRAME(0, 1),
       ),
       .frontAnimId = ANIM_GROW_VIBRATE,
       .frontAnimDelay = 15,
       .enemyMonElevation = 6,
       .backPic = gMonBackPic_Agunite,
       .backPicSize = MON_COORDS_SIZE(64, 64),
       .backPicYOffset = 0,
       .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
       .palette = gMonPalette_Agunite,
       .shinyPalette = gMonShinyPalette_Agunite,
       .iconSprite = gMonIcon_Agunite,
       .iconPalIndex = 2,
       FOOTPRINT(Agunite)
    },

#ifdef __INTELLISENSE__
};
#endif