#pragma once

#include "bf_read.h"
#include "bf_write.h"
#include "CUtlString.h"

#include <google/protobuf/message.h>
#include <google/protobuf/io/coded_stream.h>

struct NetMessageInfo_t;

enum NetChannelBufType_t : int
{
    BUF_DEFAULT = -1,
    BUF_UNRELIABLE = 0,
    BUF_RELIABLE = 1,
    BUF_VOICE = 2,
};

enum class SignonState_t : uint32_t {
    SIGNONSTATE_NONE = 0,
    SIGNONSTATE_CHALLENGE = 1,
    SIGNONSTATE_CONNECTED = 2,
    SIGNONSTATE_NEW = 3,
    SIGNONSTATE_PRESPAWN = 4,
    SIGNONSTATE_SPAWN = 5,
    SIGNONSTATE_FULL = 6,
    SIGNONSTATE_CHANGELEVEL = 7,
};

enum class NetMessageTypes : short
{
    CNETMsg_NOP = 0,
    CNETMsg_Disconnect = 1,
    CNETMsg_SplitScreenUser = 3,
    CNETMsg_Tick = 4,
    CNETMsg_StringCmd = 5,
    CNETMsg_SetConVar = 6,
    CNETMsg_SignonState = 7,
    CNETMsg_SpawnGroup_Load = 8,
    CNETMsg_SpawnGroup_ManifestUpdate = 9,
    CNETMsg_SpawnGroup_SetCreationTick = 11,
    CNETMsg_SpawnGroup_Unload = 12,
    CNETMsg_SpawnGroup_LoadCompleted = 13,
    CBidirMsg_RebroadcastGameEvent = 16,
    CBidirMsg_RebroadcastSource = 17,
    CCLCMsg_ClientInfo = 20,
    CCLCMsg_Move = 21,
    CCLCMsg_VoiceData = 22,
    CCLCMsg_BaselineAck = 23,
    CCLCMsg_RespondCvarValue = 25,
    CCLCMsg_FileCRCCheck = 26,
    CCLCMsg_LoadingProgress = 27,
    CCLCMsg_SplitPlayerConnect = 28,
    CCLCMsg_SplitPlayerDisconnect = 30,
    CCLCMsg_ServerStatus = 31,
    CCLCMsg_ServerPing = 32,
    CCLCMsg_RequestPause = 33,
    CCLCMsg_CmdKeyValues = 34,
    CSVCMsg_ServerInfo = 40,
    CSVCMsg_FlattenedSerializer = 41,
    CSVCMsg_ClassInfo = 42,
    CSVCMsg_SetPause = 43,
    CSVCMsg_CreateStringTable = 44,
    CSVCMsg_UpdateStringTable = 45,
    CSVCMsg_VoiceInit = 46,
    CSVCMsg_VoiceData = 47,
    CSVCMsg_Print = 48,
    CSVCMsg_Sounds = 49,
    CSVCMsg_SetView = 50,
    CSVCMsg_ClearAllStringTables = 51,
    CSVCMsg_CmdKeyValues = 52,
    CSVCMsg_BSPDecal = 53,
    CSVCMsg_SplitScreen = 54,
    CSVCMsg_PacketEntities = 55,
    CSVCMsg_Prefetch = 56,
    CSVCMsg_Menu = 57,
    CSVCMsg_GetCvarValue = 58,
    CSVCMsg_StopSound = 59,
    CSVCMsg_PeerList = 60,
    CSVCMsg_PacketReliable = 61,
    CSVCMsg_HLTVStatus = 62,
    CSVCMsg_ServerSteamID = 63,
    CSVCMsg_FullFrameSplit = 70,
    CUserMessageAchievementEvent = 101,
    CUserMessageCloseCaption = 102,
    CUserMessageCloseCaptionDirect = 103,
    CUserMessageCurrentTimescale = 104,
    CUserMessageDesiredTimescale = 105,
    CUserMessageFade = 106,
    CUserMessageGameTitle = 107,
    CUserMessageHintText = 109,
    CUserMessageHudMsg = 110,
    CUserMessageHudText = 111,
    CUserMessageKeyHintText = 112,
    CUserMessageColoredText = 113,
    CUserMessageRequestState = 114,
    CUserMessageResetHUD = 115,
    CUserMessageRumble = 116,
    CUserMessageSayText = 117,
    CUserMessageSayText2 = 118,
    CUserMessageSayTextChannel = 119,
    CUserMessageShake = 120,
    CUserMessageShakeDir = 121,
    CUserMessageTextMsg = 124,
    CUserMessageScreenTilt = 125,
    CUserMessageTrain = 126,
    CUserMessageVGUIMenu = 127,
    CUserMessageVoiceMask = 128,
    CUserMessageVoiceSubtitle = 129,
    CUserMessageSendAudio = 130,
    CUserMessageItemPickup = 131,
    CUserMessageAmmoDenied = 132,
    CUserMessageCrosshairAngle = 133,
    CUserMessageShowMenu = 134,
    CUserMessageCreditsMsg = 135,
    CEntityMessagePlayJingle = 136,
    CEntityMessageScreenOverlay = 137,
    CEntityMessageRemoveAllDecals = 138,
    CEntityMessagePropagateForce = 139,
    CEntityMessageDoSpark = 140,
    CEntityMessageFixAngle = 141,
    CUserMessageCloseCaptionPlaceholder = 142,
    CUserMessageCameraTransition = 143,
    CUserMessageAudioParameter = 144,
    CUserMsg_ParticleManager = 145,
    CUserMsg_HudError = 146,
    CUserMsg_CustomGameEvent = 148,
    CUserMessageHapticPulse = 149,
    CUserMessageHapticPulsePrecise = 151,
    CMsgPlaceDecalEvent = 201,
    CMsgClearWorldDecalsEvent = 202,
    CMsgClearEntityDecalsEvent = 203,
    CMsgClearDecalsForSkeletonInstanceEvent = 204,
    CMsgSource1LegacyGameEventList = 205,
    CMsgSource1LegacyListenEvents = 206,
    CMsgSource1LegacyGameEvent = 207,
    CMsgSosStartSoundEvent = 208,
    CMsgSosStopSoundEvent = 209,
    CMsgSosSetSoundEventParams = 210,
    CMsgSosSetLibraryStackFields = 211,
    CMsgSosStopSoundEventHash = 212,
    CP2P_TextMessage = 256,
    CP2P_Voice = 257,
    CP2P_Ping = 258,
    CP2P_VRAvatarPosition = 259,
    CP2P_WatchSynchronization = 260,
    CClientMsg_CustomGameEvent = 280,
    CClientMsg_CustomGameEventBounce = 281,
    CClientMsg_ClientUIEvent = 282,
    CClientMsg_RotateAnchor = 285,
    CDOTAClientMsg_MapLine = 301,
    CDOTAClientMsg_AspectRatio = 302,
    CDOTAClientMsg_MapPing = 303,
    CDOTAClientMsg_UnitsAutoAttackMode = 304,
    CDOTAClientMsg_SearchString = 307,
    CDOTAClientMsg_Pause = 308,
    CDOTAClientMsg_ShopViewMode = 309,
    CDOTAClientMsg_SetUnitShareFlag = 310,  // needs more testing
    CDOTAClientMsg_SwapRequest = 311,
    CDOTAClientMsg_SwapAccept = 312,
    CDOTAClientMsg_WorldLine = 313,
    CDOTAClientMsg_RequestGraphUpdate = 314,
    CDOTAClientMsg_ItemAlert = 315,
    CDOTAClientMsg_ChatWheel = 316,
    CDOTAClientMsg_SendStatPopup = 317, // the messages sent by those in the casting slot
    CDOTAClientMsg_BeginLastHitChallenge = 318,
    CDOTAClientMsg_UpdateQuickBuy = 319,
    CDOTAClientMsg_UpdateCoachListen = 320,
    CDOTAClientMsg_CoachHUDPing = 321,
    CDOTAClientMsg_RecordVote = 322,
    CDOTAClientMSg_UnitsAutoAttackAfterSpell = 323,
    CDOTAClientMsg_WillPurchaseAlert = 324,
    CDOTAClientMsg_PlayerShowCase = 325,
    CDOTAClientMsg_TeleportRequiresHalt = 326,
    CDOTAClientMsg_CameraZoomAmount = 327,
    CDOTAClientMsg_BroadcasterUsingCameraman = 328,
    CDOTAClientMsg_BroadcasterUsingAssistedCameraOperator = 329,
    CDOTAClientMsg_EnemyItemAlert = 330,
    CDOTAClientMsg_FreeInventory = 331,
    CDOTAClientMsg_BuyBackStateAlert = 332,
    CDOTAClientMsg_QuickBuyAlert = 333,
    CDOTAClientMsg_HeroStatueLike = 334,
    CDOTAClientMsg_ModifierAlert = 335,
    CDOTAClientMsg_TeamShowcaseEditor = 336,
    CDOTAClientMsg_HPManaAlert = 337,
    CDOTAClientMsg_GlyphAlert = 338,
    CDOTAClientMsg_TeamShowcaseClientData = 339,
    CDOTAClientMsg_PlayTeamShowcase = 340,
    CDOTAClientMsg_EventCNY2015Cmd = 341,
    CDOTAClientMsg_FillEmptySlotsWithBots = 342,
    CDOTAClientMsg_DemoHero = 343,
    CDOTAClientMsg_AbilityLearnModeToggled = 344,
    CDOTAClientMsg_AbilityStartUse = 345,
    CDOTAClientMsg_ChallengeSelect = 346,
    CDOTAClientMsg_ChallengeReroll = 347,
    CDOTAClientMsg_ClickedBuff = 348,
    CDOTAClientMsg_CoinWager = 349,
    CDOTAClientMsg_ExecuteOrders = 350,
    CDOTAClientMsg_XPAlert = 351,
    CDOTAClientMsg_EventPointsTip = 353,
    CDOTAClientMsg_MatchMetadata = 354,
    CDOTAClientMsg_KillMyHero = 355,
    CDOTAClientMsg_QuestStatus = 356,
    CDOTAClientMsg_ToggleAutoattack = 357,
    CDOTAClientMsg_SpecialAbility = 358,
    CDOTAClientMsg_KillcamDamageTaken = 359,
    CDOTAClientMsg_SetEnemyStartingPosition = 360,
    CDOTAClientMsg_SetDesiredWardPlacement = 361,
    CDOTAClientMsg_RollDice = 362,
    CDOTAClientMsg_FlipCoin = 363,
    CDOTAClientMsg_RequestItemSuggestions = 364,
    CDOTAClientMsg_MakeTeamCaptain = 365,
    CDOTAClientMsg_CoinWagerToken = 366,
    CDOTAClientMsg_RankWager = 367,
    CDOTAClientMsg_DismissAllStatPopups = 368,
    CDOTAClientMsg_HelpTipSystemStateChanged = 369,
    CDOTAClientMsg_ChannelRequiresHalt = 370,
    CDOTAClientMsg_RequestBulkCombatLog = 371,
    CDOTAClientMsg_AbilityDraftRequestAbility = 372,
    CDOTAClientMsg_GuideSelectOption = 373,
    CDOTAClientMsg_GuideSelected = 374,
    CDOTAClientMsg_DamageReport = 375,
    CDOTAClientMsg_SalutePlayer = 376,
    CDOTAClientMsg_SprayWheel = 377,
    CDOTAClientMsg_TipAlert = 378, // https://github.com/SteamDatabase/GameTracking-Dota2/blob/3e4fc846f4a99669a9bdd045f23698991b5ab529/game/dota/pak01_dir/scripts/tips.txt
    CDOTAClientMsg_EmptyTeleportAlert = 379,
    CMsgTEEffectDispatch = 400,
    CMsgTEArmorRicochet = 401,
    CMsgTEBeamEntPoint = 402,
    CMsgTEBeamEnts = 403,
    CMsgTEBeamPoints = 404,
    CMsgTEBeamRing = 405,
    CMsgTEBSPDecal = 407,
    CMsgTEBubbles = 408,
    CMsgTEBubbleTrail = 409,
    CMsgTEDecal = 410,
    CMsgTEWorldDecal = 411,
    CMsgTEEnergySplash = 412,
    CMsgTEFizz = 413,
    CMsgTEShatterSurface = 414,
    CMsgTEGlowSprite = 415,
    CMsgTEImpact = 416,
    CMsgTEMuzzleFlash = 417,
    CMsgTEBloodStream = 418,
    CMsgTEExplosion = 419,
    CMsgTEDust = 420,
    CMsgTELargeFunnel = 421,
    CMsgTESparks = 422,
    CMsgTEPhysicsProp = 423,
    CMsgTEPlayerDecal = 424,
    CMsgTEProjectedDecal = 425,
    CMsgTESmoke = 426,
    CDOTAUserMsg_AIDebugLine = 465,
    CDOTAUserMsg_ChatEvent = 466,
    CDOTAUserMsg_CombatHeroPositions = 467,
    CMsgDOTACombatLogEntry = 468,
    CDOTAUserMsg_CombatLogBulkData = 470,
    CDOTAUserMsg_CreateLinearProjectile = 471,
    CDOTAUserMsg_DestroyLinearProjectile = 472,
    CDOTAUserMsg_DodgeTrackingProjectiles = 473,
    CDOTAUserMsg_GlobalLightColor = 474,
    CDOTAUserMsg_GlobalLightDirection = 475,
    CDOTAUserMsg_InvalidCommand = 476,
    CDOTAUserMsg_LocationPing = 477,
    CDOTAUserMsg_MapLine = 478,
    CDOTAUserMsg_MiniKillCamInfo = 479,
    CDOTAUserMsg_MinimapDebugPoint = 480,
    CDOTAUserMsg_MinimapEvent = 481,
    CDOTAUserMsg_NevermoreRequiem = 482,
    CDOTAUserMsg_OverheadEvent = 483,
    CDOTAUserMsg_SetNextAutobuyItem = 484,
    CDOTAUserMsg_SharedCooldown = 485,
    CDOTAUserMsg_SpectatorPlayerClick = 486,
    CDOTAUserMsg_TutorialTipInfo = 487,
    CDOTAUserMsg_UnitEvent = 488,
    CUserMsg_ParticleManager2 = 489,
    CDOTAUserMsg_BotChat = 490,
    CDOTAUserMsg_HudError = 491,
    CDOTAUserMsg_ItemPurchased = 492,
    CDOTAUserMsg_Ping = 493,
    CDOTAUserMsg_ItemFound = 494,
    CDOTAUserMsg_SwapVerify = 496,
    CDOTAUserMsg_WorldLine = 497,
    CDOTAUserMsg_ItemAlert = 499,
    CDOTAUserMsg_HalloweenDrops = 500,
    CDOTAUserMsg_ChatWheel = 501,
    CDOTAUserMsg_ReceivedXmasGift = 502,
    CDOTAUserMsg_UpdateSharedContent = 503,
    CDOTAUserMsg_TutorialRequestExp = 504,
    CDOTAUserMsg_TutorialPingMinimap = 505,
    CDOTAUserMsg_GamerulesStateChanged = 506,
    CDOTAUserMsg_ShowSurvey = 507,
    CDOTAUserMsg_TutorialFade = 508,
    CDOTAUserMsg_AddQuestLogEntry = 509,
    CDOTAUserMsg_SendStatPopup = 510,
    CDOTAUserMsg_TutorialFinish = 511,
    CDOTAUserMsg_SendRoshanPopup = 512,
    CDOTAUserMsg_SendGenericToolTip = 513,
    CDOTAUserMsg_SendFinalGold = 514,
    CDOTAUserMsg_CustomMsg = 515,
    CDOTAUserMsg_CoachHUDPing = 516,
    CDOTAUserMsg_ClientLoadGridNav = 517,
    CDOTAUserMsg_TE_Projectile = 518,
    CDOTAUserMsg_TE_ProjectileLoc = 519,
    CDOTAUserMsg_TE_DotaBloodImpact = 520,
    CDOTAUserMsg_TE_UnitAnimation = 521,
    CDOTAUserMsg_TE_UnitAnimationEnd = 522,
    CDOTAUserMsg_AbilityPing = 523,
    CDOTAUserMsg_ShowGenericPopup = 524,
    CDOTAUserMsg_VoteStart = 525,
    CDOTAUserMsg_VoteUpdate = 526,
    CDOTAUserMsg_VoteEnd = 527,
    CDOTAUserMsg_BoosterState = 528,
    CDOTAUserMsg_WillPurchaseAlert = 529,
    CDOTAUserMsg_TutorialMinimapPosition = 530,
    CDOTAUserMsg_PlayerMMR = 531,
    CDOTAUserMsg_AbilitySteal = 532,
    CDOTAUserMsg_CourierKilledAlert = 533,
    CDOTAUserMsg_EnemyItemAlert = 534,
    CDOTAUserMsg_StatsMatchDetails = 535,
    CDOTAUserMsg_MiniTaunt = 536,
    CDOTAUserMsg_BuyBackStateAlert = 537,
    CDOTAUserMsg_SpeechBubble = 538,
    CDOTAUserMsg_CustomHeaderMessage = 539,
    CDOTAUserMsg_QuickBuyAlert = 540,
    CMsgCombatAnalyzerStats = 541,
    CDOTAUserMsg_PredictionResult = 542,
    CDOTAUserMsg_ModifierAlert = 543,
    CDOTAUserMsg_HPManaAlert = 544,
    CDOTAUserMsg_GlyphAlert = 545,
    CDOTAUserMsg_BeastChat = 546,
    CDOTAUserMsg_SpectatorPlayerUnitOrders = 547,
    CDOTAUserMsg_CustomHudElement_Create = 548,
    CDOTAUserMsg_CustomHudElement_Modify = 549,
    CDOTAUserMsg_CustomHudElement_Destroy = 550,
    CDOTAUserMsg_CompendiumState = 551,
    CDOTAUserMsg_ProjectionAbility = 552,
    CDOTAUserMsg_ProjectionEvent = 553,
    CMsgDOTACombatLogEntry2 = 554,
    CDOTAUserMsg_XPAlert = 555,
    CDOTAUserMsg_UpdateQuestProgress = 556,
    CDOTAMatchMetadataFile = 557,
    CMsgDOTAMatch = 558,
    CDOTAUserMsg_QuestStatus = 559,
    CDOTAUserMsg_SuggestHeroPick = 560,
    CDOTAUserMsg_SuggestHeroRole = 561,
    CDOTAUserMsg_KillcamDamageTaken = 562,
    CDOTAUserMsg_SelectPenaltyGold = 563,
    CDOTAUserMsg_RollDiceResult = 564,
    CDOTAUserMsg_FlipCoinResult = 565,
    CDOTAUserMessage_RequestItemSuggestions = 566,
    CDOTAUserMessage_TeamCaptainChanged = 567,
    CDOTAUserMsg_SendRoshanSpectatorPhase = 568,
    CDOTAUserMsg_ChatWheelCooldown = 569,
    CDOTAUserMsg_DismissAllStatPopups = 570,
    CDOTAUserMsg_TE_DestroyProjectile = 571,
    CDOTAUserMsg_HeroRelicProgress = 572,
    CDOTAUserMsg_AbilityDraftRequestAbility = 573,
    CDOTAUserMsg_ItemSold = 574,
    CDOTAUserMsg_DamageReport = 575,
    CDOTAUserMsg_SalutePlayer = 576,
    CDOTAUserMsg_MarsArenaOfBloodAttack = 580,
    CDOTAUserMsg_TipAlert = 577,
    CDOTAUserMsg_EmptyTeleportAlert = 579,
    CDOTAUserMsg_ReplaceQueryUnit = 578,
};

