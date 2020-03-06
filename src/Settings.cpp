#include "Settings.h"

#include "Hooks/HardHooks.h"
#include "Utils/Util_sdk.h"
#include "Interfaces.h"
#include "Utils/Logger.h"

void CC_GC_Client_Recv( ConVar*, const char *, float )
{
	if( mc_log_GC_client_recv->GetBool() ){
		MC_LOGF("Installing HardHook- Client GC Recv\n");
		HardHooks::DispatchPacket.Install( (void*)DispatchPacketFnAddr, (void*)HardHooks::MyDispatchPacket );
	} else {
		MC_LOGF("Removing HardHook - Client GC Recv");
		HardHooks::DispatchPacket.Remove();
	}
}

void CC_GC_Client_Send( ConVar*, const char *, float )
{
	MC_LOGF("GC Send convar changed!(%d)\n", mc_log_GC_client_send ->GetInt());
	if( mc_log_GC_client_send->GetBool() ){
		MC_LOGF("Installing HardHook - Client GC Recv\n");
		HardHooks::BAsyncSendProto.Install( (void*)BAsyncSendProtoFnAddr, (void*)HardHooks::MyBAsyncSendProto );
	} else {
		MC_LOGF("Removing HardHook - Client GC Send\n");
		HardHooks::BAsyncSendProto.Remove();
	}
}

/* ConVars are guaranteed to exist after this function */
bool Settings::RegisterCustomConvars( ) {

	mc_esp_type_bbox = Util::RegisterConVar( "mc_esp_type_bbox", "false" );
	mc_esp_type_absbox = Util::RegisterConVar( "mc_esp_type_absbox", "false" );
	mc_esp_type_rbox = Util::RegisterConVar( "mc_esp_type_rbox", "false" );
	mc_esp_type_entbounds = Util::RegisterConVar( "mc_esp_type_entbounds", "false" );
	mc_esp_type_entattachments = Util::RegisterConVar( "mc_esp_type_entattachments", "false" );
	mc_esp_type_entjointinfo = Util::RegisterConVar( "mc_esp_type_entjointinfo", "false" );
	mc_esp_type_entskele = Util::RegisterConVar( "mc_esp_type_entskele", "false" );
	mc_esp_type_enthitboxes = Util::RegisterConVar( "mc_esp_type_enthitboxes", "false" );
	mc_esp_type_entviewoffset = Util::RegisterConVar( "mc_esp_type_entviewoffset", "false" );
	mc_esp_type_infotext = Util::RegisterConVar( "mc_esp_type_infotext", "false" );

	mc_esp_filter_all = Util::RegisterConVar( "mc_esp_filter_all", "true" );
	mc_esp_filter_heroes_friend = Util::RegisterConVar( "mc_esp_filter_heroes_friend", "false" );
	mc_esp_filter_heroes_friend_seenby_enemy = Util::RegisterConVar( "mc_esp_filter_heroes_friend_seenby_enemy", "false" );
	mc_esp_filter_heroes_enemy = Util::RegisterConVar( "mc_esp_filter_heroes_enemy", "false" );
	mc_esp_filter_creeps_friend = Util::RegisterConVar( "mc_esp_filter_creeps_friend", "false" );
	mc_esp_filter_creeps_enemy = Util::RegisterConVar( "mc_esp_filter_creeps_enemy", "false" );
	mc_esp_filter_illusions_enemy = Util::RegisterConVar( "mc_esp_filter_illusions_enemy", "false" );

	mc_camera_pitch_add = Util::RegisterConVar( "mc_camera_pitch_add", "0.0", 136, nullptr, true, -1.0f, true, 360.0f );
	mc_camera_yaw_add = Util::RegisterConVar( "mc_camera_yaw_add", "0.0", 136, nullptr, true, 0.0f );
	mc_camera_distance = Util::RegisterConVar( "mc_camera_distance", "1200.0", 136, nullptr, true, 0.0f );

	mc_fog_disable = Util::RegisterConVar( "mc_fog_disable", "false" );
	mc_fow_disable = Util::RegisterConVar( "mc_fow_disable", "false" );
	mc_autoaccept_on = Util::RegisterConVar( "mc_autoaccept_on", "false" );

	mc_airstuck_on = Util::RegisterConVar( "mc_airstuck_on", "false" );

	mc_log_createmove = Util::RegisterConVar( "mc_log_createmove", "false" );
	mc_log_clientevents = Util::RegisterConVar( "mc_log_clientevents", "false" );
	mc_log_sendnetmsg = Util::RegisterConVar( "mc_log_sendnetmsg", "false" );
	mc_log_sendnetmsg_to_string = Util::RegisterConVar( "mc_log_sendnetmsg_to_string", "false" );
	mc_log_sendnetmsg_filter_commons = Util::RegisterConVar( "mc_log_sendnetmsg_filter_commons", "false" );
	mc_log_recvnetmsg = Util::RegisterConVar( "mc_log_recvnetmsg", "false" );
	mc_log_recvnetmsg_to_string = Util::RegisterConVar( "mc_log_recvnetmsg_to_string", "false" );
    mc_log_recvnetmsg_filter_commons = Util::RegisterConVar( "mc_log_recvnetmsg_filter_commons", "false" );
	mc_log_runscript = Util::RegisterConVar( "mc_log_runscript", "false" );
	mc_log_GC_client_recv = Util::RegisterConVar( "mc_log_GC_client_recv", "false" );
	mc_log_GC_client_send = Util::RegisterConVar( "mc_log_GC_client_send", "false" );

	if( !mc_log_GC_client_recv->AddChangeCallback( CC_GC_Client_Recv ) ){
		MC_LOGF("Failed to add Change Callback for GC Client Recv\n");
		return false;
	}
	if( !mc_log_GC_client_send->AddChangeCallback( CC_GC_Client_Send ) ){
		MC_LOGF("Failed to add Change Callback for GC Client Send\n");
		return false;
	}

    mc_mute_creeps = Util::RegisterConVar( "mc_mute_creeps", "false" );
	mc_end_createmove = Util::RegisterConVar( "mc_end_createmove", "false" );
	mc_crash_server = Util::RegisterConVar( "mc_crash_server", "false" );

	mc_anti_mute = Util::RegisterConVar( "mc_anti_mute", "false" );
	mc_hide_tips = Util::RegisterConVar( "mc_hide_tips", "false" );
	mc_send_voice = Util::RegisterConVar( "mc_send_voice", "false" );
	mc_send_freq = Util::RegisterConVar( "mc_send_freq", "25" );
	mc_send_status = Util::RegisterConVar( "mc_send_status", "false" );
	mc_stall_connect = Util::RegisterConVar( "mc_stall_connect", "false" );

    mc_custom_str = Util::RegisterConVar( "mc_custom_str", "#as Mars (Lvl 25)" );
	mc_custom_str_alt = Util::RegisterConVar( "mc_custom_str_alt", "test123" );
	mc_custom_int = Util::RegisterConVar( "mc_custom_int", "1" );
	mc_custom_int_alt = Util::RegisterConVar( "mc_custom_int_alt", "1" );
    mc_custom_bool = Util::RegisterConVar( "mc_custom_bool", "1" );
    mc_custom_bool_alt = Util::RegisterConVar( "mc_custom_bool_alt", "1" );

	for ( ConCommandBase *var : Util::createdConvars ) {
		if( !cvar->FindVar(var->m_pszName) ){
			MC_PRINTF_ERROR("Error Finding created Var: %s\n", var->m_pszName);
			return false;
		}
	}
	return true;
}