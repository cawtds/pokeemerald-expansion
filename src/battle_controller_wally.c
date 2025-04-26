#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_tv.h"
#include "bg.h"
#include "data.h"
#include "item.h"
#include "item_menu.h"
#include "link.h"
#include "main.h"
#include "m4a.h"
#include "palette.h"
#include "party_menu.h"
#include "pokeball.h"
#include "pokemon.h"
#include "random.h"
#include "reshow_battle_screen.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "util.h"
#include "window.h"
#include "constants/battle_anim.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "constants/rgb.h"

// this file's functions
static void WallyHandleSetRawMonData(u32 battler);
static void WallyHandleLoadMonSprite(u32 battler);
static void WallyHandleSwitchInAnim(u32 battler);
static void WallyHandleReturnMonToBall(u32 battler);
static void WallyHandleDrawTrainerPic(u32 battler);
static void WallyHandleTrainerSlide(u32 battler);
static void WallyHandleTrainerSlideBack(u32 battler);
static void WallyHandleFaintAnimation(u32 battler);
static void WallyHandlePaletteFade(u32 battler);
static void WallyHandleSuccessBallThrowAnim(u32 battler);
static void WallyHandleBallThrowAnim(u32 battler);
static void WallyHandlePause(u32 battler);
static void WallyHandleMoveAnimation(u32 battler);
static void WallyHandlePrintString(u32 battler);
static void WallyHandlePrintSelectionString(u32 battler);
static void WallyHandleChooseAction(u32 battler);
static void WallyHandleYesNoBox(u32 battler);
static void WallyHandleChooseMove(u32 battler);
static void WallyHandleChooseItem(u32 battler);
static void WallyHandleChoosePokemon(u32 battler);
static void WallyHandleCmd23(u32 battler);
static void WallyHandleHealthBarUpdate(u32 battler);
static void WallyHandleExpUpdate(u32 battler);
static void WallyHandleStatusIconUpdate(u32 battler);
static void WallyHandleStatusAnimation(u32 battler);
static void WallyHandleStatusXor(u32 battler);
static void WallyHandleDataTransfer(u32 battler);
static void WallyHandleDMA3Transfer(u32 battler);
static void WallyHandlePlayBGM(u32 battler);
static void WallyHandleCmd32(u32 battler);
static void WallyHandleTwoReturnValues(u32 battler);
static void WallyHandleChosenMonReturnValue(u32 battler);
static void WallyHandleOneReturnValue(u32 battler);
static void WallyHandleOneReturnValue_Duplicate(u32 battler);
static void WallyHandleClearUnkVar(u32 battler);
static void WallyHandleSetUnkVar(u32 battler);
static void WallyHandleClearUnkFlag(u32 battler);
static void WallyHandleToggleUnkFlag(u32 battler);
static void WallyHandleHitAnimation(u32 battler);
static void WallyHandleCantSwitch(u32 battler);
static void WallyHandlePlaySE(u32 battler);
static void WallyHandlePlayFanfareOrBGM(u32 battler);
static void WallyHandleFaintingCry(u32 battler);
static void WallyHandleIntroSlide(u32 battler);
static void WallyHandleIntroTrainerBallThrow(u32 battler);
static void WallyHandleDrawPartyStatusSummary(u32 battler);
static void WallyHandleHidePartyStatusSummary(u32 battler);
static void WallyHandleEndBounceEffect(u32 battler);
static void WallyHandleSpriteInvisibility(u32 battler);
static void WallyHandleBattleAnimation(u32 battler);
static void WallyHandleLinkStandbyMsg(u32 battler);
static void WallyHandleResetActionMoveSelection(u32 battler);
static void WallyHandleEndLinkBattle(u32 battler);
static void WallyCmdEnd(u32 battler);

static void WallyBufferRunCommand(u32 battler);
static void WallyBufferExecCompleted(u32 battler);
static void CompleteOnChosenItem(u32 battler);
static void Intro_WaitForShinyAnimAndHealthbox(u32 battler);
static void WallyDoMoveAnimation(u32 battler);
static void Task_StartSendOutAnim(u8 taskId);

