#pragma once

#include "CBaseEntity.h"
#include "CBaseCombatCharacter.h"
#include "vector.h"

struct ClientModelRenderInfo_t;
struct animevent_t;

class C_BaseViewModel;
class CModel;

// xref "idle_to_run" to C_DOTA_BaseNPC::OnNewModel()
// 2nd to last function call is CSkeletonInstance::ForceLOD()
// xref it to short function with 4 call's. This is C_DOTAWearableItem::OnNewModel()
class CDOTAWearableItem : CBaseEntity
{
public:
    virtual void C_EconWearable__GiveTo(CBaseEntity *entity) = 0;
    virtual bool C_EconEntity__ShouldShowToolTip(void) = 0;
    virtual void C_EconEntity__InternalDrawModel(int flags, const RenderableInstance_t &) = 0;
    virtual void C_EconEntity__OnInternalDrawModel(ClientModelRenderInfo_t *) = 0;
    virtual void C_EconEntity__OnHandleAnimEvent(C_BaseViewModel *, animevent_t *) = 0;
    virtual void C_EconEntity__UseFlexDelayedWeights(void) = 0;
    virtual bool C_DOTAWearableItem__ShouldDrawParticleSystems(void) = 0;
    virtual bool C_EconEntity__AttachmentModelsShouldBeVisible(void) = 0;
    virtual void sub_36C4FA0() = 0;
    virtual bool C_EconEntity__IsTransparent(void) = 0;
    virtual bool C_EconEntity__IsUsingFBTexture(void) = 0;
    virtual void C_EconEntity__DrawOverriddenViewmodel(C_BaseViewModel *, int) = 0;
    virtual int C_EconEntity__LookupAttachment(const char *) = 0; // check out entity attachments in the visuals section of the cheat
    // These GetAttachment Functions return true if the attachment was found, false if not.
    // Also if not found, it will just set the Vector to the origin or something default.
    virtual bool C_EconEntity__GetAttachment(const char *, Vector &) = 0;
    virtual bool C_EconEntity__GetAttachment(const char *, Vector &, QAngle &) = 0;
    virtual bool C_EconEntity__GetAttachment(int, matrix3x4_t &) = 0;
    virtual bool C_EconEntity__GetAttachment(int, Vector &) = 0;
    virtual bool C_EconEntity__GetAttachment(int, Vector &, QAngle &) = 0;

    virtual void C_EconEntity__GetAttachmentVelocity(int, Vector &, Quaternion &) = 0;
    virtual void C_EconEntity__ViewModelAttachmentBlending(const CModel *, Vector *, Quaternion *, float, int) = 0;
    virtual void C_EconEntity__SetMaterialOverride(const char *) = 0;
    virtual void* C_EconEntity__GetAttributeManager(void) = 0; // these return the same thing
    virtual void* C_EconEntity__GetAttributeContainer(void) = 0; // ^^
    virtual void* C_EconEntity__GetAttributeOwner(void) = 0;
    virtual void* C_EconEntity__GetAttributeList(void) = 0;
    virtual void C_EconEntity__ReapplyProvision(void) = 0;
    virtual void C_EconWearable__UpdateBodyGroups(CBaseCombatCharacter *, int) = 0;
    virtual void C_EconWearable__TranslateViewmodelHandActivityInternal(int) = 0;
    virtual void sub_368A270() = 0;
    virtual bool C_EconWearable__IsWearable(void) = 0;
    virtual void C_EconWearable__RemoveFrom(CBaseEntity *) = 0;
    virtual bool C_EconWearable__CanEquip(CBaseEntity *) = 0;
    virtual void CDOTAWearableItem__Equip(CBaseCombatCharacter *) = 0;
    virtual void CDOTAWearableItem__UnEquip(CBaseCombatCharacter *) = 0;
    virtual void C_EconWearable__OnWearerDeath(void) = 0;
    virtual int C_EconWearable__GetDropType(void) = 0;
    // maybe GetDrawWearable/SetDrawWearable.
    virtual void sub_367E3C0() = 0;
    virtual void sub_36C26A0() = 0;
};