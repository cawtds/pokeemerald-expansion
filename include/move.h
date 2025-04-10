#ifndef GUARD_MOVE_H
#define GUARD_MOVE_H

#include "constants/contest.h"
#include "constants/moves.h"

struct MoveInfo
{
    const u8 *name;
    const u8 *description;
    u8 effect;
    u8 power;
    u8 type;
    u8 accuracy;
    u8 pp;
    u8 secondaryEffectChance;
    u8 target;
    s8 priority;
    bool8 makesContact:1;
    bool8 protectAffected:1;
    bool8 magicCoatAffected:1;
    bool8 snatchAffected:1;
    bool8 mirrorMoveAffected:1;
    bool8 kingsRockAffected:1;
    bool8 validApprenticeMove:1;
    bool8 unusedFlags:1;
    u8 contestEffect;
    u8 contestCategory:3;
    u8 contestComboStarterId;
    u8 contestComboMoves[MAX_COMBO_MOVES];
};

extern const struct MoveInfo gMovesInfo[MOVES_COUNT];

static inline u32 SanitizeMoveId(u32 moveId)
{
    if (moveId >= MOVES_COUNT)
        return MOVE_NONE;
    else
        return moveId;
}

static inline const u8 *GetMoveName(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gMovesInfo[moveId].name == NULL)
        return gMovesInfo[MOVE_NONE].name;
    return gMovesInfo[moveId].name;
}

static inline const u8 *GetMoveDescription(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gMovesInfo[moveId].description == NULL)
        return gMovesInfo[MOVE_NONE].description;
    return gMovesInfo[moveId].description;
}

static inline bool32 GetMoveIsApprenticeValid(u32 moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].validApprenticeMove;
}

static inline u32 GetMoveContestEffect(u32 moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].contestEffect;
}

static inline u32 GetMoveContestCategory(u32 moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].contestCategory;
}

static inline u32 GetMoveContestComboStarter(u32 moveId)
{
    return gMovesInfo[SanitizeMoveId(moveId)].contestComboStarterId;
}

static inline u32 GetMoveContestComboMoves(u32 moveId, u32 comboMove)
{
    return gMovesInfo[SanitizeMoveId(moveId)].contestComboMoves[comboMove];
}

#endif //GUARD_MOVE_H