#include "asset_manager.h"
#include "entities/components.h"
//constructors/destructors

asset_man_class::asset_man_class(ent_man_class * ent_man) : ent_manager(ent_man) {

}

asset_man_class::~asset_man_class() {

}
//*****************projectiles*******************
//projectile generation
void asset_man_class::generate_projectile(vector_2D_class pos, vector_2D_class src_velocity,  int src_range, int src_speed, collider_comp_tag asset_tag) {
	auto& projectile(ent_manager->add_entity());
	projectile.add_component<trans_comp_class>(pos.x_pos, pos.y_pos, 32, 32, 1); //32x32 pixels scale 1 manage better later to avoid hard code
	projectile.add_component<sprite_class>(asset_tag); //comp_tag and animation flag if needed
	projectile.add_component<projectile_class>(src_range, src_speed, src_velocity);
	projectile.add_component<comp_collider_class>(asset_tag);
	projectile.add_to_group(projectile_group);
}

//*****************textures*******************
//add texture to mapping list
void asset_man_class::add_texture(Uint32 asset_tag, const char* file_path) {
	texture_list.emplace(asset_tag, texture_class::load_texture(file_path));
}

//retrive a texture pointer from the mapping list
SDL_Texture* asset_man_class::get_texture(Uint32 asset_tag) {
	return texture_list[asset_tag];
}

//*****************fonts*******************
//add font to mapping list
void asset_man_class::add_font(font_tag font_id, std::string file_path, int font_size) {
	font_list.emplace(font_id, TTF_OpenFont(file_path.c_str(), font_size));
}

//retrieve specified font
TTF_Font* asset_man_class::get_font(font_tag font_id) {
	return font_list[font_id];
}

//add menu texture path to mapping list
void asset_man_class::add_menu(menu_tag menu_id, std::string file_path, font_tag font_id) {
	auto& menu(ent_manager->add_entity());
	menu.add_component<menu_class>(menu_id, file_path, font_id);
	menu.add_to_group(projectile_group); //maybe used for party menus, IE character inventories in a party for example


	//menu_list.emplace();
}
