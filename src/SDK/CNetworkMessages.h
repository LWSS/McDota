#pragma once

#include "INetChannel.h"
#include "INetworkClientService.h"
#include "bf_read.h"
#include "CUtlString.h"


enum NetMessageTypes : int
{
    CNETMsg_Tick = 4,
    CCLCMsg_Move = 21,

    CMsgSource1LegacyListenEvents = 206,


    DOTA_CM_MapLine = 301,
    DOTA_CM_AspectRatio = 302,
    DOTA_CM_MapPing = 303,
    DOTA_CM_UnitsAutoAttack = 304,
    DOTA_CM_SearchString = 307,
    DOTA_CM_Pause = 308,
    DOTA_CM_ShopViewMode = 309,
    DOTA_CM_SetUnitShareFlag = 310,
    DOTA_CM_SwapRequest = 311,
    DOTA_CM_SwapAccept = 312,
    DOTA_CM_WorldLine = 313,
    DOTA_CM_RequestGraphUpdate = 314,
    DOTA_CM_ItemAlert = 315,
    DOTA_CM_ChatWheel = 316,
    DOTA_CM_SendStatPopup = 317,
    DOTA_CM_BeginLastHitChallenge = 318,
    DOTA_CM_UpdateQuickBuy = 319,
    DOTA_CM_UpdateCoachListen = 320,
    DOTA_CM_CoachHUDPing = 321,
    DOTA_CM_RecordVote = 322,
    DOTA_CM_UnitsAutoAttackAfterSpell = 323,
    DOTA_CM_WillPurchaseAlert = 324,
    DOTA_CM_PlayerShowCase = 325,
    DOTA_CM_TeleportRequiresHalt = 326,
    DOTA_CM_CameraZoomAmount = 327,
    DOTA_CM_BroadcasterUsingCamerman = 328,
    DOTA_CM_BroadcasterUsingAssistedCameraOperator = 329,
    DOTA_CM_EnemyItemAlert = 330,
    DOTA_CM_FreeInventory = 331,
    DOTA_CM_BuyBackStateAlert = 332,
    DOTA_CM_QuickBuyAlert = 333,
    DOTA_CM_HeroStatueLike = 334,
    DOTA_CM_ModifierAlert = 335,
    DOTA_CM_TeamShowcaseEditor = 336,
    DOTA_CM_HPManaAlert = 337,
    DOTA_CM_GlyphAlert = 338,
    DOTA_CM_TeamShowcaseClientData = 339,
    DOTA_CM_PlayTeamShowcase = 340,
    DOTA_CM_EventCNY2015Cmd = 341,
    DOTA_CM_FillEmptySlotsWithBots = 342,
    DOTA_CM_DemoHero = 343,
    DOTA_CM_AbilityLearnModeToggled = 344,
    DOTA_CM_AbilityStartUse = 345,
    DOTA_CM_ChallengeSelect = 346,
    DOTA_CM_ChallengeReroll = 347,
    DOTA_CM_ClickedBuff = 348,
    DOTA_CM_CoinWager = 349,
    DOTA_CM_ExecuteOrders = 350,
    DOTA_CM_XPAlert = 351,
    DOTA_CM_EventPointsTip = 353,
    DOTA_CM_MatchMetadata = 354,
    DOTA_CM_KillMyHero = 355,
    DOTA_CM_QuestStatus = 356,
    DOTA_CM_ToggleAutoattack = 357,
    DOTA_CM_SpecialAbility = 358,
    DOTA_CM_KillcamDamageTaken = 359,
    DOTA_CM_SetEnemyStartingPosition = 360,
    DOTA_CM_SetDesiredWardPlacement = 361,
    DOTA_CM_RollDice = 362,
    DOTA_CM_FlipCoin = 363,
    DOTA_CM_RequestItemSuggestions = 364,
    DOTA_CM_MakeTeamCaptain = 365,
    DOTA_CM_CoinWagerToken = 366,
    DOTA_CM_RankWager = 367,
    DOTA_CM_DismissAllStatPopups = 368,
    DOTA_CM_HelpTipSystemStateChanged = 369,
    DOTA_CM_ChannelRequiresHalt = 370,
    DOTA_CM_RequestBulkCombatLog = 371,
    DOTA_CM_AbilityDraftRequestAbility = 372,
    DOTA_CM_GuideSelectOption = 373,
    DOTA_CM_GuideSelected = 374,
    DOTA_CM_DamageReport = 375,
    DOTA_CM_SalutePlayer = 376,
    DOTA_CM_SprayWheel = 377,
    DOTA_CM_TipAlert = 378,
    DOTA_CM_EmptyTeleportAlert = 379,
};
class CProtobuffBinding
{
public:
    virtual const char* GetName(void);
    virtual int GetSize(void);
    virtual void ToString(CUtlString *strOut);
    //virtual void ToString(std::string const &);
    virtual const char *GetGroup(void);
    virtual ColorRGBA GetGroupColor(void);
    virtual NetChannelBufType_t GetBufType(void);
    virtual bool ReadFromBuffer(void *,bf_read &);
    virtual bool WriteToBuffer(void const*, void *bf_writeRef );
    virtual void AllocateMessage(void);
    virtual void DeallocateMessage(void *);
    virtual void AllocateAndCopyConstructNetMessage(void const*);
    virtual bool OkToRedispatch(void);
    virtual void Copy(void const*,void *);
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
    virtual void FindOrCreateNetMessage(int, void const* IProtobufBinding, unsigned int, void* INetworkSerializerBindingBuildFilter, bool, bool) = 0;
    virtual void Serialize(void *bfWriteRef, NetMessageHandle_t *, void const*) = 0;
    virtual void Unserialize(void *bfReadRef, NetMessageHandle_t *, void *) = 0;
    virtual void Unserialize(void *bfReadRef, NetMessageHandle_t **, void **) = 0;
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
};