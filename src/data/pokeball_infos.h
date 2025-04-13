const struct PokeballInfo gPokeballInfo[POKEBALL_COUNT] =
{
    [BALL_POKE] =
    {
        .openFadeColor = RGB(31, 22, 30),
        .particleAnimFunc = PokeBallOpenParticleAnimation,
        .particleAnimNum = 0,
        .particleSheet = &gParticleSpriteSheet_PokeBall,
        .particlePalette = &gParticlePalette_PokeBall,
        .particleTemplate = &gParticleSpriteTemplate_PokeBall,
        .spriteSheet = &gSpriteSheet_PokeBall,
        .spritePalette = &gSpritePalette_PokeBall,
        .spriteTemplate = &gSpriteTemplate_PokeBall,
    },

    [BALL_GREAT] =
    {
        .openFadeColor = RGB(16, 23, 30),
        .particleAnimFunc = GreatBallOpenParticleAnimation,
        .particleAnimNum = 0,
        .particleSheet = &gParticleSpriteSheet_GreatBall,
        .particlePalette = &gParticlePalette_GreatBall,
        .particleTemplate = &gParticleSpriteTemplate_GreatBall,
        .spriteSheet = &gSpriteSheet_GreatBall,
        .spritePalette = &gSpritePalette_GreatBall,
        .spriteTemplate = &gSpriteTemplate_GreatBall,
    },

    [BALL_SAFARI] =
    {
        .openFadeColor = RGB(23, 30, 20),
        .particleAnimFunc = SafariBallOpenParticleAnimation,
        .particleAnimNum = 0,
        .particleSheet = &gParticleSpriteSheet_SafariBall,
        .particlePalette = &gParticlePalette_SafariBall,
        .particleTemplate = &gParticleSpriteTemplate_SafariBall,
        .spriteSheet = &gSpriteSheet_SafariBall,
        .spritePalette = &gSpritePalette_SafariBall,
        .spriteTemplate = &gSpriteTemplate_SafariBall,
    },

    [BALL_ULTRA] =
    {
        .openFadeColor = RGB(31, 31, 15),
        .particleAnimFunc = UltraBallOpenParticleAnimation,
        .particleAnimNum = 5,
        .particleSheet = &gParticleSpriteSheet_UltraBall,
        .particlePalette = &gParticlePalette_UltraBall,
        .particleTemplate = &gParticleSpriteTemplate_UltraBall,
        .spriteSheet = &gSpriteSheet_UltraBall,
        .spritePalette = &gSpritePalette_UltraBall,
        .spriteTemplate = &gSpriteTemplate_UltraBall,
    },

    [BALL_MASTER] =
    {
        .openFadeColor = RGB(23, 20, 28),
        .particleAnimFunc = MasterBallOpenParticleAnimation,
        .particleAnimNum = 1,
        .particleSheet = &gParticleSpriteSheet_MasterBall,
        .particlePalette = &gParticlePalette_MasterBall,
        .particleTemplate = &gParticleSpriteTemplate_MasterBall,
        .spriteSheet = &gSpriteSheet_MasterBall,
        .spritePalette = &gSpritePalette_MasterBall,
        .spriteTemplate = &gSpriteTemplate_MasterBall,
    },

    [BALL_NET] =
    {
        .openFadeColor = RGB(21, 31, 25),
        .particleAnimFunc = SafariBallOpenParticleAnimation,
        .particleAnimNum = 2,
        .particleSheet = &gParticleSpriteSheet_NetBall,
        .particlePalette = &gParticlePalette_NetBall,
        .particleTemplate = &gParticleSpriteTemplate_NetBall,
        .spriteSheet = &gSpriteSheet_NetBall,
        .spritePalette = &gSpritePalette_NetBall,
        .spriteTemplate = &gSpriteTemplate_NetBall,
    },

    [BALL_DIVE] =
    {
        .openFadeColor = RGB(12, 25, 30),
        .particleAnimFunc = DiveBallOpenParticleAnimation,
        .particleAnimNum = 2,
        .particleSheet = &gParticleSpriteSheet_DiveBall,
        .particlePalette = &gParticlePalette_DiveBall,
        .particleTemplate = &gParticleSpriteTemplate_DiveBall,
        .spriteSheet = &gSpriteSheet_DiveBall,
        .spritePalette = &gSpritePalette_DiveBall,
        .spriteTemplate = &gSpriteTemplate_DiveBall,
    },

    [BALL_NEST] =
    {
        .openFadeColor = RGB(30, 27, 10),
        .particleAnimFunc = UltraBallOpenParticleAnimation,
        .particleAnimNum = 3,
        .particleSheet = &gParticleSpriteSheet_NestBall,
        .particlePalette = &gParticlePalette_NestBall,
        .particleTemplate = &gParticleSpriteTemplate_NestBall,
        .spriteSheet = &gSpriteSheet_NestBall,
        .spritePalette = &gSpritePalette_NestBall,
        .spriteTemplate = &gSpriteTemplate_NestBall,
    },

    [BALL_REPEAT] =
    {
        .openFadeColor = RGB(31, 24, 16),
        .particleAnimFunc = RepeatBallOpenParticleAnimation,
        .particleAnimNum = 5,
        .particleSheet = &gParticleSpriteSheet_RepeatBall,
        .particlePalette = &gParticlePalette_RepeatBall,
        .particleTemplate = &gParticleSpriteTemplate_RepeatBall,
        .spriteSheet = &gSpriteSheet_RepeatBall,
        .spritePalette = &gSpritePalette_RepeatBall,
        .spriteTemplate = &gSpriteTemplate_RepeatBall,
    },

    [BALL_TIMER] =
    {
        .openFadeColor = RGB(29, 30, 30),
        .particleAnimFunc = TimerBallOpenParticleAnimation,
        .particleAnimNum = 5,
        .particleSheet = &gParticleSpriteSheet_TimerBall,
        .particlePalette = &gParticlePalette_TimerBall,
        .particleTemplate = &gParticleSpriteTemplate_TimerBall,
        .spriteSheet = &gSpriteSheet_TimerBall,
        .spritePalette = &gSpritePalette_TimerBall,
        .spriteTemplate = &gSpriteTemplate_TimerBall,
    },

    [BALL_LUXURY] =
    {
        .openFadeColor = RGB(31, 17, 10),
        .particleAnimFunc = GreatBallOpenParticleAnimation,
        .particleAnimNum = 4,
        .particleSheet = &gParticleSpriteSheet_LuxuryBall,
        .particlePalette = &gParticlePalette_LuxuryBall,
        .particleTemplate = &gParticleSpriteTemplate_LuxuryBall,
        .spriteSheet = &gSpriteSheet_LuxuryBall,
        .spritePalette = &gSpritePalette_LuxuryBall,
        .spriteTemplate = &gSpriteTemplate_LuxuryBall,
    },

    [BALL_PREMIER] =
    {
        .openFadeColor = RGB(31, 9, 10),
        .particleAnimFunc = PremierBallOpenParticleAnimation,
        .particleAnimNum = 4,
        .particleSheet = &gParticleSpriteSheet_PremierBall,
        .particlePalette = &gParticlePalette_PremierBall,
        .particleTemplate = &gParticleSpriteTemplate_PremierBall,
        .spriteSheet = &gSpriteSheet_PremierBall,
        .spritePalette = &gSpritePalette_PremierBall,
        .spriteTemplate = &gSpriteTemplate_PremierBall,
    },

};
