#include "Netvars.h"

#include "Utils/Logger.h"

void Netvars::DumpNetvars( CSource2Client *client, const char *fileName ) {
    FileHandle_t dumpFile = fs->Open( "dotanetvars.txt", "w", "TMPDIR" );

    if( !dumpFile ){
        return;
    }


    fs->FPrintf(dumpFile, "\n\n***************** Start of Log *****************\n");

    for( ClientClass *classes = client->GetAllClasses(); classes; classes = classes->m_pNext ){
        if( !classes->recvTable || !classes->recvTable->netVarsArray || !classes->m_pClassName )
            continue;

        fs->FPrintf(dumpFile,  "%s - NumOfVars: %d\n", classes->m_pClassName, classes->recvTable->numOfVars );
        for( int i = 0; i < classes->recvTable->numOfVars; i++ ){
            Netvar *var = classes->recvTable->netVarsArray[i].netVar;
            if( !var
                || !var->netvarName
                || !var->typeName )
                break;

            fs->FPrintf(dumpFile,  "\t(%d)%s -> %s @ 0x%x\n", i + 1, var->netvarName, var->typeName, var->offset );
        }
    }

    fs->FPrintf(dumpFile, "\n\n***************** End of Log *****************\n");

    fs->Close( dumpFile );
}

void Netvars::CacheNetvars( CSource2Client *client ) {

    for( ClientClass *classes = client->GetAllClasses(); classes; classes = classes->m_pNext ){
        if( !classes->recvTable || !classes->recvTable->netVarsArray || !classes->m_pClassName )
            continue;

        for( int i = 0; i < classes->recvTable->numOfVars; i++ ){
            Netvar *var = classes->recvTable->netVarsArray[i].netVar;
            if( !var
                || !var->netvarName
                || !var->typeName )
                break;

            netvars[classes->m_pClassName][var->netvarName] = var->offset;
        }
    }

}