#include "global.h"
#include "battle.h"
#include "battle_ai_script_commands.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_interface.h"
#include "bg.h"
#include "data.h"
#include "item_use.h"
#include "link.h"
#include "main.h"
#include "m4a.h"
#include "palette.h"
#include "pokeball.h"
#include "pokemon.h"
#include "recorded_battle.h"
#include "reshow_battle_screen.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "test_runner.h"
#include "text.h"
#include "util.h"
#include "window.h"
#include "constants/battle_anim.h"
#include "constants/songs.h"

static void RecordedPlayerHandleLoadMonSprite(u32 battler);
static void RecordedPlayerHandleSwitchInAnim(u32 battler);
static void RecordedPlayerHandleDrawTrainerPic(u32 battler);
static void RecordedPlayerHandleTrainerSlideBack(u32 battler);
static void RecordedPlayerHandlePause(u32 battler);
static void RecordedPlayerHandleMoveAnimation(u32 battler);
static void RecordedPlayerHandlePrintString(u32 battler);
static void RecordedPlayerHandlePrintSelectionString(u32 battler);
static void RecordedPlayerHandleChooseAction(u32 battler);
static void RecordedPlayerHandleYesNoBox(u32 battler);
static void RecordedPlayerHandleChooseMove(u32 battler);
static void RecordedPlayerHandleChooseItem(u32 battler);
static void RecordedPlayerHandleChoosePokemon(u32 battler);
static void RecordedPlayerHandleCmd23(u32 battler);
static void RecordedPlayerHandleHealthBarUpdate(u32 battler);
static void RecordedPlayerHandleExpUpdate(u32 battler);
static void RecordedPlayerHandleStatusIconUpdate(u32 battler);
static void RecordedPlayerHandleStatusAnimation(u32 battler);
static void RecordedPlayerHandleStatusXor(u32 battler);
static void RecordedPlayerHandleDataTransfer(u32 battler);
static void RecordedPlayerHandleDMA3Transfer(u32 battler);
static void RecordedPlayerHandlePlayBGM(u32 battler);
static void RecordedPlayerHandleCmd32(u32 battler);
static void RecordedPlayerHandleTwoReturnValues(u32 battler);
static void RecordedPlayerHandleChosenMonReturnValue(u32 battler);
static void RecordedPlayerHandleOneReturnValue(u32 battler);
static void RecordedPlayerHandleOneReturnValue_Duplicate(u32 battler);
static void RecordedPlayerHandleClearUnkVar(u32 battler);
static void RecordedPlayerHandleSetUnkVar(u32 battler);
static void RecordedPlayerHandleClearUnkFlag(u32 battler);
static void RecordedPlayerHandleToggleUnkFlag(u32 battler);
static void RecordedPlayerHandleHitAnimation(u32 battler);
static void RecordedPlayerHandleCantSwitch(u32 battler);
static void RecordedPlayerHandlePlaySE(u32 battler);
static void RecordedPlayerHandlePlayFanfareOrBGM(u32 battler);
static void RecordedPlayerHandleFaintingCry(u32 battler);
static void RecordedPlayerHandleIntroSlide(u32 battler);
static void RecordedPlayerHandleIntroTrainerBallThrow(u32 battler);
static void RecordedPlayerHandleDrawPartyStatusSummary(u32 battler);
static void RecordedPlayerHandleHidePartyStatusSummary(u32 battler);
static void RecordedPlayerHandleEndBounceEffect(u32 battler);
static void RecordedPlayerHandleSpriteInvisibility(u32 battler);
static void RecordedPlayerHandleBattleAnimation(u32 battler);
static void RecordedPlayerHandleLinkStandbyMsg(u32 battler);
static void RecordedPlayerHandleResetActionMoveSelection(u32 battler);
static void RecordedPlayerHandleEndLinkBattle(u32 battler);
static void RecordedPlayerCmdEnd(u32 battler);

static void RecordedPlayerBufferRunCommand(u32 battler);
static void RecordedPlayerBufferExecCompleted(u32 battler);
static void SwitchIn_WaitAndEnd(u32 battler);
static void RecordedPlayerDoMoveAnimation(u32 battler);
static void Task_StartSendOutAnim(u8 taskId);
static void EndDrawPartyStatusSummary(u32 battler);

