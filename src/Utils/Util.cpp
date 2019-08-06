#include "Util.h"

#include <cstdio> // setbuf, fopen, fclose..
#include <cstdarg> // va_list, va_start, va_arg, va_end
#include <chrono> // chrono time stuff
#include <dlfcn.h> //dlopen
#include <link.h> // link map
#include <cstring>
#include <fstream>
#include <sstream>

void Util::Log(char const * format, ...)
{
	char buffer[4096];
	static bool bFirst = true;
	FILE *logFile;

	if ( bFirst ) {
		logFile = fopen(Util::logFileName, "w"); // create new log
		fprintf(logFile, "--Start of log--\n");
		bFirst = false;
	} else {
		logFile = fopen(Util::logFileName, "a"); // append to log
	}
	setbuf( logFile, nullptr ); // Turn off buffered I/O, decreases performance but if crash occurs, no unflushed buffer.
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 4096, format, args);
	fprintf(logFile, buffer);
	va_end(args);
	fclose(logFile);
}

long Util::GetEpochMs()
{
	auto duration = std::chrono::system_clock::now().time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

/* Removes McDota from Library-Level dynamic library linked list
 * You need to save the prev/curr/next void ptrs for unloading. */
void Util::RemoveLinkMapEntry(const char *partialName, void **prev, void **curr, void **next)
{
    auto *map = reinterpret_cast<struct link_map*>(dlopen(nullptr, RTLD_NOW));
    map = map->l_next->l_next;
    while (map) {
        if( strstr( map->l_name, partialName ) != nullptr ){
            *prev = map->l_prev;
            *curr = map;
            *next = map->l_next;
            if( map->l_prev ){
                map->l_prev->l_next = map->l_next;
            }
            if( map->l_next ){
                map->l_next->l_prev = map->l_prev;
            }
            return;
        }
        map = map->l_next;
    }
}
/* Undoes the above Function */
void Util::RestoreLinkMapEntry(void *prev, void *curr, void *next)
{
	if( prev )
	{
		auto *previousEntry = reinterpret_cast<link_map*>(prev);
		previousEntry->l_next = reinterpret_cast<link_map*>(curr);
	}
	if( next )
	{
		auto *nextEntry = reinterpret_cast<link_map*>(next);
		nextEntry->l_prev = reinterpret_cast<link_map*>(curr);
	}
}

void Util::DumpLinkMaps( )
{
    auto *map = reinterpret_cast<struct link_map*>(dlopen(nullptr, RTLD_NOW));
    map = map->l_next->l_next;
    while (map) {
        Util::Log("%s\n", map->l_name);
        map = map->l_next;
    }
}

int Util::GetFileContents( const char *path, std::string *out )
{
    std::ifstream file(path);

    if( !file.is_open() ){
        Util::Log("Error opening /proc/ file (%s)for unloading!\n", path);
        return -1;
    }

    std::stringstream buff;
    buff << file.rdbuf();
    *out = buff.str();
    return 0;
}
