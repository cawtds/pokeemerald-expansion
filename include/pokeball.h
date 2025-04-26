#ifndef GUARD_POKEBALL_H
#define GUARD_POKEBALL_H

#include "task.h"
#include "constants/pokeball.h"

enum {
    BALL_AFFINE_ANIM_0,
    BALL_ROTATE_RIGHT,
    BALL_ROTATE_LEFT,
    BALL_AFFINE_ANIM_3,
    BALL_AFFINE_ANIM_4
};

struct PokeballInfo
{
    const struct CompressedSpriteSheet *particleSheet;
    const struct CompressedSpritePalette *particlePalette;
    const struct SpriteTemplate *particleTemplate;
    const struct CompressedSpriteSheet *spriteSheet;
    const struct CompressedSpritePalette *spritePalette;
    const struct SpriteTemplate *spriteTemplate;
    TaskFunc particleAnimFunc;
    u16 openFadeColor;
    u8 particleAnimNum;
};

extern const struct PokeballInfo gPokeballInfo[POKEBALL_COUNT];

#define POKEBALL_PLAYER_SENDOUT     0xFF
#define POKEBALL_OPPONENT_SENDOUT   0xFE

u8 DoPokeballSendOutAnimation(u32 battler, s16 pan, u8 kindOfThrow);
void CreatePokeballSpriteToReleaseMon(u8 monSpriteId, u8 monPalNum, u8 x, u8 y, u8 oamPriority, u8 subpriority, u8 delay, u32 fadePalettes, u16 species);
u8 CreateTradePokeballSprite(u8 monSpriteId, u8 monPalNum, u8 x, u8 y, u8 oamPriority, u8 subPriority, u8 delay, u32 fadePalettes);
void StartHealthboxSlideIn(u8 battler);
void DoHitAnimHealthboxEffect(u8 battler);
void LoadBallGfx(enum Ball ballId);
void FreeBallGfx(enum Ball ballId);

static inline enum Ball SanitizeBallId(enum Ball ballId)
{
    if (ballId < POKEBALL_COUNT)
        return ballId;
    return BALL_POKE;
}

static inline u8 Ball_GetParticleAnimNum(enum Ball ballId)
{
    return gPokeballInfo[SanitizeBallId(ballId)].particleAnimNum;
}

static inline u16 Ball_GetOpenFadeColor(enum Ball ballId)
{
    return gPokeballInfo[SanitizeBallId(ballId)].openFadeColor;
}

static inline TaskFunc Ball_GetParticleAnimFunc(enum Ball ballId)
{
    return gPokeballInfo[SanitizeBallId(ballId)].particleAnimFunc;
}

static inline const struct CompressedSpriteSheet *Ball_GetParticleSheet(enum Ball ballId)
{
    return gPokeballInfo[SanitizeBallId(ballId)].particleSheet;
}

static inline const struct CompressedSpritePalette *Ball_GetParticlePalette(enum Ball ballId)
{
    return gPokeballInfo[SanitizeBallId(ballId)].particlePalette;
}

static inline const struct SpriteTemplate *Ball_GetParticleTemplate(enum Ball ballId)
{
    return gPokeballInfo[SanitizeBallId(ballId)].particleTemplate;
}

static inline const struct CompressedSpriteSheet *Ball_GetSpriteSheet(enum Ball ballId)
{
    return gPokeballInfo[SanitizeBallId(ballId)].spriteSheet;
}

static inline const struct CompressedSpritePalette *Ball_GetSpritePalette(enum Ball ballId)
{
    return gPokeballInfo[SanitizeBallId(ballId)].spritePalette;
}

static inline const struct SpriteTemplate *Ball_GetSpriteTemplate(enum Ball ballId)
{
    return gPokeballInfo[SanitizeBallId(ballId)].spriteTemplate;
}

#endif // GUARD_POKEBALL_H
