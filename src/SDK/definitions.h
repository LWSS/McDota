#pragma once

/* generic constants */
#define LIFE_ALIVE 0

/* Inspired by: https://github.com/DustinHLand/vkDOOM3/blob/master/neo/renderer/Vulkan/RenderBackend_VK.cpp#L91 */
#define CASE_STRING( x ) case static_cast<int>( x ) : return #x
#define CASE_STD_STRING( x ) case static_cast<int>( x ) : return std::string(#x)

typedef unsigned long long VPANEL;
typedef unsigned long long HFont;

class ICommandLine;
class KeyValues;
class CBaseClientState;
struct CGlowObjectManager;
class CDotaPlayer;

enum ClientFrameStage_t : int
{
	// (haven't run any frames yet)
	FRAME_UNDEFINED = -1,
	FRAME_START,
	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,
	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

enum class EClassIds : int
{
	CAdditionalWearable = 0,
	C_AI_BaseNPC = 1,
	C_BaseAnimating = 1,
	C_BaseAnimatingOverlay = 2,
	C_BaseAttributableItem = 3,
	C_BaseButton = 4,
	C_BaseClientUIEntity = 5,
	C_BaseCombatCharacter = 6,
	C_BaseCombatWeapon = 7,
	C_BaseDoor = 8,
	C_BaseEntity = 9,
	C_BaseFlex = 10,
	C_BaseModelEntity = 11,
	C_BasePlayer = 12,
	C_BasePropDoor = 13,
	C_BaseTeamObjectiveResource = 15,
	C_BaseToggle = 14,
	C_BaseTrigger = 15,
	C_BaseViewModel = 16,
	C_BaseVRHandAttachment = 17,
	C_Beam = 18,
	C_BeamSpotLight = 21,
	C_Breakable = 19,
	C_BreakableProp = 20,
	C_ButtonTimed = 21,
	C_ColorCorrection = 22,
	C_ColorCorrectionVolume = 23,
	C_DevtestHierarchy = 24,
	C_DOTA_Ability_Abaddon_DeathCoil = 25,
	CDOTA_Ability_AbyssalUnderlord_DarkRift = 26,
	CDOTA_Ability_AbyssalUnderlord_Firestorm = 27,
	CDOTA_Ability_AbyssalUnderlord_PitOfMalice = 28,
	CDOTA_Ability_Alchemist_AcidSpray = 29,
	C_DOTA_Ability_Alchemist_UnstableConcoction = 30,
	CDOTA_Ability_Alchemist_UnstableConcoctionThrow = 31,
	CDOTA_Ability_AncientApparition_ChillingTouch = 32,
	CDOTA_Ability_AncientApparition_ColdFeet = 33,
	CDOTA_Ability_AncientApparition_IceBlast = 34,
	CDOTA_Ability_AncientApparition_IceVortex = 35,
	C_DOTA_Ability_AntiMage_Blink = 36,
	C_DOTA_Ability_AntiMage_ManaVoid = 37,
	C_DOTA_Ability_AntiMage_SpellShield = 38,
	C_DOTA_Ability_ArcWarden_Flux = 39,
	C_DOTA_Ability_ArcWarden_MagneticField = 40,
	C_DOTA_Ability_ArcWarden_SparkWraith = 41,
	C_DOTA_Ability_ArcWarden_TempestDouble = 42,
	C_DOTA_Ability_AttributeBonus = 43,
	C_DOTA_Ability_Axe_BerserkersCall = 44,
	C_DOTA_Ability_Axe_CounterHelix = 45,
	C_DOTA_Ability_Axe_CullingBlade = 46,
	C_DOTA_Ability_Bane_BrainSap = 47,
	C_DOTA_Ability_Bane_FiendsGrip = 48,
	C_DOTA_Ability_Batrider_Flamebreak = 49,
	C_DOTA_Ability_Batrider_StickyNapalm = 50,
	CDOTA_Ability_Beastmaster_PrimalRoar = 51,
	C_DOTA_Ability_BlackDragon_Fireball = 52,
	CDOTA_Ability_Bloodseeker_Bloodbath = 53,
	C_DOTA_Ability_BountyHunter_Jinada = 54,
	C_DOTA_Ability_BountyHunter_ShurikenToss = 55,
	C_DOTA_Ability_Brewmaster_DispelMagic = 56,
	C_DOTA_Ability_Brewmaster_DrunkenBrawler = 57,
	C_DOTA_Ability_Brewmaster_DrunkenHaze = 58,
	C_DOTA_Ability_Brewmaster_PermanentImmolation = 59,
	C_DOTA_Ability_Brewmaster_PrimalSplit = 60,
	C_DOTA_Ability_Brewmaster_ThunderClap = 61,
	C_DOTA_Ability_Bristleback_QuillSpray = 62,
	C_DOTA_Ability_Bristleback_ViscousNasalGoo = 63,
	C_DOTA_Ability_Broodmother_SpinWeb = 64,
	C_DOTA_Ability_Centaur_HoofStomp = 65,
	CDOTA_Ability_Centaur_Stampede = 66,
	C_DOTA_Ability_ChaosKnight_Phantasm = 67,
	C_DOTA_Ability_ChaosKnight_Reality_Rift = 68,
	C_DOTA_Ability_Chen_HandOfGod = 69,
	C_DOTA_Ability_Chen_HolyPersuasion = 70,
	C_DOTA_Ability_Chen_TestOfFaith = 71,
	C_DOTA_Ability_Chen_TestOfFaithTeleport = 72,
	C_DOTA_Ability_Courier_TakeStashAndTransferItems = 73,
	C_DOTA_Ability_Courier_TakeStashItems = 74,
	C_DOTA_Ability_Courier_TransferItems = 75,
	C_DOTA_Ability_Courier_TransferItems_ToOtherPlayer = 76,
	C_DOTA_Ability_CrystalMaiden_CrystalNova = 77,
	C_DOTA_Ability_CrystalMaiden_FreezingField = 78,
	C_DOTA_Ability_DarkSeer_Surge = 79,
	C_DOTA_Ability_DarkSeer_Vacuum = 80,
	C_DOTA_Ability_DarkWillow_Bedlam = 81,
	C_DOTA_Ability_DarkWillow_BrambleMaze = 82,
	C_DOTA_Ability_DarkWillow_ShadowRealm = 83,
	C_DOTA_Ability_DarkWillow_Terrorize = 84,
	C_DOTA_Ability_DataDriven = 85,
	C_DOTA_Ability_Dazzle_Poison_Touch = 86,
	C_DOTA_Ability_Dazzle_ShadowWave = 87,
	C_DOTA_Ability_Dazzle_Shallow_Grave = 88,
	C_DOTA_Ability_Dazzle_Weave = 89,
	C_DOTA_Ability_DeathProphet_CarrionSwarm = 90,
	C_DOTA_Ability_DeathProphet_Exorcism = 91,
	C_DOTA_Ability_DeathProphet_Silence = 92,
	C_DOTA_Ability_Disruptor_Glimpse = 93,
	C_DOTA_Ability_Disruptor_KineticField = 94,
	C_DOTA_Ability_Disruptor_StaticStorm = 95,
	C_DOTA_Ability_DoomBringer_Devour = 96,
	C_DOTA_Ability_DoomBringer_InfernalBlade = 97,
	C_DOTA_Ability_DragonKnight_BreatheFire = 98,
	C_DOTA_Ability_DrowRanger_Silence = 99,
	C_DOTA_Ability_DrowRanger_WaveOfSilence = 100,
	C_DOTA_Ability_Earthshaker_Aftershock = 101,
	C_DOTA_Ability_Earthshaker_EnchantTotem = 102,
	C_DOTA_Ability_Earthshaker_Fissure = 103,
	C_DOTA_Ability_EarthSpirit_BoulderSmash = 104,
	C_DOTA_Ability_EarthSpirit_GeomagneticGrip = 105,
	CDOTA_Ability_EarthSpirit_Petrify = 106,
	C_DOTA_Ability_EarthSpirit_RollingBoulder = 107,
	C_DOTA_Ability_EarthSpirit_StoneCaller = 108,
	CDOTA_Ability_Elder_Titan_EarthSplitter = 109,
	C_DOTA_Ability_Elder_Titan_NaturalOrder = 110,
	C_DOTA_Ability_Elder_Titan_NaturalOrder_Spirit = 111,
	C_DOTA_Ability_EmberSpirit_Activate_FireRemnant = 112,
	C_DOTA_Ability_EmberSpirit_FireRemnant = 113,
	C_DOTA_Ability_EmberSpirit_SearingChains = 114,
	C_DOTA_Ability_EmberSpirit_SleightOfFist = 115,
	C_DOTA_Ability_Enchantress_Enchant = 116,
	C_DOTA_Ability_Enchantress_Impetus = 117,
	C_DOTA_Ability_Enchantress_NaturesAttendants = 118,
	C_DOTA_Ability_Enchantress_Untouchable = 119,
	C_DOTA_Ability_Enigma_BlackHole = 120,
	C_DOTA_Ability_Enigma_DemonicConversion = 121,
	C_DOTA_Ability_Enigma_MidnightPulse = 122,
	C_DOTA_Ability_FacelessVoid_Chronosphere = 123,
	C_DOTA_Ability_FacelessVoid_TimeDilation = 124,
	C_DOTA_Ability_FacelessVoid_TimeWalk = 125,
	C_DOTA_Ability_Furion_ForceOfNature = 126,
	C_DOTA_Ability_Furion_Sprout = 127,
	C_DOTA_Ability_Furion_Teleportation = 128,
	C_DOTA_Ability_Greevil_Miniboss_Black_BrainSap = 129,
	C_DOTA_Ability_Greevil_Miniboss_Black_Nightmare = 130,
	C_DOTA_Ability_Greevil_Miniboss_Blue_ColdFeet = 131,
	C_DOTA_Ability_Greevil_Miniboss_Blue_IceVortex = 132,
	C_DOTA_Ability_Greevil_Miniboss_Green_LivingArmor = 133,
	C_DOTA_Ability_Greevil_Miniboss_Green_Overgrowth = 134,
	C_DOTA_Ability_Greevil_Miniboss_Orange_DragonSlave = 135,
	C_DOTA_Ability_Greevil_Miniboss_Orange_LightStrikeArray = 136,
	C_DOTA_Ability_Greevil_Miniboss_Purple_PlagueWard = 137,
	C_DOTA_Ability_Greevil_Miniboss_Purple_VenomousGale = 138,
	C_DOTA_Ability_Greevil_Miniboss_Red_Earthshock = 139,
	C_DOTA_Ability_Greevil_Miniboss_Red_Overpower = 140,
	C_DOTA_Ability_Greevil_Miniboss_Sight = 141,
	C_DOTA_Ability_Greevil_Miniboss_White_Degen_Aura = 142,
	C_DOTA_Ability_Greevil_Miniboss_White_Purification = 143,
	C_DOTA_Ability_Greevil_Miniboss_Yellow_IonShell = 144,
	C_DOTA_Ability_Greevil_Miniboss_Yellow_Surge = 145,
	CDOTA_Ability_Gyrocopter_Call_Down = 146,
	C_DOTA_Ability_Gyrocopter_Flak_Cannon = 147,
	C_DOTA_Ability_Gyrocopter_Homing_Missile = 148,
	C_DOTA_Ability_Gyrocopter_Rocket_Barrage = 149,
	C_DOTA_Ability_Healing_Campfire = 150,
	C_DOTA_Ability_Holdout_CullingBlade = 151,
	C_DOTA_Ability_Holdout_GladiatorsUnite = 152,
	C_DOTA_Ability_Holdout_Multishot = 153,
	C_DOTA_Ability_Holdout_Omnislash = 154,
	C_DOTA_Ability_Huskar_Inner_Vitality = 155,
	C_DOTA_Ability_Huskar_Life_Break = 156,
	C_DOTA_Ability_Invoker_Alacrity = 157,
	C_DOTA_Ability_Invoker_AttributeBonus = 158,
	C_DOTA_Ability_Invoker_DeafeningBlast = 159,
	C_DOTA_Ability_Invoker_EMP = 160,
	C_DOTA_Ability_Invoker_GhostWalk = 161,
	C_DOTA_Ability_Invoker_Invoke = 162,
	CDOTA_Ability_Invoker_InvokedBase = 163,
	C_DOTA_Ability_Invoker_SunStrike = 164,
	C_DOTA_Ability_Invoker_Tornado = 165,
	C_DOTA_Ability_Jakiro_DualBreath = 166,
	C_DOTA_Ability_Jakiro_IcePath = 167,
	C_DOTA_Ability_Jakiro_Macropyre = 168,
	C_DOTA_Ability_Juggernaut_BladeFury = 169,
	C_DOTA_Ability_Juggernaut_HealingWard = 170,
	C_DOTA_Ability_Juggernaut_Omnislash = 171,
	C_DOTA_Ability_KeeperOfTheLight_BlindingLight = 172,
	C_DOTA_Ability_KeeperOfTheLight_Illuminate = 173,
	C_DOTA_Ability_KeeperOfTheLight_Recall = 174,
	C_DOTA_Ability_Kunkka_GhostShip = 175,
	C_DOTA_Ability_Kunkka_Tidebringer = 176,
	C_DOTA_Ability_Kunkka_Torrent = 177,
	C_DOTA_Ability_Legion_Commander_MomentOfCourage = 178,
	C_DOTA_Ability_Legion_Commander_OverwhelmingOdds = 179,
	C_DOTA_Ability_Legion_Commander_PressTheAttack = 180,
	C_DOTA_Ability_Leshrac_Diabolic_Edict = 181,
	C_DOTA_Ability_Leshrac_Pulse_Nova = 182,
	C_DOTA_Ability_Leshrac_Split_Earth = 183,
	C_DOTA_Ability_Lich_ChainFrost = 184,
	C_DOTA_Ability_Lich_FrostNova = 185,
	C_DOTA_Ability_Life_Stealer_Infest = 186,
	C_DOTA_Ability_Life_Stealer_Open_Wounds = 187,
	C_DOTA_Ability_Lina_DragonSlave = 188,
	C_DOTA_Ability_Lina_LagunaBlade = 189,
	C_DOTA_Ability_Lina_LightStrikeArray = 190,
	C_DOTA_Ability_Lion_FingerOfDeath = 191,
	C_DOTA_Ability_Lion_Impale = 192,
	C_DOTA_Ability_Lion_ManaDrain = 193,
	C_DOTA_Ability_Lion_Voodoo = 194,
	C_DOTA_Ability_LoneDruid_Rabid = 195,
	C_DOTA_Ability_LoneDruid_SavageRoar = 196,
	C_DOTA_Ability_LoneDruid_SavageRoar_Bear = 197,
	C_DOTA_Ability_LoneDruid_SpiritBear = 198,
	C_DOTA_Ability_LoneDruid_SpiritBear_Entangle = 199,
	C_DOTA_Ability_LoneDruid_SpiritBear_Return = 200,
	C_DOTA_Ability_LoneDruid_TrueForm_BattleCry = 201,
	C_DOTA_Ability_LoneDruid_TrueForm_Druid = 202,
	C_DOTA_Ability_Lua = 203,
	C_DOTA_Ability_Luna_Eclipse = 204,
	C_DOTA_Ability_Luna_LucentBeam = 205,
	C_DOTA_Ability_Luna_LunarBlessing = 206,
	C_DOTA_Ability_Lycan_FeralImpulse = 207,
	C_DOTA_Ability_Lycan_Howl = 208,
	C_DOTA_Ability_Lycan_SummonWolves = 209,
	C_DOTA_Ability_Magnataur_ReversePolarity = 210,
	C_DOTA_Ability_Magnataur_Shockwave = 211,
	C_DOTA_Ability_Magnataur_Skewer = 212,
	C_DOTA_Ability_Medusa_SplitShot = 213,
	C_DOTA_Ability_Meepo_DividedWeStand = 214,
	C_DOTA_Ability_Meepo_Earthbind = 215,
	CDOTA_Ability_Meepo_Poof = 216,
	C_DOTA_Ability_Mirana_Arrow = 217,
	C_DOTA_Ability_Mirana_Leap = 218,
	C_DOTA_Ability_Mirana_MoonlightShadow = 219,
	C_DOTA_Ability_Mirana_Starfall = 220,
	C_DOTA_Ability_MonkeyKing_FurArmy = 221,
	C_DOTA_Ability_MonkeyKing_Spring = 222,
	C_DOTA_Ability_MonkeyKing_TreeDance = 223,
	C_DOTA_Ability_Morphling_AdaptiveStrike_Agi = 224,
	C_DOTA_Ability_Morphling_AdaptiveStrike_Str = 225,
	CDOTA_Ability_Morphling_Hybrid = 226,
	C_DOTA_Ability_Morphling_Replicate = 227,
	C_DOTA_Ability_Morphling_Waveform = 228,
	C_DOTA_Ability_NagaSiren_Ensnare = 229,
	C_DOTA_Ability_NagaSiren_MirrorImage = 230,
	C_DOTA_Ability_NagaSiren_RipTide = 231,
	C_DOTA_Ability_Necrolyte_Death_Pulse = 232,
	C_DOTA_Ability_Necrolyte_ReapersScythe = 233,
	C_DOTA_Ability_Necrolyte_Sadist = 234,
	C_DOTA_Ability_Nevermore_Requiem = 235,
	C_DOTA_Ability_Nevermore_Shadowraze = 236,
	C_DOTA_Ability_Nian_Apocalypse = 237,
	C_DOTA_Ability_Nian_Eruption = 238,
	C_DOTA_Ability_Nian_Frenzy = 239,
	C_DOTA_Ability_Nian_Hurricane = 240,
	C_DOTA_Ability_Nian_Roar = 241,
	C_DOTA_Ability_Nian_Sigils = 242,
	C_DOTA_Ability_Nian_Tail_Swipe = 243,
	C_DOTA_Ability_Nian_Waterball = 244,
	C_DOTA_Ability_Nian_Whirlpool = 245,
	C_DOTA_Ability_NightStalker_CripplingFear = 246,
	C_DOTA_Ability_NightStalker_HunterInTheNight = 247,
	CDOTA_Ability_Nyx_Assassin_Burrow = 248,
	C_DOTA_Ability_Nyx_Assassin_Impale = 249,
	CDOTA_Ability_Nyx_Assassin_ManaBurn = 250,
	C_DOTA_Ability_Obsidian_Destroyer_ArcaneOrb = 251,
	C_DOTA_Ability_Obsidian_Destroyer_AstralImprisonment = 252,
	C_DOTA_Ability_Obsidian_Destroyer_SanityEclipse = 253,
	C_DOTA_Ability_Ogre_Magi_Bloodlust = 254,
	C_DOTA_Ability_Ogre_Magi_Fireblast = 255,
	C_DOTA_Ability_Ogre_Magi_Ignite = 256,
	C_DOTA_Ability_Ogre_Magi_Multicast = 257,
	C_DOTA_Ability_Ogre_Magi_Unrefined_Fireblast = 258,
	C_DOTA_Ability_Omniknight_GuardianAngel = 259,
	C_DOTA_Ability_Omniknight_Purification = 260,
	C_DOTA_Ability_Oracle_FatesEdict = 261,
	C_DOTA_Ability_Oracle_FortunesEnd = 262,
	C_DOTA_Ability_Oracle_PurifyingFlames = 263,
	C_DOTA_Ability_Pangolier_Gyroshell = 264,
	C_DOTA_Ability_Pangolier_GyroshellStop = 265,
	C_DOTA_Ability_Pangolier_ShieldCrash = 266,
	C_DOTA_Ability_Pangolier_Swashbuckle = 267,
	C_DOTA_Ability_PhantomAssassin_PhantomStrike = 268,
	C_DOTA_Ability_PhantomLancer_Doppelwalk = 269,
	C_DOTA_Ability_PhantomLancer_SpiritLance = 270,
	C_DOTA_Ability_Phoenix_LaunchFireSpirit = 271,
	C_DOTA_Ability_Phoenix_Supernova = 272,
	C_DOTA_Ability_Puck_DreamCoil = 273,
	C_DOTA_Ability_Puck_IllusoryOrb = 274,
	C_DOTA_Ability_Puck_WaningRift = 275,
	CDOTA_Ability_Pudge_Dismember = 276,
	C_DOTA_Ability_Pudge_FleshHeap = 277,
	CDOTA_Ability_Pudge_MeatHook = 278,
	C_DOTA_Ability_Pudge_Rot = 279,
	C_DOTA_Ability_Pugna_Decrepify = 280,
	C_DOTA_Ability_Pugna_LifeDrain = 281,
	C_DOTA_Ability_Pugna_NetherBlast = 282,
	C_DOTA_Ability_Pugna_NetherWard = 283,
	C_DOTA_Ability_QueenOfPain_Blink = 284,
	C_DOTA_Ability_QueenOfPain_ScreamOfPain = 285,
	C_DOTA_Ability_QueenOfPain_ShadowStrike = 286,
	C_DOTA_Ability_QueenOfPain_SonicWave = 287,
	C_DOTA_Ability_Rattletrap_BatteryAssault = 288,
	C_DOTA_Ability_Rattletrap_Hookshot = 289,
	C_DOTA_Ability_Rattletrap_PowerCogs = 290,
	C_DOTA_Ability_Rattletrap_RocketFlare = 291,
	C_DOTA_Ability_Razor_EyeOfTheStorm = 292,
	C_DOTA_Ability_Razor_PlasmaField = 293,
	C_DOTA_Ability_Razor_UnstableCurrent = 294,
	C_DOTA_Ability_Riki_BlinkStrike = 295,
	C_DOTA_Ability_Riki_SmokeScreen = 296,
	C_DOTA_Ability_Riki_TricksOfTheTrade = 297,
	C_DOTA_Ability_Rubick_NullField = 298,
	C_DOTA_Ability_Rubick_SpellSteal = 299,
	C_DOTA_Ability_Rubick_Telekinesis = 300,
	C_DOTA_Ability_Rubick_TelekinesisLand = 301,
	C_DOTA_Ability_SandKing_BurrowStrike = 302,
	C_DOTA_Ability_SandKing_Epicenter = 303,
	C_DOTA_Ability_SandKing_SandStorm = 304,
	C_DOTA_Ability_SatyrTrickster_Purge = 305,
	C_DOTA_Ability_Shadow_Demon_Disruption = 306,
	C_DOTA_Ability_Shadow_Demon_Shadow_Poison = 307,
	C_DOTA_Ability_Shadow_Demon_Soul_Catcher = 308,
	C_DOTA_Ability_ShadowShaman_Shackles = 309,
	C_DOTA_Ability_ShadowShamanVoodoo = 310,
	C_DOTA_Ability_Shredder_Chakram = 311,
	C_DOTA_Ability_Shredder_TimberChain = 312,
	C_DOTA_Ability_Silencer_CurseOfTheSilent = 313,
	C_DOTA_Ability_Silencer_GlaivesOfWisdom = 314,
	C_DOTA_Ability_Silencer_GlobalSilence = 315,
	C_DOTA_Ability_SkeletonKing_Reincarnation = 316,
	C_DOTA_Ability_SkeletonKing_VampiricAura = 317,
	C_DOTA_Ability_Skywrath_Mage_Ancient_Seal = 318,
	C_DOTA_Ability_Skywrath_Mage_Mystic_Flare = 319,
	C_DOTA_Ability_Slardar_Amplify_Damage = 320,
	C_DOTA_Ability_Slardar_Slithereen_Crush = 321,
	C_DOTA_Ability_Slark_EssenceShift = 322,
	C_DOTA_Ability_Slark_Pounce = 323,
	C_DOTA_Ability_Slark_ShadowDance = 324,
	C_DOTA_Ability_Sniper_Assassinate = 325,
	C_DOTA_Ability_Sniper_Shrapnel = 326,
	C_DOTA_Ability_Spawnlord_Master_Freeze = 327,
	C_DOTA_Ability_Spectre_Desolate = 328,
	C_DOTA_Ability_Spectre_Dispersion = 329,
	C_DOTA_Ability_Spectre_SpectralDagger = 330,
	C_DOTA_Ability_SpiritBreaker_EmpoweringHaste = 331,
	C_DOTA_Ability_SpiritBreaker_NetherStrike = 332,
	C_DOTA_Ability_StormSpirit_BallLightning = 333,
	C_DOTA_Ability_StormSpirit_ElectricVortex = 334,
	C_DOTA_Ability_StormSpirit_StaticRemnant = 335,
	C_DOTA_Ability_Sven_StormBolt = 336,
	C_DOTA_Ability_Sven_Warcry = 337,
	C_DOTA_Ability_Techies_FocusedDetonate = 338,
	CDOTA_Ability_Techies_LandMines = 339,
	CDOTA_Ability_Techies_Minefield_Sign = 340,
	CDOTA_Ability_Techies_RemoteMines = 341,
	CDOTA_Ability_Techies_RemoteMines_SelfDetonate = 342,
	CDOTA_Ability_Techies_StasisTrap = 343,
	C_DOTA_Ability_Techies_Suicide = 344,
	C_DOTA_Ability_Terrorblade_ConjureImage = 345,
	C_DOTA_Ability_Terrorblade_Reflection = 346,
	C_DOTA_Ability_Terrorblade_Sunder = 347,
	C_DOTA_Ability_Throw_Coal = 348,
	C_DOTA_Ability_Throw_Snowball = 349,
	C_DOTA_Ability_Tidehunter_AnchorSmash = 350,
	C_DOTA_Ability_Tidehunter_Gush = 351,
	C_DOTA_Ability_Tidehunter_Ravage = 352,
	C_DOTA_Ability_Tiny_Avalanche = 353,
	C_DOTA_Ability_Tiny_CraggyExterior = 354,
	C_DOTA_Ability_Tiny_Toss = 355,
	CDOTA_Ability_Treant_EyesInTheForest = 356,
	C_DOTA_Ability_Treant_LivingArmor = 357,
	C_DOTA_Ability_Treant_Overgrowth = 358,
	C_DOTA_Ability_TrollWarlord_BerserkersRage = 359,
	C_DOTA_Ability_TrollWarlord_Whirling_Axes_Melee = 360,
	C_DOTA_Ability_TrollWarlord_WhirlingAxes_Ranged = 361,
	C_DOTA_Ability_Tusk_FrozenSigil = 362,
	CDOTA_Ability_Tusk_WalrusKick = 363,
	C_DOTA_Ability_Tusk_WalrusPunch = 364,
	C_DOTA_Ability_Undying_Decay = 365,
	C_DOTA_Ability_Undying_FleshGolem = 366,
	C_DOTA_Ability_Undying_SoulRip = 367,
	C_DOTA_Ability_Ursa_Earthshock = 368,
	C_DOTA_Ability_Ursa_Enrage = 369,
	C_DOTA_Ability_VengefulSpirit_Magic_Missile = 370,
	C_DOTA_Ability_VengefulSpirit_Nether_Swap = 371,
	C_DOTA_Ability_VengefulSpirit_WaveOfTerror = 372,
	C_DOTA_Ability_Venomancer_PlagueWard = 373,
	C_DOTA_Ability_Venomancer_PoisonNova = 374,
	C_DOTA_Ability_Venomancer_VenomousGale = 375,
	C_DOTA_Ability_Viper_CorrosiveSkin = 376,
	CDOTA_Ability_Viper_Nethertoxin = 377,
	C_DOTA_Ability_Viper_PoisonAttack = 378,
	C_DOTA_Ability_Viper_ViperStrike = 379,
	C_DOTA_Ability_Visage_Stone_Form_Self_Cast = 380,
	C_DOTA_Ability_Visage_SummonFamiliars = 381,
	C_DOTA_Ability_Visage_SummonFamiliars_StoneForm = 382,
	C_DOTA_Ability_Warlock_RainOfChaos = 383,
	C_DOTA_Ability_Warlock_Shadow_Word = 384,
	C_DOTA_Ability_Warlock_Upheaval = 385,
	C_DOTA_Ability_Weaver_Shukuchi = 386,
	C_DOTA_Ability_Weaver_TheSwarm = 387,
	C_DOTA_Ability_Weaver_TimeLapse = 388,
	C_DOTA_Ability_Windrunner_FocusFire = 389,
	C_DOTA_Ability_Windrunner_Powershot = 390,
	C_DOTA_Ability_Windrunner_Windrun = 391,
	CDOTA_Ability_Winter_Wyvern_Arctic_Burn = 392,
	CDOTA_Ability_Winter_Wyvern_Cold_Embrace = 393,
	CDOTA_Ability_Winter_Wyvern_Splinter_Blast = 394,
	CDOTA_Ability_Winter_Wyvern_Winters_Curse = 395,
	C_DOTA_Ability_Wisp_Overcharge = 396,
	C_DOTA_Ability_Wisp_Relocate = 397,
	C_DOTA_Ability_Wisp_Spirits = 398,
	C_DOTA_Ability_Wisp_Tether = 399,
	C_DOTA_Ability_WitchDoctor_Maledict = 400,
	C_DOTA_Ability_WitchDoctor_ParalyzingCask = 401,
	C_DOTA_Ability_WitchDoctor_VoodooRestoration = 402,
	C_DOTA_Ability_Zuus_Cloud = 403,
	C_DOTA_Ability_Zuus_LightningBolt = 404,
	C_DOTA_BaseNPC = 405,
	C_DOTA_BaseNPC_Additive = 406,
	C_DOTA_BaseNPC_Barracks = 407,
	C_DOTA_BaseNPC_Building = 408,
	C_DOTA_BaseNPC_Creature = 409,
	C_DOTA_BaseNPC_Creep = 410,
	C_DOTA_BaseNPC_Creep_Lane = 411,
	C_DOTA_BaseNPC_Creep_Neutral = 412,
	C_DOTA_BaseNPC_Creep_Siege = 413,
	C_DOTA_BaseNPC_Creep_Talking = 414,
	C_DOTA_BaseNPC_Effigy_BattleCup = 415,
	C_DOTA_BaseNPC_Effigy_Statue = 416,
	C_DOTA_BaseNPC_Filler = 417,
	C_DOTA_BaseNPC_Fort = 418,
	C_DOTA_BaseNPC_HallofFame = 419,
	C_DOTA_BaseNPC_Healer = 420,
	C_DOTA_BaseNPC_Hero = 421,
	C_DOTA_BaseNPC_HoldoutTower = 422,
	C_DOTA_BaseNPC_HoldoutTower_HeavySlow = 423,
	C_DOTA_BaseNPC_HoldoutTower_LightFast = 424,
	C_DOTA_BaseNPC_HoldoutTower_ReduceSpeed = 425,
	C_DOTA_BaseNPC_Invoker_Forged_Spirit = 426,
	C_DOTA_BaseNPC_SDKTower = 427,
	C_DOTA_BaseNPC_ShadowShaman_SerpentWard = 428,
	C_DOTA_BaseNPC_Shop = 429,
	C_DOTA_BaseNPC_Tower = 430,
	C_DOTA_BaseNPC_Trap_Ward = 431,
	C_DOTA_BaseNPC_Tusk_Sigil = 432,
	C_DOTA_BaseNPC_Venomancer_PlagueWard = 433,
	C_DOTA_BaseNPC_Warlock_Golem = 434,
	C_DOTA_Beastmaster_Axe = 435,
	C_DOTA_DarkWillow_Creature = 436,
	C_DOTA_DataCustomTeam = 437,
	C_DOTA_DataDire = 438,
	C_DOTA_DataNonSpectator = 439,
	C_DOTA_DataRadiant = 440,
	C_DOTA_DataSpectator = 441,
	C_DOTA_DeathProphet_Exorcism_Spirit = 442,
	C_DOTA_DisplacementVisibility = 443,
	C_DOTA_Hero_Recorder = 444,
	C_DOTA_Item = 445,
	C_DOTA_Item_Aether_Lens = 446,
	C_DOTA_Item_Ancient_Janggo = 447,
	C_DOTA_Item_Arcane_Boots = 448,
	C_DOTA_Item_Armlet = 449,
	CDOTA_Item_Battlefury = 450,
	C_DOTA_Item_BlinkDagger = 451,
	C_DOTA_Item_Bloodstone = 452,
	C_DOTA_Item_BootsOfTravel = 453,
	CDOTA_Item_BootsOfTravel_2 = 454,
	C_DOTA_Item_Buckler = 455,
	C_DOTA_Item_Crimson_Guard = 456,
	C_DOTA_Item_Cyclone = 457,
	C_DOTA_Item_DataDriven = 458,
	C_DOTA_Item_DeathGoldDropped = 459,
	C_DOTA_Item_Diffusal_Blade = 460,
	C_DOTA_Item_Diffusal_Blade_Level2 = 461,
	C_DOTA_Item_EmptyBottle = 462,
	C_DOTA_Item_Ethereal_Blade = 463,
	CDOTA_Item_ForceStaff = 464,
	C_DOTA_Item_GemOfTrueSight = 465,
	CDOTA_Item_GlimmerCape = 466,
	CDOTA_Item_Guardian_Greaves = 467,
	CDOTA_Item_Hurricane_Pike = 468,
	C_DOTA_Item_Iron_Talon = 469,
	C_DOTA_Item_Lua = 470,
	C_DOTA_Item_MantaStyle = 471,
	CDOTA_Item_Medallion_Of_Courage = 472,
	C_DOTA_Item_Mekansm = 473,
	C_DOTA_Item_MeteorHammer = 474,
	CDOTA_Item_Moonshard = 475,
	C_DOTA_Item_Necronomicon = 476,
	C_DOTA_Item_Necronomicon_Level2 = 477,
	C_DOTA_Item_Necronomicon_Level3 = 478,
	C_DOTA_Item_Nian_Flag_Trap = 479,
	C_DOTA_Item_Nullifier = 480,
	CDOTA_Item_ObserverWard = 481,
	C_DOTA_Item_Physical = 482,
	C_DOTA_Item_Pipe = 483,
	C_DOTA_Item_PowerTreads = 484,
	C_DOTA_Item_QuellingBlade = 485,
	C_DOTA_Item_Radiance = 486,
	CDOTA_Item_Recipe_Guardian_Greaves = 487,
	C_DOTA_Item_Recipe_Veil_Of_Discord = 488,
	C_DOTA_Item_Ring_Of_Basilius = 489,
	C_DOTA_Item_RingOfAquila = 490,
	C_DOTA_Item_Rune = 491,
	C_DOTA_Item_RuneSpawner = 492,
	C_DOTA_Item_RuneSpawner_Bounty = 493,
	C_DOTA_Item_RuneSpawner_Powerup = 494,
	CDOTA_Item_SentryWard = 495,
	C_DOTA_Item_Shivas_Guard = 496,
	C_DOTA_Item_Smoke_Of_Deceit = 497,
	CDOTA_Item_Solar_Crest = 498,
	C_DOTA_Item_Spirit_Vessel = 499,
	C_DOTA_Item_Tango = 500,
	C_DOTA_Item_Tango_Single = 501,
	C_DOTA_Item_TeleportScroll = 502,
	C_DOTA_Item_Tome_Of_Knowledge = 503,
	C_DOTA_Item_TranquilBoots = 504,
	C_DOTA_Item_TranquilBoots2 = 505,
	C_DOTA_Item_UltimateScepter = 506,
	C_DOTA_Item_Urn_Of_Shadows = 507,
	C_DOTA_Item_Veil_Of_Discord = 508,
	C_DOTA_Item_Vladmir = 509,
	CDOTA_Item_Ward_Dispenser = 510,
	C_DOTA_NeutralSpawner = 511,
	C_DOTA_NPC_DataDriven = 512,
	CDOTA_NPC_Observer_Ward = 513,
	CDOTA_NPC_Observer_Ward_TrueSight = 514,
	C_DOTA_NPC_Techies_Minefield_Sign = 515,
	C_DOTA_NPC_TechiesMines = 516,
	C_DOTA_NPC_Treant_EyesInTheForest = 517,
	C_DOTA_NPC_WitchDoctor_Ward = 518,
	C_DOTA_PhantomAssassin_Gravestone = 519,
	C_DOTA_PlayerResource = 520,
	C_DOTA_RoshanSpawner = 521,
	C_DOTA_SimpleObstruction = 522,
	C_DOTA_TempTree = 523,
	C_DOTA_Tiny_ScepterTree = 524,
	CDOTA_Unit_Announcer = 525,
	CDOTA_Unit_Announcer_Killing_Spree = 526,
	C_DOTA_Unit_Brewmaster_PrimalEarth = 527,
	C_DOTA_Unit_Brewmaster_PrimalFire = 528,
	C_DOTA_Unit_Brewmaster_PrimalStorm = 529,
	C_DOTA_Unit_Broodmother_Spiderling = 530,
	C_DOTA_Unit_Broodmother_Web = 531,
	C_DOTA_Unit_Courier = 532,
	C_DOTA_Unit_Earth_Spirit_Stone = 533,
	CDOTA_Unit_Elder_Titan_AncestralSpirit = 534,
	C_DOTA_Unit_Fountain = 535,
	CDOTA_Unit_Hero_Abaddon = 536,
	CDOTA_Unit_Hero_AbyssalUnderlord = 537,
	CDOTA_Unit_Hero_Alchemist = 538,
	CDOTA_Unit_Hero_AncientApparition = 539,
	C_DOTA_Unit_Hero_AntiMage = 540,
	CDOTA_Unit_Hero_ArcWarden = 541,
	C_DOTA_Unit_Hero_Axe = 542,
	C_DOTA_Unit_Hero_Bane = 543,
	C_DOTA_Unit_Hero_Batrider = 544,
	C_DOTA_Unit_Hero_Beastmaster = 545,
	C_DOTA_Unit_Hero_Beastmaster_Beasts = 546,
	C_DOTA_Unit_Hero_Beastmaster_Boar = 547,
	C_DOTA_Unit_Hero_Beastmaster_Hawk = 548,
	C_DOTA_Unit_Hero_Bloodseeker = 549,
	C_DOTA_Unit_Hero_BountyHunter = 550,
	C_DOTA_Unit_Hero_Brewmaster = 551,
	C_DOTA_Unit_Hero_Bristleback = 552,
	C_DOTA_Unit_Hero_Broodmother = 553,
	CDOTA_Unit_Hero_Centaur = 554,
	C_DOTA_Unit_Hero_ChaosKnight = 555,
	C_DOTA_Unit_Hero_Chen = 556,
	C_DOTA_Unit_Hero_Clinkz = 557,
	C_DOTA_Unit_Hero_CrystalMaiden = 558,
	C_DOTA_Unit_Hero_DarkSeer = 559,
	C_DOTA_Unit_Hero_DarkWillow = 560,
	C_DOTA_Unit_Hero_Dazzle = 561,
	C_DOTA_Unit_Hero_DeathProphet = 562,
	C_DOTA_Unit_Hero_Disruptor = 563,
	C_DOTA_Unit_Hero_DoomBringer = 564,
	C_DOTA_Unit_Hero_DragonKnight = 565,
	C_DOTA_Unit_Hero_DrowRanger = 566,
	C_DOTA_Unit_Hero_Earthshaker = 567,
	C_DOTA_Unit_Hero_EarthSpirit = 568,
	CDOTA_Unit_Hero_Elder_Titan = 569,
	C_DOTA_Unit_Hero_EmberSpirit = 570,
	C_DOTA_Unit_Hero_Enchantress = 571,
	C_DOTA_Unit_Hero_Enigma = 572,
	C_DOTA_Unit_Hero_FacelessVoid = 573,
	C_DOTA_Unit_Hero_Furion = 574,
	CDOTA_Unit_Hero_Gyrocopter = 575,
	C_DOTA_Unit_Hero_Huskar = 576,
	C_DOTA_Unit_Hero_Invoker = 577,
	C_DOTA_Unit_Hero_Jakiro = 578,
	C_DOTA_Unit_Hero_Juggernaut = 579,
	C_DOTA_Unit_Hero_KeeperOfTheLight = 580,
	C_DOTA_Unit_Hero_Kunkka = 581,
	C_DOTA_Unit_Hero_Legion_Commander = 582,
	C_DOTA_Unit_Hero_Leshrac = 583,
	C_DOTA_Unit_Hero_Lich = 584,
	C_DOTA_Unit_Hero_Life_Stealer = 585,
	C_DOTA_Unit_Hero_Lina = 586,
	C_DOTA_Unit_Hero_Lion = 587,
	C_DOTA_Unit_Hero_LoneDruid = 588,
	C_DOTA_Unit_Hero_Luna = 589,
	C_DOTA_Unit_Hero_Lycan = 590,
	C_DOTA_Unit_Hero_Magnataur = 591,
	C_DOTA_Unit_Hero_Medusa = 592,
	C_DOTA_Unit_Hero_Meepo = 593,
	C_DOTA_Unit_Hero_Mirana = 594,
	C_DOTA_Unit_Hero_MonkeyKing = 595,
	C_DOTA_Unit_Hero_Morphling = 596,
	C_DOTA_Unit_Hero_Naga_Siren = 597,
	C_DOTA_Unit_Hero_Necrolyte = 598,
	C_DOTA_Unit_Hero_Nevermore = 599,
	C_DOTA_Unit_Hero_NightStalker = 600,
	C_DOTA_Unit_Hero_Nyx_Assassin = 601,
	C_DOTA_Unit_Hero_Obsidian_Destroyer = 602,
	C_DOTA_Unit_Hero_Ogre_Magi = 603,
	C_DOTA_Unit_Hero_Omniknight = 604,
	C_DOTA_Unit_Hero_Oracle = 605,
	C_DOTA_Unit_Hero_Pangolier = 606,
	C_DOTA_Unit_Hero_PhantomAssassin = 607,
	C_DOTA_Unit_Hero_PhantomLancer = 608,
	C_DOTA_Unit_Hero_Phoenix = 609,
	C_DOTA_Unit_Hero_Puck = 610,
	C_DOTA_Unit_Hero_Pudge = 611,
	C_DOTA_Unit_Hero_Pugna = 612,
	C_DOTA_Unit_Hero_QueenOfPain = 613,
	C_DOTA_Unit_Hero_Rattletrap = 614,
	C_DOTA_Unit_Hero_Razor = 615,
	C_DOTA_Unit_Hero_Riki = 616,
	C_DOTA_Unit_Hero_Rubick = 617,
	C_DOTA_Unit_Hero_SandKing = 618,
	C_DOTA_Unit_Hero_Shadow_Demon = 619,
	C_DOTA_Unit_Hero_ShadowShaman = 620,
	C_DOTA_Unit_Hero_Shredder = 621,
	C_DOTA_Unit_Hero_Silencer = 622,
	C_DOTA_Unit_Hero_SkeletonKing = 623,
	C_DOTA_Unit_Hero_Skywrath_Mage = 624,
	C_DOTA_Unit_Hero_Slardar = 625,
	C_DOTA_Unit_Hero_Slark = 626,
	C_DOTA_Unit_Hero_Sniper = 627,
	C_DOTA_Unit_Hero_Spectre = 628,
	C_DOTA_Unit_Hero_SpiritBreaker = 629,
	C_DOTA_Unit_Hero_StormSpirit = 630,
	C_DOTA_Unit_Hero_Sven = 631,
	C_DOTA_Unit_Hero_Techies = 632,
	C_DOTA_Unit_Hero_TemplarAssassin = 633,
	C_DOTA_Unit_Hero_Terrorblade = 634,
	C_DOTA_Unit_Hero_Tidehunter = 635,
	C_DOTA_Unit_Hero_Tinker = 636,
	C_DOTA_Unit_Hero_Tiny = 637,
	C_DOTA_Unit_Hero_Treant = 638,
	C_DOTA_Unit_Hero_TrollWarlord = 639,
	C_DOTA_Unit_Hero_Tusk = 640,
	C_DOTA_Unit_Hero_Undying = 641,
	C_DOTA_Unit_Hero_Ursa = 642,
	C_DOTA_Unit_Hero_VengefulSpirit = 643,
	C_DOTA_Unit_Hero_Venomancer = 644,
	C_DOTA_Unit_Hero_Viper = 645,
	C_DOTA_Unit_Hero_Visage = 646,
	C_DOTA_Unit_Hero_Warlock = 647,
	C_DOTA_Unit_Hero_Weaver = 648,
	C_DOTA_Unit_Hero_Windrunner = 649,
	C_DOTA_Unit_Hero_Winter_Wyvern = 650,
	C_DOTA_Unit_Hero_Wisp = 651,
	C_DOTA_Unit_Hero_WitchDoctor = 652,
	C_DOTA_Unit_Hero_Zuus = 653,
	C_DOTA_Unit_LoopingSound = 654,
	C_DOTA_Unit_Nian = 655,
	C_DOTA_Unit_Roshan = 656,
	C_DOTA_Unit_SpiritBear = 657,
	C_DOTA_Unit_TargetDummy = 658,
	C_DOTA_Unit_Undying_Tombstone = 659,
	C_DOTA_Unit_Undying_Zombie = 660,
	C_DOTA_Unit_VisageFamiliar = 661,
	C_DOTA_Unit_ZeusCloud = 662,
	C_DOTA_Wisp_Spirit = 663,
	C_DOTAAbilityDraftGameMode = 664,
	C_DOTABaseAbility = 665,
	C_DOTABaseCustomHeroPickRules = 666,
	C_DOTABaseGameMode = 667,
	C_DOTACameraBounds = 668,
	C_DOTAFogOfWarTempViewers = 669,
	C_DOTAGameManagerProxy = 670,
	C_DOTAGamerulesProxy = 671,
	C_DOTAHoldoutNetworker = 672,
	CDOTAInGamePredictionState = 673,
	C_DOTAMinimapBoundary = 677,
	C_DOTAMutationGameMode = 674,
	C_DOTAPlayer = 675,
	C_DOTAPropCustomTexture = 676,
	C_DotaQuest = 677,
	C_DotaQuestBase = 678,
	C_DOTASpecGraphPlayerData = 679,
	C_DOTASpectatorGraphManagerProxy = 680,
	C_DotaSubquestBase = 681,
	C_DOTATeam = 682,
	C_DOTATurboGameMode = 683,
	C_DOTATurboHeroPickRules = 684,
	C_DotaTutorialNetworker = 685,
	C_DOTAWearableItem = 686,
	C_DynamicLight = 687,
	C_DynamicProp = 688,
	C_EconEntity = 689,
	C_EconWearable = 690,
	C_EntityDissolve = 691,
	C_EntityFlame = 692,
	C_EnvClock = 693,
	C_EnvCombinedLightProbeVolume = 694,
	C_EnvCubemap = 695,
	C_EnvCubemapBox = 696,
	C_EnvDeferredLight = 697,
	C_EnvDetailController = 698,
	C_EnvDOFController = 699,
	C_EnvLightProbeVolume = 700,
	C_EnvProjectedTexture = 701,
	C_EnvScreenEffect = 702,
	C_EnvScreenOverlay = 703,
	C_EnvSky = 704,
	C_EnvVolumetricFogController = 705,
	C_EnvWind = 706,
	C_FireSmoke = 707,
	C_Fish = 708,
	C_FogController = 709,
	C_Func_Dust = 710,
	C_Func_LOD = 711,
	C_FuncAreaPortalWindow = 712,
	C_FuncBrush = 713,
	C_FuncCombineBarrier = 714,
	C_FuncConveyor = 715,
	C_FuncDistanceOccluder = 716,
	C_FuncLadder = 717,
	C_FuncMonitor = 718,
	C_FuncMoveLinear = 719,
	C_FuncOccluder = 720,
	C_FuncRotating = 721,
	C_FuncTrackTrain = 722,
	C_GameRulesProxy = 723,
	C_GenericFlexCycler = 724,
	C_HandleTest = 725,
	C_InfoLadderDismount = 726,
	C_InfoOverlayAccessor = 727,
	C_InfoPlayerStartBadGuys = 728,
	C_InfoPlayerStartDota = 729,
	C_InfoPlayerStartGoodGuys = 730,
	CInfoWorldLayer = 731,
	C_IngameEvent_Base = 732,
	C_IngameEvent_DotaPlus = 733,
	C_IngameEvent_DotaPrime = 734,
	C_IngameEvent_FM2015 = 735,
	C_IngameEvent_FM2016 = 736,
	C_IngameEvent_TI6 = 737,
	C_IngameEvent_TI7 = 738,
	C_IngameEvent_TI8 = 739,
	C_IngameEvent_WM2016 = 740,
	C_IngameEvent_WM2017 = 741,
	C_LightDirectionalEntity = 742,
	C_LightEntity = 743,
	C_LightEnvironmentEntity = 744,
	C_LightGlow = 745,
	C_LightOrthoEntity = 746,
	C_LightSpotEntity = 747,
	C_MaterialModifyControl = 748,
	C_ModelPointEntity = 749,
	C_ParticlePerformanceMonitor = 750,
	C_ParticleSystem = 751,
	C_PhysBox = 752,
	C_PhysBoxMultiplayer = 753,
	C_PhysicsProp = 754,
	C_PhysMagnet = 755,
	C_PlayerResource = 757,
	C_PointCamera = 758,
	C_PointClientUIDialog = 759,
	C_PointClientUIHUD = 763,
	C_PointClientUIWorldPanel = 760,
	C_PointClientUIWorldTextPanel = 761,
	C_PointEntity = 763,
	C_PointHMDAnchor = 764,
	C_PointHMDAnchorOverride = 765,
	C_PointValueRemapper = 766,
	C_PointWorldText = 767,
	C_PoseController = 768,
	C_PostProcessController = 769,
	C_PostProcessingVolume = 770,
	CClient_Precipitation = 771,
	C_PrecipitationBlocker = 772,
	C_PropHMDAvatar = 773,
	C_PropJeep = 777,
	C_PropVehicleChoreoGeneric = 778,
	C_PropVehicleDriveable = 774,
	C_PropVRHand = 775,
	C_PropVRTrackedObject = 776,
	C_PropZipline = 777,
	C_RagdollManager = 778,
	C_ServerRagdoll = 779,
	C_ServerRagdollAttached = 780,
	C_RopeKeyframe = 781,
	C_SceneEntity = 782,
	C_ShadowControl = 783,
	C_SkyCamera = 784,
	C_SlideshowDisplay = 790,
	C_SpeechBubbleManager = 785,
	C_SpotlightEnd = 786,
	C_Sprite = 787,
	C_SpriteOriented = 788,
	C_Sun = 789,
	C_Team = 790,
	C_TeamplayRoundBasedRulesProxy = 797,
	C_TeamRoundTimer = 798,
	C_TestTraceline = 791,
	C_TFWearableItem = 792,
	C_TonemapController2 = 793,
	C_TriggerCamera = 794,
	C_TriggerPlayerMovement = 795,
	C_VRHandModelOverride = 797,
	C_WaterBullet = 798,
	C_World = 799,
	C_NextBotCombatCharacter = 800,
};

#define FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define FL_WATERJUMP			(1<<2)	// player jumping out of water
#define FL_ONTRAIN				(1<<3)	// Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<5)	// Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<6)	// Player can't move, but keeps key inputs for controlling another entity
#define FL_CLIENT				(1<<7)	// Is a player
#define FL_FAKECLIENT			(1<<8)	// Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define FL_INWATER				(1<<9)	// In water

#define CONTENTS_EMPTY			0		// No contents

#define CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define CONTENTS_AUX			0x4
#define CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define CONTENTS_SLIME			0x10
#define CONTENTS_WATER			0x20
#define CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200

// unused
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
// CONTENTS_OPAQUE + SURF_NODRAW count as CONTENTS_OPAQUE (shadow-casting toolsblocklight textures)
#define CONTENTS_BLOCKLIGHT		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define CONTENTS_AREAPORTAL		0x8000

#define CONTENTS_PLAYERCLIP		0x10000
#define CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define CONTENTS_CURRENT_0		0x40000
#define CONTENTS_CURRENT_90		0x80000
#define CONTENTS_CURRENT_180	0x100000
#define CONTENTS_CURRENT_270	0x200000
#define CONTENTS_CURRENT_UP		0x400000
#define CONTENTS_CURRENT_DOWN	0x800000

#define CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define CONTENTS_DEBRIS			0x4000000
#define CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define MASK_SHOT	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

// These are given to FindMaterial to reference the texture groups that show up on the
#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

#define MAXSTUDIOBONES 128
#define BONE_USED_BY_HITBOX 0x100

// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define SURF_LIGHT		0x0001		// value will hold the light strength
#define SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define SURF_SKY		0x0004		// don't draw, but add to skybox
#define SURF_WARP		0x0008		// turbulent water warp
#define SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define SURF_NODRAW		0x0080	// don't bother referencing the texture

#define SURF_HINT		0x0100	// make a primary bsp splitter

#define SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOPAINT	SURF_NODECALS	// the surface can not have paint placed on it
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface
#define SURF_HITBOX		0x8000	// surface is part of a hitbox

#define MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks fluid movement
#define MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
// water physics in these contents
#define MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// bullets see these as solid, except monsters (world+brush only)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC_FLUID	(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

#define SEQUENCE_DEFAULT_DRAW						0
#define SEQUENCE_DEFAULT_IDLE1						1
#define SEQUENCE_DEFAULT_IDLE2						2
#define SEQUENCE_DEFAULT_LIGHT_MISS1				3
#define SEQUENCE_DEFAULT_LIGHT_MISS2				4
#define SEQUENCE_DEFAULT_HEAVY_MISS1				9
#define SEQUENCE_DEFAULT_HEAVY_HIT1					10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB				11
#define SEQUENCE_DEFAULT_LOOKAT01					12

#define SEQUENCE_BUTTERFLY_DRAW						0
#define SEQUENCE_BUTTERFLY_DRAW2					1
#define SEQUENCE_BUTTERFLY_LOOKAT01					13
#define SEQUENCE_BUTTERFLY_LOOKAT03					15

#define SEQUENCE_FALCHION_IDLE1						1
#define SEQUENCE_FALCHION_HEAVY_MISS1				8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP		9
#define SEQUENCE_FALCHION_LOOKAT01					12
#define SEQUENCE_FALCHION_LOOKAT02					13

#define SEQUENCE_DAGGERS_IDLE1						1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 				2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 				6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 				11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 				12

#define SEQUENCE_BOWIE_IDLE1 						1