static void (*const sWallyBufferCommands[CONTROLLER_CMDS_COUNT])(u32 battler) =
{
    [CONTROLLER_GETMONDATA]               = BtlController_HandleGetMonData,
    [CONTROLLER_GETRAWMONDATA]            = BtlController_HandleGetRawMonData,
    [CONTROLLER_SETMONDATA]               = BtlController_HandleSetMonData,
    [CONTROLLER_SETRAWMONDATA]            = WallyHandleSetRawMonData,
    [CONTROLLER_LOADMONSPRITE]            = WallyHandleLoadMonSprite,
    [CONTROLLER_SWITCHINANIM]             = WallyHandleSwitchInAnim,
    [CONTROLLER_RETURNMONTOBALL]          = WallyHandleReturnMonToBall,
    [CONTROLLER_DRAWTRAINERPIC]           = WallyHandleDrawTrainerPic,
    [CONTROLLER_TRAINERSLIDE]             = WallyHandleTrainerSlide,
    [CONTROLLER_TRAINERSLIDEBACK]         = WallyHandleTrainerSlideBack,
    [CONTROLLER_FAINTANIMATION]           = WallyHandleFaintAnimation,
    [CONTROLLER_PALETTEFADE]              = WallyHandlePaletteFade,
    [CONTROLLER_SUCCESSBALLTHROWANIM]     = WallyHandleSuccessBallThrowAnim,
    [CONTROLLER_BALLTHROWANIM]            = WallyHandleBallThrowAnim,
    [CONTROLLER_PAUSE]                    = WallyHandlePause,
    [CONTROLLER_MOVEANIMATION]            = WallyHandleMoveAnimation,
    [CONTROLLER_PRINTSTRING]              = WallyHandlePrintString,
    [CONTROLLER_PRINTSTRINGPLAYERONLY]    = WallyHandlePrintSelectionString,
    [CONTROLLER_CHOOSEACTION]             = WallyHandleChooseAction,
    [CONTROLLER_YESNOBOX]                 = WallyHandleYesNoBox,
    [CONTROLLER_CHOOSEMOVE]               = WallyHandleChooseMove,
    [CONTROLLER_OPENBAG]                  = WallyHandleChooseItem,
    [CONTROLLER_CHOOSEPOKEMON]            = WallyHandleChoosePokemon,
    [CONTROLLER_23]                       = WallyHandleCmd23,
    [CONTROLLER_HEALTHBARUPDATE]          = WallyHandleHealthBarUpdate,
    [CONTROLLER_EXPUPDATE]                = WallyHandleExpUpdate,
    [CONTROLLER_STATUSICONUPDATE]         = WallyHandleStatusIconUpdate,
    [CONTROLLER_STATUSANIMATION]          = WallyHandleStatusAnimation,
    [CONTROLLER_STATUSXOR]                = WallyHandleStatusXor,
    [CONTROLLER_DATATRANSFER]             = WallyHandleDataTransfer,
    [CONTROLLER_DMA3TRANSFER]             = WallyHandleDMA3Transfer,
    [CONTROLLER_PLAYBGM]                  = WallyHandlePlayBGM,
    [CONTROLLER_32]                       = WallyHandleCmd32,
    [CONTROLLER_TWORETURNVALUES]          = WallyHandleTwoReturnValues,
    [CONTROLLER_CHOSENMONRETURNVALUE]     = WallyHandleChosenMonReturnValue,
    [CONTROLLER_ONERETURNVALUE]           = WallyHandleOneReturnValue,
    [CONTROLLER_ONERETURNVALUE_DUPLICATE] = WallyHandleOneReturnValue_Duplicate,
    [CONTROLLER_CLEARUNKVAR]              = WallyHandleClearUnkVar,
    [CONTROLLER_SETUNKVAR]                = WallyHandleSetUnkVar,
    [CONTROLLER_CLEARUNKFLAG]             = WallyHandleClearUnkFlag,
    [CONTROLLER_TOGGLEUNKFLAG]            = WallyHandleToggleUnkFlag,
    [CONTROLLER_HITANIMATION]             = WallyHandleHitAnimation,
    [CONTROLLER_CANTSWITCH]               = WallyHandleCantSwitch,
    [CONTROLLER_PLAYSE]                   = WallyHandlePlaySE,
    [CONTROLLER_PLAYFANFAREORBGM]         = WallyHandlePlayFanfareOrBGM,
    [CONTROLLER_FAINTINGCRY]              = WallyHandleFaintingCry,
    [CONTROLLER_INTROSLIDE]               = WallyHandleIntroSlide,
    [CONTROLLER_INTROTRAINERBALLTHROW]    = WallyHandleIntroTrainerBallThrow,
    [CONTROLLER_DRAWPARTYSTATUSSUMMARY]   = WallyHandleDrawPartyStatusSummary,
    [CONTROLLER_HIDEPARTYSTATUSSUMMARY]   = WallyHandleHidePartyStatusSummary,
    [CONTROLLER_ENDBOUNCE]                = WallyHandleEndBounceEffect,
    [CONTROLLER_SPRITEINVISIBILITY]       = WallyHandleSpriteInvisibility,
    [CONTROLLER_BATTLEANIMATION]          = WallyHandleBattleAnimation,
    [CONTROLLER_LINKSTANDBYMSG]           = WallyHandleLinkStandbyMsg,
    [CONTROLLER_RESETACTIONMOVESELECTION] = WallyHandleResetActionMoveSelection,
    [CONTROLLER_ENDLINKBATTLE]            = WallyHandleEndLinkBattle,
    [CONTROLLER_TERMINATOR_NOP]           = WallyCmdEnd
};

