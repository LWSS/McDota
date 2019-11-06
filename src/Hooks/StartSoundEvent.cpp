#include "Hooks.h"

#include "../Settings.h"

typedef void (* StartSoundEventFn)( CSoundOpSystem *, const char*, int, short, void const *, int );
typedef void (* StartSoundEvent2Fn)( CSoundOpSystem *, unsigned int, int, sound_voice_layer_t, short, const char *, void const *, int, SoundEventGuid_t ) ;

//"Stinger.MatchReady" not always played.... Depends on gamemode

/* Menu Sounds */
void Hooks::StartSoundEvent( CSoundOpSystem *thisptr, const char *name, int entIndex, short unk, void const *something, int unk2 ) {
    //cvar->ConsoleDPrintf( "Sound played: %s\n", name );
    return soundOpSystemVMT->GetOriginalMethod<StartSoundEventFn>( 11 )( thisptr, name, entIndex, unk, something, unk2 );
}

/* In Game Sounds */
void Hooks::StartSoundEvent2( CSoundOpSystem *thisptr, unsigned int unk, int entIndex, sound_voice_layer_t voiceLayer, short unk2, const char *name, void const *something,
                              int unk3, SoundEventGuid_t guid ) {
    //cvar->ConsoleDPrintf( "Sound2 played: %s\n", name );
    CBaseEntity *entity;
    if( mc_mute_creeps->GetBool() ){
        entity = entitySystem->GetBaseEntity( entIndex );
        if( entity && entity->GetOwnerID() <= 0 ){
            return;
        }
    }
    return soundOpSystemVMT->GetOriginalMethod<StartSoundEvent2Fn>( 12 )( thisptr, unk, entIndex, voiceLayer, unk2, name, something, unk3, guid );
}