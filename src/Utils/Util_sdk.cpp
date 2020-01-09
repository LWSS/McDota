#include "Util_sdk.h"
#include "Util.h"

#include "../Interfaces.h"

#include <sys/stat.h>

ButtonCode_t Util::GetButtonCode(const char* buttonName)
{
	for (int i = 0; i < ButtonCode_t::LAST_KEY_VALUE; i++)
	{
		const char* currentButton = inputSystem->CodeToString((ButtonCode_t) i);
		if (strcmp(currentButton, buttonName) == 0)
			return (ButtonCode_t) i;
	}

	return ButtonCode_t::BUTTON_CODE_INVALID;
}


static const char* DataFieldType2String( fieldtype_t type )
{
    switch( (int)type )
    {
        CASE_STRING(FIELD_VOID);
        CASE_STRING(FIELD_FLOAT);
        CASE_STRING(FIELD_STRING);
        CASE_STRING(FIELD_VECTOR);
        CASE_STRING(FIELD_QUATERNION);
        CASE_STRING(FIELD_INTEGER);
        CASE_STRING(FIELD_BOOLEAN);
        CASE_STRING(FIELD_SHORT);
        CASE_STRING(FIELD_CHARACTER);
        CASE_STRING(FIELD_COLOR32);
        CASE_STRING(FIELD_EMBEDDED);
        CASE_STRING(FIELD_CUSTOM);
        CASE_STRING(FIELD_CLASSPTR);
        CASE_STRING(FIELD_EHANDLE);
        CASE_STRING(FIELD_POSITION_VECTOR);
        CASE_STRING(FIELD_TIME);
        CASE_STRING(FIELD_TICK);
        CASE_STRING(FIELD_SOUNDNAME);
        CASE_STRING(FIELD_INPUT);
        CASE_STRING(FIELD_FUNCTION);
        CASE_STRING(FIELD_VMATRIX);
        CASE_STRING(FIELD_VMATRIX_WORLDSPACE);
        CASE_STRING(FIELD_MATRIX3X4_WORLDSPACE);
        CASE_STRING(FIELD_INTERVAL);
        CASE_STRING(FIELD_UNUSED);
        CASE_STRING(FIELD_VECTOR2D);
        CASE_STRING(FIELD_INTEGER64);
        CASE_STRING(FIELD_VECTOR4D);
        CASE_STRING(FIELD_RESOURCE);
        CASE_STRING(FIELD_TYPEUNKNOWN);
        CASE_STRING(FIELD_CSTRING);
        CASE_STRING(FIELD_HSCRIPT);
        CASE_STRING(FIELD_VARIANT);
        CASE_STRING(FIELD_UINT64);
        CASE_STRING(FIELD_FLOAT64);
        CASE_STRING(FIELD_POSITIVEINTEGER_OR_NULL);
        CASE_STRING(FIELD_HSCRIPT_NEW_INSTANCE);
        CASE_STRING(FIELD_UINT);
        CASE_STRING(FIELD_UTLSTRINGTOKEN);
        CASE_STRING(FIELD_QANGLE);
        CASE_STRING(FIELD_NETWORK_ORIGIN_CELL_QUANTIZED_VECTOR);
        CASE_STRING(FIELD_HMATERIAL);
        CASE_STRING(FIELD_HMODEL);
        CASE_STRING(FIELD_NETWORK_QUANTIZED_VECTOR);
        CASE_STRING(FIELD_NETWORK_QUANTIZED_FLOAT);
        CASE_STRING(FIELD_DIRECTION_VECTOR_WORLDSPACE);
        CASE_STRING(FIELD_QANGLE_WORLDSPACE);
        CASE_STRING(FIELD_QUATERNION_WORLDSPACE);
        CASE_STRING(FIELD_HSCRIPT_LIGHTBINDING);
        CASE_STRING(FIELD_V8_VALUE);
        CASE_STRING(FIELD_V8_OBJECT);
        CASE_STRING(FIELD_V8_ARRAY);
        CASE_STRING(FIELD_V8_CALLBACK_INFO);
        CASE_STRING(FIELD_UTLSTRING);
        CASE_STRING(FIELD_NETWORK_ORIGIN_CELL_QUANTIZED_POSITION_VECTOR);
        CASE_STRING(FIELD_HRENDERTEXTURE);
        CASE_STRING(FIELD_TYPECOUNT);
        default:
            return "UNKNOWN DATAFIELD TYPE";
    }
}
void Util::SpewDataMap( Datamap *dMap, bool toLogFile ) {

	while( dMap ){
        if( toLogFile ){
            Util::Log( "\nStart of Pred Map for %s\n", dMap->className );
        } else {
            cvar->ConsoleDPrintf( "Start of Pred Map for: %s\n", dMap->className );
        }
		for( uint64_t i = 0; i < dMap->numFields; i++ ){
			if( !dMap->dataDesc[i].fieldName )
				continue;

            if( toLogFile ){
                Util::Log( "-%s - [0x%x] - (%s)\n", dMap->dataDesc[i].fieldName, dMap->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL], DataFieldType2String( dMap->dataDesc[i].type ) );
            } else {
                cvar->ConsoleDPrintf( "-%s - [0x%x] - (%s)\n", dMap->dataDesc[i].fieldName, dMap->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL], DataFieldType2String( dMap->dataDesc[i].type ) );
            }
            if( dMap->dataDesc[i].type == FIELD_EMBEDDED ){
                if( dMap->dataDesc[i].td ){
                    if( toLogFile ){
                        Util::Log("Recursing for Property: %s(%s)\n", dMap->dataDesc[i].fieldName, dMap->dataDesc[i].td->className ? dMap->dataDesc[i].td->className : "NULL_NAME");
                    } else {
                        cvar->ConsoleDPrintf("Recursing for Property: %s(%s)\n", dMap->dataDesc[i].fieldName, dMap->dataDesc[i].td->className ? dMap->dataDesc[i].td->className : "NULL_NAME");
                    }
                    Util::SpewDataMap( dMap->dataDesc[i].td, toLogFile );
                    if( toLogFile ){
                        Util::Log("^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
                    } else {
                        cvar->ConsoleDPrintf("^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
                    }
                }
            }
		}
        if( toLogFile ){
            Util::Log( "^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n" );
        } else {
            cvar->ConsoleDPrintf( "^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n" );
        }
        dMap = dMap->baseMap;
	}
}

