#pragma once

#include "Schema.h"
#include "vector.h"
#include "CCollisionProperty.h"
#include "Datamap.h"


enum OverlayFlags_t : unsigned long long
{
    BBOX = (1 << 2), //4
    ABSBOX = (1 << 5),//32
    RBOX = (1 << 6), //64
    ENTITYBOUNDS = (1 << 7), //128 - Looks like it depends on a byte being set in the class.
    ENTITYATTACHMENTS = (3 << 8), //BYTE1(flags) & 3
    ENTITYJOINTINFO = 0x40000,
    ENTITYSKELETON = (24 << 8), //BYTE1(flags) & 24 // kinda slow.
    ENTITYHITBOXES = (192 << 8), //BYTE1(flags) & 192
    BUDDHA = 0x40000000,
    ENTITYVIEWOFFSET = 0x800000000
};

enum DOTATeam_t : int {
    DOTA_TEAM_INVALID = -1,
    DOTA_TEAM_FIRST = 2,
    DOTA_TEAM_GOODGUYS = 2, //Radiant team.
    DOTA_TEAM_BADGUYS = 3, 	//Dire team.
    DOTA_TEAM_NEUTRALS = 4, //Neutral.
    DOTA_TEAM_NOTEAM = 5,
    DOTA_TEAM_CUSTOM_1 = 6,
    DOTA_TEAM_CUSTOM_MIN = 6,
    DOTA_TEAM_CUSTOM_2 = 7,
    DOTA_TEAM_CUSTOM_3 = 8,
    DOTA_TEAM_CUSTOM_COUNT = 8,
    DOTA_TEAM_CUSTOM_4 = 9,
    DOTA_TEAM_CUSTOM_5 = 10,
    DOTA_TEAM_CUSTOM_6 = 11,
    DOTA_TEAM_CUSTOM_7 = 12,
    DOTA_TEAM_CUSTOM_8 = 13,
    DOTA_TEAM_CUSTOM_MAX = 13,
    DOTA_TEAM_COUNT = 14
};

struct RenderableInstance_t{
    uint8_t m_nAlpha;
};


