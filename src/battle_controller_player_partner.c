#include "global.h"
#include "battle.h"
#include "battle_ai_script_commands.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_interface.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "bg.h"
#include "data.h"
#include "item_use.h"
#include "link.h"
#include "main.h"
#include "m4a.h"
#include "move.h"
#include "palette.h"
#include "pokeball.h"
#include "pokemon.h"
#include "reshow_battle_screen.h"
#include "sound.h"
#include "species.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "util.h"
#include "window.h"
#include "constants/battle_anim.h"
#include "constants/songs.h"
#include "constants/trainers.h"

static void PlayerPartnerHandleLoadMonSprite(u32 battler);
static void PlayerPartnerHandleSwitchInAnim(u32 battler);
static void PlayerPartnerHandleDrawTrainerPic(u32 battler);
static void PlayerPartnerHandleTrainerSlideBack(u32 battler);
static void PlayerPartnerHandlePaletteFade(u32 battler);
static void PlayerPartnerHandleSuccessBallThrowAnim(u32 battler);
static void PlayerPartnerHandleBallThrowAnim(u32 battler);
static void PlayerPartnerHandlePause(u32 battler);
static void PlayerPartnerHandleMoveAnimation(u32 battler);
static void PlayerPartnerHandlePrintString(u32 battler);
static void PlayerPartnerHandlePrintSelectionString(u32 battler);
static void PlayerPartnerHandleChooseAction(u32 battler);
static void PlayerPartnerHandleYesNoBox(u32 battler);
static void PlayerPartnerHandleChooseMove(u32 battler);
static void PlayerPartnerHandleChooseItem(u32 battler);
static void PlayerPartnerHandleChoosePokemon(u32 battler);
static void PlayerPartnerHandleCmd23(u32 battler);
static void PlayerPartnerHandleHealthBarUpdate(u32 battler);
static void PlayerPartnerHandleExpUpdate(u32 battler);
static void PlayerPartnerHandleStatusIconUpdate(u32 battler);
static void PlayerPartnerHandleStatusAnimation(u32 battler);
static void PlayerPartnerHandleStatusXor(u32 battler);
static void PlayerPartnerHandleDataTransfer(u32 battler);
static void PlayerPartnerHandleDMA3Transfer(u32 battler);
static void PlayerPartnerHandlePlayBGM(u32 battler);
static void PlayerPartnerHandleCmd32(u32 battler);
static void PlayerPartnerHandleTwoReturnValues(u32 battler);
static void PlayerPartnerHandleChosenMonReturnValue(u32 battler);
static void PlayerPartnerHandleOneReturnValue(u32 battler);
static void PlayerPartnerHandleOneReturnValue_Duplicate(u32 battler);
static void PlayerPartnerHandleClearUnkVar(u32 battler);
static void PlayerPartnerHandleSetUnkVar(u32 battler);
static void PlayerPartnerHandleClearUnkFlag(u32 battler);
static void PlayerPartnerHandleToggleUnkFlag(u32 battler);
static void PlayerPartnerHandleHitAnimation(u32 battler);
static void PlayerPartnerHandleCantSwitch(u32 battler);
static void PlayerPartnerHandlePlaySE(u32 battler);
static void PlayerPartnerHandlePlayFanfareOrBGM(u32 battler);
static void PlayerPartnerHandleFaintingCry(u32 battler);
static void PlayerPartnerHandleIntroSlide(u32 battler);
static void PlayerPartnerHandleIntroTrainerBallThrow(u32 battler);
static void PlayerPartnerHandleDrawPartyStatusSummary(u32 battler);
static void PlayerPartnerHandleHidePartyStatusSummary(u32 battler);
static void PlayerPartnerHandleEndBounceEffect(u32 battler);
static void PlayerPartnerHandleSpriteInvisibility(u32 battler);
static void PlayerPartnerHandleBattleAnimation(u32 battler);
static void PlayerPartnerHandleLinkStandbyMsg(u32 battler);
static void PlayerPartnerHandleResetActionMoveSelection(u32 battler);
static void PlayerPartnerHandleEndLinkBattle(u32 battler);
static void PlayerPartnerCmdEnd(u32 battler);

