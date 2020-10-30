#pragma once

#include "IAppSystem.h"
#include "INetChannel.h"

class IPeerToPeerCallbacks;
class IConnectionlessPacketHandler;

// xref "Leaked channel %s remote %s\n" to Shutdown()
// or xref "CNetworkSystem::ShutdownGameServer" to ShutdownGameServer()
class CNetworkSystem : IAppSystem
{
public:
    // this one is kinda tough, they changed a lot of their networking
    virtual void CNetworkSystem__InitGameServer(void) = 0; // 11
    virtual void ShutdownGameServer(void) = 0;
    virtual void sub_1E95A0() = 0;
    virtual void loc_1E6B50() = 0;
    virtual void loc_1F5210() = 0;
    virtual void sub_1E4ED0() = 0;
    virtual void sub_1F1EF0() = 0;
    virtual void InitP2PNetworking(IPeerToPeerCallbacks *) = 0; // "Can't connectloopback"
    virtual void ShutdownP2PNetworking(int) = 0;
    virtual void TerminateP2PSockets(int) = 0;
    virtual void sub_1E3CC0() = 0;
    virtual void loc_1F45C0() = 0;
    virtual void SetDefaultBroadcastPort(int) = 0;
    virtual void sub_1E8990() = 0;
    virtual void FlushP2PChannels(int) = 0;
    virtual INetChannel* CreateNetChannel(int, void *ns_address, const char *, unsigned int, unsigned int) = 0; // "netchan_t::reliabledata" xref all the way back
    virtual void sub_1F0D40() = 0;
    virtual void ProcessSocket(int, IConnectionlessPacketHandler *) = 0;
    virtual void loc_1F1CB0() = 0;
    virtual void sub_1F1A00() = 0;
    virtual void loc_1F3BA0() = 0;
    virtual void sub_1ED1B0() = 0;
    virtual void loc_1ED530() = 0;
    virtual void loc_1ECEE0() = 0;
    /*
    virtual void sub_1F0140() = 0;
    virtual void CloseNetworkSocket(int, int) = 0;
    virtual void OutOfBandPrintf(int, const void *ns_address, const char *, ...) = 0;
    virtual void SetTime(double) = 0;
    virtual void SetTimeScale(float) = 0;
    virtual double GetNetTime(void) = 0;
    virtual void DescribeSocket(int) = 0;
    virtual void sub_1E3500() = 0;
     */
    virtual void BufferToBufferCompress(char *, unsigned int *, const char *, unsigned int) = 0;
    virtual void BufferToBufferDecompress(char *, unsigned int *, const char *, unsigned int) = 0;
    /*
    virtual void *GetPublicAdr(void) = 0;
    virtual void *GetLocalAdr(void) = 0;
    virtual void GetUDPPort(int) = 0;
    virtual void sub_1E4150() = 0;
    virtual void sub_1E46D0() = 0;
    virtual void sub_1E3DD0() = 0;
    virtual void sub_1E4DB0() = 0;
    virtual void loc_1EB5F0() = 0;
    virtual void loc_1EB570() = 0;
    virtual void loc_1EB7A0() = 0;
    virtual void loc_1EB720() = 0;
    virtual void loc_1EB950() = 0;
    virtual void loc_1EB8D0() = 0;
    virtual void loc_1EBB00() = 0;
    virtual void loc_1EBA80() = 0;
    virtual void loc_1EBCB0() = 0;
    virtual void loc_1EBC30() = 0;
    virtual void sub_1F20B0() = 0;
    virtual void sub_1E51D0() = 0;
    virtual void sub_1E4FF0() = 0;
    virtual void sub_1F53F0() = 0;
    virtual void sub_1F5400() = 0;
    virtual void sub_1F5E80() = 0;
    virtual void sub_1E41A0() = 0;
    virtual void sub_1E3400() = 0;
    virtual void sub_1E49A0() = 0;
    virtual void sub_1E49D0() = 0;
    virtual void sub_1E3530() = 0;
    virtual void sub_1F0A70() = 0;
    virtual void DESTROY1(void) = 0;
    virtual void DESTROY2(void) = 0;
    virtual void MessageData(unsigned int, unsigned short, unsigned int, unsigned char *) = 0;
    */
};