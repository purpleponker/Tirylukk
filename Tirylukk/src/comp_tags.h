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
	quad_1,
	quad_2,
	quad_3,
	quad_4
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