enum NetMessageGroups : int
{
    SYSTEM = 0,
    ENTITIES = 1,
    STRING_COMMAND = 2,
    SIGNON = 3,
    SPAWNGROUPS = 4,
    MOVE = 5,
    VOICE = 6,
    GENERIC = 7,
    STRING_TABLE = 8,
    SOUNDS = 9,

    EVENTS = 12,
    CLIENT_MESSAGES = 13,
    USER_MESSAGES = 14,
    DECALS = 15,
};

/*
class CMsg_Base
{
public:
    virtual void DESTROY1() = 0;
    virtual void DESTROY2() = 0;
    virtual std::string GetTypeName(void) = 0; // google::protobuf::Message::GetTypeName
    virtual void New(void) = 0;
    virtual void New2() = 0;
    virtual void sub_1FE1A60() = 0;
    virtual void sub_1FE1A70() = 0;
    virtual void sub_23E6980() = 0;
    virtual bool IsInitialized(void) = 0;
    virtual std::string InitializationErrorString(void) = 0;
    virtual void CheckTypeAndMergeFrom(const google::protobuf::MessageLite &other) = 0;
    virtual bool MergePartialFromCodedStream(google::protobuf::io::CodedInputStream *input) = 0;
    virtual size_t ByteSize(void) = 0; // calls google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize
    virtual void SerializeWithCachedSizes(google::protobuf::io::CodedOutputStream *output) = 0;
    virtual void SerializeWithCachedSizesToArray(unsigned char *) = 0; // calls  google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray
    virtual int GetCachedSize(void) = 0;
    virtual void sub_23CBBB0() = 0;
    virtual void sub_1FE1A80() = 0;
    virtual void CopyFrom(const google::protobuf::Message &other) = 0;
    virtual void MergeFrom(const google::protobuf::Message &other) = 0;
    virtual void DiscardUnknownFields(void) = 0;
    virtual int SpaceUsed(void) = 0;
    virtual void SetCachedSize(int) = 0;
    virtual google::protobuf::Reflection* GetReflection(void) = 0;
    virtual google::protobuf::Metadata* GetMetaData(void) = 0;
};
*/

