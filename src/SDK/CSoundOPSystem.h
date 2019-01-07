#pragma once

#include "IAppSystem.h"

typedef void* sound_voice_layer_t;
typedef void* SoundEventGuid_t;


class CSoundOpSystem : IAppSystem
{
public:
    /* This one is for Menu Sounds */
    virtual void StartSoundEvent(const char *, int entIndex, short, void const *, int) = 0;
    /* This one is for In-Game Sounds */
    virtual void StartSoundEvent2(unsigned int, int entIndex, sound_voice_layer_t, short, const char *, void const *, int, SoundEventGuid_t) = 0;
    virtual void StopSoundEvent(SoundEventGuid_t) = 0;
    virtual void StopSoundEvent2(unsigned int, int entIndex) = 0;
    virtual void StopSoundEvent3(const char*, int entIndex) = 0;
    /* This class is Incomplete! This one is a pain */
};