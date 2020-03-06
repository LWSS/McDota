#pragma once

#include "bf_read.h"
#include "bf_write.h"
#include "CUtlString.h"

#include <google/protobuf/message.h>
#include <google/protobuf/io/coded_stream.h>

#define CASE_STRING( x ) case static_cast<int>( x ) : return #x

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

enum EDOTAGCMsg : int {
    k_EMsgGCDOTABase = 7000,
    k_EMsgGCGeneralResponse = 7001,
    k_EMsgGCGameMatchSignOut = 7004,
    k_EMsgGCGameMatchSignOutResponse = 7005,
    k_EMsgGCJoinChatChannel = 7009,
    k_EMsgGCJoinChatChannelResponse = 7010,
    k_EMsgGCOtherJoinedChannel = 7013,
    k_EMsgGCOtherLeftChannel = 7014,
    k_EMsgGCMatchHistoryList = 7017,
    k_EMsgServerToGCRequestStatus = 7026,
    k_EMsgGCGetRecentMatches = 7027,
    k_EMsgGCRecentMatchesResponse = 7028,
    k_EMsgGCStartFindingMatch = 7033,
    k_EMsgGCConnectedPlayers = 7034,
    k_EMsgGCAbandonCurrentGame = 7035,
    k_EMsgGCStopFindingMatch = 7036,
    k_EMsgGCPracticeLobbyCreate = 7038,
    k_EMsgGCPracticeLobbyLeave = 7040,
    k_EMsgGCPracticeLobbyLaunch = 7041,
    k_EMsgGCPracticeLobbyList = 7042,
    k_EMsgGCPracticeLobbyListResponse = 7043,
    k_EMsgGCPracticeLobbyJoin = 7044,
    k_EMsgGCPracticeLobbySetDetails = 7046,
    k_EMsgGCPracticeLobbySetTeamSlot = 7047,
    k_EMsgGCInitialQuestionnaireResponse = 7049,
    k_EMsgGCPracticeLobbyResponse = 7055,
    k_EMsgGCBroadcastNotification = 7056,
    k_EMsgGCLiveScoreboardUpdate = 7057,
    k_EMsgGCRequestChatChannelList = 7060,
    k_EMsgGCRequestChatChannelListResponse = 7061,
    k_EMsgGCRequestMatches = 7064,
    k_EMsgGCRequestMatchesResponse = 7065,
    k_EMsgGCRequestPlayerResources = 7068,
    k_EMsgGCRequestPlayerResourcesResponse = 7069,
    k_EMsgGCReadyUp = 7070,
    k_EMsgGCKickedFromMatchmakingQueue = 7071,
    k_EMsgGCLeaverDetected = 7072,
    k_EMsgGCSpectateFriendGame = 7073,
    k_EMsgGCSpectateFriendGameResponse = 7074,
    k_EMsgGCPlayerReports = 7075,
    k_EMsgGCReportsRemainingRequest = 7076,
    k_EMsgGCReportsRemainingResponse = 7077,
    k_EMsgGCSubmitPlayerReport = 7078,
    k_EMsgGCSubmitPlayerReportResponse = 7079,
    k_EMsgGCPracticeLobbyKick = 7081,
    k_EMsgGCReportCountsRequest = 7082,
    k_EMsgGCReportCountsResponse = 7083,
    k_EMsgGCRequestSaveGames = 7084,
    k_EMsgGCRequestSaveGamesServer = 7085,
    k_EMsgGCRequestSaveGamesResponse = 7086,
    k_EMsgGCLeaverDetectedResponse = 7087,
    k_EMsgGCPlayerFailedToConnect = 7088,
    k_EMsgGCGCToRelayConnect = 7089,
    k_EMsgGCGCToRelayConnectresponse = 7090,
    k_EMsgGCWatchGame = 7091,
    k_EMsgGCWatchGameResponse = 7092,
    k_EMsgGCBanStatusRequest = 7093,
    k_EMsgGCBanStatusResponse = 7094,
    k_EMsgGCMatchDetailsRequest = 7095,
    k_EMsgGCMatchDetailsResponse = 7096,
    k_EMsgGCCancelWatchGame = 7097,
    k_EMsgGCPopup = 7102,
    k_EMsgGCDOTAClearNotifySuccessfulReport = 7104,
    k_EMsgGCFriendPracticeLobbyListRequest = 7111,
    k_EMsgGCFriendPracticeLobbyListResponse = 7112,
    k_EMsgGCPracticeLobbyJoinResponse = 7113,
    k_EMsgClientEconNotification_Job = 7114,
    k_EMsgGCCreateTeam = 7115,
    k_EMsgGCCreateTeamResponse = 7116,
    k_EMsgGCTeamData = 7121,
    k_EMsgGCTeamInvite_InviterToGC = 7122,
    k_EMsgGCTeamInvite_GCImmediateResponseToInviter = 7123,
    k_EMsgGCTeamInvite_GCRequestToInvitee = 7124,
    k_EMsgGCTeamInvite_InviteeResponseToGC = 7125,
    k_EMsgGCTeamInvite_GCResponseToInviter = 7126,
    k_EMsgGCTeamInvite_GCResponseToInvitee = 7127,
    k_EMsgGCKickTeamMember = 7128,
    k_EMsgGCKickTeamMemberResponse = 7129,
    k_EMsgGCLeaveTeam = 7130,
    k_EMsgGCLeaveTeamResponse = 7131,
    k_EMsgGCSuggestTeamMatchmaking = 7132,
    k_EMsgGCPlayerHeroesFavoritesAdd = 7133,
    k_EMsgGCPlayerHeroesFavoritesRemove = 7134,
    k_EMsgGCApplyTeamToPracticeLobby = 7142,
    k_EMsgGCTransferTeamAdmin = 7144,
    k_EMsgGCPracticeLobbyJoinBroadcastChannel = 7149,
    k_EMsgGC_TournamentItemEvent = 7150,
    k_EMsgGC_TournamentItemEventResponse = 7151,
    k_EMsgCastMatchVote = 7152,
    k_EMsgCastMatchVoteResponse = 7153,
    k_EMsgRetrieveMatchVote = 7154,
    k_EMsgRetrieveMatchVoteResponse = 7155,
    k_EMsgTeamFanfare = 7156,
    k_EMsgResponseTeamFanfare = 7157,
    k_EMsgGC_GameServerUploadSaveGame = 7158,
    k_EMsgGC_GameServerSaveGameResult = 7159,
    k_EMsgGC_GameServerGetLoadGame = 7160,
    k_EMsgGC_GameServerGetLoadGameResult = 7161,
    k_EMsgGCEditTeamDetails = 7166,
    k_EMsgGCEditTeamDetailsResponse = 7167,
    k_EMsgGCProTeamListRequest = 7168,
    k_EMsgGCProTeamListResponse = 7169,
    k_EMsgGCReadyUpStatus = 7170,
    k_EMsgGCHallOfFame = 7171,
    k_EMsgGCHallOfFameRequest = 7172,
    k_EMsgGCHallOfFameResponse = 7173,
    k_EMsgGCGenerateDiretidePrizeList = 7174,
    k_EMsgGCRewardDiretidePrizes = 7176,
    k_EMsgGCDiretidePrizesRewardedResponse = 7177,
    k_EMsgGCHalloweenHighScoreRequest = 7178,
    k_EMsgGCHalloweenHighScoreResponse = 7179,
    k_EMsgGCGenerateDiretidePrizeListResponse = 7180,
    k_EMsgGCStorePromoPagesRequest = 7182,
    k_EMsgGCStorePromoPagesResponse = 7183,
    k_EMsgGCToGCMatchCompleted = 7186,
    k_EMsgGCBalancedShuffleLobby = 7188,
    k_EMsgGCToGCCheckLeaguePermission = 7189,
    k_EMsgGCToGCCheckLeaguePermissionResponse = 7190,
    k_EMsgGCMatchmakingStatsRequest = 7197,
    k_EMsgGCMatchmakingStatsResponse = 7198,
    k_EMsgGCBotGameCreate = 7199,
    k_EMsgGCSetMatchHistoryAccess = 7200,
    k_EMsgGCSetMatchHistoryAccessResponse = 7201,
    k_EMsgUpgradeLeagueItem = 7203,
    k_EMsgUpgradeLeagueItemResponse = 7204,
    k_EMsgGCTeamMemberProfileRequest = 7205,
    k_EMsgGCWatchDownloadedReplay = 7206,
    k_EMsgGCSetMapLocationState = 7207,
    k_EMsgGCSetMapLocationStateResponse = 7208,
    k_EMsgGCResetMapLocations = 7209,
    k_EMsgGCResetMapLocationsResponse = 7210,
    k_EMsgRefreshPartnerAccountLink = 7216,
    k_EMsgClientsRejoinChatChannels = 7217,
    k_EMsgGCToGCGetUserChatInfo = 7218,
    k_EMsgGCToGCGetUserChatInfoResponse = 7219,
    k_EMsgGCToGCLeaveAllChatChannels = 7220,
    k_EMsgGCToGCUpdateAccountChatBan = 7221,
    k_EMsgGCGuildCreateRequest = 7222,
    k_EMsgGCGuildCreateResponse = 7223,
    k_EMsgGCGuildSetAccountRoleRequest = 7224,
    k_EMsgGCGuildSetAccountRoleResponse = 7225,
    k_EMsgGCRequestGuildData = 7226,
    k_EMsgGCGuildData = 7227,
    k_EMsgGCGuildInviteAccountRequest = 7228,
    k_EMsgGCGuildInviteAccountResponse = 7229,
    k_EMsgGCGuildCancelInviteRequest = 7230,
    k_EMsgGCGuildCancelInviteResponse = 7231,
    k_EMsgGCGuildUpdateDetailsRequest = 7232,
    k_EMsgGCGuildUpdateDetailsResponse = 7233,
    k_EMsgGCToGCCanInviteUserToTeam = 7234,
    k_EMsgGCToGCCanInviteUserToTeamResponse = 7235,
    k_EMsgGCToGCGetUserRank = 7236,
    k_EMsgGCToGCGetUserRankResponse = 7237,
    k_EMsgGCToGCUpdateTeamStats = 7240,
    k_EMsgGCToGCValidateTeam = 7241,
    k_EMsgGCToGCValidateTeamResponse = 7242,
    k_EMsgGCPassportDataRequest = 7248,
    k_EMsgGCPassportDataResponse = 7249,
    k_EMsgGCNotInGuildData = 7251,
    k_EMsgGCGuildInviteData = 7254,
    k_EMsgGCToGCGetLeagueAdmin = 7255,
    k_EMsgGCToGCGetLeagueAdminResponse = 7256,
    k_EMsgGCRequestLeaguePrizePool = 7258,
    k_EMsgGCRequestLeaguePrizePoolResponse = 7259,
    k_EMsgGCToGCUpdateOpenGuildPartyRequest = 7261,
    k_EMsgGCToGCUpdateOpenGuildPartyResponse = 7262,
    k_EMsgGCToGCDestroyOpenGuildPartyRequest = 7263,
    k_EMsgGCToGCDestroyOpenGuildPartyResponse = 7264,
    k_EMsgGCGuildUpdateMessage = 7265,
    k_EMsgGCPartySetOpenGuildRequest = 7266,
    k_EMsgGCPartySetOpenGuildResponse = 7267,
    k_EMsgGCGuildOpenPartyRefresh = 7268,
    k_EMsgGCJoinOpenGuildPartyRequest = 7269,
    k_EMsgGCJoinOpenGuildPartyResponse = 7270,
    k_EMsgGCLeaveChatChannel = 7272,
    k_EMsgGCChatMessage = 7273,
    k_EMsgGCGetHeroStandings = 7274,
    k_EMsgGCGetHeroStandingsResponse = 7275,
    k_EMsgGCGuildEditLogoRequest = 7279,
    k_EMsgGCGuildEditLogoResponse = 7280,
    k_EMsgGCGuildmatePracticeLobbyListRequest = 7281,
    k_EMsgGCGuildmatePracticeLobbyListResponse = 7282,
    k_EMsgGCItemEditorReservationsRequest = 7283,
    k_EMsgGCItemEditorReservationsResponse = 7284,
    k_EMsgGCItemEditorReserveItemDef = 7285,
    k_EMsgGCItemEditorReserveItemDefResponse = 7286,
    k_EMsgGCItemEditorReleaseReservation = 7287,
    k_EMsgGCItemEditorReleaseReservationResponse = 7288,
    k_EMsgGCRewardTutorialPrizes = 7289,
    k_EMsgGCLastHitChallengeHighScorePost = 7290,
    k_EMsgGCLastHitChallengeHighScoreRequest = 7291,
    k_EMsgGCLastHitChallengeHighScoreResponse = 7292,
    k_EMsgGCCreateFantasyLeagueRequest = 7293,
    k_EMsgGCCreateFantasyLeagueResponse = 7294,
    k_EMsgGCFantasyLeagueInfoRequest = 7297,
    k_EMsgGCFantasyLeagueInfoResponse = 7298,
    k_EMsgGCFantasyLeagueInfo = 7299,
    k_EMsgGCCreateFantasyTeamRequest = 7300,
    k_EMsgGCCreateFantasyTeamResponse = 7301,
    k_EMsgGCEditFantasyTeamRequest = 7302,
    k_EMsgGCEditFantasyTeamResponse = 7303,
    k_EMsgGCFantasyTeamInfoRequestByFantasyLeagueID = 7304,
    k_EMsgGCFantasyTeamInfoRequestByOwnerAccountID = 7305,
    k_EMsgGCFantasyTeamInfoResponse = 7306,
    k_EMsgGCFantasyTeamInfo = 7307,
    k_EMsgGCFantasyLivePlayerStats = 7308,
    k_EMsgGCFantasyFinalPlayerStats = 7309,
    k_EMsgGCFantasyMatch = 7310,
    k_EMsgGCFantasyTeamScoreRequest = 7312,
    k_EMsgGCFantasyTeamScoreResponse = 7313,
    k_EMsgGCFantasyTeamStandingsRequest = 7314,
    k_EMsgGCFantasyTeamStandingsResponse = 7315,
    k_EMsgGCFantasyPlayerScoreRequest = 7316,
    k_EMsgGCFantasyPlayerScoreResponse = 7317,
    k_EMsgGCFantasyPlayerStandingsRequest = 7318,
    k_EMsgGCFantasyPlayerStandingsResponse = 7319,
    k_EMsgGCFlipLobbyTeams = 7320,
    k_EMsgGCCustomGameCreate = 7321,
    k_EMsgGCToGCProcessPlayerReportForTarget = 7324,
    k_EMsgGCToGCProcessReportSuccess = 7325,
    k_EMsgGCNotifyAccountFlagsChange = 7326,
    k_EMsgGCSetProfilePrivacy = 7327,
    k_EMsgGCSetProfilePrivacyResponse = 7328,
    k_EMsgGCFantasyLeagueCreateInfoRequest = 7331,
    k_EMsgGCFantasyLeagueCreateInfoResponse = 7332,
    k_EMsgGCFantasyLeagueInviteInfoRequest = 7333,
    k_EMsgGCFantasyLeagueInviteInfoResponse = 7334,
    k_EMsgGCClientIgnoredUser = 7335,
    k_EMsgGCFantasyLeagueCreateRequest = 7336,
    k_EMsgGCFantasyLeagueCreateResponse = 7337,
    k_EMsgGCFantasyTeamCreateRequest = 7338,
    k_EMsgGCFantasyTeamCreateResponse = 7339,
    k_EMsgGCFantasyLeagueFriendJoinListRequest = 7340,
    k_EMsgGCFantasyLeagueFriendJoinListResponse = 7341,
    k_EMsgGCClientSuspended = 7342,
    k_EMsgGCPartyMemberSetCoach = 7343,
    k_EMsgGCFantasyLeagueEditInvitesRequest = 7344,
    k_EMsgGCFantasyLeagueEditInvitesResponse = 7345,
    k_EMsgGCPracticeLobbySetCoach = 7346,
    k_EMsgGCFantasyLeagueEditInfoRequest = 7347,
    k_EMsgGCFantasyLeagueEditInfoResponse = 7348,
    k_EMsgGCFantasyLeagueDraftStatusRequest = 7349,
    k_EMsgGCFantasyLeagueDraftStatus = 7350,
    k_EMsgGCFantasyLeagueDraftPlayerRequest = 7351,
    k_EMsgGCFantasyLeagueDraftPlayerResponse = 7352,
    k_EMsgGCFantasyLeagueMatchupsRequest = 7353,
    k_EMsgGCFantasyLeagueMatchupsResponse = 7354,
    k_EMsgGCFantasyTeamRosterSwapRequest = 7355,
    k_EMsgGCFantasyTeamRosterSwapResponse = 7356,
    k_EMsgGCFantasyTeamRosterRequest = 7357,
    k_EMsgGCFantasyTeamRosterResponse = 7358,
    k_EMsgGCFantasyTeamRosterAddDropRequest = 7361,
    k_EMsgGCFantasyTeamRosterAddDropResponse = 7362,
    k_EMsgPresentedClientTerminateDlg = 7363,
    k_EMsgGCFantasyPlayerHisoricalStatsRequest = 7364,
    k_EMsgGCFantasyPlayerHisoricalStatsResponse = 7365,
    k_EMsgGCPCBangTimedRewardMessage = 7366,
    k_EMsgGCLobbyUpdateBroadcastChannelInfo = 7367,
    k_EMsgGCFantasyTeamTradesRequest = 7368,
    k_EMsgGCFantasyTeamTradesResponse = 7369,
    k_EMsgGCFantasyTeamTradeCancelRequest = 7370,
    k_EMsgGCFantasyTeamTradeCancelResponse = 7371,
    k_EMsgGCToGCGrantTournamentItem = 7372,
    k_EMsgGCProcessFantasyScheduledEvent = 7373,
    k_EMsgGCToGCUpgradeTwitchViewerItems = 7375,
    k_EMsgGCToGCGetLiveMatchAffiliates = 7376,
    k_EMsgGCToGCGetLiveMatchAffiliatesResponse = 7377,
    k_EMsgGCToGCUpdatePlayerPennantCounts = 7378,
    k_EMsgGCToGCGetPlayerPennantCounts = 7379,
    k_EMsgGCToGCGetPlayerPennantCountsResponse = 7380,
    k_EMsgGCGameMatchSignOutPermissionRequest = 7381,
    k_EMsgGCGameMatchSignOutPermissionResponse = 7382,
    k_EMsgDOTAChatChannelMemberUpdate = 7383,
    k_EMsgDOTAAwardEventPoints = 7384,
    k_EMsgDOTAGetEventPoints = 7387,
    k_EMsgDOTAGetEventPointsResponse = 7388,
    k_EMsgDOTASendFriendRecruits = 7393,
    k_EMsgDOTAFriendRecruitsRequest = 7394,
    k_EMsgDOTAFriendRecruitsResponse = 7395,
    k_EMsgDOTAFriendRecruitInviteAcceptDecline = 7396,
    k_EMsgGCPartyLeaderWatchGamePrompt = 7397,
    k_EMsgDOTAFrostivusTimeElapsed = 7398,
    k_EMsgDOTALiveLeagueGameUpdate = 7402,
    k_EMsgDOTAChatGetUserList = 7403,
    k_EMsgDOTAChatGetUserListResponse = 7404,
    k_EMsgGCCompendiumSetSelection = 7405,
    k_EMsgGCCompendiumDataRequest = 7406,
    k_EMsgGCCompendiumDataResponse = 7407,
    k_EMsgDOTAGetPlayerMatchHistory = 7408,
    k_EMsgDOTAGetPlayerMatchHistoryResponse = 7409,
    k_EMsgGCToGCMatchmakingAddParty = 7410,
    k_EMsgGCToGCMatchmakingRemoveParty = 7411,
    k_EMsgGCToGCMatchmakingRemoveAllParties = 7412,
    k_EMsgGCToGCMatchmakingMatchFound = 7413,
    k_EMsgGCToGCUpdateMatchManagementStats = 7414,
    k_EMsgGCToGCUpdateMatchmakingStats = 7415,
    k_EMsgGCToServerPingRequest = 7416,
    k_EMsgGCToServerPingResponse = 7417,
    k_EMsgGCToServerConsoleCommand = 7418,
    k_EMsgGCMakeOffering = 7423,
    k_EMsgGCRequestOfferings = 7424,
    k_EMsgGCRequestOfferingsResponse = 7425,
    k_EMsgGCToGCProcessMatchLeaver = 7426,
    k_EMsgGCNotificationsRequest = 7427,
    k_EMsgGCNotificationsResponse = 7428,
    k_EMsgGCToGCModifyNotification = 7429,
    k_EMsgGCToGCSetNewNotifications = 7430,
    k_EMsgGCLeagueAdminList = 7434,
    k_EMsgGCNotificationsMarkReadRequest = 7435,
    k_EMsgGCFantasyMessageAdd = 7436,
    k_EMsgGCFantasyMessagesRequest = 7437,
    k_EMsgGCFantasyMessagesResponse = 7438,
    k_EMsgGCFantasyScheduledMatchesRequest = 7439,
    k_EMsgGCFantasyScheduledMatchesResponse = 7440,
    k_EMsgGCEventGameCreate = 7443,
    k_EMsgGCPerfectWorldUserLookupRequest = 7444,
    k_EMsgGCPerfectWorldUserLookupResponse = 7445,
    k_EMsgGCFantasyRemoveOwner = 7448,
    k_EMsgGCFantasyRemoveOwnerResponse = 7449,
    k_EMsgGCRequestBatchPlayerResources = 7450,
    k_EMsgGCRequestBatchPlayerResourcesResponse = 7451,
    k_EMsgGCToGCSendUpdateLeagues = 7452,
    k_EMsgGCCompendiumSetSelectionResponse = 7453,
    k_EMsgGCPlayerInfoRequest = 7454,
    k_EMsgGCPlayerInfo = 7455,
    k_EMsgGCPlayerInfoSubmit = 7456,
    k_EMsgGCPlayerInfoSubmitResponse = 7457,
    k_EMsgGCToGCGetAccountLevel = 7458,
    k_EMsgGCToGCGetAccountLevelResponse = 7459,
    k_EMsgGCToGCGetAccountPartner = 7460,
    k_EMsgGCToGCGetAccountPartnerResponse = 7461,
    k_EMsgDOTAGetWeekendTourneySchedule = 7464,
    k_EMsgDOTAWeekendTourneySchedule = 7465,
    k_EMsgGCJoinableCustomGameModesRequest = 7466,
    k_EMsgGCJoinableCustomGameModesResponse = 7467,
    k_EMsgGCJoinableCustomLobbiesRequest = 7468,
    k_EMsgGCJoinableCustomLobbiesResponse = 7469,
    k_EMsgGCQuickJoinCustomLobby = 7470,
    k_EMsgGCQuickJoinCustomLobbyResponse = 7471,
    k_EMsgGCToGCGrantEventPointAction = 7472,
    k_EMsgServerGrantSurveyPermission = 7475,
    k_EMsgServerGrantSurveyPermissionResponse = 7476,
    k_EMsgClientProvideSurveyResult = 7477,
    k_EMsgGCToGCSetCompendiumSelection = 7478,
    k_EMsgGCToGCUpdateTI4HeroQuest = 7480,
    k_EMsgGCCompendiumDataChanged = 7481,
    k_EMsgDOTAFantasyLeagueFindRequest = 7482,
    k_EMsgDOTAFantasyLeagueFindResponse = 7483,
    k_EMsgGCHasItemQuery = 7484,
    k_EMsgGCHasItemResponse = 7485,
    k_EMsgGCConsumeFantasyTicket = 7486,
    k_EMsgGCConsumeFantasyTicketFailure = 7487,
    k_EMsgGCToGCGrantEventPointActionMsg = 7488,
    k_EMsgClientToGCTrackDialogResult = 7489,
    k_EMsgGCFantasyLeaveLeagueRequest = 7490,
    k_EMsgGCFantasyLeaveLeagueResponse = 7491,
    k_EMsgGCToGCGetCompendiumSelections = 7492,
    k_EMsgGCToGCGetCompendiumSelectionsResponse = 7493,
    k_EMsgServerToGCMatchConnectionStats = 7494,
    k_EMsgGCToClientTournamentItemDrop = 7495,
    k_EMsgSQLDelayedGrantLeagueDrop = 7496,
    k_EMsgServerGCUpdateSpectatorCount = 7497,
    k_EMsgGCFantasyPlayerScoreDetailsRequest = 7499,
    k_EMsgGCFantasyPlayerScoreDetailsResponse = 7500,
    k_EMsgGCToGCEmoticonUnlock = 7501,
    k_EMsgSignOutDraftInfo = 7502,
    k_EMsgClientToGCEmoticonDataRequest = 7503,
    k_EMsgGCToClientEmoticonData = 7504,
    k_EMsgGCPracticeLobbyToggleBroadcastChannelCameramanStatus = 7505,
    k_EMsgGCToGCCreateWeekendTourneyRequest = 7506,
    k_EMsgGCToGCCreateWeekendTourneyResponse = 7507,
    k_EMsgClientToGCSetAdditionalEquips = 7513,
    k_EMsgClientToGCGetAdditionalEquips = 7514,
    k_EMsgClientToGCGetAdditionalEquipsResponse = 7515,
    k_EMsgServerToGCGetAdditionalEquips = 7516,
    k_EMsgServerToGCGetAdditionalEquipsResponse = 7517,
    k_EMsgDOTARedeemItem = 7518,
    k_EMsgDOTARedeemItemResponse = 7519,
    k_EMsgSQLGCToGCGrantAllHeroProgress = 7520,
    k_EMsgClientToGCGetAllHeroProgress = 7521,
    k_EMsgClientToGCGetAllHeroProgressResponse = 7522,
    k_EMsgGCToGCGetServerForClient = 7523,
    k_EMsgGCToGCGetServerForClientResponse = 7524,
    k_EMsgSQLProcessTournamentGameOutcome = 7525,
    k_EMsgSQLGrantTrophyToAccount = 7526,
    k_EMsgClientToGCGetTrophyList = 7527,
    k_EMsgClientToGCGetTrophyListResponse = 7528,
    k_EMsgGCToClientTrophyAwarded = 7529,
    k_EMsgGCGameBotMatchSignOut = 7530,
    k_EMsgGCGameBotMatchSignOutPermissionRequest = 7531,
    k_EMsgSignOutBotInfo = 7532,
    k_EMsgGCToGCUpdateProfileCards = 7533,
    k_EMsgClientToGCGetProfileCard = 7534,
    k_EMsgClientToGCGetProfileCardResponse = 7535,
    k_EMsgServerToGCGetProfileCard = 7536,
    k_EMsgServerToGCGetProfileCardResponse = 7537,
    k_EMsgClientToGCSetProfileCardSlots = 7538,
    k_EMsgGCToClientProfileCardUpdated = 7539,
    k_EMsgServerToGCVictoryPredictions = 7540,
    k_EMsgClientToGCMarkNotificationListRead = 7542,
    k_EMsgServerToGCSuspiciousActivity = 7544,
    k_EMsgSignOutCommunicationSummary = 7545,
    k_EMsgServerToGCRequestStatus_Response = 7546,
    k_EMsgClientToGCCreateHeroStatue = 7547,
    k_EMsgGCToClientHeroStatueCreateResult = 7548,
    k_EMsgGCGCToLANServerRelayConnect = 7549,
    k_EMsgServerToGCGetIngameEventData = 7551,
    k_EMsgGCToGCUpdateIngameEventDataBroadcast = 7552,
    k_EMsgGCToServerIngameEventData_OraclePA = 7553,
    k_EMsgServerToGCReportKillSummaries = 7554,
    k_EMsgGCToGCReportKillSummaries = 7555,
    k_EMsgGCToGCUpdateAssassinMinigame = 7556,
    k_EMsgGCToGCFantasySetMatchLeague = 7557,
    k_EMsgGCToGCUpdatePlayerPredictions = 7561,
    k_EMsgGCToServerPredictionResult = 7562,
    k_EMsgServerToGCSignoutAwardAdditionalDrops = 7563,
    k_EMsgGCToGCSignoutAwardAdditionalDrops = 7564,
    k_EMsgGCToClientEventStatusChanged = 7565,
    k_EMsgGCHasItemDefsQuery = 7566,
    k_EMsgGCHasItemDefsResponse = 7567,
    k_EMsgGCToGCReplayMonitorValidateReplay = 7569,
    k_EMsgLobbyEventPoints = 7572,
    k_EMsgGCToGCGetCustomGameTickets = 7573,
    k_EMsgGCToGCGetCustomGameTicketsResponse = 7574,
    k_EMsgGCToGCCustomGamePlayed = 7576,
    k_EMsgGCToGCGrantEventPointsToUser = 7577,
    k_EMsgGCToGCSetEventMMPanicFlushTime = 7578,
    k_EMsgGameserverCrashReport = 7579,
    k_EMsgGameserverCrashReportResponse = 7580,
    k_EMsgGCToClientSteamDatagramTicket = 7581,
    k_EMsgGCToGCGrantEventOwnership = 7582,
    k_EMsgGCToGCSendAccountsEventPoints = 7583,
    k_EMsgClientToGCRerollPlayerChallenge = 7584,
    k_EMsgServerToGCRerollPlayerChallenge = 7585,
    k_EMsgGCRerollPlayerChallengeResponse = 7586,
    k_EMsgSignOutUpdatePlayerChallenge = 7587,
    k_EMsgClientToGCSetPartyLeader = 7588,
    k_EMsgClientToGCCancelPartyInvites = 7589,
    k_EMsgGCToGCMasterReloadAccount = 7590,
    k_EMsgSQLGrantLeagueMatchToTicketHolders = 7592,
    k_EMsgClientToGCSetAdditionalEquipsResponse = 7593,
    k_EMsgGCToGCEmoticonUnlockNoRollback = 7594,
    k_EMsgGCToGCGetCompendiumFanfare = 7595,
    k_EMsgGCToGCChatNewUserSession = 7598,
    k_EMsgClientToGCApplyGemCombiner = 7603,
    k_EMsgClientToGCDOTACreateStaticRecipe = 7604,
    k_EMsgClientToGCDOTACreateStaticRecipeResponse = 7605,
    k_EMsgClientToGCGetAllHeroOrder = 7606,
    k_EMsgClientToGCGetAllHeroOrderResponse = 7607,
    k_EMsgSQLGCToGCGrantBadgePoints = 7608,
    k_EMsgGCToGCGetAccountMatchStatus = 7609,
    k_EMsgGCToGCGetAccountMatchStatusResponse = 7610,
    k_EMsgGCToGCCheckOwnsEntireEmoticonRange = 7611,
    k_EMsgGCToGCCheckOwnsEntireEmoticonRangeResponse = 7612,
    k_EMsgClientToGCRecycleHeroRelic = 7619,
    k_EMsgClientToGCRecycleHeroRelicResponse = 7620,
    k_EMsgGCToGCRevokeEventOwnership = 7621,
    k_EMsgGCToGCUnlockEventPointSpending = 7622,
    k_EMsgGCToClientRequestLaneSelection = 7623,
    k_EMsgGCToClientRequestLaneSelectionResponse = 7624,
    k_EMsgServerToGCCavernCrawlIsHeroActive = 7625,
    k_EMsgServerToGCCavernCrawlIsHeroActiveResponse = 7626,
    k_EMsgClientToGCPlayerCardSpecificPurchaseRequest = 7627,
    k_EMsgClientToGCPlayerCardSpecificPurchaseResponse = 7628,
    k_EMsgGCtoServerTensorflowInstance = 7629,
    k_EMsgSQLSetIsLeagueAdmin = 7630,
    k_EMsgGCToGCGetLiveLeagueMatches = 7631,
    k_EMsgGCToGCGetLiveLeagueMatchesResponse = 7632,
    k_EMsgDOTALeagueInfoListAdminsRequest = 7633,
    k_EMsgDOTALeagueInfoListAdminsReponse = 7634,
    k_EMsgGCToGCLeagueMatchStarted = 7645,
    k_EMsgGCToGCLeagueMatchCompleted = 7646,
    k_EMsgGCToGCLeagueMatchStartedResponse = 7647,
    k_EMsgDOTALeagueNodeRequest = 7648,
    k_EMsgDOTALeagueNodeResponse = 7649,
    k_EMsgDOTALeagueAvailableLobbyNodesRequest = 7650,
    k_EMsgDOTALeagueAvailableLobbyNodes = 7651,
    k_EMsgGCToGCLeagueRequest = 7652,
    k_EMsgGCToGCLeagueResponse = 7653,
    k_EMsgGCToGCLeagueNodeGroupRequest = 7654,
    k_EMsgGCToGCLeagueNodeGroupResponse = 7655,
    k_EMsgGCToGCLeagueNodeRequest = 7656,
    k_EMsgGCToGCLeagueNodeResponse = 7657,
    k_EMsgGCToGCRealtimeStatsTerseRequest = 7658,
    k_EMsgGCToGCRealtimeStatsTerseResponse = 7659,
    k_EMsgGCToGCGetTopMatchesRequest = 7660,
    k_EMsgGCToGCGetTopMatchesResponse = 7661,
    k_EMsgClientToGCGetFilteredPlayers = 7662,
    k_EMsgGCToClientGetFilteredPlayersResponse = 7663,
    k_EMsgClientToGCRemoveFilteredPlayer = 7664,
    k_EMsgGCToClientRemoveFilteredPlayerResponse = 7665,
    k_EMsgGCToClientPlayerBeaconState = 7666,
    k_EMsgGCToClientPartyBeaconUpdate = 7667,
    k_EMsgGCToClientPartySearchInvite = 7668,
    k_EMsgClientToGCUpdatePartyBeacon = 7669,
    k_EMsgClientToGCRequestActiveBeaconParties = 7670,
    k_EMsgGCToClientRequestActiveBeaconPartiesResponse = 7671,
    k_EMsgClientToGCManageFavorites = 7672,
    k_EMsgGCToClientManageFavoritesResponse = 7673,
    k_EMsgClientToGCJoinPartyFromBeacon = 7674,
    k_EMsgGCToClientJoinPartyFromBeaconResponse = 7675,
    k_EMsgClientToGCGetFavoritePlayers = 7676,
    k_EMsgGCToClientGetFavoritePlayersResponse = 7677,
    k_EMsgClientToGCVerifyFavoritePlayers = 7678,
    k_EMsgGCToClientVerifyFavoritePlayersResponse = 7679,
    k_EMsgGCToClientPartySearchInvites = 7680,
    k_EMsgGCToClientRequestMMInfo = 7681,
    k_EMsgClientToGCMMInfo = 7682,
    k_EMsgGCDev_GrantWarKill = 8001,
    k_EMsgServerToGCLockCharmTrading = 8004,
    k_EMsgClientToGCPlayerStatsRequest = 8006,
    k_EMsgGCToClientPlayerStatsResponse = 8007,
    k_EMsgGCClearPracticeLobbyTeam = 8008,
    k_EMsgClientToGCFindTopSourceTVGames = 8009,
    k_EMsgGCToClientFindTopSourceTVGamesResponse = 8010,
    k_EMsgGCLobbyList = 8011,
    k_EMsgGCLobbyListResponse = 8012,
    k_EMsgGCPlayerStatsMatchSignOut = 8013,
    k_EMsgClientToGCCustomGamePlayerCountRequest = 8014,
    k_EMsgGCToClientCustomGamePlayerCountResponse = 8015,
    k_EMsgClientToGCSocialFeedPostCommentRequest = 8016,
    k_EMsgGCToClientSocialFeedPostCommentResponse = 8017,
    k_EMsgClientToGCCustomGamesFriendsPlayedRequest = 8018,
    k_EMsgGCToClientCustomGamesFriendsPlayedResponse = 8019,
    k_EMsgClientToGCFriendsPlayedCustomGameRequest = 8020,
    k_EMsgGCToClientFriendsPlayedCustomGameResponse = 8021,
    k_EMsgGCTopCustomGamesList = 8024,
    k_EMsgClientToGCSocialMatchPostCommentRequest = 8025,
    k_EMsgGCToClientSocialMatchPostCommentResponse = 8026,
    k_EMsgClientToGCSocialMatchDetailsRequest = 8027,
    k_EMsgGCToClientSocialMatchDetailsResponse = 8028,
    k_EMsgClientToGCSetPartyOpen = 8029,
    k_EMsgClientToGCMergePartyInvite = 8030,
    k_EMsgGCToClientMergeGroupInviteReply = 8031,
    k_EMsgClientToGCMergePartyResponse = 8032,
    k_EMsgGCToClientMergePartyResponseReply = 8033,
    k_EMsgClientToGCGetProfileCardStats = 8034,
    k_EMsgClientToGCGetProfileCardStatsResponse = 8035,
    k_EMsgClientToGCTopLeagueMatchesRequest = 8036,
    k_EMsgClientToGCTopFriendMatchesRequest = 8037,
    k_EMsgGCToClientProfileCardStatsUpdated = 8040,
    k_EMsgServerToGCRealtimeStats = 8041,
    k_EMsgGCToServerRealtimeStatsStartStop = 8042,
    k_EMsgGCToGCGetServersForClients = 8045,
    k_EMsgGCToGCGetServersForClientsResponse = 8046,
    k_EMsgGCPracticeLobbyKickFromTeam = 8047,
    k_EMsgDOTAChatGetMemberCount = 8048,
    k_EMsgDOTAChatGetMemberCountResponse = 8049,
    k_EMsgClientToGCSocialFeedPostMessageRequest = 8050,
    k_EMsgGCToClientSocialFeedPostMessageResponse = 8051,
    k_EMsgCustomGameListenServerStartedLoading = 8052,
    k_EMsgCustomGameClientFinishedLoading = 8053,
    k_EMsgGCPracticeLobbyCloseBroadcastChannel = 8054,
    k_EMsgGCStartFindingMatchResponse = 8055,
    k_EMsgSQLGCToGCGrantAccountFlag = 8057,
    k_EMsgGCToGCGetAccountFlags = 8058,
    k_EMsgGCToGCGetAccountFlagsResponse = 8059,
    k_EMsgSignOutWagerStats = 8060,
    k_EMsgGCToClientTopLeagueMatchesResponse = 8061,
    k_EMsgGCToClientTopFriendMatchesResponse = 8062,
    k_EMsgClientToGCMatchesMinimalRequest = 8063,
    k_EMsgClientToGCMatchesMinimalResponse = 8064,
    k_EMsgGCToGCGetProfileBadgePoints = 8065,
    k_EMsgGCToGCGetProfileBadgePointsResponse = 8066,
    k_EMsgGCToClientChatRegionsEnabled = 8067,
    k_EMsgClientToGCPingData = 8068,
    k_EMsgServerToGCMatchDetailsRequest = 8069,
    k_EMsgGCToServerMatchDetailsResponse = 8070,
    k_EMsgGCToGCEnsureAccountInParty = 8071,
    k_EMsgGCToGCEnsureAccountInPartyResponse = 8072,
    k_EMsgClientToGCGetProfileTickets = 8073,
    k_EMsgClientToGCGetProfileTicketsResponse = 8074,
    k_EMsgGCToClientMatchGroupsVersion = 8075,
    k_EMsgClientToGCH264Unsupported = 8076,
    k_EMsgClientToGCRequestH264Support = 8077,
    k_EMsgClientToGCGetQuestProgress = 8078,
    k_EMsgClientToGCGetQuestProgressResponse = 8079,
    k_EMsgSignOutXPCoins = 8080,
    k_EMsgGCToClientMatchSignedOut = 8081,
    k_EMsgGCGetHeroStatsHistory = 8082,
    k_EMsgGCGetHeroStatsHistoryResponse = 8083,
    k_EMsgClientToGCPrivateChatInvite = 8084,
    k_EMsgClientToGCPrivateChatKick = 8088,
    k_EMsgClientToGCPrivateChatPromote = 8089,
    k_EMsgClientToGCPrivateChatDemote = 8090,
    k_EMsgGCToClientPrivateChatResponse = 8091,
    k_EMsgClientToGCPrivateChatInfoRequest = 8092,
    k_EMsgGCToClientPrivateChatInfoResponse = 8093,
    k_EMsgClientToGCLatestConductScorecardRequest = 8095,
    k_EMsgClientToGCLatestConductScorecard = 8096,
    k_EMsgServerToGCPostMatchTip = 8097,
    k_EMsgServerToGCPostMatchTipResponse = 8098,
    k_EMsgClientToGCWageringRequest = 8099,
    k_EMsgGCToClientWageringResponse = 8100,
    k_EMsgClientToGCEventGoalsRequest = 8103,
    k_EMsgClientToGCEventGoalsResponse = 8104,
    k_EMsgClientToGCLeaguePredictions = 8106,
    k_EMsgGCToClientLeaguePredictionsResponse = 8107,
    k_EMsgGCToGCLeaguePredictionsUpdate = 8108,
    k_EMsgClientToGCSuspiciousActivity = 8109,
    k_EMsgGCToGCAddUserToPostGameChat = 8110,
    k_EMsgClientToGCHasPlayerVotedForMVP = 8111,
    k_EMsgClientToGCHasPlayerVotedForMVPResponse = 8112,
    k_EMsgClientToGCVoteForMVP = 8113,
    k_EMsgClientToGCVoteForMVPResponse = 8114,
    k_EMsgGCToGCGetEventOwnership = 8115,
    k_EMsgGCToGCGetEventOwnershipResponse = 8116,
    k_EMsgGCToClientAutomatedTournamentStateChange = 8117,
    k_EMsgClientToGCWeekendTourneyOpts = 8118,
    k_EMsgClientToGCWeekendTourneyOptsResponse = 8119,
    k_EMsgClientToGCWeekendTourneyLeave = 8120,
    k_EMsgClientToGCWeekendTourneyLeaveResponse = 8121,
    k_EMsgClientToGCTeammateStatsRequest = 8124,
    k_EMsgClientToGCTeammateStatsResponse = 8125,
    k_EMsgClientToGCGetGiftPermissions = 8126,
    k_EMsgClientToGCGetGiftPermissionsResponse = 8127,
    k_EMsgClientToGCVoteForArcana = 8128,
    k_EMsgClientToGCVoteForArcanaResponse = 8129,
    k_EMsgClientToGCRequestArcanaVotesRemaining = 8130,
    k_EMsgClientToGCRequestArcanaVotesRemainingResponse = 8131,
    k_EMsgGCTransferTeamAdminResponse = 8132,
    k_EMsgGCToClientTeamInfo = 8135,
    k_EMsgGCToClientTeamsInfo = 8136,
    k_EMsgClientToGCMyTeamInfoRequest = 8137,
    k_EMsgClientToGCPublishUserStat = 8140,
    k_EMsgGCToGCSignoutSpendWager = 8141,
    k_EMsgGCSubmitLobbyMVPVote = 8144,
    k_EMsgGCSubmitLobbyMVPVoteResponse = 8145,
    k_EMsgSignOutCommunityGoalProgress = 8150,
    k_EMsgGCToClientLobbyMVPNotifyRecipient = 8151,
    k_EMsgGCToClientLobbyMVPAwarded = 8152,
    k_EMsgGCToClientQuestProgressUpdated = 8153,
    k_EMsgGCToClientWageringUpdate = 8154,
    k_EMsgGCToClientArcanaVotesUpdate = 8155,
    k_EMsgClientToGCAddTI6TreeProgress = 8156,
    k_EMsgClientToGCSetSpectatorLobbyDetails = 8157,
    k_EMsgClientToGCSetSpectatorLobbyDetailsResponse = 8158,
    k_EMsgClientToGCCreateSpectatorLobby = 8159,
    k_EMsgClientToGCCreateSpectatorLobbyResponse = 8160,
    k_EMsgClientToGCSpectatorLobbyList = 8161,
    k_EMsgClientToGCSpectatorLobbyListResponse = 8162,
    k_EMsgSpectatorLobbyGameDetails = 8163,
    k_EMsgServerToGCCompendiumInGamePredictionResults = 8166,
    k_EMsgServerToGCCloseCompendiumInGamePredictionVoting = 8167,
    k_EMsgClientToGCOpenPlayerCardPack = 8168,
    k_EMsgClientToGCOpenPlayerCardPackResponse = 8169,
    k_EMsgClientToGCSelectCompendiumInGamePrediction = 8170,
    k_EMsgClientToGCSelectCompendiumInGamePredictionResponse = 8171,
    k_EMsgClientToGCWeekendTourneyGetPlayerStats = 8172,
    k_EMsgClientToGCWeekendTourneyGetPlayerStatsResponse = 8173,
    k_EMsgClientToGCRecyclePlayerCard = 8174,
    k_EMsgClientToGCRecyclePlayerCardResponse = 8175,
    k_EMsgClientToGCCreatePlayerCardPack = 8176,
    k_EMsgClientToGCCreatePlayerCardPackResponse = 8177,
    k_EMsgClientToGCGetPlayerCardRosterRequest = 8178,
    k_EMsgClientToGCGetPlayerCardRosterResponse = 8179,
    k_EMsgClientToGCSetPlayerCardRosterRequest = 8180,
    k_EMsgClientToGCSetPlayerCardRosterResponse = 8181,
    k_EMsgServerToGCCloseCompendiumInGamePredictionVotingResponse = 8183,
    k_EMsgServerToGCCompendiumInGamePredictionResultsResponse = 8185,
    k_EMsgLobbyBattleCupVictory = 8186,
    k_EMsgGCGetPlayerCardItemInfo = 8187,
    k_EMsgGCGetPlayerCardItemInfoResponse = 8188,
    k_EMsgClientToGCRequestSteamDatagramTicket = 8189,
    k_EMsgClientToGCRequestSteamDatagramTicketResponse = 8190,
    k_EMsgGCToClientBattlePassRollupRequest = 8191,
    k_EMsgGCToClientBattlePassRollupResponse = 8192,
    k_EMsgClientToGCTransferSeasonalMMRRequest = 8193,
    k_EMsgClientToGCTransferSeasonalMMRResponse = 8194,
    k_EMsgGCToGCPublicChatCommunicationBan = 8195,
    k_EMsgGCToGCUpdateAccountPublicChatBan = 8196,
    k_EMsgGCChatReportPublicSpam = 8197,
    k_EMsgClientToGCSetPartyBuilderOptions = 8198,
    k_EMsgClientToGCSetPartyBuilderOptionsResponse = 8199,
    k_EMsgGCToClientPlaytestStatus = 8200,
    k_EMsgClientToGCJoinPlaytest = 8201,
    k_EMsgClientToGCJoinPlaytestResponse = 8202,
    k_EMsgLobbyPlaytestDetails = 8203,
    k_EMsgDOTASetFavoriteTeam = 8204,
    k_EMsgGCToClientBattlePassRollupListRequest = 8205,
    k_EMsgGCToClientBattlePassRollupListResponse = 8206,
    k_EMsgGCIsProQuery = 8207,
    k_EMsgGCIsProResponse = 8208,
    k_EMsgDOTAClaimEventAction = 8209,
    k_EMsgDOTAClaimEventActionResponse = 8210,
    k_EMsgDOTAGetPeriodicResource = 8211,
    k_EMsgDOTAGetPeriodicResourceResponse = 8212,
    k_EMsgDOTAPeriodicResourceUpdated = 8213,
    k_EMsgServerToGCSpendWager = 8214,
    k_EMsgGCToGCSignoutSpendWagerToken = 8215,
    k_EMsgSubmitTriviaQuestionAnswer = 8216,
    k_EMsgSubmitTriviaQuestionAnswerResponse = 8217,
    k_EMsgClientToGCGiveTip = 8218,
    k_EMsgClientToGCGiveTipResponse = 8219,
    k_EMsgStartTriviaSession = 8220,
    k_EMsgStartTriviaSessionResponse = 8221,
    k_EMsgAnchorPhoneNumberRequest = 8222,
    k_EMsgAnchorPhoneNumberResponse = 8223,
    k_EMsgUnanchorPhoneNumberRequest = 8224,
    k_EMsgUnanchorPhoneNumberResponse = 8225,
    k_EMsgGCToClientTipNotification = 8226,
    k_EMsgClientToGCRequestSlarkGameResult = 8227,
    k_EMsgClientToGCRequestSlarkGameResultResponse = 8228,
    k_EMsgGCToGCSignoutSpendRankWager = 8229,
    k_EMsgGCToGCGetFavoriteTeam = 8230,
    k_EMsgGCToGCGetFavoriteTeamResponse = 8231,
    k_EMsgSignOutEventGameData = 8232,
    k_EMsgGCToClientAllStarVotesRequest = 8233,
    k_EMsgGCToClientAllStarVotesReply = 8234,
    k_EMsgGCToClientAllStarVotesSubmit = 8236,
    k_EMsgGCToClientAllStarVotesSubmitReply = 8237,
    k_EMsgClientToGCQuickStatsRequest = 8238,
    k_EMsgClientToGCQuickStatsResponse = 8239,
    k_EMsgGCToGCSubtractEventPointsFromUser = 8240,
    k_EMsgSelectionPriorityChoiceRequest = 8241,
    k_EMsgSelectionPriorityChoiceResponse = 8242,
    k_EMsgGCToGCCompendiumInGamePredictionResults = 8243,
    k_EMsgGameAutographReward = 8244,
    k_EMsgGameAutographRewardResponse = 8245,
    k_EMsgDestroyLobbyRequest = 8246,
    k_EMsgDestroyLobbyResponse = 8247,
    k_EMsgPurchaseItemWithEventPoints = 8248,
    k_EMsgPurchaseItemWithEventPointsResponse = 8249,
    k_EMsgServerToGCMatchPlayerItemPurchaseHistory = 8250,
    k_EMsgGCToGCGrantPlusHeroMatchResults = 8251,
    k_EMsgGCGetHeroTimedStats = 8252,
    k_EMsgGCGetHeroTimedStatsResponse = 8253,
    k_EMsgLobbyPlayerPlusSubscriptionData = 8254,
    k_EMsgServerToGCMatchStateHistory = 8255,
    k_EMsgPurchaseHeroRelic = 8256,
    k_EMsgPurchaseHeroRelicResponse = 8257,
    k_EMsgPurchaseHeroRandomRelic = 8258,
    k_EMsgPurchaseHeroRandomRelicResponse = 8259,
    k_EMsgClientToGCClaimEventActionUsingItem = 8260,
    k_EMsgClientToGCClaimEventActionUsingItemResponse = 8261,
    k_EMsgPartyReadyCheckRequest = 8262,
    k_EMsgPartyReadyCheckResponse = 8263,
    k_EMsgPartyReadyCheckAcknowledge = 8264,
    k_EMsgGetRecentPlayTimeFriendsRequest = 8265,
    k_EMsgGetRecentPlayTimeFriendsResponse = 8266,
    k_EMsgGCToClientCommendNotification = 8267,
    k_EMsgProfileRequest = 8268,
    k_EMsgProfileResponse = 8269,
    k_EMsgProfileUpdate = 8270,
    k_EMsgProfileUpdateResponse = 8271,
    k_EMsgSuccessfulHero = 8273,
    k_EMsgHeroGlobalDataRequest = 8274,
    k_EMsgHeroGlobalDataResponse = 8275,
    k_EMsgClientToGCRequestPlusWeeklyChallengeResult = 8276,
    k_EMsgClientToGCRequestPlusWeeklyChallengeResultResponse = 8277,
    k_EMsgGCToGCGrantPlusPrepaidTime = 8278,
    k_EMsgPrivateMetadataKeyRequest = 8279,
    k_EMsgPrivateMetadataKeyResponse = 8280,
    k_EMsgGCToGCReconcilePlusStatus = 8281,
    k_EMsgGCToGCCheckPlusStatus = 8282,
    k_EMsgGCToGCCheckPlusStatusResponse = 8283,
    k_EMsgGCToGCReconcilePlusAutoGrantItems = 8284,
    k_EMsgGCToGCReconcilePlusStatusUnreliable = 8285,
    k_EMsgActivatePlusFreeTrialRequest = 8286,
    k_EMsgActivatePlusFreeTrialResponse = 8287,
    k_EMsgGCToClientCavernCrawlMapPathCompleted = 8288,
    k_EMsgClientToGCCavernCrawlClaimRoom = 8289,
    k_EMsgClientToGCCavernCrawlClaimRoomResponse = 8290,
    k_EMsgClientToGCCavernCrawlUseItemOnRoom = 8291,
    k_EMsgClientToGCCavernCrawlUseItemOnRoomResponse = 8292,
    k_EMsgClientToGCCavernCrawlUseItemOnPath = 8293,
    k_EMsgClientToGCCavernCrawlUseItemOnPathResponse = 8294,
    k_EMsgClientToGCCavernCrawlRequestMapState = 8295,
    k_EMsgClientToGCCavernCrawlRequestMapStateResponse = 8296,
    k_EMsgSignOutTips = 8297,
    k_EMsgClientToGCRequestEventPointLogV2 = 8298,
    k_EMsgClientToGCRequestEventPointLogResponseV2 = 8299,
    k_EMsgClientToGCRequestEventTipsSummary = 8300,
    k_EMsgClientToGCRequestEventTipsSummaryResponse = 8301,
    k_EMsgHeroGlobalDataAllHeroes = 8302,
    k_EMsgClientToGCRequestSocialFeed = 8303,
    k_EMsgClientToGCRequestSocialFeedResponse = 8304,
    k_EMsgClientToGCRequestSocialFeedComments = 8305,
    k_EMsgClientToGCRequestSocialFeedCommentsResponse = 8306,
    k_EMsgClientToGCCavernCrawlGetClaimedRoomCount = 8308,
    k_EMsgClientToGCCavernCrawlGetClaimedRoomCountResponse = 8309,
    k_EMsgGCToGCReconcilePlusAutoGrantItemsUnreliable = 8310,
    k_EMsgServerToGCAddBroadcastTimelineEvent = 8311,
    k_EMsgGCToServerUpdateSteamBroadcasting = 8312,
    k_EMsgClientToGCRecordContestVote = 8313,
    k_EMsgGCToClientRecordContestVoteResponse = 8314,
    k_EMsgGCToGCGrantAutograph = 8315,
    k_EMsgGCToGCGrantAutographResponse = 8316,
    k_EMsgSignOutConsumableUsage = 8317,
    k_EMsgLobbyEventGameDetails = 8318,
    k_EMsgDevGrantEventPoints = 8319,
    k_EMsgDevGrantEventPointsResponse = 8320,
    k_EMsgDevGrantEventAction = 8321,
    k_EMsgDevGrantEventActionResponse = 8322,
    k_EMsgDevResetEventState = 8323,
    k_EMsgDevResetEventStateResponse = 8324,
    k_EMsgGCToGCReconcileEventOwnership = 8325,
    k_EMsgConsumeEventSupportGrantItem = 8326,
    k_EMsgConsumeEventSupportGrantItemResponse = 8327,
    k_EMsgGCToClientClaimEventActionUsingItemCompleted = 8328,
    k_EMsgGCToClientCavernCrawlMapUpdated = 8329,
    k_EMsgServerToGCRequestPlayerRecentAccomplishments = 8330,
    k_EMsgServerToGCRequestPlayerRecentAccomplishmentsResponse = 8331,
    k_EMsgClientToGCRequestPlayerRecentAccomplishments = 8332,
    k_EMsgClientToGCRequestPlayerRecentAccomplishmentsResponse = 8333,
    k_EMsgClientToGCRequestPlayerHeroRecentAccomplishments = 8334,
    k_EMsgClientToGCRequestPlayerHeroRecentAccomplishmentsResponse = 8335,
    k_EMsgSignOutEventActionGrants = 8336,
    k_EMsgClientToGCRequestPlayerCoachMatches = 8337,
    k_EMsgClientToGCRequestPlayerCoachMatchesResponse = 8338,
    k_EMsgClientToGCGetTicketCodesRequest = 8339,
    k_EMsgClientToGCGetTicketCodesResponse = 8340,
    k_EMsgClientToGCSubmitCoachTeammateRating = 8341,
    k_EMsgClientToGCSubmitCoachTeammateRatingResponse = 8342,
    k_EMsgGCToClientCoachTeammateRatingsChanged = 8343,
    k_EMsgClientToGCVoteForLeagueGameMVP = 8344,
    k_EMsgClientToGCRequestPlayerCoachMatch = 8345,
    k_EMsgClientToGCRequestPlayerCoachMatchResponse = 8346,
    k_EMsgClientToGCRequestContestVotes = 8347,
    k_EMsgClientToGCRequestContestVotesResponse = 8348,
    k_EMsgClientToGCMVPVoteTimeout = 8349,
    k_EMsgClientToGCMVPVoteTimeoutResponse = 8350,
    k_EMsgClientToGCGetUnderlordsCDKeyRequest = 8351,
    k_EMsgClientToGCGetUnderlordsCDKeyResponse = 8352,
    k_EMsgDetailedGameStats = 8353,
    k_EMsgClientToGCSetFavoriteAllStarPlayer = 8354,
    k_EMsgClientToGCSetFavoriteAllStarPlayerResponse = 8355,
    k_EMsgAllStarStats = 8356,
    k_EMsgClientToGCGetFavoriteAllStarPlayerRequest = 8357,
    k_EMsgClientToGCGetFavoriteAllStarPlayerResponse = 8358,
    k_EMsgClientToGCVerifyIntegrity = 8359,
    k_EMsgMatchMatchmakingStats = 8360,
    k_EMsgClientToGCSubmitPlayerMatchSurvey = 8361,
    k_EMsgClientToGCSubmitPlayerMatchSurveyResponse = 8362,
    k_EMsgSQLGCToGCGrantAllHeroProgressAccount = 8363,
    k_EMsgSQLGCToGCGrantAllHeroProgressVictory = 8364,
    k_eMsgGCToGCGetAllHeroCurrent = 8635,
    k_eMsgGCToGCGetAllHeroCurrentResponse = 8636,
    k_EMsgGCSubmitPlayerAvoidRequest = 8637,
    k_EMsgGCSubmitPlayerAvoidRequestResponse = 8638,
    k_EMsgGCToClientNotificationsUpdated = 8639,
    k_EMsgGCtoGCAssociatedExploiterAccountInfo = 8640,
    k_EMsgGCtoGCAssociatedExploiterAccountInfoResponse = 8641,
    k_EMsgGCtoGCRequestRecalibrationCheck = 8642,
};

