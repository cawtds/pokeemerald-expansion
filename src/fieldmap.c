#include "global.h"
#include "battle_pyramid.h"
#include "bg.h"
#include "fieldmap.h"
#include "fldeff.h"
#include "fldeff_misc.h"
#include "frontier_util.h"
#include "menu.h"
#include "mirage_tower.h"
#include "overworld.h"
#include "palette.h"
#include "pokenav.h"
#include "script.h"
#include "secret_base.h"
#include "trainer_hill.h"
#include "tv.h"
#include "constants/rgb.h"
#include "constants/metatile_behaviors.h"
#include "wild_encounter.h"

struct ConnectionFlags
{
    u8 south:1;
    u8 north:1;
    u8 west:1;
    u8 east:1;
};

EWRAM_DATA u16 ALIGNED(4) sBackupMapData[MAX_MAP_DATA_SIZE] = {0};
EWRAM_DATA struct MapHeader gMapHeader = {0};
EWRAM_DATA struct Camera gCamera = {0};
EWRAM_DATA static struct ConnectionFlags sMapConnectionFlags = {0};

COMMON_DATA struct BackupMapLayout gBackupMapLayout = {0};

static const struct ConnectionFlags sDummyConnectionFlags = {0};

static void InitMapLayoutData(struct MapHeader *mapHeader);
static void InitBackupMapLayoutData(const u16 *map, u16 width, u16 height);
static void FillSouthConnection(struct MapHeader const *mapHeader, struct MapHeader const *connectedMapHeader, s32 offset);
static void FillNorthConnection(struct MapHeader const *mapHeader, struct MapHeader const *connectedMapHeader, s32 offset);
static void FillWestConnection(struct MapHeader const *mapHeader, struct MapHeader const *connectedMapHeader, s32 offset);
static void FillEastConnection(struct MapHeader const *mapHeader, struct MapHeader const *connectedMapHeader, s32 offset);
static void InitBackupMapLayoutConnections(struct MapHeader *mapHeader);
static void LoadSavedMapView(void);
static bool8 SkipCopyingMetatileFromSavedMap(u16 *mapBlock, u16 mapWidth, u8 yMode);
static const struct MapConnection *GetIncomingConnection(u8 direction, int x, int y);
static bool8 IsPosInIncomingConnectingMap(u8 direction, int x, int y, const struct MapConnection *connection);
static bool8 IsCoordInIncomingConnectingMap(int coord, int srcMax, int destMax, int offset);

static inline u16 GetBorderBlockAt(int x, int y)
{
    int i = (x + 1) & 1;
    i += ((y + 1) & 1) * 2;
    return gMapHeader.mapLayout->border[i] | MAPGRID_COLLISION_MASK;
}

#define AreCoordsWithinMapGridBounds(x, y) (x >= 0 && x < gBackupMapLayout.width && y >= 0 && y < gBackupMapLayout.height)

#define GetMapGridBlockAt(x, y) (AreCoordsWithinMapGridBounds(x, y) ? gBackupMapLayout.map[x + gBackupMapLayout.width * y] : GetBorderBlockAt(x, y))

// Masks/shifts for metatile attributes
// This is the format of the data stored in each data/tilesets/*/*/metatile_attributes.bin file
static const u32 sMetatileAttrMasks[METATILE_ATTRIBUTE_COUNT] = {
    [METATILE_ATTRIBUTE_BEHAVIOR]       = 0x000001ff, // Bits 0-8
    [METATILE_ATTRIBUTE_TERRAIN]        = 0x00003e00, // Bits 9-13
    [METATILE_ATTRIBUTE_2]              = 0x0003c000, // Bits 14-17
    [METATILE_ATTRIBUTE_3]              = 0x00fc0000, // Bits 18-23
    [METATILE_ATTRIBUTE_ENCOUNTER_TYPE] = 0x07000000, // Bits 24-26
    [METATILE_ATTRIBUTE_5]              = 0x18000000, // Bits 27-28
    [METATILE_ATTRIBUTE_LAYER_TYPE]     = 0x60000000, // Bits 29-30
    [METATILE_ATTRIBUTE_7]              = 0x80000000  // Bit  31
};

static const u8 sMetatileAttrShifts[METATILE_ATTRIBUTE_COUNT] = {
    [METATILE_ATTRIBUTE_BEHAVIOR]       = 0,
    [METATILE_ATTRIBUTE_TERRAIN]        = 9,
    [METATILE_ATTRIBUTE_2]              = 14,
    [METATILE_ATTRIBUTE_3]              = 18,
    [METATILE_ATTRIBUTE_ENCOUNTER_TYPE] = 24,
    [METATILE_ATTRIBUTE_5]              = 27,
    [METATILE_ATTRIBUTE_LAYER_TYPE]     = 29,
    [METATILE_ATTRIBUTE_7]              = 31
};

static const u32 sMetatileAttrMasksEmerald[METATILE_ATTRIBUTE_COUNT] = {
    
    [METATILE_ATTRIBUTE_BEHAVIOR]       = METATILE_ATTR_BEHAVIOR_MASK,
    [METATILE_ATTRIBUTE_TERRAIN]        = 0xFFFFFFFF,
    [METATILE_ATTRIBUTE_2]              = 0xFFFFFFFF,
    [METATILE_ATTRIBUTE_3]              = 0xFFFFFFFF,
    [METATILE_ATTRIBUTE_ENCOUNTER_TYPE] = 0xFFFFFFFF,
    [METATILE_ATTRIBUTE_5]              = 0xFFFFFFFF,
    [METATILE_ATTRIBUTE_LAYER_TYPE]     = METATILE_ATTR_LAYER_MASK,
    [METATILE_ATTRIBUTE_7]              = 0xFFFFFFFF
};

static const u8 sMetatileAttrShiftsEmerald[METATILE_ATTRIBUTE_COUNT] = {
    
    [METATILE_ATTRIBUTE_BEHAVIOR]       = 0,
    [METATILE_ATTRIBUTE_TERRAIN]        = 0,
    [METATILE_ATTRIBUTE_2]              = 0,
    [METATILE_ATTRIBUTE_3]              = 0,
    [METATILE_ATTRIBUTE_ENCOUNTER_TYPE] = 0,
    [METATILE_ATTRIBUTE_5]              = 0,
    [METATILE_ATTRIBUTE_LAYER_TYPE]     = METATILE_ATTR_LAYER_SHIFT,
    [METATILE_ATTRIBUTE_7]              = 0
};