static void (*const sRecordedPlayerBufferCommands[CONTROLLER_CMDS_COUNT])(u32 battler) =
{
    [CONTROLLER_GETMONDATA]               = BtlController_HandleGetMonData,
    [CONTROLLER_GETRAWMONDATA]            = BtlController_Empty,
    [CONTROLLER_SETMONDATA]               = BtlController_HandleSetMonData,
    [CONTROLLER_SETRAWMONDATA]            = BtlController_HandleSetRawMonData,
    [CONTROLLER_LOADMONSPRITE]            = RecordedPlayerHandleLoadMonSprite,
    [CONTROLLER_SWITCHINANIM]             = RecordedPlayerHandleSwitchInAnim,
    [CONTROLLER_RETURNMONTOBALL]          = BtlController_HandleReturnMonToBall,
    [CONTROLLER_DRAWTRAINERPIC]           = RecordedPlayerHandleDrawTrainerPic,
    [CONTROLLER_TRAINERSLIDE]             = BtlController_Empty,
    [CONTROLLER_TRAINERSLIDEBACK]         = RecordedPlayerHandleTrainerSlideBack,
    [CONTROLLER_FAINTANIMATION]           = BtlController_HandleFaintAnimation,
    [CONTROLLER_PALETTEFADE]              = BtlController_Empty,
    [CONTROLLER_SUCCESSBALLTHROWANIM]     = BtlController_Empty,
    [CONTROLLER_BALLTHROWANIM]            = BtlController_Empty,
    [CONTROLLER_PAUSE]                    = RecordedPlayerHandlePause,
    [CONTROLLER_MOVEANIMATION]            = RecordedPlayerHandleMoveAnimation,
    [CONTROLLER_PRINTSTRING]              = RecordedPlayerHandlePrintString,
    [CONTROLLER_PRINTSTRINGPLAYERONLY]    = RecordedPlayerHandlePrintSelectionString,
    [CONTROLLER_CHOOSEACTION]             = RecordedPlayerHandleChooseAction,
    [CONTROLLER_YESNOBOX]                 = RecordedPlayerHandleYesNoBox,
    [CONTROLLER_CHOOSEMOVE]               = RecordedPlayerHandleChooseMove,
    [CONTROLLER_OPENBAG]                  = RecordedPlayerHandleChooseItem,
    [CONTROLLER_CHOOSEPOKEMON]            = RecordedPlayerHandleChoosePokemon,
    [CONTROLLER_23]                       = RecordedPlayerHandleCmd23,
    [CONTROLLER_HEALTHBARUPDATE]          = RecordedPlayerHandleHealthBarUpdate,
    [CONTROLLER_EXPUPDATE]                = RecordedPlayerHandleExpUpdate,
    [CONTROLLER_STATUSICONUPDATE]         = RecordedPlayerHandleStatusIconUpdate,
    [CONTROLLER_STATUSANIMATION]          = RecordedPlayerHandleStatusAnimation,
    [CONTROLLER_STATUSXOR]                = RecordedPlayerHandleStatusXor,
    [CONTROLLER_DATATRANSFER]             = RecordedPlayerHandleDataTransfer,
    [CONTROLLER_DMA3TRANSFER]             = RecordedPlayerHandleDMA3Transfer,
    [CONTROLLER_PLAYBGM]                  = RecordedPlayerHandlePlayBGM,
    [CONTROLLER_32]                       = RecordedPlayerHandleCmd32,
    [CONTROLLER_TWORETURNVALUES]          = RecordedPlayerHandleTwoReturnValues,
    [CONTROLLER_CHOSENMONRETURNVALUE]     = RecordedPlayerHandleChosenMonReturnValue,
    [CONTROLLER_ONERETURNVALUE]           = RecordedPlayerHandleOneReturnValue,
    [CONTROLLER_ONERETURNVALUE_DUPLICATE] = RecordedPlayerHandleOneReturnValue_Duplicate,
    [CONTROLLER_CLEARUNKVAR]              = RecordedPlayerHandleClearUnkVar,
    [CONTROLLER_SETUNKVAR]                = RecordedPlayerHandleSetUnkVar,
    [CONTROLLER_CLEARUNKFLAG]             = RecordedPlayerHandleClearUnkFlag,
    [CONTROLLER_TOGGLEUNKFLAG]            = RecordedPlayerHandleToggleUnkFlag,
    [CONTROLLER_HITANIMATION]             = RecordedPlayerHandleHitAnimation,
    [CONTROLLER_CANTSWITCH]               = RecordedPlayerHandleCantSwitch,
    [CONTROLLER_PLAYSE]                   = RecordedPlayerHandlePlaySE,
    [CONTROLLER_PLAYFANFAREORBGM]         = RecordedPlayerHandlePlayFanfareOrBGM,
    [CONTROLLER_FAINTINGCRY]              = RecordedPlayerHandleFaintingCry,
    [CONTROLLER_INTROSLIDE]               = RecordedPlayerHandleIntroSlide,
    [CONTROLLER_INTROTRAINERBALLTHROW]    = RecordedPlayerHandleIntroTrainerBallThrow,
    [CONTROLLER_DRAWPARTYSTATUSSUMMARY]   = RecordedPlayerHandleDrawPartyStatusSummary,
    [CONTROLLER_HIDEPARTYSTATUSSUMMARY]   = RecordedPlayerHandleHidePartyStatusSummary,
    [CONTROLLER_ENDBOUNCE]                = RecordedPlayerHandleEndBounceEffect,
    [CONTROLLER_SPRITEINVISIBILITY]       = RecordedPlayerHandleSpriteInvisibility,
    [CONTROLLER_BATTLEANIMATION]          = RecordedPlayerHandleBattleAnimation,
    [CONTROLLER_LINKSTANDBYMSG]           = RecordedPlayerHandleLinkStandbyMsg,
    [CONTROLLER_RESETACTIONMOVESELECTION] = RecordedPlayerHandleResetActionMoveSelection,
    [CONTROLLER_ENDLINKBATTLE]            = RecordedPlayerHandleEndLinkBattle,
    [CONTROLLER_TERMINATOR_NOP]           = RecordedPlayerCmdEnd
};

