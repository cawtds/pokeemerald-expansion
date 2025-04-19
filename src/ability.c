#include "global.h"
#include "ability.h"
#include "constants/abilities.h"


const struct AbilityInfo gAbilityInfo[ABILITY_COUNT] =
{
    [ABILITY_NONE] =
    {
        .name = _("-------"),
        .description = COMPOUND_STRING("No special ability."),
    },

    [ABILITY_STENCH] =
    {
        .name = _("STENCH"),
        .description = COMPOUND_STRING("Helps repel wild POKéMON."),
    },

    [ABILITY_DRIZZLE] =
    {
        .name = _("DRIZZLE"),
        .description = COMPOUND_STRING("Summons rain in battle."),
    },

    [ABILITY_SPEED_BOOST] =
    {
        .name = _("SPEED BOOST"),
        .description = COMPOUND_STRING("Gradually boosts SPEED."),
    },

    [ABILITY_BATTLE_ARMOR] =
    {
        .name = _("BATTLE ARMOR"),
        .description = COMPOUND_STRING("Blocks critical hits."),
    },

    [ABILITY_STURDY] =
    {
        .name = _("STURDY"),
        .description = COMPOUND_STRING("Negates 1-hit KO attacks."),
    },

    [ABILITY_DAMP] =
    {
        .name = _("DAMP"),
        .description = COMPOUND_STRING("Prevents self-destruction."),
    },

    [ABILITY_LIMBER] =
    {
        .name = _("LIMBER"),
        .description = COMPOUND_STRING("Prevents paralysis."),
    },

    [ABILITY_SAND_VEIL] =
    {
        .name = _("SAND VEIL"),
        .description = COMPOUND_STRING("Ups evasion in a sandstorm."),
    },

    [ABILITY_STATIC] =
    {
        .name = _("STATIC"),
        .description = COMPOUND_STRING("Paralyzes on contact."),
    },

    [ABILITY_VOLT_ABSORB] =
    {
        .name = _("VOLT ABSORB"),
        .description = COMPOUND_STRING("Turns electricity into HP."),
    },

    [ABILITY_WATER_ABSORB] =
    {
        .name = _("WATER ABSORB"),
        .description = COMPOUND_STRING("Changes water into HP."),
    },

    [ABILITY_OBLIVIOUS] =
    {
        .name = _("OBLIVIOUS"),
        .description = COMPOUND_STRING("Prevents attraction."),
    },

    [ABILITY_CLOUD_NINE] =
    {
        .name = _("CLOUD NINE"),
        .description = COMPOUND_STRING("Negates weather effects."),
    },

    [ABILITY_COMPOUND_EYES] =
    {
        .name = _("COMPOUNDEYES"),
        .description = COMPOUND_STRING("Raises accuracy."),
    },

    [ABILITY_INSOMNIA] =
    {
        .name = _("INSOMNIA"),
        .description = COMPOUND_STRING("Prevents sleep."),
    },

    [ABILITY_COLOR_CHANGE] =
    {
        .name = _("COLOR CHANGE"),
        .description = COMPOUND_STRING("Changes type to foe's move."),
    },

    [ABILITY_IMMUNITY] =
    {
        .name = _("IMMUNITY"),
        .description = COMPOUND_STRING("Prevents poisoning."),
    },

    [ABILITY_FLASH_FIRE] =
    {
        .name = _("FLASH FIRE"),
        .description = COMPOUND_STRING("Powers up if hit by fire."),
    },

    [ABILITY_SHIELD_DUST] =
    {
        .name = _("SHIELD DUST"),
        .description = COMPOUND_STRING("Prevents added effects."),
    },

    [ABILITY_OWN_TEMPO] =
    {
        .name = _("OWN TEMPO"),
        .description = COMPOUND_STRING("Prevents confusion."),
    },

    [ABILITY_SUCTION_CUPS] =
    {
        .name = _("SUCTION CUPS"),
        .description = COMPOUND_STRING("Firmly anchors the body."),
    },

    [ABILITY_INTIMIDATE] =
    {
        .name = _("INTIMIDATE"),
        .description = COMPOUND_STRING("Lowers the foe's ATTACK."),
    },

    [ABILITY_SHADOW_TAG] =
    {
        .name = _("SHADOW TAG"),
        .description = COMPOUND_STRING("Prevents the foe's escape."),
    },

    [ABILITY_ROUGH_SKIN] =
    {
        .name = _("ROUGH SKIN"),
        .description = COMPOUND_STRING("Hurts to touch."),
    },

    [ABILITY_WONDER_GUARD] =
    {
        .name = _("WONDER GUARD"),
        .description = COMPOUND_STRING("“Super effective” hits."),
    },

    [ABILITY_LEVITATE] =
    {
        .name = _("LEVITATE"),
        .description = COMPOUND_STRING("Not hit by GROUND attacks."),
    },

    [ABILITY_EFFECT_SPORE] =
    {
        .name = _("EFFECT SPORE"),
        .description = COMPOUND_STRING("Leaves spores on contact."),
    },

    [ABILITY_SYNCHRONIZE] =
    {
        .name = _("SYNCHRONIZE"),
        .description = COMPOUND_STRING("Passes on status problems."),
    },

    [ABILITY_CLEAR_BODY] =
    {
        .name = _("CLEAR BODY"),
        .description = COMPOUND_STRING("Prevents ability reduction."),
    },

    [ABILITY_NATURAL_CURE] =
    {
        .name = _("NATURAL CURE"),
        .description = COMPOUND_STRING("Heals upon switching out."),
    },

    [ABILITY_LIGHTNING_ROD] =
    {
        .name = _("LIGHTNINGROD"),
        .description = COMPOUND_STRING("Draws electrical moves."),
    },

    [ABILITY_SERENE_GRACE] =
    {
        .name = _("SERENE GRACE"),
        .description = COMPOUND_STRING("Promotes added effects."),
    },

    [ABILITY_SWIFT_SWIM] =
    {
        .name = _("SWIFT SWIM"),
        .description = COMPOUND_STRING("Raises SPEED in rain."),
    },

    [ABILITY_CHLOROPHYLL] =
    {
        .name = _("CHLOROPHYLL"),
        .description = COMPOUND_STRING("Raises SPEED in sunshine."),
    },

    [ABILITY_ILLUMINATE] =
    {
        .name = _("ILLUMINATE"),
        .description = COMPOUND_STRING("Encounter rate increases."),
    },

    [ABILITY_TRACE] =
    {
        .name = _("TRACE"),
        .description = COMPOUND_STRING("Copies special ability."),
    },

    [ABILITY_HUGE_POWER] =
    {
        .name = _("HUGE POWER"),
        .description = COMPOUND_STRING("Raises ATTACK."),
    },

    [ABILITY_POISON_POINT] =
    {
        .name = _("POISON POINT"),
        .description = COMPOUND_STRING("Poisons foe on contact."),
    },

    [ABILITY_INNER_FOCUS] =
    {
        .name = _("INNER FOCUS"),
        .description = COMPOUND_STRING("Prevents flinching."),
    },

    [ABILITY_MAGMA_ARMOR] =
    {
        .name = _("MAGMA ARMOR"),
        .description = COMPOUND_STRING("Prevents freezing."),
    },

    [ABILITY_WATER_VEIL] =
    {
        .name = _("WATER VEIL"),
        .description = COMPOUND_STRING("Prevents burns."),
    },

    [ABILITY_MAGNET_PULL] =
    {
        .name = _("MAGNET PULL"),
        .description = COMPOUND_STRING("Traps STEEL-type POKéMON."),
    },

    [ABILITY_SOUNDPROOF] =
    {
        .name = _("SOUNDPROOF"),
        .description = COMPOUND_STRING("Avoids sound-based moves."),
    },

    [ABILITY_RAIN_DISH] =
    {
        .name = _("RAIN DISH"),
        .description = COMPOUND_STRING("Slight HP recovery in rain."),
    },

    [ABILITY_SAND_STREAM] =
    {
        .name = _("SAND STREAM"),
        .description = COMPOUND_STRING("Summons a sandstorm."),
    },

    [ABILITY_PRESSURE] =
    {
        .name = _("PRESSURE"),
        .description = COMPOUND_STRING("Raises foe's PP usage."),
    },

    [ABILITY_THICK_FAT] =
    {
        .name = _("THICK FAT"),
        .description = COMPOUND_STRING("Heat-and-cold protection."),
    },

    [ABILITY_EARLY_BIRD] =
    {
        .name = _("EARLY BIRD"),
        .description = COMPOUND_STRING("Awakens quickly from sleep."),
    },

    [ABILITY_FLAME_BODY] =
    {
        .name = _("FLAME BODY"),
        .description = COMPOUND_STRING("Burns the foe on contact."),
    },

    [ABILITY_RUN_AWAY] =
    {
        .name = _("RUN AWAY"),
        .description = COMPOUND_STRING("Makes escaping easier."),
    },

    [ABILITY_KEEN_EYE] =
    {
        .name = _("KEEN EYE"),
        .description = COMPOUND_STRING("Prevents loss of accuracy."),
    },

    [ABILITY_HYPER_CUTTER] =
    {
        .name = _("HYPER CUTTER"),
        .description = COMPOUND_STRING("Prevents ATTACK reduction."),
    },

    [ABILITY_PICKUP] =
    {
        .name = _("PICKUP"),
        .description = COMPOUND_STRING("May pick up items."),
    },

    [ABILITY_TRUANT] =
    {
        .name = _("TRUANT"),
        .description = COMPOUND_STRING("Moves only every two turns."),
    },

    [ABILITY_HUSTLE] =
    {
        .name = _("HUSTLE"),
        .description = COMPOUND_STRING("Trades accuracy for power."),
    },

    [ABILITY_CUTE_CHARM] =
    {
        .name = _("CUTE CHARM"),
        .description = COMPOUND_STRING("Infatuates on contact."),
    },

    [ABILITY_PLUS] =
    {
        .name = _("PLUS"),
        .description = COMPOUND_STRING("Powers up with MINUS."),
    },

    [ABILITY_MINUS] =
    {
        .name = _("MINUS"),
        .description = COMPOUND_STRING("Powers up with PLUS."),
    },

    [ABILITY_FORECAST] =
    {
        .name = _("FORECAST"),
        .description = COMPOUND_STRING("Changes with the weather."),
    },

    [ABILITY_STICKY_HOLD] =
    {
        .name = _("STICKY HOLD"),
        .description = COMPOUND_STRING("Prevents item theft."),
    },

    [ABILITY_SHED_SKIN] =
    {
        .name = _("SHED SKIN"),
        .description = COMPOUND_STRING("Heals the body by shedding."),
    },

    [ABILITY_GUTS] =
    {
        .name = _("GUTS"),
        .description = COMPOUND_STRING("Ups ATTACK if suffering."),
    },

    [ABILITY_MARVEL_SCALE] =
    {
        .name = _("MARVEL SCALE"),
        .description = COMPOUND_STRING("Ups DEFENSE if suffering."),
    },

    [ABILITY_LIQUID_OOZE] =
    {
        .name = _("LIQUID OOZE"),
        .description = COMPOUND_STRING("Draining causes injury."),
    },

    [ABILITY_OVERGROW] =
    {
        .name = _("OVERGROW"),
        .description = COMPOUND_STRING("Ups GRASS moves in a pinch."),
    },

    [ABILITY_BLAZE] =
    {
        .name = _("BLAZE"),
        .description = COMPOUND_STRING("Ups FIRE moves in a pinch."),
    },

    [ABILITY_TORRENT] =
    {
        .name = _("TORRENT"),
        .description = COMPOUND_STRING("Ups WATER moves in a pinch."),
    },

    [ABILITY_SWARM] =
    {
        .name = _("SWARM"),
        .description = COMPOUND_STRING("Ups BUG moves in a pinch."),
    },

    [ABILITY_ROCK_HEAD] =
    {
        .name = _("ROCK HEAD"),
        .description = COMPOUND_STRING("Prevents recoil damage."),
    },

    [ABILITY_DROUGHT] =
    {
        .name = _("DROUGHT"),
        .description = COMPOUND_STRING("Summons sunlight in battle."),
    },

    [ABILITY_ARENA_TRAP] =
    {
        .name = _("ARENA TRAP"),
        .description = COMPOUND_STRING("Prevents fleeing."),
    },

    [ABILITY_VITAL_SPIRIT] =
    {
        .name = _("VITAL SPIRIT"),
        .description = COMPOUND_STRING("Prevents sleep."),
    },

    [ABILITY_WHITE_SMOKE] =
    {
        .name = _("WHITE SMOKE"),
        .description = COMPOUND_STRING("Prevents ability reduction."),
    },

    [ABILITY_PURE_POWER] =
    {
        .name = _("PURE POWER"),
        .description = COMPOUND_STRING("Raises ATTACK."),
    },

    [ABILITY_SHELL_ARMOR] =
    {
        .name = _("SHELL ARMOR"),
        .description = COMPOUND_STRING("Blocks critical hits."),
    },

    [ABILITY_CACOPHONY] =
    {
        .name = _("CACOPHONY"),
        .description = COMPOUND_STRING("Avoids sound-based moves."),
    },

    [ABILITY_AIR_LOCK] =
    {
        .name = _("AIR LOCK"),
        .description = COMPOUND_STRING("Negates weather effects."),
    },

};
