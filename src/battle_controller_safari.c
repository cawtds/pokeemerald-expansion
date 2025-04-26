#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_message.h"
#include "bg.h"
#include "data.h"
#include "item_menu.h"
#include "link.h"
#include "main.h"
#include "m4a.h"
#include "palette.h"
#include "pokeball.h"
#include "pokeblock.h"
#include "pokemon.h"
#include "reshow_battle_screen.h"
#include "sound.h"
#include "task.h"
#include "text.h"
#include "util.h"
#include "window.h"
#include "constants/battle_anim.h"
#include "constants/songs.h"
#include "constants/rgb.h"

static void SafariHandleDrawTrainerPic(u32 battler);
static void SafariHandleSuccessBallThrowAnim(u32 battler);
static void SafariHandleBallThrowAnim(u32 battler);
static void SafariHandlePrintString(u32 battler);
static void SafariHandlePrintSelectionString(u32 battler);
static void SafariHandleChooseAction(u32 battler);
static void SafariHandleChooseItem(u32 battler);
static void SafariHandleStatusIconUpdate(u32 battler);
static void SafariHandlePlaySE(u32 battler);
static void SafariHandlePlayFanfareOrBGM(u32 battler);
static void SafariHandleFaintingCry(u32 battler);
static void SafariHandleIntroSlide(u32 battler);
static void SafariHandleIntroTrainerBallThrow(u32 battler);
static void SafariHandleBattleAnimation(u32 battler);
static void SafariHandleEndLinkBattle(u32 battler);

static void SafariBufferRunCommand(u32 battler);
static void SafariBufferExecCompleted(u32 battler);
static void CompleteWhenChosePokeblock(u32 battler);