static void RecordedPlayerDummy(u32 battler)
{
}

void SetControllerToRecordedPlayer(u32 battler)
{
    gBattlerControllerFuncs[battler] = RecordedPlayerBufferRunCommand;
    gBattlerControllerEndFuncs[battler] = RecordedPlayerBufferExecCompleted;
}

static void RecordedPlayerBufferRunCommand(u32 battler)
{
    if (gBattleControllerExecFlags & gBitTable[battler])
    {
        if (gBattleBufferA[battler][0] < ARRAY_COUNT(sRecordedPlayerBufferCommands))
            sRecordedPlayerBufferCommands[gBattleBufferA[battler][0]](battler);
        else
            RecordedPlayerBufferExecCompleted(battler);
    }
}

static void CompleteOnBattlerSpriteCallbackDummy(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
        RecordedPlayerBufferExecCompleted(battler);
}

static void Intro_DelayAndEnd(u32 battler)
{
    if (--gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay == (u8)-1)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay = 0;
        RecordedPlayerBufferExecCompleted(battler);
    }
}

static void Intro_WaitForShinyAnimAndHealthbox(u32 battler)
{
    bool32 healthboxAnimDone = FALSE;

    if (GetBattlerPosition(battler) == B_POSITION_PLAYER_LEFT)
    {
        if (!IsDoubleBattle() || (IsDoubleBattle() && (gBattleTypeFlags & BATTLE_TYPE_MULTI)))
        {
            if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy)
                healthboxAnimDone = TRUE;
        }
        else
        {
            if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy
                && gSprites[gHealthboxSpriteIds[BATTLE_PARTNER(battler)]].callback == SpriteCallbackDummy)
            {
                healthboxAnimDone = TRUE;
            }
        }

        if (healthboxAnimDone && gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim
            && gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].finishedShinyMonAnim)
        {
            gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim = FALSE;
            gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim = FALSE;

            gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].triedShinyMonAnim = FALSE;
            gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].finishedShinyMonAnim = FALSE;

            FreeSpriteTilesByTag(ANIM_TAG_GOLD_STARS);
            FreeSpritePaletteByTag(ANIM_TAG_GOLD_STARS);

            HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
            if (IsDoubleBattle())
                HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]], BATTLE_PARTNER(battler));

            gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay = 3;
            gBattlerControllerFuncs[battler] = Intro_DelayAndEnd;
        }
    }
    else
    {
        if (!IsDoubleBattle() || (IsDoubleBattle() && (gBattleTypeFlags & BATTLE_TYPE_MULTI)))
        {
            if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy)
                healthboxAnimDone = TRUE;
        }
        else
        {
            if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy
                && gSprites[gHealthboxSpriteIds[BATTLE_PARTNER(battler)]].callback == SpriteCallbackDummy)
            {
                healthboxAnimDone = TRUE;
            }
        }

        if (IsCryPlayingOrClearCrySongs())
            healthboxAnimDone = FALSE;

        if (healthboxAnimDone)
        {
            gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay = 3;
            gBattlerControllerFuncs[battler] = Intro_DelayAndEnd;
        }
    }
}

