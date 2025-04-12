#ifndef GUARD_TYPE_H
#define GUARD_TYPE_H

#include "constants/types.h"

struct TypeInfo
{
    const u8 name[TYPE_NAME_LENGTH + 1];
    const u8 moveText[17];
    u16 menuInfoOffset;
    u8 paletteNum:4;
    u8 damageCategory:2;
    const u32 *const paletteTMHM;
    const u8 *effectiveness[NUMBER_OF_MON_TYPES];
};

extern const struct TypeInfo gTypeInfos[NUMBER_OF_MON_TYPES];

static inline u32 SanitizeTypeId(u32 typeId)
{
    if (typeId >= NUMBER_OF_MON_TYPES)
        return TYPE_MYSTERY;
    else
        return typeId;
}

static inline const u8 *GetTypeName(u32 typeId)
{
    typeId = SanitizeTypeId(typeId);
    if (gTypeInfos[typeId].name == NULL)
        return gTypeInfos[TYPE_MYSTERY].name;
    return gTypeInfos[typeId].name;
}

static inline const u8 *GetTypeMoveText(u32 typeId)
{
    typeId = SanitizeTypeId(typeId);
    if (gTypeInfos[typeId].moveText == NULL)
        return gTypeInfos[TYPE_MYSTERY].moveText;
    return gTypeInfos[typeId].moveText;
}

static inline const u16 GetTypeMenuInfoOffset(u32 typeId)
{
    return gTypeInfos[SanitizeTypeId(typeId)].menuInfoOffset;
}

static inline const u32 *GetTypeTMHMPalette(u32 typeId)
{
    typeId = SanitizeTypeId(typeId);
    if (gTypeInfos[typeId].paletteTMHM == NULL)
        return gTypeInfos[TYPE_MYSTERY].paletteTMHM;
    return gTypeInfos[typeId].paletteTMHM;
}

#endif//GUARD_TYPE_H