static void PlayerPartnerBufferRunCommand(u32 battler);
static void PlayerPartnerBufferExecCompleted(u32 battler);
static void Task_LaunchLvlUpAnim(u8 taskId);
static void DestroyExpTaskAndCompleteOnInactiveTextPrinter(u8 taskId);
static void Task_PrepareToGiveExpWithExpBar(u8 taskId);
static void Task_GiveExpWithExpBar(u8 taskId);
static void Task_UpdateLvlInHealthbox(u8 taskId);
static void SwitchIn_WaitAndEnd(u32 battler);
static void PlayerPartnerDoMoveAnimation(u32 battler);
static void Task_StartSendOutAnim(u8 taskId);
static void EndDrawPartyStatusSummary(u32 battler);

static void (*const sPlayerPartnerBufferCommands[CONTROLLER_CMDS_COUNT])(u32 battler) =
{
    [CONTROLLER_GETMONDATA]               = BtlController_HandleGetMonData,
    [CONTROLLER_GETRAWMONDATA]            = BtlController_Empty,
    [CONTROLLER_SETMONDATA]               = BtlController_HandleSetMonData,
    [CONTROLLER_SETRAWMONDATA]            = BtlController_HandleSetRawMonData,
    [CONTROLLER_LOADMONSPRITE]            = PlayerPartnerHandleLoadMonSprite,
    [CONTROLLER_SWITCHINANIM]             = PlayerPartnerHandleSwitchInAnim,
    [CONTROLLER_RETURNMONTOBALL]          = BtlController_HandleReturnMonToBall,
    [CONTROLLER_DRAWTRAINERPIC]           = PlayerPartnerHandleDrawTrainerPic,
    [CONTROLLER_TRAINERSLIDE]             = BtlController_Empty,
    [CONTROLLER_TRAINERSLIDEBACK]         = PlayerPartnerHandleTrainerSlideBack,
    [CONTROLLER_FAINTANIMATION]           = BtlController_HandleFaintAnimation,
    [CONTROLLER_PALETTEFADE]              = PlayerPartnerHandlePaletteFade,
    [CONTROLLER_SUCCESSBALLTHROWANIM]     = PlayerPartnerHandleSuccessBallThrowAnim,
    [CONTROLLER_BALLTHROWANIM]            = PlayerPartnerHandleBallThrowAnim,
    [CONTROLLER_PAUSE]                    = PlayerPartnerHandlePause,
    [CONTROLLER_MOVEANIMATION]            = PlayerPartnerHandleMoveAnimation,
    [CONTROLLER_PRINTSTRING]              = PlayerPartnerHandlePrintString,
    [CONTROLLER_PRINTSTRINGPLAYERONLY]    = PlayerPartnerHandlePrintSelectionString,
    [CONTROLLER_CHOOSEACTION]             = PlayerPartnerHandleChooseAction,
    [CONTROLLER_YESNOBOX]                 = PlayerPartnerHandleYesNoBox,
    [CONTROLLER_CHOOSEMOVE]               = PlayerPartnerHandleChooseMove,
    [CONTROLLER_OPENBAG]                  = PlayerPartnerHandleChooseItem,
    [CONTROLLER_CHOOSEPOKEMON]            = PlayerPartnerHandleChoosePokemon,
    [CONTROLLER_23]                       = PlayerPartnerHandleCmd23,
    [CONTROLLER_HEALTHBARUPDATE]          = PlayerPartnerHandleHealthBarUpdate,
    [CONTROLLER_EXPUPDATE]                = PlayerPartnerHandleExpUpdate,
    [CONTROLLER_STATUSICONUPDATE]         = PlayerPartnerHandleStatusIconUpdate,
    [CONTROLLER_STATUSANIMATION]          = PlayerPartnerHandleStatusAnimation,
    [CONTROLLER_STATUSXOR]                = PlayerPartnerHandleStatusXor,
    [CONTROLLER_DATATRANSFER]             = PlayerPartnerHandleDataTransfer,
    [CONTROLLER_DMA3TRANSFER]             = PlayerPartnerHandleDMA3Transfer,
    [CONTROLLER_PLAYBGM]                  = PlayerPartnerHandlePlayBGM,
    [CONTROLLER_32]                       = PlayerPartnerHandleCmd32,
    [CONTROLLER_TWORETURNVALUES]          = PlayerPartnerHandleTwoReturnValues,
    [CONTROLLER_CHOSENMONRETURNVALUE]     = PlayerPartnerHandleChosenMonReturnValue,
    [CONTROLLER_ONERETURNVALUE]           = PlayerPartnerHandleOneReturnValue,
    [CONTROLLER_ONERETURNVALUE_DUPLICATE] = PlayerPartnerHandleOneReturnValue_Duplicate,
    [CONTROLLER_CLEARUNKVAR]              = PlayerPartnerHandleClearUnkVar,
    [CONTROLLER_SETUNKVAR]                = PlayerPartnerHandleSetUnkVar,
    [CONTROLLER_CLEARUNKFLAG]             = PlayerPartnerHandleClearUnkFlag,
    [CONTROLLER_TOGGLEUNKFLAG]            = PlayerPartnerHandleToggleUnkFlag,
    [CONTROLLER_HITANIMATION]             = PlayerPartnerHandleHitAnimation,
    [CONTROLLER_CANTSWITCH]               = PlayerPartnerHandleCantSwitch,
    [CONTROLLER_PLAYSE]                   = PlayerPartnerHandlePlaySE,
    [CONTROLLER_PLAYFANFAREORBGM]         = PlayerPartnerHandlePlayFanfareOrBGM,
    [CONTROLLER_FAINTINGCRY]              = PlayerPartnerHandleFaintingCry,
    [CONTROLLER_INTROSLIDE]               = PlayerPartnerHandleIntroSlide,
    [CONTROLLER_INTROTRAINERBALLTHROW]    = PlayerPartnerHandleIntroTrainerBallThrow,
    [CONTROLLER_DRAWPARTYSTATUSSUMMARY]   = PlayerPartnerHandleDrawPartyStatusSummary,
    [CONTROLLER_HIDEPARTYSTATUSSUMMARY]   = PlayerPartnerHandleHidePartyStatusSummary,
    [CONTROLLER_ENDBOUNCE]                = PlayerPartnerHandleEndBounceEffect,
    [CONTROLLER_SPRITEINVISIBILITY]       = PlayerPartnerHandleSpriteInvisibility,
    [CONTROLLER_BATTLEANIMATION]          = PlayerPartnerHandleBattleAnimation,
    [CONTROLLER_LINKSTANDBYMSG]           = PlayerPartnerHandleLinkStandbyMsg,
    [CONTROLLER_RESETACTIONMOVESELECTION] = PlayerPartnerHandleResetActionMoveSelection,
    [CONTROLLER_ENDLINKBATTLE]            = PlayerPartnerHandleEndLinkBattle,
    [CONTROLLER_TERMINATOR_NOP]           = PlayerPartnerCmdEnd
};

