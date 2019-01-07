#pragma once

#include "vector.h"

static const int debugBinsDelta = -16;
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
    virtual Vector* GetPosition(void) = 0;
    virtual QAngle* GetAngles(void) = 0;
    virtual float GetFOV(void) = 0;
    virtual Vector& GetEyeVector(void) = 0;
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
    virtual bool ShouldHideHealthBars(void) = 0;
    virtual void sub_2FDFEB0() = 0;
    virtual void sub_2DB7F30() = 0;
    virtual void sub_2DB7F40() = 0;
    virtual void sub_2DB7F50() = 0;
    virtual void sub_2FDFE70() = 0;
    virtual void sub_2DB7F70() = 0;
    virtual void sub_2DB7F80() = 0;
    virtual void sub_2DB7F90() = 0;
    virtual void sub_2DB7FA0() = 0;
    virtual void sub_2DB7FB0() = 0;
    virtual float GetTime(void) = 0;


    /* Xref "SetCameraYaw", CDOTA_PanoramaScript_GameUI::SetCameraYaw() will be right above it */
    void SetExtraYaw( float amount )
    {
        float *extraYaw = (float*)((uintptr_t)this + (0x264 + debugBinsDelta));
        *extraYaw = amount;
    }

    void SetMinPitch( float amount )
    {
        float *minPitch = (float*)((uintptr_t)this + (0x260 + debugBinsDelta));
        *minPitch = amount;
    }

    void SetMaxPitch( float amount )
    {
        float *maxPitch = (float*)((uintptr_t)this + (0x25C + debugBinsDelta));
        *maxPitch = amount;
    }

    float GetMinPitch( )
    {
        float *minPitch = (float*)((uintptr_t)this + (0x260 + debugBinsDelta));
        return *minPitch;
    }

    float GetMaxPitch( )
    {
        float *maxPitch = (float*)((uintptr_t)this + (0x25C + debugBinsDelta));
        return *maxPitch;
    }

    void SetDistanceToLookAtPos( float dist )
    {
        float *distance = (float*)((uintptr_t)this + (0x268 + debugBinsDelta));
        *distance = dist;
    }

    void SetFOWAmount( float amount )
    {
        float *fowAmount = (float*)((uintptr_t)this + 0x60);
        *fowAmount = amount;
    }
};


typedef CDotaCamera* (* GetCameraFn)( void );

inline GetCameraFn GetCurrentCamera;