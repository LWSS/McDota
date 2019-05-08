#pragma once

#include "SDK/Convar.h"

/* Namespace is kinda annoying for these */
inline ConVar *mc_esp_type_bbox;
inline ConVar *mc_esp_type_absbox;
inline ConVar *mc_esp_type_rbox;
inline ConVar *mc_esp_type_entbounds;
inline ConVar *mc_esp_type_entattachments;
inline ConVar *mc_esp_type_entjointinfo;
inline ConVar *mc_esp_type_entskele;
inline ConVar *mc_esp_type_enthitboxes;
inline ConVar *mc_esp_type_entviewoffset;
inline ConVar *mc_esp_type_infotext;

inline ConVar *mc_esp_filter_all;
inline ConVar *mc_esp_filter_heroes_friend;
inline ConVar *mc_esp_filter_heroes_friend_seenby_enemy;
inline ConVar *mc_esp_filter_heroes_enemy;
inline ConVar *mc_esp_filter_creeps_friend;
inline ConVar *mc_esp_filter_creeps_enemy;
inline ConVar *mc_esp_filter_illusions_enemy;

inline ConVar *mc_camera_pitch_add;
inline ConVar *mc_camera_yaw_add;
inline ConVar *mc_camera_distance;

inline ConVar *mc_fog_disable;
inline ConVar *mc_fow_disable;
inline ConVar *mc_autoaccept_on;
inline ConVar *mc_airstuck_on;
inline ConVar *mc_command_repeater;
inline ConVar *mc_ent_select;

inline ConVar *mc_log_createmove;
inline ConVar *mc_log_clientevents;
inline ConVar *mc_log_sendnetmsg;
inline ConVar *mc_log_sendnetmsg_filter_commons;
inline ConVar *mc_log_prepareunitorders;
inline ConVar *mc_log_runscript;

inline ConVar *mc_raw_command;
inline ConVar *mc_cmd_src;
inline ConVar *mc_end_createmove;

inline ConVar *mc_send_voice;
inline ConVar *mc_send_freq;
inline ConVar *mc_send_status;

inline ConVar *mc_retarget_orders;
inline ConVar *mc_allow_customnames;
inline ConVar *mc_custom_str;
inline ConVar *mc_custom_int;


namespace Settings
{
	bool RegisterCustomConvars();
}