// unknown unused data
static const u8 sUnused[] =
{
    0x83, 0x4d, 0xf3, 0x5f, 0x6f, 0x4f, 0xeb, 0x3e,
    0x67, 0x2e, 0x10, 0x46, 0x8c, 0x3d, 0x28, 0x35,
    0xc5, 0x2c, 0x15, 0x7f, 0xb5, 0x56, 0x9d, 0x53,
    0x3b, 0x43, 0xda, 0x36, 0x79, 0x2a, 0x0e, 0x53,
};

static void PlayerPartnerDummy(u32 battler)
{
}

void SetControllerToPlayerPartner(u32 battler)
{
    gBattlerControllerFuncs[battler] = PlayerPartnerBufferRunCommand;
    gBattlerControllerEndFuncs[battler] = PlayerPartnerBufferExecCompleted;
}

static void PlayerPartnerBufferRunCommand(u32 battler)
{
    if (gBattleControllerExecFlags & gBitTable[battler])
    {
        if (gBattleBufferA[battler][0] < ARRAY_COUNT(sPlayerPartnerBufferCommands))
            sPlayerPartnerBufferCommands[gBattleBufferA[battler][0]](battler);
        else
            PlayerPartnerBufferExecCompleted(battler);
    }
}

static void CompleteOnBattlerSpriteCallbackDummy(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
        PlayerPartnerBufferExecCompleted(battler);
}

static void Intro_DelayAndEnd(u32 battler)
{
    if (--gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay == (u8)-1)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay = 0;
        PlayerPartnerBufferExecCompleted(battler);
    }
}

static void Intro_WaitForHealthbox(u32 battler)
{
    bool32 finished = FALSE;

    if (!IsDoubleBattle() || (IsDoubleBattle() && (gBattleTypeFlags & BATTLE_TYPE_MULTI)))
    {
        if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy)
            finished = TRUE;
    }
    else
    {
        if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy
            && gSprites[gHealthboxSpriteIds[BATTLE_PARTNER(battler)]].callback == SpriteCallbackDummy)
        {
            finished = TRUE;
        }
    }

    if (IsCryPlayingOrClearCrySongs())
        finished = FALSE;

    if (finished)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay = 3;
        gBattlerControllerFuncs[battler] = Intro_DelayAndEnd;
    }
}

