#pragma once

#include "Schema.h"

// xref "CParticleCollection::CParticleCollection [%p]" to constructor. (libparticles)
// vtable is first offset in function.

class CParticleControlPoint;

class CParticleCollection
{
public:
    virtual CSchemaClassBinding* Schema_DynamicBinding(void) = 0;
    virtual void* GetOwner(void) = 0;
    virtual void SetAssociatedObj( void * )= 0;
    virtual void* GetAssociatedObj()= 0;
    virtual void SetSomethingElse( void* )= 0;
    virtual void* GetSomethingElse()= 0;
    virtual bool IsValid(void)= 0;
    virtual bool IsFullyValid(void)= 0;
    virtual void* GetDefinition(void)= 0;
    virtual CParticleCollection* GetParentCollection(void) = 0;
    virtual CParticleCollection* GetFirstChildCollection(void) = 0;
    virtual CParticleCollection* GetNextSiblingCollection(void) = 0;
    virtual CParticleCollection* GetNextCollectionUsingSameDef(void) = 0;
    virtual bool UsesPowerOfTwoFrameBufferTexture(bool) = 0;
    virtual void sub_105ED0() = 0;
    virtual void sub_1062B0() = 0;
    virtual void sub_1064A0() = 0; // confirmed void
    virtual void SetOrientationFLU() = 0;
    virtual void sub_105C60() = 0;
    virtual void sub_107C90() = 0;
    virtual void sub_1073F0() = 0;
    virtual Vector* GetControlPointPosition(int index) = 0; // ***think this is it***
    virtual void sub_105861() = 0;
    virtual CParticleControlPoint* GetControlPointObject(int index) = 0;
    virtual void sub_105D00() = 0;
    virtual void sub_105740() = 0;
    virtual void sub_1056B0() = 0;
    virtual void sub_105700() = 0;
    virtual void sub_12DDA0() = 0;
    virtual void FullRestart(void) = 0;
    virtual void Simulate( float dt ) = 0;
    virtual void SleepingSimulate( float dt ) = 0;
    virtual void SkipToTime( float time ) = 0;
    virtual float GetSimulationTime(void) = 0;
    virtual bool IsFinished(void) = 0;
    virtual float GetNextSleepTime(void) = 0;
    virtual void UpdateNextSleepTime(void) = 0;
    virtual void sub_106350() = 0;
    virtual void sub_106390() = 0;
    virtual void sub_106450() = 0;
    virtual void sub_1063D0() = 0;
    virtual void sub_106410() = 0;
    virtual void sub_105F40() = 0;
    virtual void sub_124A80() = 0;
    virtual void sub_1249B0() = 0;
    virtual void sub_126AA0() = 0;
    virtual bool IsBoundsValid(void) = 0;
    virtual Vector* GetMinBounds(void) = 0;
    virtual Vector* GetMaxBounds(void) = 0;
    virtual void sub_105830() = 0;
    virtual void sub_105840() = 0;
    virtual void SetMinBounds(Vector min) = 0;
    virtual void SetMaxBounds(Vector max) = 0;
    virtual void BloatBoundsUsingControlPoint(void) = 0;
    virtual void DrawDebug(void *IRenderContext, void const * CSceneObject, void *ISceneView, void *ISceneLayer, int, int) = 0;
    virtual void StartEmission(bool) = 0;
    virtual void StopEmission(bool, bool, bool, bool) = 0; // first one if false, particles at 0,0,0  -- last one if false, renders them normally
    virtual bool IsEmissionStopped(void) = 0;
    virtual bool IsEmitting(void) = 0;
    virtual float GetMinimumTimeStepModifier(void) = 0;
    virtual void StartQueuedEmission(void) = 0;
    virtual void SetDormant(bool state) = 0;
    virtual bool IsDormant(void) = 0;
    virtual void sub_105950() = 0;
    virtual void sub_105980() = 0;
    virtual void sub_105990() = 0;
    virtual void sub_133E00() = 0;
    virtual void sub_12E910() = 0;
    virtual void sub_12A3E0() = 0;
    virtual void sub_12A420() = 0;
    virtual void SetQueuedStartEmission(bool state) = 0;
    virtual bool GetQueuedStartEmission(void) = 0;
    virtual bool IsFrozen(void) = 0;
    virtual void SetFrozen(bool state) = 0;
    virtual void sub_12FCD0() = 0;
    virtual void sub_130990() = 0;
    virtual void sub_1241D0() = 0;
    virtual void DESTRUCTOR() = 0;
    virtual void DESTRUCTOR_2() = 0;
    virtual void sub_123F70() = 0;
    virtual void sub_105770() = 0;
    virtual void sub_1057A0() = 0;
    virtual void sub_12A290() = 0;
    virtual void SetOwningSceneObject( void *CSceneParticleObject) = 0;
    virtual void* GetOwningSceneObject(void) = 0;
    virtual void SetMaterialOverride() = 0; // (CWeakHandle<InfoForResourceTypeIMaterial2>)
    virtual bool GetRenderingEnabled(void) = 0;
    virtual void SetRenderingEnabled(bool state) = 0;
    virtual bool InEndCap(void) = 0;
    virtual int GetFlags(void) = 0;
    virtual void SetFlags(int ParticleCollectionFlags_t) = 0; // these flags are tricky, no clue what they do except crash ur game and make particles spawn at the origin.
    virtual void RemoveFlags(int ParticleCollectionFlags_t) = 0;
    virtual void GetSecondarySceneObjects() = 0;// (CUtlVector<CSceneObject *,CUtlMemory<CSceneObject *,int>> &)
    virtual bool HasAttribute(int) = 0;
    virtual void SetMinimumTimeStepModifier(float min) = 0;
    virtual void GetPerformanceData(void **ParticleCollectionPerf_t) = 0;
    virtual void OnSleepingStateChanged(bool) = 0;
    virtual void ValidateSystem(bool *, void *CUtlString) = 0;
    virtual int GetSystemParticleCount(void) = 0;
    virtual int GetSystemMaxParticleCount(void) = 0;
    virtual int GetTotalSystemCount(void) = 0;
    virtual void sub_1248F0() = 0;
    virtual void sub_1244B0() = 0;
    virtual void sub_124040() = 0;
    virtual void sub_1056F0() = 0;

    size_t GetHighestControlPoint( void )
    {
        return *(int*)(uintptr_t(this) + 0xEC);
    }
};