int Util::FindDataMapElementOffset( Datamap *dMap, const char *element ) {
    while( dMap ){
        for( uint64_t i = 0; i < dMap->numFields; i++ ){
            if( !dMap->dataDesc[i].fieldName )
                continue;

            if( !strcmp(dMap->dataDesc[i].fieldName, element) )
                return dMap->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL];

            if( dMap->dataDesc[i].type == FIELD_EMBEDDED ){
                if( dMap->dataDesc[i].td ){

                    int temp = Util::FindDataMapElementOffset( dMap->dataDesc[i].td, element );
                    if( temp != 0 )
                        return temp;
                }
            }
        }
        dMap = dMap->baseMap;
    }


    return 0;
}
ConVar *Util::RegisterConVar( const char *name, const char *defaultValue, uint32_t flags, const char *helpString, bool bMin, float fMin, bool bMax, float fMax ) {
	/** GHETTO HACKS AHEAD - BEWARE! **/
	// we're gonna base our convar off of this random one
	ConCommandBase* sens = cvar->FindCommandBase("sensitivity");
	auto* command = new ConCommandBase;
	// copy er' in
	memcpy(command, sens, sizeof(ConCommandBase));
	// Lastly, change the variables we want to be different.
	command->isRegistered = false;
	command->flags = flags;
	command->next = nullptr;
	command->thisptr = command;
	command->hasMin = bMin;
	command->hasMax = bMax;
	command->minVal = fMin;
	command->maxVal = fMax;
	//command->unk = NULL;
	//command->unk2 = NULL;
    command->fValue = strtof(defaultValue, nullptr);
    command->iValue = atoi(defaultValue);

	size_t nameLen = strlen(name) + 1;
	command->name = new char[nameLen];
	if( command->name && name ){
		strncpy( command->name, name, nameLen);
	} else {
        MC_PRINTF_ERROR("Error allocating space for ConVar name (%s)!\n", name);
		return nullptr;
	}


	size_t valueLen = strlen(defaultValue) + 1;
	command->strValue = new char[valueLen];
    command->strDefault = new char[valueLen];

	if( command->strValue && command->strDefault && defaultValue ){
		strncpy( command->strValue, defaultValue, valueLen );
        strncpy( command->strDefault, defaultValue, valueLen );
	} else {
        MC_PRINTF_ERROR("[%s]Error allocating space for ConVar values (%s)!\n", name);
		return nullptr;
	}

	if( helpString ){
		size_t descLen = strlen( helpString ) + 1;
		command->description = new char[descLen];
		if( command->description ){
			strncpy( command->description, helpString, descLen );
		} else{
			MC_PRINTF_ERROR("[%s]Error allocating space for ConVar description (%s)!\n", name);
			return nullptr;
		}
	} else {
		command->description = nullptr;
	}

	cvar->RegisterConCommand( command );
	Util::createdConvars.push_back(command);
    // cvar->ConsoleDPrintf("Registered convar %s @ %p\n", command->name, (void*)command);

    return cvar->FindVar(name);
}