static void (*const sSafariBufferCommands[CONTROLLER_CMDS_COUNT])(u32 battler) =
{
    [CONTROLLER_GETMONDATA]               = BtlController_Empty,
    [CONTROLLER_GETRAWMONDATA]            = BtlController_Empty,
    [CONTROLLER_SETMONDATA]               = BtlController_Empty,
    [CONTROLLER_SETRAWMONDATA]            = BtlController_Empty,
    [CONTROLLER_LOADMONSPRITE]            = BtlController_Empty,
    [CONTROLLER_SWITCHINANIM]             = BtlController_Empty,
    [CONTROLLER_RETURNMONTOBALL]          = BtlController_Empty,
    [CONTROLLER_DRAWTRAINERPIC]           = SafariHandleDrawTrainerPic,
    [CONTROLLER_TRAINERSLIDE]             = BtlController_Empty,
    [CONTROLLER_TRAINERSLIDEBACK]         = BtlController_Empty,
    [CONTROLLER_FAINTANIMATION]           = BtlController_Empty,
    [CONTROLLER_PALETTEFADE]              = BtlController_Empty,
    [CONTROLLER_SUCCESSBALLTHROWANIM]     = SafariHandleSuccessBallThrowAnim,
    [CONTROLLER_BALLTHROWANIM]            = SafariHandleBallThrowAnim,
    [CONTROLLER_PAUSE]                    = BtlController_Empty,
    [CONTROLLER_MOVEANIMATION]            = BtlController_Empty,
    [CONTROLLER_PRINTSTRING]              = SafariHandlePrintString,
    [CONTROLLER_PRINTSTRINGPLAYERONLY]    = SafariHandlePrintSelectionString,
    [CONTROLLER_CHOOSEACTION]             = SafariHandleChooseAction,
    [CONTROLLER_YESNOBOX]                 = BtlController_Empty,
    [CONTROLLER_CHOOSEMOVE]               = BtlController_Empty,
    [CONTROLLER_OPENBAG]                  = SafariHandleChooseItem,
    [CONTROLLER_CHOOSEPOKEMON]            = BtlController_Empty,
    [CONTROLLER_23]                       = BtlController_Empty,
    [CONTROLLER_HEALTHBARUPDATE]          = BtlController_Empty,
    [CONTROLLER_EXPUPDATE]                = BtlController_Empty,
    [CONTROLLER_STATUSICONUPDATE]         = SafariHandleStatusIconUpdate,
    [CONTROLLER_STATUSANIMATION]          = BtlController_Empty,
    [CONTROLLER_STATUSXOR]                = BtlController_Empty,
    [CONTROLLER_DATATRANSFER]             = BtlController_Empty,
    [CONTROLLER_DMA3TRANSFER]             = BtlController_Empty,
    [CONTROLLER_PLAYBGM]                  = BtlController_Empty,
    [CONTROLLER_32]                       = BtlController_Empty,
    [CONTROLLER_TWORETURNVALUES]          = BtlController_Empty,
    [CONTROLLER_ONERETURNVALUE]           = BtlController_Empty,
    [CONTROLLER_ONERETURNVALUE_DUPLICATE] = BtlController_Empty,
    [CONTROLLER_CLEARUNKVAR]              = BtlController_Empty,
    [CONTROLLER_SETUNKVAR]                = BtlController_Empty,
    [CONTROLLER_CLEARUNKFLAG]             = BtlController_Empty,
    [CONTROLLER_TOGGLEUNKFLAG]            = BtlController_Empty,
    [CONTROLLER_HITANIMATION]             = BtlController_Empty,
    [CONTROLLER_CANTSWITCH]               = BtlController_Empty,
    [CONTROLLER_PLAYSE]                   = SafariHandlePlaySE,
    [CONTROLLER_PLAYFANFAREORBGM]         = SafariHandlePlayFanfareOrBGM,
    [CONTROLLER_FAINTINGCRY]              = SafariHandleFaintingCry,
    [CONTROLLER_INTROSLIDE]               = SafariHandleIntroSlide,
    [CONTROLLER_INTROTRAINERBALLTHROW]    = SafariHandleIntroTrainerBallThrow,
    [CONTROLLER_DRAWPARTYSTATUSSUMMARY]   = BtlController_Empty,
    [CONTROLLER_HIDEPARTYSTATUSSUMMARY]   = BtlController_Empty,
    [CONTROLLER_ENDBOUNCE]                = BtlController_Empty,
    [CONTROLLER_SPRITEINVISIBILITY]       = BtlController_Empty,
    [CONTROLLER_BATTLEANIMATION]          = SafariHandleBattleAnimation,
    [CONTROLLER_LINKSTANDBYMSG]           = BtlController_Empty,
    [CONTROLLER_RESETACTIONMOVESELECTION] = BtlController_Empty,
    [CONTROLLER_ENDLINKBATTLE]            = SafariHandleEndLinkBattle,
    [CONTROLLER_TERMINATOR_NOP]           = BtlController_TerminatorNop
};

static void UNUSED SpriteCB_Null4(u32 battler)
{
}

void SetControllerToSafari(u32 battler)
{
    gBattlerControllerFuncs[battler] = SafariBufferRunCommand;
    gBattlerControllerEndFuncs[battler] = SafariBufferExecCompleted;
}

static void SafariBufferRunCommand(u32 battler)
{
    if (gBattleControllerExecFlags & gBitTable[battler])
    {
        if (gBattleBufferA[battler][0] < ARRAY_COUNT(sSafariBufferCommands))
            sSafariBufferCommands[gBattleBufferA[battler][0]](battler);
        else
            SafariBufferExecCompleted(battler);
    }
}

static void HandleInputChooseAction(u32 battler)
{
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        switch (gActionSelectionCursor[battler])
        {
        case 0:
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_SAFARI_BALL, 0);
            break;
        case 1:
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_SAFARI_POKEBLOCK, 0);
            break;
        case 2:
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_SAFARI_GO_NEAR, 0);
            break;
        case 3:
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_SAFARI_RUN, 0);
            break;
        }
        SafariBufferExecCompleted(battler);
    }
    else if (JOY_NEW(DPAD_LEFT))
    {
        if (gActionSelectionCursor[battler] & 1)
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[battler]);
            gActionSelectionCursor[battler] ^= 1;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[battler], 0);
        }
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        if (!(gActionSelectionCursor[battler] & 1))
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[battler]);
            gActionSelectionCursor[battler] ^= 1;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[battler], 0);
        }
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (gActionSelectionCursor[battler] & 2)
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[battler]);
            gActionSelectionCursor[battler] ^= 2;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[battler], 0);
        }
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (!(gActionSelectionCursor[battler] & 2))
        {
            PlaySE(SE_SELECT);
            ActionSelectionDestroyCursorAt(gActionSelectionCursor[battler]);
            gActionSelectionCursor[battler] ^= 2;
            ActionSelectionCreateCursorAt(gActionSelectionCursor[battler], 0);
        }
    }
}