const struct MapHeader *const GetMapHeaderFromConnection(const struct MapConnection *connection)
{
    return Overworld_GetMapHeaderByGroupAndId(connection->mapGroup, connection->mapNum);
}

void InitMap(void)
{
    InitMapLayoutData(&gMapHeader);
    SetOccupiedSecretBaseEntranceMetatiles(gMapHeader.events);
    RunOnLoadMapScript();
}

void InitMapFromSavedGame(void)
{
    InitMapLayoutData(&gMapHeader);
    InitSecretBaseAppearance(FALSE);
    SetOccupiedSecretBaseEntranceMetatiles(gMapHeader.events);
    LoadSavedMapView();
    RunOnLoadMapScript();
    UpdateTVScreensOnMap(gBackupMapLayout.width, gBackupMapLayout.height);
}

void InitBattlePyramidMap(bool8 setPlayerPosition)
{
    CpuFastFill16(MAPGRID_UNDEFINED, sBackupMapData, sizeof(sBackupMapData));
    GenerateBattlePyramidFloorLayout(sBackupMapData, setPlayerPosition);
}

void InitTrainerHillMap(void)
{
    CpuFastFill16(MAPGRID_UNDEFINED, sBackupMapData, sizeof(sBackupMapData));
    GenerateTrainerHillFloorLayout(sBackupMapData);
}

static void InitMapLayoutData(struct MapHeader *mapHeader)
{
    struct MapLayout const *mapLayout;
    int width;
    int height;
    mapLayout = mapHeader->mapLayout;
    CpuFastFill16(MAPGRID_UNDEFINED, sBackupMapData, sizeof(sBackupMapData));
    gBackupMapLayout.map = sBackupMapData;
    width = mapLayout->width + MAP_OFFSET_W;
    gBackupMapLayout.width = width;
    height = mapLayout->height + MAP_OFFSET_H;
    gBackupMapLayout.height = height;
    if (width * height <= MAX_MAP_DATA_SIZE)
    {
        InitBackupMapLayoutData(mapLayout->map, mapLayout->width, mapLayout->height);
        InitBackupMapLayoutConnections(mapHeader);
    }
}

static void InitBackupMapLayoutData(const u16 *map, u16 width, u16 height)
{
    u16 *dest;
    int y;
    dest = gBackupMapLayout.map;
    dest += gBackupMapLayout.width * 7 + MAP_OFFSET;
    for (y = 0; y < height; y++)
    {
        CpuCopy16(map, dest, width * 2);
        dest += width + MAP_OFFSET_W;
        map += width;
    }
}

static void InitBackupMapLayoutConnections(struct MapHeader *mapHeader)
{
    int count;
    const struct MapConnection *connection;
    int i;

    if (mapHeader->connections)
    {
        count = mapHeader->connections->count;
        connection = mapHeader->connections->connections;
        sMapConnectionFlags = sDummyConnectionFlags;
        for (i = 0; i < count; i++, connection++)
        {
            struct MapHeader const *cMap = GetMapHeaderFromConnection(connection);
            s32 offset = connection->offset;
            switch (connection->direction)
            {
            case CONNECTION_SOUTH:
                FillSouthConnection(mapHeader, cMap, offset);
                sMapConnectionFlags.south = TRUE;
                break;
            case CONNECTION_NORTH:
                FillNorthConnection(mapHeader, cMap, offset);
                sMapConnectionFlags.north = TRUE;
                break;
            case CONNECTION_WEST:
                FillWestConnection(mapHeader, cMap, offset);
                sMapConnectionFlags.west = TRUE;
                break;
            case CONNECTION_EAST:
                FillEastConnection(mapHeader, cMap, offset);
                sMapConnectionFlags.east = TRUE;
                break;
            }
        }
    }
}

static void FillConnection(int x, int y, struct MapHeader const *connectedMapHeader, int x2, int y2, int width, int height)
{
    int i;
    const u16 *src;
    u16 *dest;
    int mapWidth;

    mapWidth = connectedMapHeader->mapLayout->width;
    src = &connectedMapHeader->mapLayout->map[mapWidth * y2 + x2];
    dest = &gBackupMapLayout.map[gBackupMapLayout.width * y + x];

    for (i = 0; i < height; i++)
    {
        CpuCopy16(src, dest, width * 2);
        dest += gBackupMapLayout.width;
        src += mapWidth;
    }
}

static void FillSouthConnection(struct MapHeader const *mapHeader, struct MapHeader const *connectedMapHeader, s32 offset)
{
    int x, y;
    int x2;
    int width;
    int cWidth;

    if (connectedMapHeader)
    {
        cWidth = connectedMapHeader->mapLayout->width;
        x = offset + MAP_OFFSET;
        y = mapHeader->mapLayout->height + MAP_OFFSET;
        if (x < 0)
        {
            x2 = -x;
            x += cWidth;
            if (x < gBackupMapLayout.width)
                width = x;
            else
                width = gBackupMapLayout.width;
            x = 0;
        }
        else
        {
            x2 = 0;
            if (x + cWidth < gBackupMapLayout.width)
                width = cWidth;
            else
                width = gBackupMapLayout.width - x;
        }

        FillConnection(
            x, y,
            connectedMapHeader,
            x2, /*y2*/ 0,
            width, /*height*/ MAP_OFFSET);
    }
}

