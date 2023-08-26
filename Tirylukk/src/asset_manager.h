#pragma once

#include <map>
#include <string>
#include "textures.h"
#include "vector2D.h"
#include "comp_tags.h"
#include "entities/entity_comps.h"
#include "SDL_ttf.h"

class asset_man_class {
public:
	asset_man_class(ent_man_class* ent_man);
	~asset_man_class();
	//game object managment
	void generate_projectile(vector_2D_class position, vector_2D_class velocity, int range, int speed, collider_comp_tag asset_tag);
		

	//texture managment
	void add_texture(Uint32 asset_tag, const char * file_path);
	SDL_Texture* get_texture(Uint32 comp_tag); //comes from comp_tags.h groups

	//font managment
	void add_font(font_tag font_id, std::string file_path, int font_size);
	TTF_Font* get_font(font_tag font_id);

private:
	ent_man_class* ent_manager;
	std::map<Uint32, SDL_Texture*> texture_list;
	std::map<Uint32, TTF_Font*> font_list;
};
