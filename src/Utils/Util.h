#pragma once

#include <string>

namespace Util
{
	extern const char *logFileName;
	void Log(char const * format, ...);
	long GetEpochMs();
	void RemoveLinkMapEntry(const char *partialName, void **prev, void **curr, void **next);
	void RestoreLinkMapEntry(void *prev, void *curr, void *next);
    void DumpLinkMaps();
    int GetFileContents( const char *path, std::string *out );
}