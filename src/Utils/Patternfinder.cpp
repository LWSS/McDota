#include "Patternfinder.h"

#include <link.h> // dl_iterate_phdr
#include <vector>
#include <string.h> //strcasestr
#include "../Interfaces.h"

// taken from aixxe's cstrike-basehook-linux
static bool GetLibraryInformation(const char* library, uintptr_t* address, size_t* size) {
    static std::vector<dlinfo_t> libraries;

    if (libraries.size() == 0) {
        dl_iterate_phdr([] (struct dl_phdr_info* info, size_t, void*) {
            dlinfo_t library_info = {};

            library_info.library = info->dlpi_name;
            library_info.address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
            library_info.size = info->dlpi_phdr[0].p_memsz;

            libraries.push_back(library_info);

            return 0;
        }, nullptr);
    }

    for (const dlinfo_t& current: libraries) {
        if (!strcasestr(current.library, library))
            continue;

        if (address)
            *address = current.address;

        if (size)
            *size = current.size;

        return true;
    }

    return false;
}

// original code by dom1n1k and Patrick at GameDeception
inline bool Compare(const unsigned char* pData, const unsigned char* bMask, const char* szMask)
{
    for (; *szMask; ++szMask, ++pData, ++bMask)
        if (*szMask == 'x' && *pData != *bMask)
            return false;

    return (*szMask) == 0;
}

uintptr_t PatternFinder::FindPattern(uintptr_t dwAddress, uintptr_t dwLen, unsigned char* bMask, const char* szMask)
{
	for (uintptr_t i = 0; i < dwLen; i++)
		if (Compare((unsigned char*)(dwAddress + i), bMask, szMask))
			return (uintptr_t)(dwAddress + i);

	return 0;
}

uintptr_t PatternFinder::FindPatternInModule(const char* moduleName, unsigned char* bMask, const char* szMask, const char* why)
{
	uintptr_t baseAddress;
	size_t memSize;

	if (!GetLibraryInformation(moduleName, &baseAddress, &memSize)){
		MC_PRINTF_ERROR("Could Not Get info for Module %s\n", moduleName);
		return 0;
	}

	uintptr_t ret = FindPattern(baseAddress, memSize, bMask, szMask);
	if( !ret ){
		MC_PRINTF_ERROR("Could not find pattern for %s\n", why );
	}
	return ret;
}