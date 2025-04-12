const struct TypeInfo gTypeInfos[NUMBER_OF_MON_TYPES] =
{
    [TYPE_NORMAL] =
    {
        .name = _("NORMAL"),
        .moveText = _("a NORMAL move"),
        .damageCategory = DAMAGE_CATEGORY_PHYSICAL,
        .menuInfoOffset = 0x20,
        .conversionWeight = 3,
        .paletteNum = 13,
        .paletteTMHM = gItemIconPalette_NormalTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_NORMAL],
    },

    [TYPE_FIGHTING] =
    {
        .name = _("FIGHT"),
        .moveText = _("a FIGHTING move"),
        .damageCategory = DAMAGE_CATEGORY_PHYSICAL,
        .menuInfoOffset = 0x64,
        .conversionWeight = 5,
        .paletteNum = 13,
        .paletteTMHM = gItemIconPalette_FightingTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_FIGHTING],
    },

    [TYPE_FLYING] =
    {
        .name = _("FLYING"),
        .moveText = _("a FLYING move"),
        .damageCategory = DAMAGE_CATEGORY_PHYSICAL,
        .menuInfoOffset = 0x60,
        .conversionWeight = 3,
        .paletteNum = 14,
        .paletteTMHM = gItemIconPalette_FlyingTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_FLYING],
    },

    [TYPE_POISON] =
    {
        .name = _("POISON"),
        .moveText = _("a POISON move"),
        .damageCategory = DAMAGE_CATEGORY_PHYSICAL,
        .menuInfoOffset = 0x80,
        .conversionWeight = 5,
        .paletteNum = 14,
        .paletteTMHM = gItemIconPalette_PoisonTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_POISON],
    },

    [TYPE_GROUND] =
    {
        .name = _("GROUND"),
        .moveText = _("a GROUND move"),
        .damageCategory = DAMAGE_CATEGORY_PHYSICAL,
        .menuInfoOffset = 0x48,
        .conversionWeight = 3,
        .paletteNum = 13,
        .paletteTMHM = gItemIconPalette_GroundTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_GROUND],
    },

    [TYPE_ROCK] =
    {
        .name = _("ROCK"),
        .moveText = _("a ROCK move"),
        .damageCategory = DAMAGE_CATEGORY_PHYSICAL,
        .menuInfoOffset = 0x44,
        .conversionWeight = 3,
        .paletteNum = 13,
        .paletteTMHM = gItemIconPalette_RockTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_ROCK],
    },

    [TYPE_BUG] =
    {
        .name = _("BUG"),
        .moveText = _("a BUG move"),
        .damageCategory = DAMAGE_CATEGORY_PHYSICAL,
        .menuInfoOffset = 0x6C,
        .conversionWeight = 6,
        .paletteNum = 15,
        .paletteTMHM = gItemIconPalette_BugTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_BUG],
    },

    [TYPE_GHOST] =
    {
        .name = _("GHOST"),
        .moveText = _("a GHOST move"),
        .damageCategory = DAMAGE_CATEGORY_PHYSICAL,
        .menuInfoOffset = 0x68,
        .conversionWeight = 3,
        .paletteNum = 14,
        .paletteTMHM = gItemIconPalette_GhostTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_GHOST],
    },

    [TYPE_STEEL] =
    {
        .name = _("STEEL"),
        .moveText = _("a STEEL move"),
        .damageCategory = DAMAGE_CATEGORY_PHYSICAL,
        .menuInfoOffset = 0x88,
        .conversionWeight = 4,
        .paletteNum = 13,
        .paletteTMHM = gItemIconPalette_SteelTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_STEEL],
    },

    [TYPE_MYSTERY] =
    {
        .name = _("???"),
        .moveText = _("a ??? move"),
        .damageCategory = DAMAGE_CATEGORY_SPECIAL,
        .menuInfoOffset = 0xA4,
        .paletteNum = 15,
        .paletteTMHM = gItemIconPalette_NormalTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_MYSTERY],
    },

    [TYPE_FIRE] =
    {
        .name = _("FIRE"),
        .moveText = _("a FIRE move"),
        .damageCategory = DAMAGE_CATEGORY_SPECIAL,
        .menuInfoOffset = 0x24,
        .conversionWeight = 4,
        .paletteNum = 13,
        .paletteTMHM = gItemIconPalette_FireTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_FIRE],
    },

    [TYPE_WATER] =
    {
        .name = _("WATER"),
        .moveText = _("a WATER move"),
        .damageCategory = DAMAGE_CATEGORY_SPECIAL,
        .menuInfoOffset = 0x28,
        .conversionWeight = 3,
        .paletteNum = 14,
        .paletteTMHM = gItemIconPalette_WaterTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_WATER],
    },

    [TYPE_GRASS] =
    {
        .name = _("GRASS"),
        .moveText = _("a GRASS move"),
        .damageCategory = DAMAGE_CATEGORY_SPECIAL,
        .menuInfoOffset = 0x2C,
        .conversionWeight = 7,
        .paletteNum = 15,
        .paletteTMHM = gItemIconPalette_GrassTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_GRASS],
    },

    [TYPE_ELECTRIC] =
    {
        .name = _("ELECTR"),
        .moveText = _("an ELECTRIC move"),
        .damageCategory = DAMAGE_CATEGORY_SPECIAL,
        .menuInfoOffset = 0x40,
        .conversionWeight = 4,
        .paletteNum = 13,
        .paletteTMHM = gItemIconPalette_ElectricTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_ELECTRIC],
    },

    [TYPE_PSYCHIC] =
    {
        .name = _("PSYCHC"),
        .moveText = _("a PSYCHIC move"),
        .damageCategory = DAMAGE_CATEGORY_SPECIAL,
        .menuInfoOffset = 0x84,
        .conversionWeight = 3,
        .paletteNum = 14,
        .paletteTMHM = gItemIconPalette_PsychicTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_PSYCHIC],
    },

    [TYPE_ICE] =
    {
        .name = _("ICE"),
        .moveText = _("an ICE move"),
        .damageCategory = DAMAGE_CATEGORY_SPECIAL,
        .menuInfoOffset = 0x4C,
        .conversionWeight = 4,
        .paletteNum = 14,
        .paletteTMHM = gItemIconPalette_IceTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_ICE],
    },

    [TYPE_DRAGON] =
    {
        .name = _("DRAGON"),
        .moveText = _("a DRAGON move"),
        .damageCategory = DAMAGE_CATEGORY_SPECIAL,
        .menuInfoOffset = 0xA0,
        .conversionWeight = 1,
        .paletteNum = 15,
        .paletteTMHM = gItemIconPalette_DragonTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_DRAGON],
    },

    [TYPE_DARK] =
    {
        .name = _("DARK"),
        .moveText = _("a DARK move"),
        .damageCategory = DAMAGE_CATEGORY_SPECIAL,
        .menuInfoOffset = 0x8C,
        .conversionWeight = 3,
        .paletteNum = 13,
        .paletteTMHM = gItemIconPalette_DarkTMHM,
        .effectiveness = gTypeEffectivenessTable[TYPE_DARK],
    },

};
