#include "global.h"
#include "battle.h"
#include "battle_ai_script_commands.h"
#include "battle_anim.h"
#include "battle_arena.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_message.h"
#include "battle_tv.h"
#include "cable_club.h"
#include "data.h"
#include "link.h"
#include "link_rfu.h"
#include "move.h"
#include "party_menu.h"
#include "recorded_battle.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "test_runner.h"
#include "text.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/songs.h"
#include "constants/sound.h"

static EWRAM_DATA u8 sLinkSendTaskId = 0;
static EWRAM_DATA u8 sLinkReceiveTaskId = 0;
static EWRAM_DATA u8 sBattleBuffersTransferData[0x100] = {};
COMMON_DATA void (*gBattlerControllerEndFuncs[MAX_BATTLERS_COUNT])(u32 battler) = {0}; // Controller's buffer complete function for each battler

static void CreateTasksForSendRecvLinkBuffers(void);
static void InitLinkBtlControllers(void);
static void InitSinglePlayerBtlControllers(void);
static void SetBattlePartyIds(void);
static void Task_HandleSendLinkBuffersData(u8 taskId);
static void Task_HandleCopyReceivedLinkBuffersData(u8 taskId);

void HandleLinkBattleSetup(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        if (gWirelessCommType)
            SetWirelessCommType1();
        if (!gReceivedRemoteLinkPlayers)
            OpenLink();
        CreateTask(Task_WaitForLinkPlayerConnection, 0);
        CreateTasksForSendRecvLinkBuffers();
    }
}

void SetUpBattleVarsAndBirchZigzagoon(void)
{
    s32 i;

    gBattleMainFunc = BeginBattleIntroDummy;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        gBattlerControllerFuncs[i] = BattleControllerDummy;
        gBattlerPositions[i] = 0xFF;
        gActionSelectionCursor[i] = 0;
        gMoveSelectionCursor[i] = 0;
    }

    HandleLinkBattleSetup();
    gBattleControllerExecFlags = 0;
    ClearBattleAnimationVars();
    ClearBattleMonForms();
    BattleAI_HandleItemUseBeforeAISetup(B_POSITION_OPPONENT_LEFT, ALL_MOVES_MASK);

    if (gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE)
    {
        ZeroEnemyPartyMons();
        CreateMon(&gEnemyParty[0], SPECIES_ZIGZAGOON, 2, USE_RANDOM_IVS, 0, 0, OT_ID_PLAYER_ID, 0);
        i = 0;
        SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, &i);
    }

    // Below are never read
    gUnusedFirstBattleVar1 = 0;
    gUnusedFirstBattleVar2 = 0;
}

void InitBattleControllers(void)
{
    s32 i;

    if (!(gBattleTypeFlags & BATTLE_TYPE_RECORDED))
        RecordedBattle_Init(B_RECORD_MODE_RECORDING);
    else
        RecordedBattle_Init(B_RECORD_MODE_PLAYBACK);

    if (!(gBattleTypeFlags & BATTLE_TYPE_RECORDED))
        RecordedBattle_SaveParties();

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        InitLinkBtlControllers();
    else
        InitSinglePlayerBtlControllers();

    SetBattlePartyIds();

    if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
    {
        for (i = 0; i < gBattlersCount; i++)
            BufferBattlePartyCurrentOrderBySide(i, 0);
    }

    for (i = 0; i < sizeof(gBattleStruct->tvMovePoints); i++)
        *((u8 *)(&gBattleStruct->tvMovePoints) + i) = 0;

    for (i = 0; i < sizeof(gBattleStruct->tv); i++)
        *((u8 *)(&gBattleStruct->tv) + i) = 0;
}

static void InitSinglePlayerBtlControllers(void)
{
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
    {
        gBattleMainFunc = BeginBattleIntro;

        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            gBattlerControllerFuncs[0] = SetControllerToRecordedPlayer;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

            gBattlerControllerFuncs[1] = SetControllerToOpponent;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

            gBattlerControllerFuncs[2] = SetControllerToPlayerPartner;
            gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;

            gBattlerControllerFuncs[3] = SetControllerToOpponent;
            gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;
        }
        else
        {
            gBattlerControllerFuncs[0] = SetControllerToPlayer;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

            gBattlerControllerFuncs[1] = SetControllerToOpponent;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

            gBattlerControllerFuncs[2] = SetControllerToPlayerPartner;
            gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;

            gBattlerControllerFuncs[3] = SetControllerToOpponent;
            gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;
        }

        gBattlersCount = MAX_BATTLERS_COUNT;

        BufferBattlePartyCurrentOrderBySide(0, 0);
        BufferBattlePartyCurrentOrderBySide(1, 0);
        BufferBattlePartyCurrentOrderBySide(2, 1);
        BufferBattlePartyCurrentOrderBySide(3, 1);

        gBattlerPartyIndexes[0] = 0;
        gBattlerPartyIndexes[1] = 0;
        gBattlerPartyIndexes[2] = 3;
        gBattlerPartyIndexes[3] = 3;
    }
    else if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
    {
        gBattleMainFunc = BeginBattleIntro;

        if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
            gBattlerControllerFuncs[0] = SetControllerToSafari;
        else if (gBattleTypeFlags & BATTLE_TYPE_WALLY_TUTORIAL)
            gBattlerControllerFuncs[0] = SetControllerToWally;
        else
            gBattlerControllerFuncs[0] = SetControllerToPlayer;

        gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

        gBattlerControllerFuncs[1] = SetControllerToOpponent;
        gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

        gBattlersCount = 2;

        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_IS_MASTER)
                {
                    gBattleMainFunc = BeginBattleIntro;

                    gBattlerControllerFuncs[0] = SetControllerToRecordedPlayer;
                    gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

                    gBattlerControllerFuncs[1] = SetControllerToRecordedOpponent;
                    gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

                    gBattlersCount = 2;
                }
                else // see how the banks are switched
                {
                    gBattlerControllerFuncs[1] = SetControllerToRecordedPlayer;
                    gBattlerPositions[1] = B_POSITION_PLAYER_LEFT;

                    gBattlerControllerFuncs[0] = SetControllerToRecordedOpponent;
                    gBattlerPositions[0] = B_POSITION_OPPONENT_LEFT;

                    gBattlersCount = 2;
                }
            }
            else
            {
                gBattlerControllerFuncs[0] = SetControllerToRecordedPlayer;
                gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

                gBattlerControllerFuncs[1] = SetControllerToOpponent;
                gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;
            }
        }
    }
    else
    {
        gBattleMainFunc = BeginBattleIntro;

        gBattlerControllerFuncs[0] = SetControllerToPlayer;
        gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

        gBattlerControllerFuncs[1] = SetControllerToOpponent;
        gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

        gBattlerControllerFuncs[2] = SetControllerToPlayer;
        gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;

        gBattlerControllerFuncs[3] = SetControllerToOpponent;
        gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;

        gBattlersCount = MAX_BATTLERS_COUNT;

        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI && gBattleTypeFlags & BATTLE_TYPE_BATTLE_TOWER)
            {
                gBattleMainFunc = BeginBattleIntro;

                gBattlerControllerFuncs[0] = SetControllerToRecordedPlayer;
                gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

                gBattlerControllerFuncs[1] = SetControllerToOpponent;
                gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

                gBattlerControllerFuncs[2] = SetControllerToRecordedPlayer;
                gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;

                gBattlerControllerFuncs[3] = SetControllerToOpponent;
                gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;

                gBattlersCount = MAX_BATTLERS_COUNT;

                BufferBattlePartyCurrentOrderBySide(0, 0);
                BufferBattlePartyCurrentOrderBySide(1, 0);
                BufferBattlePartyCurrentOrderBySide(2, 1);
                BufferBattlePartyCurrentOrderBySide(3, 1);

                gBattlerPartyIndexes[0] = 0;
                gBattlerPartyIndexes[1] = 0;
                gBattlerPartyIndexes[2] = 3;
                gBattlerPartyIndexes[3] = 3;
            }
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                u8 multiplayerId;

                for (multiplayerId = gRecordedBattleMultiplayerId, i = 0; i < MAX_BATTLERS_COUNT; i++)
                {
                    switch (gLinkPlayers[i].id)
                    {
                    case 0:
                    case 3:
                        BufferBattlePartyCurrentOrderBySide(gLinkPlayers[i].id, 0);
                        break;
                    case 1:
                    case 2:
                        BufferBattlePartyCurrentOrderBySide(gLinkPlayers[i].id, 1);
                        break;
                    }

                    if (i == multiplayerId)
                    {
                        gBattlerControllerFuncs[gLinkPlayers[i].id] = SetControllerToRecordedPlayer;
                        switch (gLinkPlayers[i].id)
                        {
                        case 0:
                        case 3:
                            gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_LEFT;
                            gBattlerPartyIndexes[gLinkPlayers[i].id] = 0;
                            break;
                        case 1:
                        case 2:
                            gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_RIGHT;
                            gBattlerPartyIndexes[gLinkPlayers[i].id] = 3;
                            break;
                        }
                    }
                    else if ((!(gLinkPlayers[i].id & 1) && !(gLinkPlayers[multiplayerId].id & 1))
                            || ((gLinkPlayers[i].id & 1) && (gLinkPlayers[multiplayerId].id & 1)))
                    {
                        gBattlerControllerFuncs[gLinkPlayers[i].id] = SetControllerToRecordedPlayer;
                        switch (gLinkPlayers[i].id)
                        {
                        case 0:
                        case 3:
                            gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_LEFT;
                            gBattlerPartyIndexes[gLinkPlayers[i].id] = 0;
                            break;
                        case 1:
                        case 2:
                            gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_RIGHT;
                            gBattlerPartyIndexes[gLinkPlayers[i].id] = 3;
                            break;
                        }
                    }
                    else
                    {
                        gBattlerControllerFuncs[gLinkPlayers[i].id] = SetControllerToRecordedOpponent;
                        switch (gLinkPlayers[i].id)
                        {
                        case 0:
                        case 3:
                            gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_OPPONENT_LEFT;
                            gBattlerPartyIndexes[gLinkPlayers[i].id] = 0;
                            break;
                        case 1:
                        case 2:
                            gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_OPPONENT_RIGHT;
                            gBattlerPartyIndexes[gLinkPlayers[i].id] = 3;
                            break;
                        }
                    }
                }
            }
            else if (gBattleTypeFlags & BATTLE_TYPE_IS_MASTER)
            {
                gBattlerControllerFuncs[0] = SetControllerToRecordedPlayer;
                gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

                gBattlerControllerFuncs[2] = SetControllerToRecordedPlayer;
                gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;

                if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                {
                  gBattlerControllerFuncs[1] = SetControllerToRecordedOpponent;
                  gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

                  gBattlerControllerFuncs[3] = SetControllerToRecordedOpponent;
                  gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;
                }
                else
                {
                  gBattlerControllerFuncs[1] = SetControllerToOpponent;
                  gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

                  gBattlerControllerFuncs[3] = SetControllerToOpponent;
                  gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;
                }
            }
            else
            {
                gBattlerControllerFuncs[1] = SetControllerToRecordedPlayer;
                gBattlerPositions[1] = B_POSITION_PLAYER_LEFT;

                gBattlerControllerFuncs[3] = SetControllerToRecordedPlayer;
                gBattlerPositions[3] = B_POSITION_PLAYER_RIGHT;

                if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                {
                    gBattlerControllerFuncs[0] = SetControllerToRecordedOpponent;
                    gBattlerPositions[0] = B_POSITION_OPPONENT_LEFT;

                    gBattlerControllerFuncs[2] = SetControllerToRecordedOpponent;
                    gBattlerPositions[2] = B_POSITION_OPPONENT_RIGHT;
                }
                else
                {
                    gBattlerControllerFuncs[0] = SetControllerToOpponent;
                    gBattlerPositions[0] = B_POSITION_OPPONENT_LEFT;

                    gBattlerControllerFuncs[2] = SetControllerToOpponent;
                    gBattlerPositions[2] = B_POSITION_OPPONENT_RIGHT;
                }
            }
        }
    }
}