static void UNUSED SpriteCB_Null7(u32 battler)
{
}

void SetControllerToWally(u32 battler)
{
    gBattlerControllerFuncs[battler] = WallyBufferRunCommand;
    gBattlerControllerEndFuncs[battler] = WallyBufferExecCompleted;
    gBattleStruct->wallyBattleState = 0;
    gBattleStruct->wallyMovesState = 0;
    gBattleStruct->wallyWaitFrames = 0;
    gBattleStruct->wallyMoveFrames = 0;
}

static void WallyBufferRunCommand(u32 battler)
{
    if (gBattleControllerExecFlags & gBitTable[battler])
    {
        if (gBattleBufferA[battler][0] < ARRAY_COUNT(sWallyBufferCommands))
            sWallyBufferCommands[gBattleBufferA[battler][0]](battler);
        else
            WallyBufferExecCompleted(battler);
    }
}

static void WallyHandleActions(u32 battler)
{
    switch (gBattleStruct->wallyBattleState)
    {
    case 0:
        gBattleStruct->wallyWaitFrames = B_WAIT_TIME_LONG;
        gBattleStruct->wallyBattleState++;
    case 1:
        if (--gBattleStruct->wallyWaitFrames == 0)
        {
            PlaySE(SE_SELECT);
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_USE_MOVE, 0);
            WallyBufferExecCompleted(battler);
            gBattleStruct->wallyBattleState++;
            gBattleStruct->wallyMovesState = 0;
            gBattleStruct->wallyWaitFrames = B_WAIT_TIME_LONG;
        }
        break;
    case 2:
        if (--gBattleStruct->wallyWaitFrames == 0)
        {
            PlaySE(SE_SELECT);
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_USE_MOVE, 0);
            WallyBufferExecCompleted(battler);
            gBattleStruct->wallyBattleState++;
            gBattleStruct->wallyMovesState = 0;
            gBattleStruct->wallyWaitFrames = B_WAIT_TIME_LONG;
        }
        break;
    case 3:
        if (--gBattleStruct->wallyWaitFrames == 0)
        {
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_WALLY_THROW, 0);
            WallyBufferExecCompleted(battler);
            gBattleStruct->wallyBattleState++;
            gBattleStruct->wallyMovesState = 0;
            gBattleStruct->wallyWaitFrames = B_WAIT_TIME_LONG;
        }
        break;
    case 4:
        if (--gBattleStruct->wallyWaitFrames == 0)
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(0);
            ActionSelectionCreateCursorAt(1, 0);
            gBattleStruct->wallyWaitFrames = B_WAIT_TIME_LONG;
            gBattleStruct->wallyBattleState++;
        }
        break;
    case 5:
        if (--gBattleStruct->wallyWaitFrames == 0)
        {
            PlaySE(SE_SELECT);
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_USE_ITEM, 0);
            WallyBufferExecCompleted(battler);
        }
        break;
    }
}

static void CompleteOnBattlerSpriteCallbackDummy(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
        WallyBufferExecCompleted(battler);
}

static void CompleteOnInactiveTextPrinter(u32 battler)
{
    if (!IsTextPrinterActive(B_WIN_MSG))
        WallyBufferExecCompleted(battler);
}

static void CompleteOnFinishedAnimation(u32 battler)
{
    if (!gDoingBattleAnim)
        WallyBufferExecCompleted(battler);
}

static void OpenBagAfterPaletteFade(u32 battler)
{
    if (!gPaletteFade.active)
    {
        gBattlerControllerFuncs[battler] = CompleteOnChosenItem;
        ReshowBattleScreenDummy();
        FreeAllWindowBuffers();
        DoWallyTutorialBagMenu();
    }
}