static void Intro_TryShinyAnimShowHealthbox(u32 battler)
{
    bool32 bgmRestored = FALSE;

    if (GetBattlerPosition(battler) == B_POSITION_PLAYER_LEFT)
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim
        && !gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive)
            TryShinyAnimation(battler, &gPlayerParty[gBattlerPartyIndexes[battler]]);

        if (!gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].triedShinyMonAnim
        && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].ballAnimActive)
            TryShinyAnimation(BATTLE_PARTNER(battler), &gPlayerParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]]);
    }

    if (!gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive
        && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].ballAnimActive)
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted)
        {
            if (IsDoubleBattle() && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
            {
                UpdateHealthboxAttribute(gHealthboxSpriteIds[BATTLE_PARTNER(battler)], &gPlayerParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]], HEALTHBOX_ALL);
                StartHealthboxSlideIn(BATTLE_PARTNER(battler));
                SetHealthboxSpriteVisible(gHealthboxSpriteIds[BATTLE_PARTNER(battler)]);
            }
            UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gPlayerParty[gBattlerPartyIndexes[battler]], HEALTHBOX_ALL);
            StartHealthboxSlideIn(battler);
            SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);
        }
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted = TRUE;
    }

    if (gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted
        && !gBattleSpritesDataPtr->healthBoxesData[battler].waitForCry
        && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].waitForCry
        && !IsCryPlayingOrClearCrySongs())
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].bgmRestored)
        {
            if ((gBattleTypeFlags & BATTLE_TYPE_LINK) && (gBattleTypeFlags & BATTLE_TYPE_MULTI))
            {
                if (GetBattlerPosition(battler) == B_POSITION_PLAYER_LEFT)
                    m4aMPlayContinue(&gMPlayInfo_BGM);
            }
            else
            {
                m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, 0x100);
            }

        }
        gBattleSpritesDataPtr->healthBoxesData[battler].bgmRestored = TRUE;
        bgmRestored = TRUE;
    }

    if (bgmRestored && gSprites[gBattleControllerData[battler]].callback == SpriteCallbackDummy
        && gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
    {
        if (IsDoubleBattle() && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
            DestroySprite(&gSprites[gBattleControllerData[BATTLE_PARTNER(battler)]]);

        DestroySprite(&gSprites[gBattleControllerData[battler]]);
        gBattleSpritesDataPtr->animationData->introAnimActive = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].bgmRestored = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted = FALSE;
        gBattlerControllerFuncs[battler] = Intro_WaitForShinyAnimAndHealthbox;
    }
}

static void WaitForMonAnimAfterLoad(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].animEnded && gSprites[gBattlerSpriteIds[battler]].x2 == 0)
        RecordedPlayerBufferExecCompleted(battler);
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
        RecordedPlayerBufferExecCompleted(battler);
    }
}

static void CompleteOnInactiveTextPrinter(u32 battler)
{
    if (!IsTextPrinterActive(B_WIN_MSG))
        RecordedPlayerBufferExecCompleted(battler);
}

static void DoHitAnimBlinkSpriteEffect(u32 battler)
{
    u8 spriteId = gBattlerSpriteIds[battler];

    if (gSprites[spriteId].data[1] == 32)
    {
        gSprites[spriteId].data[1] = 0;
        gSprites[spriteId].invisible = FALSE;
        gDoingBattleAnim = FALSE;
        RecordedPlayerBufferExecCompleted(battler);
    }
    else
    {
        if ((gSprites[spriteId].data[1] % 4) == 0)
            gSprites[spriteId].invisible ^= 1;
        gSprites[spriteId].data[1]++;
    }
}

static void SwitchIn_ShowSubstitute(u32 battler)
{
    if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy)
    {
        CopyBattleSpriteInvisibility(battler);
        if (gBattleSpritesDataPtr->battlerData[battler].behindSubstitute)
            InitAndLaunchSpecialAnimation(battler, battler, battler, B_ANIM_MON_TO_SUBSTITUTE);

        gBattlerControllerFuncs[battler] = SwitchIn_WaitAndEnd;
    }
}