static void InitLinkBtlControllers(void)
{
    s32 i;
    u8 multiplayerId;

    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
    {
        if (gBattleTypeFlags & BATTLE_TYPE_IS_MASTER)
        {
            gBattleMainFunc = BeginBattleIntro;

            gBattlerControllerFuncs[0] = SetControllerToPlayer;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

            gBattlerControllerFuncs[1] = SetControllerToLinkOpponent;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

            gBattlersCount = 2;
        }
        else
        {
            gBattlerControllerFuncs[1] = SetControllerToPlayer;
            gBattlerPositions[1] = B_POSITION_PLAYER_LEFT;

            gBattlerControllerFuncs[0] = SetControllerToLinkOpponent;
            gBattlerPositions[0] = B_POSITION_OPPONENT_LEFT;

            gBattlersCount = 2;
        }
    }
    else if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_IS_MASTER)
        {
            gBattleMainFunc = BeginBattleIntro;

            gBattlerControllerFuncs[0] = SetControllerToPlayer;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

            gBattlerControllerFuncs[1] = SetControllerToLinkOpponent;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

            gBattlerControllerFuncs[2] = SetControllerToPlayer;
            gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;

            gBattlerControllerFuncs[3] = SetControllerToLinkOpponent;
            gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;

            gBattlersCount = MAX_BATTLERS_COUNT;
        }
        else
        {
            gBattlerControllerFuncs[1] = SetControllerToPlayer;
            gBattlerPositions[1] = B_POSITION_PLAYER_LEFT;

            gBattlerControllerFuncs[0] = SetControllerToLinkOpponent;
            gBattlerPositions[0] = B_POSITION_OPPONENT_LEFT;

            gBattlerControllerFuncs[3] = SetControllerToPlayer;
            gBattlerPositions[3] = B_POSITION_PLAYER_RIGHT;

            gBattlerControllerFuncs[2] = SetControllerToLinkOpponent;
            gBattlerPositions[2] = B_POSITION_OPPONENT_RIGHT;

            gBattlersCount = MAX_BATTLERS_COUNT;
        }
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_BATTLE_TOWER)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_IS_MASTER)
        {
            gBattleMainFunc = BeginBattleIntro;

            gBattlerControllerFuncs[0] = SetControllerToPlayer;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

            gBattlerControllerFuncs[1] = SetControllerToOpponent;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

            gBattlerControllerFuncs[2] = SetControllerToLinkPartner;
            gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;

            gBattlerControllerFuncs[3] = SetControllerToOpponent;
            gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;

            gBattlersCount = MAX_BATTLERS_COUNT;
        }
        else
        {
            gBattlerControllerFuncs[0] = SetControllerToLinkPartner;
            gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;

            gBattlerControllerFuncs[1] = SetControllerToLinkOpponent;
            gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;

            gBattlerControllerFuncs[2] = SetControllerToPlayer;
            gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;

            gBattlerControllerFuncs[3] = SetControllerToLinkOpponent;
            gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;

            gBattlersCount = MAX_BATTLERS_COUNT;
        }

        BufferBattlePartyCurrentOrderBySide(0, 0);
        BufferBattlePartyCurrentOrderBySide(1, 0);
        BufferBattlePartyCurrentOrderBySide(2, 1);
        BufferBattlePartyCurrentOrderBySide(3, 1);
        gBattlerPartyIndexes[0] = 0;
        gBattlerPartyIndexes[1] = 0;
        gBattlerPartyIndexes[2] = 3;
        gBattlerPartyIndexes[3] = 3;
    }
    else
    {
        multiplayerId = GetMultiplayerId();

        if (gBattleTypeFlags & BATTLE_TYPE_IS_MASTER)
            gBattleMainFunc = BeginBattleIntro;

        for (i = 0; i < MAX_BATTLERS_COUNT; i++)
        {
            switch (gLinkPlayers[i].id)
            {
            case 0:
            case 3:
                BufferBattlePartyCurrentOrderBySide(gLinkPlayers[i].id, 0);
                break;
            case 1:
            case 2:
                BufferBattlePartyCurrentOrderBySide(gLinkPlayers[i].id, 1);
                break;
            }

            if (i == multiplayerId)
            {
                gBattlerControllerFuncs[gLinkPlayers[i].id] = SetControllerToPlayer;
                switch (gLinkPlayers[i].id)
                {
                case 0:
                case 3:
                    gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_LEFT;
                    gBattlerPartyIndexes[gLinkPlayers[i].id] = 0;
                    break;
                case 1:
                case 2:
                    gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_RIGHT;
                    gBattlerPartyIndexes[gLinkPlayers[i].id] = 3;
                    break;
                }
            }
            else
            {
                if ((!(gLinkPlayers[i].id & 1) && !(gLinkPlayers[multiplayerId].id & 1))
                 || ((gLinkPlayers[i].id & 1) && (gLinkPlayers[multiplayerId].id & 1)))
                {
                    gBattlerControllerFuncs[gLinkPlayers[i].id] = SetControllerToLinkPartner;
                    switch (gLinkPlayers[i].id)
                    {
                    case 0:
                    case 3:
                        gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_LEFT;
                        gBattlerPartyIndexes[gLinkPlayers[i].id] = 0;
                        break;
                    case 1:
                    case 2:
                        gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_PLAYER_RIGHT;
                        gBattlerPartyIndexes[gLinkPlayers[i].id] = 3;
                        break;
                    }
                }
                else
                {
                    gBattlerControllerFuncs[gLinkPlayers[i].id] = SetControllerToLinkOpponent;
                    switch (gLinkPlayers[i].id)
                    {
                    case 0:
                    case 3:
                        gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_OPPONENT_LEFT;
                        gBattlerPartyIndexes[gLinkPlayers[i].id] = 0;
                        break;
                    case 1:
                    case 2:
                        gBattlerPositions[gLinkPlayers[i].id] = B_POSITION_OPPONENT_RIGHT;
                        gBattlerPartyIndexes[gLinkPlayers[i].id] = 3;
                        break;
                    }
                }
            }
        }

        gBattlersCount = MAX_BATTLERS_COUNT;
    }
}

static void SetBattlePartyIds(void)
{
    s32 i, j;

    if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
    {
        for (i = 0; i < gBattlersCount; i++)
        {
            for (j = 0; j < PARTY_SIZE; j++)
            {
                if (i < 2)
                {
                    if (GetBattlerSide(i) == B_SIDE_PLAYER)
                    {
                        if (GetMonData(&gPlayerParty[j], MON_DATA_HP) != 0
                         && GetMonData(&gPlayerParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
                         && GetMonData(&gPlayerParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
                         && !GetMonData(&gPlayerParty[j], MON_DATA_IS_EGG))
                        {
                            gBattlerPartyIndexes[i] = j;
                            break;
                        }
                    }
                    else
                    {
                        if (GetMonData(&gEnemyParty[j], MON_DATA_HP) != 0
                         && GetMonData(&gEnemyParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
                         && GetMonData(&gEnemyParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
                         && !GetMonData(&gEnemyParty[j], MON_DATA_IS_EGG))
                        {
                            gBattlerPartyIndexes[i] = j;
                            break;
                        }
                    }
                }
                else
                {
                    if (GetBattlerSide(i) == B_SIDE_PLAYER)
                    {
                        if (GetMonData(&gPlayerParty[j], MON_DATA_HP) != 0
                         && GetMonData(&gPlayerParty[j], MON_DATA_SPECIES) != SPECIES_NONE  // Probably a typo by Game Freak. The rest use SPECIES2.
                         && GetMonData(&gPlayerParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
                         && !GetMonData(&gPlayerParty[j], MON_DATA_IS_EGG)
                         && gBattlerPartyIndexes[i - 2] != j)
                        {
                            gBattlerPartyIndexes[i] = j;
                            break;
                        }
                    }
                    else
                    {
                        if (GetMonData(&gEnemyParty[j], MON_DATA_HP) != 0
                         && GetMonData(&gEnemyParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
                         && GetMonData(&gEnemyParty[j], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
                         && !GetMonData(&gEnemyParty[j], MON_DATA_IS_EGG)
                         && gBattlerPartyIndexes[i - 2] != j)
                        {
                            gBattlerPartyIndexes[i] = j;
                            break;
                        }
                    }
                }
            }
        }

        if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
            gBattlerPartyIndexes[1] = 0, gBattlerPartyIndexes[3] = 3;
    }
}

static void PrepareBufferDataTransfer(u32 battler, u8 bufferId, u8 *data, u16 size)
{
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        PrepareBufferDataTransferLink(battler, bufferId, size, data);
    }
    else
    {
        switch (bufferId)
        {
        case BUFFER_A:
            for (i = 0; i < size; data++, i++)
                gBattleBufferA[battler][i] = *data;
            break;
        case BUFFER_B:
            for (i = 0; i < size; data++, i++)
                gBattleBufferB[battler][i] = *data;
            break;
        }
    }
}

static void CreateTasksForSendRecvLinkBuffers(void)
{
    sLinkSendTaskId = CreateTask(Task_HandleSendLinkBuffersData, 0);
    gTasks[sLinkSendTaskId].data[11] = 0;
    gTasks[sLinkSendTaskId].data[12] = 0;
    gTasks[sLinkSendTaskId].data[13] = 0;
    gTasks[sLinkSendTaskId].data[14] = 0;
    gTasks[sLinkSendTaskId].data[15] = 0;

    sLinkReceiveTaskId = CreateTask(Task_HandleCopyReceivedLinkBuffersData, 0);
    gTasks[sLinkReceiveTaskId].data[12] = 0;
    gTasks[sLinkReceiveTaskId].data[13] = 0;
    gTasks[sLinkReceiveTaskId].data[14] = 0;
    gTasks[sLinkReceiveTaskId].data[15] = 0;
}

enum
{
    LINK_BUFF_BUFFER_ID,
    LINK_BUFF_ACTIVE_BATTLER,
    LINK_BUFF_ATTACKER,
    LINK_BUFF_TARGET,
    LINK_BUFF_SIZE_LO,
    LINK_BUFF_SIZE_HI,
    LINK_BUFF_ABSENT_BATTLER_FLAGS,
    LINK_BUFF_EFFECT_BATTLER,
    LINK_BUFF_DATA,
};

void PrepareBufferDataTransferLink(u32 battler, u8 bufferId, u16 size, u8 *data)
{
    s32 alignedSize;
    s32 i;

    alignedSize = size - size % 4 + 4;
    if (gTasks[sLinkSendTaskId].data[14] + alignedSize + LINK_BUFF_DATA + 1 > BATTLE_BUFFER_LINK_SIZE)
    {
        gTasks[sLinkSendTaskId].data[12] = gTasks[sLinkSendTaskId].data[14];
        gTasks[sLinkSendTaskId].data[14] = 0;
    }
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_BUFFER_ID] = bufferId;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_ACTIVE_BATTLER] = battler;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_ATTACKER] = gBattlerAttacker;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_TARGET] = gBattlerTarget;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_SIZE_LO] = alignedSize;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_SIZE_HI] = (alignedSize & 0x0000FF00) >> 8;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_ABSENT_BATTLER_FLAGS] = gAbsentBattlerFlags;
    gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_EFFECT_BATTLER] = gEffectBattler;

    for (i = 0; i < size; i++)
        gLinkBattleSendBuffer[gTasks[sLinkSendTaskId].data[14] + LINK_BUFF_DATA + i] = data[i];

    gTasks[sLinkSendTaskId].data[14] = gTasks[sLinkSendTaskId].data[14] + alignedSize + LINK_BUFF_DATA;
}

