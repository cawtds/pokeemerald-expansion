#ifndef GUARD_NATURE_H
#define GUARD_NATURE_H

#include "global.h"
#include "constants/natures.h"

struct NatureInfo
{
    const u8 *name;
    u8 statUp;
    u8 statDown;
    u8 backAnim;
    u8 pokeBlockAnim[2];
    u8 battlePalacePercents[4];
    u8 battlePalaceFlavorText;
    u8 battlePalaceSmokescreen;
    const u8 *natureGirlMessage;
};

extern const struct NatureInfo gNatureInfo[NUM_NATURES];

static inline enum Nature SanitizeNatureId(enum Nature nature)
{
    if (nature >= NUM_NATURES)
        return NATURE_HARDY;
    return nature;
}

static inline const u8 *Nature_GetName(enum Nature nature)
{
    nature = SanitizeNatureId(nature);
    if (gNatureInfo[nature].name == NULL)
        return gNatureInfo[NATURE_HARDY].name;
    return gNatureInfo[nature].name;
}

static inline u8 Nature_GetStatUp(enum Nature nature)
{
    return gNatureInfo[SanitizeNatureId(nature)].statUp;
}

static inline u8 Nature_GetStatDown(enum Nature nature)
{
    return gNatureInfo[SanitizeNatureId(nature)].statDown;
}

static inline u8 Nature_GetBackAnim(enum Nature nature)
{
    return gNatureInfo[SanitizeNatureId(nature)].backAnim;
}

static inline const u8 *Nature_GetPokeBlockAnim(enum Nature nature)
{
    return gNatureInfo[SanitizeNatureId(nature)].pokeBlockAnim;
}

static inline const u8 *Nature_GetBattlePalacePercents(enum Nature nature)
{
    return gNatureInfo[SanitizeNatureId(nature)].battlePalacePercents;
}

static inline u8 Nature_GetBattlePalaceFlavorText(enum Nature nature)
{
    return gNatureInfo[SanitizeNatureId(nature)].battlePalaceFlavorText;
}

static inline u8 Nature_GetBattlePalaceSmokescreen(enum Nature nature)
{
    return gNatureInfo[SanitizeNatureId(nature)].battlePalaceSmokescreen;
}

static inline const u8 *Nature_GetNatureGirlMessage(enum Nature nature)
{
    nature = SanitizeNatureId(nature);
    if (gNatureInfo[nature].natureGirlMessage == NULL)
        return gNatureInfo[NATURE_HARDY].natureGirlMessage;
    return gNatureInfo[nature].natureGirlMessage;
}

#endif //GUARD_NATURE_H