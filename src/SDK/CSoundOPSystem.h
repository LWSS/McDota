#pragma once

#include "IAppSystem.h"

typedef void* sound_voice_layer_t;
typedef void* SoundEventGuid_t;


//xref "SoundOpSystem001" to ::QueryInterface() - [libsoundsystem]
// function will be short and only contains a stricmp()
class CSoundOpSystem : IAppSystem
{
public:
    /* This one is for Menu Sounds */
    virtual void StartSoundEvent(const char *, int entIndex, short, void const *, int) = 0;
    virtual void unk() = 0; //added around the time the furry hero came out, maybe earlier. -- I imagine this is just another StartSoundEvent() with different params
    /* This one is for In-Game Sounds */
    //virtual void StartSoundEvent2(unsigned int, int entIndex, sound_voice_layer_t, short, const char *, void const *, int, SoundEventGuid_t) = 0;
    virtual void StartSoundEvent2(void *unkParamStruct) = 0;

    /* This class is Incomplete! This one is a pain */

    //virtual void StopSoundEvent(SoundEventGuid_t) = 0;
    //virtual void StopSoundEvent2(unsigned int, int entIndex) = 0;
    //virtual void StopSoundEvent3(const char*, int entIndex) = 0;
};