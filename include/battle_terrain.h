#ifndef GUARD_TERRAIN_H
#define GUARD_TERRAIN_H

#include "task.h"
#include "battle_bg.h"
#include "constants/battle_terrain.h"

struct BattleTerrainInfo
{
    u16 naturePowerMove;
    s16 camouflageBlend;
    u8 camouflageType;
    u16 secretPowerMove;
    u8 secretPowerEffect;
    const TaskFunc introSlide;
    const struct BattleBackground battleBackground;
};

extern const struct BattleTerrainInfo gBattleTerrainInfos[NUM_BATTLE_ENVIRONMENTS];

static inline u32 SanitizeBattleTerrain(u32 battleTerrain)
{
    if (battleTerrain >= NUM_BATTLE_ENVIRONMENTS)
        return BATTLE_ENVIRONMENT_GRASS;
    return battleTerrain;
}

static inline u16 BattleTerrain_GetNaturePowerMove(u32 battleTerrain)
{
    return gBattleTerrainInfos[SanitizeBattleTerrain(battleTerrain)].naturePowerMove;
}

static inline s16 BattleTerrain_GetCamouflageBlend(u32 battleTerrain)
{
    return gBattleTerrainInfos[SanitizeBattleTerrain(battleTerrain)].camouflageBlend;
}

static inline u8 BattleTerrain_GetCamouflageType(u32 battleTerrain)
{
    return gBattleTerrainInfos[SanitizeBattleTerrain(battleTerrain)].camouflageType;
}

static inline u16 BattleTerrain_GetSecretPowerMove(u32 battleTerrain)
{
    return gBattleTerrainInfos[SanitizeBattleTerrain(battleTerrain)].secretPowerMove;
}

static inline u8 BattleTerrain_GetSecretPowerEffect(u32 battleTerrain)
{
    return gBattleTerrainInfos[SanitizeBattleTerrain(battleTerrain)].secretPowerEffect;
}

static inline const TaskFunc BattleTerrain_GetIntroSlide(u32 battleTerrain)
{
    return gBattleTerrainInfos[SanitizeBattleTerrain(battleTerrain)].introSlide;
}

static inline const struct BattleBackground BattleTerrain_GetBattleBackground(u32 battleTerrain)
{
    return gBattleTerrainInfos[SanitizeBattleTerrain(battleTerrain)].battleBackground;
}


#endif//GUARD_TERRAIN_H