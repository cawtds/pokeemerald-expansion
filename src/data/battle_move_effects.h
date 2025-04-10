#include "battle_scripts.h"

const struct BattleMoveEffect gBattleMoveEffects[NUM_BATTLE_MOVE_EFFECTS] =
{
    [EFFECT_HIT] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_SLEEP] =
    {
        .battleScript = BattleScript_EffectSleep,
        .battleTvScore = 1,
    },

    [EFFECT_POISON_HIT] =
    {
        .battleScript = BattleScript_EffectPoisonHit,
        .battleTvScore = 1,
    },

    [EFFECT_ABSORB] =
    {
        .battleScript = BattleScript_EffectAbsorb,
        .battleTvScore = 4,
    },

    [EFFECT_BURN_HIT] =
    {
        .battleScript = BattleScript_EffectBurnHit,
        .battleTvScore = 1,
    },

    [EFFECT_FREEZE_HIT] =
    {
        .battleScript = BattleScript_EffectFreezeHit,
        .battleTvScore = 1,
    },

    [EFFECT_PARALYZE_HIT] =
    {
        .battleScript = BattleScript_EffectParalyzeHit,
        .battleTvScore = 1,
    },

    [EFFECT_EXPLOSION] =
    {
        .battleScript = BattleScript_EffectExplosion,
        .battleTvScore = 0,
    },

    [EFFECT_DREAM_EATER] =
    {
        .battleScript = BattleScript_EffectDreamEater,
        .battleTvScore = 5,
    },

    [EFFECT_MIRROR_MOVE] =
    {
        .battleScript = BattleScript_EffectMirrorMove,
        .battleTvScore = 1,
    },

    [EFFECT_ATTACK_UP] =
    {
        .battleScript = BattleScript_EffectAttackUp,
        .battleTvScore = 1,
    },

    [EFFECT_DEFENSE_UP] =
    {
        .battleScript = BattleScript_EffectDefenseUp,
        .battleTvScore = 1,
    },

    [EFFECT_SPEED_UP] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_SPECIAL_ATTACK_UP] =
    {
        .battleScript = BattleScript_EffectSpecialAttackUp,
        .battleTvScore = 1,
    },

    [EFFECT_SPECIAL_DEFENSE_UP] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_ACCURACY_UP] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_EVASION_UP] =
    {
        .battleScript = BattleScript_EffectEvasionUp,
        .battleTvScore = 1,
    },

    [EFFECT_ALWAYS_HIT] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 2,
    },

    [EFFECT_ATTACK_DOWN] =
    {
        .battleScript = BattleScript_EffectAttackDown,
        .battleTvScore = 1,
    },

    [EFFECT_DEFENSE_DOWN] =
    {
        .battleScript = BattleScript_EffectDefenseDown,
        .battleTvScore = 1,
    },

    [EFFECT_SPEED_DOWN] =
    {
        .battleScript = BattleScript_EffectSpeedDown,
        .battleTvScore = 1,
    },

    [EFFECT_SPECIAL_ATTACK_DOWN] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_SPECIAL_DEFENSE_DOWN] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_ACCURACY_DOWN] =
    {
        .battleScript = BattleScript_EffectAccuracyDown,
        .battleTvScore = 1,
    },

    [EFFECT_EVASION_DOWN] =
    {
        .battleScript = BattleScript_EffectEvasionDown,
        .battleTvScore = 1,
    },

    [EFFECT_HAZE] =
    {
        .battleScript = BattleScript_EffectHaze,
        .battleTvScore = 5,
    },

    [EFFECT_BIDE] =
    {
        .battleScript = BattleScript_EffectBide,
        .battleTvScore = 5,
    },

    [EFFECT_RAMPAGE] =
    {
        .battleScript = BattleScript_EffectRampage,
        .battleTvScore = 4,
    },

    [EFFECT_ROAR] =
    {
        .battleScript = BattleScript_EffectRoar,
        .battleTvScore = 5,
    },

    [EFFECT_MULTI_HIT] =
    {
        .battleScript = BattleScript_EffectMultiHit,
        .battleTvScore = 1,
    },

    [EFFECT_CONVERSION] =
    {
        .battleScript = BattleScript_EffectConversion,
        .battleTvScore = 3,
    },

    [EFFECT_FLINCH_HIT] =
    {
        .battleScript = BattleScript_EffectFlinchHit,
        .battleTvScore = 1,
    },

    [EFFECT_RESTORE_HP] =
    {
        .battleScript = BattleScript_EffectRestoreHp,
        .battleTvScore = 3,
    },

    [EFFECT_TOXIC] =
    {
        .battleScript = BattleScript_EffectToxic,
        .battleTvScore = 5,
    },

    [EFFECT_PAY_DAY] =
    {
        .battleScript = BattleScript_EffectPayDay,
        .battleTvScore = 1,
    },

    [EFFECT_LIGHT_SCREEN] =
    {
        .battleScript = BattleScript_EffectLightScreen,
        .battleTvScore = 7,
    },

    [EFFECT_TRI_ATTACK] =
    {
        .battleScript = BattleScript_EffectTriAttack,
        .battleTvScore = 1,
    },

    [EFFECT_REST] =
    {
        .battleScript = BattleScript_EffectRest,
        .battleTvScore = 7,
    },

    [EFFECT_OHKO] =
    {
        .battleScript = BattleScript_EffectOHKO,
        .battleTvScore = 7,
    },

    [EFFECT_RAZOR_WIND] =
    {
        .battleScript = BattleScript_EffectRazorWind,
        .battleTvScore = 1,
    },

    [EFFECT_SUPER_FANG] =
    {
        .battleScript = BattleScript_EffectSuperFang,
        .battleTvScore = 5,
    },

    [EFFECT_DRAGON_RAGE] =
    {
        .battleScript = BattleScript_EffectDragonRage,
        .battleTvScore = 2,
    },

    [EFFECT_TRAP] =
    {
        .battleScript = BattleScript_EffectTrap,
        .battleTvScore = 4,
    },

    [EFFECT_HIGH_CRITICAL] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_DOUBLE_HIT] =
    {
        .battleScript = BattleScript_EffectDoubleHit,
        .battleTvScore = 1,
    },

    [EFFECT_RECOIL_IF_MISS] =
    {
        .battleScript = BattleScript_EffectRecoilIfMiss,
        .battleTvScore = 1,
    },

    [EFFECT_MIST] =
    {
        .battleScript = BattleScript_EffectMist,
        .battleTvScore = 5,
    },

    [EFFECT_FOCUS_ENERGY] =
    {
        .battleScript = BattleScript_EffectFocusEnergy,
        .battleTvScore = 1,
    },

    [EFFECT_RECOIL] =
    {
        .battleScript = BattleScript_EffectRecoil,
        .battleTvScore = 2,
    },

    [EFFECT_CONFUSE] =
    {
        .battleScript = BattleScript_EffectConfuse,
        .battleTvScore = 4,
    },

    [EFFECT_ATTACK_UP_2] =
    {
        .battleScript = BattleScript_EffectAttackUp2,
        .battleTvScore = 1,
    },

    [EFFECT_DEFENSE_UP_2] =
    {
        .battleScript = BattleScript_EffectDefenseUp2,
        .battleTvScore = 1,
    },

    [EFFECT_SPEED_UP_2] =
    {
        .battleScript = BattleScript_EffectSpeedUp2,
        .battleTvScore = 1,
    },

    [EFFECT_SPECIAL_ATTACK_UP_2] =
    {
        .battleScript = BattleScript_EffectSpecialAttackUp2,
        .battleTvScore = 1,
    },

    [EFFECT_SPECIAL_DEFENSE_UP_2] =
    {
        .battleScript = BattleScript_EffectSpecialDefenseUp2,
        .battleTvScore = 1,
    },

    [EFFECT_ACCURACY_UP_2] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_EVASION_UP_2] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_TRANSFORM] =
    {
        .battleScript = BattleScript_EffectTransform,
        .battleTvScore = 0,
    },

    [EFFECT_ATTACK_DOWN_2] =
    {
        .battleScript = BattleScript_EffectAttackDown2,
        .battleTvScore = 1,
    },

    [EFFECT_DEFENSE_DOWN_2] =
    {
        .battleScript = BattleScript_EffectDefenseDown2,
        .battleTvScore = 1,
    },

    [EFFECT_SPEED_DOWN_2] =
    {
        .battleScript = BattleScript_EffectSpeedDown2,
        .battleTvScore = 1,
    },

    [EFFECT_SPECIAL_ATTACK_DOWN_2] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_SPECIAL_DEFENSE_DOWN_2] =
    {
        .battleScript = BattleScript_EffectSpecialDefenseDown2,
        .battleTvScore = 1,
    },

    [EFFECT_ACCURACY_DOWN_2] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_EVASION_DOWN_2] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_REFLECT] =
    {
        .battleScript = BattleScript_EffectReflect,
        .battleTvScore = 7,
    },

    [EFFECT_POISON] =
    {
        .battleScript = BattleScript_EffectPoison,
        .battleTvScore = 4,
    },

    [EFFECT_PARALYZE] =
    {
        .battleScript = BattleScript_EffectParalyze,
        .battleTvScore = 4,
    },

    [EFFECT_ATTACK_DOWN_HIT] =
    {
        .battleScript = BattleScript_EffectAttackDownHit,
        .battleTvScore = 1,
    },

    [EFFECT_DEFENSE_DOWN_HIT] =
    {
        .battleScript = BattleScript_EffectDefenseDownHit,
        .battleTvScore = 1,
    },

    [EFFECT_SPEED_DOWN_HIT] =
    {
        .battleScript = BattleScript_EffectSpeedDownHit,
        .battleTvScore = 1,
    },

    [EFFECT_SPECIAL_ATTACK_DOWN_HIT] =
    {
        .battleScript = BattleScript_EffectSpecialAttackDownHit,
        .battleTvScore = 1,
    },

    [EFFECT_SPECIAL_DEFENSE_DOWN_HIT] =
    {
        .battleScript = BattleScript_EffectSpecialDefenseDownHit,
        .battleTvScore = 1,
    },

    [EFFECT_ACCURACY_DOWN_HIT] =
    {
        .battleScript = BattleScript_EffectAccuracyDownHit,
        .battleTvScore = 1,
    },

    [EFFECT_EVASION_DOWN_HIT] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_SKY_ATTACK] =
    {
        .battleScript = BattleScript_EffectSkyAttack,
        .battleTvScore = 4,
    },

    [EFFECT_CONFUSE_HIT] =
    {
        .battleScript = BattleScript_EffectConfuseHit,
        .battleTvScore = 1,
    },

    [EFFECT_TWINEEDLE] =
    {
        .battleScript = BattleScript_EffectTwineedle,
        .battleTvScore = 1,
    },

    [EFFECT_VITAL_THROW] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_SUBSTITUTE] =
    {
        .battleScript = BattleScript_EffectSubstitute,
        .battleTvScore = 4,
    },

    [EFFECT_RECHARGE] =
    {
        .battleScript = BattleScript_EffectRecharge,
        .battleTvScore = 5,
    },

    [EFFECT_RAGE] =
    {
        .battleScript = BattleScript_EffectRage,
        .battleTvScore = 2,
    },

    [EFFECT_MIMIC] =
    {
        .battleScript = BattleScript_EffectMimic,
        .battleTvScore = 4,
    },

    [EFFECT_METRONOME] =
    {
        .battleScript = BattleScript_EffectMetronome,
        .battleTvScore = 1,
    },

    [EFFECT_LEECH_SEED] =
    {
        .battleScript = BattleScript_EffectLeechSeed,
        .battleTvScore = 4,
    },

    [EFFECT_SPLASH] =
    {
        .battleScript = BattleScript_EffectSplash,
        .battleTvScore = 1,
    },

    [EFFECT_DISABLE] =
    {
        .battleScript = BattleScript_EffectDisable,
        .battleTvScore = 7,
    },

    [EFFECT_LEVEL_DAMAGE] =
    {
        .battleScript = BattleScript_EffectLevelDamage,
        .battleTvScore = 2,
    },

    [EFFECT_PSYWAVE] =
    {
        .battleScript = BattleScript_EffectPsywave,
        .battleTvScore = 1,
    },

    [EFFECT_COUNTER] =
    {
        .battleScript = BattleScript_EffectCounter,
        .battleTvScore = 5,
    },

    [EFFECT_ENCORE] =
    {
        .battleScript = BattleScript_EffectEncore,
        .battleTvScore = 7,
    },

    [EFFECT_PAIN_SPLIT] =
    {
        .battleScript = BattleScript_EffectPainSplit,
        .battleTvScore = 3,
    },

    [EFFECT_SNORE] =
    {
        .battleScript = BattleScript_EffectSnore,
        .battleTvScore = 3,
    },

    [EFFECT_CONVERSION_2] =
    {
        .battleScript = BattleScript_EffectConversion2,
        .battleTvScore = 4,
    },

    [EFFECT_LOCK_ON] =
    {
        .battleScript = BattleScript_EffectLockOn,
        .battleTvScore = 3,
    },

    [EFFECT_SKETCH] =
    {
        .battleScript = BattleScript_EffectSketch,
        .battleTvScore = 3,
    },

    [EFFECT_UNUSED_60] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 3,
    },

    [EFFECT_SLEEP_TALK] =
    {
        .battleScript = BattleScript_EffectSleepTalk,
        .battleTvScore = 3,
    },

    [EFFECT_DESTINY_BOND] =
    {
        .battleScript = BattleScript_EffectDestinyBond,
        .battleTvScore = 3,
    },

    [EFFECT_FLAIL] =
    {
        .battleScript = BattleScript_EffectFlail,
        .battleTvScore = 2,
    },

    [EFFECT_SPITE] =
    {
        .battleScript = BattleScript_EffectSpite,
        .battleTvScore = 4,
    },

    [EFFECT_FALSE_SWIPE] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_HEAL_BELL] =
    {
        .battleScript = BattleScript_EffectHealBell,
        .battleTvScore = 5,
    },

    [EFFECT_QUICK_ATTACK] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_TRIPLE_KICK] =
    {
        .battleScript = BattleScript_EffectTripleKick,
        .battleTvScore = 1,
    },

    [EFFECT_THIEF] =
    {
        .battleScript = BattleScript_EffectThief,
        .battleTvScore = 4,
    },

    [EFFECT_MEAN_LOOK] =
    {
        .battleScript = BattleScript_EffectMeanLook,
        .battleTvScore = 5,
    },

    [EFFECT_NIGHTMARE] =
    {
        .battleScript = BattleScript_EffectNightmare,
        .battleTvScore = 3,
    },

    [EFFECT_MINIMIZE] =
    {
        .battleScript = BattleScript_EffectMinimize,
        .battleTvScore = 1,
    },

    [EFFECT_CURSE] =
    {
        .battleScript = BattleScript_EffectCurse,
        .battleTvScore = 2,
    },

    [EFFECT_UNUSED_6E] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_PROTECT] =
    {
        .battleScript = BattleScript_EffectProtect,
        .battleTvScore = 5,
    },

    [EFFECT_SPIKES] =
    {
        .battleScript = BattleScript_EffectSpikes,
        .battleTvScore = 4,
    },

    [EFFECT_FORESIGHT] =
    {
        .battleScript = BattleScript_EffectForesight,
        .battleTvScore = 3,
    },

    [EFFECT_PERISH_SONG] =
    {
        .battleScript = BattleScript_EffectPerishSong,
        .battleTvScore = 6,
    },

    [EFFECT_SANDSTORM] =
    {
        .battleScript = BattleScript_EffectSandstorm,
        .battleTvScore = 4,
    },

    [EFFECT_ENDURE] =
    {
        .battleScript = BattleScript_EffectEndure,
        .battleTvScore = 3,
    },

    [EFFECT_ROLLOUT] =
    {
        .battleScript = BattleScript_EffectRollout,
        .battleTvScore = 3,
    },

    [EFFECT_SWAGGER] =
    {
        .battleScript = BattleScript_EffectSwagger,
        .battleTvScore = 3,
    },

    [EFFECT_FURY_CUTTER] =
    {
        .battleScript = BattleScript_EffectFuryCutter,
        .battleTvScore = 2,
    },

    [EFFECT_ATTRACT] =
    {
        .battleScript = BattleScript_EffectAttract,
        .battleTvScore = 4,
    },

    [EFFECT_RETURN] =
    {
        .battleScript = BattleScript_EffectReturn,
        .battleTvScore = 1,
    },

    [EFFECT_PRESENT] =
    {
        .battleScript = BattleScript_EffectPresent,
        .battleTvScore = 1,
    },

    [EFFECT_FRUSTRATION] =
    {
        .battleScript = BattleScript_EffectFrustration,
        .battleTvScore = 1,
    },

    [EFFECT_SAFEGUARD] =
    {
        .battleScript = BattleScript_EffectSafeguard,
        .battleTvScore = 5,
    },

    [EFFECT_THAW_HIT] =
    {
        .battleScript = BattleScript_EffectThawHit,
        .battleTvScore = 1,
    },

    [EFFECT_MAGNITUDE] =
    {
        .battleScript = BattleScript_EffectMagnitude,
        .battleTvScore = 1,
    },

    [EFFECT_BATON_PASS] =
    {
        .battleScript = BattleScript_EffectBatonPass,
        .battleTvScore = 7,
    },

    [EFFECT_PURSUIT] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 2,
    },

    [EFFECT_RAPID_SPIN] =
    {
        .battleScript = BattleScript_EffectRapidSpin,
        .battleTvScore = 2,
    },

    [EFFECT_SONICBOOM] =
    {
        .battleScript = BattleScript_EffectSonicboom,
        .battleTvScore = 1,
    },

    [EFFECT_UNUSED_83] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_MORNING_SUN] =
    {
        .battleScript = BattleScript_EffectMorningSun,
        .battleTvScore = 4,
    },

    [EFFECT_SYNTHESIS] =
    {
        .battleScript = BattleScript_EffectSynthesis,
        .battleTvScore = 4,
    },

    [EFFECT_MOONLIGHT] =
    {
        .battleScript = BattleScript_EffectMoonlight,
        .battleTvScore = 4,
    },

    [EFFECT_HIDDEN_POWER] =
    {
        .battleScript = BattleScript_EffectHiddenPower,
        .battleTvScore = 1,
    },

    [EFFECT_RAIN_DANCE] =
    {
        .battleScript = BattleScript_EffectRainDance,
        .battleTvScore = 4,
    },

    [EFFECT_SUNNY_DAY] =
    {
        .battleScript = BattleScript_EffectSunnyDay,
        .battleTvScore = 4,
    },

    [EFFECT_DEFENSE_UP_HIT] =
    {
        .battleScript = BattleScript_EffectDefenseUpHit,
        .battleTvScore = 1,
    },

    [EFFECT_ATTACK_UP_HIT] =
    {
        .battleScript = BattleScript_EffectAttackUpHit,
        .battleTvScore = 1,
    },

    [EFFECT_ALL_STATS_UP_HIT] =
    {
        .battleScript = BattleScript_EffectAllStatsUpHit,
        .battleTvScore = 1,
    },

    [EFFECT_UNUSED_8D] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_BELLY_DRUM] =
    {
        .battleScript = BattleScript_EffectBellyDrum,
        .battleTvScore = 7,
    },

    [EFFECT_PSYCH_UP] =
    {
        .battleScript = BattleScript_EffectPsychUp,
        .battleTvScore = 7,
    },

    [EFFECT_MIRROR_COAT] =
    {
        .battleScript = BattleScript_EffectMirrorCoat,
        .battleTvScore = 6,
    },

    [EFFECT_SKULL_BASH] =
    {
        .battleScript = BattleScript_EffectSkullBash,
        .battleTvScore = 3,
    },

    [EFFECT_TWISTER] =
    {
        .battleScript = BattleScript_EffectTwister,
        .battleTvScore = 1,
    },

    [EFFECT_EARTHQUAKE] =
    {
        .battleScript = BattleScript_EffectEarthquake,
        .battleTvScore = 1,
    },

    [EFFECT_FUTURE_SIGHT] =
    {
        .battleScript = BattleScript_EffectFutureSight,
        .battleTvScore = 1,
    },

    [EFFECT_GUST] =
    {
        .battleScript = BattleScript_EffectGust,
        .battleTvScore = 1,
    },

    [EFFECT_FLINCH_MINIMIZE_HIT] =
    {
        .battleScript = BattleScript_EffectStomp,
        .battleTvScore = 1,
    },

    [EFFECT_SOLAR_BEAM] =
    {
        .battleScript = BattleScript_EffectSolarBeam,
        .battleTvScore = 1,
    },

    [EFFECT_THUNDER] =
    {
        .battleScript = BattleScript_EffectThunder,
        .battleTvScore = 1,
    },

    [EFFECT_TELEPORT] =
    {
        .battleScript = BattleScript_EffectTeleport,
        .battleTvScore = 1,
    },

    [EFFECT_BEAT_UP] =
    {
        .battleScript = BattleScript_EffectBeatUp,
        .battleTvScore = 2,
    },

    [EFFECT_SEMI_INVULNERABLE] =
    {
        .battleScript = BattleScript_EffectSemiInvulnerable,
        .battleTvScore = 3,
    },

    [EFFECT_DEFENSE_CURL] =
    {
        .battleScript = BattleScript_EffectDefenseCurl,
        .battleTvScore = 1,
    },

    [EFFECT_SOFTBOILED] =
    {
        .battleScript = BattleScript_EffectSoftboiled,
        .battleTvScore = 1,
    },

    [EFFECT_FAKE_OUT] =
    {
        .battleScript = BattleScript_EffectFakeOut,
        .battleTvScore = 4,
    },

    [EFFECT_UPROAR] =
    {
        .battleScript = BattleScript_EffectUproar,
        .battleTvScore = 4,
    },

    [EFFECT_STOCKPILE] =
    {
        .battleScript = BattleScript_EffectStockpile,
        .battleTvScore = 3,
    },

    [EFFECT_SPIT_UP] =
    {
        .battleScript = BattleScript_EffectSpitUp,
        .battleTvScore = 3,
    },

    [EFFECT_SWALLOW] =
    {
        .battleScript = BattleScript_EffectSwallow,
        .battleTvScore = 3,
    },

    [EFFECT_UNUSED_A3] =
    {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },

    [EFFECT_HAIL] =
    {
        .battleScript = BattleScript_EffectHail,
        .battleTvScore = 4,
    },

    [EFFECT_TORMENT] =
    {
        .battleScript = BattleScript_EffectTorment,
        .battleTvScore = 7,
    },

    [EFFECT_FLATTER] =
    {
        .battleScript = BattleScript_EffectFlatter,
        .battleTvScore = 7,
    },

    [EFFECT_WILL_O_WISP] =
    {
        .battleScript = BattleScript_EffectWillOWisp,
        .battleTvScore = 5,
    },

    [EFFECT_MEMENTO] =
    {
        .battleScript = BattleScript_EffectMemento,
        .battleTvScore = 7,
    },

    [EFFECT_FACADE] =
    {
        .battleScript = BattleScript_EffectFacade,
        .battleTvScore = 1,
    },

    [EFFECT_FOCUS_PUNCH] =
    {
        .battleScript = BattleScript_EffectFocusPunch,
        .battleTvScore = 7,
    },

    [EFFECT_SMELLINGSALT] =
    {
        .battleScript = BattleScript_EffectSmellingsalt,
        .battleTvScore = 1,
    },

    [EFFECT_FOLLOW_ME] =
    {
        .battleScript = BattleScript_EffectFollowMe,
        .battleTvScore = 5,
    },

    [EFFECT_NATURE_POWER] =
    {
        .battleScript = BattleScript_EffectNaturePower,
        .battleTvScore = 0,
    },

    [EFFECT_CHARGE] =
    {
        .battleScript = BattleScript_EffectCharge,
        .battleTvScore = 4,
    },

    [EFFECT_TAUNT] =
    {
        .battleScript = BattleScript_EffectTaunt,
        .battleTvScore = 4,
    },

    [EFFECT_HELPING_HAND] =
    {
        .battleScript = BattleScript_EffectHelpingHand,
        .battleTvScore = 4,
    },

    [EFFECT_TRICK] =
    {
        .battleScript = BattleScript_EffectTrick,
        .battleTvScore = 4,
    },

    [EFFECT_ROLE_PLAY] =
    {
        .battleScript = BattleScript_EffectRolePlay,
        .battleTvScore = 4,
    },

    [EFFECT_WISH] =
    {
        .battleScript = BattleScript_EffectWish,
        .battleTvScore = 2,
    },

    [EFFECT_ASSIST] =
    {
        .battleScript = BattleScript_EffectAssist,
        .battleTvScore = 2,
    },

    [EFFECT_INGRAIN] =
    {
        .battleScript = BattleScript_EffectIngrain,
        .battleTvScore = 6,
    },

    [EFFECT_SUPERPOWER] =
    {
        .battleScript = BattleScript_EffectSuperpower,
        .battleTvScore = 3,
    },

    [EFFECT_MAGIC_COAT] =
    {
        .battleScript = BattleScript_EffectMagicCoat,
        .battleTvScore = 6,
    },

    [EFFECT_RECYCLE] =
    {
        .battleScript = BattleScript_EffectRecycle,
        .battleTvScore = 4,
    },

    [EFFECT_REVENGE] =
    {
        .battleScript = BattleScript_EffectRevenge,
        .battleTvScore = 4,
    },

    [EFFECT_BRICK_BREAK] =
    {
        .battleScript = BattleScript_EffectBrickBreak,
        .battleTvScore = 2,
    },

    [EFFECT_YAWN] =
    {
        .battleScript = BattleScript_EffectYawn,
        .battleTvScore = 5,
    },

    [EFFECT_KNOCK_OFF] =
    {
        .battleScript = BattleScript_EffectKnockOff,
        .battleTvScore = 2,
    },

    [EFFECT_ENDEAVOR] =
    {
        .battleScript = BattleScript_EffectEndeavor,
        .battleTvScore = 1,
    },

    [EFFECT_ERUPTION] =
    {
        .battleScript = BattleScript_EffectEruption,
        .battleTvScore = 1,
    },

    [EFFECT_SKILL_SWAP] =
    {
        .battleScript = BattleScript_EffectSkillSwap,
        .battleTvScore = 6,
    },

    [EFFECT_IMPRISON] =
    {
        .battleScript = BattleScript_EffectImprison,
        .battleTvScore = 6,
    },

    [EFFECT_REFRESH] =
    {
        .battleScript = BattleScript_EffectRefresh,
        .battleTvScore = 6,
    },

    [EFFECT_GRUDGE] =
    {
        .battleScript = BattleScript_EffectGrudge,
        .battleTvScore = 1,
    },

    [EFFECT_SNATCH] =
    {
        .battleScript = BattleScript_EffectSnatch,
        .battleTvScore = 1,
    },

    [EFFECT_LOW_KICK] =
    {
        .battleScript = BattleScript_EffectLowKick,
        .battleTvScore = 1,
    },

    [EFFECT_SECRET_POWER] =
    {
        .battleScript = BattleScript_EffectSecretPower,
        .battleTvScore = 1,
    },

    [EFFECT_DOUBLE_EDGE] =
    {
        .battleScript = BattleScript_EffectDoubleEdge,
        .battleTvScore = 2,
    },

    [EFFECT_TEETER_DANCE] =
    {
        .battleScript = BattleScript_EffectTeeterDance,
        .battleTvScore = 6,
    },

    [EFFECT_BLAZE_KICK] =
    {
        .battleScript = BattleScript_EffectBurnHit,
        .battleTvScore = 1,
    },

    [EFFECT_MUD_SPORT] =
    {
        .battleScript = BattleScript_EffectMudSport,
        .battleTvScore = 4,
    },

    [EFFECT_POISON_FANG] =
    {
        .battleScript = BattleScript_EffectPoisonFang,
        .battleTvScore = 1,
    },

    [EFFECT_WEATHER_BALL] =
    {
        .battleScript = BattleScript_EffectWeatherBall,
        .battleTvScore = 1,
    },

    [EFFECT_OVERHEAT] =
    {
        .battleScript = BattleScript_EffectOverheat,
        .battleTvScore = 3,
    },

    [EFFECT_TICKLE] =
    {
        .battleScript = BattleScript_EffectTickle,
        .battleTvScore = 1,
    },

    [EFFECT_COSMIC_POWER] =
    {
        .battleScript = BattleScript_EffectCosmicPower,
        .battleTvScore = 1,
    },

    [EFFECT_SKY_UPPERCUT] =
    {
        .battleScript = BattleScript_EffectSkyUppercut,
        .battleTvScore = 1,
    },

    [EFFECT_BULK_UP] =
    {
        .battleScript = BattleScript_EffectBulkUp,
        .battleTvScore = 1,
    },

    [EFFECT_POISON_TAIL] =
    {
        .battleScript = BattleScript_EffectPoisonHit,
        .battleTvScore = 1,
    },

    [EFFECT_WATER_SPORT] =
    {
        .battleScript = BattleScript_EffectWaterSport,
        .battleTvScore = 4,
    },

    [EFFECT_CALM_MIND] =
    {
        .battleScript = BattleScript_EffectCalmMind,
        .battleTvScore = 1,
    },

    [EFFECT_DRAGON_DANCE] =
    {
        .battleScript = BattleScript_EffectDragonDance,
        .battleTvScore = 1,
    },

    [EFFECT_CAMOUFLAGE] =
    {
        .battleScript = BattleScript_EffectCamouflage,
        .battleTvScore = 3,
    },

};
