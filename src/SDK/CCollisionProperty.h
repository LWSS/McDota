#pragma once
#include "vector.h"
#include "Schema.h"
#include "Datamap.h"
#include "../Utils/Util_sdk.h"

struct RnCollisionAttr_t
{
    int64_t nInteractAs;
    int64_t nInteractsWith;
    int64_t nInteractsExclude;
    int nEntityId;
    short nHierarchyId;
    unsigned char nCollisionGroup;
    unsigned char nCollisionFunctionMask;
};

struct SolidType_t;
struct ChangeAccessorFieldPathIndex_t
{
    short value;
};

class CCollisionProperty
{
public:
    virtual CSchemaClassBinding* Schema_DynamicBinding(void);
    virtual Datamap* GetPredDescMap();


    /* Use CBaseEntity->WorldAlignMins/Maxs Instead of this crap I reversed for no reason */
    inline const Vector * GetMins()
    {
        static int offset = Util::FindDataMapElementOffset( this->GetPredDescMap(), "m_vecMins" );
        if( !offset )
            return nullptr;
        return (const Vector *)((uintptr_t)this + offset);
    }

    inline const Vector * GetMaxs()
    {
        static int offset = Util::FindDataMapElementOffset( this->GetPredDescMap(), "m_vecMaxs" );
        if( !offset )
            return nullptr;
        return (const Vector *)((uintptr_t)this + offset);
    }



    /* This all changed when the valve nation attacked(rubick arcana), only one person, the last dota bender could restore order to CCollisionProperty

    virtual uint64_t GetEntityHandle(void) = 0;
    virtual const Vector& OBBMins(void) = 0;
    virtual const Vector& OBBMaxs(void) = 0;
    virtual void WorldSpaceTriggerBounds(Vector *pVecWorldMins, Vector *pVecWorldMaxs) = 0;
    virtual const Vector& GetCollisionOrigin(void) = 0;
    virtual const QAngle& GetCollisionAngles(void) = 0;
    virtual const matrix3x4_t& CollisionToWorldTransform(void) = 0;
    virtual SolidType_t GetSolid(void) = 0;
    virtual int GetSolidFlags(void) = 0;
    virtual int GetCollisionGroup(void) = 0;
    virtual void WorldSpaceSurroundingBounds(Vector *pVecMins, Vector *pVecMaxs) = 0;
    virtual bool ShouldTouchTrigger(const RnCollisionAttr_t &) = 0;
    virtual void* GetVPhysicsObject(void) = 0;
    virtual void* GetCollisionAttribute(void) = 0;
    virtual bool IsCollisionEnabled(void) = 0;
    virtual void EnableAllCollisions(void) = 0;
    virtual void DisableAllCollisoins(void) = 0;
    virtual void EnableSolidCollisions(void) = 0;
    virtual void DisableSolidCollisions(void) = 0;
    virtual const Vector& OBBCenter(void) = 0;
    virtual void UpdateCollisionAttribute(void) = 0;
    virtual void MarkPartitionHandleDirty(void) = 0;
    virtual bool DoesRotationInvalidateSurroundingBox(void) = 0;
    virtual bool DoesVPhysicsInvalidateSurroundingBox(void) = 0;
    virtual bool DoesSequenceChangeInvalidateSurroundingBox(void) = 0;
    virtual void MarkSurroundingBoundsDirty(void) = 0;
    virtual void SetSolid(SolidType_t) = 0;
    virtual void sub_2DF1510() = 0;
    virtual CSchemaClassBinding* Schema_DynamicBinding() = 0;
    virtual void* GetPredDescMap(void) = 0;
    virtual void NetworkStateChanged(void) = 0;
    virtual void NetworkStateChanged2(unsigned int, int, ChangeAccessorFieldPathIndex_t) = 0;
    virtual void sub_2BE1070() = 0; // UseTriggerBounds?
     */
};