static void Task_HandleSendLinkBuffersData(u8 taskId)
{
    u16 numPlayers;
    u16 blockSize;

    switch (gTasks[taskId].data[11])
    {
    case 0:
        gTasks[taskId].data[10] = 100;
        gTasks[taskId].data[11]++;
        break;
    case 1:
        gTasks[taskId].data[10]--;
        if (gTasks[taskId].data[10] == 0)
            gTasks[taskId].data[11]++;
        break;
    case 2:
        if (gWirelessCommType)
        {
            gTasks[taskId].data[11]++;
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_BATTLE_TOWER)
                numPlayers = 2;
            else
                numPlayers = (gBattleTypeFlags & BATTLE_TYPE_MULTI) ? 4 : 2;

            if (GetLinkPlayerCount_2() >= numPlayers)
            {
                if (IsLinkMaster())
                {
                    CheckShouldAdvanceLinkState();
                    gTasks[taskId].data[11]++;
                }
                else
                {
                    gTasks[taskId].data[11]++;
                }
            }
        }
        break;
    case 3:
        if (gTasks[taskId].data[15] != gTasks[taskId].data[14])
        {
            if (gTasks[taskId].data[13] == 0)
            {
                if (gTasks[taskId].data[15] > gTasks[taskId].data[14]
                 && gTasks[taskId].data[15] == gTasks[taskId].data[12])
                {
                    gTasks[taskId].data[12] = 0;
                    gTasks[taskId].data[15] = 0;
                }
                blockSize = (gLinkBattleSendBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_LO] | (gLinkBattleSendBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_HI] << 8)) + LINK_BUFF_DATA;
                SendBlock(BitmaskAllOtherLinkPlayers(), &gLinkBattleSendBuffer[gTasks[taskId].data[15]], blockSize);
                gTasks[taskId].data[11]++;
            }
            else
            {
                gTasks[taskId].data[13]--;
                break;
            }
        }
        break;
    case 4:
        if (IsLinkTaskFinished())
        {
            blockSize = gLinkBattleSendBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_LO] | (gLinkBattleSendBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_HI] << 8);
            gTasks[taskId].data[13] = 1;
            gTasks[taskId].data[15] = gTasks[taskId].data[15] + blockSize + LINK_BUFF_DATA;
            gTasks[taskId].data[11] = 3;
        }
        break;
    case 5:
        if (--gTasks[taskId].data[13] == 0)
        {
            gTasks[taskId].data[13] = 1;
            gTasks[taskId].data[11] = 3;
        }
        break;
    }
}

void TryReceiveLinkBattleData(void)
{
    u8 i;
    s32 j;
    u8 *recvBuffer;

    if (gReceivedRemoteLinkPlayers && (gBattleTypeFlags & BATTLE_TYPE_LINK_IN_BATTLE))
    {
        DestroyTask_RfuIdle();
        for (i = 0; i < GetLinkPlayerCount(); i++)
        {
            if (GetBlockReceivedStatus() & gBitTable[i])
            {
                ResetBlockReceivedFlag(i);
                recvBuffer = (u8 *)gBlockRecvBuffer[i];
                {
                    u8 *dest, *src;
                    u16 dataSize = gBlockRecvBuffer[i][2];

                    if (gTasks[sLinkReceiveTaskId].data[14] + 9 + dataSize > 0x1000)
                    {
                        gTasks[sLinkReceiveTaskId].data[12] = gTasks[sLinkReceiveTaskId].data[14];
                        gTasks[sLinkReceiveTaskId].data[14] = 0;
                    }

                    dest = &gLinkBattleRecvBuffer[gTasks[sLinkReceiveTaskId].data[14]];
                    src = recvBuffer;

                    for (j = 0; j < dataSize + 8; j++)
                        dest[j] = src[j];

                    gTasks[sLinkReceiveTaskId].data[14] = gTasks[sLinkReceiveTaskId].data[14] + dataSize + 8;
                }
            }
        }
    }
}

static void Task_HandleCopyReceivedLinkBuffersData(u8 taskId)
{
    u16 blockSize;
    u8 battlerId;
    u8 var;

    if (gTasks[taskId].data[15] != gTasks[taskId].data[14])
    {
        if (gTasks[taskId].data[15] > gTasks[taskId].data[14]
         && gTasks[taskId].data[15] == gTasks[taskId].data[12])
        {
            gTasks[taskId].data[12] = 0;
            gTasks[taskId].data[15] = 0;
        }
        battlerId = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_ACTIVE_BATTLER];
        blockSize = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_LO] | (gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_SIZE_HI] << 8);

        switch (gLinkBattleRecvBuffer[gTasks[taskId].data[15] + 0])
        {
        case 0:
            if (gBattleControllerExecFlags & gBitTable[battlerId])
                return;

            memcpy(gBattleBufferA[battlerId], &gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_DATA], blockSize);
            MarkBattlerReceivedLinkData(battlerId);

            if (!(gBattleTypeFlags & BATTLE_TYPE_IS_MASTER))
            {
                gBattlerAttacker = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_ATTACKER];
                gBattlerTarget = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_TARGET];
                gAbsentBattlerFlags = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_ABSENT_BATTLER_FLAGS];
                gEffectBattler = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_EFFECT_BATTLER];
            }
            break;
        case 1:
            memcpy(gBattleBufferB[battlerId], &gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_DATA], blockSize);
            break;
        case 2:
            var = gLinkBattleRecvBuffer[gTasks[taskId].data[15] + LINK_BUFF_DATA];
            gBattleControllerExecFlags &= ~(gBitTable[battlerId] << (var * 4));
            break;
        }

        gTasks[taskId].data[15] = gTasks[taskId].data[15] + blockSize + LINK_BUFF_DATA;
    }
}

void BtlController_EmitGetMonData(u32 battler, u8 bufferId, u8 requestId, u8 monToCheck)
{
    sBattleBuffersTransferData[0] = CONTROLLER_GETMONDATA;
    sBattleBuffersTransferData[1] = requestId;
    sBattleBuffersTransferData[2] = monToCheck;
    sBattleBuffersTransferData[3] = 0;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

static void UNUSED BtlController_EmitGetRawMonData(u32 battler, u8 bufferId, u8 monId, u8 bytes)
{
    sBattleBuffersTransferData[0] = CONTROLLER_GETRAWMONDATA;
    sBattleBuffersTransferData[1] = monId;
    sBattleBuffersTransferData[2] = bytes;
    sBattleBuffersTransferData[3] = 0;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitSetMonData(u32 battler, u8 bufferId, u8 requestId, u8 monToCheck, u8 bytes, void *data)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_SETMONDATA;
    sBattleBuffersTransferData[1] = requestId;
    sBattleBuffersTransferData[2] = monToCheck;
    for (i = 0; i < bytes; i++)
        sBattleBuffersTransferData[3 + i] = *(u8 *)(data++);
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 3 + bytes);
}

static void UNUSED BtlController_EmitSetRawMonData(u32 battler, u8 bufferId, u8 monId, u8 bytes, void *data)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_SETRAWMONDATA;
    sBattleBuffersTransferData[1] = monId;
    sBattleBuffersTransferData[2] = bytes;
    for (i = 0; i < bytes; i++)
        sBattleBuffersTransferData[3 + i] = *(u8 *)(data++);
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, bytes + 3);
}

void BtlController_EmitLoadMonSprite(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_LOADMONSPRITE;
    sBattleBuffersTransferData[1] = CONTROLLER_LOADMONSPRITE;
    sBattleBuffersTransferData[2] = CONTROLLER_LOADMONSPRITE;
    sBattleBuffersTransferData[3] = CONTROLLER_LOADMONSPRITE;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitSwitchInAnim(u32 battler, u8 bufferId, u8 partyId, bool8 dontClearSubstituteBit)
{
    sBattleBuffersTransferData[0] = CONTROLLER_SWITCHINANIM;
    sBattleBuffersTransferData[1] = partyId;
    sBattleBuffersTransferData[2] = dontClearSubstituteBit;
    sBattleBuffersTransferData[3] = 5;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitReturnMonToBall(u32 battler, u8 bufferId, bool8 skipAnim)
{
    sBattleBuffersTransferData[0] = CONTROLLER_RETURNMONTOBALL;
    sBattleBuffersTransferData[1] = skipAnim;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 2);
}

void BtlController_EmitDrawTrainerPic(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_DRAWTRAINERPIC;
    sBattleBuffersTransferData[1] = CONTROLLER_DRAWTRAINERPIC;
    sBattleBuffersTransferData[2] = CONTROLLER_DRAWTRAINERPIC;
    sBattleBuffersTransferData[3] = CONTROLLER_DRAWTRAINERPIC;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitTrainerSlide(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_TRAINERSLIDE;
    sBattleBuffersTransferData[1] = CONTROLLER_TRAINERSLIDE;
    sBattleBuffersTransferData[2] = CONTROLLER_TRAINERSLIDE;
    sBattleBuffersTransferData[3] = CONTROLLER_TRAINERSLIDE;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitTrainerSlideBack(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_TRAINERSLIDEBACK;
    sBattleBuffersTransferData[1] = CONTROLLER_TRAINERSLIDEBACK;
    sBattleBuffersTransferData[2] = CONTROLLER_TRAINERSLIDEBACK;
    sBattleBuffersTransferData[3] = CONTROLLER_TRAINERSLIDEBACK;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitFaintAnimation(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_FAINTANIMATION;
    sBattleBuffersTransferData[1] = CONTROLLER_FAINTANIMATION;
    sBattleBuffersTransferData[2] = CONTROLLER_FAINTANIMATION;
    sBattleBuffersTransferData[3] = CONTROLLER_FAINTANIMATION;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

static void UNUSED BtlController_EmitPaletteFade(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_PALETTEFADE;
    sBattleBuffersTransferData[1] = CONTROLLER_PALETTEFADE;
    sBattleBuffersTransferData[2] = CONTROLLER_PALETTEFADE;
    sBattleBuffersTransferData[3] = CONTROLLER_PALETTEFADE;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

static void UNUSED BtlController_EmitSuccessBallThrowAnim(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_SUCCESSBALLTHROWANIM;
    sBattleBuffersTransferData[1] = CONTROLLER_SUCCESSBALLTHROWANIM;
    sBattleBuffersTransferData[2] = CONTROLLER_SUCCESSBALLTHROWANIM;
    sBattleBuffersTransferData[3] = CONTROLLER_SUCCESSBALLTHROWANIM;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitBallThrowAnim(u32 battler, u8 bufferId, u8 caseId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_BALLTHROWANIM;
    sBattleBuffersTransferData[1] = caseId;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 2);
}

static void UNUSED BtlController_EmitPause(u32 battler, u8 bufferId, u8 toWait, void *data)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_PAUSE;
    sBattleBuffersTransferData[1] = toWait;
    for (i = 0; i < toWait * 3; i++)
        sBattleBuffersTransferData[2 + i] = *(u8 *)(data++);
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, toWait * 3 + 2);
}

void BtlController_EmitMoveAnimation(u32 battler, u8 bufferId, u16 move, u8 turnOfMove, u16 movePower, s32 dmg, u8 friendship, struct DisableStruct *disableStructPtr, u8 multihit)
{
    sBattleBuffersTransferData[0] = CONTROLLER_MOVEANIMATION;
    sBattleBuffersTransferData[1] = move;
    sBattleBuffersTransferData[2] = (move & 0xFF00) >> 8;
    sBattleBuffersTransferData[3] = turnOfMove;
    sBattleBuffersTransferData[4] = movePower;
    sBattleBuffersTransferData[5] = (movePower & 0xFF00) >> 8;
    sBattleBuffersTransferData[6] = dmg;
    sBattleBuffersTransferData[7] = (dmg & 0x0000FF00) >> 8;
    sBattleBuffersTransferData[8] = (dmg & 0x00FF0000) >> 16;
    sBattleBuffersTransferData[9] = (dmg & 0xFF000000) >> 24;
    sBattleBuffersTransferData[10] = friendship;
    sBattleBuffersTransferData[11] = multihit;
    if (WEATHER_HAS_EFFECT2)
    {
        sBattleBuffersTransferData[12] = gBattleWeather;
        sBattleBuffersTransferData[13] = (gBattleWeather & 0xFF00) >> 8;
    }
    else
    {
        sBattleBuffersTransferData[12] = 0;
        sBattleBuffersTransferData[13] = 0;
    }
    sBattleBuffersTransferData[14] = 0;
    sBattleBuffersTransferData[15] = 0;
    memcpy(&sBattleBuffersTransferData[16], disableStructPtr, sizeof(struct DisableStruct));
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 16 + sizeof(struct DisableStruct));
}

void BtlController_EmitPrintString(u32 battler, u8 bufferId, u16 stringID)
{
    s32 i;
    struct BattleMsgData *stringInfo;

    sBattleBuffersTransferData[0] = CONTROLLER_PRINTSTRING;
    sBattleBuffersTransferData[1] = gBattleOutcome;
    sBattleBuffersTransferData[2] = stringID;
    sBattleBuffersTransferData[3] = (stringID & 0xFF00) >> 8;

    stringInfo = (struct BattleMsgData *)(&sBattleBuffersTransferData[4]);
    stringInfo->currentMove = gCurrentMove;
    stringInfo->originallyUsedMove = gChosenMove;
    stringInfo->lastItem = gLastUsedItem;
    stringInfo->lastAbility = gLastUsedAbility;
    stringInfo->scrActive = gBattleScripting.battler;
    stringInfo->bakScriptPartyIdx = gBattleStruct->scriptPartyIdx;
    stringInfo->hpScale = gBattleStruct->hpScale;
    stringInfo->itemEffectBattler = gPotentialItemEffectBattler;
    stringInfo->moveType = GetMoveType(gCurrentMove);

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
        stringInfo->abilities[i] = gBattleMons[i].ability;
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; i++)
    {
        stringInfo->textBuffs[0][i] = gBattleTextBuff1[i];
        stringInfo->textBuffs[1][i] = gBattleTextBuff2[i];
        stringInfo->textBuffs[2][i] = gBattleTextBuff3[i];
    }
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, sizeof(struct BattleMsgData) + 4);
}

void BtlController_EmitPrintSelectionString(u32 battler, u8 bufferId, u16 stringID)
{
    s32 i;
    struct BattleMsgData *stringInfo;

    sBattleBuffersTransferData[0] = CONTROLLER_PRINTSTRINGPLAYERONLY;
    sBattleBuffersTransferData[1] = CONTROLLER_PRINTSTRINGPLAYERONLY;
    sBattleBuffersTransferData[2] = stringID;
    sBattleBuffersTransferData[3] = (stringID & 0xFF00) >> 8;

    stringInfo = (struct BattleMsgData *)(&sBattleBuffersTransferData[4]);
    stringInfo->currentMove = gCurrentMove;
    stringInfo->originallyUsedMove = gChosenMove;
    stringInfo->lastItem = gLastUsedItem;
    stringInfo->lastAbility = gLastUsedAbility;
    stringInfo->scrActive = gBattleScripting.battler;
    stringInfo->bakScriptPartyIdx = gBattleStruct->scriptPartyIdx;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
        stringInfo->abilities[i] = gBattleMons[i].ability;
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; i++)
    {
        stringInfo->textBuffs[0][i] = gBattleTextBuff1[i];
        stringInfo->textBuffs[1][i] = gBattleTextBuff2[i];
        stringInfo->textBuffs[2][i] = gBattleTextBuff3[i];
    }
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, sizeof(struct BattleMsgData) + 4);
}