static void Intro_ShowHealthbox(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive
        && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].ballAnimActive
        && gSprites[gBattleControllerData[battler]].callback == SpriteCallbackDummy
        && gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy
        && ++gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay != 1)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay = 0;

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

        gBattlerControllerFuncs[battler] = Intro_WaitForHealthbox;
    }
}

static void WaitForMonAnimAfterLoad(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].animEnded && gSprites[gBattlerSpriteIds[battler]].x2 == 0)
        PlayerPartnerBufferExecCompleted(battler);
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
        PlayerPartnerBufferExecCompleted(battler);
    }
}

static void CompleteOnInactiveTextPrinter(u32 battler)
{
    if (!IsTextPrinterActive(B_WIN_MSG))
        PlayerPartnerBufferExecCompleted(battler);
}

// the whole exp task is copied&pasted from player controller
#define tExpTask_monId      data[0]
#define tExpTask_gainedExp  data[1]
#define tExpTask_bank       data[2]
#define tExpTask_frames     data[10]

static void Task_GiveExpToMon(u8 taskId)
{
    u32 monId = (u8)(gTasks[taskId].tExpTask_monId);
    u32 battler = gTasks[taskId].tExpTask_bank;
    s16 gainedExp = gTasks[taskId].tExpTask_gainedExp;

    if (IsDoubleBattle() == TRUE || monId != gBattlerPartyIndexes[battler]) // give exp without the expbar
    {
        struct Pokemon *mon = &gPlayerParty[monId];
        u16 species = GetMonData(mon, MON_DATA_SPECIES);
        u8 level = GetMonData(mon, MON_DATA_LEVEL);
        u32 currExp = GetMonData(mon, MON_DATA_EXP);
        u32 nextLvlExp = gExperienceTables[gSpeciesInfo[species].growthRate][level + 1];

        if (currExp + gainedExp >= nextLvlExp)
        {
            SetMonData(mon, MON_DATA_EXP, &nextLvlExp);
            CalculateMonStats(mon);
            gainedExp -= nextLvlExp - currExp;
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, RET_VALUE_LEVELED_UP, gainedExp);

            if (IsDoubleBattle() == TRUE
             && ((u16)(monId) == gBattlerPartyIndexes[battler] || (u16)(monId) == gBattlerPartyIndexes[BATTLE_PARTNER(battler)]))
                gTasks[taskId].func = Task_LaunchLvlUpAnim;
            else
                gTasks[taskId].func = DestroyExpTaskAndCompleteOnInactiveTextPrinter;
        }
        else
        {
            currExp += gainedExp;
            SetMonData(mon, MON_DATA_EXP, &currExp);
            gBattlerControllerFuncs[battler] = CompleteOnInactiveTextPrinter;
            DestroyTask(taskId);
        }
    }
    else
    {
        gTasks[taskId].func = Task_PrepareToGiveExpWithExpBar;
    }
}

static void Task_PrepareToGiveExpWithExpBar(u8 taskId)
{
    u8 monIndex = gTasks[taskId].tExpTask_monId;
    s32 gainedExp = gTasks[taskId].tExpTask_gainedExp;
    u8 battlerId = gTasks[taskId].tExpTask_bank;
    struct Pokemon *mon = &gPlayerParty[monIndex];
    u8 level = GetMonData(mon, MON_DATA_LEVEL);
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u32 exp = GetMonData(mon, MON_DATA_EXP);
    u32 currLvlExp = gExperienceTables[gSpeciesInfo[species].growthRate][level];
    u32 expToNextLvl;

    exp -= currLvlExp;
    expToNextLvl = gExperienceTables[gSpeciesInfo[species].growthRate][level + 1] - currLvlExp;
    SetBattleBarStruct(battlerId, gHealthboxSpriteIds[battlerId], expToNextLvl, exp, -gainedExp);
    PlaySE(SE_EXP);
    gTasks[taskId].func = Task_GiveExpWithExpBar;
}