static void CompleteOnChosenItem(u32 battler)
{
    if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
    {
        BtlController_EmitOneReturnValue(battler, BUFFER_B, gSpecialVar_ItemId);
        WallyBufferExecCompleted(battler);
    }
}

static void Intro_TryShinyAnimShowHealthbox(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim
     && !gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive)
        TryShinyAnimation(battler, &gPlayerParty[gBattlerPartyIndexes[battler]]);

    if (!gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].triedShinyMonAnim
     && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].ballAnimActive)
        TryShinyAnimation(BATTLE_PARTNER(battler), &gPlayerParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]]);

    if (!gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive
        && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].ballAnimActive
        && gSprites[gBattleControllerData[battler]].callback == SpriteCallbackDummy
        && gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
    {
        if (IsDoubleBattle() && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
        {
            DestroySprite(&gSprites[gBattleControllerData[BATTLE_PARTNER(battler)]]);
            UpdateHealthboxAttribute(gHealthboxSpriteIds[BATTLE_PARTNER(battler)], &gPlayerParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]], HEALTHBOX_ALL);
            StartHealthboxSlideIn(BATTLE_PARTNER(battler));
            SetHealthboxSpriteVisible(gHealthboxSpriteIds[BATTLE_PARTNER(battler)]);
        }
        DestroySprite(&gSprites[gBattleControllerData[battler]]);
        UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gPlayerParty[gBattlerPartyIndexes[battler]], HEALTHBOX_ALL);
        StartHealthboxSlideIn(battler);
        SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);

        gBattleSpritesDataPtr->animationData->introAnimActive = FALSE;
        gBattlerControllerFuncs[battler] = Intro_WaitForShinyAnimAndHealthbox;
    }

}

static void Intro_WaitForShinyAnimAndHealthbox(u32 battler)
{
    bool32 healthboxAnimDone = FALSE;

    if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy)
        healthboxAnimDone = TRUE;

    if (healthboxAnimDone && gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim
        && gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].finishedShinyMonAnim)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim = FALSE;

        gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].triedShinyMonAnim = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].finishedShinyMonAnim = FALSE;

        FreeSpriteTilesByTag(ANIM_TAG_GOLD_STARS);
        FreeSpritePaletteByTag(ANIM_TAG_GOLD_STARS);

        CreateTask(Task_PlayerController_RestoreBgmAfterCry, 10);
        HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);

        WallyBufferExecCompleted(battler);
    }
}

static void CompleteOnHealthbarDone(u32 battler)
{
    s16 hpValue = MoveBattleBar(battler, gHealthboxSpriteIds[battler], HEALTH_BAR, 0);

    SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);

    if (hpValue != -1)
    {
        UpdateHpTextInHealthbox(gHealthboxSpriteIds[battler], hpValue, HP_CURRENT);
    }
    else
    {
        HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
        WallyBufferExecCompleted(battler);
    }
}

static void DoHitAnimBlinkSpriteEffect(u32 battler)
{
    u8 spriteId = gBattlerSpriteIds[battler];

    if (gSprites[spriteId].data[1] == 32)
    {
        gSprites[spriteId].data[1] = 0;
        gSprites[spriteId].invisible = FALSE;
        gDoingBattleAnim = FALSE;
        WallyBufferExecCompleted(battler);
    }
    else
    {
        if ((gSprites[spriteId].data[1] % 4) == 0)
            gSprites[spriteId].invisible ^= 1;
        gSprites[spriteId].data[1]++;
    }
}

static void DoSwitchOutAnimation(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive)
    {
        FreeSpriteOamMatrix(&gSprites[gBattlerSpriteIds[battler]]);
        DestroySprite(&gSprites[gBattlerSpriteIds[battler]]);
        SetHealthboxSpriteInvisible(gHealthboxSpriteIds[battler]);
        WallyBufferExecCompleted(battler);
    }
}

static void CompleteOnBankSpriteCallbackDummy2(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
        WallyBufferExecCompleted(battler);
}

static void CompleteOnFinishedBattleAnimation(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].animFromTableActive)
        WallyBufferExecCompleted(battler);
}

static void WallyBufferExecCompleted(u32 battler)
{
    gBattlerControllerFuncs[battler] = WallyBufferRunCommand;
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        u8 playerId = GetMultiplayerId();

        PrepareBufferDataTransferLink(battler, 2, 4, &playerId);
        gBattleBufferA[battler][0] = CONTROLLER_TERMINATOR_NOP;
    }
    else
    {
        gBattleControllerExecFlags &= ~gBitTable[battler];
    }
}

