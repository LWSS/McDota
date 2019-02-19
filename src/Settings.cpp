#include "Settings.h"

#include "Utils/Util_sdk.h"
#include "Interfaces.h"

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

	mc_camera_pitch_add = Util::RegisterConVar( "mc_camera_pitch_add", "0.0", 136, NULL, true, -1.0f, true, 360.0f );
	mc_camera_yaw_add = Util::RegisterConVar( "mc_camera_yaw_add", "0.0", 136, NULL, true, 0.0f );

	mc_camera_distance = Util::RegisterConVar( "mc_camera_distance", "1134.0", 136, NULL, true, 0.0f );

	mc_fog_disable = Util::RegisterConVar( "mc_fog_disable", "false" );
	mc_fow_disable = Util::RegisterConVar( "mc_fow_disable", "false" );
	mc_autoaccept_on = Util::RegisterConVar( "mc_autoaccept_on", "false" );

	mc_airstuck_on = Util::RegisterConVar( "mc_airstuck_on", "false" );
	mc_command_repeater = Util::RegisterConVar( "mc_command_repeater", "true" );

	mc_ent_select = Util::RegisterConVar( "mc_ent_select", "1" );

	mc_log_createmove = Util::RegisterConVar( "mc_log_createmove", "false" );
	mc_log_clientevents = Util::RegisterConVar( "mc_log_clientevents", "false" );
	mc_log_sendnetmsg = Util::RegisterConVar( "mc_log_sendnetmsg", "false" );
	mc_log_sendnetmsg_filter_commons = Util::RegisterConVar( "mc_log_sendnetmsg_filter_commons", "true" );
	mc_log_prepareunitorders = Util::RegisterConVar( "mc_log_prepareunitorders", "false" );
	mc_log_runscript = Util::RegisterConVar( "mc_log_runscript", "false" );

	mc_raw_command = Util::RegisterConVar( "mc_raw_command", "say wow!" );
	mc_cmd_src = Util::RegisterConVar( "mc_cmd_src", "0" );
	mc_end_createmove = Util::RegisterConVar( "mc_end_createmove", "false" );
	mc_send_voice = Util::RegisterConVar( "mc_send_voice", "false" );
	mc_send_freq = Util::RegisterConVar( "mc_send_freq", "25" );
	mc_send_status = Util::RegisterConVar( "mc_send_status", "false" );

	mc_retarget_orders = Util::RegisterConVar( "mc_retarget_orders", "false" );
    mc_allow_customnames = Util::RegisterConVar( "mc_allow_customnames", "false" );
    mc_custom_str = Util::RegisterConVar( "mc_custom_str", "#as Mars (Lvl 25)" );

	for ( ConCommandBase *var : Util::createdConvars ) {
		if( !cvar->FindVar(var->name) ){
			MC_PRINTF_ERROR("Error Finding created Var: %s\n", var->name);
			return false;
		}
	}
	return true;
}