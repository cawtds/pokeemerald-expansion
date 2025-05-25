#ifndef GUARD_SPECIES_H
#define GUARD_SPECIES_H

#include "global.h"
#include "constants/species.h"

struct LevelUpMove
{
    u16 move;
    u16 level;
};

struct Evolution
{
    u16 method;
    u16 param;
    u16 targetSpecies;
};

struct SpeciesInfo
{
 /* 0x00 */ u8 baseHP;
 /* 0x01 */ u8 baseAttack;
 /* 0x02 */ u8 baseDefense;
 /* 0x03 */ u8 baseSpeed;
 /* 0x04 */ u8 baseSpAttack;
 /* 0x05 */ u8 baseSpDefense;
 /* 0x06 */ u8 types[2];
 /* 0x08 */ u8 catchRate;
 /* 0x09 */ u8 expYield;
 /* 0x0A */ u16 evYield_HP:2;
 /* 0x0A */ u16 evYield_Attack:2;
 /* 0x0A */ u16 evYield_Defense:2;
 /* 0x0A */ u16 evYield_Speed:2;
 /* 0x0B */ u16 evYield_SpAttack:2;
 /* 0x0B */ u16 evYield_SpDefense:2;
 /* 0x0C */ u16 itemCommon;
 /* 0x0E */ u16 itemRare;
 /* 0x10 */ u8 genderRatio;
 /* 0x11 */ u8 eggCycles;
 /* 0x12 */ u8 friendship;
 /* 0x13 */ u8 growthRate;
 /* 0x14 */ u8 eggGroups[EGG_GROUPS_PER_MON];
 /* 0x16 */ u8 abilities[NUM_ABILITY_SLOTS];
 /* 0x18 */ u8 safariZoneFleeRate;
 /* 0x19 */ u8 bodyColor : 7;
            u8 noFlip : 1;
            // new
            u8 frontAnimId;
            u8 frontAnimDelay;
            u8 frontPicSize; // The dimensions of this drawn pixel area.
            u8 frontPicYOffset; // The number of pixels between the drawn pixel area and the bottom edge.
            u8 backAnimId;
            const union AnimCmd *const *frontAnimFrames;
            u8 backPicSize; // The dimensions of this drawn pixel area.
            u8 backPicYOffset; // The number of pixels between the drawn pixel area and the bottom edge.
            const u32 *frontPic;
            const u32 *backPic;
            const u32 *palette;
            const u32 *shinyPalette;
            const u8 *iconSprite;
            u8 iconPalIndex:3;        
            u8 pokemonJumpType:2;
            u8 enemyMonElevation; // This determines how much higher above the usual position the enemy Pokémon is during battle. Species that float or fly have nonzero values.
            struct Evolution evolutions[EVOS_PER_MON];
            const struct LevelUpMove *levelUpLearnset;
            const u16 *tmhmLearnset;
            const u16 *tutorLearnset;
            const u16 *eggMoveLearnset;
            const u8 *footprint;
            u8 speciesName[POKEMON_NAME_LENGTH + 1];
            u16 cryId;
            u16 natDexNum;
            // struct PokedexEntry
            u8 categoryName[12];
            u16 height; //in decimeters
            u16 weight; //in hectograms
            const u8 *description;
            u16 pokemonScale;
            u16 pokemonOffset;
            u16 trainerScale;
            u16 trainerOffset;
};

extern const struct SpeciesInfo gSpeciesInfo[];

static inline u32 SanitizeSpeciesId(u32 speciesId)
{
    if (speciesId >= NUM_SPECIES_AND_FORMS)
        return SPECIES_NONE;
    return speciesId;
}

static inline const u8 *GetSpeciesName(u32 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].speciesName[0] == 0)
        return gSpeciesInfo[SPECIES_NONE].speciesName;
    return gSpeciesInfo[species].speciesName;
}

static inline const u8 *GetSpeciesCategory(u32 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].categoryName[0] == 0)
        return gSpeciesInfo[SPECIES_NONE].categoryName;
    return gSpeciesInfo[species].categoryName;
}

static inline const u8 *GetSpeciesPokedexDescription(u32 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].description == NULL)
        return gSpeciesInfo[SPECIES_NONE].description;
    return gSpeciesInfo[species].description;
}

static inline u32 GetSpeciesHeight(u32 species)
{
    return gSpeciesInfo[SanitizeSpeciesId(species)].height;
}

static inline u32 GetSpeciesWeight(u32 species)
{
    return gSpeciesInfo[SanitizeSpeciesId(species)].weight;
}

static inline const u16 *GetSpeciesEggMoves(u32 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].eggMoveLearnset == NULL)
        return gSpeciesInfo[SPECIES_NONE].eggMoveLearnset;
    return gSpeciesInfo[species].eggMoveLearnset;
}

#endif //GUARD_SPECIES_H