static void Task_GiveExpWithExpBar(u8 taskId)
{
    if (gTasks[taskId].tExpTask_frames < 13)
    {
        gTasks[taskId].tExpTask_frames++;
    }
    else
    {
        u8 monId = gTasks[taskId].tExpTask_monId;
        s16 gainedExp = gTasks[taskId].tExpTask_gainedExp;
        u32 battler = gTasks[taskId].tExpTask_bank;
        s16 r4;

        r4 = MoveBattleBar(battler, gHealthboxSpriteIds[battler], EXP_BAR, 0);
        SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);
        if (r4 == -1)
        {
            u8 level;
            s32 currExp;
            u16 species;
            s32 expOnNextLvl;

            m4aSongNumStop(SE_EXP);
            level = GetMonData(&gPlayerParty[monId], MON_DATA_LEVEL);
            currExp = GetMonData(&gPlayerParty[monId], MON_DATA_EXP);
            species = GetMonData(&gPlayerParty[monId], MON_DATA_SPECIES);
            expOnNextLvl = gExperienceTables[gSpeciesInfo[species].growthRate][level + 1];

            if (currExp + gainedExp >= expOnNextLvl)
            {
                SetMonData(&gPlayerParty[monId], MON_DATA_EXP, &expOnNextLvl);
                CalculateMonStats(&gPlayerParty[monId]);
                gainedExp -= expOnNextLvl - currExp;
                BtlController_EmitTwoReturnValues(battler, BUFFER_B, RET_VALUE_LEVELED_UP, gainedExp);
                gTasks[taskId].func = Task_LaunchLvlUpAnim;
            }
            else
            {
                currExp += gainedExp;
                SetMonData(&gPlayerParty[monId], MON_DATA_EXP, &currExp);
                gBattlerControllerFuncs[battler] = CompleteOnInactiveTextPrinter;
                DestroyTask(taskId);
            }
        }
    }
}

static void Task_LaunchLvlUpAnim(u8 taskId)
{
    u8 battlerId = gTasks[taskId].tExpTask_bank;
    u8 monIndex = gTasks[taskId].tExpTask_monId;

    if (IsDoubleBattle() == TRUE && monIndex == gBattlerPartyIndexes[BATTLE_PARTNER(battlerId)])
        battlerId ^= BIT_FLANK;

    InitAndLaunchSpecialAnimation(battlerId, battlerId, battlerId, B_ANIM_LVL_UP);
    gTasks[taskId].func = Task_UpdateLvlInHealthbox;
}

static void Task_UpdateLvlInHealthbox(u8 taskId)
{
    u8 battlerId = gTasks[taskId].tExpTask_bank;

    if (!gBattleSpritesDataPtr->healthBoxesData[battlerId].specialAnimActive)
    {
        u8 monIndex = gTasks[taskId].tExpTask_monId;

        GetMonData(&gPlayerParty[monIndex], MON_DATA_LEVEL);  // Unused return value

        if (IsDoubleBattle() == TRUE && monIndex == gBattlerPartyIndexes[BATTLE_PARTNER(battlerId)])
            UpdateHealthboxAttribute(gHealthboxSpriteIds[BATTLE_PARTNER(battlerId)], &gPlayerParty[monIndex], HEALTHBOX_ALL);
        else
            UpdateHealthboxAttribute(gHealthboxSpriteIds[battlerId], &gPlayerParty[monIndex], HEALTHBOX_ALL);

        gTasks[taskId].func = DestroyExpTaskAndCompleteOnInactiveTextPrinter;
    }
}

static void DestroyExpTaskAndCompleteOnInactiveTextPrinter(u8 taskId)
{
    u8 monIndex;
    u8 battlerId;

    monIndex = gTasks[taskId].tExpTask_monId;
    GetMonData(&gPlayerParty[monIndex], MON_DATA_LEVEL);  // Unused return value
    battlerId = gTasks[taskId].tExpTask_bank;
    gBattlerControllerFuncs[battlerId] = CompleteOnInactiveTextPrinter;
    DestroyTask(taskId);
}

static void CompleteOnInactiveTextPrinter2(u32 battler)
{
    if (!IsTextPrinterActive(B_WIN_MSG))
        PlayerPartnerBufferExecCompleted(battler);
}