static void FillNorthConnection(struct MapHeader const *mapHeader, struct MapHeader const *connectedMapHeader, s32 offset)
{
    int x;
    int x2, y2;
    int width;
    int cWidth, cHeight;

    if (connectedMapHeader)
    {
        cWidth = connectedMapHeader->mapLayout->width;
        cHeight = connectedMapHeader->mapLayout->height;
        x = offset + MAP_OFFSET;
        y2 = cHeight - MAP_OFFSET;
        if (x < 0)
        {
            x2 = -x;
            x += cWidth;
            if (x < gBackupMapLayout.width)
                width = x;
            else
                width = gBackupMapLayout.width;
            x = 0;
        }
        else
        {
            x2 = 0;
            if (x + cWidth < gBackupMapLayout.width)
                width = cWidth;
            else
                width = gBackupMapLayout.width - x;
        }

        FillConnection(
            x, /*y*/ 0,
            connectedMapHeader,
            x2, y2,
            width, /*height*/ MAP_OFFSET);

    }
}

static void FillWestConnection(struct MapHeader const *mapHeader, struct MapHeader const *connectedMapHeader, s32 offset)
{
    int y;
    int x2, y2;
    int height;
    int cWidth, cHeight;
    if (connectedMapHeader)
    {
        cWidth = connectedMapHeader->mapLayout->width;
        cHeight = connectedMapHeader->mapLayout->height;
        y = offset + MAP_OFFSET;
        x2 = cWidth - MAP_OFFSET;
        if (y < 0)
        {
            y2 = -y;
            if (y + cHeight < gBackupMapLayout.height)
                height = y + cHeight;
            else
                height = gBackupMapLayout.height;
            y = 0;
        }
        else
        {
            y2 = 0;
            if (y + cHeight < gBackupMapLayout.height)
                height = cHeight;
            else
                height = gBackupMapLayout.height - y;
        }

        FillConnection(
            /*x*/ 0, y,
            connectedMapHeader,
            x2, y2,
            /*width*/ MAP_OFFSET, height);
    }
}

static void FillEastConnection(struct MapHeader const *mapHeader, struct MapHeader const *connectedMapHeader, s32 offset)
{
    int x, y;
    int y2;
    int height;
    int cHeight;
    if (connectedMapHeader)
    {
        cHeight = connectedMapHeader->mapLayout->height;
        x = mapHeader->mapLayout->width + MAP_OFFSET;
        y = offset + MAP_OFFSET;
        if (y < 0)
        {
            y2 = -y;
            if (y + cHeight < gBackupMapLayout.height)
                height = y + cHeight;
            else
                height = gBackupMapLayout.height;
            y = 0;
        }
        else
        {
            y2 = 0;
            if (y + cHeight < gBackupMapLayout.height)
                height = cHeight;
            else
                height = gBackupMapLayout.height - y;
        }

        FillConnection(
            x, y,
            connectedMapHeader,
            /*x2*/ 0, y2,
            /*width*/ MAP_OFFSET + 1, height);
    }
}

u8 MapGridGetElevationAt(int x, int y)
{
    u16 block = GetMapGridBlockAt(x, y);

    if (block == MAPGRID_UNDEFINED)
        return 0;

    return block >> MAPGRID_ELEVATION_SHIFT;
}

u8 MapGridGetCollisionAt(int x, int y)
{
    u16 block = GetMapGridBlockAt(x, y);

    if (block == MAPGRID_UNDEFINED)
        return TRUE;

    return (block & MAPGRID_COLLISION_MASK) >> MAPGRID_COLLISION_SHIFT;
}

u32 GetNumTilesInPrimary(struct MapLayout const *mapLayout)
{
    return mapLayout->isFrlg ? NUM_TILES_IN_PRIMARY_FRLG : NUM_TILES_IN_PRIMARY;
}

u32 GetNumMetatilesInPrimary(struct MapLayout const *mapLayout)
{
    return mapLayout->isFrlg ? NUM_METATILES_IN_PRIMARY_FRLG : NUM_METATILES_IN_PRIMARY;
}

u32 GetNumPalsInPrimary(struct MapLayout const *mapLayout)
{
    return mapLayout->isFrlg ? NUM_PALS_IN_PRIMARY_FRLG : NUM_PALS_IN_PRIMARY;
}

u32 MapGridGetMetatileIdAt(int x, int y)
{
    u16 block = GetMapGridBlockAt(x, y);

    if (block == MAPGRID_UNDEFINED)
        return GetBorderBlockAt(x, y) & MAPGRID_METATILE_ID_MASK;

    return block & MAPGRID_METATILE_ID_MASK;
}

u32 MapGridGetMetatileAttributeAt(s16 x, s16 y, u8 attributeType)
{
    u16 metatileId = MapGridGetMetatileIdAt(x, y);
    return GetAttributeByMetatileIdAndMapLayout(metatileId, attributeType, gMapHeader.mapLayout->isFrlg);
}

u32 MapGridGetMetatileBehaviorAt(int x, int y)
{
    return MapGridGetMetatileAttributeAt(x, y, METATILE_ATTRIBUTE_BEHAVIOR);
}

u8 MapGridGetMetatileLayerTypeAt(int x, int y)
{
    return MapGridGetMetatileAttributeAt(x, y, METATILE_ATTRIBUTE_LAYER_TYPE);
}

void MapGridSetMetatileIdAt(int x, int y, u16 metatile)
{
    int i;
    if (AreCoordsWithinMapGridBounds(x, y))
    {
        i = x + y * gBackupMapLayout.width;
        gBackupMapLayout.map[i] = (gBackupMapLayout.map[i] & MAPGRID_ELEVATION_MASK) | (metatile & ~MAPGRID_ELEVATION_MASK);
    }
}

void MapGridSetMetatileEntryAt(int x, int y, u16 metatile)
{
    int i;
    if (AreCoordsWithinMapGridBounds(x, y))
    {
        i = x + gBackupMapLayout.width * y;
        gBackupMapLayout.map[i] = metatile;
    }
}