// itemId only relevant for B_ACTION_USE_ITEM
void BtlController_EmitChooseAction(u32 battler, u8 bufferId, u8 action, u16 itemId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_CHOOSEACTION;
    sBattleBuffersTransferData[1] = action;
    sBattleBuffersTransferData[2] = itemId;
    sBattleBuffersTransferData[3] = (itemId & 0xFF00) >> 8;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

// Only used by the forfeit prompt in the Battle Frontier
// For other Yes/No boxes in battle, see Cmd_yesnobox
void BtlController_EmitYesNoBox(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_YESNOBOX;
    sBattleBuffersTransferData[1] = CONTROLLER_YESNOBOX;
    sBattleBuffersTransferData[2] = CONTROLLER_YESNOBOX;
    sBattleBuffersTransferData[3] = CONTROLLER_YESNOBOX;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitChooseMove(u32 battler, u8 bufferId, bool8 isDoubleBattle, bool8 NoPpNumber, struct ChooseMoveStruct *movePpData)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_CHOOSEMOVE;
    sBattleBuffersTransferData[1] = isDoubleBattle;
    sBattleBuffersTransferData[2] = NoPpNumber;
    sBattleBuffersTransferData[3] = 0;
    for (i = 0; i < sizeof(*movePpData); i++)
        sBattleBuffersTransferData[4 + i] = *((u8 *)(movePpData) + i);
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, sizeof(*movePpData) + 4);
}

void BtlController_EmitChooseItem(u32 battler, u8 bufferId, u8 *battlePartyOrder)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_OPENBAG;
    for (i = 0; i < PARTY_SIZE / 2; i++)
        sBattleBuffersTransferData[1 + i] = battlePartyOrder[i];
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitChoosePokemon(u32 battler, u8 bufferId, u8 caseId, u8 slotId, u8 abilityId, u8 *data)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_CHOOSEPOKEMON;
    sBattleBuffersTransferData[1] = caseId;
    sBattleBuffersTransferData[2] = slotId;
    sBattleBuffersTransferData[3] = abilityId;
    for (i = 0; i < 3; i++)
        sBattleBuffersTransferData[4 + i] = data[i];
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 8);  // Only 7 bytes were written.
}

static void UNUSED BtlController_EmitCmd23(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_23;
    sBattleBuffersTransferData[1] = CONTROLLER_23;
    sBattleBuffersTransferData[2] = CONTROLLER_23;
    sBattleBuffersTransferData[3] = CONTROLLER_23;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

// why is the argument u16 if it's being cast to s16 anyway?
void BtlController_EmitHealthBarUpdate(u32 battler, u8 bufferId, u16 hpValue)
{
    sBattleBuffersTransferData[0] = CONTROLLER_HEALTHBARUPDATE;
    sBattleBuffersTransferData[1] = 0;
    sBattleBuffersTransferData[2] = (s16)hpValue;
    sBattleBuffersTransferData[3] = ((s16)hpValue & 0xFF00) >> 8;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

// why is the argument u16 if it's being cast to s16 anyway?
void BtlController_EmitExpUpdate(u32 battler, u8 bufferId, u8 partyId, u16 expPoints)
{
    sBattleBuffersTransferData[0] = CONTROLLER_EXPUPDATE;
    sBattleBuffersTransferData[1] = partyId;
    sBattleBuffersTransferData[2] = (s16)expPoints;
    sBattleBuffersTransferData[3] = ((s16)expPoints & 0xFF00) >> 8;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitStatusIconUpdate(u32 battler, u8 bufferId, u32 status1, u32 status2)
{
    sBattleBuffersTransferData[0] = CONTROLLER_STATUSICONUPDATE;
    sBattleBuffersTransferData[1] = status1;
    sBattleBuffersTransferData[2] = (status1 & 0x0000FF00) >> 8;
    sBattleBuffersTransferData[3] = (status1 & 0x00FF0000) >> 16;
    sBattleBuffersTransferData[4] = (status1 & 0xFF000000) >> 24;
    sBattleBuffersTransferData[5] = status2;
    sBattleBuffersTransferData[6] = (status2 & 0x0000FF00) >> 8;
    sBattleBuffersTransferData[7] = (status2 & 0x00FF0000) >> 16;
    sBattleBuffersTransferData[8] = (status2 & 0xFF000000) >> 24;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 9);
}

void BtlController_EmitStatusAnimation(u32 battler, u8 bufferId, bool8 status2, u32 status)
{
    sBattleBuffersTransferData[0] = CONTROLLER_STATUSANIMATION;
    sBattleBuffersTransferData[1] = status2;
    sBattleBuffersTransferData[2] = status;
    sBattleBuffersTransferData[3] = (status & 0x0000FF00) >> 8;
    sBattleBuffersTransferData[4] = (status & 0x00FF0000) >> 16;
    sBattleBuffersTransferData[5] = (status & 0xFF000000) >> 24;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 6);
}

static void UNUSED BtlController_EmitStatusXor(u32 battler, u8 bufferId, u8 b)
{
    sBattleBuffersTransferData[0] = CONTROLLER_STATUSXOR;
    sBattleBuffersTransferData[1] = b;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 2);
}

void BtlController_EmitDataTransfer(u32 battler, u8 bufferId, u16 size, void *data)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_DATATRANSFER;
    sBattleBuffersTransferData[1] = CONTROLLER_DATATRANSFER;
    sBattleBuffersTransferData[2] = size;
    sBattleBuffersTransferData[3] = (size & 0xFF00) >> 8;
    for (i = 0; i < size; i++)
        sBattleBuffersTransferData[4 + i] = *(u8 *)(data++);
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, size + 4);
}

static void UNUSED BtlController_EmitDMA3Transfer(u32 battler, u8 bufferId, void *dst, u16 size, void *data)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_DMA3TRANSFER;
    sBattleBuffersTransferData[1] = (u32)(dst);
    sBattleBuffersTransferData[2] = ((u32)(dst) & 0x0000FF00) >> 8;
    sBattleBuffersTransferData[3] = ((u32)(dst) & 0x00FF0000) >> 16;
    sBattleBuffersTransferData[4] = ((u32)(dst) & 0xFF000000) >> 24;
    sBattleBuffersTransferData[5] = size;
    sBattleBuffersTransferData[6] = (size & 0xFF00) >> 8;
    for (i = 0; i < size; i++)
        sBattleBuffersTransferData[7 + i] = *(u8 *)(data++);
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, size + 7);
}

static void UNUSED BtlController_EmitPlayBGM(u32 battler, u8 bufferId, u16 songId, void *data)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_PLAYBGM;
    sBattleBuffersTransferData[1] = songId;
    sBattleBuffersTransferData[2] = (songId & 0xFF00) >> 8;

    // Nonsense loop using songId as a size
    // Would go out of bounds for any song id after SE_RG_BAG_POCKET (253)
    for (i = 0; i < songId; i++)
        sBattleBuffersTransferData[3 + i] = *(u8 *)(data++);
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, songId + 3);
}

static void UNUSED BtlController_EmitCmd32(u32 battler, u8 bufferId, u16 size, void *data)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_32;
    sBattleBuffersTransferData[1] = size;
    sBattleBuffersTransferData[2] = (size & 0xFF00) >> 8;
    for (i = 0; i < size; i++)
        sBattleBuffersTransferData[3 + i] = *(u8 *)(data++);
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, size + 3);
}

