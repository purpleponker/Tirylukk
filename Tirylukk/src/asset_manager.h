#pragma once

#include <map>
#include <string>
#include "textures.h"
#include "vector2D.h"
#include "comp_tags.h"
#include "entities/entity_comps.h"

class asset_man_class {
public:
	asset_man_class(ent_man_class* ent_man);
	~asset_man_class();

	void add_texture(Uint32 asset_tag, const char * file_path);
	SDL_Texture* get_texture(Uint32 comp_tag); //comes from comp_tags.h groups
private:
	ent_man_class* ent_manager;
	std::map<Uint32, SDL_Texture*> texture_list;
};
