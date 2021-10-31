#pragma once

#include "CNetworkMessages.h"

// Find SetMaxRoutablePayloadSize with "Setting max routable payload" (libnetworksystem)
// Or "CNetChan::SendNetMessage" to SendNetMessage()
class INetChannel
{
public:
    virtual const char* GetName(void) = 0;// get channel name
    virtual const char* GetAddress(void) = 0;// get channel IP address as string
    virtual float GetTime(void) = 0;// current net time
    virtual float GetTimeConnected(void) = 0;// get connection time in seconds
    virtual int GetBufferSize(void) = 0;// netchannel packet history size
    virtual int GetDataRate(void) = 0;// send data rate in byte/sec
    virtual bool IsLocalHost(void) = 0;
    virtual bool IsLoopback(void) = 0;// true if loopback channel
    virtual bool IsTimingOut(void) = 0;// true if timing out
    virtual bool IsPlayback(void) = 0;// true if demo playback
    virtual float GetLatency(int) = 0;// current latency (RTT), more accurate but jittering
    virtual float GetAvgLatency(int) = 0;// average packet latency in seconds
    virtual float GetStdDevLatency(int) = 0;
    virtual void* GetLatencyBreakdown(void *NetChanStat_t,void *NetChanStat_t2, void *NetChanStat_t3, void *NetChanStat_t4) = 0;
    virtual float _unk() = 0;
    virtual float _unk1() = 0;
    virtual float _unk2() = 0;
    virtual void* GetTotalData(int) = 0;
    virtual void* GetTotalPackets(int) = 0;
    virtual int GetSequenceNr(int) = 0;
    virtual bool  IsValidPacket(int,int) = 0;
    virtual float  GetPacketTime(int,int) = 0;
    virtual void* GetPacketBits(int flow,int frameNum,int group,bool) = 0;
    virtual float GetTimeSinceLastReceived(void) = 0;
    virtual float GetCommandInterpolationAmount(int,int) = 0;
    virtual void GetPacketResponseLatency(int,int,int *,int *) = 0;
    virtual void GetRemoteFramerate(float *,float *,float *) = 0;
    virtual float GetTimeoutSeconds(void) = 0;
    virtual void _unknown(); //added w/ rubick arcana
    virtual void ResetLatencyStats(int) = 0;
    virtual void* GetLatencyStats(int) = 0;
    virtual void SetLatencyStats(int, void const * SNetChannelLatencyStats) = 0;
    virtual void SetInterpolationAmount(float) = 0;
    virtual void sub_C7980() = 0;
    virtual void sub_CC680() = 0; // added with 2020 BP
    virtual void sub_CC840() = 0; // added with 2020 BP
    virtual void sub_CC650() = 0; // added with 2020 BP
    virtual void sub_CC300() = 0; // added with 2020 BP
    virtual void sub_CC330() = 0; // added with 2020 BP
    virtual void sub_C2220(bool state) = 0; // added post-nemestice, 09-01-21, Sets bool this+0x57
    virtual void DESTROY() = 0;
    virtual void DESTROY2() = 0;
    virtual int GetTotalPacketBytes(int,int) = 0;
    virtual int GetTotalPacketReliableBytes(int,int) = 0;
    virtual int GetTotalPacketSomething();
    virtual void Reset(void) = 0;
    virtual void Clear(void) = 0;
    virtual void Shutdown(int ENetworkDisconnectionReason) = 0;
    virtual void SendData(void *bf_write, NetChannelBufType_t type) = 0;
    virtual void _unk3() = 0; // this is Transmit()
    virtual const char* GetRemoteAddress(void) = 0;
    virtual void _unk4() = 0;
    virtual void sub_C4AC0() = 0; // added with Road2TI10
    virtual void CanPacket() = 0;
    virtual bool IsOverflowed(void) = 0;
    virtual bool HasPendingReliableData(void) = 0;
    virtual void SetMaxBufferSize(NetChannelBufType_t type,int) = 0; // "CNetChan::SetMaxBufferSize"
    virtual void SetActiveChannel(INetChannel *) = 0;
    virtual void AttachSplitPlayer(int CSplitScreenSlot,INetChannel *) = 0;
    virtual void DetachSplitPlayer(int CSplitScreenSlot) = 0;
    virtual void SetUsesMaxRoutablePayload(bool state) = 0;
    virtual void Setup(void) = 0;
    virtual void _unk6() = 0;
    virtual void SetTimeout(float,bool) = 0;
    virtual bool IsTimedOut(void) = 0;
    virtual void SomethingTimeOut() = 0;
    virtual void SetRemoteFramerate(float,float,float) = 0;
    virtual bool IsRemoteDisconnected(void) = 0;
    virtual void SetNetMessageDispatcher(void *INetMessageDispatcher) = 0;
    virtual void GetNetMessageDispatcher(void) = 0;
    virtual void SendNetMessage(NetMessageHandle_t *messageHandle, google::protobuf::Message *message, NetChannelBufType_t type) = 0;
    virtual void StartRegisteringMessageHandlers(void) = 0;
    virtual void FinishRegisteringMessageHandlers(void) = 0;
    virtual void RegisterNetMessageHandlerAbstract();//CUtlSlot *,CUtlAbstractDelegate const&,int,NetMessageHandle_t__ *,int) = 0;
    virtual void UnregisterNetMessageHandlerAbstract();//CUtlSlot *,CUtlAbstractDelegate const&,NetMessageHandle_t__ *) = 0;
    virtual void SetChallengeNr(unsigned int) = 0;
    virtual void GetNumBitsWritten(NetChannelBufType_t type) = 0;
    virtual void SetCompressionMode(bool) = 0;
    virtual void SetMaxRoutablePayloadSize(int) = 0;
    virtual int GetMaxRoutablePayloadSize(void) = 0;
    virtual void SetDemoRecorder(void *IDemoRecorderBase) = 0;
    virtual void SetInstantReplayIntercept(void *IInstantReplayIntercept) = 0;
    virtual void SetFileTransmissionMode(bool) = 0;
    virtual bool IsNull(void) = 0;
    virtual void ProcessDemoPacket(void *NetPacket_t) = 0;
    virtual bool WasLastMessageReliable(void) = 0;
    virtual void InstallMessageFilter(void *INetworkMessageProcessingPreFilter) = 0;
    virtual void UninstallMessageFilter(void *INetworkMessageProcessingPreFilter) = 0;
    virtual void PostReceivedNetMessage(NetMessageHandle_t *, google::protobuf::Message* ,NetChannelBufType_t const*, int) = 0;
    virtual void InsertReplayMessage(void *InstantReplayMessage_t) = 0;
    virtual bool HasQueuedPackets(void) = 0;
    virtual void _unk8() = 0;
    virtual void SetPendingDisconnect(int ENetworkDisconnectionReason) = 0;
    virtual void GetPendingDisconnect(void) = 0;
    virtual void SuppressTransmit(bool) = 0;
    virtual bool IsSuppressingTransmit(void) = 0;
    virtual void unkExtra(); // steam networking socket related
    virtual bool unkExtra2(); //returns bool
};