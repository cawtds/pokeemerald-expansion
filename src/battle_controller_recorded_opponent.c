#include "global.h"
#include "battle.h"
#include "battle_ai_script_commands.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "battle_tv.h"
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
#include "constants/trainers.h"

static void RecordedOpponentHandleLoadMonSprite(u32 battler);
static void RecordedOpponentHandleSwitchInAnim(u32 battler);
static void RecordedOpponentHandleDrawTrainerPic(u32 battler);
static void RecordedOpponentHandleTrainerSlideBack(u32 battler);
static void RecordedOpponentHandleMoveAnimation(u32 battler);
static void RecordedOpponentHandlePrintString(u32 battler);
static void RecordedOpponentHandleChooseAction(u32 battler);
static void RecordedOpponentHandleChooseMove(u32 battler);
static void RecordedOpponentHandleChooseItem(u32 battler);
static void RecordedOpponentHandleChoosePokemon(u32 battler);
static void RecordedOpponentHandleHealthBarUpdate(u32 battler);
static void RecordedOpponentHandlePlayFanfareOrBGM(u32 battler);
static void RecordedOpponentHandleFaintingCry(u32 battler);
static void RecordedOpponentHandleIntroSlide(u32 battler);
static void RecordedOpponentHandleIntroTrainerBallThrow(u32 battler);
static void RecordedOpponentHandleDrawPartyStatusSummary(u32 battler);
static void RecordedOpponentHandleHidePartyStatusSummary(u32 battler);
static void RecordedOpponentHandleSpriteInvisibility(u32 battler);
static void RecordedOpponentHandleBattleAnimation(u32 battler);
static void RecordedOpponentHandleEndLinkBattle(u32 battler);

static void RecordedOpponentBufferRunCommand(u32 battler);
static void RecordedOpponentBufferExecCompleted(u32 battler);
static void SwitchIn_HandleSoundAndEnd(u32 battler);
static void Task_StartSendOutAnim(u8 taskId);
static void SpriteCB_FreeOpponentSprite(struct Sprite *sprite);
static void EndDrawPartyStatusSummary(u32 battler);