void BtlController_EmitTwoReturnValues(u32 battler, u8 bufferId, u8 ret8, u16 ret16)
{
    sBattleBuffersTransferData[0] = CONTROLLER_TWORETURNVALUES;
    sBattleBuffersTransferData[1] = ret8;
    sBattleBuffersTransferData[2] = ret16;
    sBattleBuffersTransferData[3] = (ret16 & 0xFF00) >> 8;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitChosenMonReturnValue(u32 battler, u8 bufferId, u8 partyId, u8 *battlePartyOrder)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_CHOSENMONRETURNVALUE;
    sBattleBuffersTransferData[1] = partyId;
    for (i = 0; i < (int)ARRAY_COUNT(gBattlePartyCurrentOrder); i++)
        sBattleBuffersTransferData[2 + i] = battlePartyOrder[i];
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 5);
}

void BtlController_EmitOneReturnValue(u32 battler, u8 bufferId, u16 ret)
{
    sBattleBuffersTransferData[0] = CONTROLLER_ONERETURNVALUE;
    sBattleBuffersTransferData[1] = ret;
    sBattleBuffersTransferData[2] = (ret & 0xFF00) >> 8;
    sBattleBuffersTransferData[3] = 0;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitOneReturnValue_Duplicate(u32 battler, u8 bufferId, u16 ret)
{
    sBattleBuffersTransferData[0] = CONTROLLER_ONERETURNVALUE_DUPLICATE;
    sBattleBuffersTransferData[1] = ret;
    sBattleBuffersTransferData[2] = (ret & 0xFF00) >> 8;
    sBattleBuffersTransferData[3] = 0;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitHitAnimation(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_HITANIMATION;
    sBattleBuffersTransferData[1] = CONTROLLER_HITANIMATION;
    sBattleBuffersTransferData[2] = CONTROLLER_HITANIMATION;
    sBattleBuffersTransferData[3] = CONTROLLER_HITANIMATION;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitCantSwitch(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_CANTSWITCH;
    sBattleBuffersTransferData[1] = CONTROLLER_CANTSWITCH;
    sBattleBuffersTransferData[2] = CONTROLLER_CANTSWITCH;
    sBattleBuffersTransferData[3] = CONTROLLER_CANTSWITCH;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitPlaySE(u32 battler, u8 bufferId, u16 songId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_PLAYSE;
    sBattleBuffersTransferData[1] = songId;
    sBattleBuffersTransferData[2] = (songId & 0xFF00) >> 8;
    sBattleBuffersTransferData[3] = 0;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitPlayFanfareOrBGM(u32 battler, u8 bufferId, u16 songId, bool8 playBGM)
{
    sBattleBuffersTransferData[0] = CONTROLLER_PLAYFANFAREORBGM;
    sBattleBuffersTransferData[1] = songId;
    sBattleBuffersTransferData[2] = (songId & 0xFF00) >> 8;
    sBattleBuffersTransferData[3] = playBGM;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitFaintingCry(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_FAINTINGCRY;
    sBattleBuffersTransferData[1] = CONTROLLER_FAINTINGCRY;
    sBattleBuffersTransferData[2] = CONTROLLER_FAINTINGCRY;
    sBattleBuffersTransferData[3] = CONTROLLER_FAINTINGCRY;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitIntroSlide(u32 battler, u8 bufferId, u8 terrainId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_INTROSLIDE;
    sBattleBuffersTransferData[1] = terrainId;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 2);
}

void BtlController_EmitIntroTrainerBallThrow(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_INTROTRAINERBALLTHROW;
    sBattleBuffersTransferData[1] = CONTROLLER_INTROTRAINERBALLTHROW;
    sBattleBuffersTransferData[2] = CONTROLLER_INTROTRAINERBALLTHROW;
    sBattleBuffersTransferData[3] = CONTROLLER_INTROTRAINERBALLTHROW;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitDrawPartyStatusSummary(u32 battler, u8 bufferId, struct HpAndStatus* hpAndStatus, u8 flags)
{
    s32 i;

    sBattleBuffersTransferData[0] = CONTROLLER_DRAWPARTYSTATUSSUMMARY;
    sBattleBuffersTransferData[1] = flags & ~PARTY_SUMM_SKIP_DRAW_DELAY; // If true, skip player side
    sBattleBuffersTransferData[2] = (flags & PARTY_SUMM_SKIP_DRAW_DELAY) >> 7; // If true, skip delay after drawing. True during intro
    sBattleBuffersTransferData[3] = CONTROLLER_DRAWPARTYSTATUSSUMMARY;
    for (i = 0; i < (s32)(sizeof(struct HpAndStatus) * PARTY_SIZE); i++)
        sBattleBuffersTransferData[4 + i] = *(i + (u8 *)(hpAndStatus));
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, sizeof(struct HpAndStatus) * PARTY_SIZE + 4);
}

void BtlController_EmitHidePartyStatusSummary(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_HIDEPARTYSTATUSSUMMARY;
    sBattleBuffersTransferData[1] = CONTROLLER_HIDEPARTYSTATUSSUMMARY;
    sBattleBuffersTransferData[2] = CONTROLLER_HIDEPARTYSTATUSSUMMARY;
    sBattleBuffersTransferData[3] = CONTROLLER_HIDEPARTYSTATUSSUMMARY;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitEndBounceEffect(u32 battler, u8 bufferId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_ENDBOUNCE;
    sBattleBuffersTransferData[1] = CONTROLLER_ENDBOUNCE;
    sBattleBuffersTransferData[2] = CONTROLLER_ENDBOUNCE;
    sBattleBuffersTransferData[3] = CONTROLLER_ENDBOUNCE;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitSpriteInvisibility(u32 battler, u8 bufferId, bool8 isInvisible)
{
    sBattleBuffersTransferData[0] = CONTROLLER_SPRITEINVISIBILITY;
    sBattleBuffersTransferData[1] = isInvisible;
    sBattleBuffersTransferData[2] = CONTROLLER_SPRITEINVISIBILITY;
    sBattleBuffersTransferData[3] = CONTROLLER_SPRITEINVISIBILITY;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

void BtlController_EmitBattleAnimation(u32 battler, u8 bufferId, u8 animationId, u16 argument)
{
    sBattleBuffersTransferData[0] = CONTROLLER_BATTLEANIMATION;
    sBattleBuffersTransferData[1] = animationId;
    sBattleBuffersTransferData[2] = argument;
    sBattleBuffersTransferData[3] = (argument & 0xFF00) >> 8;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 4);
}

// mode is a LINK_STANDBY_* constant
void BtlController_EmitLinkStandbyMsg(u32 battler, u8 bufferId, u8 mode, bool32 record)
{
    bool8 record_ = record;
    sBattleBuffersTransferData[0] = CONTROLLER_LINKSTANDBYMSG;
    sBattleBuffersTransferData[1] = mode;

    if (record_)
        sBattleBuffersTransferData[3] = sBattleBuffersTransferData[2] = RecordedBattle_BufferNewBattlerData(&sBattleBuffersTransferData[4]);
    else
        sBattleBuffersTransferData[3] = sBattleBuffersTransferData[2] = 0;

    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, sBattleBuffersTransferData[2] + 4);
}

void BtlController_EmitResetActionMoveSelection(u32 battler, u8 bufferId, u8 caseId)
{
    sBattleBuffersTransferData[0] = CONTROLLER_RESETACTIONMOVESELECTION;
    sBattleBuffersTransferData[1] = caseId;
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, 2);
}

void BtlController_EmitEndLinkBattle(u32 battler, u8 bufferId, u8 battleOutcome)
{
    sBattleBuffersTransferData[0] = CONTROLLER_ENDLINKBATTLE;
    sBattleBuffersTransferData[1] = battleOutcome;
    sBattleBuffersTransferData[2] = gSaveBlock2Ptr->frontier.disableRecordBattle;
    sBattleBuffersTransferData[3] = gSaveBlock2Ptr->frontier.disableRecordBattle;
    sBattleBuffersTransferData[5] = sBattleBuffersTransferData[4] = RecordedBattle_BufferNewBattlerData(&sBattleBuffersTransferData[6]);
    PrepareBufferDataTransfer(battler, bufferId, sBattleBuffersTransferData, sBattleBuffersTransferData[4] + 6);
}


void BtlController_ExecCompleted(u32 battler)
{
    gBattlerControllerEndFuncs[battler](battler);
}

void BtlController_Empty(u32 battler)
{
    BtlController_ExecCompleted(battler);
}

static u32 GetBattlerMonData(u32 battler, struct Pokemon *party, u8 monId, u8 *dst)
{
    struct BattlePokemon battleMon;
    struct MovePpInfo moveData;
    u8 nickname[POKEMON_NAME_BUFFER_SIZE];
    u8 *src;
    s16 data16;
    u32 data32;
    s32 size = 0;

    switch (gBattleBufferA[battler][1])
    {
    case REQUEST_ALL_BATTLE:
        battleMon.species = GetMonData(&party[monId], MON_DATA_SPECIES);
        battleMon.item = GetMonData(&party[monId], MON_DATA_HELD_ITEM);
        for (size = 0; size < MAX_MON_MOVES; size++)
        {
            battleMon.moves[size] = GetMonData(&party[monId], MON_DATA_MOVE1 + size);
            battleMon.pp[size] = GetMonData(&party[monId], MON_DATA_PP1 + size);
        }
        battleMon.ppBonuses = GetMonData(&party[monId], MON_DATA_PP_BONUSES);
        battleMon.friendship = GetMonData(&party[monId], MON_DATA_FRIENDSHIP);
        battleMon.experience = GetMonData(&party[monId], MON_DATA_EXP);
        battleMon.hpIV = GetMonData(&party[monId], MON_DATA_HP_IV);
        battleMon.attackIV = GetMonData(&party[monId], MON_DATA_ATK_IV);
        battleMon.defenseIV = GetMonData(&party[monId], MON_DATA_DEF_IV);
        battleMon.speedIV = GetMonData(&party[monId], MON_DATA_SPEED_IV);
        battleMon.spAttackIV = GetMonData(&party[monId], MON_DATA_SPATK_IV);
        battleMon.spDefenseIV = GetMonData(&party[monId], MON_DATA_SPDEF_IV);
        battleMon.personality = GetMonData(&party[monId], MON_DATA_PERSONALITY);
        battleMon.status1 = GetMonData(&party[monId], MON_DATA_STATUS);
        battleMon.level = GetMonData(&party[monId], MON_DATA_LEVEL);
        battleMon.hp = GetMonData(&party[monId], MON_DATA_HP);
        battleMon.maxHP = GetMonData(&party[monId], MON_DATA_MAX_HP);
        battleMon.attack = GetMonData(&party[monId], MON_DATA_ATK);
        battleMon.defense = GetMonData(&party[monId], MON_DATA_DEF);
        battleMon.speed = GetMonData(&party[monId], MON_DATA_SPEED);
        battleMon.spAttack = GetMonData(&party[monId], MON_DATA_SPATK);
        battleMon.spDefense = GetMonData(&party[monId], MON_DATA_SPDEF);
        battleMon.isEgg = GetMonData(&party[monId], MON_DATA_IS_EGG);
        battleMon.abilityNum = GetMonData(&party[monId], MON_DATA_ABILITY_NUM);
        battleMon.otId = GetMonData(&party[monId], MON_DATA_OT_ID);
        GetMonData(&party[monId], MON_DATA_NICKNAME, nickname);
        StringCopy_Nickname(battleMon.nickname, nickname);
        GetMonData(&party[monId], MON_DATA_OT_NAME, battleMon.otName);
        src = (u8 *)&battleMon;
        for (size = 0; size < sizeof(battleMon); size++)
            dst[size] = src[size];
        #if TESTING
        if (gTestRunnerEnabled)
        {
            u32 side = GetBattlerSide(battler);
            u32 partyIndex = gBattlerPartyIndexes[battler];
            if (TestRunner_Battle_GetForcedAbility(side, partyIndex))
                gBattleMons[battler].ability = TestRunner_Battle_GetForcedAbility(side, partyIndex);
        }
        #endif
        break;
    case REQUEST_SPECIES_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_SPECIES);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_HELDITEM_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_HELD_ITEM);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_MOVES_PP_BATTLE:
        for (size = 0; size < MAX_MON_MOVES; size++)
        {
            moveData.moves[size] = GetMonData(&party[monId], MON_DATA_MOVE1 + size);
            moveData.pp[size] = GetMonData(&party[monId], MON_DATA_PP1 + size);
        }
        moveData.ppBonuses = GetMonData(&party[monId], MON_DATA_PP_BONUSES);
        src = (u8 *)(&moveData);
        for (size = 0; size < sizeof(moveData); size++)
            dst[size] = src[size];
        break;
    case REQUEST_MOVE1_BATTLE:
    case REQUEST_MOVE2_BATTLE:
    case REQUEST_MOVE3_BATTLE:
    case REQUEST_MOVE4_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_MOVE1 + gBattleBufferA[battler][1] - REQUEST_MOVE1_BATTLE);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_PP_DATA_BATTLE:
        for (size = 0; size < MAX_MON_MOVES; size++)
            dst[size] = GetMonData(&party[monId], MON_DATA_PP1 + size);
        dst[size] = GetMonData(&party[monId], MON_DATA_PP_BONUSES);
        size++;
        break;
    case REQUEST_PPMOVE1_BATTLE:
    case REQUEST_PPMOVE2_BATTLE:
    case REQUEST_PPMOVE3_BATTLE:
    case REQUEST_PPMOVE4_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_PP1 + gBattleBufferA[battler][1] - REQUEST_PPMOVE1_BATTLE);
        size = 1;
        break;
    case REQUEST_OTID_BATTLE:
        data32 = GetMonData(&party[monId], MON_DATA_OT_ID);
        dst[0] = (data32 & 0x000000FF);
        dst[1] = (data32 & 0x0000FF00) >> 8;
        dst[2] = (data32 & 0x00FF0000) >> 16;
        size = 3;
        break;
    case REQUEST_EXP_BATTLE:
        data32 = GetMonData(&party[monId], MON_DATA_EXP);
        dst[0] = (data32 & 0x000000FF);
        dst[1] = (data32 & 0x0000FF00) >> 8;
        dst[2] = (data32 & 0x00FF0000) >> 16;
        size = 3;
        break;
    case REQUEST_HP_EV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_HP_EV);
        size = 1;
        break;
    case REQUEST_ATK_EV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_ATK_EV);
        size = 1;
        break;
    case REQUEST_DEF_EV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_DEF_EV);
        size = 1;
        break;
    case REQUEST_SPEED_EV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_SPEED_EV);
        size = 1;
        break;
    case REQUEST_SPATK_EV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_SPATK_EV);
        size = 1;
        break;
    case REQUEST_SPDEF_EV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_SPDEF_EV);
        size = 1;
        break;
    case REQUEST_FRIENDSHIP_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_FRIENDSHIP);
        size = 1;
        break;
    case REQUEST_POKERUS_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_POKERUS);
        size = 1;
        break;
    case REQUEST_MET_LOCATION_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_MET_LOCATION);
        size = 1;
        break;
    case REQUEST_MET_LEVEL_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_MET_LEVEL);
        size = 1;
        break;
    case REQUEST_MET_GAME_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_MET_GAME);
        size = 1;
        break;
    case REQUEST_POKEBALL_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_POKEBALL);
        size = 1;
        break;
    case REQUEST_ALL_IVS_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_HP_IV);
        dst[1] = GetMonData(&party[monId], MON_DATA_ATK_IV);
        dst[2] = GetMonData(&party[monId], MON_DATA_DEF_IV);
        dst[3] = GetMonData(&party[monId], MON_DATA_SPEED_IV);
        dst[4] = GetMonData(&party[monId], MON_DATA_SPATK_IV);
        dst[5] = GetMonData(&party[monId], MON_DATA_SPDEF_IV);
        size = 6;
        break;
    case REQUEST_HP_IV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_HP_IV);
        size = 1;
        break;
    case REQUEST_ATK_IV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_ATK_IV);
        size = 1;
        break;
    case REQUEST_DEF_IV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_DEF_IV);
        size = 1;
        break;
    case REQUEST_SPEED_IV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_SPEED_IV);
        size = 1;
        break;
    case REQUEST_SPATK_IV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_SPATK_IV);
        size = 1;
        break;
    case REQUEST_SPDEF_IV_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_SPDEF_IV);
        size = 1;
        break;
    case REQUEST_PERSONALITY_BATTLE:
        data32 = GetMonData(&party[monId], MON_DATA_PERSONALITY);
        dst[0] = (data32 & 0x000000FF);
        dst[1] = (data32 & 0x0000FF00) >> 8;
        dst[2] = (data32 & 0x00FF0000) >> 16;
        dst[3] = (data32 & 0xFF000000) >> 24;
        size = 4;
        break;
    case REQUEST_CHECKSUM_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_CHECKSUM);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_STATUS_BATTLE:
        data32 = GetMonData(&party[monId], MON_DATA_STATUS);
        dst[0] = (data32 & 0x000000FF);
        dst[1] = (data32 & 0x0000FF00) >> 8;
        dst[2] = (data32 & 0x00FF0000) >> 16;
        dst[3] = (data32 & 0xFF000000) >> 24;
        size = 4;
        break;
    case REQUEST_LEVEL_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_LEVEL);
        size = 1;
        break;
    case REQUEST_HP_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_HP);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_MAX_HP_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_MAX_HP);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_ATK_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_ATK);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_DEF_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_DEF);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_SPEED_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_SPEED);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_SPATK_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_SPATK);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_SPDEF_BATTLE:
        data16 = GetMonData(&party[monId], MON_DATA_SPDEF);
        dst[0] = data16;
        dst[1] = data16 >> 8;
        size = 2;
        break;
    case REQUEST_COOL_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_COOL);
        size = 1;
        break;
    case REQUEST_BEAUTY_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_BEAUTY);
        size = 1;
        break;
    case REQUEST_CUTE_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_CUTE);
        size = 1;
        break;
    case REQUEST_SMART_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_SMART);
        size = 1;
        break;
    case REQUEST_TOUGH_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_TOUGH);
        size = 1;
        break;
    case REQUEST_SHEEN_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_SHEEN);
        size = 1;
        break;
    case REQUEST_COOL_RIBBON_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_COOL_RIBBON);
        size = 1;
        break;
    case REQUEST_BEAUTY_RIBBON_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_BEAUTY_RIBBON);
        size = 1;
        break;
    case REQUEST_CUTE_RIBBON_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_CUTE_RIBBON);
        size = 1;
        break;
    case REQUEST_SMART_RIBBON_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_SMART_RIBBON);
        size = 1;
        break;
    case REQUEST_TOUGH_RIBBON_BATTLE:
        dst[0] = GetMonData(&party[monId], MON_DATA_TOUGH_RIBBON);
        size = 1;
        break;
    }

    return size;
}

