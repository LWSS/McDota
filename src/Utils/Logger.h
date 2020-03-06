#pragma once

#include "../SDK/CBaseFileSystem.h"

inline CBaseFileSystem *fs;
namespace Logger
{
    inline FileHandle_t logFile; // logfile Handle
}

#define MC_LOGF(f_, ...) fs->FPrintf( Logger::logFile, ("" f_), ##__VA_ARGS__);fs->Flush( Logger::logFile )