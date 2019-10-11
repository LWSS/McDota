#pragma once

#include <cstdint>
#include <vector>

#include "../SDK/Datamap.h"
#include "../SDK/IInputSystem.h" //ButtonCode
#include "../SDK/Convar.h"
#include "../SDK/CPanoramaGameScriptScope.h"


namespace Util
{
    inline std::vector<ConCommandBase*> createdConvars;

	ButtonCode_t GetButtonCode(const char* buttonName);
    /* 136 flag is client & archive */
	ConVar *RegisterConVar( const char *name, const char *defaultValue, uint32_t flags = 136, const char *helpString = nullptr, bool bMin = false, float fMin = 0.0f, bool bMax = false, float fMax = false );

	void SpewDataMap( Datamap *dMap, bool toLogFile = false );
	void SpewScriptScopes( GameScriptScopesWrapper *scopes, bool toLogFile = false );
	void* GetScriptScopeFunction( GameScriptScopesWrapper *scopes, const char *exactName );

	int FindDataMapElementOffset( Datamap *dMap, const char *element );
}