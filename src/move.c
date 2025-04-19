#include "global.h"
#include "battle.h"
#include "battle_anims_scripts.h"
#include "item.h"
#include "move.h"
#include "constants/battle_move_effects.h"
#include "constants/contest.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/types.h"


#include "data/moves_info.h"

bool32 IsHMMove(enum Move move)
{
    enum Item hm;
    for (hm = ITEM_HM01; hm < ITEM_HM01 + NUM_HIDDEN_MACHINES; hm++)
    {
        if (ItemIdToBattleMoveId(hm) == move)
            return TRUE;
    }
    return FALSE;
}