#define MB_FRLG_NORMAL 0x00
#define MB_FRLG_UNUSED_01 0x01
#define MB_FRLG_TALL_GRASS 0x02
//
#define MB_FRLG_CAVE 0x08
//
#define MB_FRLG_RUNNING_DISALLOWED 0x0A
#define MB_FRLG_INDOOR_ENCOUNTER 0x0B
#define MB_FRLG_MOUNTAIN_TOP 0x0C
//
#define MB_FRLG_POND_WATER 0x10
#define MB_FRLG_FAST_WATER 0x11
#define MB_FRLG_DEEP_WATER 0x12
#define MB_FRLG_WATERFALL 0x13
//
#define MB_FRLG_OCEAN_WATER 0x15
#define MB_FRLG_PUDDLE 0x16
#define MB_FRLG_SHALLOW_WATER 0x17
//
#define MB_FRLG_UNDERWATER_BLOCKED_ABOVE 0x19
#define MB_FRLG_UNUSED_WATER 0x1A
#define MB_FRLG_CYCLING_ROAD_WATER 0x1B
//
#define MB_FRLG_STRENGTH_BUTTON 0x20
#define MB_FRLG_SAND 0x21
#define MB_FRLG_SEAWEED 0x22
#define MB_FRLG_ICE 0x23
//
#define MB_FRLG_THIN_ICE 0x26
#define MB_FRLG_CRACKED_ICE 0x27
#define MB_FRLG_HOT_SPRINGS 0x28
//
#define MB_FRLG_ROCK_STAIRS 0x2A
#define MB_FRLG_SAND_CAVE 0x2B
//
#define MB_FRLG_IMPASSABLE_EAST 0x30
#define MB_FRLG_IMPASSABLE_WEST 0x31
#define MB_FRLG_IMPASSABLE_NORTH 0x32
#define MB_FRLG_IMPASSABLE_SOUTH 0x33
#define MB_FRLG_IMPASSABLE_NORTHEAST 0x34
#define MB_FRLG_IMPASSABLE_NORTHWEST 0x35
#define MB_FRLG_IMPASSABLE_SOUTHEAST 0x36
#define MB_FRLG_IMPASSABLE_SOUTHWEST 0x37
#define MB_FRLG_JUMP_EAST 0x38
#define MB_FRLG_JUMP_WEST 0x39
#define MB_FRLG_JUMP_NORTH 0x3A
#define MB_FRLG_JUMP_SOUTH 0x3B
//
#define MB_FRLG_WALK_EAST 0x40
#define MB_FRLG_WALK_WEST 0x41
#define MB_FRLG_WALK_NORTH 0x42
#define MB_FRLG_WALK_SOUTH 0x43
#define MB_FRLG_SLIDE_EAST 0x44
#define MB_FRLG_SLIDE_WEST 0x45
#define MB_FRLG_SLIDE_NORTH 0x46
#define MB_FRLG_SLIDE_SOUTH 0x47
#define MB_FRLG_TRICK_HOUSE_PUZZLE_8_FLOOR 0x48
//
#define MB_FRLG_EASTWARD_CURRENT 0x50
#define MB_FRLG_WESTWARD_CURRENT 0x51
#define MB_FRLG_NORTHWARD_CURRENT 0x52
#define MB_FRLG_SOUTHWARD_CURRENT 0x53
#define MB_FRLG_SPIN_RIGHT 0x54
#define MB_FRLG_SPIN_LEFT 0x55
#define MB_FRLG_SPIN_UP 0x56
#define MB_FRLG_SPIN_DOWN 0x57
#define MB_FRLG_STOP_SPINNING 0x58
//
#define MB_FRLG_CAVE_DOOR 0x60
#define MB_FRLG_LADDER 0x61
#define MB_FRLG_EAST_ARROW_WARP 0x62
#define MB_FRLG_WEST_ARROW_WARP 0x63
#define MB_FRLG_NORTH_ARROW_WARP 0x64
#define MB_FRLG_SOUTH_ARROW_WARP 0x65
#define MB_FRLG_FALL_WARP 0x66
#define MB_FRLG_REGULAR_WARP 0x67
#define MB_FRLG_LAVARIDGE_1F_WARP 0x68
#define MB_FRLG_WARP_DOOR 0x69
#define MB_FRLG_UP_ESCALATOR 0x6A
#define MB_FRLG_DOWN_ESCALATOR 0x6B
#define MB_FRLG_UP_RIGHT_STAIR_WARP 0x6C
#define MB_FRLG_UP_LEFT_STAIR_WARP 0x6D
#define MB_FRLG_DOWN_RIGHT_STAIR_WARP 0x6E
#define MB_FRLG_DOWN_LEFT_STAIR_WARP 0x6F
//
#define MB_FRLG_UNION_ROOM_WARP 0x71
//
#define MB_FRLG_COUNTER 0x80
#define MB_FRLG_BOOKSHELF 0x81
#define MB_FRLG_POKEMART_SHELF 0x82
#define MB_FRLG_PC 0x83
#define MB_FRLG_SIGNPOST 0x84
#define MB_FRLG_REGION_MAP 0x85
#define MB_FRLG_TELEVISION 0x86
#define MB_FRLG_POKEMON_CENTER_SIGN 0x87
#define MB_FRLG_POKEMART_SIGN 0x88
#define MB_FRLG_CABINET 0x89
#define MB_FRLG_KITCHEN 0x8A
#define MB_FRLG_DRESSER 0x8B
#define MB_FRLG_SNACKS 0x8C
#define MB_FRLG_CABLE_CLUB_WIRELESS_MONITOR 0x8D
#define MB_FRLG_BATTLE_RECORDS 0x8E
#define MB_FRLG_QUESTIONNAIRE 0x8F
#define MB_FRLG_FOOD 0x90
#define MB_FRLG_INDIGO_PLATEAU_SIGN_1 0x91
#define MB_FRLG_INDIGO_PLATEAU_SIGN_2 0x92
#define MB_FRLG_BLUEPRINTS 0x93
#define MB_FRLG_PAINTING 0x94
#define MB_FRLG_POWER_PLANT_MACHINE 0x95
#define MB_FRLG_TELEPHONE 0x96
#define MB_FRLG_COMPUTER 0x97
#define MB_FRLG_ADVERTISING_POSTER 0x98
#define MB_FRLG_FOOD_SMELLS_TASTY 0x99
#define MB_FRLG_TRASH_BIN 0x9A
#define MB_FRLG_CUP 0x9B
#define MB_FRLG_PORTHOLE 0x9C
#define MB_FRLG_WINDOW 0x9D
#define MB_FRLG_BLINKING_LIGHTS 0x9E
#define MB_FRLG_NEATLY_LINED_UP_TOOLS 0x9F
#define MB_FRLG_IMPRESSIVE_MACHINE 0xA0
#define MB_FRLG_VIDEO_GAME 0xA1
#define MB_FRLG_BURGLARY 0xA2
#define MB_FRLG_TRAINER_TOWER_MONITOR 0xA3
//
#define MB_FRLG_CYCLING_ROAD_PULL_DOWN 0xD0
#define MB_FRLG_CYCLING_ROAD_PULL_DOWN_GRASS 0xD1