class CMsgProtoBufHeader;
class IProtoBufSendHandler;

class CProtoBufMsgBase
{
public:
    virtual void DESTROY() = 0;
    virtual void DESTROY2() = 0;
    virtual google::protobuf::Message *GetGenericBody(void) = 0;
};

class CStructNetPacket
{
public:
    virtual void DESTROY();
    virtual void DESTROY2();
    virtual void DestroyThis(void);
    virtual int GetEMsgFormatType(void);
    virtual void* GetCNetPacket(void);
    virtual const void *PubData(void); // Pointer-Unsigned-Byte Data
    virtual uint32_t CubData(void); // Count-Unsigned-Byte Data - u can find some of this in the steamworks sdk
    virtual int GetEMsg(void);
    virtual int GetSourceJobID(void);
    virtual unsigned long long GetTargetJobID(void);
    virtual void SetTargetJobID(unsigned long long);
    virtual int64_t GetSteamID(void);
    virtual void SetSteamID(int64_t CSteamID);
    virtual unsigned int GetSourceAppID(void);
    virtual void SetSourceAppID(unsigned int);
    virtual bool BHasTargetJobName(void);
    virtual const char *GetTargetJobName(void);
};

class CProtobuffBinding
{
public:
    virtual const char* GetName(void);
    virtual int GetSize(void);
    virtual const char* ToString(google::protobuf::Message *msg, CUtlString *storage);
    virtual const char *GetGroup(void);
    virtual ColorRGBA GetGroupColor(void);
    virtual NetChannelBufType_t GetBufType(void);
    virtual bool ReadFromBuffer(google::protobuf::Message *msg, bf_read &); // true if parsing OK
    virtual bool WriteToBuffer(google::protobuf::Message *msg, bf_write &); // true if parsing OK
    virtual void AllocateMessage(void);
    virtual void DeallocateMessage(void *);
    virtual void AllocateAndCopyConstructNetMessage(void const*);
    virtual bool OkToRedispatch(void);
    virtual void Copy(void const*,void *);
};

