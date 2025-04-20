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

static inline const u8 *Nature_GetName(enum Nature nature)
{
    return gNatureInfo[nature].name;
}

static inline u8 Nature_GetStatUp(enum Nature nature)
{
    return gNatureInfo[nature].statUp;
}

static inline u8 Nature_GetStatDown(enum Nature nature)
{
    return gNatureInfo[nature].statDown;
}

static inline u8 Nature_GetBackAnim(enum Nature nature)
{
    return gNatureInfo[nature].backAnim;
}

static inline const u8 *Nature_GetPokeBlockAnim(enum Nature nature)
{
    return gNatureInfo[nature].pokeBlockAnim;
}

static inline const u8 *Nature_GetBattlePalacePercents(enum Nature nature)
{
    return gNatureInfo[nature].battlePalacePercents;
}

static inline u8 Nature_GetBattlePalaceFlavorText(enum Nature nature)
{
    return gNatureInfo[nature].battlePalaceFlavorText;
}

static inline u8 Nature_GetBattlePalaceSmokescreen(enum Nature nature)
{
    return gNatureInfo[nature].battlePalaceSmokescreen;
}

static inline const u8 *Nature_GetNatureGirlMessage(enum Nature nature)
{
    return gNatureInfo[nature].natureGirlMessage;
}

#endif //GUARD_NATURE_H