static void SwitchIn_WaitAndEnd(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive
        && gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
    {
        RecordedPlayerBufferExecCompleted(battler);
    }
}

static void SwitchIn_ShowHealthbox(u32 battler)
{
    if (gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim = FALSE;

        FreeSpriteTilesByTag(ANIM_TAG_GOLD_STARS);
        FreeSpritePaletteByTag(ANIM_TAG_GOLD_STARS);

        CreateTask(Task_PlayerController_RestoreBgmAfterCry, 10);
        HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
        StartSpriteAnim(&gSprites[gBattlerSpriteIds[battler]], 0);
        UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gPlayerParty[gBattlerPartyIndexes[battler]], HEALTHBOX_ALL);
        StartHealthboxSlideIn(battler);
        SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);

        gBattlerControllerFuncs[battler] = SwitchIn_ShowSubstitute;
    }
}

static void SwitchIn_TryShinyAnim(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim
     && !gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive)
    {
        TryShinyAnimation(battler, &gPlayerParty[gBattlerPartyIndexes[battler]]);
    }

    if (gSprites[gBattleControllerData[battler]].callback == SpriteCallbackDummy
     && !gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive)
    {
        DestroySprite(&gSprites[gBattleControllerData[battler]]);
        gBattlerControllerFuncs[battler] = SwitchIn_ShowHealthbox;
    }
}

static void RecordedPlayerBufferExecCompleted(u32 battler)
{
    gBattlerControllerFuncs[battler] = RecordedPlayerBufferRunCommand;
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

static void CompleteOnFinishedStatusAnimation(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].statusAnimActive)
        RecordedPlayerBufferExecCompleted(battler);
}

static void CompleteOnFinishedBattleAnimation(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].animFromTableActive)
        RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleLoadMonSprite(u32 battler)
{
    BtlController_HandleLoadMonSprite(battler, WaitForMonAnimAfterLoad);
}

static void RecordedPlayerHandleSwitchInAnim(u32 battler)
{
    BtlController_HandleSwitchInAnim(battler, SwitchIn_TryShinyAnim);
}

static void RecordedPlayerHandleDrawTrainerPic(u32 battler)
{
    u32 trainerPicId;
    bool32 isFrontPic;
    s16 xPos, yPos;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            trainerPicId = GetActiveBattlerLinkPlayerGender(battler);
        else
            trainerPicId = gLinkPlayers[gRecordedBattleMultiplayerId].gender;
    }
    else
    {
        trainerPicId = gLinkPlayers[0].gender;
    }

    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if ((GetBattlerPosition(battler) & BIT_FLANK) != 0) // second mon
            xPos = 90;
        else // first mon
            xPos = 32;

        if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
        {
            xPos = 90;
            yPos = (8 - gTrainerFrontPicCoords[trainerPicId].size) * 4 + 80;
        }
        else
        {
            yPos = (8 - gTrainerBackPicCoords[trainerPicId].size) * 4 + 80;
        }

    }
    else
    {
        xPos = 80;
        yPos = (8 - gTrainerBackPicCoords[trainerPicId].size) * 4 + 80;
    }

    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
    {
        isFrontPic = TRUE;
        trainerPicId = PlayerGenderToFrontTrainerPicId(gSaveBlock2Ptr->playerGender);
    }
    else
    {
        isFrontPic = FALSE;
    }

    BtlController_HandleDrawTrainerPic(battler, trainerPicId, xPos, yPos, GetBattlerSpriteSubpriority(battler), isFrontPic);
}

static void RecordedPlayerHandleTrainerSlideBack(u32 battler)
{
    BtlController_HandleTrainerSlideBack(battler, 35, FALSE);
}

static void RecordedPlayerHandlePause(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleMoveAnimation(u32 battler)
{
    if (!IsBattleSEPlaying(battler))
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
            RecordedPlayerBufferExecCompleted(battler);
        }
        else
        {
            gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 0;
            gBattlerControllerFuncs[battler] = RecordedPlayerDoMoveAnimation;
        }
    }
}

