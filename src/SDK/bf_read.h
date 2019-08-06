#pragma once

#include <cstdint>

typedef int32_t int32;
typedef int64_t int64;
typedef uint32_t uint32;
typedef uint64_t uint64;

#define BITBUF_INLINE inline
#define RESTRICT __restrict

class bf_read
{
public:
    // The current buffer.
    const unsigned char* __restrict m_pData;
    int						m_nDataBytes;
    int						m_nDataBits;

    // Where we are in the buffer.
    int				m_iCurBit;


private:
    // Errors?
    bool			m_bOverflow;

    // For debugging..
    bool			m_bAssertOnOverflow;

    const char		*m_pDebugName;

public:
    bf_read()
    {
        m_pData = NULL;
        m_nDataBytes = 0;
        m_nDataBits = -1; // set to -1 so we overflow on any operation
        m_iCurBit = 0;
        m_bOverflow = false;
        m_bAssertOnOverflow = true;
        m_pDebugName = NULL;
    }

    // nMaxBits can be used as the number of bits in the buffer.
    // It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
    bf_read( const void *pData, int nBytes, int nBits = -1 );
    bf_read( const char *pDebugName, const void *pData, int nBytes, int nBits = -1 );

    // Start reading from the specified buffer.
    // pData's start address must be dword-aligned.
    // nMaxBits can be used as the number of bits in the buffer.
    // It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
    void			StartReading( const void *pData, int nBytes, int iStartBit = 0, int nBits = -1 );

    // Restart buffer reading.
    void			Reset();

    // Enable or disable assertion on overflow. 99% of the time, it's a bug that we need to catch,
    // but there may be the occasional buffer that is allowed to overflow gracefully.
    void			SetAssertOnOverflow( bool bAssert );

    // This can be set to assign a name that gets output if the buffer overflows.
    [[nodiscard]] const char*		GetDebugName() const { return m_pDebugName; }
    void			SetDebugName( const char *pName );

    void			ExciseBits( int startbit, int bitstoremove );


// Bit functions.
public:

    // Returns 0 or 1.
    int				ReadOneBit();


protected:

    unsigned int	CheckReadUBitLong(int numbits);		// For debugging.
    int				ReadOneBitNoCheck();				// Faster version, doesn't check bounds and is inlined.
    bool			CheckForOverflow(int nBits);


public:

    // Get the base pointer.
    const unsigned char*	GetBasePointer() { return m_pData; }

    [[nodiscard]] BITBUF_INLINE int TotalBytesAvailable( void ) const
    {
        return m_nDataBytes;
    }

    // Read a list of bits in.
    void            ReadBits(void *pOut, int nBits);
    // Read a list of bits in, but don't overrun the destination buffer.
    // Returns the number of bits read into the buffer. The remaining
    // bits are skipped over.
    int             ReadBitsClamped_ptr(void *pOut, size_t outSizeBytes, size_t nBits);
    // Helper 'safe' template function that infers the size of the destination
    // array. This version of the function should be preferred.
    // Usage: char databuffer[100];
    //        ReadBitsClamped( dataBuffer, msg->m_nLength );
    template <typename T, size_t N>
    int             ReadBitsClamped( T (&pOut)[N], size_t nBits )
    {
        return ReadBitsClamped_ptr( pOut, N * sizeof(T), nBits );
    }

    float			ReadBitAngle( int numbits );

    unsigned int	ReadUBitLong( int numbits ) RESTRICT;
    unsigned int	ReadUBitLongNoInline( int numbits ) RESTRICT;
    unsigned int	PeekUBitLong( int numbits );
    int				ReadSBitLong( int numbits );

    // reads an unsigned integer with variable bit length
    unsigned int	ReadUBitVar();
    unsigned int	ReadUBitVarInternal( int encodingType );

    // reads a varint encoded integer
    uint32			ReadVarInt32();
    uint64			ReadVarInt64();
    int32			ReadSignedVarInt32();
    int64			ReadSignedVarInt64();

    // You can read signed or unsigned data with this, just cast to
    // a signed int if necessary.
    unsigned int	ReadBitLong(int numbits, bool bSigned);

    float			ReadBitCoord();
    float			ReadBitCoordMP( bool bIntegral, bool bLowPrecision );
    float			ReadBitFloat();
    float			ReadBitNormal();
    void			ReadBitVec3Coord( Vector& fa );
    void			ReadBitVec3Normal( Vector& fa );
    void			ReadBitAngles( QAngle& fa );

    // Faster for comparisons but do not fully decode float values
    unsigned int	ReadBitCoordBits();
    unsigned int	ReadBitCoordMPBits( bool bIntegral, bool bLowPrecision );

// Byte functions (these still read data in bit-by-bit).
public:

    BITBUF_INLINE int	ReadChar() { return (char)ReadUBitLong(8); }
    BITBUF_INLINE int	ReadByte() { return ReadUBitLong(8); }
    BITBUF_INLINE int	ReadShort() { return (short)ReadUBitLong(16); }
    BITBUF_INLINE int	ReadWord() { return ReadUBitLong(16); }
    BITBUF_INLINE long ReadLong() { return ReadUBitLong(32); }
    int64			ReadLongLong();
    float			ReadFloat();
    bool			ReadBytes(void *pOut, int nBytes);

    // Returns false if bufLen isn't large enough to hold the
    // string in the buffer.
    //
    // Always reads to the end of the string (so you can read the
    // next piece of data waiting).
    //
    // If bLine is true, it stops when it reaches a '\n' or a null-terminator.
    //
    // pStr is always null-terminated (unless bufLen is 0).
    //
    // pOutNumChars is set to the number of characters left in pStr when the routine is
    // complete (this will never exceed bufLen-1).
    //
    bool			ReadString( char *pStr, int bufLen, bool bLine=false, int *pOutNumChars=NULL );

    // Reads a string and allocates memory for it. If the string in the buffer
    // is > 2048 bytes, then pOverflow is set to true (if it's not NULL).
    char*			ReadAndAllocateString( bool *pOverflow = nullptr );

    // Returns nonzero if any bits differ
    int				CompareBits( bf_read * RESTRICT other, int bits ) RESTRICT;
    int				CompareBitsAt( int offset, bf_read * RESTRICT other, int otherOffset, int bits ) RESTRICT;

// Status.
public:
    int				GetNumBytesLeft();
    int				GetNumBytesRead();
    int				GetNumBitsLeft();
    [[nodiscard]] int				GetNumBitsRead() const;

    // Has the buffer overflowed?
    [[nodiscard]] inline bool		IsOverflowed() const {return m_bOverflow;}

    inline bool		Seek(int iBit);					// Seek to a specific bit.
    inline bool		SeekRelative(int iBitDelta);	// Seek to an offset from the current position.

    // Called when the buffer is overflowed.
    void			SetOverflowFlag();
};