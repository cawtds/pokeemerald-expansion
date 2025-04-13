
static const struct OamData sBallOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sBallAnimSeq3[] =
{
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sBallAnimSeq5[] =
{
    ANIMCMD_FRAME(4, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sBallAnimSeq4[] =
{
    ANIMCMD_FRAME(8, 5),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sBallAnimSeq6[] =
{
    ANIMCMD_FRAME(12, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sBallAnimSeq0[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END,
};

static const union AnimCmd sBallAnimSeq1[] =
{
    ANIMCMD_FRAME(4, 5),
    ANIMCMD_FRAME(8, 5),
    ANIMCMD_END,
};

static const union AnimCmd sBallAnimSeq2[] =
{
    ANIMCMD_FRAME(4, 5),
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_END,
};

static const union AnimCmd *const sBallAnimSequences[] =
{
    sBallAnimSeq0,
    sBallAnimSeq1,
    sBallAnimSeq2,

    // unused?
    sBallAnimSeq3,
    sBallAnimSeq4,
    sBallAnimSeq5,
    sBallAnimSeq6,
};

static const union AffineAnimCmd sAffineAnim_BallRotate_0[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 0, 1),
    AFFINEANIMCMD_JUMP(0),
};

static const union AffineAnimCmd sAffineAnim_BallRotate_Right[] =
{
    AFFINEANIMCMD_FRAME(0, 0, -3, 1),
    AFFINEANIMCMD_JUMP(0),
};

static const union AffineAnimCmd sAffineAnim_BallRotate_Left[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 3, 1),
    AFFINEANIMCMD_JUMP(0),
};

static const union AffineAnimCmd sAffineAnim_BallRotate_3[] =
{
    AFFINEANIMCMD_FRAME(256, 256, 0, 0),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_BallRotate_4[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 25, 1),
    AFFINEANIMCMD_JUMP(0),
};

static const union AffineAnimCmd *const sAffineAnim_BallRotate[] =
{
    [BALL_AFFINE_ANIM_0] = sAffineAnim_BallRotate_0,
    [BALL_ROTATE_RIGHT]  = sAffineAnim_BallRotate_Right,
    [BALL_ROTATE_LEFT]   = sAffineAnim_BallRotate_Left,
    [BALL_AFFINE_ANIM_3] = sAffineAnim_BallRotate_3,
    [BALL_AFFINE_ANIM_4] = sAffineAnim_BallRotate_4,
};

// sprite sheets
const struct CompressedSpriteSheet gSpriteSheet_PokeBall =
{
    .data = gBallGfx_Poke,
    .size = 384,
    .tag = GFX_TAG_POKE_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_GreatBall =
{
    .data = gBallGfx_Great,
    .size = 384,
    .tag = GFX_TAG_GREAT_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_SafariBall =
{
    .data = gBallGfx_Safari,
    .size = 384,
    .tag = GFX_TAG_SAFARI_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_UltraBall =
{
    .data = gBallGfx_Ultra,
    .size = 384,
    .tag = GFX_TAG_ULTRA_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_MasterBall =
{
    .data = gBallGfx_Master,
    .size = 384,
    .tag = GFX_TAG_MASTER_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_NetBall =
{
    .data = gBallGfx_Net,
    .size = 384,
    .tag = GFX_TAG_NET_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_DiveBall =
{
    .data = gBallGfx_Dive,
    .size = 384,
    .tag = GFX_TAG_DIVE_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_NestBall =
{
    .data = gBallGfx_Nest,
    .size = 384,
    .tag = GFX_TAG_NEST_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_RepeatBall =
{
    .data = gBallGfx_Repeat,
    .size = 384,
    .tag = GFX_TAG_REPEAT_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_TimerBall =
{
    .data = gBallGfx_Timer,
    .size = 384,
    .tag = GFX_TAG_TIMER_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_LuxuryBall =
{
    .data = gBallGfx_Luxury,
    .size = 384,
    .tag = GFX_TAG_LUXURY_BALL,
};

const struct CompressedSpriteSheet gSpriteSheet_PremierBall =
{
    .data = gBallGfx_Premier,
    .size = 384,
    .tag = GFX_TAG_PREMIER_BALL,
};


// sprite palettes
const struct CompressedSpritePalette gSpritePalette_PokeBall =
{
    .data = gBallPal_Poke,
    .tag = GFX_TAG_POKE_BALL,
};

const struct CompressedSpritePalette gSpritePalette_GreatBall =
{
    .data = gBallPal_Great,
    .tag = GFX_TAG_GREAT_BALL,
};

const struct CompressedSpritePalette gSpritePalette_SafariBall =
{
    .data = gBallPal_Safari,
    .tag = GFX_TAG_SAFARI_BALL,
};

const struct CompressedSpritePalette gSpritePalette_UltraBall =
{
    .data = gBallPal_Ultra,
    .tag = GFX_TAG_ULTRA_BALL,
};

const struct CompressedSpritePalette gSpritePalette_MasterBall =
{
    .data = gBallPal_Master,
    .tag = GFX_TAG_MASTER_BALL,
};

const struct CompressedSpritePalette gSpritePalette_NetBall =
{
    .data = gBallPal_Net,
    .tag = GFX_TAG_NET_BALL,
};

const struct CompressedSpritePalette gSpritePalette_DiveBall =
{
    .data = gBallPal_Dive,
    .tag = GFX_TAG_DIVE_BALL,
};

const struct CompressedSpritePalette gSpritePalette_NestBall =
{
    .data = gBallPal_Nest,
    .tag = GFX_TAG_NEST_BALL,
};

const struct CompressedSpritePalette gSpritePalette_RepeatBall =
{
    .data = gBallPal_Repeat,
    .tag = GFX_TAG_REPEAT_BALL,
};

const struct CompressedSpritePalette gSpritePalette_TimerBall =
{
    .data = gBallPal_Timer,
    .tag = GFX_TAG_TIMER_BALL,
};

const struct CompressedSpritePalette gSpritePalette_LuxuryBall =
{
    .data = gBallPal_Luxury,
    .tag = GFX_TAG_LUXURY_BALL,
};

const struct CompressedSpritePalette gSpritePalette_PremierBall =
{
    .data = gBallPal_Premier,
    .tag = GFX_TAG_PREMIER_BALL,
};


// sprite templates
const struct SpriteTemplate gSpriteTemplate_PokeBall =
{
    .tileTag = GFX_TAG_POKE_BALL,
    .paletteTag = GFX_TAG_POKE_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_GreatBall =
{
    .tileTag = GFX_TAG_GREAT_BALL,
    .paletteTag = GFX_TAG_GREAT_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_SafariBall =
{
    .tileTag = GFX_TAG_SAFARI_BALL,
    .paletteTag = GFX_TAG_SAFARI_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_UltraBall =
{
    .tileTag = GFX_TAG_ULTRA_BALL,
    .paletteTag = GFX_TAG_ULTRA_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_MasterBall =
{
    .tileTag = GFX_TAG_MASTER_BALL,
    .paletteTag = GFX_TAG_MASTER_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_NetBall =
{
    .tileTag = GFX_TAG_NET_BALL,
    .paletteTag = GFX_TAG_NET_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_DiveBall =
{
    .tileTag = GFX_TAG_DIVE_BALL,
    .paletteTag = GFX_TAG_DIVE_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_NestBall =
{
    .tileTag = GFX_TAG_NEST_BALL,
    .paletteTag = GFX_TAG_NEST_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_RepeatBall =
{
    .tileTag = GFX_TAG_REPEAT_BALL,
    .paletteTag = GFX_TAG_REPEAT_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_TimerBall =
{
    .tileTag = GFX_TAG_TIMER_BALL,
    .paletteTag = GFX_TAG_TIMER_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_LuxuryBall =
{
    .tileTag = GFX_TAG_LUXURY_BALL,
    .paletteTag = GFX_TAG_LUXURY_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};

const struct SpriteTemplate gSpriteTemplate_PremierBall =
{
    .tileTag = GFX_TAG_PREMIER_BALL,
    .paletteTag = GFX_TAG_PREMIER_BALL,
    .oam = &sBallOamData,
    .anims = sBallAnimSequences,
    .images = NULL,
    .affineAnims = sAffineAnim_BallRotate,
    .callback = SpriteCB_BallThrow,
};