static void (*const sRecordedOpponentBufferCommands[CONTROLLER_CMDS_COUNT])(u32 battler) =
{
    [CONTROLLER_GETMONDATA]               = BtlController_HandleGetMonData,
    [CONTROLLER_GETRAWMONDATA]            = BtlController_Empty,
    [CONTROLLER_SETMONDATA]               = BtlController_HandleSetMonData,
    [CONTROLLER_SETRAWMONDATA]            = BtlController_Empty,
    [CONTROLLER_LOADMONSPRITE]            = RecordedOpponentHandleLoadMonSprite,
    [CONTROLLER_SWITCHINANIM]             = RecordedOpponentHandleSwitchInAnim,
    [CONTROLLER_RETURNMONTOBALL]          = BtlController_HandleReturnMonToBall,
    [CONTROLLER_DRAWTRAINERPIC]           = RecordedOpponentHandleDrawTrainerPic,
    [CONTROLLER_TRAINERSLIDE]             = BtlController_Empty,
    [CONTROLLER_TRAINERSLIDEBACK]         = RecordedOpponentHandleTrainerSlideBack,
    [CONTROLLER_FAINTANIMATION]           = BtlController_HandleFaintAnimation,
    [CONTROLLER_PALETTEFADE]              = BtlController_Empty,
    [CONTROLLER_SUCCESSBALLTHROWANIM]     = BtlController_Empty,
    [CONTROLLER_BALLTHROWANIM]            = BtlController_Empty,
    [CONTROLLER_PAUSE]                    = BtlController_Empty,
    [CONTROLLER_MOVEANIMATION]            = RecordedOpponentHandleMoveAnimation,
    [CONTROLLER_PRINTSTRING]              = RecordedOpponentHandlePrintString,
    [CONTROLLER_PRINTSTRINGPLAYERONLY]    = BtlController_Empty,
    [CONTROLLER_CHOOSEACTION]             = RecordedOpponentHandleChooseAction,
    [CONTROLLER_YESNOBOX]                 = BtlController_Empty,
    [CONTROLLER_CHOOSEMOVE]               = RecordedOpponentHandleChooseMove,
    [CONTROLLER_OPENBAG]                  = RecordedOpponentHandleChooseItem,
    [CONTROLLER_CHOOSEPOKEMON]            = RecordedOpponentHandleChoosePokemon,
    [CONTROLLER_23]                       = BtlController_Empty,
    [CONTROLLER_HEALTHBARUPDATE]          = RecordedOpponentHandleHealthBarUpdate,
    [CONTROLLER_EXPUPDATE]                = BtlController_Empty,
    [CONTROLLER_STATUSICONUPDATE]         = BtlController_HandleStatusIconUpdate,
    [CONTROLLER_STATUSANIMATION]          = BtlController_HandleStatusAnimation,
    [CONTROLLER_STATUSXOR]                = BtlController_Empty,
    [CONTROLLER_DATATRANSFER]             = BtlController_Empty,
    [CONTROLLER_DMA2TRANSFER]             = BtlController_Empty,
    [CONTROLLER_PLAYBGM]                  = BtlController_Empty,
    [CONTROLLER_32]                       = BtlController_Empty,
    [CONTROLLER_TWORETURNVALUES]          = BtlController_Empty,
    [CONTROLLER_CHOSENMONRETURNVALUE]     = BtlController_Empty,
    [CONTROLLER_ONERETURNVALUE]           = BtlController_Empty,
    [CONTROLLER_ONERETURNVALUE_DUPLICATE] = BtlController_Empty,
    [CONTROLLER_CLEARUNKVAR]              = BtlController_Empty,
    [CONTROLLER_SETUNKVAR]                = BtlController_Empty,
    [CONTROLLER_CLEARUNKFLAG]             = BtlController_Empty,
    [CONTROLLER_TOGGLEUNKFLAG]            = BtlController_Empty,
    [CONTROLLER_HITANIMATION]             = BtlController_HandleHitAnimation,
    [CONTROLLER_CANTSWITCH]               = BtlController_Empty,
    [CONTROLLER_PLAYSE]                   = BtlController_HandlePlaySE,
    [CONTROLLER_PLAYFANFAREORBGM]         = RecordedOpponentHandlePlayFanfareOrBGM,
    [CONTROLLER_FAINTINGCRY]              = RecordedOpponentHandleFaintingCry,
    [CONTROLLER_INTROSLIDE]               = RecordedOpponentHandleIntroSlide,
    [CONTROLLER_INTROTRAINERBALLTHROW]    = RecordedOpponentHandleIntroTrainerBallThrow,
    [CONTROLLER_DRAWPARTYSTATUSSUMMARY]   = RecordedOpponentHandleDrawPartyStatusSummary,
    [CONTROLLER_HIDEPARTYSTATUSSUMMARY]   = RecordedOpponentHandleHidePartyStatusSummary,
    [CONTROLLER_ENDBOUNCE]                = BtlController_Empty,
    [CONTROLLER_SPRITEINVISIBILITY]       = RecordedOpponentHandleSpriteInvisibility,
    [CONTROLLER_BATTLEANIMATION]          = RecordedOpponentHandleBattleAnimation,
    [CONTROLLER_LINKSTANDBYMSG]           = BtlController_Empty,
    [CONTROLLER_RESETACTIONMOVESELECTION] = BtlController_Empty,
    [CONTROLLER_ENDLINKBATTLE]            = RecordedOpponentHandleEndLinkBattle,
    [CONTROLLER_TERMINATOR_NOP]           = BtlController_TerminatorNop
};

static void RecordedOpponentDummy(u32 battler)
{
}

void SetControllerToRecordedOpponent(u32 battler)
{
    gBattlerControllerFuncs[battler] = RecordedOpponentBufferRunCommand;
    gBattlerControllerEndFuncs[battler] = RecordedOpponentBufferExecCompleted;
}

static void RecordedOpponentBufferRunCommand(u32 battler)
{
    if (gBattleControllerExecFlags & gBitTable[battler])
    {
        if (gBattleBufferA[battler][0] < ARRAY_COUNT(sRecordedOpponentBufferCommands))
            sRecordedOpponentBufferCommands[gBattleBufferA[battler][0]](battler);
        else
            RecordedOpponentBufferExecCompleted(battler);
    }
}