inline std::string EDOTAGCMsg2String( EDOTAGCMsg msg )
{
    switch( msg ){
        CASE_STD_STRING(k_EMsgGCDOTABase);
        CASE_STD_STRING(k_EMsgGCGeneralResponse);
        CASE_STD_STRING(k_EMsgGCGameMatchSignOut);
        CASE_STD_STRING(k_EMsgGCGameMatchSignOutResponse);
        CASE_STD_STRING(k_EMsgGCJoinChatChannel);
        CASE_STD_STRING(k_EMsgGCJoinChatChannelResponse);
        CASE_STD_STRING(k_EMsgGCOtherJoinedChannel);
        CASE_STD_STRING(k_EMsgGCOtherLeftChannel);
        CASE_STD_STRING(k_EMsgGCMatchHistoryList);
        CASE_STD_STRING(k_EMsgServerToGCRequestStatus);
        CASE_STD_STRING(k_EMsgGCGetRecentMatches);
        CASE_STD_STRING(k_EMsgGCRecentMatchesResponse);
        CASE_STD_STRING(k_EMsgGCStartFindingMatch);
        CASE_STD_STRING(k_EMsgGCConnectedPlayers);
        CASE_STD_STRING(k_EMsgGCAbandonCurrentGame);
        CASE_STD_STRING(k_EMsgGCStopFindingMatch);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyCreate);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyLeave);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyLaunch);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyList);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyListResponse);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyJoin);
        CASE_STD_STRING(k_EMsgGCPracticeLobbySetDetails);
        CASE_STD_STRING(k_EMsgGCPracticeLobbySetTeamSlot);
        CASE_STD_STRING(k_EMsgGCInitialQuestionnaireResponse);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyResponse);
        CASE_STD_STRING(k_EMsgGCBroadcastNotification);
        CASE_STD_STRING(k_EMsgGCLiveScoreboardUpdate);
        CASE_STD_STRING(k_EMsgGCRequestChatChannelList);
        CASE_STD_STRING(k_EMsgGCRequestChatChannelListResponse);
        CASE_STD_STRING(k_EMsgGCRequestMatches);
        CASE_STD_STRING(k_EMsgGCRequestMatchesResponse);
        CASE_STD_STRING(k_EMsgGCRequestPlayerResources);
        CASE_STD_STRING(k_EMsgGCRequestPlayerResourcesResponse);
        CASE_STD_STRING(k_EMsgGCReadyUp);
        CASE_STD_STRING(k_EMsgGCKickedFromMatchmakingQueue);
        CASE_STD_STRING(k_EMsgGCLeaverDetected);
        CASE_STD_STRING(k_EMsgGCSpectateFriendGame);
        CASE_STD_STRING(k_EMsgGCSpectateFriendGameResponse);
        CASE_STD_STRING(k_EMsgGCPlayerReports);
        CASE_STD_STRING(k_EMsgGCReportsRemainingRequest);
        CASE_STD_STRING(k_EMsgGCReportsRemainingResponse);
        CASE_STD_STRING(k_EMsgGCSubmitPlayerReport);
        CASE_STD_STRING(k_EMsgGCSubmitPlayerReportResponse);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyKick);
        CASE_STD_STRING(k_EMsgGCReportCountsRequest);
        CASE_STD_STRING(k_EMsgGCReportCountsResponse);
        CASE_STD_STRING(k_EMsgGCRequestSaveGames);
        CASE_STD_STRING(k_EMsgGCRequestSaveGamesServer);
        CASE_STD_STRING(k_EMsgGCRequestSaveGamesResponse);
        CASE_STD_STRING(k_EMsgGCLeaverDetectedResponse);
        CASE_STD_STRING(k_EMsgGCPlayerFailedToConnect);
        CASE_STD_STRING(k_EMsgGCGCToRelayConnect);
        CASE_STD_STRING(k_EMsgGCGCToRelayConnectresponse);
        CASE_STD_STRING(k_EMsgGCWatchGame);
        CASE_STD_STRING(k_EMsgGCWatchGameResponse);
        CASE_STD_STRING(k_EMsgGCBanStatusRequest);
        CASE_STD_STRING(k_EMsgGCBanStatusResponse);
        CASE_STD_STRING(k_EMsgGCMatchDetailsRequest);
        CASE_STD_STRING(k_EMsgGCMatchDetailsResponse);
        CASE_STD_STRING(k_EMsgGCCancelWatchGame);
        CASE_STD_STRING(k_EMsgGCPopup);
        CASE_STD_STRING(k_EMsgGCDOTAClearNotifySuccessfulReport);
        CASE_STD_STRING(k_EMsgGCFriendPracticeLobbyListRequest);
        CASE_STD_STRING(k_EMsgGCFriendPracticeLobbyListResponse);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyJoinResponse);
        CASE_STD_STRING(k_EMsgClientEconNotification_Job);
        CASE_STD_STRING(k_EMsgGCCreateTeam);
        CASE_STD_STRING(k_EMsgGCCreateTeamResponse);
        CASE_STD_STRING(k_EMsgGCTeamData);
        CASE_STD_STRING(k_EMsgGCTeamInvite_InviterToGC);
        CASE_STD_STRING(k_EMsgGCTeamInvite_GCImmediateResponseToInviter);
        CASE_STD_STRING(k_EMsgGCTeamInvite_GCRequestToInvitee);
        CASE_STD_STRING(k_EMsgGCTeamInvite_InviteeResponseToGC);
        CASE_STD_STRING(k_EMsgGCTeamInvite_GCResponseToInviter);
        CASE_STD_STRING(k_EMsgGCTeamInvite_GCResponseToInvitee);
        CASE_STD_STRING(k_EMsgGCKickTeamMember);
        CASE_STD_STRING(k_EMsgGCKickTeamMemberResponse);
        CASE_STD_STRING(k_EMsgGCLeaveTeam);
        CASE_STD_STRING(k_EMsgGCLeaveTeamResponse);
        CASE_STD_STRING(k_EMsgGCSuggestTeamMatchmaking);
        CASE_STD_STRING(k_EMsgGCPlayerHeroesFavoritesAdd);
        CASE_STD_STRING(k_EMsgGCPlayerHeroesFavoritesRemove);
        CASE_STD_STRING(k_EMsgGCApplyTeamToPracticeLobby);
        CASE_STD_STRING(k_EMsgGCTransferTeamAdmin);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyJoinBroadcastChannel);
        CASE_STD_STRING(k_EMsgGC_TournamentItemEvent);
        CASE_STD_STRING(k_EMsgGC_TournamentItemEventResponse);
        CASE_STD_STRING(k_EMsgCastMatchVote);
        CASE_STD_STRING(k_EMsgCastMatchVoteResponse);
        CASE_STD_STRING(k_EMsgRetrieveMatchVote);
        CASE_STD_STRING(k_EMsgRetrieveMatchVoteResponse);
        CASE_STD_STRING(k_EMsgTeamFanfare);
        CASE_STD_STRING(k_EMsgResponseTeamFanfare);
        CASE_STD_STRING(k_EMsgGC_GameServerUploadSaveGame);
        CASE_STD_STRING(k_EMsgGC_GameServerSaveGameResult);
        CASE_STD_STRING(k_EMsgGC_GameServerGetLoadGame);
        CASE_STD_STRING(k_EMsgGC_GameServerGetLoadGameResult);
        CASE_STD_STRING(k_EMsgGCEditTeamDetails);
        CASE_STD_STRING(k_EMsgGCEditTeamDetailsResponse);
        CASE_STD_STRING(k_EMsgGCProTeamListRequest);
        CASE_STD_STRING(k_EMsgGCProTeamListResponse);
        CASE_STD_STRING(k_EMsgGCReadyUpStatus);
        CASE_STD_STRING(k_EMsgGCHallOfFame);
        CASE_STD_STRING(k_EMsgGCHallOfFameRequest);
        CASE_STD_STRING(k_EMsgGCHallOfFameResponse);
        CASE_STD_STRING(k_EMsgGCGenerateDiretidePrizeList);
        CASE_STD_STRING(k_EMsgGCRewardDiretidePrizes);
        CASE_STD_STRING(k_EMsgGCDiretidePrizesRewardedResponse);
        CASE_STD_STRING(k_EMsgGCHalloweenHighScoreRequest);
        CASE_STD_STRING(k_EMsgGCHalloweenHighScoreResponse);
        CASE_STD_STRING(k_EMsgGCGenerateDiretidePrizeListResponse);
        CASE_STD_STRING(k_EMsgGCStorePromoPagesRequest);
        CASE_STD_STRING(k_EMsgGCStorePromoPagesResponse);
        CASE_STD_STRING(k_EMsgGCToGCMatchCompleted);
        CASE_STD_STRING(k_EMsgGCBalancedShuffleLobby);
        CASE_STD_STRING(k_EMsgGCToGCCheckLeaguePermission);
        CASE_STD_STRING(k_EMsgGCToGCCheckLeaguePermissionResponse);
        CASE_STD_STRING(k_EMsgGCMatchmakingStatsRequest);
        CASE_STD_STRING(k_EMsgGCMatchmakingStatsResponse);
        CASE_STD_STRING(k_EMsgGCBotGameCreate);
        CASE_STD_STRING(k_EMsgGCSetMatchHistoryAccess);
        CASE_STD_STRING(k_EMsgGCSetMatchHistoryAccessResponse);
        CASE_STD_STRING(k_EMsgUpgradeLeagueItem);
        CASE_STD_STRING(k_EMsgUpgradeLeagueItemResponse);
        CASE_STD_STRING(k_EMsgGCTeamMemberProfileRequest);
        CASE_STD_STRING(k_EMsgGCWatchDownloadedReplay);
        CASE_STD_STRING(k_EMsgGCSetMapLocationState);
        CASE_STD_STRING(k_EMsgGCSetMapLocationStateResponse);
        CASE_STD_STRING(k_EMsgGCResetMapLocations);
        CASE_STD_STRING(k_EMsgGCResetMapLocationsResponse);
        CASE_STD_STRING(k_EMsgRefreshPartnerAccountLink);
        CASE_STD_STRING(k_EMsgClientsRejoinChatChannels);
        CASE_STD_STRING(k_EMsgGCToGCGetUserChatInfo);
        CASE_STD_STRING(k_EMsgGCToGCGetUserChatInfoResponse);
        CASE_STD_STRING(k_EMsgGCToGCLeaveAllChatChannels);
        CASE_STD_STRING(k_EMsgGCToGCUpdateAccountChatBan);
        CASE_STD_STRING(k_EMsgGCGuildCreateRequest);
        CASE_STD_STRING(k_EMsgGCGuildCreateResponse);
        CASE_STD_STRING(k_EMsgGCGuildSetAccountRoleRequest);
        CASE_STD_STRING(k_EMsgGCGuildSetAccountRoleResponse);
        CASE_STD_STRING(k_EMsgGCRequestGuildData);
        CASE_STD_STRING(k_EMsgGCGuildData);
        CASE_STD_STRING(k_EMsgGCGuildInviteAccountRequest);
        CASE_STD_STRING(k_EMsgGCGuildInviteAccountResponse);
        CASE_STD_STRING(k_EMsgGCGuildCancelInviteRequest);
        CASE_STD_STRING(k_EMsgGCGuildCancelInviteResponse);
        CASE_STD_STRING(k_EMsgGCGuildUpdateDetailsRequest);
        CASE_STD_STRING(k_EMsgGCGuildUpdateDetailsResponse);
        CASE_STD_STRING(k_EMsgGCToGCCanInviteUserToTeam);
        CASE_STD_STRING(k_EMsgGCToGCCanInviteUserToTeamResponse);
        CASE_STD_STRING(k_EMsgGCToGCGetUserRank);
        CASE_STD_STRING(k_EMsgGCToGCGetUserRankResponse);
        CASE_STD_STRING(k_EMsgGCToGCUpdateTeamStats);
        CASE_STD_STRING(k_EMsgGCToGCValidateTeam);
        CASE_STD_STRING(k_EMsgGCToGCValidateTeamResponse);
        CASE_STD_STRING(k_EMsgGCPassportDataRequest);
        CASE_STD_STRING(k_EMsgGCPassportDataResponse);
        CASE_STD_STRING(k_EMsgGCNotInGuildData);
        CASE_STD_STRING(k_EMsgGCGuildInviteData);
        CASE_STD_STRING(k_EMsgGCToGCGetLeagueAdmin);
        CASE_STD_STRING(k_EMsgGCToGCGetLeagueAdminResponse);
        CASE_STD_STRING(k_EMsgGCRequestLeaguePrizePool);
        CASE_STD_STRING(k_EMsgGCRequestLeaguePrizePoolResponse);
        CASE_STD_STRING(k_EMsgGCToGCUpdateOpenGuildPartyRequest);
        CASE_STD_STRING(k_EMsgGCToGCUpdateOpenGuildPartyResponse);
        CASE_STD_STRING(k_EMsgGCToGCDestroyOpenGuildPartyRequest);
        CASE_STD_STRING(k_EMsgGCToGCDestroyOpenGuildPartyResponse);
        CASE_STD_STRING(k_EMsgGCGuildUpdateMessage);
        CASE_STD_STRING(k_EMsgGCPartySetOpenGuildRequest);
        CASE_STD_STRING(k_EMsgGCPartySetOpenGuildResponse);
        CASE_STD_STRING(k_EMsgGCGuildOpenPartyRefresh);
        CASE_STD_STRING(k_EMsgGCJoinOpenGuildPartyRequest);
        CASE_STD_STRING(k_EMsgGCJoinOpenGuildPartyResponse);
        CASE_STD_STRING(k_EMsgGCLeaveChatChannel);
        CASE_STD_STRING(k_EMsgGCChatMessage);
        CASE_STD_STRING(k_EMsgGCGetHeroStandings);
        CASE_STD_STRING(k_EMsgGCGetHeroStandingsResponse);
        CASE_STD_STRING(k_EMsgGCGuildEditLogoRequest);
        CASE_STD_STRING(k_EMsgGCGuildEditLogoResponse);
        CASE_STD_STRING(k_EMsgGCGuildmatePracticeLobbyListRequest);
        CASE_STD_STRING(k_EMsgGCGuildmatePracticeLobbyListResponse);
        CASE_STD_STRING(k_EMsgGCItemEditorReservationsRequest);
        CASE_STD_STRING(k_EMsgGCItemEditorReservationsResponse);
        CASE_STD_STRING(k_EMsgGCItemEditorReserveItemDef);
        CASE_STD_STRING(k_EMsgGCItemEditorReserveItemDefResponse);
        CASE_STD_STRING(k_EMsgGCItemEditorReleaseReservation);
        CASE_STD_STRING(k_EMsgGCItemEditorReleaseReservationResponse);
        CASE_STD_STRING(k_EMsgGCRewardTutorialPrizes);
        CASE_STD_STRING(k_EMsgGCLastHitChallengeHighScorePost);
        CASE_STD_STRING(k_EMsgGCLastHitChallengeHighScoreRequest);
        CASE_STD_STRING(k_EMsgGCLastHitChallengeHighScoreResponse);
        CASE_STD_STRING(k_EMsgGCCreateFantasyLeagueRequest);
        CASE_STD_STRING(k_EMsgGCCreateFantasyLeagueResponse);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueInfoRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueInfoResponse);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueInfo);
        CASE_STD_STRING(k_EMsgGCCreateFantasyTeamRequest);
        CASE_STD_STRING(k_EMsgGCCreateFantasyTeamResponse);
        CASE_STD_STRING(k_EMsgGCEditFantasyTeamRequest);
        CASE_STD_STRING(k_EMsgGCEditFantasyTeamResponse);
        CASE_STD_STRING(k_EMsgGCFantasyTeamInfoRequestByFantasyLeagueID);
        CASE_STD_STRING(k_EMsgGCFantasyTeamInfoRequestByOwnerAccountID);
        CASE_STD_STRING(k_EMsgGCFantasyTeamInfoResponse);
        CASE_STD_STRING(k_EMsgGCFantasyTeamInfo);
        CASE_STD_STRING(k_EMsgGCFantasyLivePlayerStats);
        CASE_STD_STRING(k_EMsgGCFantasyFinalPlayerStats);
        CASE_STD_STRING(k_EMsgGCFantasyMatch);
        CASE_STD_STRING(k_EMsgGCFantasyTeamScoreRequest);
        CASE_STD_STRING(k_EMsgGCFantasyTeamScoreResponse);
        CASE_STD_STRING(k_EMsgGCFantasyTeamStandingsRequest);
        CASE_STD_STRING(k_EMsgGCFantasyTeamStandingsResponse);
        CASE_STD_STRING(k_EMsgGCFantasyPlayerScoreRequest);
        CASE_STD_STRING(k_EMsgGCFantasyPlayerScoreResponse);
        CASE_STD_STRING(k_EMsgGCFantasyPlayerStandingsRequest);
        CASE_STD_STRING(k_EMsgGCFantasyPlayerStandingsResponse);
        CASE_STD_STRING(k_EMsgGCFlipLobbyTeams);
        CASE_STD_STRING(k_EMsgGCCustomGameCreate);
        CASE_STD_STRING(k_EMsgGCToGCProcessPlayerReportForTarget);
        CASE_STD_STRING(k_EMsgGCToGCProcessReportSuccess);
        CASE_STD_STRING(k_EMsgGCNotifyAccountFlagsChange);
        CASE_STD_STRING(k_EMsgGCSetProfilePrivacy);
        CASE_STD_STRING(k_EMsgGCSetProfilePrivacyResponse);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueCreateInfoRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueCreateInfoResponse);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueInviteInfoRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueInviteInfoResponse);
        CASE_STD_STRING(k_EMsgGCClientIgnoredUser);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueCreateRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueCreateResponse);
        CASE_STD_STRING(k_EMsgGCFantasyTeamCreateRequest);
        CASE_STD_STRING(k_EMsgGCFantasyTeamCreateResponse);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueFriendJoinListRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueFriendJoinListResponse);
        CASE_STD_STRING(k_EMsgGCClientSuspended);
        CASE_STD_STRING(k_EMsgGCPartyMemberSetCoach);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueEditInvitesRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueEditInvitesResponse);
        CASE_STD_STRING(k_EMsgGCPracticeLobbySetCoach);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueEditInfoRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueEditInfoResponse);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueDraftStatusRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueDraftStatus);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueDraftPlayerRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueDraftPlayerResponse);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueMatchupsRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeagueMatchupsResponse);
        CASE_STD_STRING(k_EMsgGCFantasyTeamRosterSwapRequest);
        CASE_STD_STRING(k_EMsgGCFantasyTeamRosterSwapResponse);
        CASE_STD_STRING(k_EMsgGCFantasyTeamRosterRequest);
        CASE_STD_STRING(k_EMsgGCFantasyTeamRosterResponse);
        CASE_STD_STRING(k_EMsgGCFantasyTeamRosterAddDropRequest);
        CASE_STD_STRING(k_EMsgGCFantasyTeamRosterAddDropResponse);
        CASE_STD_STRING(k_EMsgPresentedClientTerminateDlg);
        CASE_STD_STRING(k_EMsgGCFantasyPlayerHisoricalStatsRequest);
        CASE_STD_STRING(k_EMsgGCFantasyPlayerHisoricalStatsResponse);
        CASE_STD_STRING(k_EMsgGCPCBangTimedRewardMessage);
        CASE_STD_STRING(k_EMsgGCLobbyUpdateBroadcastChannelInfo);
        CASE_STD_STRING(k_EMsgGCFantasyTeamTradesRequest);
        CASE_STD_STRING(k_EMsgGCFantasyTeamTradesResponse);
        CASE_STD_STRING(k_EMsgGCFantasyTeamTradeCancelRequest);
        CASE_STD_STRING(k_EMsgGCFantasyTeamTradeCancelResponse);
        CASE_STD_STRING(k_EMsgGCToGCGrantTournamentItem);
        CASE_STD_STRING(k_EMsgGCProcessFantasyScheduledEvent);
        CASE_STD_STRING(k_EMsgGCToGCUpgradeTwitchViewerItems);
        CASE_STD_STRING(k_EMsgGCToGCGetLiveMatchAffiliates);
        CASE_STD_STRING(k_EMsgGCToGCGetLiveMatchAffiliatesResponse);
        CASE_STD_STRING(k_EMsgGCToGCUpdatePlayerPennantCounts);
        CASE_STD_STRING(k_EMsgGCToGCGetPlayerPennantCounts);
        CASE_STD_STRING(k_EMsgGCToGCGetPlayerPennantCountsResponse);
        CASE_STD_STRING(k_EMsgGCGameMatchSignOutPermissionRequest);
        CASE_STD_STRING(k_EMsgGCGameMatchSignOutPermissionResponse);
        CASE_STD_STRING(k_EMsgDOTAChatChannelMemberUpdate);
        CASE_STD_STRING(k_EMsgDOTAAwardEventPoints);
        CASE_STD_STRING(k_EMsgDOTAGetEventPoints);
        CASE_STD_STRING(k_EMsgDOTAGetEventPointsResponse);
        CASE_STD_STRING(k_EMsgDOTASendFriendRecruits);
        CASE_STD_STRING(k_EMsgDOTAFriendRecruitsRequest);
        CASE_STD_STRING(k_EMsgDOTAFriendRecruitsResponse);
        CASE_STD_STRING(k_EMsgDOTAFriendRecruitInviteAcceptDecline);
        CASE_STD_STRING(k_EMsgGCPartyLeaderWatchGamePrompt);
        CASE_STD_STRING(k_EMsgDOTAFrostivusTimeElapsed);
        CASE_STD_STRING(k_EMsgDOTALiveLeagueGameUpdate);
        CASE_STD_STRING(k_EMsgDOTAChatGetUserList);
        CASE_STD_STRING(k_EMsgDOTAChatGetUserListResponse);
        CASE_STD_STRING(k_EMsgGCCompendiumSetSelection);
        CASE_STD_STRING(k_EMsgGCCompendiumDataRequest);
        CASE_STD_STRING(k_EMsgGCCompendiumDataResponse);
        CASE_STD_STRING(k_EMsgDOTAGetPlayerMatchHistory);
        CASE_STD_STRING(k_EMsgDOTAGetPlayerMatchHistoryResponse);
        CASE_STD_STRING(k_EMsgGCToGCMatchmakingAddParty);
        CASE_STD_STRING(k_EMsgGCToGCMatchmakingRemoveParty);
        CASE_STD_STRING(k_EMsgGCToGCMatchmakingRemoveAllParties);
        CASE_STD_STRING(k_EMsgGCToGCMatchmakingMatchFound);
        CASE_STD_STRING(k_EMsgGCToGCUpdateMatchManagementStats);
        CASE_STD_STRING(k_EMsgGCToGCUpdateMatchmakingStats);
        CASE_STD_STRING(k_EMsgGCToServerPingRequest);
        CASE_STD_STRING(k_EMsgGCToServerPingResponse);
        CASE_STD_STRING(k_EMsgGCToServerConsoleCommand);
        CASE_STD_STRING(k_EMsgGCMakeOffering);
        CASE_STD_STRING(k_EMsgGCRequestOfferings);
        CASE_STD_STRING(k_EMsgGCRequestOfferingsResponse);
        CASE_STD_STRING(k_EMsgGCToGCProcessMatchLeaver);
        CASE_STD_STRING(k_EMsgGCNotificationsRequest);
        CASE_STD_STRING(k_EMsgGCNotificationsResponse);
        CASE_STD_STRING(k_EMsgGCToGCModifyNotification);
        CASE_STD_STRING(k_EMsgGCToGCSetNewNotifications);
        CASE_STD_STRING(k_EMsgGCLeagueAdminList);
        CASE_STD_STRING(k_EMsgGCNotificationsMarkReadRequest);
        CASE_STD_STRING(k_EMsgGCFantasyMessageAdd);
        CASE_STD_STRING(k_EMsgGCFantasyMessagesRequest);
        CASE_STD_STRING(k_EMsgGCFantasyMessagesResponse);
        CASE_STD_STRING(k_EMsgGCFantasyScheduledMatchesRequest);
        CASE_STD_STRING(k_EMsgGCFantasyScheduledMatchesResponse);
        CASE_STD_STRING(k_EMsgGCEventGameCreate);
        CASE_STD_STRING(k_EMsgGCPerfectWorldUserLookupRequest);
        CASE_STD_STRING(k_EMsgGCPerfectWorldUserLookupResponse);
        CASE_STD_STRING(k_EMsgGCFantasyRemoveOwner);
        CASE_STD_STRING(k_EMsgGCFantasyRemoveOwnerResponse);
        CASE_STD_STRING(k_EMsgGCRequestBatchPlayerResources);
        CASE_STD_STRING(k_EMsgGCRequestBatchPlayerResourcesResponse);
        CASE_STD_STRING(k_EMsgGCToGCSendUpdateLeagues);
        CASE_STD_STRING(k_EMsgGCCompendiumSetSelectionResponse);
        CASE_STD_STRING(k_EMsgGCPlayerInfoRequest);
        CASE_STD_STRING(k_EMsgGCPlayerInfo);
        CASE_STD_STRING(k_EMsgGCPlayerInfoSubmit);
        CASE_STD_STRING(k_EMsgGCPlayerInfoSubmitResponse);
        CASE_STD_STRING(k_EMsgGCToGCGetAccountLevel);
        CASE_STD_STRING(k_EMsgGCToGCGetAccountLevelResponse);
        CASE_STD_STRING(k_EMsgGCToGCGetAccountPartner);
        CASE_STD_STRING(k_EMsgGCToGCGetAccountPartnerResponse);
        CASE_STD_STRING(k_EMsgDOTAGetWeekendTourneySchedule);
        CASE_STD_STRING(k_EMsgDOTAWeekendTourneySchedule);
        CASE_STD_STRING(k_EMsgGCJoinableCustomGameModesRequest);
        CASE_STD_STRING(k_EMsgGCJoinableCustomGameModesResponse);
        CASE_STD_STRING(k_EMsgGCJoinableCustomLobbiesRequest);
        CASE_STD_STRING(k_EMsgGCJoinableCustomLobbiesResponse);
        CASE_STD_STRING(k_EMsgGCQuickJoinCustomLobby);
        CASE_STD_STRING(k_EMsgGCQuickJoinCustomLobbyResponse);
        CASE_STD_STRING(k_EMsgGCToGCGrantEventPointAction);
        CASE_STD_STRING(k_EMsgServerGrantSurveyPermission);
        CASE_STD_STRING(k_EMsgServerGrantSurveyPermissionResponse);
        CASE_STD_STRING(k_EMsgClientProvideSurveyResult);
        CASE_STD_STRING(k_EMsgGCToGCSetCompendiumSelection);
        CASE_STD_STRING(k_EMsgGCToGCUpdateTI4HeroQuest);
        CASE_STD_STRING(k_EMsgGCCompendiumDataChanged);
        CASE_STD_STRING(k_EMsgDOTAFantasyLeagueFindRequest);
        CASE_STD_STRING(k_EMsgDOTAFantasyLeagueFindResponse);
        CASE_STD_STRING(k_EMsgGCHasItemQuery);
        CASE_STD_STRING(k_EMsgGCHasItemResponse);
        CASE_STD_STRING(k_EMsgGCConsumeFantasyTicket);
        CASE_STD_STRING(k_EMsgGCConsumeFantasyTicketFailure);
        CASE_STD_STRING(k_EMsgGCToGCGrantEventPointActionMsg);
        CASE_STD_STRING(k_EMsgClientToGCTrackDialogResult);
        CASE_STD_STRING(k_EMsgGCFantasyLeaveLeagueRequest);
        CASE_STD_STRING(k_EMsgGCFantasyLeaveLeagueResponse);
        CASE_STD_STRING(k_EMsgGCToGCGetCompendiumSelections);
        CASE_STD_STRING(k_EMsgGCToGCGetCompendiumSelectionsResponse);
        CASE_STD_STRING(k_EMsgServerToGCMatchConnectionStats);
        CASE_STD_STRING(k_EMsgGCToClientTournamentItemDrop);
        CASE_STD_STRING(k_EMsgSQLDelayedGrantLeagueDrop);
        CASE_STD_STRING(k_EMsgServerGCUpdateSpectatorCount);
        CASE_STD_STRING(k_EMsgGCFantasyPlayerScoreDetailsRequest);
        CASE_STD_STRING(k_EMsgGCFantasyPlayerScoreDetailsResponse);
        CASE_STD_STRING(k_EMsgGCToGCEmoticonUnlock);
        CASE_STD_STRING(k_EMsgSignOutDraftInfo);
        CASE_STD_STRING(k_EMsgClientToGCEmoticonDataRequest);
        CASE_STD_STRING(k_EMsgGCToClientEmoticonData);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyToggleBroadcastChannelCameramanStatus);
        CASE_STD_STRING(k_EMsgGCToGCCreateWeekendTourneyRequest);
        CASE_STD_STRING(k_EMsgGCToGCCreateWeekendTourneyResponse);
        CASE_STD_STRING(k_EMsgClientToGCSetAdditionalEquips);
        CASE_STD_STRING(k_EMsgClientToGCGetAdditionalEquips);
        CASE_STD_STRING(k_EMsgClientToGCGetAdditionalEquipsResponse);
        CASE_STD_STRING(k_EMsgServerToGCGetAdditionalEquips);
        CASE_STD_STRING(k_EMsgServerToGCGetAdditionalEquipsResponse);
        CASE_STD_STRING(k_EMsgDOTARedeemItem);
        CASE_STD_STRING(k_EMsgDOTARedeemItemResponse);
        CASE_STD_STRING(k_EMsgSQLGCToGCGrantAllHeroProgress);
        CASE_STD_STRING(k_EMsgClientToGCGetAllHeroProgress);
        CASE_STD_STRING(k_EMsgClientToGCGetAllHeroProgressResponse);
        CASE_STD_STRING(k_EMsgGCToGCGetServerForClient);
        CASE_STD_STRING(k_EMsgGCToGCGetServerForClientResponse);
        CASE_STD_STRING(k_EMsgSQLProcessTournamentGameOutcome);
        CASE_STD_STRING(k_EMsgSQLGrantTrophyToAccount);
        CASE_STD_STRING(k_EMsgClientToGCGetTrophyList);
        CASE_STD_STRING(k_EMsgClientToGCGetTrophyListResponse);
        CASE_STD_STRING(k_EMsgGCToClientTrophyAwarded);
        CASE_STD_STRING(k_EMsgGCGameBotMatchSignOut);
        CASE_STD_STRING(k_EMsgGCGameBotMatchSignOutPermissionRequest);
        CASE_STD_STRING(k_EMsgSignOutBotInfo);
        CASE_STD_STRING(k_EMsgGCToGCUpdateProfileCards);
        CASE_STD_STRING(k_EMsgClientToGCGetProfileCard);
        CASE_STD_STRING(k_EMsgClientToGCGetProfileCardResponse);
        CASE_STD_STRING(k_EMsgServerToGCGetProfileCard);
        CASE_STD_STRING(k_EMsgServerToGCGetProfileCardResponse);
        CASE_STD_STRING(k_EMsgClientToGCSetProfileCardSlots);
        CASE_STD_STRING(k_EMsgGCToClientProfileCardUpdated);
        CASE_STD_STRING(k_EMsgServerToGCVictoryPredictions);
        CASE_STD_STRING(k_EMsgClientToGCMarkNotificationListRead);
        CASE_STD_STRING(k_EMsgServerToGCSuspiciousActivity);
        CASE_STD_STRING(k_EMsgSignOutCommunicationSummary);
        CASE_STD_STRING(k_EMsgServerToGCRequestStatus_Response);
        CASE_STD_STRING(k_EMsgClientToGCCreateHeroStatue);
        CASE_STD_STRING(k_EMsgGCToClientHeroStatueCreateResult);
        CASE_STD_STRING(k_EMsgGCGCToLANServerRelayConnect);
        CASE_STD_STRING(k_EMsgServerToGCGetIngameEventData);
        CASE_STD_STRING(k_EMsgGCToGCUpdateIngameEventDataBroadcast);
        CASE_STD_STRING(k_EMsgGCToServerIngameEventData_OraclePA);
        CASE_STD_STRING(k_EMsgServerToGCReportKillSummaries);
        CASE_STD_STRING(k_EMsgGCToGCReportKillSummaries);
        CASE_STD_STRING(k_EMsgGCToGCUpdateAssassinMinigame);
        CASE_STD_STRING(k_EMsgGCToGCFantasySetMatchLeague);
        CASE_STD_STRING(k_EMsgGCToGCUpdatePlayerPredictions);
        CASE_STD_STRING(k_EMsgGCToServerPredictionResult);
        CASE_STD_STRING(k_EMsgServerToGCSignoutAwardAdditionalDrops);
        CASE_STD_STRING(k_EMsgGCToGCSignoutAwardAdditionalDrops);
        CASE_STD_STRING(k_EMsgGCToClientEventStatusChanged);
        CASE_STD_STRING(k_EMsgGCHasItemDefsQuery);
        CASE_STD_STRING(k_EMsgGCHasItemDefsResponse);
        CASE_STD_STRING(k_EMsgGCToGCReplayMonitorValidateReplay);
        CASE_STD_STRING(k_EMsgLobbyEventPoints);
        CASE_STD_STRING(k_EMsgGCToGCGetCustomGameTickets);
        CASE_STD_STRING(k_EMsgGCToGCGetCustomGameTicketsResponse);
        CASE_STD_STRING(k_EMsgGCToGCCustomGamePlayed);
        CASE_STD_STRING(k_EMsgGCToGCGrantEventPointsToUser);
        CASE_STD_STRING(k_EMsgGCToGCSetEventMMPanicFlushTime);
        CASE_STD_STRING(k_EMsgGameserverCrashReport);
        CASE_STD_STRING(k_EMsgGameserverCrashReportResponse);
        CASE_STD_STRING(k_EMsgGCToClientSteamDatagramTicket);
        CASE_STD_STRING(k_EMsgGCToGCGrantEventOwnership);
        CASE_STD_STRING(k_EMsgGCToGCSendAccountsEventPoints);
        CASE_STD_STRING(k_EMsgClientToGCRerollPlayerChallenge);
        CASE_STD_STRING(k_EMsgServerToGCRerollPlayerChallenge);
        CASE_STD_STRING(k_EMsgGCRerollPlayerChallengeResponse);
        CASE_STD_STRING(k_EMsgSignOutUpdatePlayerChallenge);
        CASE_STD_STRING(k_EMsgClientToGCSetPartyLeader);
        CASE_STD_STRING(k_EMsgClientToGCCancelPartyInvites);
        CASE_STD_STRING(k_EMsgGCToGCMasterReloadAccount);
        CASE_STD_STRING(k_EMsgSQLGrantLeagueMatchToTicketHolders);
        CASE_STD_STRING(k_EMsgClientToGCSetAdditionalEquipsResponse);
        CASE_STD_STRING(k_EMsgGCToGCEmoticonUnlockNoRollback);
        CASE_STD_STRING(k_EMsgGCToGCGetCompendiumFanfare);
        CASE_STD_STRING(k_EMsgGCToGCChatNewUserSession);
        CASE_STD_STRING(k_EMsgClientToGCApplyGemCombiner);
        CASE_STD_STRING(k_EMsgClientToGCDOTACreateStaticRecipe);
        CASE_STD_STRING(k_EMsgClientToGCDOTACreateStaticRecipeResponse);
        CASE_STD_STRING(k_EMsgClientToGCGetAllHeroOrder);
        CASE_STD_STRING(k_EMsgClientToGCGetAllHeroOrderResponse);
        CASE_STD_STRING(k_EMsgSQLGCToGCGrantBadgePoints);
        CASE_STD_STRING(k_EMsgGCToGCGetAccountMatchStatus);
        CASE_STD_STRING(k_EMsgGCToGCGetAccountMatchStatusResponse);
        CASE_STD_STRING(k_EMsgGCToGCCheckOwnsEntireEmoticonRange);
        CASE_STD_STRING(k_EMsgGCToGCCheckOwnsEntireEmoticonRangeResponse);
        CASE_STD_STRING(k_EMsgClientToGCRecycleHeroRelic);
        CASE_STD_STRING(k_EMsgClientToGCRecycleHeroRelicResponse);
        CASE_STD_STRING(k_EMsgGCToGCRevokeEventOwnership);
        CASE_STD_STRING(k_EMsgGCToGCUnlockEventPointSpending);
        CASE_STD_STRING(k_EMsgGCToClientRequestLaneSelection);
        CASE_STD_STRING(k_EMsgGCToClientRequestLaneSelectionResponse);
        CASE_STD_STRING(k_EMsgServerToGCCavernCrawlIsHeroActive);
        CASE_STD_STRING(k_EMsgServerToGCCavernCrawlIsHeroActiveResponse);
        CASE_STD_STRING(k_EMsgClientToGCPlayerCardSpecificPurchaseRequest);
        CASE_STD_STRING(k_EMsgClientToGCPlayerCardSpecificPurchaseResponse);
        CASE_STD_STRING(k_EMsgGCtoServerTensorflowInstance);
        CASE_STD_STRING(k_EMsgSQLSetIsLeagueAdmin);
        CASE_STD_STRING(k_EMsgGCToGCGetLiveLeagueMatches);
        CASE_STD_STRING(k_EMsgGCToGCGetLiveLeagueMatchesResponse);
        CASE_STD_STRING(k_EMsgDOTALeagueInfoListAdminsRequest);
        CASE_STD_STRING(k_EMsgDOTALeagueInfoListAdminsReponse);
        CASE_STD_STRING(k_EMsgGCToGCLeagueMatchStarted);
        CASE_STD_STRING(k_EMsgGCToGCLeagueMatchCompleted);
        CASE_STD_STRING(k_EMsgGCToGCLeagueMatchStartedResponse);
        CASE_STD_STRING(k_EMsgDOTALeagueNodeRequest);
        CASE_STD_STRING(k_EMsgDOTALeagueNodeResponse);
        CASE_STD_STRING(k_EMsgDOTALeagueAvailableLobbyNodesRequest);
        CASE_STD_STRING(k_EMsgDOTALeagueAvailableLobbyNodes);
        CASE_STD_STRING(k_EMsgGCToGCLeagueRequest);
        CASE_STD_STRING(k_EMsgGCToGCLeagueResponse);
        CASE_STD_STRING(k_EMsgGCToGCLeagueNodeGroupRequest);
        CASE_STD_STRING(k_EMsgGCToGCLeagueNodeGroupResponse);
        CASE_STD_STRING(k_EMsgGCToGCLeagueNodeRequest);
        CASE_STD_STRING(k_EMsgGCToGCLeagueNodeResponse);
        CASE_STD_STRING(k_EMsgGCToGCRealtimeStatsTerseRequest);
        CASE_STD_STRING(k_EMsgGCToGCRealtimeStatsTerseResponse);
        CASE_STD_STRING(k_EMsgGCToGCGetTopMatchesRequest);
        CASE_STD_STRING(k_EMsgGCToGCGetTopMatchesResponse);
        CASE_STD_STRING(k_EMsgClientToGCGetFilteredPlayers);
        CASE_STD_STRING(k_EMsgGCToClientGetFilteredPlayersResponse);
        CASE_STD_STRING(k_EMsgClientToGCRemoveFilteredPlayer);
        CASE_STD_STRING(k_EMsgGCToClientRemoveFilteredPlayerResponse);
        CASE_STD_STRING(k_EMsgGCToClientPlayerBeaconState);
        CASE_STD_STRING(k_EMsgGCToClientPartyBeaconUpdate);
        CASE_STD_STRING(k_EMsgGCToClientPartySearchInvite);
        CASE_STD_STRING(k_EMsgClientToGCUpdatePartyBeacon);
        CASE_STD_STRING(k_EMsgClientToGCRequestActiveBeaconParties);
        CASE_STD_STRING(k_EMsgGCToClientRequestActiveBeaconPartiesResponse);
        CASE_STD_STRING(k_EMsgClientToGCManageFavorites);
        CASE_STD_STRING(k_EMsgGCToClientManageFavoritesResponse);
        CASE_STD_STRING(k_EMsgClientToGCJoinPartyFromBeacon);
        CASE_STD_STRING(k_EMsgGCToClientJoinPartyFromBeaconResponse);
        CASE_STD_STRING(k_EMsgClientToGCGetFavoritePlayers);
        CASE_STD_STRING(k_EMsgGCToClientGetFavoritePlayersResponse);
        CASE_STD_STRING(k_EMsgClientToGCVerifyFavoritePlayers);
        CASE_STD_STRING(k_EMsgGCToClientVerifyFavoritePlayersResponse);
        CASE_STD_STRING(k_EMsgGCToClientPartySearchInvites);
        CASE_STD_STRING(k_EMsgGCToClientRequestMMInfo);
        CASE_STD_STRING(k_EMsgClientToGCMMInfo);
        CASE_STD_STRING(k_EMsgGCDev_GrantWarKill);
        CASE_STD_STRING(k_EMsgServerToGCLockCharmTrading);
        CASE_STD_STRING(k_EMsgClientToGCPlayerStatsRequest);
        CASE_STD_STRING(k_EMsgGCToClientPlayerStatsResponse);
        CASE_STD_STRING(k_EMsgGCClearPracticeLobbyTeam);
        CASE_STD_STRING(k_EMsgClientToGCFindTopSourceTVGames);
        CASE_STD_STRING(k_EMsgGCToClientFindTopSourceTVGamesResponse);
        CASE_STD_STRING(k_EMsgGCLobbyList);
        CASE_STD_STRING(k_EMsgGCLobbyListResponse);
        CASE_STD_STRING(k_EMsgGCPlayerStatsMatchSignOut);
        CASE_STD_STRING(k_EMsgClientToGCCustomGamePlayerCountRequest);
        CASE_STD_STRING(k_EMsgGCToClientCustomGamePlayerCountResponse);
        CASE_STD_STRING(k_EMsgClientToGCSocialFeedPostCommentRequest);
        CASE_STD_STRING(k_EMsgGCToClientSocialFeedPostCommentResponse);
        CASE_STD_STRING(k_EMsgClientToGCCustomGamesFriendsPlayedRequest);
        CASE_STD_STRING(k_EMsgGCToClientCustomGamesFriendsPlayedResponse);
        CASE_STD_STRING(k_EMsgClientToGCFriendsPlayedCustomGameRequest);
        CASE_STD_STRING(k_EMsgGCToClientFriendsPlayedCustomGameResponse);
        CASE_STD_STRING(k_EMsgGCTopCustomGamesList);
        CASE_STD_STRING(k_EMsgClientToGCSocialMatchPostCommentRequest);
        CASE_STD_STRING(k_EMsgGCToClientSocialMatchPostCommentResponse);
        CASE_STD_STRING(k_EMsgClientToGCSocialMatchDetailsRequest);
        CASE_STD_STRING(k_EMsgGCToClientSocialMatchDetailsResponse);
        CASE_STD_STRING(k_EMsgClientToGCSetPartyOpen);
        CASE_STD_STRING(k_EMsgClientToGCMergePartyInvite);
        CASE_STD_STRING(k_EMsgGCToClientMergeGroupInviteReply);
        CASE_STD_STRING(k_EMsgClientToGCMergePartyResponse);
        CASE_STD_STRING(k_EMsgGCToClientMergePartyResponseReply);
        CASE_STD_STRING(k_EMsgClientToGCGetProfileCardStats);
        CASE_STD_STRING(k_EMsgClientToGCGetProfileCardStatsResponse);
        CASE_STD_STRING(k_EMsgClientToGCTopLeagueMatchesRequest);
        CASE_STD_STRING(k_EMsgClientToGCTopFriendMatchesRequest);
        CASE_STD_STRING(k_EMsgGCToClientProfileCardStatsUpdated);
        CASE_STD_STRING(k_EMsgServerToGCRealtimeStats);
        CASE_STD_STRING(k_EMsgGCToServerRealtimeStatsStartStop);
        CASE_STD_STRING(k_EMsgGCToGCGetServersForClients);
        CASE_STD_STRING(k_EMsgGCToGCGetServersForClientsResponse);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyKickFromTeam);
        CASE_STD_STRING(k_EMsgDOTAChatGetMemberCount);
        CASE_STD_STRING(k_EMsgDOTAChatGetMemberCountResponse);
        CASE_STD_STRING(k_EMsgClientToGCSocialFeedPostMessageRequest);
        CASE_STD_STRING(k_EMsgGCToClientSocialFeedPostMessageResponse);
        CASE_STD_STRING(k_EMsgCustomGameListenServerStartedLoading);
        CASE_STD_STRING(k_EMsgCustomGameClientFinishedLoading);
        CASE_STD_STRING(k_EMsgGCPracticeLobbyCloseBroadcastChannel);
        CASE_STD_STRING(k_EMsgGCStartFindingMatchResponse);
        CASE_STD_STRING(k_EMsgSQLGCToGCGrantAccountFlag);
        CASE_STD_STRING(k_EMsgGCToGCGetAccountFlags);
        CASE_STD_STRING(k_EMsgGCToGCGetAccountFlagsResponse);
        CASE_STD_STRING(k_EMsgSignOutWagerStats);
        CASE_STD_STRING(k_EMsgGCToClientTopLeagueMatchesResponse);
        CASE_STD_STRING(k_EMsgGCToClientTopFriendMatchesResponse);
        CASE_STD_STRING(k_EMsgClientToGCMatchesMinimalRequest);
        CASE_STD_STRING(k_EMsgClientToGCMatchesMinimalResponse);
        CASE_STD_STRING(k_EMsgGCToGCGetProfileBadgePoints);
        CASE_STD_STRING(k_EMsgGCToGCGetProfileBadgePointsResponse);
        CASE_STD_STRING(k_EMsgGCToClientChatRegionsEnabled);
        CASE_STD_STRING(k_EMsgClientToGCPingData);
        CASE_STD_STRING(k_EMsgServerToGCMatchDetailsRequest);
        CASE_STD_STRING(k_EMsgGCToServerMatchDetailsResponse);
        CASE_STD_STRING(k_EMsgGCToGCEnsureAccountInParty);
        CASE_STD_STRING(k_EMsgGCToGCEnsureAccountInPartyResponse);
        CASE_STD_STRING(k_EMsgClientToGCGetProfileTickets);
        CASE_STD_STRING(k_EMsgClientToGCGetProfileTicketsResponse);
        CASE_STD_STRING(k_EMsgGCToClientMatchGroupsVersion);
        CASE_STD_STRING(k_EMsgClientToGCH264Unsupported);
        CASE_STD_STRING(k_EMsgClientToGCRequestH264Support);
        CASE_STD_STRING(k_EMsgClientToGCGetQuestProgress);
        CASE_STD_STRING(k_EMsgClientToGCGetQuestProgressResponse);
        CASE_STD_STRING(k_EMsgSignOutXPCoins);
        CASE_STD_STRING(k_EMsgGCToClientMatchSignedOut);
        CASE_STD_STRING(k_EMsgGCGetHeroStatsHistory);
        CASE_STD_STRING(k_EMsgGCGetHeroStatsHistoryResponse);
        CASE_STD_STRING(k_EMsgClientToGCPrivateChatInvite);
        CASE_STD_STRING(k_EMsgClientToGCPrivateChatKick);
        CASE_STD_STRING(k_EMsgClientToGCPrivateChatPromote);
        CASE_STD_STRING(k_EMsgClientToGCPrivateChatDemote);
        CASE_STD_STRING(k_EMsgGCToClientPrivateChatResponse);
        CASE_STD_STRING(k_EMsgClientToGCPrivateChatInfoRequest);
        CASE_STD_STRING(k_EMsgGCToClientPrivateChatInfoResponse);
        CASE_STD_STRING(k_EMsgClientToGCLatestConductScorecardRequest);
        CASE_STD_STRING(k_EMsgClientToGCLatestConductScorecard);
        CASE_STD_STRING(k_EMsgServerToGCPostMatchTip);
        CASE_STD_STRING(k_EMsgServerToGCPostMatchTipResponse);
        CASE_STD_STRING(k_EMsgClientToGCWageringRequest);
        CASE_STD_STRING(k_EMsgGCToClientWageringResponse);
        CASE_STD_STRING(k_EMsgClientToGCEventGoalsRequest);
        CASE_STD_STRING(k_EMsgClientToGCEventGoalsResponse);
        CASE_STD_STRING(k_EMsgClientToGCLeaguePredictions);
        CASE_STD_STRING(k_EMsgGCToClientLeaguePredictionsResponse);
        CASE_STD_STRING(k_EMsgGCToGCLeaguePredictionsUpdate);
        CASE_STD_STRING(k_EMsgClientToGCSuspiciousActivity);
        CASE_STD_STRING(k_EMsgGCToGCAddUserToPostGameChat);
        CASE_STD_STRING(k_EMsgClientToGCHasPlayerVotedForMVP);
        CASE_STD_STRING(k_EMsgClientToGCHasPlayerVotedForMVPResponse);
        CASE_STD_STRING(k_EMsgClientToGCVoteForMVP);
        CASE_STD_STRING(k_EMsgClientToGCVoteForMVPResponse);
        CASE_STD_STRING(k_EMsgGCToGCGetEventOwnership);
        CASE_STD_STRING(k_EMsgGCToGCGetEventOwnershipResponse);
        CASE_STD_STRING(k_EMsgGCToClientAutomatedTournamentStateChange);
        CASE_STD_STRING(k_EMsgClientToGCWeekendTourneyOpts);
        CASE_STD_STRING(k_EMsgClientToGCWeekendTourneyOptsResponse);
        CASE_STD_STRING(k_EMsgClientToGCWeekendTourneyLeave);
        CASE_STD_STRING(k_EMsgClientToGCWeekendTourneyLeaveResponse);
        CASE_STD_STRING(k_EMsgClientToGCTeammateStatsRequest);
        CASE_STD_STRING(k_EMsgClientToGCTeammateStatsResponse);
        CASE_STD_STRING(k_EMsgClientToGCGetGiftPermissions);
        CASE_STD_STRING(k_EMsgClientToGCGetGiftPermissionsResponse);
        CASE_STD_STRING(k_EMsgClientToGCVoteForArcana);
        CASE_STD_STRING(k_EMsgClientToGCVoteForArcanaResponse);
        CASE_STD_STRING(k_EMsgClientToGCRequestArcanaVotesRemaining);
        CASE_STD_STRING(k_EMsgClientToGCRequestArcanaVotesRemainingResponse);
        CASE_STD_STRING(k_EMsgGCTransferTeamAdminResponse);
        CASE_STD_STRING(k_EMsgGCToClientTeamInfo);
        CASE_STD_STRING(k_EMsgGCToClientTeamsInfo);
        CASE_STD_STRING(k_EMsgClientToGCMyTeamInfoRequest);
        CASE_STD_STRING(k_EMsgClientToGCPublishUserStat);
        CASE_STD_STRING(k_EMsgGCToGCSignoutSpendWager);
        CASE_STD_STRING(k_EMsgGCSubmitLobbyMVPVote);
        CASE_STD_STRING(k_EMsgGCSubmitLobbyMVPVoteResponse);
        CASE_STD_STRING(k_EMsgSignOutCommunityGoalProgress);
        CASE_STD_STRING(k_EMsgGCToClientLobbyMVPNotifyRecipient);
        CASE_STD_STRING(k_EMsgGCToClientLobbyMVPAwarded);
        CASE_STD_STRING(k_EMsgGCToClientQuestProgressUpdated);
        CASE_STD_STRING(k_EMsgGCToClientWageringUpdate);
        CASE_STD_STRING(k_EMsgGCToClientArcanaVotesUpdate);
        CASE_STD_STRING(k_EMsgClientToGCAddTI6TreeProgress);
        CASE_STD_STRING(k_EMsgClientToGCSetSpectatorLobbyDetails);
        CASE_STD_STRING(k_EMsgClientToGCSetSpectatorLobbyDetailsResponse);
        CASE_STD_STRING(k_EMsgClientToGCCreateSpectatorLobby);
        CASE_STD_STRING(k_EMsgClientToGCCreateSpectatorLobbyResponse);
        CASE_STD_STRING(k_EMsgClientToGCSpectatorLobbyList);
        CASE_STD_STRING(k_EMsgClientToGCSpectatorLobbyListResponse);
        CASE_STD_STRING(k_EMsgSpectatorLobbyGameDetails);
        CASE_STD_STRING(k_EMsgServerToGCCompendiumInGamePredictionResults);
        CASE_STD_STRING(k_EMsgServerToGCCloseCompendiumInGamePredictionVoting);
        CASE_STD_STRING(k_EMsgClientToGCOpenPlayerCardPack);
        CASE_STD_STRING(k_EMsgClientToGCOpenPlayerCardPackResponse);
        CASE_STD_STRING(k_EMsgClientToGCSelectCompendiumInGamePrediction);
        CASE_STD_STRING(k_EMsgClientToGCSelectCompendiumInGamePredictionResponse);
        CASE_STD_STRING(k_EMsgClientToGCWeekendTourneyGetPlayerStats);
        CASE_STD_STRING(k_EMsgClientToGCWeekendTourneyGetPlayerStatsResponse);
        CASE_STD_STRING(k_EMsgClientToGCRecyclePlayerCard);
        CASE_STD_STRING(k_EMsgClientToGCRecyclePlayerCardResponse);
        CASE_STD_STRING(k_EMsgClientToGCCreatePlayerCardPack);
        CASE_STD_STRING(k_EMsgClientToGCCreatePlayerCardPackResponse);
        CASE_STD_STRING(k_EMsgClientToGCGetPlayerCardRosterRequest);
        CASE_STD_STRING(k_EMsgClientToGCGetPlayerCardRosterResponse);
        CASE_STD_STRING(k_EMsgClientToGCSetPlayerCardRosterRequest);
        CASE_STD_STRING(k_EMsgClientToGCSetPlayerCardRosterResponse);
        CASE_STD_STRING(k_EMsgServerToGCCloseCompendiumInGamePredictionVotingResponse);
        CASE_STD_STRING(k_EMsgServerToGCCompendiumInGamePredictionResultsResponse);
        CASE_STD_STRING(k_EMsgLobbyBattleCupVictory);
        CASE_STD_STRING(k_EMsgGCGetPlayerCardItemInfo);
        CASE_STD_STRING(k_EMsgGCGetPlayerCardItemInfoResponse);
        CASE_STD_STRING(k_EMsgClientToGCRequestSteamDatagramTicket);
        CASE_STD_STRING(k_EMsgClientToGCRequestSteamDatagramTicketResponse);
        CASE_STD_STRING(k_EMsgGCToClientBattlePassRollupRequest);
        CASE_STD_STRING(k_EMsgGCToClientBattlePassRollupResponse);
        CASE_STD_STRING(k_EMsgClientToGCTransferSeasonalMMRRequest);
        CASE_STD_STRING(k_EMsgClientToGCTransferSeasonalMMRResponse);
        CASE_STD_STRING(k_EMsgGCToGCPublicChatCommunicationBan);
        CASE_STD_STRING(k_EMsgGCToGCUpdateAccountPublicChatBan);
        CASE_STD_STRING(k_EMsgGCChatReportPublicSpam);
        CASE_STD_STRING(k_EMsgClientToGCSetPartyBuilderOptions);
        CASE_STD_STRING(k_EMsgClientToGCSetPartyBuilderOptionsResponse);
        CASE_STD_STRING(k_EMsgGCToClientPlaytestStatus);
        CASE_STD_STRING(k_EMsgClientToGCJoinPlaytest);
        CASE_STD_STRING(k_EMsgClientToGCJoinPlaytestResponse);
        CASE_STD_STRING(k_EMsgLobbyPlaytestDetails);
        CASE_STD_STRING(k_EMsgDOTASetFavoriteTeam);
        CASE_STD_STRING(k_EMsgGCToClientBattlePassRollupListRequest);
        CASE_STD_STRING(k_EMsgGCToClientBattlePassRollupListResponse);
        CASE_STD_STRING(k_EMsgGCIsProQuery);
        CASE_STD_STRING(k_EMsgGCIsProResponse);
        CASE_STD_STRING(k_EMsgDOTAClaimEventAction);
        CASE_STD_STRING(k_EMsgDOTAClaimEventActionResponse);
        CASE_STD_STRING(k_EMsgDOTAGetPeriodicResource);
        CASE_STD_STRING(k_EMsgDOTAGetPeriodicResourceResponse);
        CASE_STD_STRING(k_EMsgDOTAPeriodicResourceUpdated);
        CASE_STD_STRING(k_EMsgServerToGCSpendWager);
        CASE_STD_STRING(k_EMsgGCToGCSignoutSpendWagerToken);
        CASE_STD_STRING(k_EMsgSubmitTriviaQuestionAnswer);
        CASE_STD_STRING(k_EMsgSubmitTriviaQuestionAnswerResponse);
        CASE_STD_STRING(k_EMsgClientToGCGiveTip);
        CASE_STD_STRING(k_EMsgClientToGCGiveTipResponse);
        CASE_STD_STRING(k_EMsgStartTriviaSession);
        CASE_STD_STRING(k_EMsgStartTriviaSessionResponse);
        CASE_STD_STRING(k_EMsgAnchorPhoneNumberRequest);
        CASE_STD_STRING(k_EMsgAnchorPhoneNumberResponse);
        CASE_STD_STRING(k_EMsgUnanchorPhoneNumberRequest);
        CASE_STD_STRING(k_EMsgUnanchorPhoneNumberResponse);
        CASE_STD_STRING(k_EMsgGCToClientTipNotification);
        CASE_STD_STRING(k_EMsgClientToGCRequestSlarkGameResult);
        CASE_STD_STRING(k_EMsgClientToGCRequestSlarkGameResultResponse);
        CASE_STD_STRING(k_EMsgGCToGCSignoutSpendRankWager);
        CASE_STD_STRING(k_EMsgGCToGCGetFavoriteTeam);
        CASE_STD_STRING(k_EMsgGCToGCGetFavoriteTeamResponse);
        CASE_STD_STRING(k_EMsgSignOutEventGameData);
        CASE_STD_STRING(k_EMsgGCToClientAllStarVotesRequest);
        CASE_STD_STRING(k_EMsgGCToClientAllStarVotesReply);
        CASE_STD_STRING(k_EMsgGCToClientAllStarVotesSubmit);
        CASE_STD_STRING(k_EMsgGCToClientAllStarVotesSubmitReply);
        CASE_STD_STRING(k_EMsgClientToGCQuickStatsRequest);
        CASE_STD_STRING(k_EMsgClientToGCQuickStatsResponse);
        CASE_STD_STRING(k_EMsgGCToGCSubtractEventPointsFromUser);
        CASE_STD_STRING(k_EMsgSelectionPriorityChoiceRequest);
        CASE_STD_STRING(k_EMsgSelectionPriorityChoiceResponse);
        CASE_STD_STRING(k_EMsgGCToGCCompendiumInGamePredictionResults);
        CASE_STD_STRING(k_EMsgGameAutographReward);
        CASE_STD_STRING(k_EMsgGameAutographRewardResponse);
        CASE_STD_STRING(k_EMsgDestroyLobbyRequest);
        CASE_STD_STRING(k_EMsgDestroyLobbyResponse);
        CASE_STD_STRING(k_EMsgPurchaseItemWithEventPoints);
        CASE_STD_STRING(k_EMsgPurchaseItemWithEventPointsResponse);
        CASE_STD_STRING(k_EMsgServerToGCMatchPlayerItemPurchaseHistory);
        CASE_STD_STRING(k_EMsgGCToGCGrantPlusHeroMatchResults);
        CASE_STD_STRING(k_EMsgGCGetHeroTimedStats);
        CASE_STD_STRING(k_EMsgGCGetHeroTimedStatsResponse);
        CASE_STD_STRING(k_EMsgLobbyPlayerPlusSubscriptionData);
        CASE_STD_STRING(k_EMsgServerToGCMatchStateHistory);
        CASE_STD_STRING(k_EMsgPurchaseHeroRelic);
        CASE_STD_STRING(k_EMsgPurchaseHeroRelicResponse);
        CASE_STD_STRING(k_EMsgPurchaseHeroRandomRelic);
        CASE_STD_STRING(k_EMsgPurchaseHeroRandomRelicResponse);
        CASE_STD_STRING(k_EMsgClientToGCClaimEventActionUsingItem);
        CASE_STD_STRING(k_EMsgClientToGCClaimEventActionUsingItemResponse);
        CASE_STD_STRING(k_EMsgPartyReadyCheckRequest);
        CASE_STD_STRING(k_EMsgPartyReadyCheckResponse);
        CASE_STD_STRING(k_EMsgPartyReadyCheckAcknowledge);
        CASE_STD_STRING(k_EMsgGetRecentPlayTimeFriendsRequest);
        CASE_STD_STRING(k_EMsgGetRecentPlayTimeFriendsResponse);
        CASE_STD_STRING(k_EMsgGCToClientCommendNotification);
        CASE_STD_STRING(k_EMsgProfileRequest);
        CASE_STD_STRING(k_EMsgProfileResponse);
        CASE_STD_STRING(k_EMsgProfileUpdate);
        CASE_STD_STRING(k_EMsgProfileUpdateResponse);
        CASE_STD_STRING(k_EMsgSuccessfulHero);
        CASE_STD_STRING(k_EMsgHeroGlobalDataRequest);
        CASE_STD_STRING(k_EMsgHeroGlobalDataResponse);
        CASE_STD_STRING(k_EMsgClientToGCRequestPlusWeeklyChallengeResult);
        CASE_STD_STRING(k_EMsgClientToGCRequestPlusWeeklyChallengeResultResponse);
        CASE_STD_STRING(k_EMsgGCToGCGrantPlusPrepaidTime);
        CASE_STD_STRING(k_EMsgPrivateMetadataKeyRequest);
        CASE_STD_STRING(k_EMsgPrivateMetadataKeyResponse);
        CASE_STD_STRING(k_EMsgGCToGCReconcilePlusStatus);
        CASE_STD_STRING(k_EMsgGCToGCCheckPlusStatus);
        CASE_STD_STRING(k_EMsgGCToGCCheckPlusStatusResponse);
        CASE_STD_STRING(k_EMsgGCToGCReconcilePlusAutoGrantItems);
        CASE_STD_STRING(k_EMsgGCToGCReconcilePlusStatusUnreliable);
        CASE_STD_STRING(k_EMsgActivatePlusFreeTrialRequest);
        CASE_STD_STRING(k_EMsgActivatePlusFreeTrialResponse);
        CASE_STD_STRING(k_EMsgGCToClientCavernCrawlMapPathCompleted);
        CASE_STD_STRING(k_EMsgClientToGCCavernCrawlClaimRoom);
        CASE_STD_STRING(k_EMsgClientToGCCavernCrawlClaimRoomResponse);
        CASE_STD_STRING(k_EMsgClientToGCCavernCrawlUseItemOnRoom);
        CASE_STD_STRING(k_EMsgClientToGCCavernCrawlUseItemOnRoomResponse);
        CASE_STD_STRING(k_EMsgClientToGCCavernCrawlUseItemOnPath);
        CASE_STD_STRING(k_EMsgClientToGCCavernCrawlUseItemOnPathResponse);
        CASE_STD_STRING(k_EMsgClientToGCCavernCrawlRequestMapState);
        CASE_STD_STRING(k_EMsgClientToGCCavernCrawlRequestMapStateResponse);
        CASE_STD_STRING(k_EMsgSignOutTips);
        CASE_STD_STRING(k_EMsgClientToGCRequestEventPointLogV2);
        CASE_STD_STRING(k_EMsgClientToGCRequestEventPointLogResponseV2);
        CASE_STD_STRING(k_EMsgClientToGCRequestEventTipsSummary);
        CASE_STD_STRING(k_EMsgClientToGCRequestEventTipsSummaryResponse);
        CASE_STD_STRING(k_EMsgHeroGlobalDataAllHeroes);
        CASE_STD_STRING(k_EMsgClientToGCRequestSocialFeed);
        CASE_STD_STRING(k_EMsgClientToGCRequestSocialFeedResponse);
        CASE_STD_STRING(k_EMsgClientToGCRequestSocialFeedComments);
        CASE_STD_STRING(k_EMsgClientToGCRequestSocialFeedCommentsResponse);
        CASE_STD_STRING(k_EMsgClientToGCCavernCrawlGetClaimedRoomCount);
        CASE_STD_STRING(k_EMsgClientToGCCavernCrawlGetClaimedRoomCountResponse);
        CASE_STD_STRING(k_EMsgGCToGCReconcilePlusAutoGrantItemsUnreliable);
        CASE_STD_STRING(k_EMsgServerToGCAddBroadcastTimelineEvent);
        CASE_STD_STRING(k_EMsgGCToServerUpdateSteamBroadcasting);
        CASE_STD_STRING(k_EMsgClientToGCRecordContestVote);
        CASE_STD_STRING(k_EMsgGCToClientRecordContestVoteResponse);
        CASE_STD_STRING(k_EMsgGCToGCGrantAutograph);
        CASE_STD_STRING(k_EMsgGCToGCGrantAutographResponse);
        CASE_STD_STRING(k_EMsgSignOutConsumableUsage);
        CASE_STD_STRING(k_EMsgLobbyEventGameDetails);
        CASE_STD_STRING(k_EMsgDevGrantEventPoints);
        CASE_STD_STRING(k_EMsgDevGrantEventPointsResponse);
        CASE_STD_STRING(k_EMsgDevGrantEventAction);
        CASE_STD_STRING(k_EMsgDevGrantEventActionResponse);
        CASE_STD_STRING(k_EMsgDevResetEventState);
        CASE_STD_STRING(k_EMsgDevResetEventStateResponse);
        CASE_STD_STRING(k_EMsgGCToGCReconcileEventOwnership);
        CASE_STD_STRING(k_EMsgConsumeEventSupportGrantItem);
        CASE_STD_STRING(k_EMsgConsumeEventSupportGrantItemResponse);
        CASE_STD_STRING(k_EMsgGCToClientClaimEventActionUsingItemCompleted);
        CASE_STD_STRING(k_EMsgGCToClientCavernCrawlMapUpdated);
        CASE_STD_STRING(k_EMsgServerToGCRequestPlayerRecentAccomplishments);
        CASE_STD_STRING(k_EMsgServerToGCRequestPlayerRecentAccomplishmentsResponse);
        CASE_STD_STRING(k_EMsgClientToGCRequestPlayerRecentAccomplishments);
        CASE_STD_STRING(k_EMsgClientToGCRequestPlayerRecentAccomplishmentsResponse);
        CASE_STD_STRING(k_EMsgClientToGCRequestPlayerHeroRecentAccomplishments);
        CASE_STD_STRING(k_EMsgClientToGCRequestPlayerHeroRecentAccomplishmentsResponse);
        CASE_STD_STRING(k_EMsgSignOutEventActionGrants);
        CASE_STD_STRING(k_EMsgClientToGCRequestPlayerCoachMatches);
        CASE_STD_STRING(k_EMsgClientToGCRequestPlayerCoachMatchesResponse);
        CASE_STD_STRING(k_EMsgClientToGCGetTicketCodesRequest);
        CASE_STD_STRING(k_EMsgClientToGCGetTicketCodesResponse);
        CASE_STD_STRING(k_EMsgClientToGCSubmitCoachTeammateRating);
        CASE_STD_STRING(k_EMsgClientToGCSubmitCoachTeammateRatingResponse);
        CASE_STD_STRING(k_EMsgGCToClientCoachTeammateRatingsChanged);
        CASE_STD_STRING(k_EMsgClientToGCVoteForLeagueGameMVP);
        CASE_STD_STRING(k_EMsgClientToGCRequestPlayerCoachMatch);
        CASE_STD_STRING(k_EMsgClientToGCRequestPlayerCoachMatchResponse);
        CASE_STD_STRING(k_EMsgClientToGCRequestContestVotes);
        CASE_STD_STRING(k_EMsgClientToGCRequestContestVotesResponse);
        CASE_STD_STRING(k_EMsgClientToGCMVPVoteTimeout);
        CASE_STD_STRING(k_EMsgClientToGCMVPVoteTimeoutResponse);
        CASE_STD_STRING(k_EMsgClientToGCGetUnderlordsCDKeyRequest);
        CASE_STD_STRING(k_EMsgClientToGCGetUnderlordsCDKeyResponse);
        CASE_STD_STRING(k_EMsgDetailedGameStats);
        CASE_STD_STRING(k_EMsgClientToGCSetFavoriteAllStarPlayer);
        CASE_STD_STRING(k_EMsgClientToGCSetFavoriteAllStarPlayerResponse);
        CASE_STD_STRING(k_EMsgAllStarStats);
        CASE_STD_STRING(k_EMsgClientToGCGetFavoriteAllStarPlayerRequest);
        CASE_STD_STRING(k_EMsgClientToGCGetFavoriteAllStarPlayerResponse);
        CASE_STD_STRING(k_EMsgClientToGCVerifyIntegrity);
        CASE_STD_STRING(k_EMsgMatchMatchmakingStats);
        CASE_STD_STRING(k_EMsgClientToGCSubmitPlayerMatchSurvey);
        CASE_STD_STRING(k_EMsgClientToGCSubmitPlayerMatchSurveyResponse);
        CASE_STD_STRING(k_EMsgSQLGCToGCGrantAllHeroProgressAccount);
        CASE_STD_STRING(k_EMsgSQLGCToGCGrantAllHeroProgressVictory);
        CASE_STD_STRING(k_eMsgGCToGCGetAllHeroCurrent);
        CASE_STD_STRING(k_eMsgGCToGCGetAllHeroCurrentResponse);
        CASE_STD_STRING(k_EMsgGCSubmitPlayerAvoidRequest);
        CASE_STD_STRING(k_EMsgGCSubmitPlayerAvoidRequestResponse);
        CASE_STD_STRING(k_EMsgGCToClientNotificationsUpdated);
        CASE_STD_STRING(k_EMsgGCtoGCAssociatedExploiterAccountInfo);
        CASE_STD_STRING(k_EMsgGCtoGCAssociatedExploiterAccountInfoResponse);
        default:
            return std::string( std::to_string(int(msg)) );
    }
}
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