void BtlController_HandleGetMonData(u32 battler)
{
    u8 monData[sizeof(struct Pokemon) * 2 + 56]; // this allows to get full data of two Pokémon, trying to get more will result in overwriting data
    u32 size = 0;
    u8 monToCheck;
    s32 i;

    if (gBattleBufferA[battler][2] == 0)
    {
        size += GetBattlerMonData(battler, GetBattlerParty(battler), gBattlerPartyIndexes[battler], monData);
    }
    else
    {
        monToCheck = gBattleBufferA[battler][2];
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (monToCheck & 1)
                size += GetBattlerMonData(battler, GetBattlerParty(battler), i, monData + size);
            monToCheck >>= 1;
        }
    }
    BtlController_EmitDataTransfer(battler, BUFFER_B, size, monData);
    BtlController_ExecCompleted(battler);
}

void BtlController_HandleGetRawMonData(u32 battler)
{
    struct BattlePokemon battleMon;
    struct Pokemon *party = GetBattlerParty(battler);
    u8 *src = (u8 *)&party[gBattlerPartyIndexes[battler]] + gBattleBufferA[battler][1];
    u8 *dst = (u8 *)&battleMon + gBattleBufferA[battler][1];
    u8 i;

    for (i = 0; i < gBattleBufferA[battler][2]; i++)
        dst[i] = src[i];

    BtlController_EmitDataTransfer(battler, BUFFER_B, gBattleBufferA[battler][2], dst);
    BtlController_ExecCompleted(battler);
}

