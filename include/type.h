#ifndef GUARD_TYPE_H
#define GUARD_TYPE_H

#include "constants/types.h"

struct TypeInfo
{
    const u8 name[TYPE_NAME_LENGTH + 1];
    const u8 moveText[17];
    u16 menuInfoOffset;
    u8 paletteNum;
    enum DamageCategory damageCategory;
    const u32 *const paletteTMHM;
    const u8 *effectiveness;
};

extern const struct TypeInfo gTypeInfos[NUMBER_OF_MON_TYPES];

static inline const u8 *GetTypeName(u32 typeId)
{
    return gTypeInfos[typeId].name;
}

static inline const u8 *GetTypeMoveText(u32 typeId)
{
    return gTypeInfos[typeId].moveText;
}

static inline const u16 GetTypeMenuInfoOffset(u32 typeId)
{
    return gTypeInfos[typeId].menuInfoOffset;
}

static inline u8 GetTypePaletteNum(u32 typeId)
{
    return gTypeInfos[typeId].paletteNum;
}

static inline enum DamageCategory GetTypeDamageCategory(u32 typeId)
{
    return gTypeInfos[typeId].damageCategory;
}

static inline const u32 *GetTypeTMHMPalette(u32 typeId)
{
    return gTypeInfos[typeId].paletteTMHM;
}

static inline u8 GetTypeEffectiveness(u32 attackingType, u32 defendingType)
{
    return gTypeInfos[attackingType].effectiveness[defendingType];
}

#endif//GUARD_TYPE_H