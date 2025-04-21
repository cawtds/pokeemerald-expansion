#ifndef GUARD_BERRY_H
#define GUARD_BERRY_H

#include "global.h"

// needs to be identical to struct EngimaBerryData
struct BerryData
{
    const u8 name[BERRY_NAME_LENGTH + 1];
    u8 firmness;
    u16 size;
    u8 maxYield;
    u8 minYield;
    const u8 *description1;
    const u8 *description2;
    u8 stageDuration;
    u8 spicy;
    u8 dry;
    u8 sweet;
    u8 bitter;
    u8 sour;
    u8 smoothness;
    //u8 padding;
};

struct BerryInfo
{
    const struct BerryData berryData;
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
const struct BerryData *GetBerryData(u8 berry);
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

static inline const u32 *Berry_GetImageTiles(enum Berry berry)
{
    return gBerryInfo[berry].imageTiles;
}

static inline const u32 *Berry_GetImagePalette(enum Berry berry)
{
    return gBerryInfo[berry].imagePalette;
}

static inline const u8 *Berry_GetName(enum Berry berry)
{
    return gBerryInfo[berry].berryData.name;
}

static inline const struct SpriteFrameImage *Berry_GetTreeImages(enum Berry berry)
{
    return gBerryInfo[berry].treeImages;
}

static inline const u8 *Berry_GetTreePaletteSlots(enum Berry berry)
{
    return gBerryInfo[berry].treePaletteSlots;
}

static inline u16 Berry_GetCrushPowder(enum Berry berry)
{
    return gBerryInfo[berry].crushPowder;
}

static inline u8 Berry_GetCrushDifficulty(enum Berry berry)
{
    return gBerryInfo[berry].crushDifficulty;
}

#endif // GUARD_BERRY_H