static const u32 sFrlgToEmeraldBehavior[NUM_METATILE_BEHAVIORS] =
{
    [MB_FRLG_CAVE] = MB_CAVE,
    [MB_FRLG_UP_RIGHT_STAIR_WARP] = MB_UP_RIGHT_STAIR_WARP,
    [MB_FRLG_UP_LEFT_STAIR_WARP] = MB_UP_LEFT_STAIR_WARP,
    [MB_FRLG_DOWN_RIGHT_STAIR_WARP] = MB_DOWN_RIGHT_STAIR_WARP,
    [MB_FRLG_DOWN_LEFT_STAIR_WARP] = MB_DOWN_LEFT_STAIR_WARP,
    [MB_FRLG_NORTH_ARROW_WARP] = MB_NORTH_ARROW_WARP,
    [MB_FRLG_SOUTH_ARROW_WARP] = MB_SOUTH_ARROW_WARP,
    [MB_FRLG_WEST_ARROW_WARP] = MB_WEST_ARROW_WARP,
    [MB_FRLG_EAST_ARROW_WARP] = MB_EAST_ARROW_WARP,
    [MB_FRLG_PC] = MB_PC,
    [MB_FRLG_WARP_DOOR] = MB_ANIMATED_DOOR,
    [MB_FRLG_TALL_GRASS] = MB_TALL_GRASS,
    [MB_FRLG_JUMP_NORTH] = MB_JUMP_NORTH,
    [MB_FRLG_JUMP_SOUTH] = MB_JUMP_SOUTH,
    [MB_FRLG_JUMP_WEST] = MB_JUMP_WEST,
    [MB_FRLG_JUMP_EAST] = MB_JUMP_EAST,
    [MB_FRLG_CAVE_DOOR] = MB_NON_ANIMATED_DOOR,
    [MB_FRLG_COUNTER] = MB_COUNTER,
    [MB_FRLG_LADDER] = MB_LADDER,
    [MB_FRLG_SPIN_RIGHT] = MB_SPIN_RIGHT,
    [MB_FRLG_SPIN_LEFT] = MB_SPIN_LEFT,
    [MB_FRLG_SPIN_UP] = MB_SPIN_UP,
    [MB_FRLG_SPIN_DOWN] = MB_SPIN_DOWN,
    [MB_FRLG_STOP_SPINNING] = MB_STOP_SPINNING,
    [MB_FRLG_CYCLING_ROAD_PULL_DOWN] = MB_CYCLING_ROAD_PULL_DOWN,
    [MB_FRLG_CYCLING_ROAD_PULL_DOWN_GRASS] = MB_CYCLING_ROAD_PULL_DOWN_GRASS,
};

static u32 TranslateFrlgBehaviour(u32 behavior)
{
    if (behavior >= NUM_METATILE_BEHAVIORS)
        return MB_INVALID;
    return sFrlgToEmeraldBehavior[behavior];
}

u32 ExtractMetatileAttribute(u32 attributes, u8 attributeType, bool32 isFrlg)
{
    if (attributeType >= METATILE_ATTRIBUTE_COUNT) // Check for METATILE_ATTRIBUTES_ALL
        return attributes;

    if (isFrlg)
    {
        if (attributeType == METATILE_ATTRIBUTE_BEHAVIOR)
            return TranslateFrlgBehaviour((attributes & sMetatileAttrMasks[attributeType]) >> sMetatileAttrShifts[attributeType]);
        else
            return (attributes & sMetatileAttrMasks[attributeType]) >> sMetatileAttrShifts[attributeType];
    }

    return (attributes & sMetatileAttrMasksEmerald[attributeType]) >> sMetatileAttrShiftsEmerald[attributeType];
}

static u32 GetAttributeByMetatileIdAndMapLayoutFrlg(u16 metatile, u8 attributeType)
{
    u32 attribute;
    if (metatile < GetNumMetatilesInPrimary(gMapHeader.mapLayout))
    {
        const u32 *attributes = (const u32*)gMapHeader.mapLayout->primaryTileset->metatileAttributes;
        attribute = attributes[metatile];
    }
    else if (metatile < NUM_METATILES_TOTAL)
    {
        const u32 *attributes = (const u32*) gMapHeader.mapLayout->secondaryTileset->metatileAttributes;
        metatile -= GetNumMetatilesInPrimary(gMapHeader.mapLayout);
        attribute = attributes[metatile];
    }
    else
    {
        return MB_INVALID;
    }

    return ExtractMetatileAttribute(attribute, attributeType, TRUE);
}

u32 GetAttributeByMetatileIdAndMapLayout(u16 metatile, u8 attributeType, bool32 isFrlg)
{
    u32 attribute;

    if (isFrlg)
        return GetAttributeByMetatileIdAndMapLayoutFrlg(metatile, attributeType);

    if (metatile < GetNumMetatilesInPrimary(gMapHeader.mapLayout))
    {
        const u16 *attributes = (const u16*)gMapHeader.mapLayout->primaryTileset->metatileAttributes;
        attribute = attributes[metatile];
    }
    else if (metatile < NUM_METATILES_TOTAL)
    {
        const u16 *attributes = (const u16*)gMapHeader.mapLayout->secondaryTileset->metatileAttributes;
        metatile -= GetNumMetatilesInPrimary(gMapHeader.mapLayout);
        attribute = attributes[metatile];
    }
    else
    {
        return MB_INVALID;
    }

    return ExtractMetatileAttribute(attribute, attributeType, FALSE);
}