static void CompleteOnBattlerSpriteCallbackDummy(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
        SafariBufferExecCompleted(battler);
}

static void CompleteOnInactiveTextPrinter(u32 battler)
{
    if (!IsTextPrinterActive(B_WIN_MSG))
        SafariBufferExecCompleted(battler);
}

static void CompleteOnHealthboxSpriteCallbackDummy(u32 battler)
{
    if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy)
        SafariBufferExecCompleted(battler);
}

static void SafariSetBattleEndCallbacks(u32 battler)
{
    if (!gPaletteFade.active)
    {
        gMain.inBattle = FALSE;
        gMain.callback1 = gPreBattleCallback1;
        SetMainCallback2(gMain.savedCallback);
    }
}

static void CompleteOnSpecialAnimDone(u32 battler)
{
    if (!gDoingBattleAnim || !gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive)
        SafariBufferExecCompleted(battler);
}

static void SafariOpenPokeblockCase(u32 battler)
{
    if (!gPaletteFade.active)
    {
        gBattlerControllerFuncs[battler] = CompleteWhenChosePokeblock;
        FreeAllWindowBuffers();
        OpenPokeblockCaseInBattle();
    }
}

static void CompleteWhenChosePokeblock(u32 battler)
{
    if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
    {
        BtlController_EmitOneReturnValue(battler, BUFFER_B, gSpecialVar_ItemId);
        SafariBufferExecCompleted(battler);
    }
}

static void CompleteOnFinishedBattleAnimation(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].animFromTableActive)
        SafariBufferExecCompleted(battler);
}

static void SafariBufferExecCompleted(u32 battler)
{
    gBattlerControllerFuncs[battler] = SafariBufferRunCommand;
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
        SafariBufferExecCompleted(battler);
}

#define sSpeedX data[0]

static void SafariHandleDrawTrainerPic(u32 battler)
{
    DecompressTrainerBackPic(gSaveBlock2Ptr->playerGender, battler);
    SetMultiuseSpriteTemplateToTrainerBack(gSaveBlock2Ptr->playerGender, GetBattlerPosition(battler));
    gBattlerSpriteIds[battler] = CreateSprite(
      &gMultiuseSpriteTemplate,
      80,
      (8 - gTrainerBackPicCoords[gSaveBlock2Ptr->playerGender].size) * 4 + 80,
      30);
    gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = battler;
    gSprites[gBattlerSpriteIds[battler]].x2 = DISPLAY_WIDTH;
    gSprites[gBattlerSpriteIds[battler]].sSpeedX = -2;
    gSprites[gBattlerSpriteIds[battler]].callback = SpriteCB_TrainerSlideIn;
    gBattlerControllerFuncs[battler] = CompleteOnBattlerSpriteCallbackDummy;
}

#undef sSpeedX

static void SafariHandleSuccessBallThrowAnim(u32 battler)
{
    gBattleSpritesDataPtr->animationData->ballThrowCaseId = BALL_3_SHAKES_SUCCESS;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(battler, battler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), B_ANIM_BALL_THROW_WITH_TRAINER);
    gBattlerControllerFuncs[battler] = CompleteOnSpecialAnimDone;
}

static void SafariHandleBallThrowAnim(u32 battler)
{
    u8 ballThrowCaseId = gBattleBufferA[battler][1];

    gBattleSpritesDataPtr->animationData->ballThrowCaseId = ballThrowCaseId;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(battler, battler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), B_ANIM_BALL_THROW_WITH_TRAINER);
    gBattlerControllerFuncs[battler] = CompleteOnSpecialAnimDone;
}

