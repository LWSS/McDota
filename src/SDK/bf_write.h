#pragma once

#include <cstdint>

typedef int32_t int32;
typedef int64_t int64;
typedef uint32_t uint32;
typedef uint64_t uint64;

#define RESTRICT __restrict

class bf_write
{
public:
    // The current buffer.
    unsigned long*  RESTRICT m_pData;
    int				m_nDataBytes;
    int				m_nDataBits;

    // Where we are in the buffer.
    int				m_iCurBit;

private:

    // Errors?
    bool			m_bOverflow;

    bool			m_bAssertOnOverflow;
    const char		*m_pDebugName;

public:
    bf_write(){
        m_pData = NULL;
        m_nDataBytes = 0;
        m_nDataBits = -1; // set to -1 so we generate overflow on any operation
        m_iCurBit = 0;
        m_bOverflow = false;
        m_bAssertOnOverflow = true;
        m_pDebugName = NULL;
    }

    bf_write( const char *pDebugName, void *pData, int nBytes, int nBits = -1 )
    {
        m_bAssertOnOverflow = true;
        m_pDebugName = pDebugName;
        StartWriting( pData, nBytes, 0, nBits );
    }

    bf_write( void *pData, int nBytes, int nBits = -1 )
    {
        m_bAssertOnOverflow = true;
        m_pDebugName = NULL;
        StartWriting( pData, nBytes, 0, nBits );
    }

    // Start writing to the specified buffer.
    // nMaxBits can be used as the number of bits in the buffer.
    // It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
    void			StartWriting( void *pData, int nBytes, int iStartBit = 0, int nMaxBits = -1 );

    // Restart buffer writing.
    void			Reset();

    // Get the base pointer.
    unsigned char*	GetBasePointer() { return (unsigned char*) m_pData; }

    // Enable or disable assertion on overflow. 99% of the time, it's a bug that we need to catch,
    // but there may be the occasional buffer that is allowed to overflow gracefully.
    void			SetAssertOnOverflow( bool bAssert );

    // This can be set to assign a name that gets output if the buffer overflows.
    const char*		GetDebugName();
    void			SetDebugName( const char *pDebugName );


// Seek to a specific position.
public:

    void			SeekToBit( int bitPos );


// Bit functions.
public:

    void			WriteOneBit(int nValue);
    void			WriteOneBitNoCheck(int nValue);
    void			WriteOneBitAt( int iBit, int nValue );

    // Write signed or unsigned. Range is only checked in debug.
    void			WriteUBitLong( unsigned int data, int numbits, bool bCheckRange=true );
    void			WriteSBitLong( int data, int numbits );

    // Tell it whether or not the data is unsigned. If it's signed,
    // cast to unsigned before passing in (it will cast back inside).
    void			WriteBitLong(unsigned int data, int numbits, bool bSigned);

    // Write a list of bits in.
    bool			WriteBits(const void *pIn, int nBits);

    // writes an unsigned integer with variable bit length
    void			WriteUBitVar( unsigned int data );

    // writes a varint encoded integer
    void			WriteVarInt32( uint32 data );
    void			WriteVarInt64( uint64 data );
    void			WriteSignedVarInt32( int32 data );
    void			WriteSignedVarInt64( int64 data );
    int				ByteSizeVarInt32( uint32 data );
    int				ByteSizeVarInt64( uint64 data );
    int				ByteSizeSignedVarInt32( int32 data );
    int				ByteSizeSignedVarInt64( int64 data );

    // Copy the bits straight out of pIn. This seeks pIn forward by nBits.
    // Returns an error if this buffer or the read buffer overflows.
    bool			WriteBitsFromBuffer( class bf_read *pIn, int nBits );

    void			WriteBitAngle( float fAngle, int numbits );
    void			WriteBitCoord (float f);
    void			WriteBitCoordMP( float f, bool bIntegral, bool bLowPrecision );
    void			WriteBitFloat(float val);
    void			WriteBitVec3Coord( const Vector& fa );
    void			WriteBitNormal( float f );
    void			WriteBitVec3Normal( const Vector& fa );
    void			WriteBitAngles( const QAngle& fa );


// Byte functions.
public:

    void			WriteChar(int val);
    void			WriteByte(int val);
    void			WriteShort(int val);
    void			WriteWord(int val);
    void			WriteLong(long val);
    void			WriteLongLong(int64 val);
    void			WriteFloat(float val);
    bool			WriteBytes( const void *pBuf, int nBytes );

    // Returns false if it overflows the buffer.
    bool			WriteString(const char *pStr);


// Status.
public:

    // How many bytes are filled in?
    [[nodiscard]] int				GetNumBytesWritten() const;
    [[nodiscard]] int				GetNumBitsWritten() const;
    int				GetMaxNumBits();
    int				GetNumBitsLeft();
    int				GetNumBytesLeft();
    unsigned char*	GetData();
    [[nodiscard]] const unsigned char*	GetData() const;

    // Has the buffer overflowed?
    bool			CheckForOverflow(int nBits);
    [[nodiscard]] inline bool		IsOverflowed() const {return m_bOverflow;}

    void			SetOverflowFlag();
};

inline void bf_write::StartWriting( void *pData, int nBytes, int iStartBit, int nBits )
{
    // Make sure it's dword aligned and padded.
    Assert( (nBytes % 4) == 0 );
    Assert(((unsigned long)pData & 3) == 0);

    // The writing code will overrun the end of the buffer if it isn't dword aligned, so truncate to force alignment
    nBytes &= ~3;

    m_pData = (unsigned long*)pData;
    m_nDataBytes = nBytes;

    if ( nBits == -1 )
    {
        m_nDataBits = nBytes << 3;
    }
    else
    {
        Assert( nBits <= nBytes*8 );
        m_nDataBits = nBits;
    }

    m_iCurBit = iStartBit;
    m_bOverflow = false;
}