static void UNUSED CompleteOnFinishedStatusAnimation(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].statusAnimActive)
        WallyBufferExecCompleted(battler);
}

static void WallyHandleSetRawMonData(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleLoadMonSprite(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleSwitchInAnim(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleReturnMonToBall(u32 battler)
{
    if (gBattleBufferA[battler][1] == 0)
    {
        InitAndLaunchSpecialAnimation(battler, battler, battler, B_ANIM_SWITCH_OUT_PLAYER_MON);
        gBattlerControllerFuncs[battler] = DoSwitchOutAnimation;
    }
    else
    {
        FreeSpriteOamMatrix(&gSprites[gBattlerSpriteIds[battler]]);
        DestroySprite(&gSprites[gBattlerSpriteIds[battler]]);
        SetHealthboxSpriteInvisible(gHealthboxSpriteIds[battler]);
        WallyBufferExecCompleted(battler);
    }
}

#define sSpeedX data[0]

static void WallyHandleDrawTrainerPic(u32 battler)
{
    DecompressTrainerBackPic(TRAINER_BACK_PIC_WALLY, battler);
    SetMultiuseSpriteTemplateToTrainerBack(TRAINER_BACK_PIC_WALLY, GetBattlerPosition(battler));
    gBattlerSpriteIds[battler] = CreateSprite(&gMultiuseSpriteTemplate,
                                               80,
                                               80 + 4 * (8 - gTrainerBackPicCoords[TRAINER_BACK_PIC_WALLY].size),
                                               30);
    gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = battler;
    gSprites[gBattlerSpriteIds[battler]].x2 = DISPLAY_WIDTH;
    gSprites[gBattlerSpriteIds[battler]].sSpeedX = -2;
    gSprites[gBattlerSpriteIds[battler]].callback = SpriteCB_TrainerSlideIn;
    gBattlerControllerFuncs[battler] = CompleteOnBattlerSpriteCallbackDummy;
}

static void WallyHandleTrainerSlide(u32 battler)
{
    DecompressTrainerBackPic(TRAINER_BACK_PIC_WALLY, battler);
    SetMultiuseSpriteTemplateToTrainerBack(TRAINER_BACK_PIC_WALLY, GetBattlerPosition(battler));
    gBattlerSpriteIds[battler] = CreateSprite(&gMultiuseSpriteTemplate,
                                               80,
                                               80 + 4 * (8 - gTrainerBackPicCoords[TRAINER_BACK_PIC_WALLY].size),
                                               30);
    gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = battler;
    gSprites[gBattlerSpriteIds[battler]].x2 = -96;
    gSprites[gBattlerSpriteIds[battler]].sSpeedX = 2;
    gSprites[gBattlerSpriteIds[battler]].callback = SpriteCB_TrainerSlideIn;
    gBattlerControllerFuncs[battler] = CompleteOnBankSpriteCallbackDummy2;
}

#undef sSpeedX

static void WallyHandleTrainerSlideBack(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleFaintAnimation(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandlePaletteFade(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleSuccessBallThrowAnim(u32 battler)
{
    gBattleSpritesDataPtr->animationData->ballThrowCaseId = BALL_3_SHAKES_SUCCESS;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(battler, battler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), B_ANIM_BALL_THROW_WITH_TRAINER);
    gBattlerControllerFuncs[battler] = CompleteOnFinishedAnimation;
}

static void WallyHandleBallThrowAnim(u32 battler)
{
    u8 ballThrowCaseId = gBattleBufferA[battler][1];

    gBattleSpritesDataPtr->animationData->ballThrowCaseId = ballThrowCaseId;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(battler, battler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), B_ANIM_BALL_THROW_WITH_TRAINER);
    gBattlerControllerFuncs[battler] = CompleteOnFinishedAnimation;
}

static void WallyHandlePause(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleMoveAnimation(u32 battler)
{
    u16 move = gBattleBufferA[battler][1] | (gBattleBufferA[battler][2] << 8);

    gAnimMoveTurn = gBattleBufferA[battler][3];
    gAnimMovePower = gBattleBufferA[battler][4] | (gBattleBufferA[battler][5] << 8);
    gAnimMoveDmg = gBattleBufferA[battler][6] | (gBattleBufferA[battler][7] << 8) | (gBattleBufferA[battler][8] << 16) | (gBattleBufferA[battler][9] << 24);
    gAnimFriendship = gBattleBufferA[battler][10];
    gWeatherMoveAnim = gBattleBufferA[battler][12] | (gBattleBufferA[battler][13] << 8);
    gAnimDisableStructPtr = (struct DisableStruct *)&gBattleBufferA[battler][16];
    gTransformedPersonalities[battler] = gAnimDisableStructPtr->transformedMonPersonality;
    if (IsMoveWithoutAnimation(move, gAnimMoveTurn)) // always returns FALSE
    {
        WallyBufferExecCompleted(battler);
    }
    else
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 0;
        gBattlerControllerFuncs[battler] = WallyDoMoveAnimation;
    }

}

static void WallyDoMoveAnimation(u32 battler)
{
    u16 move = gBattleBufferA[battler][1] | (gBattleBufferA[battler][2] << 8);

    switch (gBattleSpritesDataPtr->healthBoxesData[battler].animationState)
    {
    case 0:
        if (gBattleSpritesDataPtr->battlerData[battler].behindSubstitute)
        {
            InitAndLaunchSpecialAnimation(battler, battler, battler, B_ANIM_SUBSTITUTE_TO_MON);
        }
        gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 1;
        break;
    case 1:
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive)
        {
            SetBattlerSpriteAffineMode(ST_OAM_AFFINE_OFF);
            DoMoveAnim(move);
            gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 2;
        }
        break;
    case 2:
        gAnimScriptCallback();
        if (!gAnimScriptActive)
        {
            SetBattlerSpriteAffineMode(ST_OAM_AFFINE_NORMAL);
            if (gBattleSpritesDataPtr->battlerData[battler].behindSubstitute)
            {
                InitAndLaunchSpecialAnimation(battler, battler, battler, B_ANIM_MON_TO_SUBSTITUTE);
            }
            gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 3;
        }
        break;
    case 3:
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive)
        {
            CopyAllBattleSpritesInvisibilities();
            TrySetBehindSubstituteSpriteBit(battler, gBattleBufferA[battler][1] | (gBattleBufferA[battler][2] << 8));
            gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 0;
            WallyBufferExecCompleted(battler);
        }
        break;
    }
}

static void WallyHandlePrintString(u32 battler)
{
    u16 *stringId;

    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    stringId = (u16 *)(&gBattleBufferA[battler][2]);
    BufferStringBattle(battler, *stringId);
    BattlePutTextOnWindow(gDisplayedStringBattle, B_WIN_MSG);
    gBattlerControllerFuncs[battler] = CompleteOnInactiveTextPrinter;
}

static void WallyHandlePrintSelectionString(u32 battler)
{
    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        WallyHandlePrintString(battler);
    else
        WallyBufferExecCompleted(battler);
}

static void HandleChooseActionAfterDma3(u32 battler)
{
    if (!IsDma3ManagerBusyWithBgCopy())
    {
        gBattle_BG0_X = 0;
        gBattle_BG0_Y = DISPLAY_HEIGHT;
        gBattlerControllerFuncs[battler] = WallyHandleActions;
    }
}

static void WallyHandleChooseAction(u32 battler)
{
    s32 i;

    gBattlerControllerFuncs[battler] = HandleChooseActionAfterDma3;
    BattlePutTextOnWindow(gText_BattleMenu, B_WIN_ACTION_MENU);

    for (i = 0; i < 4; i++)
        ActionSelectionDestroyCursorAt(i);

    ActionSelectionCreateCursorAt(gActionSelectionCursor[battler], 0);
    BattleStringExpandPlaceholdersToDisplayedString(gText_WhatWillWallyDo);
    BattlePutTextOnWindow(gDisplayedStringBattle, B_WIN_ACTION_PROMPT);
}

static void WallyHandleYesNoBox(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleChooseMove(u32 battler)
{
    switch (gBattleStruct->wallyMovesState)
    {
    case 0:
        InitMoveSelectionsVarsAndStrings(battler);
        gBattleStruct->wallyMovesState++;
        gBattleStruct->wallyMoveFrames = 80;
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            gBattle_BG0_X = 0;
            gBattle_BG0_Y = DISPLAY_HEIGHT * 2;
            gBattleStruct->wallyMovesState++;
        }
        break;
    case 2:
        if (--gBattleStruct->wallyMoveFrames == 0)
        {
            PlaySE(SE_SELECT);
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, 0x100);
            WallyBufferExecCompleted(battler);
        }
        break;
    }
}

static void WallyHandleChooseItem(u32 battler)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gBattlerControllerFuncs[battler] = OpenBagAfterPaletteFade;
    gBattlerInMenuId = battler;
}