class CNetworkSerializerPB // PB must = protobuf
{
public:
    virtual void DESTROY1() = 0;
    virtual void DESTROY2() = 0;
    virtual const char* GetUnscopedName(void) = 0;
    virtual void* GetNetMessageInfo(void) = 0;
    virtual void SetMessageID(unsigned int) = 0;
    virtual void AddCategoryMask(unsigned int bitflag, bool applyToAnotherMember) = 0;
    virtual void SwitchMode(int networkValidationMode_t) = 0;
    virtual void AllocateMessage(void) = 0;
    virtual void DeallocateMessage(void *unk) = 0;
    virtual void AllocateAndCopyConstructNetMessage(void const *) = 0;
    virtual void Serialize(void *bfWriteRef, void const *, int NetworkSerializationMode_t) = 0;
    virtual void UnSerialize(bf_read &, void *, int NetworkSerializationMode_t) = 0;

    const char *unscopedName;
    uint32_t categoryMask;
    int unk;
    CProtobuffBinding *protobufBinding;
    const char *groupName;
    short messageID;
    uint8_t groupID;
    uint8_t defaultBufferType;
    char _pad[22];
};

typedef CNetworkSerializerPB NetMessageHandle_t;

struct MessageEntryWrapper {
    void *unk[2];
    CNetworkSerializerPB *entry;
};