class ClientClass;
//xref "SUB_Remove called on entity" to SUB_Remove()
class CBaseEntity
{
public:
    inline DOTATeam_t GetTeam( )
    {
        static int offset = Util::FindDataMapElementOffset( this->C_DOTAPlayer__GetPredDescMap(), "m_iTeamNum" );
        if( !offset ){
            return DOTA_TEAM_INVALID;
        }
        return *( DOTATeam_t* )( ((uintptr_t)this) + offset );
    }
    inline QAngle* GetNetworkAngles( )
    {
        static int offset = Util::FindDataMapElementOffset( this->C_DOTAPlayer__GetPredDescMap(), "m_angNetworkAngles" );
        if( !offset ){
            return nullptr;
        }
        return ( QAngle* )( ((uintptr_t)this) + offset );
    }
    inline Vector* GetNetworkOrigin( )
    {
        static int offset = Util::FindDataMapElementOffset( this->C_DOTAPlayer__GetPredDescMap(), "m_vecNetworkOrigin" );
        if( !offset ){
            return nullptr;
        }
        return ( Vector* )( ((uintptr_t)this) + offset );
    }
    inline int GetOwnerID( )
    {
        static int offset = Util::FindDataMapElementOffset( this->C_DOTAPlayer__GetPredDescMap(), "m_hOwnerEntity" );
        if( !offset ){
            return -1;
        }
        int *ptr = ( int* )( ((uintptr_t)this) + offset );
        if( *ptr < 0 ){
            return -1;
        }
        return *ptr & 0xFFF;
    }
    virtual CSchemaClassBinding* Schema_DynamicBinding(void);
    virtual void DESTROY();
    virtual void DESTROY2();
    virtual int CEntityInstance__GetRefEHandle(void);
    virtual void* C_BaseCombatCharacter__GetScriptDesc(void);
    virtual void C_BaseFlex__Connect(void);
    virtual void PreCache() = 0;
    virtual void C_BaseAnimating__AddedToEntityDatabase(void);
    virtual void C_DOTAPlayer__Spawn(void* CEntityKeyValues);
    virtual void C_DOTAPlayer__PostDataUpdate(int DataUpdateType_t);
    virtual void C_BaseFlex__Activate(void);
    virtual void C_BasePlayer__UpdateOnRemove(void);
    virtual void C_BaseAnimating__OnSetDormant(void); // 0FFFFFFFEh
    virtual void C_BasePlayer__PreDataUpdate(int DataUpdateType_t);
    virtual void C_BaseEntity__DrawEntityDebugOverlays(OverlayFlags_t flags);
    virtual void sub_2F95420(); // added with dota-anime
    virtual void C_BaseEntity__Save( void* ISave ); // miner54
    virtual void C_BaseEntity__Restore( void* IRestore );
    virtual void C_BaseEntity__OnSave(void);
    virtual void C_BasePlayer__OnRestore(void);
    virtual void C_BaseEntity__ObjectCaps(void); // miner50
    virtual int CEntityInstance__RequiredEdictIndex(void);
    virtual void C_BaseEntity__NetworkStateChanged(void);
    virtual void C_BaseEntity__NetworkStateChanged2(unsigned int unk, int unk2, int ChangeAccessorFieldPathIndex_t);
    virtual void sub_273BE20();
    virtual void CEntityInstance__AddChangeAccessorPath(void* CFieldPath);
    virtual void CEntityInstance__ReloadPrivateScripts(void);
    virtual Datamap* C_DOTAPlayer__GetPredDescMap(void);
    virtual void YouForgotToImplementOrDeclareClientClass();
    virtual ClientClass* C_DOTAPlayer__GetClientClass(void);
    virtual void* datamap_maybe(); // might be the missing datamap from above. unsure - diretide 2020
    virtual void C_BaseModelEntity__SpawnShared(void* CEntityKeyValues);
    virtual void C_BaseModelEntity__PopulatePoseParameters(void);
    virtual void C_BasePlayer__PreFirstNetworkUpdate(void);
    virtual void* C_BaseModelEntity__GetBaseModelEntity(void);
    virtual void* C_BaseModelEntity__GetBaseModelEntity2(void);
    virtual void* C_BaseAnimating__GetBaseAnimating(void);
    virtual void* C_BaseAnimating__GetBaseAnimating2(void); // +38
    virtual void sub_285FB30();
    virtual void sub_285FB40();
    virtual bool C_BasePlayer__Classify(void);
    virtual CCollisionProperty* C_BaseModelEntity__GetCollideable(void); // moved w/ diretide 2020
    virtual void C_BaseEntity__ModifyEconParticles(int unk);
    virtual bool C_BaseEntity__ShouldSavePhysics(void);
    virtual bool C_BaseEntity__CreateVPhysics(void);
    virtual void C_BaseAnimating__DrawVCollide(void);
    virtual void C_BaseEntity__VPhysicsDestroyObject(void);
    virtual void C_BaseEntity__VPhysicsUpdate(void* IPhysicsObject);
    virtual void C_BaseAnimating__VPhysicsGetObjectList(void** IPhysicsObject, int unk);
    virtual bool C_BaseEntity__VPhysicsIsFlesh(void);
    virtual int sub_32BD9A0() = 0; // Added with TI10
    virtual int sub_35A2D60() = 0; // Added with TI10
    virtual void* C_BaseEntity__GetShadowDrawMaterial(void);
    virtual bool C_BaseEntity__IsAbleToHaveFireEffect(void); // Checks for low violence mode, kek.
    virtual bool C_BaseEntity__IsSelectable(void);
    virtual bool C_BaseEntity__ReceivesMouseoverButNotSelection(void);
    virtual float C_BaseEntity__GetRingRadius(void);
    virtual void sub_2A7EEE0();
    virtual void sub_2A5E4E0();
    virtual void C_BaseFlex__SetupWeights(matrix3x4_t * matrix, int unk, float *unk2, float *unk3);
    virtual void C_BaseEntity__GetVectors(Vector *outForward, Vector *outRight, Vector *outUp);
    virtual const Vector* C_BaseEntity__WorldAlignMins(void);
    virtual const Vector* C_BaseEntity__WorldAlignMaxs(void);
    virtual const Vector* C_BaseEntity__WorldSpaceCenter(void);
    virtual void sub_2A5E2D0();
    virtual void sub_2739BE0();
    virtual void C_BaseEntity__ValidateModelIndex(void);
    virtual void C_BaseCombatCharacter__OnNewParticleEffect(const char* name, void* CNewParticleEffect);
    virtual void C_BaseCombatCharacter__OnParticleEffectDeleted(void *CNewParticleEffect);
    virtual void* C_BaseAnimating__GetMouth(void);
    virtual void C_BaseEntity__OnBoneTransformsChanged(void);
    virtual void C_BaseEntity__ChangeTeam(DOTATeam_t team);
    virtual bool C_BaseEntity__InSameTeam(CBaseEntity *otherEnt); // double edi
    virtual bool C_BaseEntity__InLocalTeam(void);
    virtual bool C_BaseEntity__IsValidIDTarget(void);
    virtual const char* C_BaseEntity__GetIDString(void); // haystack
    virtual bool C_BaseEntity__IsPotentiallyUsable(void);
    virtual int C_BaseEntity__GetUseType(CBaseEntity *ent);
    virtual void* C_BaseModelEntity__GetGlowEntity(void);
    virtual bool C_BaseEntity__IsSaveNonNetworkable(void);
    virtual void sub_2A65970();
    virtual bool C_DOTAPlayer__ShouldDraw(void); // "vr_hmd_tracking_passthrough"
    virtual void C_DOTAPlayer__Simulate(void);
    virtual void sub_2A97C00();
    virtual void sub_2CDAE91();
    virtual void sub_2CDAD10();
    virtual void* C_BaseEntity__GetClientVehicle(void);
    virtual void sub_26F5240();
    virtual void C_BaseEntity__OverrideAlphaModulation(unsigned char alpha);
    virtual void C_BaseEntity__OverrideShadowAlphaModulation(unsigned char alpha);
    virtual void sub_26F5250();
    virtual void loc_2A93EF0();
    virtual void sub_2A7C7A0();
    virtual void C_BaseModelEntity__Clear(void);
    virtual float C_BaseEntity__GetTextureAnimationStartTime(void);
    virtual bool C_BaseEntity__TextureAnimationWrapped(void);
    virtual void loc_2A7A330();
    virtual void C_BaseEntity__OnTakeDamage(void* CTakeDamageInfo);
    virtual void C_BaseEntity__TakeDamage(void* CTakeDamageInfo);
    virtual void sub_26F57E0();
    virtual void sub_2E1E560(); // added with aghanim's labyrinth. xor eax, eax.
    virtual void unk_newFuncHashBucket(); // added with summer scrub pt2 - elf_gnu_hash_bucket
    virtual void sub_2907330();
    virtual void unk_elfshit(); //  rax, qword ptr ds:stru_D90.st_name - added 7-17-19
    virtual void* C_BasePlayer__GetPredictionOwner(void);
    virtual void unk_NewFunc(); // added with summer scrub pt2
    virtual void C_BaseEntity__InitPredictable(void* C_BasePlayer);
    virtual void C_BaseAnimating__SetPredictable(bool predictable);
    virtual int sub_2F50EC0(void); // added with nemestice - returns 1
    virtual void C_BaseEntity__DecalTrace(void* CGameTrace, const char* unk);
    virtual void C_BaseEntity__ImpactTrace(void* CGameTrace, int unk, const char* unk2);
    virtual bool C_DOTAPlayer__ShouldPredict(void);
    virtual void C_BasePlayer__PreRender(int splitScreenSlot);
    virtual const char* C_BaseEntity__GetPlayerName(void); // This function doesn't really do jack
    virtual int C_BaseEntity__GetUsePriority(void* C_BaseEntity); //returns 1
    virtual void C_BaseEntity__EstimateAbsVelocity(Vector &out);
    virtual bool C_BaseEntity__CanBePoweredUp(void);
    virtual void C_BaseEntity__AttemptToPowerup(int unk, float unk2, float unk3, void* C_BaseEntity, void* CDamageModifier);
    virtual void C_BaseEntity__StartTouch(void* C_BaseEntity);
    virtual void C_BaseEntity__Touch(void* C_BaseEntity);
    virtual void C_BaseEntity__EndTouch(void* C_BaseEntity);
    virtual void C_BaseEntity__Think(void);
    virtual void sub_2CCC210();
    virtual void C_BasePlayer__PhysicsSimulate(void);
    virtual void C_BaseEntity__SimulateThinkInternal(void);
    virtual void* C_BaseEntity__ClothGetEntityInstanceSettings(void);
    virtual void C_BaseEntity__NotifySystemEvent(void* C_BaseEntity, int notify_system_event_t, void* notify_system_event_params_t);
    virtual void C_BaseEntity__SUB_Remove(void); // "SUB_Remove"
    virtual void sub_2903930();
    virtual void sub_2F56F60(); // added with dota-anime
    virtual void sub_2F2C540(); // added with dota-anime
    virtual void sub_273A9D0(); // cmp qword ptr [rsi+50h], 0
    virtual void C_BaseEntity__DispatchTraceAttack(void* CTakeDamageInfo, const Vector &direction, void* CGameTrace);
    virtual void C_BaseEntity__TraceAttack(void* CTakeDamageInfo, const Vector &direction, void* CGameTrace);
    virtual bool C_BaseEntity__ShouldDrawWaterImpacts(void);
    virtual bool C_BaseEntity__ShouldDrawUnderwaterBulletBubbles(void);
    virtual ColorRGBA C_BaseCombatCharacter__BloodColor(void);
    virtual bool unk_something_new(void); //added with TI2019 battlepass, setz al // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual bool C_DOTAPlayer__IsPlayer(void); // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual bool C_BaseEntity__IsHMDAvatar(void); // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual void sub_26F5350(); // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual void sub_25DDBB0(); //added with sept 26 dota+ update. // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual bool C_BaseCombatCharacter__IsBaseCombatCharacter(void); // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual void* C_BaseCombatCharacter__MyCombatCharacterPointer(void); // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual void* C_BaseCombatCharacter__MyCombatCharacterPointer2(void); // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual bool C_BaseEntity__IsBaseObject(void); // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual bool C_BaseEntity__IsBaseTrain(void); // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual bool C_BaseEntity__IsNextBot(void); // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual void* C_BaseEntity__MyInfectedPointer(void); // Note: One of these is missing, couldn't tell which one, they all return 0 --- //virtual void* C_BaseEntity__MyInfectedRagdollPointer(void); Removed this one
    virtual bool C_BaseEntity__IsSprite(void); // Note: One of these is missing, couldn't tell which one, they all return 0
    virtual int C_BaseEntity__GetMaxHealth(void);
    virtual void C_BaseEntity__SetHealth(int health);
    virtual int C_BaseEntity__GetHealth(void);
    virtual int C_BaseEntity__GetActualHealth(void);
    virtual void C_BaseEntity__ModifyOrAppendCriteria(void* CResponseCriteriaSet); // "unitname"
    virtual void sub_3310EF0() = 0; // added or moved with TI10
    virtual bool C_BaseEntity__WantSpawnCallOnPreData(void); // 1
    virtual Vector* C_DOTAPlayer__EyePosition(void);
    virtual QAngle* C_DOTAPlayer__EyeAngles(void);
    virtual QAngle* C_BasePlayer__LocalEyeAngles(void);
    virtual Vector* C_BasePlayer__EarPosition(void);
    virtual float C_BaseEntity__GetFriction(void);
    virtual Vector* C_BaseModelEntity__GetViewOffset(void);
    virtual void C_BaseEntity__GetVelocity(Vector *out1, Vector *out2);
    virtual bool C_BaseEntity__IsMoving(void);
    virtual void C_BaseEntity__OnGroundChanged(void* C_BaseEntity, void* C_BaseEntity2);
    virtual void C_BasedEntity__GetGroundVelocityToApply(Vector &out);
    virtual float C_BaseEntity__GetAttackDamageScale(void);
    virtual void C_BaseEntity__InternalSetEffects(int unk);
    virtual bool C_DOTAPlayer__ShouldInterpolate(void);
    virtual void* C_BaseEntity__GetS1Skin(void);
    virtual void sub_2739EE0();
    virtual void sub_2D7A100(); // added with furry hero
    virtual void sub_2D7A110(); // added with furry hero
    virtual void sub_2D7A120(); // added with furry hero
    virtual void C_BaseEntity__AddRagdollToFadeQueue();
    virtual void C_BaseEntity__OnLeftClick(void* C_BasePlayer, bool unk);
    virtual void C_BaseEntity__OnRightClick(void* C_BasePlayer);
    virtual void C_BaseEntity__OnCursorEntered(void);
    virtual void C_BaseEntity__OnCursorExited(void);
    virtual void* C_BaseEntity__GetSelection(void);
    virtual void C_BaseEntity__GenericSelectionGetClickValidBehaviors(void); //0x0FFFFFFFFh
    virtual void sub_2B6C440();
    virtual void sub_2BAEE50(); // added in outlanders update.
    virtual const Vector* C_BaseEntity__GetRenderOrigin(void);
    virtual const QAngle& C_BaseEntity__GetRenderAngles(void);
    virtual Vector C_BaseEntity__GetObserverCamOrigin(void);
    virtual void C_BaseEntity__RenderableToWorldTransform(void);
    virtual void C_BasePlayer__DrawModel(int flags, RenderableInstance_t*);
    virtual void C_BaseEntity__GetRenderBounds(Vector &out1, Vector &out2);
    virtual void C_BaseEntity__GetRenderBoundsWorldSpace(Vector &out1, Vector &out2);
    virtual void sub_2739E80();
    virtual void sub_2739E90();
    virtual void sub_2739F00();
    virtual void sub_2739EA0();
    virtual void sub_2739EB0();
    virtual void sub_2739F30();
    virtual void sub_2739ED0();
    virtual void sub_2B50A80(); //empty func - diretide 2020
    virtual void sub_2739F10();
    virtual void sub_2739F20();
    virtual void C_BaseCombatCharacter__OnNewModel_0();
    virtual void sub_diretide_stinker(); // added w/ diretide 2020
    virtual void sub_diretide_stinker1();// added w/ diretide 2020
    virtual void sub_diretide_stinker2();// added w/ diretide 2020
    virtual void C_BaseModelEntity__GetColorModulation(float *out);
    virtual void C_BaseModelEntity__DamageDecal(int unk, int unk2);
    virtual void sub_26F56F0();
    virtual void sub_26F5700(); // added sept 26 dota+ update -- empty function.
    virtual void sub_30C20C0(); // added with nemestice update.
    virtual void sub_25DDF10(); // "m_vecX" quantizedfloat meme
    virtual bool C_BaseModelEntity__CanBeSeenByTeam(DOTATeam_t team) = 0;
    virtual bool C_BaseModelEntity__IsPartOfFOWSystem(void); // F.O.W. = Fog Of War
    virtual void C_BaseAnimating__SetTransmit(void* CCheckTransmitInfo, bool unk);
    virtual void C_BaseAnimating__GetRenderData(void* unk, int ModelDataCategory_t); // StudioFrameAdvance wrapper
    virtual void C_BaseAnimating__UpdateClientSideAnimation(void);
    virtual void C_BaseAnimating__ComputeClientSideAnimationFlags(void);
    virtual void PlayPlayerFootstep(); // a guess
    virtual void sub_26F57A0();
    virtual void sub_2910170(); // 0x80000000h
    virtual void sub_26F57B0();
    virtual void no_idea_how_this_pad_happened();
    virtual void sub_26F6A90();
    virtual void sub_2902760(); // returns 0
    virtual void sub_26F57C0();
    virtual void sub_2912B60();
    virtual void sub_26F57D0();
    virtual void sub_2902720(); // floater
    virtual void sub_26F5800();
    virtual void sub_2902630(); // mov 3
    virtual void sub_29F9230(); //added w/ new bloom extension 2020
    virtual void sub_29F9500(); //added w/ new bloom extension 2020 cmp byte 2
    virtual void sub_29D23B0(); //added w/ shader update march 3 2020 - test80
    virtual void sub_32BE010(); //added w/ TI10
    virtual void sub_32BE020(); //added w/ TI10
    virtual void sub_32BE030(); //added w/ TI10
    virtual void sub_32BE040(); //added w/ TI10
    virtual void sub_292A800(); //samey
    virtual void sub_292A800_grug();
    virtual void sub_292A800_grug2(); // mouther -5
    virtual void C_BaseAnimating__HandleScriptedAnimEvent(void* animevent_t);
    virtual void C_BaseAnimating__HandleBehaviorAnimEvent(void* animevent_t);
    virtual void C_BaseAnimating__SpeechAnimEvent(const char* unk);
    virtual void unk_animEvent(); // added 7-17-19
    virtual void C_BaseAnimating__ControlMouth(const void* CModel); //"mouth"
    virtual bool C_BaseAnimating__IsViewModelOrAttachment(void);
    virtual void sub_2902780();
    virtual bool C_BaseAnimating__IsClientRagdoll(void);
    virtual void loc_2929160();
    virtual void C_BaseAnimating__CreateClientRagdoll(bool unk); //"client_ragdoll"
    virtual void sub_2A68210();
    virtual void C_BaseAnimating__DispatchMuzzleEffect(const char* effectNameMaybe, bool unk); // "weaponType"
    virtual void C_BaseAnimating__EjectParticleBrass(const char* brassNameMaybe, int unk);
    virtual bool C_BaseAnimating__IsViewModel(void);
    virtual void C_BaseAnimating__FormatViewModelAttachment(int unk, matrix3x4_t &matrix);
    virtual bool C_BaseAnimating__IsMenuModel(void);
    virtual void C_BaseAnimating__ComputeStencilState(void* ShaderStencilState_t);
    virtual bool C_BaseAnimating__WantsInterpolatedVars(void);
    virtual void sub_29025F0();
    virtual void sub_26F5880();
    virtual void sub_26F5890();
    virtual void C_BaseFlex__InitPhonemeMappings(void); //"phonemes"
    virtual void sub_empty(); // empty function added with furry hero
    virtual void C_BaseFlex__OverrideBlinkWeight(float weight);
    virtual void C_BaseFlex__StartSceneEvent();
    virtual void C_BaseFlex__ProcessSequenceSceneEvent();
    virtual void C_BaseFlex__ClearSceneEvent();
};