class CNetPacket
{
public:
    int notsure;
    int cubData;
    void *pubData;
};

class IMsgNetPacket
{
public:
    virtual void DESTROY() = 0;
    virtual void DESTROY2() = 0;
    virtual void DestroyThis(void) = 0;
    virtual int GetEMsgFormatType(void) = 0;
    virtual CNetPacket* GetCNetPacket(void) = 0;
    virtual const uint8_t *PubData(void) = 0; // Pointer-Unsigned-Byte Data
    virtual uint32_t CubData(void) = 0; // Count-Unsigned-Byte Data - u can find some of this in the steamworks sdk
    virtual EDOTAGCMsg GetEMsg(void) = 0;
    virtual int GetSourceJobID(void) = 0;
    virtual unsigned long long GetTargetJobID(void) = 0;
    virtual void SetTargetJobID(unsigned long long) = 0;
    virtual int64_t GetSteamID(void) = 0;
    virtual void SetSteamID(int64_t CSteamID) = 0;
    virtual unsigned int GetSourceAppID(void) = 0;
    virtual void SetSourceAppID(unsigned int) = 0;
    virtual bool BHasTargetJobName(void) = 0;
    virtual const char *GetTargetJobName(void) = 0;

    inline void GetMsgBody( const uint8_t **msg, uint32_t *msgSize )
    {
        unsigned int messageSize = *(unsigned int*)(this->PubData() + 4);
        messageSize += 8; // min size
        *msg = this->PubData() + messageSize;
        *msgSize = this->CubData() - messageSize;
    }
};