void SaveMapView(void)
{
    int i, j;
    int x, y;
    u16 *mapView;
    int width;
    mapView = gSaveBlock1Ptr->mapView;
    width = gBackupMapLayout.width;
    x = gSaveBlock1Ptr->pos.x;
    y = gSaveBlock1Ptr->pos.y;
    for (i = y; i < y + MAP_OFFSET_H; i++)
    {
        for (j = x; j < x + MAP_OFFSET_W; j++)
            *mapView++ = sBackupMapData[width * i + j];
    }
}

static bool32 SavedMapViewIsEmpty(void)
{
    u16 i;
    u32 marker = 0;

#ifndef UBFIX
    // BUG: This loop extends past the bounds of the mapView array. Its size is only 0x100.
    for (i = 0; i < 0x200; i++)
        marker |= gSaveBlock1Ptr->mapView[i];
#else
    // UBFIX: Only iterate over 0x100
    for (i = 0; i < ARRAY_COUNT(gSaveBlock1Ptr->mapView); i++)
        marker |= gSaveBlock1Ptr->mapView[i];
#endif


    if (marker == 0)
        return TRUE;
    else
        return FALSE;
}

static void ClearSavedMapView(void)
{
    CpuFill16(0, gSaveBlock1Ptr->mapView, sizeof(gSaveBlock1Ptr->mapView));
}

static void LoadSavedMapView(void)
{
    u8 yMode;
    int i, j;
    int x, y;
    u16 *mapView;
    int width;
    mapView = gSaveBlock1Ptr->mapView;
    if (!SavedMapViewIsEmpty())
    {
        width = gBackupMapLayout.width;
        x = gSaveBlock1Ptr->pos.x;
        y = gSaveBlock1Ptr->pos.y;
        for (i = y; i < y + MAP_OFFSET_H; i++)
        {
            if (i == y && i != 0)
                yMode = 0;
            else if (i == y + MAP_OFFSET_H - 1 && i != gMapHeader.mapLayout->height - 1)
                yMode = 1;
            else
                yMode = 0xFF;

            for (j = x; j < x + MAP_OFFSET_W; j++)
            {
                if (!SkipCopyingMetatileFromSavedMap(&sBackupMapData[j + width * i], width, yMode))
                    sBackupMapData[j + width * i] = *mapView;
                mapView++;
            }
        }
        for (j = x; j < x + MAP_OFFSET_W; j++)
        {
            if (y != 0)
                FixLongGrassMetatilesWindowTop(j, y - 1);
            if (i < gMapHeader.mapLayout->height - 1)
                FixLongGrassMetatilesWindowBottom(j, y + MAP_OFFSET_H - 1);
        }
        ClearSavedMapView();
    }
}

static void MoveMapViewToBackup(u8 direction)
{
    int width;
    u16 *mapView;
    int x0, y0;
    int x2, y2;
    u16 *src, *dest;
    int srci, desti;
    int r9, r8;
    int x, y;
    int i, j;
    mapView = gSaveBlock1Ptr->mapView;
    width = gBackupMapLayout.width;
    r9 = 0;
    r8 = 0;
    x0 = gSaveBlock1Ptr->pos.x;
    y0 = gSaveBlock1Ptr->pos.y;
    x2 = MAP_OFFSET_W;
    y2 = MAP_OFFSET_H;
    switch (direction)
    {
    case CONNECTION_NORTH:
        y0 += 1;
        y2 = MAP_OFFSET_H - 1;
        break;
    case CONNECTION_SOUTH:
        r8 = 1;
        y2 = MAP_OFFSET_H - 1;
        break;
    case CONNECTION_WEST:
        x0 += 1;
        x2 = MAP_OFFSET_W - 1;
        break;
    case CONNECTION_EAST:
        r9 = 1;
        x2 = MAP_OFFSET_W - 1;
        break;
    }
    for (y = 0; y < y2; y++)
    {
        i = 0;
        j = 0;
        for (x = 0; x < x2; x++)
        {
            desti = width * (y + y0);
            srci = (y + r8) * MAP_OFFSET_W + r9;
            src = &mapView[srci + i];
            dest = &sBackupMapData[x0 + desti + j];
            *dest = *src;
            i++;
            j++;
        }
    }
    ClearSavedMapView();
}

int GetMapBorderIdAt(int x, int y)
{
    if (GetMapGridBlockAt(x, y) == MAPGRID_UNDEFINED)
        return CONNECTION_INVALID;

    if (x >= (gBackupMapLayout.width - (MAP_OFFSET + 1)))
    {
        if (!sMapConnectionFlags.east)
            return CONNECTION_INVALID;

        return CONNECTION_EAST;
    }
    else if (x < MAP_OFFSET)
    {
        if (!sMapConnectionFlags.west)
            return CONNECTION_INVALID;

        return CONNECTION_WEST;
    }
    else if (y >= (gBackupMapLayout.height - MAP_OFFSET))
    {
        if (!sMapConnectionFlags.south)
            return CONNECTION_INVALID;

        return CONNECTION_SOUTH;
    }
    else if (y < MAP_OFFSET)
    {
        if (!sMapConnectionFlags.north)
            return CONNECTION_INVALID;

        return CONNECTION_NORTH;
    }
    else
    {
        return CONNECTION_NONE;
    }
}

int GetPostCameraMoveMapBorderId(int x, int y)
{
    return GetMapBorderIdAt(gSaveBlock1Ptr->pos.x + MAP_OFFSET + x, gSaveBlock1Ptr->pos.y + MAP_OFFSET + y);
}

bool32 CanCameraMoveInDirection(int direction)
{
    int x, y;
    x = gSaveBlock1Ptr->pos.x + MAP_OFFSET + gDirectionToVectors[direction].x;
    y = gSaveBlock1Ptr->pos.y + MAP_OFFSET + gDirectionToVectors[direction].y;

    if (GetMapBorderIdAt(x, y) == CONNECTION_INVALID)
        return FALSE;

    return TRUE;
}

