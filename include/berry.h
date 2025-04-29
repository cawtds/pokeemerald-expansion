#ifndef GUARD_BERRY_H
#define GUARD_BERRY_H

#include "global.h"

struct BerryInfo
{    
    const u8 name[BERRY_NAME_LENGTH + 1];
    u8 firmness;
    u16 size;
    u8 maxYield;
    u8 minYield;
    const u8 *description1;
    const u8 *description2;
    u8 stageDuration;
    u8 smoothness;
    u8 flavors[FLAVOR_COUNT];
    const u8 *treePaletteSlots;
    const struct SpriteFrameImage *treeImages;
    const u32 *imageTiles;
    const u32 *imagePalette;
    u16 crushPowder;
    u8 crushDifficulty; // The number of A presses required to crush it
};

void ClearEnigmaBerries(void);
void SetEnigmaBerry(u8 *src);
bool32 IsEnigmaBerryValid(void);
struct BerryTree *GetBerryTreeInfo(u8 id);
bool32 ObjectEventInteractionWaterBerryTree(void);
bool8 IsPlayerFacingEmptyBerryTreePatch(void);
bool8 TryToWaterBerryTree(void);
void ClearBerryTrees(void);
void BerryTreeTimeUpdate(s32 minutes);
void PlantBerryTree(u8 id, u8 berry, u8 stage, bool8 sparkle);
void RemoveBerryTree(u8 id);
u8 GetBerryTypeByBerryTreeId(u8 id);
u8 GetStageByBerryTreeId(u8);
void GetBerryNameByBerryType(u8 berry, u8 *string);
void ResetBerryTreeSparkleFlag(u8 id);
void Bag_ChooseBerry(void);
void ObjectEventInteractionGetBerryTreeData(void);
void ObjectEventInteractionPlantBerryTree(void);
void ObjectEventInteractionPickBerryTree(void);
void ObjectEventInteractionRemoveBerryTree(void);
bool8 PlayerHasBerries(void);
void SetBerryTreesSeen(void);
bool32 BerryTreeGrow(struct BerryTree *tree);

extern const struct BerryInfo gBerryInfo[];
extern const struct SpriteFrameImage gPicTable_PechaBerryTree[];

static inline enum BerryID SanitizeBerryID(enum BerryID berryID)
{
    if (berryID == BERRY_NONE || berryID >= BERRY_COUNT)
        return BERRY_CHERI;
    return berryID;
}

static inline const u8 *Berry_GetDynamicName(enum BerryID berry)
{
    if (berry == BERRY_ENIGMA && IsEnigmaBerryValid())
        return gSaveBlock1Ptr->enigmaBerry.berry.name;
    else
        return gBerryInfo[SanitizeBerryID(berry)].name;
}

static inline u32 Berry_GetFirmness(enum BerryID berry)
{
    if (berry == BERRY_ENIGMA && IsEnigmaBerryValid())
        return gSaveBlock1Ptr->enigmaBerry.berry.firmness;
    else
        return gBerryInfo[SanitizeBerryID(berry)].firmness;
}

static inline u32 Berry_GetSize(enum BerryID berry)
{
    if (berry == BERRY_ENIGMA && IsEnigmaBerryValid())
        return gSaveBlock1Ptr->enigmaBerry.berry.size;
    else
        return gBerryInfo[SanitizeBerryID(berry)].size;
}

static inline u32 Berry_GetMaxYield(enum BerryID berry)
{
    if (berry == BERRY_ENIGMA && IsEnigmaBerryValid())
        return gSaveBlock1Ptr->enigmaBerry.berry.maxYield;
    else
        return gBerryInfo[SanitizeBerryID(berry)].maxYield;
}

static inline u32 Berry_GetMinYield(enum BerryID berry)
{
    if (berry == BERRY_ENIGMA && IsEnigmaBerryValid())
        return gSaveBlock1Ptr->enigmaBerry.berry.minYield;
    else
        return gBerryInfo[SanitizeBerryID(berry)].minYield;
}

static inline const u8 *Berry_GetDescription1(enum BerryID berry)
{
    if (berry == BERRY_ENIGMA && IsEnigmaBerryValid())
        return (const u8*)gSaveBlock1Ptr->enigmaBerry.berry.description1;
    else
        return gBerryInfo[SanitizeBerryID(berry)].description1;
}

static inline const u8 *Berry_GetDescription2(enum BerryID berry)
{
    if (berry == BERRY_ENIGMA && IsEnigmaBerryValid())
        return (const u8*)gSaveBlock1Ptr->enigmaBerry.berry.description2;
    else
        return gBerryInfo[SanitizeBerryID(berry)].description2;
}

static inline u32 Berry_GetStageDuration(enum BerryID berry)
{
    if (berry == BERRY_ENIGMA && IsEnigmaBerryValid())
        return gSaveBlock1Ptr->enigmaBerry.berry.stageDuration;
    else
        return gBerryInfo[SanitizeBerryID(berry)].stageDuration;
}

static inline u32 Berry_GetFlavor(enum BerryID berryID, enum BerryFlavor flavorID)
{
    if (berryID == BERRY_ENIGMA && IsEnigmaBerryValid())
        switch (flavorID)
        {
            default:
            case FLAVOR_SPICY:
                return gSaveBlock1Ptr->enigmaBerry.berry.spicy;
            case FLAVOR_DRY:
                return gSaveBlock1Ptr->enigmaBerry.berry.dry;
            case FLAVOR_SWEET:
                return gSaveBlock1Ptr->enigmaBerry.berry.sweet;
            case FLAVOR_BITTER:
                return gSaveBlock1Ptr->enigmaBerry.berry.bitter;
            case FLAVOR_SOUR:
                return gSaveBlock1Ptr->enigmaBerry.berry.sour;
        }
    else
        return gBerryInfo[SanitizeBerryID(berryID)].flavors[flavorID];
}

static inline u32 Berry_GetSmoothness(enum BerryID berry)
{
    if (berry == BERRY_ENIGMA && IsEnigmaBerryValid())
        return gSaveBlock1Ptr->enigmaBerry.berry.smoothness;
    else
        return gBerryInfo[SanitizeBerryID(berry)].smoothness;
}

static inline const u32 *Berry_GetImageTiles(enum BerryID berry)
{
    return gBerryInfo[berry].imageTiles;
}

static inline const u32 *Berry_GetImagePalette(enum BerryID berry)
{
    return gBerryInfo[berry].imagePalette;
}

static inline const u8 *Berry_GetName(enum BerryID berry)
{
    return gBerryInfo[berry].name;
}

static inline const struct SpriteFrameImage *Berry_GetTreeImages(enum BerryID berry)
{
    return gBerryInfo[berry].treeImages;
}

static inline const u8 *Berry_GetTreePaletteSlots(enum BerryID berry)
{
    return gBerryInfo[berry].treePaletteSlots;
}

static inline u16 Berry_GetCrushPowder(enum BerryID berry)
{
    return gBerryInfo[berry].crushPowder;
}

static inline u8 Berry_GetCrushDifficulty(enum BerryID berry)
{
    return gBerryInfo[berry].crushDifficulty;
}

#endif // GUARD_BERRY_H