static void RecordedPlayerDoMoveAnimation(u32 battler)
{
    u16 move = gBattleBufferA[battler][1] | (gBattleBufferA[battler][2] << 8);
    u8 multihit = gBattleBufferA[battler][11];

    switch (gBattleSpritesDataPtr->healthBoxesData[battler].animationState)
    {
    case 0:
        if (gBattleSpritesDataPtr->battlerData[battler].behindSubstitute
            && !gBattleSpritesDataPtr->battlerData[battler].flag_x8)
        {
            gBattleSpritesDataPtr->battlerData[battler].flag_x8 = 1;
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
            if (gBattleSpritesDataPtr->battlerData[battler].behindSubstitute && multihit < 2)
            {
                InitAndLaunchSpecialAnimation(battler, battler, battler, B_ANIM_MON_TO_SUBSTITUTE);
                gBattleSpritesDataPtr->battlerData[battler].flag_x8 = 0;
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
            RecordedPlayerBufferExecCompleted(battler);
        }
        break;
    }
}

static void RecordedPlayerHandlePrintString(u32 battler)
{
    u16 *stringId;

    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    stringId = (u16 *)(&gBattleBufferA[battler][2]);
    BufferStringBattle(battler, *stringId);

    if (gTestRunnerEnabled)
    {
        TestRunner_Battle_RecordMessage(gDisplayedStringBattle);
        if (gTestRunnerHeadless)
        {
            RecordedPlayerBufferExecCompleted(battler);
            return;
        }
    }
    BattlePutTextOnWindow(gDisplayedStringBattle, B_WIN_MSG);
    gBattlerControllerFuncs[battler] = CompleteOnInactiveTextPrinter;
}

static void RecordedPlayerHandlePrintSelectionString(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void ChooseActionInBattlePalace(u32 battler)
{
    if (gBattleCommunication[4] >= gBattlersCount / 2)
    {
        BtlController_EmitTwoReturnValues(battler, BUFFER_B, RecordedBattle_GetBattlerAction(RECORDED_BATTLE_PALACE_ACTION, battler), 0);
        RecordedPlayerBufferExecCompleted(battler);
    }
}

static void RecordedPlayerHandleChooseAction(u32 battler)
{
    if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
    {
        gBattlerControllerFuncs[battler] = ChooseActionInBattlePalace;
    }
    else
    {
        BtlController_EmitTwoReturnValues(battler, BUFFER_B, RecordedBattle_GetBattlerAction(RECORDED_ACTION_TYPE, battler), 0);
        RecordedPlayerBufferExecCompleted(battler);
    }
}

static void RecordedPlayerHandleYesNoBox(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleChooseMove(u32 battler)
{
    if (gBattleTypeFlags & BATTLE_TYPE_PALACE)
    {
        BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, ChooseMoveAndTargetInBattlePalace(battler));
    }
    else
    {
        u8 moveId = RecordedBattle_GetBattlerAction(RECORDED_MOVE_SLOT, battler);
        u8 target = RecordedBattle_GetBattlerAction(RECORDED_MOVE_TARGET, battler);
        BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, moveId | (target << 8));
    }

    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleChooseItem(u32 battler)
{
    u8 byte1 = RecordedBattle_GetBattlerAction(RECORDED_ITEM_ID, battler);
    u8 byte2 = RecordedBattle_GetBattlerAction(RECORDED_ITEM_ID, battler);
    gBattleStruct->chosenItem[battler] = (byte1 << 8) | byte2;
    RecordedBattle_GetBattlerAction(RECORDED_ITEM_TARGET, battler);
    RecordedBattle_GetBattlerAction(RECORDED_ITEM_MOVE, battler);
    BtlController_EmitOneReturnValue(battler, BUFFER_B, gBattleStruct->chosenItem[battler]);
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleChoosePokemon(u32 battler)
{
    gBattleStruct->monToSwitchIntoId[battler] = RecordedBattle_GetBattlerAction(RECORDED_PARTY_INDEX, battler);
    BtlController_EmitChosenMonReturnValue(battler, BUFFER_B, gBattleStruct->monToSwitchIntoId[battler], NULL);
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleCmd23(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleHealthBarUpdate(u32 battler)
{
    u32 maxHP, curHP;
    s16 hpVal;

    LoadBattleBarGfx(0);
    hpVal = gBattleBufferA[battler][2] | (gBattleBufferA[battler][3] << 8);
    maxHP = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_MAX_HP);
    curHP = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_HP);

    if (hpVal != INSTANT_HP_BAR_DROP)
    {
        SetBattleBarStruct(battler, gHealthboxSpriteIds[battler], maxHP, curHP, hpVal);
        TestRunner_Battle_RecordHP(battler, curHP, min(maxHP, max(0, curHP - hpVal)));
    }
    else
    {
        SetBattleBarStruct(battler, gHealthboxSpriteIds[battler], maxHP, 0, hpVal);
        UpdateHpTextInHealthbox(gHealthboxSpriteIds[battler], 0, HP_CURRENT);
        TestRunner_Battle_RecordHP(battler, curHP, 0);
    }

    gBattlerControllerFuncs[battler] = CompleteOnHealthbarDone;
}

static void RecordedPlayerHandleExpUpdate(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleStatusIconUpdate(u32 battler)
{
    if (!IsBattleSEPlaying(battler))
    {
        UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gPlayerParty[gBattlerPartyIndexes[battler]], HEALTHBOX_STATUS_ICON);
        gBattleSpritesDataPtr->healthBoxesData[battler].statusAnimActive = 0;
        gBattlerControllerFuncs[battler] = CompleteOnFinishedStatusAnimation;
        if (gTestRunnerEnabled)
            TestRunner_Battle_RecordStatus1(battler, GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_STATUS));
    }
}

static void RecordedPlayerHandleStatusAnimation(u32 battler)
{
    if (!IsBattleSEPlaying(battler))
    {
        InitAndLaunchChosenStatusAnimation(battler, gBattleBufferA[battler][1],
                        gBattleBufferA[battler][2] | (gBattleBufferA[battler][3] << 8) | (gBattleBufferA[battler][4] << 16) | (gBattleBufferA[battler][5] << 24));
        gBattlerControllerFuncs[battler] = CompleteOnFinishedStatusAnimation;
    }
}

static void RecordedPlayerHandleStatusXor(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleDataTransfer(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleDMA3Transfer(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandlePlayBGM(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleCmd32(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleTwoReturnValues(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleChosenMonReturnValue(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleOneReturnValue(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleOneReturnValue_Duplicate(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleClearUnkVar(u32 battler)
{
    gUnusedControllerStruct.unk = 0;
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleSetUnkVar(u32 battler)
{
    gUnusedControllerStruct.unk = gBattleBufferA[battler][1];
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleClearUnkFlag(u32 battler)
{
    gUnusedControllerStruct.flag = 0;
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleToggleUnkFlag(u32 battler)
{
    gUnusedControllerStruct.flag ^= 1;
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleHitAnimation(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].invisible == TRUE)
    {
        RecordedPlayerBufferExecCompleted(battler);
    }
    else
    {
        gDoingBattleAnim = TRUE;
        gSprites[gBattlerSpriteIds[battler]].data[1] = 0;
        DoHitAnimHealthboxEffect(battler);
        gBattlerControllerFuncs[battler] = DoHitAnimBlinkSpriteEffect;
    }
}

static void RecordedPlayerHandleCantSwitch(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandlePlaySE(u32 battler)
{
    s8 pan;

    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        pan = SOUND_PAN_ATTACKER;
    else
        pan = SOUND_PAN_TARGET;

    PlaySE12WithPanning(gBattleBufferA[battler][1] | (gBattleBufferA[battler][2] << 8), pan);
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandlePlayFanfareOrBGM(u32 battler)
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

    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleFaintingCry(u32 battler)
{
    u16 species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);

    PlayCry_ByMode(species, -25, CRY_MODE_FAINT);
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleIntroSlide(u32 battler)
{
    HandleIntroSlide(gBattleBufferA[battler][1]);
    gIntroSlideFlags |= 1;
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleIntroTrainerBallThrow(u32 battler)
{
    u8 paletteNum;
    u8 taskId;
    u32 trainerPicId;

    SetSpritePrimaryCoordsFromSecondaryCoords(&gSprites[gBattlerSpriteIds[battler]]);

    gSprites[gBattlerSpriteIds[battler]].data[0] = 50;
    gSprites[gBattlerSpriteIds[battler]].data[2] = -40;
    gSprites[gBattlerSpriteIds[battler]].data[4] = gSprites[gBattlerSpriteIds[battler]].y;
    gSprites[gBattlerSpriteIds[battler]].callback = StartAnimLinearTranslation;
    gSprites[gBattlerSpriteIds[battler]].data[5] = battler;

    StoreSpriteCallbackInData6(&gSprites[gBattlerSpriteIds[battler]], SpriteCB_FreePlayerSpriteLoadMonSprite);
    StartSpriteAnim(&gSprites[gBattlerSpriteIds[battler]], 1);

    paletteNum = AllocSpritePalette(0xD6F9);
    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        trainerPicId = gLinkPlayers[GetBattlerMultiplayerId(battler)].gender;
    else
        trainerPicId = gSaveBlock2Ptr->playerGender;

    LoadCompressedPalette(gTrainerBackPicPaletteTable[trainerPicId].data, OBJ_PLTT_ID(paletteNum), PLTT_SIZE_4BPP);

    gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = paletteNum;

    taskId = CreateTask(Task_StartSendOutAnim, 5);
    gTasks[taskId].data[0] = battler;

    if (gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusSummaryShown)
        gTasks[gBattlerStatusSummaryTaskId[battler]].func = Task_HidePartyStatusSummary;

    gBattleSpritesDataPtr->animationData->introAnimActive = TRUE;
    gBattlerControllerFuncs[battler] = RecordedPlayerDummy;
}

static void Task_StartSendOutAnim(u8 taskId)
{
    if (gTasks[taskId].data[1] < 24)
    {
        gTasks[taskId].data[1]++;
    }
    else
    {
        u32 battler = gTasks[taskId].data[0];
        if (!IsDoubleBattle() || (gBattleTypeFlags & BATTLE_TYPE_MULTI))
        {
            gBattleBufferA[battler][1] = gBattlerPartyIndexes[battler];
            StartSendOutAnim(battler, FALSE);
        }
        else
        {
            gBattleBufferA[battler][1] = gBattlerPartyIndexes[battler];
            StartSendOutAnim(battler, FALSE);
            battler ^= BIT_FLANK;
            gBattleBufferA[battler][1] = gBattlerPartyIndexes[battler];
            BattleLoadPlayerMonSpriteGfx(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
            StartSendOutAnim(battler, FALSE);
            battler ^= BIT_FLANK;
        }
        gBattlerControllerFuncs[battler] = Intro_TryShinyAnimShowHealthbox;
        DestroyTask(taskId);
    }
}

static void RecordedPlayerHandleDrawPartyStatusSummary(u32 battler)
{
    if (gBattleBufferA[battler][1] != 0 && GetBattlerSide(battler) == B_SIDE_PLAYER)
    {
        RecordedPlayerBufferExecCompleted(battler);
    }
    else
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusSummaryShown = 1;
        gBattlerStatusSummaryTaskId[battler] = CreatePartyStatusSummarySprites(battler, (struct HpAndStatus *)&gBattleBufferA[battler][4], gBattleBufferA[battler][1], gBattleBufferA[battler][2]);
        gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusDelayTimer = 0;

        if (gBattleBufferA[battler][2] != 0)
            gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusDelayTimer = 93;

        gBattlerControllerFuncs[battler] = EndDrawPartyStatusSummary;
    }
}

static void EndDrawPartyStatusSummary(u32 battler)
{
    if (gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusDelayTimer++ > 92)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusDelayTimer = 0;
        RecordedPlayerBufferExecCompleted(battler);
    }
}

static void RecordedPlayerHandleHidePartyStatusSummary(u32 battler)
{
    if (gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusSummaryShown)
        gTasks[gBattlerStatusSummaryTaskId[battler]].func = Task_HidePartyStatusSummary;
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleEndBounceEffect(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleSpriteInvisibility(u32 battler)
{
    if (IsBattlerSpritePresent(battler))
    {
        gSprites[gBattlerSpriteIds[battler]].invisible = gBattleBufferA[battler][1];
        CopyBattleSpriteInvisibility(battler);
    }
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleBattleAnimation(u32 battler)
{
    if (!IsBattleSEPlaying(battler))
    {
        u8 animationId = gBattleBufferA[battler][1];
        u16 argument = gBattleBufferA[battler][2] | (gBattleBufferA[battler][3] << 8);

        if (TryHandleLaunchBattleTableAnimation(battler, battler, battler, animationId, argument))
            RecordedPlayerBufferExecCompleted(battler);
        else
            gBattlerControllerFuncs[battler] = CompleteOnFinishedBattleAnimation;
    }
}

static void RecordedPlayerHandleLinkStandbyMsg(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleResetActionMoveSelection(u32 battler)
{
    RecordedPlayerBufferExecCompleted(battler);
}

static void RecordedPlayerHandleEndLinkBattle(u32 battler)
{
    gBattleOutcome = gBattleBufferA[battler][1];
    FadeOutMapMusic(5);
    BeginFastPaletteFade(3);
    RecordedPlayerBufferExecCompleted(battler);
    gBattlerControllerFuncs[battler] = SetBattleEndCallbacks;
}

static void RecordedPlayerCmdEnd(u32 battler)
{
}
