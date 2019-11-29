#include "Hooks.h"

#include "../Utils/Util_sdk.h"

#include <csignal>

typedef CParticleCollection* ( *CreateParticleCollectionFn)( CParticleSystemMgr *, CWeakHandle_InfoForResourceTypeIParticleSystemDefinition *, void *, IParticleSystemQuery *, bool, float, int );

CParticleCollection* Hooks::CreateParticleCollection( CParticleSystemMgr *thisptr, CWeakHandle_InfoForResourceTypeIParticleSystemDefinition *info, void *unk, IParticleSystemQuery *query, bool bUnk, float fUnk, int iUnk ) {
    CParticleCollection *ret = particleSystemVMT->GetOriginalMethod<CreateParticleCollectionFn>( 18 )( thisptr, info, unk, query, bUnk, fUnk, iUnk );

    /*
    Util::Log("CreateParticleCollection called - name(%s) -info(%p) - unk(%p) - query(%p) - bool(%s) - float(%f) - int(%d) - ret(%p)\n",
              info->contents->info->name, (void*)info, unk, (void*)query, bUnk ? "true" : "false", fUnk, iUnk, ret);
    std::raise(SIGINT); */

    /*
    if( !strcmp( info->contents->info->name, "particles/units/heroes/hero_tinker/tinker_machine.vpcf" ) ){
        //ret->SetRenderingEnabled( false );
        ret->SetDormant( true );
    }*/

    for ( size_t i = 0; i < Util::blacklistedParticles.size(); i++ ){
        if( !strcmp( Util::blacklistedParticles[i].c_str(), info->contents->info->name ) ){
            ret->SetDormant( true );
            return ret;
        }
    }

    for ( size_t i = 0; i < Util::trackedParticles.size(); i++ ){
        if( !strcmp( Util::trackedParticles[i].c_str(), info->contents->info->name ) ){
            CreateParticleCollection::particlesTracked.push_back( ret );
        }
    }

    return ret;
}