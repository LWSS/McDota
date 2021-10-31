#pragma once

#include "IAppSystem.h"

enum SearchPathAdd_t
{
    PATH_ADD_TO_HEAD,		// First path searched
    PATH_ADD_TO_TAIL,		// Last path searched
};

enum FileWarningLevel_t
{
    // A problem!
    FILESYSTEM_WARNING = -1,

    // Don't print anything
    FILESYSTEM_WARNING_QUIET = 0,

    // On shutdown, report names of files left unclosed
    FILESYSTEM_WARNING_REPORTUNCLOSED,

    // Report number of times a file was opened, closed
    FILESYSTEM_WARNING_REPORTUSAGE,

    // Report all open/close events to console ( !slow! )
    FILESYSTEM_WARNING_REPORTALLACCESSES,

    // Report all open/close/read events to the console ( !slower! )
    FILESYSTEM_WARNING_REPORTALLACCESSES_READ,

    // Report all open/close/read/write events to the console ( !slower! )
    FILESYSTEM_WARNING_REPORTALLACCESSES_READWRITE,

    // Report all open/close/read/write events and all async I/O file events to the console ( !slower(est)! )
    FILESYSTEM_WARNING_REPORTALLACCESSES_ASYNC,
};

enum DVDMode_t
{
    DVDMODE_OFF    = 0, // not using dvd
    DVDMODE_STRICT = 1, // dvd device only
    DVDMODE_DEV    = 2, // dev mode, mutiple devices ok
};

enum KeyValuesPreloadType_t
{
    TYPE_VMT,
    TYPE_SOUNDEMITTER,
    TYPE_SOUNDSCAPE,
    NUM_PRELOAD_TYPES
};

enum FilesystemOpenExFlags_t
{
    FSOPEN_UNBUFFERED		= (1 << 0),
    FSOPEN_FORCE_TRACK_CRC	= (1 << 1),		// This makes it calculate a CRC for the file (if the file came from disk) regardless
    // of the IFileList passed to RegisterFileWhitelist.
    FSOPEN_NEVERINPACK	    = (1 << 2),		// 360 only, hint to FS that file is not allowed to be in pack file
};

enum EFileCRCStatus
{
    k_eFileCRCStatus_CantOpenFile,		// We don't have this file.
    k_eFileCRCStatus_GotCRC
};

enum ECacheCRCType
{
    k_eCacheCRCType_SingleFile,
    k_eCacheCRCType_Directory,
    k_eCacheCRCType_Directory_Recursive
};

enum FileSystemSeek_t
{
    FILESYSTEM_SEEK_HEAD	= 0,
    FILESYSTEM_SEEK_CURRENT = 1,
    FILESYSTEM_SEEK_TAIL	= 2,
};

typedef unsigned long CRC32_t;

#define MAX_PATH        4096 // no clue if this is correct, MAX_PATH doesn't have a linux equivalent. (yes I know about PATH_MAX, but it can vary which is an issue).
class CUnverifiedCRCFile
{
public:
    char m_PathID[MAX_PATH];
    char m_Filename[MAX_PATH];
    CRC32_t m_CRC;
};

typedef void* FileHandle_t;
typedef int FileFindHandle_t;
typedef void* FileNameHandle_t;

class IFileList;
class CSysModule;
class KeyValues;
class CUtlBuffer;