struct MessageEntries {
    std::array<MessageEntryWrapper, 334> messages;
};

struct NetMessageInfo_t
{
    void* pad;
    CProtobuffBinding* pProtobufBinding;
};

//"NetworkMessages::FindOrCreateNetMessage" (libnetworksystem)
class CNetworkMessages
{
public:
    virtual void RegisterNetworkCategory( unsigned int, const char* ) = 0;
    virtual void AssociateNetMessageWithChannelCategoryAbstract( NetMessageHandle_t *, unsigned int, bool) = 0;
    virtual NetMessageHandle_t* FindOrCreateNetMessage(int, void const* IProtobufBinding, unsigned int, void* INetworkSerializerBindingBuildFilter, bool, bool) = 0;
    virtual void SerializeAbstract(bf_read &buffer, NetMessageHandle_t *, void const*) = 0;
    virtual void UnserializeAbstract(bf_read &buffer, NetMessageHandle_t *, void*) = 0;
    virtual void UnserializeAbstract(bf_read &buffer, NetMessageHandle_t **, void **) = 0;
    virtual void AllocateUnserializedMessage(NetMessageHandle_t *) = 0;
    virtual void AllocateAndCopyConstructNetMessageAbstract(NetMessageHandle_t *, void const*) = 0;
    virtual void DeallocateUnserializedMessage(NetMessageHandle_t *, void*) = 0;
    virtual void RegisterNetworkFieldSerializer() = 0; // (char const*,NetworkSerializationMode_t,NetworkableDataType_t,int,NetworkFieldResult_t (*)(NetworkSerializerInfo_t const&,int,NetworkableData_t *),NetworkFieldResult_t (*)(NetworkUnserializerInfo_t const&,int,NetworkableData_t const*),ulong (*)(NetworkFieldInfo_t const&),bool (*)(FieldMetaInfo_t const&,CSchemaClassBindingBase const*,NetworkFieldInfo_t const&,void *),bool (*)(NetworkableData_t const*,CUtlString &),char const* (*)(void),NetworkFieldResult_t (*)(NetworkSerializerInfo_t const&,int,NetworkableData_t *),NetworkFieldResult_t (*)(NetworkUnserializerInfo_t const&,int,NetworkableData_t const*))
    virtual void RegisterNetworkArrayFieldSerializer() = 0; // (char const*,NetworkSerializationMode_t,NetworkFieldResult_t (*)(NetworkSerializerInfo_t const&,bf_write &,int *,void const**,bool),NetworkFieldResult_t (*)(NetworkUnserializerInfo_t const&,bf_read &,int *,void **,bool,CSchemaClassBindingBase const*),ulong (*)(NetworkFieldInfo_t const&),bool (*)(FieldMetaInfo_t const&,CSchemaClassBindingBase const*,NetworkFieldInfo_t const&,void *),NetworkFieldResult_t (*)(NetworkSerializerInfo_t const&,bf_write &,int *,void const**,bool),NetworkFieldResult_t (*)(NetworkUnserializerInfo_t const&,bf_read &,int *,void **,bool,CSchemaClassBindingBase const*))
    virtual NetMessageInfo_t* GetNetMessageInfo(NetMessageHandle_t *) = 0;
    virtual void* FindNetworkMessage(const char*) = 0;
    virtual void FindNetworkMessage2() = 0;
    virtual int GetNetworkGroupCount(void) = 0;
    virtual const char* GetNetworkGroupName(int groupId) = 0;
    virtual int FindNetworkGroup(const char*, bool) = 0;
    virtual void AssociateNetMessageGroupIdWithChannelCategory(unsigned int, const char*) = 0;
    virtual void RegisterSchemaAtomicTypeOverride(unsigned int, void *CSchemaType) = 0;
    virtual void SetNextworkSerializationContextData(const char*, int NetworkSerializationMode_t, void*) = 0;
    virtual void sub_1E1570() = 0;
    virtual void sub_1E1070() = 0;
    virtual void RegisterNetworkFieldChangeCallback() = 0; //(char const*,NetworkFieldChangedDelegateType_t,CUtlAbstractDelegate,NetworkFieldChangeCallbackPerformType_t,int)
    virtual void AllowAdditionalMessageRegistration(bool allow) = 0;
    virtual int GetFieldChangeCallbackOrderCount(void) = 0;
    virtual void GetFieldChangeCallbackPriorities(int, int*) = 0;
    virtual void RegisterFieldChangeCallbackPriority(int) = 0;
    virtual void* FindNetworkMessageByID(int) = 0;
    virtual void SetIsForServer(bool isForServer) = 0;
    virtual bool IsForServer(void) = 0;
    virtual void RegisterSchemaTypeOverride(unsigned int, const char*) = 0;
    virtual void sub_1E2170() = 0;
    virtual void sub_1E4020() = 0;
    virtual void sub_1E4C50() = 0;

    NetMessageHandle_t* GetMessageHandleByName( const char *partialName ){
        for( size_t i = 0; i < this->messageList->messages.size(); i++ ){
            if( strcasestr( this->messageList->messages[i].entry->unscopedName, partialName ) ){
                return this->messageList->messages[i].entry;
            }
        }
        return nullptr;
    }

    char _pad[0x1F0 - sizeof(void*)];
    MessageEntries *messageList; // usermessage list @ +0x1F0
    // @ +0x420 some sort of protobuf descriptions
};