#include "Netvars.h"
#include "Interfaces.h"

#include <cstdio>
#include <sys/stat.h>

void Netvars::DumpNetvars( const char *fileName ) {
    FILE *logFile;
    struct stat buffer;

    // already exists? skip
    if( stat( fileName, &buffer ) == 0 ) {
        return;
    }

    logFile = fopen(fileName, "a");
    setbuf( logFile, nullptr ); // turn off buffered I/O so it writes even if a crash occurs soon after.
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

void Netvars::CacheNetvars( ) {

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