static void DoHitAnimBlinkSpriteEffect(u32 battler)
{
    u8 spriteId = gBattlerSpriteIds[battler];

    if (gSprites[spriteId].data[1] == 32)
    {
        gSprites[spriteId].data[1] = 0;
        gSprites[spriteId].invisible = FALSE;
        gDoingBattleAnim = FALSE;
        PlayerPartnerBufferExecCompleted(battler);
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
        PlayerPartnerBufferExecCompleted(battler);
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

static void PlayerPartnerBufferExecCompleted(u32 battler)
{
    gBattlerControllerFuncs[battler] = PlayerPartnerBufferRunCommand;
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
        PlayerPartnerBufferExecCompleted(battler);
}

static void CompleteOnFinishedBattleAnimation(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].animFromTableActive)
        PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleLoadMonSprite(u32 battler)
{
    BtlController_HandleLoadMonSprite(battler, WaitForMonAnimAfterLoad);
}

static void PlayerPartnerHandleSwitchInAnim(u32 battler)
{
    ClearTemporarySpeciesSpriteData(battler, gBattleBufferA[battler][2]);
    gBattlerPartyIndexes[battler] = gBattleBufferA[battler][1];
    BattleLoadPlayerMonSpriteGfx(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
    StartSendOutAnim(battler, gBattleBufferA[battler][2], FALSE);
    gBattlerControllerFuncs[battler] = SwitchIn_TryShinyAnim;
}

#define sSpeedX data[0]

// some explanation here
// in emerald it's possible to have a tag battle in the battle frontier facilities with AI
// which use the front sprite for both the player and the partner as opposed to any other battles (including the one with Steven) that use the back pic as well as animate it
static void PlayerPartnerHandleDrawTrainerPic(u32 battler)
{
    u32 trainerPicId;
    bool32 isFrontPic;
    s16 xPos, yPos;

    if (gPartnerTrainerId == TRAINER_STEVEN_PARTNER)
    {
        trainerPicId = TRAINER_BACK_PIC_STEVEN;
        xPos = 90;
        yPos = (8 - gTrainerBackPicCoords[trainerPicId].size) * 4 + 80;
        isFrontPic = FALSE;
    }
    else
    {
        trainerPicId = GetFrontierTrainerFrontSpriteId(gPartnerTrainerId);
        xPos = 32;
        yPos = (8 - gTrainerFrontPicCoords[trainerPicId].size) * 4 + 80;
        isFrontPic = TRUE;
    }

    BtlController_HandleDrawTrainerPic(battler, trainerPicId, xPos, yPos, GetBattlerSpriteSubpriority(battler), isFrontPic);
}

#undef sSpeedX

static void PlayerPartnerHandleTrainerSlideBack(u32 battler)
{
    BtlController_HandleTrainerSlideBack(battler, 35, FALSE);
}

static void PlayerPartnerHandlePaletteFade(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleSuccessBallThrowAnim(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleBallThrowAnim(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandlePause(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleMoveAnimation(u32 battler)
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
            PlayerPartnerBufferExecCompleted(battler);
        }
        else
        {
            gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 0;
            gBattlerControllerFuncs[battler] = PlayerPartnerDoMoveAnimation;
        }
    }
}

static void PlayerPartnerDoMoveAnimation(u32 battler)
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
            PlayerPartnerBufferExecCompleted(battler);
        }
        break;
    }
}

static void PlayerPartnerHandlePrintString(u32 battler)
{
    u16 *stringId;

    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    stringId = (u16 *)(&gBattleBufferA[battler][2]);
    BufferStringBattle(battler, *stringId);
    BattlePutTextOnWindow(gDisplayedStringBattle, B_WIN_MSG);
    gBattlerControllerFuncs[battler] = CompleteOnInactiveTextPrinter2;
}

