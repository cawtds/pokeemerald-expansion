#include "global.h"
#include "data.h"
#include "graphics.h"
#include "species.h"
#include "constants/abilities.h"
#include "constants/cries.h"
#include "constants/pokedex.h"
#include "constants/pokemon.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/types.h"


#include "data/pokemon/egg_moves.h"
#include "data/pokemon/level_up_learnsets.h"
#include "data/pokemon/tutor_learnsets.h"
#include "data/pokemon/tmhm_learnsets.h"
#include "data/pokemon/species_info.h"

static u32 SanitizeSpeciesId(u32 speciesId)
{
    if (speciesId >= NUM_SPECIES_AND_FORMS)
        return SPECIES_NONE;
    return speciesId;
}

const u8 *GetSpeciesName(u32 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].speciesName[0] == 0)
        return gSpeciesInfo[SPECIES_NONE].speciesName;
    return gSpeciesInfo[species].speciesName;
}

const u8 *GetSpeciesCategory(u32 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].categoryName[0] == 0)
        return gSpeciesInfo[SPECIES_NONE].categoryName;
    return gSpeciesInfo[species].categoryName;
}

const u8 *GetSpeciesPokedexDescription(u32 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].description == NULL)
        return gSpeciesInfo[SPECIES_NONE].description;
    return gSpeciesInfo[species].description;
}

u32 GetSpeciesHeight(u32 species)
{
    return gSpeciesInfo[SanitizeSpeciesId(species)].height;
}

u32 GetSpeciesWeight(u32 species)
{
    return gSpeciesInfo[SanitizeSpeciesId(species)].weight;
}

const u16 *GetSpeciesEggMoves(u32 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].eggMoveLearnset == NULL)
        return gSpeciesInfo[SPECIES_NONE].eggMoveLearnset;
    return gSpeciesInfo[species].eggMoveLearnset;
}