static void Intro_DelayAndEnd(u32 battler)
{
    if (--gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay == (u8)-1)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay = 0;
        RecordedOpponentBufferExecCompleted(battler);
    }
}

static void Intro_WaitForShinyAnimAndHealthbox(u32 battler)
{
    bool8 healthboxAnimDone = FALSE;

    if (!IsDoubleBattle() || (IsDoubleBattle() && (gBattleTypeFlags & BATTLE_TYPE_MULTI)))
    {
        if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy
         && gSprites[gBattlerSpriteIds[battler]].animEnded)
            healthboxAnimDone = TRUE;

    }
    else
    {
        if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy
         && gSprites[gHealthboxSpriteIds[BATTLE_PARTNER(battler)]].callback == SpriteCallbackDummy
         && gSprites[gBattlerSpriteIds[battler]].animEnded
         && gSprites[gBattlerSpriteIds[BATTLE_PARTNER(battler)]].animEnded)
             healthboxAnimDone = TRUE;
    }

    if (healthboxAnimDone)
    {
        if (GetBattlerPosition(battler) == B_POSITION_OPPONENT_LEFT)
        {
            if (!gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim)
                return;
            if (!gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].finishedShinyMonAnim)
                return;

            gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim = FALSE;
            gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim = FALSE;
            gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].triedShinyMonAnim = FALSE;
            gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].finishedShinyMonAnim = FALSE;
            FreeSpriteTilesByTag(ANIM_TAG_GOLD_STARS);
            FreeSpritePaletteByTag(ANIM_TAG_GOLD_STARS);
        }

        gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay = 3;
        gBattlerControllerFuncs[battler] = Intro_DelayAndEnd;
    }
}

static void Intro_TryShinyAnimShowHealthbox(u32 battler)
{
    bool32 bgmRestored = FALSE;
    bool32 battlerAnimsDone = FALSE;

    if (!gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim
     && !gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive)
        TryShinyAnimation(battler, &gEnemyParty[gBattlerPartyIndexes[battler]]);

    if (!gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].triedShinyMonAnim
     && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].ballAnimActive)
        TryShinyAnimation(BATTLE_PARTNER(battler), &gEnemyParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]]);

    if (!gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].ballAnimActive)
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted)
        {
            if (IsDoubleBattle() && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
            {
                UpdateHealthboxAttribute(gHealthboxSpriteIds[BATTLE_PARTNER(battler)], &gEnemyParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]], HEALTHBOX_ALL);
                StartHealthboxSlideIn(BATTLE_PARTNER(battler));
                SetHealthboxSpriteVisible(gHealthboxSpriteIds[BATTLE_PARTNER(battler)]);
            }
            UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gEnemyParty[gBattlerPartyIndexes[battler]], HEALTHBOX_ALL);
            StartHealthboxSlideIn(battler);
            SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);
        }
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted = TRUE;
    }

    if (!gBattleSpritesDataPtr->healthBoxesData[battler].waitForCry
        && gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted
        && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].waitForCry
        && !IsCryPlayingOrClearCrySongs())
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].bgmRestored)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI && gBattleTypeFlags & BATTLE_TYPE_LINK)
            {
                if (GetBattlerPosition(battler) == B_POSITION_OPPONENT_LEFT)
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

    if (!IsDoubleBattle())
    {
        if (gSprites[gBattleControllerData[battler]].callback == SpriteCallbackDummy
            && gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
        {
            battlerAnimsDone = TRUE;
        }
    }
    else
    {
        if (gSprites[gBattleControllerData[battler]].callback == SpriteCallbackDummy
            && gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy
            && gSprites[gBattleControllerData[BATTLE_PARTNER(battler)]].callback == SpriteCallbackDummy
            && gSprites[gBattlerSpriteIds[BATTLE_PARTNER(battler)]].callback == SpriteCallbackDummy)
        {
            battlerAnimsDone = TRUE;
        }
    }

    if (bgmRestored && battlerAnimsDone)
    {
        if (IsDoubleBattle() && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
        {
            DestroySprite(&gSprites[gBattleControllerData[BATTLE_PARTNER(battler)]]);
            SetBattlerShadowSpriteCallback(BATTLE_PARTNER(battler), GetMonData(&gEnemyParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]], MON_DATA_SPECIES));
        }

        DestroySprite(&gSprites[gBattleControllerData[battler]]);
        SetBattlerShadowSpriteCallback(battler, GetMonData(&gEnemyParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES));

        gBattleSpritesDataPtr->animationData->introAnimActive = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].bgmRestored = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted = FALSE;

        gBattlerControllerFuncs[battler] = Intro_WaitForShinyAnimAndHealthbox;
    }
}

