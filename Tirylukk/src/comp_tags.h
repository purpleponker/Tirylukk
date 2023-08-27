#pragma once

//for rendering all the assets in layers in the render display func of engine
enum group_ids : Uint32{
	null_group,
	map_group,
	players_group,
	npcs_group,
	enemies_group,
	colliders_group,
	equipment_group,
	object_group,
	placeable_group,
	resource_group,
	projectile_group,
};

//for asset textures and collisions primarily
enum collider_comp_tag : Uint32 {
	player_tag,
	terrain_tag,
	npc_tag,
	object_tag,
	projectile_tag,
	interactable_tag,
	border_tag,
};

//for different tile asset ids for matching correct textures
enum tile_tag : Uint32 {
	null_tag,
	dirt_tag,
	grass_tag,
	water_tag,
};

//for collisions physics engine to determine the location of collisions on hit boxes
//based on boat directions for Congruity
enum collision_loc_tag : Uint32 {
	null_loc,
	//5 quads per side see no reason to add more
	left_top_edge_tag,
	top_mid_left_tag,
	top_mid_tag,
	top_mid_right_tag,
	right_top_edge_tag,
	left_mid_uppper_tag,
	left_mid_tag,
	left_mid_low_tag,
	right_mid_upper_tag,
	right_mid_tag,
	right_mid_low_tag,
	left_bot_edge_tag,
	bot_mid_left_tag,
	bot_mid_tag,
	bot_mid_right_tag,
	right_bot_edge_tag,
	//for 3 quadrants per side
	left_tag,		//port
	right_tag,		//starboard
	top_tag,		//bow
	bottom_tag,		//stern
	left_top_tag,	//etc.
	left_bottom_tag,
	right_top_tag,
	right_bottom_tag,
	//for 2 quads per side
	diag_left_top_tag,
	diag_right_top_tag,
	diag_left_bot_tag,
	diag_right_bot_tag,
	//for 1 quad IE the whole rect
	center_tag
};

//font types for asset managment
enum font_tag : Uint32 {
	font_1,
	font_2,
	font_3,
	font_4
};

//for menu buttons and clicks
enum button_tag : Uint32 {
	exit_button,
	resume_button,
	sub_menu_1,
	sub_menu_2,
	sub_menu_3,
	sub_menu_4,
	settings_button,
	controls_button,

};

