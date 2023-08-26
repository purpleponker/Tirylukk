#include "asset_manager.h"
//constructors/destructors

asset_man_class::asset_man_class(ent_man_class * ent_man) : ent_manager(ent_man) {

}

asset_man_class::~asset_man_class() {

}

//add texture to mapping list
void asset_man_class::add_texture(Uint32 asset_tag, const char* file_path) {
	texture_list.emplace(asset_tag, texture_class::load_texture(file_path));
}

//retrive a texture pointer from the mapping list
SDL_Texture* asset_man_class::get_texture(Uint32 asset_tag) {
	return texture_list[asset_tag];
}