static void SafariHandlePrintString(u32 battler)
{
    u16 *stringId;

    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    stringId = (u16 *)(&gBattleBufferA[battler][2]);
    BufferStringBattle(battler, *stringId);
    BattlePutTextOnWindow(gDisplayedStringBattle, B_WIN_MSG);
    gBattlerControllerFuncs[battler] = CompleteOnInactiveTextPrinter;
}

static void SafariHandlePrintSelectionString(u32 battler)
{
    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        SafariHandlePrintString(battler);
    else
        SafariBufferExecCompleted(battler);
}

static void HandleChooseActionAfterDma3(u32 battler)
{
    if (!IsDma3ManagerBusyWithBgCopy())
    {
        gBattle_BG0_X = 0;
        gBattle_BG0_Y = DISPLAY_HEIGHT;
        gBattlerControllerFuncs[battler] = HandleInputChooseAction;
    }
}

static void SafariHandleChooseAction(u32 battler)
{
    s32 i;

    gBattlerControllerFuncs[battler] = HandleChooseActionAfterDma3;
    BattlePutTextOnWindow(gText_SafariZoneMenu, B_WIN_ACTION_MENU);

    for (i = 0; i < 4; i++)
        ActionSelectionDestroyCursorAt(i);

    ActionSelectionCreateCursorAt(gActionSelectionCursor[battler], 0);
    BattleStringExpandPlaceholdersToDisplayedString(gText_WhatWillPkmnDo2);
    BattlePutTextOnWindow(gDisplayedStringBattle, B_WIN_ACTION_PROMPT);
}

static void SafariHandleChooseItem(u32 battler)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gBattlerControllerFuncs[battler] = SafariOpenPokeblockCase;
    gBattlerInMenuId = battler;
}

static void SafariHandleStatusIconUpdate(u32 battler)
{
    UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gPlayerParty[gBattlerPartyIndexes[battler]], HEALTHBOX_SAFARI_BALLS_TEXT);
    SafariBufferExecCompleted(battler);
}

static void SafariHandlePlaySE(u32 battler)
{
    s8 pan;

    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        pan = SOUND_PAN_ATTACKER;
    else
        pan = SOUND_PAN_TARGET;

    PlaySE12WithPanning(gBattleBufferA[battler][1] | (gBattleBufferA[battler][2] << 8), pan);
    SafariBufferExecCompleted(battler);
}

static void SafariHandlePlayFanfareOrBGM(u32 battler)
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

    SafariBufferExecCompleted(battler);
}

static void SafariHandleFaintingCry(u32 battler)
{
    u16 species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);

    PlayCry_Normal(species, 25);
    SafariBufferExecCompleted(battler);
}

static void SafariHandleIntroSlide(u32 battler)
{
    HandleIntroSlide(gBattleBufferA[battler][1]);
    gIntroSlideFlags |= 1;
    SafariBufferExecCompleted(battler);
}

static void SafariHandleIntroTrainerBallThrow(u32 battler)
{
    UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gPlayerParty[gBattlerPartyIndexes[battler]], HEALTHBOX_SAFARI_ALL_TEXT);
    StartHealthboxSlideIn(battler);
    SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);
    gBattlerControllerFuncs[battler] = CompleteOnHealthboxSpriteCallbackDummy;
}

static void SafariHandleBattleAnimation(u32 battler)
{
    u8 animationId = gBattleBufferA[battler][1];
    u16 argument = gBattleBufferA[battler][2] | (gBattleBufferA[battler][3] << 8);

    if (TryHandleLaunchBattleTableAnimation(battler, battler, battler, animationId, argument))
        SafariBufferExecCompleted(battler);
    else
        gBattlerControllerFuncs[battler] = CompleteOnFinishedBattleAnimation;
}

static void SafariHandleEndLinkBattle(u32 battler)
{
    gBattleOutcome = gBattleBufferA[battler][1];
    FadeOutMapMusic(5);
    BeginFastPaletteFade(3);
    SafariBufferExecCompleted(battler);
    if ((gBattleTypeFlags & BATTLE_TYPE_LINK) && !(gBattleTypeFlags & BATTLE_TYPE_IS_MASTER))
        gBattlerControllerFuncs[battler] = SafariSetBattleEndCallbacks;
}