static void WallyHandleChoosePokemon(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleCmd23(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleHealthBarUpdate(u32 battler)
{
    s16 hpVal;

    LoadBattleBarGfx(0);
    hpVal = gBattleBufferA[battler][2] | (gBattleBufferA[battler][3] << 8);

    if (hpVal != INSTANT_HP_BAR_DROP)
    {
        u32 maxHP = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_MAX_HP);
        u32 curHP = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_HP);

        SetBattleBarStruct(battler, gHealthboxSpriteIds[battler], maxHP, curHP, hpVal);
    }
    else
    {
        u32 maxHP = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_MAX_HP);

        SetBattleBarStruct(battler, gHealthboxSpriteIds[battler], maxHP, 0, hpVal);
        UpdateHpTextInHealthbox(gHealthboxSpriteIds[battler], 0, HP_CURRENT);
    }

    gBattlerControllerFuncs[battler] = CompleteOnHealthbarDone;
}

static void WallyHandleExpUpdate(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleStatusIconUpdate(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleStatusAnimation(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleStatusXor(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleDataTransfer(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleDMA3Transfer(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandlePlayBGM(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleCmd32(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleTwoReturnValues(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleChosenMonReturnValue(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleOneReturnValue(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleOneReturnValue_Duplicate(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleClearUnkVar(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleSetUnkVar(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleClearUnkFlag(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleToggleUnkFlag(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleHitAnimation(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].invisible == TRUE)
    {
        WallyBufferExecCompleted(battler);
    }
    else
    {
        gDoingBattleAnim = TRUE;
        gSprites[gBattlerSpriteIds[battler]].data[1] = 0;
        DoHitAnimHealthboxEffect(battler);
        gBattlerControllerFuncs[battler] = DoHitAnimBlinkSpriteEffect;
    }
}

static void WallyHandleCantSwitch(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandlePlaySE(u32 battler)
{
    PlaySE(gBattleBufferA[battler][1] | (gBattleBufferA[battler][2] << 8));
    WallyBufferExecCompleted(battler);
}

static void WallyHandlePlayFanfareOrBGM(u32 battler)
{
    if (gBattleBufferA[battler][3])
    {
        BattleStopLowHpSound();
        PlayBGM(gBattleBufferA[battler][1] | (gBattleBufferA[battler][2] << 8));
    }
    else
    {
        PlayFanfare(gBattleBufferA[battler][1] | (gBattleBufferA[battler][2] << 8));
    }

    WallyBufferExecCompleted(battler);
}

static void WallyHandleFaintingCry(u32 battler)
{
    u16 species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);

    // Seems that it doesn't bother using CRY_MODE_FAINT because
    // Wally's Pokémon during the tutorial is never intended to faint.
    PlayCry_Normal(species, 25);
    WallyBufferExecCompleted(battler);
}

static void WallyHandleIntroSlide(u32 battler)
{
    HandleIntroSlide(gBattleBufferA[battler][1]);
    gIntroSlideFlags |= 1;
    WallyBufferExecCompleted(battler);
}

static void WallyHandleIntroTrainerBallThrow(u32 battler)
{
    u8 paletteNum;
    u8 taskId;

    SetSpritePrimaryCoordsFromSecondaryCoords(&gSprites[gBattlerSpriteIds[battler]]);

    gSprites[gBattlerSpriteIds[battler]].data[0] = 50;
    gSprites[gBattlerSpriteIds[battler]].data[2] = -40;
    gSprites[gBattlerSpriteIds[battler]].data[4] = gSprites[gBattlerSpriteIds[battler]].y;
    gSprites[gBattlerSpriteIds[battler]].callback = StartAnimLinearTranslation;
    gSprites[gBattlerSpriteIds[battler]].data[5] = battler;

    StoreSpriteCallbackInData6(&gSprites[gBattlerSpriteIds[battler]], SpriteCB_FreePlayerSpriteLoadMonSprite);
    StartSpriteAnim(&gSprites[gBattlerSpriteIds[battler]], 1);

    paletteNum = AllocSpritePalette(0xD6F8);
    LoadCompressedPalette(gTrainerBackPicPaletteTable[TRAINER_BACK_PIC_WALLY].data, OBJ_PLTT_ID(paletteNum), PLTT_SIZE_4BPP);
    gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = paletteNum;

    taskId = CreateTask(Task_StartSendOutAnim, 5);
    gTasks[taskId].data[0] = battler;

    if (gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusSummaryShown)
        gTasks[gBattlerStatusSummaryTaskId[battler]].func = Task_HidePartyStatusSummary;

    gBattleSpritesDataPtr->animationData->introAnimActive = TRUE;
    gBattlerControllerFuncs[battler] = BattleControllerDummy;
}

static void StartSendOutAnim(u8 battler)
{
    u16 species;

    gBattleSpritesDataPtr->battlerData[battler].transformSpecies = 0;
    gBattlerPartyIndexes[battler] = gBattleBufferA[battler][1];
    species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);
    gBattleControllerData[battler] = CreateInvisibleSpriteWithCallback(SpriteCB_WaitForBattlerBallReleaseAnim);
    SetMultiuseSpriteTemplateToPokemon(species, GetBattlerPosition(battler));
    gBattlerSpriteIds[battler] = CreateSprite(&gMultiuseSpriteTemplate,
                                        GetBattlerSpriteCoord(battler, BATTLER_COORD_X_2),
                                        GetBattlerSpriteDefault_Y(battler),
                                        GetBattlerSpriteSubpriority(battler));

    gSprites[gBattleControllerData[battler]].data[1] = gBattlerSpriteIds[battler];
    gSprites[gBattleControllerData[battler]].data[2] = battler;

    gSprites[gBattlerSpriteIds[battler]].data[0] = battler;
    gSprites[gBattlerSpriteIds[battler]].data[2] = species;
    gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = battler;

    StartSpriteAnim(&gSprites[gBattlerSpriteIds[battler]], gBattleMonForms[battler]);
    gSprites[gBattlerSpriteIds[battler]].invisible = TRUE;
    gSprites[gBattlerSpriteIds[battler]].callback = SpriteCallbackDummy;
    gSprites[gBattleControllerData[battler]].data[0] = DoPokeballSendOutAnimation(battler, 0, POKEBALL_PLAYER_SENDOUT);
}

static void Task_StartSendOutAnim(u8 taskId)
{
    if (gTasks[taskId].data[1] < 31)
    {
        gTasks[taskId].data[1]++;
    }
    else
    {
        u32 battler = gTasks[taskId].data[0];

        gBattleBufferA[battler][1] = gBattlerPartyIndexes[battler];
        StartSendOutAnim(battler);
        gBattlerControllerFuncs[battler] = Intro_TryShinyAnimShowHealthbox;
        DestroyTask(taskId);
    }
}

static void WallyHandleDrawPartyStatusSummary(u32 battler)
{
    if (gBattleBufferA[battler][1] != 0 && GetBattlerSide(battler) == B_SIDE_PLAYER)
    {
        WallyBufferExecCompleted(battler);
    }
    else
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusSummaryShown = 1;
        gBattlerStatusSummaryTaskId[battler] = CreatePartyStatusSummarySprites(battler, (struct HpAndStatus *)&gBattleBufferA[battler][4], gBattleBufferA[battler][1], gBattleBufferA[battler][2]);
        WallyBufferExecCompleted(battler);
    }
}

static void WallyHandleHidePartyStatusSummary(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleEndBounceEffect(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleSpriteInvisibility(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleBattleAnimation(u32 battler)
{
    u8 animationId = gBattleBufferA[battler][1];
    u16 argument = gBattleBufferA[battler][2] | (gBattleBufferA[battler][3] << 8);

    if (TryHandleLaunchBattleTableAnimation(battler, battler, battler, animationId, argument))
        WallyBufferExecCompleted(battler);
    else
        gBattlerControllerFuncs[battler] = CompleteOnFinishedBattleAnimation;
}

static void WallyHandleLinkStandbyMsg(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleResetActionMoveSelection(u32 battler)
{
    WallyBufferExecCompleted(battler);
}

static void WallyHandleEndLinkBattle(u32 battler)
{
    gBattleOutcome = gBattleBufferA[battler][1];
    FadeOutMapMusic(5);
    BeginFastPaletteFade(3);
    WallyBufferExecCompleted(battler);

    if (!(gBattleTypeFlags & BATTLE_TYPE_IS_MASTER) && gBattleTypeFlags & BATTLE_TYPE_LINK)
        gBattlerControllerFuncs[battler] = SetBattleEndCallbacks;
}

static void WallyCmdEnd(u32 battler)
{
}