static void PlayerPartnerHandlePrintSelectionString(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleChooseAction(u32 battler)
{
    AI_TrySwitchOrUseItem(battler);
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleYesNoBox(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleChooseMove(u32 battler)
{
    u8 chosenMoveId;
    struct ChooseMoveStruct *moveInfo = (struct ChooseMoveStruct *)(&gBattleBufferA[battler][4]);

    BattleAI_SetupAIData(battler, ALL_MOVES_MASK);
    chosenMoveId = BattleAI_ChooseMoveOrAction(battler);

    if (GetMoveTarget(moveInfo->moves[chosenMoveId]) & (MOVE_TARGET_USER | MOVE_TARGET_USER_OR_SELECTED))
        gBattlerTarget = battler;
    if (GetMoveTarget(moveInfo->moves[chosenMoveId]) & MOVE_TARGET_BOTH)
    {
        gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
            gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
    }

    BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, chosenMoveId | (gBattlerTarget << 8));
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleChooseItem(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleChoosePokemon(u32 battler)
{
    s32 chosenMonId = GetMostSuitableMonToSwitchInto(battler);

    if (chosenMonId == PARTY_SIZE) // just switch to the next mon
    {
        u8 playerMonIdentity = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        u8 selfIdentity = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);

        for (chosenMonId = PARTY_SIZE / 2; chosenMonId < PARTY_SIZE; chosenMonId++)
        {
            if (GetMonData(&gPlayerParty[chosenMonId], MON_DATA_HP) != 0
                && chosenMonId != gBattlerPartyIndexes[playerMonIdentity]
                && chosenMonId != gBattlerPartyIndexes[selfIdentity])
            {
                break;
            }
        }
    }

    gBattleStruct->monToSwitchIntoId[battler] = chosenMonId;
    BtlController_EmitChosenMonReturnValue(battler, BUFFER_B, chosenMonId, NULL);
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleCmd23(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleHealthBarUpdate(u32 battler)
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
    }

    gBattlerControllerFuncs[battler] = CompleteOnHealthbarDone;
}

static void PlayerPartnerHandleExpUpdate(u32 battler)
{
    u8 monId = gBattleBufferA[battler][1];

    if (GetMonData(&gPlayerParty[monId], MON_DATA_LEVEL) >= MAX_LEVEL)
    {
        PlayerPartnerBufferExecCompleted(battler);
    }
    else
    {
        s16 expPointsToGive;
        u8 taskId;

        LoadBattleBarGfx(1);
        GetMonData(&gPlayerParty[monId], MON_DATA_SPECIES);  // unused return value
        expPointsToGive = gBattleBufferA[battler][2] | (gBattleBufferA[battler][3] << 8);
        taskId = CreateTask(Task_GiveExpToMon, 10);
        gTasks[taskId].tExpTask_monId = monId;
        gTasks[taskId].tExpTask_gainedExp = expPointsToGive;
        gTasks[taskId].tExpTask_bank = battler;
        gBattlerControllerFuncs[battler] = BattleControllerDummy;
    }
}

#undef tExpTask_monId
#undef tExpTask_gainedExp
#undef tExpTask_bank
#undef tExpTask_frames

static void PlayerPartnerHandleStatusIconUpdate(u32 battler)
{
    if (!IsBattleSEPlaying(battler))
    {
        UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gPlayerParty[gBattlerPartyIndexes[battler]], HEALTHBOX_STATUS_ICON);
        gBattleSpritesDataPtr->healthBoxesData[battler].statusAnimActive = 0;
        gBattlerControllerFuncs[battler] = CompleteOnFinishedStatusAnimation;
    }
}

static void PlayerPartnerHandleStatusAnimation(u32 battler)
{
    if (!IsBattleSEPlaying(battler))
    {
        InitAndLaunchChosenStatusAnimation(battler, gBattleBufferA[battler][1],
                        gBattleBufferA[battler][2] | (gBattleBufferA[battler][3] << 8) | (gBattleBufferA[battler][4] << 16) | (gBattleBufferA[battler][5] << 24));
        gBattlerControllerFuncs[battler] = CompleteOnFinishedStatusAnimation;
    }
}

static void PlayerPartnerHandleStatusXor(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleDataTransfer(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleDMA3Transfer(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandlePlayBGM(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleCmd32(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleTwoReturnValues(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleChosenMonReturnValue(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleOneReturnValue(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleOneReturnValue_Duplicate(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleClearUnkVar(u32 battler)
{
    gUnusedControllerStruct.unk = 0;
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleSetUnkVar(u32 battler)
{
    gUnusedControllerStruct.unk = gBattleBufferA[battler][1];
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleClearUnkFlag(u32 battler)
{
    gUnusedControllerStruct.flag = 0;
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleToggleUnkFlag(u32 battler)
{
    gUnusedControllerStruct.flag ^= 1;
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleHitAnimation(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].invisible == TRUE)
    {
        PlayerPartnerBufferExecCompleted(battler);
    }
    else
    {
        gDoingBattleAnim = TRUE;
        gSprites[gBattlerSpriteIds[battler]].data[1] = 0;
        DoHitAnimHealthboxEffect(battler);
        gBattlerControllerFuncs[battler] = DoHitAnimBlinkSpriteEffect;
    }
}

static void PlayerPartnerHandleCantSwitch(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandlePlaySE(u32 battler)
{
    s8 pan;

    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        pan = SOUND_PAN_ATTACKER;
    else
        pan = SOUND_PAN_TARGET;

    PlaySE12WithPanning(gBattleBufferA[battler][1] | (gBattleBufferA[battler][2] << 8), pan);
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandlePlayFanfareOrBGM(u32 battler)
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

    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleFaintingCry(u32 battler)
{
    u16 species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);

    PlayCry_ByMode(species, -25, CRY_MODE_FAINT);
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleIntroSlide(u32 battler)
{
    HandleIntroSlide(gBattleBufferA[battler][1]);
    gIntroSlideFlags |= 1;
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleIntroTrainerBallThrow(u32 battler)
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

    paletteNum = AllocSpritePalette(0xD6F9);
    if (gPartnerTrainerId == TRAINER_STEVEN_PARTNER)
    {
        u8 spriteId = TRAINER_BACK_PIC_STEVEN;
        LoadCompressedPalette(gTrainerBackPicPaletteTable[spriteId].data, OBJ_PLTT_ID(paletteNum), PLTT_SIZE_4BPP);
    }
    else
    {
        u8 spriteId = GetFrontierTrainerFrontSpriteId(gPartnerTrainerId);
        LoadCompressedPalette(gTrainerFrontPicPaletteTable[spriteId].data, OBJ_PLTT_ID(paletteNum), PLTT_SIZE_4BPP);
    }


    gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = paletteNum;

    taskId = CreateTask(Task_StartSendOutAnim, 5);
    gTasks[taskId].data[0] = battler;

    if (gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusSummaryShown)
        gTasks[gBattlerStatusSummaryTaskId[battler]].func = Task_HidePartyStatusSummary;

    gBattleSpritesDataPtr->animationData->introAnimActive = TRUE;
    gBattlerControllerFuncs[battler] = PlayerPartnerDummy;
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
            StartSendOutAnim(battler, FALSE, FALSE);
        }
        else
        {
            gBattleBufferA[battler][1] = gBattlerPartyIndexes[battler];
            StartSendOutAnim(battler, FALSE, FALSE);
            battler ^= BIT_FLANK;
            gBattleBufferA[battler][1] = gBattlerPartyIndexes[battler];
            BattleLoadPlayerMonSpriteGfx(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
            StartSendOutAnim(battler, FALSE, FALSE);
            battler ^= BIT_FLANK;
        }
        gBattlerControllerFuncs[battler] = Intro_ShowHealthbox;
        DestroyTask(taskId);
    }
}

static void PlayerPartnerHandleDrawPartyStatusSummary(u32 battler)
{
    if (gBattleBufferA[battler][1] != 0 && GetBattlerSide(battler) == B_SIDE_PLAYER)
    {
        PlayerPartnerBufferExecCompleted(battler);
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
        PlayerPartnerBufferExecCompleted(battler);
    }
}

static void PlayerPartnerHandleHidePartyStatusSummary(u32 battler)
{
    if (gBattleSpritesDataPtr->healthBoxesData[battler].partyStatusSummaryShown)
        gTasks[gBattlerStatusSummaryTaskId[battler]].func = Task_HidePartyStatusSummary;
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleEndBounceEffect(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleSpriteInvisibility(u32 battler)
{
    if (IsBattlerSpritePresent(battler))
    {
        gSprites[gBattlerSpriteIds[battler]].invisible = gBattleBufferA[battler][1];
        CopyBattleSpriteInvisibility(battler);
    }
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleBattleAnimation(u32 battler)
{
    if (!IsBattleSEPlaying(battler))
    {
        u8 animationId = gBattleBufferA[battler][1];
        u16 argument = gBattleBufferA[battler][2] | (gBattleBufferA[battler][3] << 8);

        if (TryHandleLaunchBattleTableAnimation(battler, battler, battler, animationId, argument))
            PlayerPartnerBufferExecCompleted(battler);
        else
            gBattlerControllerFuncs[battler] = CompleteOnFinishedBattleAnimation;
    }
}

static void PlayerPartnerHandleLinkStandbyMsg(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleResetActionMoveSelection(u32 battler)
{
    PlayerPartnerBufferExecCompleted(battler);
}

static void PlayerPartnerHandleEndLinkBattle(u32 battler)
{
    gBattleOutcome = gBattleBufferA[battler][1];
    FadeOutMapMusic(5);
    BeginFastPaletteFade(3);
    PlayerPartnerBufferExecCompleted(battler);
    gBattlerControllerFuncs[battler] = SetBattleEndCallbacks;
}

static void PlayerPartnerCmdEnd(u32 battler)
{
}