static void SetBattlerMonData(u32 battler, struct Pokemon *party, u8 monId)
{
    struct BattlePokemon *battlePokemon = (struct BattlePokemon *)&gBattleBufferA[battler][3];
    struct MovePpInfo *moveData = (struct MovePpInfo *)&gBattleBufferA[battler][3];
    s32 i;

    switch (gBattleBufferA[battler][1])
    {
    case REQUEST_ALL_BATTLE:
        {
            u8 iv;

            SetMonData(&party[monId], MON_DATA_SPECIES, &battlePokemon->species);
            SetMonData(&party[monId], MON_DATA_HELD_ITEM, &battlePokemon->item);
            for (i = 0; i < MAX_MON_MOVES; i++)
            {
                SetMonData(&party[monId], MON_DATA_MOVE1 + i, &battlePokemon->moves[i]);
                SetMonData(&party[monId], MON_DATA_PP1 + i, &battlePokemon->pp[i]);
            }
            SetMonData(&party[monId], MON_DATA_PP_BONUSES, &battlePokemon->ppBonuses);
            SetMonData(&party[monId], MON_DATA_FRIENDSHIP, &battlePokemon->friendship);
            SetMonData(&party[monId], MON_DATA_EXP, &battlePokemon->experience);
            iv = battlePokemon->hpIV;
            SetMonData(&party[monId], MON_DATA_HP_IV, &iv);
            iv = battlePokemon->attackIV;
            SetMonData(&party[monId], MON_DATA_ATK_IV, &iv);
            iv = battlePokemon->defenseIV;
            SetMonData(&party[monId], MON_DATA_DEF_IV, &iv);
            iv = battlePokemon->speedIV;
            SetMonData(&party[monId], MON_DATA_SPEED_IV, &iv);
            iv = battlePokemon->spAttackIV;
            SetMonData(&party[monId], MON_DATA_SPATK_IV, &iv);
            iv = battlePokemon->spDefenseIV;
            SetMonData(&party[monId], MON_DATA_SPDEF_IV, &iv);
            SetMonData(&party[monId], MON_DATA_PERSONALITY, &battlePokemon->personality);
            SetMonData(&party[monId], MON_DATA_STATUS, &battlePokemon->status1);
            SetMonData(&party[monId], MON_DATA_LEVEL, &battlePokemon->level);
            SetMonData(&party[monId], MON_DATA_HP, &battlePokemon->hp);
            SetMonData(&party[monId], MON_DATA_MAX_HP, &battlePokemon->maxHP);
            SetMonData(&party[monId], MON_DATA_ATK, &battlePokemon->attack);
            SetMonData(&party[monId], MON_DATA_DEF, &battlePokemon->defense);
            SetMonData(&party[monId], MON_DATA_SPEED, &battlePokemon->speed);
            SetMonData(&party[monId], MON_DATA_SPATK, &battlePokemon->spAttack);
            SetMonData(&party[monId], MON_DATA_SPDEF, &battlePokemon->spDefense);
        }
        break;
    case REQUEST_SPECIES_BATTLE:
        SetMonData(&party[monId], MON_DATA_SPECIES, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_HELDITEM_BATTLE:
        SetMonData(&party[monId], MON_DATA_HELD_ITEM, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_MOVES_PP_BATTLE:
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            SetMonData(&party[monId], MON_DATA_MOVE1 + i, &moveData->moves[i]);
            SetMonData(&party[monId], MON_DATA_PP1 + i, &moveData->pp[i]);
        }
        SetMonData(&party[monId], MON_DATA_PP_BONUSES, &moveData->ppBonuses);
        break;
    case REQUEST_MOVE1_BATTLE:
    case REQUEST_MOVE2_BATTLE:
    case REQUEST_MOVE3_BATTLE:
    case REQUEST_MOVE4_BATTLE:
        SetMonData(&party[monId], MON_DATA_MOVE1 + gBattleBufferA[battler][1] - REQUEST_MOVE1_BATTLE, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_PP_DATA_BATTLE:
        SetMonData(&party[monId], MON_DATA_PP1, &gBattleBufferA[battler][3]);
        SetMonData(&party[monId], MON_DATA_PP2, &gBattleBufferA[battler][4]);
        SetMonData(&party[monId], MON_DATA_PP3, &gBattleBufferA[battler][5]);
        SetMonData(&party[monId], MON_DATA_PP4, &gBattleBufferA[battler][6]);
        SetMonData(&party[monId], MON_DATA_PP_BONUSES, &gBattleBufferA[battler][7]);
        break;
    case REQUEST_PPMOVE1_BATTLE:
    case REQUEST_PPMOVE2_BATTLE:
    case REQUEST_PPMOVE3_BATTLE:
    case REQUEST_PPMOVE4_BATTLE:
        SetMonData(&party[monId], MON_DATA_PP1 + gBattleBufferA[battler][1] - REQUEST_PPMOVE1_BATTLE, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_OTID_BATTLE:
        SetMonData(&party[monId], MON_DATA_OT_ID, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_EXP_BATTLE:
        SetMonData(&party[monId], MON_DATA_EXP, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_HP_EV_BATTLE:
        SetMonData(&party[monId], MON_DATA_HP_EV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_ATK_EV_BATTLE:
        SetMonData(&party[monId], MON_DATA_ATK_EV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_DEF_EV_BATTLE:
        SetMonData(&party[monId], MON_DATA_DEF_EV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SPEED_EV_BATTLE:
        SetMonData(&party[monId], MON_DATA_SPEED_EV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SPATK_EV_BATTLE:
        SetMonData(&party[monId], MON_DATA_SPATK_EV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SPDEF_EV_BATTLE:
        SetMonData(&party[monId], MON_DATA_SPDEF_EV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_FRIENDSHIP_BATTLE:
        SetMonData(&party[monId], MON_DATA_FRIENDSHIP, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_POKERUS_BATTLE:
        SetMonData(&party[monId], MON_DATA_POKERUS, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_MET_LOCATION_BATTLE:
        SetMonData(&party[monId], MON_DATA_MET_LOCATION, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_MET_LEVEL_BATTLE:
        SetMonData(&party[monId], MON_DATA_MET_LEVEL, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_MET_GAME_BATTLE:
        SetMonData(&party[monId], MON_DATA_MET_GAME, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_POKEBALL_BATTLE:
        SetMonData(&party[monId], MON_DATA_POKEBALL, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_ALL_IVS_BATTLE:
        SetMonData(&party[monId], MON_DATA_HP_IV, &gBattleBufferA[battler][3]);
        SetMonData(&party[monId], MON_DATA_ATK_IV, &gBattleBufferA[battler][4]);
        SetMonData(&party[monId], MON_DATA_DEF_IV, &gBattleBufferA[battler][5]);
        SetMonData(&party[monId], MON_DATA_SPEED_IV, &gBattleBufferA[battler][6]);
        SetMonData(&party[monId], MON_DATA_SPATK_IV, &gBattleBufferA[battler][7]);
        SetMonData(&party[monId], MON_DATA_SPDEF_IV, &gBattleBufferA[battler][8]);
        break;
    case REQUEST_HP_IV_BATTLE:
        SetMonData(&party[monId], MON_DATA_HP_IV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_ATK_IV_BATTLE:
        SetMonData(&party[monId], MON_DATA_ATK_IV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_DEF_IV_BATTLE:
        SetMonData(&party[monId], MON_DATA_DEF_IV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SPEED_IV_BATTLE:
        SetMonData(&party[monId], MON_DATA_SPEED_IV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SPATK_IV_BATTLE:
        SetMonData(&party[monId], MON_DATA_SPATK_IV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SPDEF_IV_BATTLE:
        SetMonData(&party[monId], MON_DATA_SPDEF_IV, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_PERSONALITY_BATTLE:
        SetMonData(&party[monId], MON_DATA_PERSONALITY, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_CHECKSUM_BATTLE:
        SetMonData(&party[monId], MON_DATA_CHECKSUM, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_STATUS_BATTLE:
        SetMonData(&party[monId], MON_DATA_STATUS, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_LEVEL_BATTLE:
        SetMonData(&party[monId], MON_DATA_LEVEL, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_HP_BATTLE:
        SetMonData(&party[monId], MON_DATA_HP, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_MAX_HP_BATTLE:
        SetMonData(&party[monId], MON_DATA_MAX_HP, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_ATK_BATTLE:
        SetMonData(&party[monId], MON_DATA_ATK, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_DEF_BATTLE:
        SetMonData(&party[monId], MON_DATA_DEF, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SPEED_BATTLE:
        SetMonData(&party[monId], MON_DATA_SPEED, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SPATK_BATTLE:
        SetMonData(&party[monId], MON_DATA_SPATK, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SPDEF_BATTLE:
        SetMonData(&party[monId], MON_DATA_SPDEF, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_COOL_BATTLE:
        SetMonData(&party[monId], MON_DATA_COOL, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_BEAUTY_BATTLE:
        SetMonData(&party[monId], MON_DATA_BEAUTY, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_CUTE_BATTLE:
        SetMonData(&party[monId], MON_DATA_CUTE, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SMART_BATTLE:
        SetMonData(&party[monId], MON_DATA_SMART, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_TOUGH_BATTLE:
        SetMonData(&party[monId], MON_DATA_TOUGH, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SHEEN_BATTLE:
        SetMonData(&party[monId], MON_DATA_SHEEN, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_COOL_RIBBON_BATTLE:
        SetMonData(&party[monId], MON_DATA_COOL_RIBBON, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_BEAUTY_RIBBON_BATTLE:
        SetMonData(&party[monId], MON_DATA_BEAUTY_RIBBON, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_CUTE_RIBBON_BATTLE:
        SetMonData(&party[monId], MON_DATA_CUTE_RIBBON, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_SMART_RIBBON_BATTLE:
        SetMonData(&party[monId], MON_DATA_SMART_RIBBON, &gBattleBufferA[battler][3]);
        break;
    case REQUEST_TOUGH_RIBBON_BATTLE:
        SetMonData(&party[monId], MON_DATA_TOUGH_RIBBON, &gBattleBufferA[battler][3]);
        break;
    }

    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        HandleLowHpMusicChange(&party[gBattlerPartyIndexes[battler]], battler);
}

void BtlController_HandleSetMonData(u32 battler)
{
    struct Pokemon *party = GetBattlerParty(battler);
    u8 monToCheck;
    u8 i;

    if (gBattleBufferA[battler][2] == 0)
    {
        SetBattlerMonData(battler, party,gBattlerPartyIndexes[battler]);
    }
    else
    {
        monToCheck = gBattleBufferA[battler][2];
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (monToCheck & 1)
                SetBattlerMonData(battler, party, i);
            monToCheck >>= 1;
        }
    }
    BtlController_ExecCompleted(battler);
}

void BtlController_HandleSetRawMonData(u32 battler)
{
    struct Pokemon *party = GetBattlerParty(battler);
    u8 *dst = (u8 *)&party[gBattlerPartyIndexes[battler]] + gBattleBufferA[battler][1];
    u8 i;

    for (i = 0; i < gBattleBufferA[battler][2]; i++)
        dst[i] = gBattleBufferA[battler][3 + i];

    BtlController_ExecCompleted(battler);
}

void BtlController_HandleLoadMonSprite(u32 battler, void (*controllerCallback)(u32 battler))
{
    struct Pokemon *party = GetBattlerParty(battler);
    u16 species = GetMonData(&party[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);

    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        BattleLoadPlayerMonSpriteGfx(&party[gBattlerPartyIndexes[battler]], battler);
    else
        BattleLoadOpponentMonSpriteGfx(&party[gBattlerPartyIndexes[battler]], battler);
    SetMultiuseSpriteTemplateToPokemon(species, GetBattlerPosition(battler));

    gBattlerSpriteIds[battler] = CreateSprite(&gMultiuseSpriteTemplate,
                                               GetBattlerSpriteCoord(battler, BATTLER_COORD_X_2),
                                               GetBattlerSpriteDefault_Y(battler),
                                               GetBattlerSpriteSubpriority(battler));

    gSprites[gBattlerSpriteIds[battler]].x2 = -DISPLAY_WIDTH;
    gSprites[gBattlerSpriteIds[battler]].data[0] = battler;
    gSprites[gBattlerSpriteIds[battler]].data[2] = species;
    gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = battler;
    StartSpriteAnim(&gSprites[gBattlerSpriteIds[battler]], gBattleMonForms[battler]);

    if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
        SetBattlerShadowSpriteCallback(battler, species);

    gBattlerControllerFuncs[battler] = controllerCallback;
}

void StartSendOutAnim(u32 battler, bool32 dontClearSubstituteBit)
{
    struct Pokemon *party = GetBattlerParty(battler);
    u32 battlerSide = GetBattlerSide(battler);
    u16 species;

    ClearTemporarySpeciesSpriteData(battler, dontClearSubstituteBit);
    gBattlerPartyIndexes[battler] = gBattleBufferA[battler][1];
    species = GetMonData(&party[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);
    gBattleControllerData[battler] = CreateInvisibleSpriteWithCallback(SpriteCB_WaitForBattlerBallReleaseAnim);
    if (battlerSide == B_SIDE_OPPONENT)
        BattleLoadOpponentMonSpriteGfx(&party[gBattlerPartyIndexes[battler]], battler);
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

    gSprites[gBattleControllerData[battler]].data[0] = DoPokeballSendOutAnimation(battler, 0, battlerSide == B_SIDE_PLAYER ? POKEBALL_PLAYER_SENDOUT : POKEBALL_OPPONENT_SENDOUT);
}

void BtlController_HandleSwitchInAnim(u32 battler, void (*controllerCallback)(u32 battler))
{
    u32 battlerSide = GetBattlerSide(battler);
    if (battlerSide == B_SIDE_PLAYER)
        ClearTemporarySpeciesSpriteData(battler, gBattleBufferA[battler][2]);
    gBattlerPartyIndexes[battler] = gBattleBufferA[battler][1];
    if (battlerSide == B_SIDE_PLAYER)
        BattleLoadPlayerMonSpriteGfx(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
    StartSendOutAnim(battler, gBattleBufferA[battler][2]);
    gBattlerControllerFuncs[battler] = controllerCallback;
}

static void FreeMonSprite(u32 battler)
{
    FreeSpriteOamMatrix(&gSprites[gBattlerSpriteIds[battler]]);
    DestroySprite(&gSprites[gBattlerSpriteIds[battler]]);
    if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
        HideBattlerShadowSprite(battler);
    SetHealthboxSpriteInvisible(gHealthboxSpriteIds[battler]);
}

static void FreeMonSpriteAfterSwitchOutAnim(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive)
    {
        FreeMonSprite(battler);
        BtlController_ExecCompleted(battler);
    }
}

static void DoSwitchOutAnimation(u32 battler)
{
    switch (gBattleSpritesDataPtr->healthBoxesData[battler].animationState)
    {
    case 0:
        if (gBattleSpritesDataPtr->battlerData[battler].behindSubstitute)
            InitAndLaunchSpecialAnimation(battler, battler, battler, B_ANIM_SUBSTITUTE_TO_MON);

        gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 1;
        break;
    case 1:
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive)
        {
            gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 0;
            InitAndLaunchSpecialAnimation(battler, battler, battler, GetBattlerSide(battler) == B_SIDE_PLAYER ? B_ANIM_SWITCH_OUT_PLAYER_MON : B_ANIM_SWITCH_OUT_OPPONENT_MON);
            gBattlerControllerFuncs[battler] = FreeMonSpriteAfterSwitchOutAnim;
        }
        break;
    }
}

void BtlController_HandleReturnMonToBall(u32 battler)
{
    if (gBattleBufferA[battler][1] == 0)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 0;
        gBattlerControllerFuncs[battler] = DoSwitchOutAnimation;
    }
    else
    {
        FreeMonSprite(battler);
        BtlController_ExecCompleted(battler);
    }
}

static void CompleteOnBattlerSpriteCallbackDummy(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
        BtlController_ExecCompleted(battler);
}

#define sSpeedX data[0]

// In emerald it's possible to have a tag battle in the battle frontier facilities with AI
// which use the front sprite for both the player and the partner as opposed to any other battles (including the one with Steven)
// that use an animated back pic.
void BtlController_HandleDrawTrainerPic(u32 battler, u32 trainerPicId, s16 xPos, s16 yPos, s32 subpriority, bool32 isFrontPic)
{
    if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
    {
        DecompressTrainerFrontPic(trainerPicId, battler);
        SetMultiuseSpriteTemplateToTrainerBack(trainerPicId, GetBattlerPosition(battler));
        gBattlerSpriteIds[battler] = CreateSprite(&gMultiuseSpriteTemplate, xPos, yPos, subpriority);

        gSprites[gBattlerSpriteIds[battler]].x2 = -DISPLAY_WIDTH;
        gSprites[gBattlerSpriteIds[battler]].sSpeedX = 2;
        gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = IndexOfSpritePaletteTag(gTrainerFrontPicPaletteTable[trainerPicId].tag);
        gSprites[gBattlerSpriteIds[battler]].oam.affineParam = trainerPicId;
        gSprites[gBattlerSpriteIds[battler]].callback = SpriteCB_TrainerSlideIn;
    }
    else
    {
        // Use front pic table for any tag battles unless your partner is Steven.
        if (isFrontPic)
        {
            DecompressTrainerFrontPic(trainerPicId, battler);
            SetMultiuseSpriteTemplateToTrainerFront(trainerPicId, GetBattlerPosition(battler));
            gBattlerSpriteIds[battler] = CreateSprite(&gMultiuseSpriteTemplate, xPos, yPos, subpriority);
    
            gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = IndexOfSpritePaletteTag(gTrainerFrontPicPaletteTable[trainerPicId].tag);
            gSprites[gBattlerSpriteIds[battler]].x2 = DISPLAY_WIDTH;
            gSprites[gBattlerSpriteIds[battler]].y2 = 48;
            gSprites[gBattlerSpriteIds[battler]].sSpeedX = -2;
            gSprites[gBattlerSpriteIds[battler]].callback = SpriteCB_TrainerSlideIn;
            gSprites[gBattlerSpriteIds[battler]].oam.affineMode = ST_OAM_AFFINE_OFF;
            gSprites[gBattlerSpriteIds[battler]].hFlip = 1;
        }
        else
        {
            DecompressTrainerBackPic(trainerPicId, battler);
            SetMultiuseSpriteTemplateToTrainerBack(trainerPicId, GetBattlerPosition(battler));
            gBattlerSpriteIds[battler] = CreateSprite(&gMultiuseSpriteTemplate, xPos, yPos, subpriority);
    
            gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = battler;
            gSprites[gBattlerSpriteIds[battler]].x2 = DISPLAY_WIDTH;
            gSprites[gBattlerSpriteIds[battler]].sSpeedX = -2;
            gSprites[gBattlerSpriteIds[battler]].callback = SpriteCB_TrainerSlideIn;
        }
    }
    gBattlerControllerFuncs[battler] = CompleteOnBattlerSpriteCallbackDummy;
}

static void CompleteOnBankSpriteCallbackDummy2(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
        BtlController_ExecCompleted(battler);
}

void BtlController_HandleTrainerSlide(u32 battler, u32 trainerPicId)
{
    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
    {
        DecompressTrainerBackPic(trainerPicId, battler);
        SetMultiuseSpriteTemplateToTrainerBack(trainerPicId, GetBattlerPosition(battler));
        gBattlerSpriteIds[battler] = CreateSprite(&gMultiuseSpriteTemplate, 80, (8 - gTrainerBackPicCoords[trainerPicId].size) * 4 + 80, 30);
    
        gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = battler;
        gSprites[gBattlerSpriteIds[battler]].x2 = -96;
        gSprites[gBattlerSpriteIds[battler]].sSpeedX = 2;
    }
    else
    {
        DecompressTrainerFrontPic(trainerPicId, battler);
        SetMultiuseSpriteTemplateToTrainerBack(trainerPicId, GetBattlerPosition(battler));
        gBattlerSpriteIds[battler] = CreateSprite(&gMultiuseSpriteTemplate, 176, (8 - gTrainerFrontPicCoords[trainerPicId].size) * 4 + 40, 30);
    
        gSprites[gBattlerSpriteIds[battler]].x2 = 96;
        gSprites[gBattlerSpriteIds[battler]].x += 32;
        gSprites[gBattlerSpriteIds[battler]].sSpeedX = -2;
        gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = IndexOfSpritePaletteTag(gTrainerFrontPicPaletteTable[trainerPicId].tag);
        gSprites[gBattlerSpriteIds[battler]].oam.affineParam = trainerPicId;
    }
    gSprites[gBattlerSpriteIds[battler]].callback = SpriteCB_TrainerSlideIn;

    gBattlerControllerFuncs[battler] = CompleteOnBankSpriteCallbackDummy2;
}

#undef sSpeedX

static void FreeTrainerSpriteAfterSlide(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
    {
        if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
            FreeTrainerFrontPicPalette(gSprites[gBattlerSpriteIds[battler]].oam.affineParam);
        FreeSpriteOamMatrix(&gSprites[gBattlerSpriteIds[battler]]);
        DestroySprite(&gSprites[gBattlerSpriteIds[battler]]);
        BtlController_ExecCompleted(battler);
    }
}

void BtlController_HandleTrainerSlideBack(u32 battler, s16 data0, bool32 doAnim)
{
    u32 battlerSide = GetBattlerSide(battler);

    SetSpritePrimaryCoordsFromSecondaryCoords(&gSprites[gBattlerSpriteIds[battler]]);
    gSprites[gBattlerSpriteIds[battler]].data[0] = data0;
    gSprites[gBattlerSpriteIds[battler]].data[2] = battlerSide == B_SIDE_PLAYER ? -40 : 280;
    gSprites[gBattlerSpriteIds[battler]].data[4] = gSprites[gBattlerSpriteIds[battler]].y;
    gSprites[gBattlerSpriteIds[battler]].callback = StartAnimLinearTranslation;
    StoreSpriteCallbackInData6(&gSprites[gBattlerSpriteIds[battler]], SpriteCallbackDummy);
    if (doAnim)
        StartSpriteAnim(&gSprites[gBattlerSpriteIds[battler]], 1);
    gBattlerControllerFuncs[battler] = FreeTrainerSpriteAfterSlide;
}

#define sSpeedX data[1]
#define sSpeedY data[2]

static void FreeMonSpriteAfterFaintAnim(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].y + gSprites[gBattlerSpriteIds[battler]].y2 > DISPLAY_HEIGHT)
    {
        FreeOamMatrix(gSprites[gBattlerSpriteIds[battler]].oam.matrixNum);
        DestroySprite(&gSprites[gBattlerSpriteIds[battler]]);
        SetHealthboxSpriteInvisible(gHealthboxSpriteIds[battler]);
        BtlController_ExecCompleted(battler);
    }
}

static void HideHealthboxAfterMonFaint(u32 battler)
{
    if (!gSprites[gBattlerSpriteIds[battler]].inUse)
    {
        SetHealthboxSpriteInvisible(gHealthboxSpriteIds[battler]);
        BtlController_ExecCompleted(battler);
    }
}

void BtlController_HandleFaintAnimation(u32 battler)
{
    if (gBattleSpritesDataPtr->healthBoxesData[battler].animationState == 0)
    {
        if (gBattleSpritesDataPtr->battlerData[battler].behindSubstitute)
            InitAndLaunchSpecialAnimation(battler, battler, battler, B_ANIM_SUBSTITUTE_TO_MON);
        gBattleSpritesDataPtr->healthBoxesData[battler].animationState++;
    }
    else
    {
        if (gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive)
            return;

        gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 0;
        if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        {
            HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
            PlaySE12WithPanning(SE_FAINT, SOUND_PAN_ATTACKER);
            gSprites[gBattlerSpriteIds[battler]].sSpeedX = 0;
            gSprites[gBattlerSpriteIds[battler]].sSpeedY = 5;
            gSprites[gBattlerSpriteIds[battler]].callback = SpriteCB_FaintSlideAnim;
            gBattlerControllerFuncs[battler] = FreeMonSpriteAfterFaintAnim;
        }
        else
        {
            PlaySE12WithPanning(SE_FAINT, SOUND_PAN_TARGET);
            gSprites[gBattlerSpriteIds[battler]].callback = SpriteCB_FaintOpponentMon;
            gBattlerControllerFuncs[battler] = HideHealthboxAfterMonFaint;
        }
    }
}

#undef sSpeedX
#undef sSpeedY

static void CompleteOnSpecialAnimDone(u32 battler)
{
    if (!gDoingBattleAnim || !gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive)
        BtlController_ExecCompleted(battler);
}

void BtlController_HandleBallThrowAnim(u32 battler, enum BallThrowCaseID caseID, enum AnimationSpecial anim)
{
    gBattleSpritesDataPtr->animationData->ballThrowCaseId = caseID;
    gDoingBattleAnim = TRUE;
    InitAndLaunchSpecialAnimation(battler, battler, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), anim);
    gBattlerControllerFuncs[battler] = CompleteOnSpecialAnimDone;
}

static void Controller_DoMoveAnimation(u32 battler)
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
            BtlController_ExecCompleted(battler);
        }
        break;
    }
}

void BtlController_HandleMoveAnimation(u32 battler, bool32 updateBattleTV)
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
        gBattleSpritesDataPtr->healthBoxesData[battler].animationState = 0;
        gBattlerControllerFuncs[battler] = Controller_DoMoveAnimation;
        if (updateBattleTV)
            BattleTv_SetDataBasedOnMove(move, gWeatherMoveAnim, gAnimDisableStructPtr);
    }
}

static void CompleteOnInactiveTextPrinter(u32 battler)
{
    if (!IsTextPrinterActive(B_WIN_MSG))
        BtlController_ExecCompleted(battler);
}

void BtlController_HandlePrintString(u32 battler, bool32 updateBattleTV, bool32 updateArenaPoints)
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
            BtlController_ExecCompleted(battler);
            return;
        }
    }
    BattlePutTextOnWindow(gDisplayedStringBattle, B_WIN_MSG);
    gBattlerControllerFuncs[battler] = CompleteOnInactiveTextPrinter;
    if (updateBattleTV)
        BattleTv_SetDataBasedOnString(*stringId);
    if (updateArenaPoints)
        BattleArena_DeductSkillPoints(battler, *stringId);
}

void BtlController_TerminatorNop(u32 UNUSED battler)
{
}
