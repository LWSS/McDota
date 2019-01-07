#include "util_sdk.h"
#include "util.h"

#include <string>

#include "../interfaces.h"
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
    std::string error("ERROR! UNKNOWN FIELD TYPE! - ");
    switch( type )
    {
        case FIELD_VOID:
            return "FIELD_VOID";
        case FIELD_FLOAT:
            return "FIELD_FLOAT";
        case FIELD_STRING:
            return "FIELD_STRING";
        case FIELD_VECTOR:
            return "FIELD_VECTOR";
        case FIELD_QUATERNION:
            return "FIELD_QUATERNION";
        case FIELD_INTEGER:
            return "FIELD_INTEGER";
        case FIELD_BOOLEAN:
            return "FIELD_BOOLEAN";
        case FIELD_SHORT:
            return "FIELD_SHORT";
        case FIELD_CHARACTER:
            return "FIELD_CHARACTER";
        case FIELD_COLOR32:
            return "FIELD_COLOR32";
        case FIELD_EMBEDDED:
            return "FIELD_EMBEDDED";
        case FIELD_CUSTOM:
            return "FIELD_CUSTOM";
        case FIELD_CLASSPTR:
            return "FIELD_CLASSPTR";
        case FIELD_EHANDLE:
            return "FIELD_EHANDLE";
        case FIELD_EDICT:
            return "FIELD_EDICT";
        case FIELD_POSITION_VECTOR:
            return "FIELD_POSITION_VECTOR";
        case FIELD_TIME:
            return "FIELD_TIME";
        case FIELD_TICK:
            return "FIELD_TICK";
        case FIELD_MODELNAME:
            return "FIELD_MODELNAME";
        case FIELD_SOUNDNAME:
            return "FIELD_SOUNDNAME";
        case FIELD_INPUT:
            return "FIELD_INPUT";
        case FIELD_FUNCTION:
            return "FIELD_FUNCTION";
        case FIELD_VMATRIX:
            return "FIELD_VMATRIX";
        case FIELD_VMATRIX_WORLDSPACE:
            return "FIELD_VMATRIX_WORLDSPACE";
        case FIELD_MATRIX3X4_WORLDSPACE:
            return "FIELD_MATRIX3X4_WORLDSPACE";
        case FIELD_INTERVAL:
            return "FIELD_INTERVAL";
        case FIELD_MODELINDEX:
            return "FIELD_MODELINDEX";
        case FIELD_MATERIALINDEX:
            return "FIELD_MATERIALINDEX";
        case FIELD_VECTOR2D:
            return "FIELD_VECTOR2D";
        case FIELD_TYPECOUNT:
            return "FIELD_TYPECOUNT";
        default:
            error.append( std::to_string((int)type) );
            return error.c_str();
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
	ConCommandBase* command = new ConCommandBase;
	// copy er' in
	memcpy(command, sens, sizeof(ConCommandBase));
	// Lastly, change the variables we want to be different.
	command->isRegistered = false;
	command->flags = flags;
	command->next = NULL;
	command->thisptr = command;
	command->hasMin = bMin;
	command->hasMax = bMax;
	command->minVal = fMin;
	command->maxVal = fMax;
	//command->unk = NULL;
	//command->unk2 = NULL;
    command->fValue = strtof(defaultValue, NULL);
    command->iValue = atoi(defaultValue);

	size_t nameLen = strlen(name) + 1;
	command->name = new char[nameLen];
	if( command->name && name ){
		strncpy( command->name, name, nameLen);
	} else {
		cvar->ConsoleDPrintf("[%s]Error allocating space for ConVar name (%s)!\n", __func__, name);
		return NULL;
	}


	size_t valueLen = strlen(defaultValue) + 1;
	command->strValue = new char[valueLen];
    command->strDefault = new char[valueLen];

	if( command->strValue && command->strDefault && defaultValue ){
		strncpy( command->strValue, defaultValue, valueLen );
        strncpy( command->strDefault, defaultValue, valueLen );
	} else {
		cvar->ConsoleDPrintf("[%s]Error allocating space for ConVar values (%s)!\n", __func__, name);
		return NULL;
	}

	if( helpString ){
		size_t descLen = strlen( helpString ) + 1;
		command->description = new char[descLen];
		if( command->description ){
			strncpy( command->description, helpString, descLen );
		} else{
			cvar->ConsoleDPrintf("[%s]Error allocating space for ConVar description (%s)!\n", __func__, name);
			return NULL;
		}
	} else {
		command->description = NULL;
	}

	cvar->RegisterConCommand( command );
	Util::createdConvars.push_back(command);
    // cvar->ConsoleDPrintf("Registered convar %s @ %p\n", command->name, (void*)command);

    return cvar->FindVar(name);
}