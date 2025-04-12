#include "global.h"
#include "graphics.h"
#include "type.h"
#include "constants/types.h"

#define TYPE_MUL_NO_EFFECT          0
#define TYPE_MUL_NOT_EFFECTIVE      5
#define TYPE_MUL_NORMAL             10
#define TYPE_MUL_SUPER_EFFECTIVE    20

#define X(a) (a == 2.0 ? TYPE_MUL_SUPER_EFFECTIVE : (a == 1.0 ? TYPE_MUL_NORMAL : (a == 0.5 ? TYPE_MUL_NOT_EFFECTIVE : TYPE_MUL_NO_EFFECT)))
#define ______ X(1.0) // Regular effectiveness.

static const u8 gTypeEffectivenessTable[NUMBER_OF_MON_TYPES][NUMBER_OF_MON_TYPES] =
{//                   Defender -->
 //  Attacker          Normal Fighting Flying  Poison  Ground   Rock    Bug     Ghost   Steel  Mystery  Fire   Water   Grass  Electric Psychic   Ice   Dragon   Dark
    [TYPE_NORMAL]   = {______, ______, ______, ______, ______, X(0.5), ______, X(0.0), X(0.5), ______, ______, ______, ______, ______, ______, ______, ______, ______, },
    [TYPE_FIGHTING] = {X(2.0), ______, X(0.5), X(0.5), ______, X(2.0), X(0.5), X(0.0), X(2.0), ______, ______, ______, ______, ______, X(0.5), X(2.0), ______, X(2.0), },
    [TYPE_FLYING]   = {______, X(2.0), ______, ______, ______, X(0.5), X(2.0), ______, X(0.5), ______, ______, ______, X(2.0), X(0.5), ______, ______, ______, ______, },
    [TYPE_POISON]   = {______, ______, ______, X(0.5), X(0.5), X(0.5), ______, X(0.5), X(0.0), ______, ______, ______, X(2.0), ______, ______, ______, ______, ______, },
    [TYPE_GROUND]   = {______, ______, X(0.0), X(2.0), ______, X(2.0), X(0.5), ______, X(2.0), ______, X(2.0), ______, X(0.5), X(2.0), ______, ______, ______, ______, },
    [TYPE_ROCK]     = {______, X(0.5), X(2.0), ______, X(0.5), ______, X(2.0), ______, X(0.5), ______, X(2.0), ______, ______, ______, ______, X(2.0), ______, ______, },
    [TYPE_BUG]      = {______, X(0.5), X(0.5), X(0.5), ______, ______, ______, X(0.5), X(0.5), ______, X(0.5), ______, X(2.0), ______, X(2.0), ______, ______, X(2.0), },
    [TYPE_GHOST]    = {X(0.0), ______, ______, ______, ______, ______, ______, X(2.0), X(0.5), ______, ______, ______, ______, ______, X(2.0), ______, ______, X(0.5), },
    [TYPE_STEEL]    = {______, ______, ______, ______, ______, X(2.0), ______, ______, X(0.5), ______, X(0.5), X(0.5), ______, X(0.5), ______, X(2.0), ______, ______, },
    [TYPE_MYSTERY]  = {______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, },
    [TYPE_FIRE]     = {______, ______, ______, ______, ______, X(0.5), X(2.0), ______, X(2.0), ______, X(0.5), X(0.5), X(2.0), ______, ______, X(2.0), X(0.5), ______, },
    [TYPE_WATER]    = {______, ______, ______, ______, X(2.0), X(2.0), ______, ______, ______, ______, X(2.0), X(0.5), X(0.5), ______, ______, ______, X(0.5), ______, },
    [TYPE_GRASS]    = {______, ______, X(0.5), X(0.5), X(2.0), X(2.0), X(0.5), ______, X(0.5), ______, X(0.5), X(2.0), X(0.5), ______, ______, ______, X(0.5), ______, },
    [TYPE_ELECTRIC] = {______, ______, X(2.0), ______, X(0.0), ______, ______, ______, ______, ______, ______, X(2.0), X(0.5), X(0.5), ______, ______, X(0.5), ______, },
    [TYPE_PSYCHIC]  = {______, X(2.0), ______, X(2.0), ______, ______, ______, ______, X(0.5), ______, ______, ______, ______, ______, X(0.5), ______, ______, X(0.0), },
    [TYPE_ICE]      = {______, ______, X(2.0), ______, X(2.0), ______, ______, ______, X(0.5), ______, X(0.5), X(0.5), X(2.0), ______, ______, X(0.5), X(2.0), ______, },
    [TYPE_DRAGON]   = {______, ______, ______, ______, ______, ______, ______, ______, X(0.5), ______, ______, ______, ______, ______, ______, ______, X(2.0), ______, },
    [TYPE_DARK]     = {______, X(0.5), ______, ______, ______, ______, ______, X(2.0), X(0.5), ______, ______, ______, ______, ______, X(2.0), ______, ______, X(0.5), },
};

#undef ______
#undef X

#include "data/type_infos.h"
