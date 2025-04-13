static const union AnimCmd sAnim_RegularBall[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(0, 1, .hFlip = TRUE),
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_MasterBall[] =
{
    ANIMCMD_FRAME(3, 1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_NetDiveBall[] =
{
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_NestBall[] =
{
    ANIMCMD_FRAME(5, 1),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_LuxuryPremierBall[] =
{
    ANIMCMD_FRAME(6, 4),
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_UltraRepeatTimerBall[] =
{
    ANIMCMD_FRAME(7, 4),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnims_BallParticles[] =
{
    sAnim_RegularBall,
    sAnim_MasterBall,
    sAnim_NetDiveBall,
    sAnim_NestBall,
    sAnim_LuxuryPremierBall,
    sAnim_UltraRepeatTimerBall,
};

// particle sprite sheets
const struct CompressedSpriteSheet gParticleSpriteSheet_PokeBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_POKEBALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_GreatBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_GREATBALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_SafariBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_SAFARIBALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_UltraBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_ULTRABALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_MasterBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_MASTERBALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_NetBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_NETBALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_DiveBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_DIVEBALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_NestBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_NESTBALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_RepeatBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_REPEATBALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_TimerBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_TIMERBALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_LuxuryBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_LUXURYBALL,
};

const struct CompressedSpriteSheet gParticleSpriteSheet_PremierBall =
{
    .data = gBattleAnimSpriteGfx_Particles,
    .size = 0x100,
    .tag = TAG_PARTICLES_PREMIERBALL,
};


// particle palettes
const struct CompressedSpritePalette gParticlePalette_PokeBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_POKEBALL,
};

const struct CompressedSpritePalette gParticlePalette_GreatBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_GREATBALL,
};

const struct CompressedSpritePalette gParticlePalette_SafariBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_SAFARIBALL,
};

const struct CompressedSpritePalette gParticlePalette_UltraBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_ULTRABALL,
};

const struct CompressedSpritePalette gParticlePalette_MasterBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_MASTERBALL,
};

const struct CompressedSpritePalette gParticlePalette_NetBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_NETBALL,
};

const struct CompressedSpritePalette gParticlePalette_DiveBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_DIVEBALL,
};

const struct CompressedSpritePalette gParticlePalette_NestBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_NESTBALL,
};

const struct CompressedSpritePalette gParticlePalette_RepeatBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_REPEATBALL,
};

const struct CompressedSpritePalette gParticlePalette_TimerBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_TIMERBALL,
};

const struct CompressedSpritePalette gParticlePalette_LuxuryBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_LUXURYBALL,
};

const struct CompressedSpritePalette gParticlePalette_PremierBall =
{
    .data = gBattleAnimSpritePal_CircleImpact,
    .tag = TAG_PARTICLES_PREMIERBALL,
};


// particle sprite templates
const struct SpriteTemplate gParticleSpriteTemplate_PokeBall =
{
    .tileTag = TAG_PARTICLES_POKEBALL,
    .paletteTag = TAG_PARTICLES_POKEBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_GreatBall =
{
    .tileTag = TAG_PARTICLES_GREATBALL,
    .paletteTag = TAG_PARTICLES_GREATBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_SafariBall =
{
    .tileTag = TAG_PARTICLES_SAFARIBALL,
    .paletteTag = TAG_PARTICLES_SAFARIBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_UltraBall =
{
    .tileTag = TAG_PARTICLES_ULTRABALL,
    .paletteTag = TAG_PARTICLES_ULTRABALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_MasterBall =
{
    .tileTag = TAG_PARTICLES_MASTERBALL,
    .paletteTag = TAG_PARTICLES_MASTERBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_NetBall =
{
    .tileTag = TAG_PARTICLES_NETBALL,
    .paletteTag = TAG_PARTICLES_NETBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_DiveBall =
{
    .tileTag = TAG_PARTICLES_DIVEBALL,
    .paletteTag = TAG_PARTICLES_DIVEBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_NestBall =
{
    .tileTag = TAG_PARTICLES_NESTBALL,
    .paletteTag = TAG_PARTICLES_NESTBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_RepeatBall =
{
    .tileTag = TAG_PARTICLES_REPEATBALL,
    .paletteTag = TAG_PARTICLES_REPEATBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_TimerBall =
{
    .tileTag = TAG_PARTICLES_TIMERBALL,
    .paletteTag = TAG_PARTICLES_TIMERBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_LuxuryBall =
{
    .tileTag = TAG_PARTICLES_LUXURYBALL,
    .paletteTag = TAG_PARTICLES_LUXURYBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gParticleSpriteTemplate_PremierBall =
{
    .tileTag = TAG_PARTICLES_PREMIERBALL,
    .paletteTag = TAG_PARTICLES_PREMIERBALL,
    .oam = &gOamData_AffineOff_ObjNormal_8x8,
    .anims = sAnims_BallParticles,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};