class CMsgProtoBufHeader;
class IProtoBufSendHandler
{
public:
    virtual bool BAsyncSend( EDOTAGCMsg eMsg, const uint8_t *pubMsgBytes, uint32 cubSize ) = 0;
};

class CProtoBufMsgBase
{
public:
    virtual ~CProtoBufMsgBase() = 0;
    virtual void DESTROY2() = 0;
    virtual google::protobuf::Message *GetGenericBody(void) = 0;

    void *pNetPacket;
    CMsgProtoBufHeader *pProtoBufHdr;
    EDOTAGCMsg eMsg;
    char _pad[4];
};

template<typename T>
class CProtoBufMsg : CProtoBufMsgBase
{
public:

    T *pProtoBufBody;
};

class CProtobuffBinding
{
public:
    virtual const char* GetName(void) = 0;
    virtual int GetSize(void) = 0;
    virtual const char* ToString(google::protobuf::Message *msg, CUtlString *storage) = 0;
    virtual const char *GetGroup(void) = 0;
    virtual ColorRGBA GetGroupColor(void) = 0;
    virtual NetChannelBufType_t GetBufType(void) = 0;
    virtual bool ReadFromBuffer(google::protobuf::Message *msg, bf_read &); // true if parsing O = 0K
    virtual bool WriteToBuffer(google::protobuf::Message *msg, bf_write &); // true if parsing O = 0K
    virtual void AllocateMessage(void) = 0;
    virtual void DeallocateMessage(void *) = 0;
    virtual void AllocateAndCopyConstructNetMessage(void const*) = 0;
    virtual bool OkToRedispatch(void) = 0;
    virtual void Copy(void const*,void *) = 0;
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
    int16_t messageID;
    uint8_t groupID;
    uint8_t defaultBufferType;
    char _pad[28];
};

typedef CNetworkSerializerPB GameEventHandle_t;
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
    virtual void FindNetworkMessage3() = 0;
    virtual int GetNetworkGroupCount(void) = 0;
    virtual const char* GetNetworkGroupName(int groupId) = 0;
    virtual int FindNetworkGroup(const char*, bool) = 0;
    virtual void AssociateNetMessageGroupIdWithChannelCategory(unsigned int, const char*) = 0; // "AssociateNetMessageGroupIdWithChannelCategory: Trying to use"
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