static void TryShinyAnimAfterMonAnim(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy
     && gSprites[gBattlerSpriteIds[battler]].x2 == 0)
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim)
        {
            TryShinyAnimation(battler, &gEnemyParty[gBattlerPartyIndexes[battler]]);
        }
        else
        {
            if (gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim)
            {
                gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim = FALSE;
                gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim = FALSE;
                FreeSpriteTilesByTag(ANIM_TAG_GOLD_STARS);
                FreeSpritePaletteByTag(ANIM_TAG_GOLD_STARS);
                RecordedOpponentBufferExecCompleted(battler);
            }
        }
    }
}

static void SwitchIn_ShowSubstitute(u32 battler)
{
    if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy)
    {
        if (gBattleSpritesDataPtr->battlerData[battler].behindSubstitute)
            InitAndLaunchSpecialAnimation(battler, battler, battler, B_ANIM_MON_TO_SUBSTITUTE);

        gBattlerControllerFuncs[battler] = SwitchIn_HandleSoundAndEnd;
    }
}

static void SwitchIn_HandleSoundAndEnd(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive
        && !IsCryPlayingOrClearCrySongs())
    {
        if (gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy
            || gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy_2)
        {
            m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, 0x100);
            RecordedOpponentBufferExecCompleted(battler);
        }
    }
}

static void SwitchIn_ShowHealthbox(u32 battler)
{
    if (gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim
     && gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim = FALSE;

        FreeSpriteTilesByTag(ANIM_TAG_GOLD_STARS);
        FreeSpritePaletteByTag(ANIM_TAG_GOLD_STARS);

        StartSpriteAnim(&gSprites[gBattlerSpriteIds[battler]], 0);

        UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gEnemyParty[gBattlerPartyIndexes[battler]], HEALTHBOX_ALL);
        StartHealthboxSlideIn(battler);
        SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);
        CopyBattleSpriteInvisibility(battler);
        gBattlerControllerFuncs[battler] = SwitchIn_ShowSubstitute;
    }
}

static void SwitchIn_TryShinyAnim(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive
        && !gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim)
        TryShinyAnimation(battler, &gEnemyParty[gBattlerPartyIndexes[battler]]);

    if (gSprites[gBattleControllerData[battler]].callback == SpriteCallbackDummy
        && !gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive)
    {
        DestroySprite(&gSprites[gBattleControllerData[battler]]);
        SetBattlerShadowSpriteCallback(battler, GetMonData(&gEnemyParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES));
        gBattlerControllerFuncs[battler] = SwitchIn_ShowHealthbox;
    }
}

static void CompleteOnFinishedBattleAnimation(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].animFromTableActive)
        RecordedOpponentBufferExecCompleted(battler);
}

static void RecordedOpponentBufferExecCompleted(u32 battler)
{
    gBattlerControllerFuncs[battler] = RecordedOpponentBufferRunCommand;
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

static void RecordedOpponentHandleLoadMonSprite(u32 battler)
{
    BtlController_HandleLoadMonSprite(battler, TryShinyAnimAfterMonAnim);
}

static void RecordedOpponentHandleSwitchInAnim(u32 battler)
{
    BtlController_HandleSwitchInAnim(battler, SwitchIn_TryShinyAnim);
}

static u32 RecordedOpponentGetTrainerPic(u32 battler)
{
    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_BATTLE_TOWER)
        {
            if (battler == B_POSITION_OPPONENT_LEFT)
                return GetFrontierTrainerFrontSpriteId(gTrainerBattleOpponent_A);
            else
                return GetFrontierTrainerFrontSpriteId(gTrainerBattleOpponent_B);
        }
        return PlayerGenderToFrontTrainerPicId(GetActiveBattlerLinkPlayerGender(battler));
    }

    if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
        return GetUnionRoomTrainerPic();
    
    return PlayerGenderToFrontTrainerPicId(gLinkPlayers[gRecordedBattleMultiplayerId ^ BIT_SIDE].gender);
}