static void SetPositionFromConnection(const struct MapConnection *connection, int direction, int x, int y)
{
    struct MapHeader const *mapHeader = GetMapHeaderFromConnection(connection);

    switch (direction)
    {
    case CONNECTION_EAST:
        gSaveBlock1Ptr->pos.x = -x;
        gSaveBlock1Ptr->pos.y -= connection->offset;
        break;
    case CONNECTION_WEST:
        gSaveBlock1Ptr->pos.x = mapHeader->mapLayout->width;
        gSaveBlock1Ptr->pos.y -= connection->offset;
        break;
    case CONNECTION_SOUTH:
        gSaveBlock1Ptr->pos.x -= connection->offset;
        gSaveBlock1Ptr->pos.y = -y;
        break;
    case CONNECTION_NORTH:
        gSaveBlock1Ptr->pos.x -= connection->offset;
        gSaveBlock1Ptr->pos.y = mapHeader->mapLayout->height;
        break;
    default:
        DebugPrintfLevel(MGBA_LOG_WARN, "SetPositionFromConnection was passed an invalid direction (%d)!", direction);
        break;
    }
}

bool8 CameraMove(int x, int y)
{
    int direction;
    const struct MapConnection *connection;
    int old_x, old_y;
    gCamera.active = FALSE;
    direction = GetPostCameraMoveMapBorderId(x, y);
    if (direction == CONNECTION_NONE || direction == CONNECTION_INVALID)
    {
        gSaveBlock1Ptr->pos.x += x;
        gSaveBlock1Ptr->pos.y += y;
    }
    else
    {
        SaveMapView();
        ClearMirageTowerPulseBlendEffect();
        old_x = gSaveBlock1Ptr->pos.x;
        old_y = gSaveBlock1Ptr->pos.y;
        connection = GetIncomingConnection(direction, gSaveBlock1Ptr->pos.x, gSaveBlock1Ptr->pos.y);
        if (connection)
        {
            SetPositionFromConnection(connection, direction, x, y);
            LoadMapFromCameraTransition(connection->mapGroup, connection->mapNum);
            gCamera.active = TRUE;
            gCamera.x = old_x - gSaveBlock1Ptr->pos.x;
            gCamera.y = old_y - gSaveBlock1Ptr->pos.y;
            gSaveBlock1Ptr->pos.x += x;
            gSaveBlock1Ptr->pos.y += y;
            MoveMapViewToBackup(direction);
        }
        else
        {
            DebugPrintfLevel(MGBA_LOG_WARN, "GetIncomingConnection returned an invalid connection inside CameraMove!");
        }

    }
    return gCamera.active;
}

static const struct MapConnection *GetIncomingConnection(u8 direction, int x, int y)
{
    int count;
    int i;
    const struct MapConnection *connection;
    const struct MapConnections *connections = gMapHeader.connections;

#ifdef UBFIX // UB: Multiple possible null dereferences
    if (connections == NULL || connections->connections == NULL)
        return NULL;
#endif
    count = connections->count;
    connection = connections->connections;
    for (i = 0; i < count; i++, connection++)
    {
        if (connection->direction == direction && IsPosInIncomingConnectingMap(direction, x, y, connection) == TRUE)
            return connection;
    }
    return NULL;
}

static bool8 IsPosInIncomingConnectingMap(u8 direction, int x, int y, const struct MapConnection *connection)
{
    struct MapHeader const *mapHeader;
    mapHeader = GetMapHeaderFromConnection(connection);
    switch (direction)
    {
    case CONNECTION_SOUTH:
    case CONNECTION_NORTH:
        return IsCoordInIncomingConnectingMap(x, gMapHeader.mapLayout->width, mapHeader->mapLayout->width, connection->offset);
    case CONNECTION_WEST:
    case CONNECTION_EAST:
        return IsCoordInIncomingConnectingMap(y, gMapHeader.mapLayout->height, mapHeader->mapLayout->height, connection->offset);
    }
    return FALSE;
}

static bool8 IsCoordInIncomingConnectingMap(int coord, int srcMax, int destMax, int offset)
{
    int offset2;
    offset2 = offset;

    if (offset2 < 0)
        offset2 = 0;

    if (destMax + offset < srcMax)
        srcMax = destMax + offset;

    if (offset2 <= coord && coord <= srcMax)
        return TRUE;

    return FALSE;
}

static int IsCoordInConnectingMap(int coord, int max)
{
    if (coord >= 0 && coord < max)
        return TRUE;

    return FALSE;
}

static int IsPosInConnectingMap(const struct MapConnection *connection, int x, int y)
{
    struct MapHeader const *mapHeader;
    mapHeader = GetMapHeaderFromConnection(connection);
    switch (connection->direction)
    {
    case CONNECTION_SOUTH:
    case CONNECTION_NORTH:
        return IsCoordInConnectingMap(x - connection->offset, mapHeader->mapLayout->width);
    case CONNECTION_WEST:
    case CONNECTION_EAST:
        return IsCoordInConnectingMap(y - connection->offset, mapHeader->mapLayout->height);
    }
    return FALSE;
}

const struct MapConnection *GetMapConnectionAtPos(s16 x, s16 y)
{
    int count;
    const struct MapConnection *connection;
    int i;
    u8 direction;
    if (!gMapHeader.connections)
    {
        return NULL;
    }
    else
    {
        count = gMapHeader.connections->count;
        connection = gMapHeader.connections->connections;
        for (i = 0; i < count; i++, connection++)
        {
            direction = connection->direction;
            if ((direction == CONNECTION_DIVE || direction == CONNECTION_EMERGE)
             || (direction == CONNECTION_NORTH && y > MAP_OFFSET - 1)
             || (direction == CONNECTION_SOUTH && y < gMapHeader.mapLayout->height + MAP_OFFSET)
             || (direction == CONNECTION_WEST && x > MAP_OFFSET - 1)
             || (direction == CONNECTION_EAST && x < gMapHeader.mapLayout->width + MAP_OFFSET))
            {
                continue;
            }
            if (IsPosInConnectingMap(connection, x - MAP_OFFSET, y - MAP_OFFSET) == TRUE)
            {
                return connection;
            }
        }
    }
    return NULL;
}

void SetCameraFocusCoords(u16 x, u16 y)
{
    gSaveBlock1Ptr->pos.x = x - MAP_OFFSET;
    gSaveBlock1Ptr->pos.y = y - MAP_OFFSET;
}

