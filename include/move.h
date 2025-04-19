#ifndef GUARD_MOVE_H
#define GUARD_MOVE_H

#include "global.h"
#include "battle_scripts.h"
#include "constants/contest.h"
#include "constants/moves.h"


struct BattleMoveEffect
{
    const u8 *battleScript;
    u8 battleTvScore;
};

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
    const u8 *battleAnimScript;
};

extern const struct MoveInfo gMoveInfo[MOVES_COUNT];
extern const struct BattleMoveEffect gBattleMoveEffects[];

bool32 IsHMMove(enum Move move);

static inline enum Move SanitizeMoveId(enum Move moveId)
{
    if (moveId >= MOVES_COUNT)
        return MOVE_NONE;
    else
        return moveId;
}

static inline const u8 *GetMoveName(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gMoveInfo[moveId].name == NULL)
        return gMoveInfo[MOVE_NONE].name;
    return gMoveInfo[moveId].name;
}

static inline const u8 *GetMoveDescription(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gMoveInfo[moveId].description == NULL)
        return gMoveInfo[MOVE_NONE].description;
    return gMoveInfo[moveId].description;
}

static inline u32 GetMoveEffect(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].effect;
}

static inline u32 GetMoveType(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].type;
}

static inline u32 GetMovePower(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].power;
}

static inline u32 GetMoveAccuracy(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].accuracy;
}

static inline u32 GetMoveTarget(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].target;
}

static inline u32 GetMovePP(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].pp;
}

static inline s32 GetMovePriority(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].priority;
}

static inline u32 GetMoveSecondaryEffectChance(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].secondaryEffectChance;
}

static inline bool32 IsContactMove(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].makesContact;
}

static inline bool32 IsMoveAffectedByProtect(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].protectAffected;
}

static inline bool32 IsMoveAffectedByMagicCoat(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].magicCoatAffected;
}

static inline bool32 IsMoveAffectedBySnatch(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].snatchAffected;
}

static inline bool32 IsMoveAffectedByMirrorMove(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].mirrorMoveAffected;
}

static inline bool32 IsMoveAffectedByKingsRock(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].kingsRockAffected;
}

static inline bool32 IsValidApprenticeMove(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].validApprenticeMove;
}

static inline u32 GetMoveContestEffect(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].contestEffect;
}

static inline u32 GetMoveContestCategory(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].contestCategory;
}

static inline u32 GetMoveContestComboStarter(u32 moveId)
{
    return gMoveInfo[SanitizeMoveId(moveId)].contestComboStarterId;
}

static inline u32 GetMoveContestComboMoves(u32 moveId, u32 comboMove)
{
    return gMoveInfo[SanitizeMoveId(moveId)].contestComboMoves[comboMove];
}

static inline const u8 *GetMoveAnimationScript(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gMoveInfo[moveId].battleAnimScript == NULL)
    {
        DebugPrintfLevel(MGBA_LOG_WARN, "No animation for moveId=%u", moveId);
        return gMoveInfo[MOVE_NONE].battleAnimScript;
    }
    return gMoveInfo[moveId].battleAnimScript;
}

static inline const u8 *GetMoveBattleScript(u32 moveId)
{
    moveId = SanitizeMoveId(moveId);
    if (gBattleMoveEffects[gMoveInfo[moveId].effect].battleScript == NULL)
    {
        DebugPrintfLevel(MGBA_LOG_WARN, "No effect for moveId=%u", moveId);
        return BattleScript_EffectPlaceholder;
    }
    return gBattleMoveEffects[gMoveInfo[moveId].effect].battleScript;
}

#endif //GUARD_MOVE_H