static void RecordedOpponentHandleDrawTrainerPic(u32 battler)
{
    s16 xPos;
    u32 trainerPicId = RecordedOpponentGetTrainerPic(battler);

    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if ((GetBattlerPosition(battler) & BIT_FLANK) != 0) // second mon
            xPos = 152;
        else // first mon
            xPos = 200;
    }
    else
    {
        xPos = 176;
    }

    BtlController_HandleDrawTrainerPic(battler, trainerPicId, xPos, (8 - gTrainerFrontPicCoords[trainerPicId].size) * 4 + 40, GetBattlerSpriteSubpriority(battler), TRUE);
}

static void RecordedOpponentHandleTrainerSlideBack(u32 battler)
{
    BtlController_HandleTrainerSlideBack(battler, 35, FALSE);
}

static void RecordedOpponentHandleMoveAnimation(u32 battler)
{
    BtlController_HandleMoveAnimation(battler, FALSE);
}

static void RecordedOpponentHandlePrintString(u32 battler)
{
    BtlController_HandlePrintString(battler, FALSE, FALSE);
}

static void RecordedOpponentHandleChooseAction(u32 battler)
{
    BtlController_EmitTwoReturnValues(battler, BUFFER_B, RecordedBattle_GetBattlerAction(RECORDED_ACTION_TYPE, battler), 0);
    RecordedOpponentBufferExecCompleted(battler);
}

static void RecordedOpponentHandleChooseMove(u32 battler)
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

    RecordedOpponentBufferExecCompleted(battler);
}

static void RecordedOpponentHandleChooseItem(u32 battler)
{
    u8 byte1 = RecordedBattle_GetBattlerAction(RECORDED_ITEM_ID, battler);
    u8 byte2 = RecordedBattle_GetBattlerAction(RECORDED_ITEM_ID, battler);
    gBattleStruct->chosenItem[battler] = (byte1 << 8) | byte2;
    RecordedBattle_GetBattlerAction(RECORDED_ITEM_TARGET, battler);
    RecordedBattle_GetBattlerAction(RECORDED_ITEM_MOVE, battler);
    BtlController_EmitOneReturnValue(battler, BUFFER_B, gBattleStruct->chosenItem[battler]);
    RecordedOpponentBufferExecCompleted(battler);
}

static void RecordedOpponentHandleChoosePokemon(u32 battler)
{
    gBattleStruct->monToSwitchIntoId[battler] = RecordedBattle_GetBattlerAction(RECORDED_PARTY_INDEX, battler);
    BtlController_EmitChosenMonReturnValue(battler, BUFFER_B, gBattleStruct->monToSwitchIntoId[battler], NULL);
    RecordedOpponentBufferExecCompleted(battler);
}

static void RecordedOpponentHandleHealthBarUpdate(u32 battler)
{
    BtlController_HandleHealthBarUpdate(battler, FALSE);
}

static void RecordedOpponentHandlePlayFanfareOrBGM(u32 battler)
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

    RecordedOpponentBufferExecCompleted(battler);
}

static void RecordedOpponentHandleFaintingCry(u32 battler)
{
    u16 species = GetMonData(&gEnemyParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);

    PlayCry_ByMode(species, 25, CRY_MODE_FAINT);
    RecordedOpponentBufferExecCompleted(battler);
}

static void RecordedOpponentHandleIntroSlide(u32 battler)
{
    HandleIntroSlide(gBattleBufferA[battler][1]);
    gIntroSlideFlags |= 1;
    RecordedOpponentBufferExecCompleted(battler);
}

