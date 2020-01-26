#pragma once

#include "../SDK/IInputSystem.h" //ButtonCode
#include "../SDK/Convar.h"
#include "../SDK/CPanoramaGameScriptScope.h"
#include "../SDK/Datamap.h"

#include <cstdint>
#include <vector>
#include <string>

namespace Util
{
    inline std::vector<ConVar*> createdConvars;

	// List of particles that should hid or tracked for performance reasons.
	// Linear will be faster than a hashmap until about ~400 entries.
	inline std::vector<std::string> blacklistedParticles;
	inline std::vector<std::string> trackedParticles;

	ButtonCode_t GetButtonCode(const char* buttonName);
	ConVar *RegisterConVar( const char *name, const char *defaultValue, uint32_t flags = FCVAR_CLIENTDLL | FCVAR_ARCHIVE, const char *helpString = nullptr, bool bMin = false, float fMin = 0.0f, bool bMax = false, float fMax = false );

	void SpewDataMap( Datamap *dMap, bool toLogFile = false );
	void SpewScriptScopes( GameScriptScopesWrapper *scopes, bool toLogFile = false );
	void* GetScriptScopeFunction( GameScriptScopesWrapper *scopes, const char *exactName );

	int FindDataMapElementOffset( Datamap *dMap, const char *element );

	bool ReadParticleFiles( const char *blacklistFile = nullptr, const char *trackedFile = nullptr );
}