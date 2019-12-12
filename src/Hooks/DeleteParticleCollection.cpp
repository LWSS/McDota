#include "Hooks.h"

typedef void ( *DeleteParticleCollectionFn)( CParticleSystemMgr *, CParticleCollection * );

void Hooks::DeleteParticleCollection( CParticleSystemMgr *thisptr, CParticleCollection *collectionToDelete ) {

    {
        const std::lock_guard<std::mutex> lock( CreateParticleCollection::particleRemoveGuard );
        for( size_t i = CreateParticleCollection::particlesTracked.size(); i-- > 0 ; ){
            if( CreateParticleCollection::particlesTracked[i] == collectionToDelete ){
                CreateParticleCollection::particlesTracked.erase( CreateParticleCollection::particlesTracked.begin() + i );
            }
        }
    }

    particleSystemVMT->GetOriginalMethod< DeleteParticleCollectionFn >( 19 )( thisptr, collectionToDelete );
}