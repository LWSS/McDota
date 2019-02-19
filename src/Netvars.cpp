#include "Netvars.h"
#include "Interfaces.h"

#include <cstdio>

void Netvars::DumpNetvars( const char *fileName ) {
    FILE *logFile;
    logFile = fopen(fileName, "a");
    setbuf( logFile, NULL ); // turn off buffered I/O so it writes even if a crash occurs soon after.
    fprintf(logFile, "\n\n***************** Start of Log *****************\n");

    for( ClientClass *classes = client->GetAllClasses(); classes; classes = classes->m_pNext ){
        if( !classes->recvTable || !classes->recvTable->netVarsArray || !classes->m_pClassName )
            continue;

        fprintf( logFile, "%s - NumOfVars: %d\n", classes->m_pClassName, classes->recvTable->numOfVars );
        for( int i = 0; i < classes->recvTable->numOfVars; i++ ){
            Netvar *var = classes->recvTable->netVarsArray[i].netVar;
            if( !var
                || !var->netvarName
                || !var->typeName )
                break;

            fprintf( logFile, "\t(%d)%s -> %s @ 0x%x\n", i + 1, var->netvarName, var->typeName, var->offset );
        }
    }


    fclose(logFile);
}


unsigned int Netvars::GetNetvar( const char *className, const char *netvarName ) {
    ClientClass *targetClass = nullptr;
    for( ClientClass *classes = client->GetAllClasses(); classes; classes = classes->m_pNext ){
        if( !strcmp(classes->m_pClassName, className) ){
            targetClass = classes;
            for( int i = 0; i < classes->recvTable->numOfVars; i++ ){
                Netvar *var = classes->recvTable->netVarsArray[i].netVar;
                if( !var )
                    continue;
                if( !strcmp( var->netvarName, netvarName ) ){
                    return var->offset;
                }
            }
        }
    }
    if( !targetClass ){
        MC_PRINTF_ERROR( "Couldn't Find Netvar Class (%s)\n", className );
        return 0;
    }

    MC_PRINTF_ERROR( "Couldn't Find Netvar(%s) for Class(%s)\n", netvarName, className );
    return 0;
}