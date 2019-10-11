#pragma once

#include "vector.h"

static const int debugBinsDelta = -16;
// xref "camera_dota_default" to sub_I__unity_dota_05. go into function below string. it should have operator new.
// go into the function it calls, then vtable will be first offset address.
class CDotaCamera
{
public:
    virtual void DESTROY(void) = 0;
    virtual void DESTROY2(void) = 0;
    virtual void Init(void) = 0;
    virtual void PreThink(void) = 0;
    virtual void Think(void) = 0;
    virtual void PostThink(void) = 0;
    virtual void AddObserver(void *ICameraObserver) = 0;
    virtual void OnTransitionIn(void const *ICamera) = 0;
    virtual void OnTransitionOut(void) = 0;
    virtual void OnDemoSkip(void *IGameEvent) = 0;
    virtual void OnMouseWheeled(int) = 0;
    virtual void SetForwardMove(float value) = 0; // for moving camera
    virtual void SetSideMove(float value) = 0; // ^^
    virtual Vector* GetPosition(void) = 0; // 13
    virtual void* UnkPosition() = 0; // Calls GetPosition() - Added sometime in mid 2019
    virtual QAngle* GetAngles(void) = 0;
    virtual float GetFOV(void) = 0;
    virtual Vector GetEyeVector(void) = 0; // 17
    virtual float GetFogStart(float) = 0;
    virtual float GetFogEnd(float) = 0;
    virtual float GetZFar(float) = 0;
    virtual float GetZNear(float) = 0;
    virtual bool ShouldHideCursor(void) = 0;
    virtual void SetLODOverride(int) = 0;
    virtual int GetLODOverride(void) = 0;
    virtual float GetShadowDepthBiasOverrideFadeAmount(void) = 0;
    virtual float GetFOWAmount(void) = 0;
    virtual bool ShouldAllowUnitSelectionOnMouseDown(void) = 0;
    virtual bool ShouldAllowUnitSelectionOnMouseRelease(void) = 0;
    virtual bool ShouldSuppressGlows(void) = 0;
    virtual bool ShouldHideHealthBars(void) = 0; // 30
    virtual void sub_2FDFEB0() = 0;
    virtual void sub_2DB7F30() = 0;
    virtual void sub_2DB7F40() = 0;
    virtual void sub_2DB7F50() = 0;
    virtual void sub_2FDFE70() = 0;
    virtual void sub_2DB7F70() = 0;
    virtual void sub_2DB7F80() = 0;
    virtual void sub_2DB7F90() = 0;
    virtual void sub_2DB7FA0() = 0;
    virtual void sub_2DB7FB0() = 0; // 40
    virtual void sub_28F7270() = 0;
    virtual void sub_28F7290() = 0;
    virtual void sub_28F72A0() = 0;
    virtual void sub_28F72B0() = 0;
    virtual void sub_28F72C0() = 0;
    virtual void sub_28F72D0() = 0;
    virtual void sub_28F72E0() = 0;
    virtual void sub_28F72F0() = 0;
    virtual void sub_28F7300() = 0;
    virtual void sub_28F7170() = 0;
    virtual float GetTime(void) = 0; // 51


    // Xref "SetCameraYaw", CDOTA_PanoramaScript_GameUI::SetCameraYaw() will be right above it
    // Function jmp'd at the end.
    void SetExtraYaw( float amount )
    {
        auto *extraYaw = (float*)((uintptr_t)this + 0x264);
        *extraYaw = amount;
    }

    void SetMinPitch( float amount )
    {
        auto *minPitch = (float*)((uintptr_t)this + 0x260);
        *minPitch = amount;
    }

    void SetMaxPitch( float amount )
    {
        auto *maxPitch = (float*)((uintptr_t)this + 0x25C);
        *maxPitch = amount;
    }

    float GetMinPitch( )
    {
        auto *minPitch = (float*)((uintptr_t)this + 0x260);
        return *minPitch;
    }

    float GetMaxPitch( )
    {
        auto *maxPitch = (float*)((uintptr_t)this + 0x25C);
        return *maxPitch;
    }

    void SetDistanceToLookAtPos( float dist )
    {
        auto *distance = (float*)((uintptr_t)this + 0x268);
        *distance = dist;
    }

    const Vector *GetLookAtPos( void )
    {
        auto *lookAtPos = (const Vector*)((uintptr_t)this + 0x270);
        return lookAtPos;
    }

    void SetLookAtPos( Vector &input )
    {
        auto *lookatPos = (Vector*)((uintptr_t)this + 0x270);
        *lookatPos = input;
    }

    void SetFOWAmount( float amount )
    {
        auto *fowAmount = (float*)((uintptr_t)this + 0x60);
        *fowAmount = amount;
    }
};


typedef CDotaCamera* (* GetCameraFn)( void );

inline GetCameraFn GetCurrentCamera;