#pragma once

#include "Schema.h"
#include "vector.h"
#include "ICvar.h"
#include "CCollisionProperty.h"
#include "Datamap.h"
#include "../Utils/Util.h"


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

class CBaseEntity
{
public:
    inline const DOTATeam_t GetTeam( )
    {
        static int offset = Util::FindDataMapElementOffset( this->C_DOTAPlayer__GetPredDescMap(), "m_iTeamNum" );
        if( !offset ){
            Util::Log("ERROR GetTeam offset is Zero!\n");
            return DOTA_TEAM_INVALID;
        }
        return *( DOTATeam_t* )( ((uintptr_t)this) + offset );
    }
    inline QAngle* const GetNetworkAngles( )
    {
        static int offset = Util::FindDataMapElementOffset( this->C_DOTAPlayer__GetPredDescMap(), "m_angNetworkAngles" );
        if( !offset ){
            Util::Log("ERROR NetworkAngles offset is Zero!\n");
            return NULL;
        }
        return ( QAngle* )( ((uintptr_t)this) + offset );
    }
    inline Vector* const GetNetworkOrigin( )
    {
        static int offset = Util::FindDataMapElementOffset( this->C_DOTAPlayer__GetPredDescMap(), "m_vecNetworkOrigin" );
        if( !offset ){
            Util::Log("ERROR NetworkOrigin offset is Zero!\n");
            return NULL;
        }
        return ( Vector* )( ((uintptr_t)this) + offset );
    }
    inline const int GetOwnerID( )
    {
        static int offset = Util::FindDataMapElementOffset( this->C_DOTAPlayer__GetPredDescMap(), "m_hOwnerEntity" );
        if( !offset ){
            Util::Log("ERROR OwnerEntity offset is Zero!\n");
            return -1;
        }
        int *ptr = ( int* )( ((uintptr_t)this) + offset );
        if( ptr[0] < 0 ){
            return -1;
        }
        return ptr[0] & 0xFFF;
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
    virtual void C_BaseAnimating__OnSetDormant(void);
    virtual void C_BasePlayer__PreDataUpdate(int DataUpdateType_t);
    virtual void C_BaseEntity__DrawEntityDebugOverlays(OverlayFlags_t flags);
    virtual void C_BaseEntity__Save( void* ISave );
    virtual void C_BaseEntity__Restore( void* IRestore );
    virtual void C_BaseEntity__OnSave(void);
    virtual void C_BasePlayer__OnRestore(void);
    virtual void C_BaseEntity__ObjectCaps(void);
    virtual int CEntityInstance__RequiredEdictIndex(void);
    virtual void C_BaseEntity__NetworkStateChanged(void);
    virtual void C_BaseEntity__NetworkStateChanged2(unsigned int unk, int unk2, int ChangeAccessorFieldPathIndex_t);
    virtual void sub_273BE20();
    virtual void CEntityInstance__AddChangeAccessorPath(void* CFieldPath);
    virtual void CEntityInstance__ReloadPrivateScripts(void);
    virtual void sub_26F4ED0();
    virtual void sub_26F4EE0();
    virtual void* C_BaseAnimating__GetDataDescMap(void); // C_BaseAnimatingOverlay::m_DataMap
    virtual Datamap* C_DOTAPlayer__GetPredDescMap(void);
    virtual CCollisionProperty* C_BaseModelEntity__GetCollideable(void);
    virtual void* C_BaseEntity__GetPredictionCopyable(void);
    virtual void YouForgotToImplementOrDeclareClientClass();
    virtual ClientClass* C_DOTAPlayer__GetClientClass(void);
    virtual void C_BaseModelEntity__SpawnShared(void* CEntityKeyValues);
    virtual void C_BaseModelEntity__PopulatePoseParameters(void);
    virtual void C_BasePlayer__PreFirstNetworkUpdate(void);
    virtual void* C_BaseModelEntity__GetBaseModelEntity(void);
    virtual void* C_BaseModelEntity__GetBaseModelEntity2(void);
    virtual void* C_BaseAnimating__GetBaseAnimating(void);
    virtual void* C_BaseAnimating__GetBaseAnimating2(void);
    virtual void sub_285FB30();
    virtual void sub_285FB40();
    virtual bool C_BasePlayer__Classify(void);
    virtual void C_BaseEntity__ModifyEconParticles(int unk);
    virtual bool C_BaseEntity__ShouldSavePhysics(void);
    virtual bool C_BaseEntity__CreateVPhysics(void);
    virtual void C_BaseAnimating__DrawVCollide(void);
    virtual void C_BaseEntity__VPhysicsDestroyObject(void);
    virtual void C_BaseEntity__VPhysicsUpdate(void* IPhysicsObject);
    virtual void C_BaseAnimating__VPhysicsGetObjectList(void** IPhysicsObject, int unk);
    virtual bool C_BaseEntity__VPhysicsIsFlesh(void);
    virtual void* C_BaseEntity__GetShadowDrawMaterial(void);
    virtual bool C_BaseEntity__IsAbleToHaveFireEffect(void); // Checks for low violence mode, kek.
    virtual bool C_BaseEntity__IsSelectable(void);
    virtual bool C_BaseEntity__ReceivesMouseoverButNotSelection(void);
    virtual float C_BaseEntity__GetRingRadius(void);
    virtual void sub_2A7EEE0();
    virtual void sub_2A5E4E0();
    virtual void C_BaseFlex__SetupWeights(matrix3x4_t * matrix, int unk, float *unk2, float *unk3);
    virtual void C_BaseEntity__GetVectors(Vector *outForward, Vector *outRight, Vector *outUp);
    virtual const Vector* const C_BaseEntity__WorldAlignMins(void);
    virtual const Vector* const C_BaseEntity__WorldAlignMaxs(void);
    virtual const Vector* const C_BaseEntity__WorldSpaceCenter(void);
    virtual void sub_2A5E2D0();
    virtual void sub_2739BE0();
    virtual void C_BaseEntity__ValidateModelIndex(void);
    virtual void C_BaseEntity__AsParticleEHandle(void);
    virtual void C_BaseCombatCharacter__OnNewParticleEffect(const char* name, void* CNewParticleEffect);
    virtual void C_BaseCombatCharacter__OnParticleEffectDeleted(void *CNewParticleEffect);
    virtual void C_BaseEntity__PredCopy_SetHeapSize(int);
    virtual void* C_BaseEntity__PredCopy_GetStructBase(void);
    virtual int C_BaseEntity__PredCopy_GetOffsetType(void);
    virtual void C_BaseEntity__PredCopy_SetCommand(int);
    virtual void* C_BaseEntity__PredCopy_GetCommand(void);
    virtual void C_BaseEntity__PredCopy_Alloc(unsigned int unk, void* datamap_t, bool unk2);
    virtual void C_BaseEntity__PredCopy_Tell(void);
    virtual void C_BaseEntity__PredCopy_GetHeaderBlock(void* CFieldPath, unsigned int unk);
    virtual void* C_BaseAnimating__GetMouth(void);
    virtual void C_BaseEntity__GetSoundSpatialization(void* SpatializationInfo_t);
    virtual int C_BaseAnimating__LookupAttachment(const char* name);
    virtual bool C_BaseAnimating__GetAttachment(unsigned char, matrix3x4_t &);
    virtual void C_BaseEntity__InvalidateAttachments(void);
    virtual void C_BaseEntity__OnBoneTransformsChanged(void);
    virtual void C_BaseEntity__ChangeTeam(DOTATeam_t team);
    virtual bool C_BaseEntity__InSameTeam(CBaseEntity *otherEnt);
    virtual bool C_BaseEntity__InLocalTeam(void);
    virtual void C_BaseAnimating__DrawDebugTextOverlays(unsigned long long unk, int unk2);
    virtual bool C_BaseEntity__IsValidIDTarget(void);
    virtual const char* C_BaseEntity__GetIDString(void);
    virtual bool C_BaseEntity__IsPotentiallyUsable(void);
    virtual const char* C_BaseEntity__GetUseString(CBaseEntity *ent);
    virtual bool C_BaseEntity__IsAbleToGlow(void);
    virtual int C_BaseEntity__GetUseType(CBaseEntity *ent);
    virtual void* C_BaseModelEntity__GetGlowEntity(void);
    virtual bool C_BaseEntity__IsSaveNonNetworkable(void);
    virtual void sub_2A65970();
    virtual bool C_DOTAPlayer__ShouldDraw(void);
    virtual void C_DOTAPlayer__Simulate(void);
    virtual void sub_2A97C00();
    virtual void sub_2CDAE90();
    virtual void sub_2CDAD10();
    virtual void* C_BaseEntity__GetClientVehicle(void);
    virtual void sub_26F5240();
    virtual void C_BaseEntity__OverrideAlphaModulation(unsigned char alpha);
    virtual void C_BaseEntity__OverrideShadowAlphaModulation(unsigned char alpha);
    virtual void sub_26F5250();
    virtual void loc_2A93EF0();
    virtual void sub_2A7C7A0();
    virtual void C_BaseModelEntity__Clear(void);
    virtual long C_BaseEntity__GetTextureAnimationStartTime(void);
    virtual bool C_BaseEntity__TextureAnimationWrapped(void);
    virtual int C_BasePlayer__ShadowCastType(void);
    virtual bool C_BasePlayer__ShouldReceiveProjectedTextures(int unk);
    virtual void* sub_2A95330(); // added dec 7th 2018, returns pointer most likely
    virtual void loc_2A7A330();
    virtual void C_BaseEntity__OnTakeDamage(void* CTakeDamageInfo);
    virtual void C_BaseEntity__TakeDamage(void* CTakeDamageInfo);
    virtual void sub_26F57E0();
    virtual void sub_2937C60();
    virtual int C_BaseEntity__ClothSettingsTypeID(); // a guess
    virtual void sub_2907330();
    virtual void* C_BasePlayer__GetPredictionOwner(void);
    virtual void C_BaseEntity__InitPredictable(void* C_BasePlayer);
    virtual void C_BaseAnimating__SetPredictable(bool predictable);
    virtual void C_BaseEntity__DecalTrace(void* CGameTrace, const char* unk);
    virtual void C_BaseEntity__ImpactTrace(void* CGameTrace, int unk, const char* unk2);
    virtual bool C_DOTAPlayer__ShouldPredict(void);
    virtual void C_BasePlayer__PreRender(int splitScreenSlot);
    virtual const char* C_BaseEntity__GetPlayerName(void); // This function doesn't really do jack
    virtual int C_BaseEntity__GetUsePriority(void* C_BaseEntity);
    virtual void C_BaseEntity__EstimateAbsVelocity(Vector &out);
    virtual bool C_BaseEntity__CanBePoweredUp(void);
    virtual void C_BaseEntity__AttemptToPowerup(int unk, float unk2, float unk3, void* C_BaseEntity, void* CDamageModifier);
    virtual void C_BaseEntity__StartTouch(void* C_BaseEntity);
    virtual void C_BaseEntity__Touch(void* C_BaseEntity);
    virtual void C_BaseEntity__EndTouch(void* C_BaseEntity);
    virtual void C_BaseEntity__Think(void);
    virtual void sub_2CCC210();
    virtual void C_BasePlayer__PhysicsSimulate(void);
    virtual void qword_2B708B0();
    virtual void C_BasePlayer__PhysicsSolidMaskForEntity(void);
    virtual void* C_BaseEntity__ClothGetEntityInstanceSettings(void);
    virtual void C_BaseEntity__NotifySystemEvent(void* C_BaseEntity, int notify_system_event_t, void* notify_system_event_params_t);
    virtual void C_BaseEntity__SUB_Remove(void);
    virtual void sub_2903930();
    virtual void sub_275B090();
    virtual void sub_273A9D0();
    virtual void sub_2A60550();
    virtual void* C_BaseEntity__GetTracerAttachment(void);
    virtual int C_BasePlayer__GetTracerType(void);
    virtual void* C_BaseEntity__GetBeamTraceFilter(void);
    virtual void C_BaseEntity__DispatchTraceAttack(void* CTakeDamageInfo, const Vector &direction, void* CGameTrace);
    virtual void C_BaseEntity__TraceAttack(void* CTakeDamageInfo, const Vector &direction, void* CGameTrace);
    virtual void sub_273C020();
    virtual bool C_BaseEntity__ShouldDrawWaterImpacts(void);
    virtual bool C_BaseEntity__ShouldDrawUnderwaterBulletBubbles(void);
    virtual void sub_273F850();
    virtual ColorRGBA C_BaseCombatCharacter__BloodColor(void);
    virtual bool C_DOTAPlayer__IsPlayer(void);
    virtual bool C_BaseEntity__IsHMDAvatar(void);
    virtual void sub_26F5350();
    virtual bool C_BaseCombatCharacter__IsBaseCombatCharacter(void);
    virtual void* C_BaseCombatCharacter__MyCombatCharacterPointer(void);
    virtual void* C_BaseCombatCharacter__MyCombatCharacterPointer2(void);
    virtual bool C_BaseEntity__IsBaseCombatWeapon(void);
    virtual void* C_BaseEntity__MyCombatWeaponPointer(void);
    virtual bool C_BaseEntity__IsBaseObject(void);
    virtual bool C_BaseEntity__IsBaseTrain(void);
    virtual bool C_BaseEntity__IsNextBot(void);
    virtual void* C_BaseEntity__MyInfectedPointer(void);
    virtual void* C_BaseEntity__MyInfectedRagdollPointer(void);
    virtual bool C_BaseEntity__IsSprite(void);
    virtual int C_BaseEntity__GetMaxHealth(void);
    virtual void C_BaseEntity__SetHealth(int health);
    virtual int C_BaseEntity__GetHealth(void);
    virtual int C_BaseEntity__GetActualHealth(void);
    virtual void C_BaseEntity__ModifyOrAppendCriteria(void* CResponseCriteriaSet);
    virtual bool C_BaseEntity__WantSpawnCallOnPreData(void);
    virtual Vector* C_DOTAPlayer__EyePosition(void);
    virtual QAngle* C_DOTAPlayer__EyeAngles(void);
    virtual QAngle* C_BasePlayer__LocalEyeAngles(void);
    virtual Vector* C_BasePlayer__EarPosition(void);
    virtual float C_BaseEntity__GetFriction(void);
    virtual Vector* C_BaseModelEntity__GetViewOffset(void);
    virtual float C_BaseEntity__GetSmoothedVelocity(void);
    virtual void C_BaseEntity__GetVelocity(Vector *out1, Vector *out2);
    virtual bool C_BaseEntity__IsMoving(void);
    virtual void C_BaseEntity__OnGroundChanged(void* C_BaseEntity, void* C_BaseEntity2);
    virtual void C_BasedEntity__GetGroundVelocityToApply(Vector &out);
    virtual float C_BaseEntity__GetAttackDamageScale(void);
    virtual void C_BaseEntity__InternalSetEffects(int unk);
    virtual bool C_DOTAPlayer__ShouldInterpolate(void);
    virtual void* C_BaseEntity__GetS1Skin(void);
    virtual void C_BaseEntity__BoneMergeFastCullBloat();
    virtual void sub_2739EE0();
    virtual void sub_2739EF0();
    virtual void C_BaseEntity__AddRagdollToFadeQueue();
    virtual void C_BaseEntity__OnLeftClick(void* C_BasePlayer, bool unk);
    virtual void C_BaseEntity__OnRightClick(void* C_BasePlayer);
    virtual void C_BaseEntity__OnCursorEntered(void);
    virtual void C_BaseEntity__OnCursorExited(void);
    virtual void* C_BaseEntity__GetSelection(void);
    virtual void C_BaseEntity__GenericSelectionGetClickValidBehaviors(void);
    virtual void sub_2B6C440();
    virtual const Vector* C_BaseEntity__GetRenderOrigin(void);
    virtual const QAngle& C_BaseEntity__GetRenderAngles(void);
    virtual Vector C_BaseEntity__GetObserverCamOrigin(void);
    virtual void C_BaseEntity__RenderableToWorldTransform(void);
    virtual void C_BasePlayer__DrawModel(int unk, void* RenderableInstance_t);
    virtual void sub_2919540();
    virtual void C_BaseEntity__GetRenderBoundsWorldSpace(Vector &out1, Vector &out2);
    virtual void sub_2739E80();
    virtual void sub_2739E90();
    virtual void sub_2739F00();
    virtual void sub_2739EA0();
    virtual void sub_2739EB0();
    virtual void sub_2739EC0();
    virtual void sub_2739F30();
    virtual void sub_2739ED0();
    virtual void sub_2739F10();
    virtual void sub_2739F20();
    virtual void C_BaseCombatCharacter__OnNewModel_0();
    virtual void C_BaseModelEntity__GetColorModulation(float *out);
    virtual float C_BaseAnimating__GetGlobalFadeScale(void);
    virtual void C_BaseModelEntity__DamageDecal(int unk, int unk2);
    virtual void sub_26F56F0();
    virtual void sub_26F5700();
    virtual void sub_26FF8D0();
    virtual bool C_BaseModelEntity__CanBeSeenByTeam(DOTATeam_t team) = 0;
    virtual bool C_BaseModelEntity__IsPartOfFOWSystem(void); // F.O.W. = Fog Of War
    virtual void C_BaseAnimating__SetTransmit(void* CCheckTransmitInfo, bool unk);
    virtual void C_BaseAnimating__GetRenderData(void* unk, int ModelDataCategory_t);
    virtual void C_BaseAnimating__UpdateClientSideAnimation(void);
    virtual void C_BaseAnimating__ComputeClientSideAnimationFlags(void);
    virtual void PlayPlayerFootstep(); // a guess
    virtual void sub_29027A0();
    virtual void sub_26F57A0();
    virtual void sub_29032A0();
    virtual void sub_2910170();
    virtual void sub_26F57B0();
    virtual void sub_26F6A90();
    virtual void sub_26F57C0();
    virtual void sub_2912B60();
    virtual void sub_26F57D0();
    virtual void sub_2902720();
    virtual void sub_2902760();
    virtual void sub_26F57F0();
    virtual void sub_26F5800();
    virtual void sub_2902630();
    virtual void sub_292A800();
    virtual void sub_292A801();
    virtual void C_BaseAnimating__HandleScriptedAnimEvent(void* animevent_t);
    virtual void C_BaseAnimating__HandleBehaviorAnimEvent(void* animevent_t);
    virtual void C_BaseAnimating__SpeechAnimEvent(const char* unk);
    virtual void C_BaseAnimating__ControlMouth(const void* CModel);
    virtual bool C_BaseAnimating__IsViewModelOrAttachment(void);
    virtual void sub_2902780();
    virtual bool C_BaseAnimating__IsClientRagdoll(void);
    virtual void loc_2929160();
    virtual void C_BaseAnimating__CreateClientRagdoll(bool unk);
    virtual void sub_2A68210();
    virtual void sub_26F5850();
    virtual void C_BaseAnimating__DispatchMuzzleEffect(const char* effectNameMaybe, bool unk);
    virtual void C_BaseAnimating__EjectParticleBrass(const char* brassNameMaybe, int unk);
    virtual void sub_2A82700();
    virtual void sub_290EAC0();
    virtual bool C_BaseAnimating__IsViewModel(void);
    virtual void C_BaseAnimating__FormatViewModelAttachment(int unk, matrix3x4_t &matrix);
    virtual bool C_BaseAnimating__IsMenuModel(void);
    virtual void C_BaseAnimating__ComputeStencilState(void* ShaderStencilState_t);
    virtual bool C_BaseAnimating__WantsInterpolatedVars(void);
    virtual void sub_29025F0();
    virtual void C_BasePlayer__FootstepSound();
    virtual void sub_26F5880();
    virtual void sub_26F5890();
    virtual void C_BaseFlex__InitPhonemeMappings(void);
    virtual void C_BaseFlex__OwnsChoreoScene(void* CChoreoScene);
    virtual void C_BaseFlex__OverrideBlinkWeight(float weight);
    virtual void C_BaseFlex__StartSceneEvent();
    virtual void C_BaseFlex__ProcessSequenceSceneEvent();
    virtual void C_BaseFlex__ClearSceneEvent();
    virtual void C_BaseFlex__CheckSceneEventCompletion();
    virtual void C_BaseFlex__ShouldProcessSceneEvents();
};