void Util::SpewScriptScopes( GameScriptScopesWrapper *scopes, bool toLogFile ) {
    for( size_t i = 0; i < scopes->numScopes; i++ ){
        Util::Log("------ %s(%d) ------\n", scopes->scopes[i]->name, scopes->scopes[i]->numFuncs);

        for( size_t j = 0; j < scopes->scopes[i]->numFuncs; j++ ){
            ScopeFunction &func = scopes->scopes[i]->funcs[j];
            Util::Log("%s %s ( ", GetArgTypeString(func.returnType), func.name);
            const char *names = func.argNames;
            if( names ){
                for( int k = 0; k < func.argNum; k++ ){
                    Util::Log( "%s %s, ", GetArgTypeString( func.argTypes[k] ), names );
                    names += strlen( names ) + 1;
                }
            } else {
                for( int k = 0; k < func.argNum; k++ ){
                    Util::Log( "%s noname_arg_%d, ", GetArgTypeString( func.argTypes[k] ), k );
                }
            }
            Util::Log(")\n");
        }
    }
}

void* Util::GetScriptScopeFunction( GameScriptScopesWrapper *scopes, const char *exactName ) {
    Util::Log("GetScriptScopeFunction called!\n");
    for( size_t i = 0; i < scopes->numScopes; i++ ) {
        for ( size_t j = 0; j < scopes->scopes[i]->numFuncs; j++ ) {
            ScopeFunction &func = scopes->scopes[i]->funcs[j];
            if( !strcmp( func.name, exactName ) ){
                Util::Log("Found func at %p\n", func.function);
                return func.function;
            }
        }
    }
    return nullptr;
}


bool Util::ReadParticleFiles( const char *blacklistFile, const char *trackedFile ) {
    struct stat buffer;
    FILE *fp;
    char fileline[256];
    std::string temp;

    if( blacklistFile && ( stat( blacklistFile, &buffer ) == 0 ) ){
        fp = fopen( blacklistFile, "r" );
        while( fgets( fileline, sizeof(fileline), fp ) ) {
            temp = fileline;
            if( temp.size() > 2 && temp[temp.length() - 1] == '\n' ){
                temp.erase( temp.length() -1 );
            }
            blacklistedParticles.push_back( temp );
        }
        fclose( fp );
    }

    if( trackedFile && ( stat( trackedFile, &buffer ) == 0 ) ){
        fp = fopen( trackedFile, "r" );
        while( fgets( fileline, sizeof(fileline), fp ) ) {
            temp = fileline;
            if( temp.size() > 2 && temp[temp.length() - 1] == '\n' ){
                temp.erase( temp.length() -1 );
            }
            trackedParticles.push_back( temp );
        }
        fclose( fp );
    }

    for( size_t i = 0; i < blacklistedParticles.size(); i++ ){
        Util::Log("Blacklisted particle - (%s)\n", blacklistedParticles[i].c_str());
    }

    for( size_t i = 0; i < trackedParticles.size(); i++ ){
        Util::Log("Tracked particle - (%s)\n", trackedParticles[i].c_str());
    }

    return true;
}