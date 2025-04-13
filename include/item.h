#ifndef GUARD_ITEM_H
#define GUARD_ITEM_H

#include "constants/item.h"
#include "constants/items.h"
#include "constants/pokeball.h"
#include "constants/tms_hms.h"

typedef void (*ItemUseFunc)(u8);

struct ItemInfo
{
    ItemUseFunc fieldUseFunc;
    ItemUseFunc battleUseFunc;
    const u8 *description;
    const u8 *effect;
    const u32 *iconPic;
    const u32 *iconPalette;
    u16 price;
    u16 secondaryId;
    u8 name[ITEM_NAME_LENGTH];
    u8 holdEffect;
    u8 holdEffectParam;
    u8 importance;
    u8 pocket;
    u8 type;
    u8 battleUsage;
};

struct BagPocket
{
    struct ItemSlot *itemSlots;
    u8 capacity;
};

extern const struct ItemInfo gItemInfo[];
extern struct BagPocket gBagPockets[];

void ApplyNewEncryptionKeyToBagItems(u32 newKey);
void ApplyNewEncryptionKeyToBagItems_(u32 newKey);
void SetBagItemsPointers(void);
u8 *CopyItemName(u16 itemId, u8 *dst);
u8 *CopyItemNameHandlePlural(u16 itemId, u8 *dst, u32 quantity);
void GetBerryCountString(u8 *dst, const u8 *berryName, u32 quantity);
bool8 IsBagPocketNonEmpty(u8 pocket);
bool8 CheckBagHasItem(u16 itemId, u16 count);
bool8 HasAtLeastOneBerry(void);
bool8 CheckBagHasSpace(u16 itemId, u16 count);
bool8 AddBagItem(u16 itemId, u16 count);
bool8 RemoveBagItem(u16 itemId, u16 count);
u8 GetPocketByItemId(u16 itemId);
void ClearItemSlots(struct ItemSlot *itemSlots, u8 itemCount);
u8 CountUsedPCItemSlots(void);
bool8 CheckPCHasItem(u16 itemId, u16 count);
bool8 AddPCItem(u16 itemId, u16 count);
void RemovePCItem(u8 index, u16 count);
void CompactPCItems(void);
void SwapRegisteredBike(void);
u16 BagGetItemIdByPocketPosition(u8 pocketId, u16 pocketPos);
u16 BagGetQuantityByPocketPosition(u8 pocketId, u16 pocketPos);
void CompactItemsInBagPocket(struct BagPocket *bagPocket);
void SortBerriesOrTMHMs(struct BagPocket *bagPocket);
void MoveItemSlotInList(struct ItemSlot* itemSlots_, u32 from, u32 to_);
void ClearBag(void);
u16 CountTotalItemQuantityInBag(u16 itemId);
bool8 AddPyramidBagItem(u16 itemId, u16 count);
bool8 RemovePyramidBagItem(u16 itemId, u16 count);

const u8 *Item_GetName(enum Item itemId);
u32 Item_GetPrice(enum Item itemId);
u32 Item_GetHoldEffect(enum Item itemId);
u32 Item_GetHoldEffectParam(enum Item itemId);
const u8 *Item_GetDescription(enum Item itemId);
u32 Item_GetImportance(enum Item itemId);
u32 Item_GetPocket(enum Item itemId);
u32 Item_GetType(enum Item itemId);
ItemUseFunc Item_GetFieldFunc(enum Item itemId);
u32 Item_GetBattleUsage(enum Item itemId);
ItemUseFunc Item_GetBattleFunc(enum Item itemId);
u32 Item_GetSecondaryId(enum Item itemId);
const u32 *Item_GetIconPic(u16 itemId);
const u32 *Item_GetIconPalette(u16 itemId);
const u8 *Item_GetEffect(u32 itemId);
enum Ball ItemIdToBallId(u16 itemId);
u16 ItemIdToBattleMoveId(u16 itemId);
u8 ItemIdToBerryType(u16 itemId);

/* Expands to:
 * enum
 * {
 *   ITEM_TM_FOCUS_PUNCH,
 *   ...
 *   ITEM_HM_CUT,
 *   ...
 * }; */
#define ENUM_TM(id) CAT(ITEM_TM_, id),
#define ENUM_HM(id) CAT(ITEM_HM_, id),
enum
{
    ENUM_TM_START_ = ITEM_TM01 - 1,
    FOREACH_TM(ENUM_TM)

    ENUM_HM_START_ = ITEM_HM01 - 1,
    FOREACH_HM(ENUM_HM)
};
#undef ENUM_TM
#undef ENUM_HM

#endif // GUARD_ITEM_H
