#ifndef GUARD_ABILITY_H
#define GUARD_ABILITY_H

#include "global.h"
#include "constants/abilities.h"

struct AbilityInfo
{
    u8 name[ABILITY_NAME_LENGTH + 1];
    const u8 *description;
};

extern const struct AbilityInfo gAbilityInfo[];

static inline enum Ability SanitizeAbilityId(enum Ability abilityId)
{
    if (abilityId >= ABILITY_COUNT)
        return ABILITY_NONE;
    return abilityId;
}

static inline const u8 *GetAbilityName(enum Ability ability)
{
    ability = SanitizeAbilityId(ability);
    if (gAbilityInfo[ability].name[0] == 0)
        return gAbilityInfo[ABILITY_NONE].name;
    return gAbilityInfo[ability].name;
}

static inline const u8 *GetAbilityDescription(enum Ability ability)
{
    ability = SanitizeAbilityId(ability);
    if (gAbilityInfo[ability].description[0] == 0)
        return gAbilityInfo[ABILITY_NONE].description;
    return gAbilityInfo[ability].description;
}

#endif //GUARD_ABILITY_H