// xref "fs_debug" to CBaseFileSystem::Init() - (libfilesystem_stdio)
class CBaseFileSystem : IAppSystem
{
public:
    virtual void sub_12AD0() = 0;
    virtual void sub_11330() = 0;
    virtual FileHandle_t Open( const char *pFileName, const char *pOptions, const char *pathID = 0 ) = 0;     // if pathID is NULL, all paths will be searched for the file
    virtual void Close( FileHandle_t file ) = 0;
    virtual void Seek( FileHandle_t file, int pos, FileSystemSeek_t seekType ) = 0;
    virtual unsigned int Tell( FileHandle_t file ) = 0;
    virtual unsigned int Size( FileHandle_t file ) = 0;
    virtual unsigned int Size( const char *pFileName, const char *pPathID = 0 ) = 0; // "FS:  Tried to Size NULL filename!"
    virtual void Flush( FileHandle_t file ) = 0;
    virtual bool Precache( const char *pFileName, const char *pPathID = 0 ) = 0;
    virtual void loc_2A870() = 0;
    virtual void loc_2ABE0() = 0;
    virtual int Read( void* pOutput, int size, FileHandle_t file ) = 0;
    virtual int	Write( void const* pInput, int size, FileHandle_t file ) = 0;
    virtual bool ReadFile() = 0;//const char *pFileName, const char *pPath, CUtlBuffer &buf, int nMaxBytes = 0, int nStartingByte = 0, FSAllocFunc_t pfnAlloc = NULL ) = 0;
    virtual bool WriteFile( const char *pFileName, const char *pPath, CUtlBuffer &buf ) = 0;
    virtual bool UnzipFile( const char *pFileName, const char *pPath, const char *pDestination ) = 0;    // zip stuff Not "hooked up" for linux
    virtual bool CopyAFile( const char *pFileName, const char *pPath, const char *pDestination, bool unk ) = 0;
    virtual void sub_19350() = 0;
    virtual void sub_29580() = 0;
    virtual void AddSearchPath( const char *pPath, const char *pathID, SearchPathAdd_t addType, int searchPathPriority ) = 0;// 11
    virtual void RemoveSearchPath( const char *pPath, const char *pathID ) = 0;
    virtual void SaveSearchPathState( const char * ) = 0;
    virtual void RestoreSearchPathState( void * SearchPathStateHandle_t__ ) = 0;
    virtual void DestroySearchPathState( void * SearchPathStateHandle_t__ ) = 0;
    virtual void RemoveAllSearchPaths( void ) = 0;
    virtual void RemoveSearchPaths( const char * ) = 0;
    virtual void MarkPathIDByRequestOnly( const char *, bool ) = 0;
    virtual void loc_27BA0() = 0;
    virtual void loc_280E0() = 0;
    virtual void loc_27610() = 0;
    virtual void sub_11F20() = 0;
    virtual void sub_19F30() = 0;
    virtual void sub_232E0() = 0;
    virtual void sub_11E60() = 0;
    virtual void sub_1BFC0() = 0;
    virtual void sub_1EDC0() = 0;
    virtual void RemoveFile( char const* pRelativePath, const char *pathID = 0 ) = 0;
    virtual bool RenameFile( char const *pOldPath, char const *pNewPath, const char *pathID = 0 ) = 0;
    virtual bool IsDirectory( const char *pFileName, const char *pathID = 0  ) = 0; // 30
    virtual void FileTimeToString( char* pStrip, int maxCharsIncludingTerminator, long long fileTime ) = 0;
    virtual void SetBufferSize( FileHandle_t, unsigned int nBytes ) = 0; //"FS:  Tried to SetBufferSize NULL file"
    virtual bool IsOK( FileHandle_t file ) = 0;
    virtual bool EndOfFile( FileHandle_t file ) = 0;
    virtual char* ReadLine( char *pOutput, int maxChars, FileHandle_t file ) = 0;
    virtual int FPrintf( FileHandle_t file, const char *pFormat, ... ) = 0;
    virtual CSysModule* LoadModule( const char *pFileName, const char *pPathID = 0, bool bValidatedDllOnly = true ) = 0;
    virtual void UnloadModule( CSysModule *pModule ) = 0;
    virtual const char* FindFirst( const char *pWildCard, FileFindHandle_t *pHandle ) = 0;
    virtual const char* FindNext( FileFindHandle_t &handle ) = 0;
    virtual bool FindIsDirectory( const FileFindHandle_t &handle ) = 0;
    virtual void FindClose( FileFindHandle_t &handle ) = 0;
    virtual const char* FindFirstEx( const char *pWildCard, const char *pPathID, FileFindHandle_t *pHandle ) = 0;
    virtual void FindFileAbsoluteList() = 0;//CUtlVector<CUtlString,CUtlMemory<CUtlString,int>> &,char const*,char const* ) = 0;
    virtual const char* GetLocalPath( const char *pFileName, char *pLocalPath, int localPathBufferSize ) = 0;
    virtual bool GetCurrentDirectory( char* pDirectory, int maxlen ) = 0;
    virtual FileNameHandle_t FindOrAddFileName( const char *pFileName ) = 0;
    virtual bool String( const FileNameHandle_t& handle, char *buf, int buflen ) = 0;
    virtual void pure1() = 0;
    virtual void pure2() = 0;
    virtual void pure3() = 0;
    virtual void pure4() = 0;
    virtual void pure5() = 0;
    virtual void GetLocalCopy( const char *pFileName ) = 0;
    virtual void PrintOpenedFiles( void ) = 0;
    virtual void PrintSearchPaths( void ) = 0;
    virtual void SetWarningFunc( void (*pfnWarning)( const char *fmt, ... ) ) = 0;
    virtual void SetWarningLevel( FileWarningLevel_t level ) = 0;
    virtual void AddLoggingFunc( void (*pfnLogFunc)( const char *fileName, const char *accessType ) ) = 0;
    virtual void RemoveLoggingFunc( void (*pfnLogFunc)( const char *fileName, const char *accessType ) ) = 0;
    virtual void* GetFilesystemStatistics( void ) = 0;
    virtual FileHandle_t OpenEx( const char *pFileName, const char *pOptions, unsigned int flags = 0, const char *pathID = 0 ) = 0;
    virtual int	ReadEx( void* pOutput, int sizeDest, int size, FileHandle_t file ) = 0;
    virtual int	ReadFileEx() = 0;// const char *pFileName, const char *pPath, void **ppBuf, bool bNullTerminate = false, bool bOptimalAlloc = false, int nMaxBytes = 0, int nStartingByte = 0, FSAllocFunc_t pfnAlloc = NULL ) = 0;
    virtual FileNameHandle_t FindFilename( char const *pFileName ) = 0;
    virtual KeyValues	*LoadKeyValues( KeyValuesPreloadType_t type, char const *filename, char const *pPathID = 0 ) = 0;
    virtual void loc_16F30() = 0;
    virtual bool GetFileTypeForFullPath( char const *pFullPath, wchar_t *buf, int bufSizeInBytes ) = 0;
    virtual bool ReadToBuffer() = 0;//void *,CUtlBuffer &,int,void * (*)(char const*,uint)
    virtual bool GetOptimalIOConstraints( FileHandle_t hFile, unsigned *pOffsetAlign, unsigned *pSizeAlign, unsigned *pBufferAlign ) = 0;
    virtual void *AllocOptimalReadBuffer( FileHandle_t hFile, unsigned nSize = 0, unsigned nOffset = 0 ) = 0;
    virtual void FreeOptimalReadBuffer( void * ) = 0;
    virtual int	GetPathIndex( const FileNameHandle_t &handle ) = 0;
    virtual long long GetPathTime( const char *pPath, const char *pPathID ) = 0;
    virtual DVDMode_t GetDVDMode() = 0;
    virtual void EnableWhitelistFileTracking( bool bEnable ) = 0;
    virtual void RegisterFileWhitelist( IFileList *pWantCRCList, IFileList *pAllowFromDiskList, IFileList **pFilesToReload ) = 0;
    virtual void MarkAllCRCsUnverified() = 0;
    virtual void CacheFileCRCs( const char *pPathname, ECacheCRCType eType, IFileList *pFilter ) = 0;
    virtual EFileCRCStatus	CheckCachedFileCRC( const char *pPathID, const char *pRelativeFilename, CRC32_t *pCRC ) = 0;
    virtual int GetUnverifiedCRCFiles( CUnverifiedCRCFile *pFiles, int nMaxFiles ) = 0;
    virtual int GetWhitelistSpewFlags(void) = 0;
    virtual void SetWhitelistSpewFlags( int flags ) = 0;
    virtual void InstallDirtyDiskReportFunc(void (*)(void)) = 0;
    virtual bool IsLaunchedFromXboxHDD(void) = 0;
    virtual bool IsInstalledToXboxHDDCache(void) = 0;
    virtual bool IsDVDHosted(void) = 0;
    virtual bool IsInstallAllowed(void) = 0;
    virtual void GetSearchPathID(char *, int) = 0;
    virtual void FixupSearchPathsAfterInstall() = 0;
    virtual void GetDirtyDiskReportFunc() = 0;
    virtual void AddVPKFile() = 0;
    virtual void RemoveVPKFile() = 0;
    virtual void IsVPKFileLoaded() = 0;
    virtual void EnableAutoVPKFileLoading() = 0;
    virtual void GetAutoVPKFileLoading() = 0;
    virtual void AddUGCVPKFile() = 0;
    virtual void RemoveUGCVPKFile() = 0;
    virtual void IsUGCVPKFileLoaded() = 0;
    virtual void ParseUGCHandleFromFilename() = 0;
    virtual void CreateFilenameforUGCFile() = 0;
    virtual void OpenUGCFile() = 0;
    virtual void sub_10E00() = 0; // DLC-related functions. Changed with battlepass 2020
    virtual void DeleteDirectory() = 0;
    virtual void DeleteDirectoryAndContents() = 0;
    virtual void IsPathInvalidForFilesystem() = 0; //strLener
    virtual void GetAvailableDrives() = 0;
    virtual void Readline() = 0;
    virtual void sub_238A0() = 0;
    virtual void loc_26460() = 0; // "WARNING: Local content might be corrupt"
    virtual void loc_25B30() = 0;
    virtual void unk_26910() = 0;
    virtual void unk_26D50() = 0;
    virtual void pure6() = 0;
    virtual void pure7() = 0;
    virtual void pure8() = 0;
    virtual void pure9() = 0;
    virtual void pure10() = 0;
    virtual void pure11() = 0;
    virtual void pure12() = 0;
    virtual void pure13() = 0;
    virtual void pure14() = 0;
    virtual void pure15() = 0;
    virtual void pure16() = 0;
    virtual void pure17() = 0;
    virtual void sub_10DE0() = 0;
    virtual void pure18() = 0;
};