static void RecordedOpponentHandleIntroTrainerBallThrow(u32 battler)
{
    u8 taskId;

    SetSpritePrimaryCoordsFromSecondaryCoords(&gSprites[gBattlerSpriteIds[battler]]);

    gSprites[gBattlerSpriteIds[battler]].data[0] = 35;
    gSprites[gBattlerSpriteIds[battler]].data[2] = 280;
    gSprites[gBattlerSpriteIds[battler]].data[4] = gSprites[gBattlerSpriteIds[battler]].y;
    gSprites[gBattlerSpriteIds[battler]].callback = StartAnimLinearTranslation;

    StoreSpriteCallbackInData6(&gSprites[gBattlerSpriteIds[battler]], SpriteCB_FreeOpponentSprite);

    taskId = CreateTask(Task_StartSendOutAnim, 5);
    gTasks[taskId].data[0] = battler;

    if (gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusSummaryShown)
        gTasks[gBattlerStatusSummaryTaskId[battler]].func = Task_HidePartyStatusSummary;

    gBattleSpritesDataPtr->animationData->introAnimActive = TRUE;
    gBattlerControllerFuncs[battler] = RecordedOpponentDummy;
}

static void Task_StartSendOutAnim(u8 taskId)
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
        StartSendOutAnim(battler, FALSE);
        battler ^= BIT_FLANK;
    }
    gBattlerControllerFuncs[battler] = Intro_TryShinyAnimShowHealthbox;
    DestroyTask(taskId);
}

static void SpriteCB_FreeOpponentSprite(struct Sprite *sprite)
{
    FreeTrainerFrontPicPalette(sprite->oam.affineParam);
    FreeSpriteOamMatrix(sprite);
    DestroySprite(sprite);
}

static void RecordedOpponentHandleDrawPartyStatusSummary(u32 battler)
{
    if (gBattleBufferA[battler][1] != 0 && GetBattlerSide(battler) == B_SIDE_PLAYER)
    {
        RecordedOpponentBufferExecCompleted(battler);
    }
    else
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusSummaryShown = 1;

        if (gBattleBufferA[battler][2] != 0)
        {
            if (gBattleSpritesDataPtr->healthBoxesData[battler].opponentDrawPartyStatusSummaryDelay < 2)
            {
                gBattleSpritesDataPtr->healthBoxesData[battler].opponentDrawPartyStatusSummaryDelay++;
                return;
            }
            else
            {
                gBattleSpritesDataPtr->healthBoxesData[battler].opponentDrawPartyStatusSummaryDelay = 0;
            }
        }

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
        RecordedOpponentBufferExecCompleted(battler);
    }
}

static void RecordedOpponentHandleHidePartyStatusSummary(u32 battler)
{
    if (gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusSummaryShown)
        gTasks[gBattlerStatusSummaryTaskId[battler]].func = Task_HidePartyStatusSummary;
    RecordedOpponentBufferExecCompleted(battler);
}

static void RecordedOpponentHandleSpriteInvisibility(u32 battler)
{
    if (IsBattlerSpritePresent(battler))
    {
        gSprites[gBattlerSpriteIds[battler]].invisible = gBattleBufferA[battler][1];
        CopyBattleSpriteInvisibility(battler);
    }
    RecordedOpponentBufferExecCompleted(battler);
}

static void RecordedOpponentHandleBattleAnimation(u32 battler)
{
    if (!IsBattleSEPlaying(battler))
    {
        u8 animationId = gBattleBufferA[battler][1];
        u16 argument = gBattleBufferA[battler][2] | (gBattleBufferA[battler][3] << 8);

        if (TryHandleLaunchBattleTableAnimation(battler, battler, battler, animationId, argument))
            RecordedOpponentBufferExecCompleted(battler);
        else
            gBattlerControllerFuncs[battler] = CompleteOnFinishedBattleAnimation;
    }
}

static void RecordedOpponentHandleEndLinkBattle(u32 battler)
{
    if (gBattleBufferA[battler][1] == B_OUTCOME_DREW)
        gBattleOutcome = gBattleBufferA[battler][1];
    else
        gBattleOutcome = gBattleBufferA[battler][1] ^ B_OUTCOME_DREW;

    FadeOutMapMusic(5);
    BeginFastPaletteFade(3);
    RecordedOpponentBufferExecCompleted(battler);
    gBattlerControllerFuncs[battler] = SetBattleEndCallbacks;
}