void GetCameraFocusCoords(u16 *x, u16 *y)
{
    *x = gSaveBlock1Ptr->pos.x + MAP_OFFSET;
    *y = gSaveBlock1Ptr->pos.y + MAP_OFFSET;
}

static void UNUSED SetCameraCoords(u16 x, u16 y)
{
    gSaveBlock1Ptr->pos.x = x;
    gSaveBlock1Ptr->pos.y = y;
}

void GetCameraCoords(u16 *x, u16 *y)
{
    *x = gSaveBlock1Ptr->pos.x;
    *y = gSaveBlock1Ptr->pos.y;
}

void MapGridSetMetatileImpassabilityAt(int x, int y, bool32 impassable)
{
    if (AreCoordsWithinMapGridBounds(x, y))
    {
        if (impassable)
            gBackupMapLayout.map[x + gBackupMapLayout.width * y] |= MAPGRID_COLLISION_MASK;
        else
            gBackupMapLayout.map[x + gBackupMapLayout.width * y] &= ~MAPGRID_COLLISION_MASK;
    }
}

static bool8 SkipCopyingMetatileFromSavedMap(u16 *mapBlock, u16 mapWidth, u8 yMode)
{
    if (yMode == 0xFF)
        return FALSE;

    if (yMode == 0)
        mapBlock -= mapWidth;
    else
        mapBlock += mapWidth;

    if (IsLargeBreakableDecoration(*mapBlock & MAPGRID_METATILE_ID_MASK, yMode) == TRUE)
        return TRUE;
    return FALSE;
}

static void CopyTilesetToVram(struct Tileset const *tileset, u16 numTiles, u16 offset)
{
    if (tileset)
    {
        if (!tileset->isCompressed)
            LoadBgTiles(2, tileset->tiles, numTiles * 32, offset);
        else
            DecompressAndCopyTileDataToVram(2, tileset->tiles, numTiles * 32, offset, 0);
    }
}

static void CopyTilesetToVramUsingHeap(struct Tileset const *tileset, u16 numTiles, u16 offset)
{
    if (tileset)
    {
        if (!tileset->isCompressed)
            LoadBgTiles(2, tileset->tiles, numTiles * 32, offset);
        else
            DecompressAndLoadBgGfxUsingHeap(2, tileset->tiles, numTiles * 32, offset, 0);
    }
}

// Below two are dummied functions from FRLG, used to tint the overworld palettes for the Quest Log
static void ApplyGlobalTintToPaletteEntries(u16 offset, u16 size)
{

}

static void UNUSED ApplyGlobalTintToPaletteSlot(u8 slot, u8 count)
{

}

static void LoadTilesetPalette(struct Tileset const *tileset, u16 destOffset, u16 size, bool8 skipFaded, u32 numPalsInPrimary)
{
    if (tileset)
    {
        if (tileset->isSecondary == FALSE)
        {
            if (skipFaded)
                CpuFastCopy(tileset->palettes, &gPlttBufferUnfaded[destOffset], size); // always word-aligned
            else
                LoadPaletteFast(tileset->palettes, destOffset, size);
            gPlttBufferFaded[destOffset] = gPlttBufferUnfaded[destOffset] = RGB_BLACK;
            ApplyGlobalTintToPaletteEntries(destOffset + 1, (size - 2) >> 1);
        }
        else if (tileset->isSecondary == TRUE)
        {
            // All 'gTilesetPalettes_' arrays should have ALIGNED(4) in them,
            // but we use SmartCopy here just in case they don't
            if (skipFaded)
                CpuCopy16(tileset->palettes[numPalsInPrimary], &gPlttBufferUnfaded[destOffset], size);
            else
                LoadPaletteFast(tileset->palettes[numPalsInPrimary], destOffset, size);
        }
        else
        {
            LoadPalette((const u16 *)tileset->palettes, destOffset, size);
            ApplyGlobalTintToPaletteEntries(destOffset, size >> 1);
        }
    }
}

void CopyPrimaryTilesetToVram(struct MapLayout const *mapLayout)
{
    CopyTilesetToVram(mapLayout->primaryTileset, GetNumTilesInPrimary(mapLayout), 0);
}

void CopySecondaryTilesetToVram(struct MapLayout const *mapLayout)
{
    CopyTilesetToVram(mapLayout->secondaryTileset, NUM_TILES_TOTAL - GetNumTilesInPrimary(mapLayout), GetNumTilesInPrimary(mapLayout));
}

void CopySecondaryTilesetToVramUsingHeap(struct MapLayout const *mapLayout)
{
    CopyTilesetToVramUsingHeap(mapLayout->secondaryTileset, NUM_TILES_TOTAL - GetNumTilesInPrimary(mapLayout), GetNumTilesInPrimary(mapLayout));
}

static void LoadPrimaryTilesetPalette(struct MapLayout const *mapLayout)
{
    LoadTilesetPalette(mapLayout->primaryTileset, 0, GetNumPalsInPrimary(mapLayout) * PLTT_SIZE_4BPP, FALSE, GetNumPalsInPrimary(mapLayout));
}

void LoadSecondaryTilesetPalette(struct MapLayout const *mapLayout, bool8 skipFaded)
{
    LoadTilesetPalette(mapLayout->secondaryTileset, GetNumPalsInPrimary(mapLayout) * 16, (NUM_PALS_TOTAL - GetNumPalsInPrimary(mapLayout)) * PLTT_SIZE_4BPP, skipFaded, GetNumPalsInPrimary(mapLayout));
}

void CopyMapTilesetsToVram(struct MapLayout const *mapLayout)
{
    if (mapLayout)
    {
        CopyTilesetToVramUsingHeap(mapLayout->primaryTileset, GetNumTilesInPrimary(mapLayout), 0);
        CopyTilesetToVramUsingHeap(mapLayout->secondaryTileset, NUM_TILES_TOTAL - GetNumTilesInPrimary(mapLayout), GetNumTilesInPrimary(mapLayout));
    }
}

void LoadMapTilesetPalettes(struct MapLayout const *mapLayout)
{
    if (mapLayout)
    {
        LoadPrimaryTilesetPalette(mapLayout);
        LoadSecondaryTilesetPalette(mapLayout, FALSE);
    }
}
