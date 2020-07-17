#include "Util_sdk.h"

#include "Logger.h"
#include "../Interfaces.h"

#include <link.h>

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
            MC_LOGF( "\nStart of Pred Map for %s\n", dMap->className );
        } else {
            MC_PRINTF( "Start of Pred Map for: %s\n", dMap->className );
        }
		for( uint64_t i = 0; i < dMap->numFields; i++ ){
			if( !dMap->dataDesc[i].fieldName )
				continue;

            if( toLogFile ){
                MC_LOGF( "-%s - [0x%x] - (%s)\n", dMap->dataDesc[i].fieldName, dMap->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL], DataFieldType2String( dMap->dataDesc[i].type ) );
            } else {
                MC_PRINTF( "-%s - [0x%x] - (%s)\n", dMap->dataDesc[i].fieldName, dMap->dataDesc[i].fieldOffset[TD_OFFSET_NORMAL], DataFieldType2String( dMap->dataDesc[i].type ) );
            }
            if( dMap->dataDesc[i].type == FIELD_EMBEDDED ){
                if( dMap->dataDesc[i].td ){
                    if( toLogFile ){
                        MC_LOGF("Recursing for Property: %s(%s)\n", dMap->dataDesc[i].fieldName, dMap->dataDesc[i].td->className ? dMap->dataDesc[i].td->className : "NULL_NAME");
                    } else {
                        MC_PRINTF("Recursing for Property: %s(%s)\n", dMap->dataDesc[i].fieldName, dMap->dataDesc[i].td->className ? dMap->dataDesc[i].td->className : "NULL_NAME");
                    }
                    Util::SpewDataMap( dMap->dataDesc[i].td, toLogFile );
                    if( toLogFile ){
                        MC_LOGF("^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
                    } else {
                        MC_PRINTF("^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
                    }
                }
            }
		}
        if( toLogFile ){
            MC_LOGF( "^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n" );
        } else {
            MC_PRINTF( "^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n" );
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
	ConCommandBase* sens = cvar->FindCommandBase("m_yaw");
    ConVar* command = (ConVar*)new char[sizeof(ConVar)];

    // copy the vtable/layout from the existing convar
	memcpy(command, sens, sizeof(ConVar));

	command->m_bRegistered = false;
	command->m_nFlags = flags;
	command->m_pNext = nullptr;
	command->parent = command;
	command->bHasMin = bMin;
	command->bHasMax = bMax;
	command->m_fMinVal = fMin;
	command->m_fMaxVal = fMax;
    command->m_Value.m_fValue = strtof(defaultValue, nullptr);
    command->m_Value.m_nValue = atoi(defaultValue);

	size_t nameLen = strlen(name) + 1;
	command->m_pszName = new char[nameLen];
	if( command->m_pszName && name ){
		strncpy( command->m_pszName, name, nameLen);
	} else {
        MC_PRINTF_ERROR("Error allocating space for ConVar name (%s)!\n", name);
		return nullptr;
	}

	size_t valueLen = strlen(defaultValue) + 1;
	command->m_Value.m_pszString = new char[valueLen];
    command->m_pszDefaultValue = new char[valueLen];

	if( command->m_Value.m_pszString && command->m_pszDefaultValue && defaultValue ){
		strncpy( command->m_Value.m_pszString, defaultValue, valueLen );
        strncpy( command->m_pszDefaultValue, defaultValue, valueLen );
	} else {
        MC_PRINTF_ERROR("[%s]Error allocating space for ConVar values (%s)!\n", name);
		return nullptr;
	}

	if( helpString ){
		size_t descLen = strlen( helpString ) + 1;
		command->m_pszHelpString = new char[descLen];
		if( command->m_pszHelpString ){
			strncpy( command->m_pszHelpString, helpString, descLen );
		} else{
			MC_PRINTF_ERROR("[%s]Error allocating space for ConVar description (%s)!\n", name);
			return nullptr;
		}
	} else {
		command->m_pszHelpString = nullptr;
	}

	cvar->RegisterConCommand( command );
	Util::createdConvars.push_back(command);

    return cvar->FindVar(name);
}

void Util::SpewScriptScopes( GameScriptScopesWrapper *scopes, bool toLogFile ) {
    for( size_t i = 0; i < scopes->numScopes; i++ ){
        MC_LOGF("------ %s(%d) ------\n", scopes->scopes[i]->name, scopes->scopes[i]->numFuncs);

        for( size_t j = 0; j < scopes->scopes[i]->numFuncs; j++ ){
            ScopeFunction &func = scopes->scopes[i]->funcs[j];
            MC_LOGF("%s %s ( ", GetArgTypeString(func.returnType), func.name);
            const char *names = func.argNames;
            if( names ){
                for( int k = 0; k < func.argNum; k++ ){
                    MC_LOGF( "%s %s, ", GetArgTypeString( func.argTypes[k] ), names );
                    names += strlen( names ) + 1;
                }
            } else {
                for( int k = 0; k < func.argNum; k++ ){
                    MC_LOGF( "%s noname_arg_%d, ", GetArgTypeString( func.argTypes[k] ), k );
                }
            }
            MC_LOGF(")\n");
        }
    }
}

void* Util::GetScriptScopeFunction( GameScriptScopesWrapper *scopes, const char *exactName ) {
    MC_LOGF("GetScriptScopeFunction called!\n");
    for( size_t i = 0; i < scopes->numScopes; i++ ) {
        for ( size_t j = 0; j < scopes->scopes[i]->numFuncs; j++ ) {
            ScopeFunction &func = scopes->scopes[i]->funcs[j];
            if( !strcmp( func.name, exactName ) ){
                MC_LOGF("Found func at %p\n", func.function);
                return func.function;
            }
        }
    }
    return nullptr;
}


bool Util::ReadParticleFiles( const char *pathID, const char *blacklistFileName, const char *tracklistFileName ) {
    char linebuffer[256];
    char *scan;
    std::string temp;

    FileHandle_t blacklist = fileSystem->Open( blacklistFileName, "r", pathID );
    FileHandle_t tracklist = fileSystem->Open( tracklistFileName, "r", pathID );

    if( blacklist ){
        while( fileSystem->ReadLine( linebuffer, sizeof( linebuffer ), blacklist) ) {
            scan = linebuffer;
            temp.clear();
            while( *scan && (*scan != ' ') && (*scan != '\n') ){
                temp.push_back( *scan );
                scan++;
            }
            blacklistedParticles.push_back( temp );
        }
        fileSystem->Close( blacklist );
    }

    if( tracklist ){
        while( fileSystem->ReadLine( linebuffer, sizeof( linebuffer ), tracklist) ) {
            scan = linebuffer;
            temp.clear();
            while( *scan && (*scan != ' ') && (*scan != '\n') ){
                temp.push_back( *scan );
                scan++;
            }
            trackedParticles.push_back( temp );
        }
        fileSystem->Close( tracklist );
    }

    for( const std::string& particle : blacklistedParticles ){
        MC_LOGF("Blacklisted particle - (%s)\n", particle.c_str());
    }

    for( const std::string& particle : trackedParticles ){
        MC_LOGF("Tracked particle - (%s)\n", particle.c_str());
    }

    return true;
}

GFX_API Util::GetGraphicsApiType() {
    static GFX_API ret = GFX_API::UNKNOWN;

    dl_iterate_phdr([] (struct dl_phdr_info* info, size_t, void*) {
        /* Only one of the rendersystem dll's will be loaded at once. */
        if( strstr(info->dlpi_name, "librendersystemgl") ){
            ret = GFX_API::OPENGL;
        }
        if( strstr(info->dlpi_name, "librendersystemvulkan") ){
            ret = GFX_API::VULKAN;
        }

        return 0;
    }, nullptr);

    return ret;
}