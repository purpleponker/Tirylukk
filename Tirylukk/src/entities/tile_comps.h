#pragma once

#include "sprite_comps.h"
#include "transform_comps.h"
#include "SDL.h"
#include "entity_comps.h"


//class for map tile creations
class tile_comp_class : public component_class {
public:
	trans_comp_class* transform = NULL;
	sprite_class* sprite_text = NULL;
	SDL_Rect tile_dims = {};
	vector_2D_class position_holder = {}; //holds original position while camera moves around the map
	Uint32 tile_id = 0;

	tile_comp_class() = default;
	tile_comp_class(int x, int y, int w, int h, Uint32 tile_sprite_id) {
		tile_dims.x = x;
		tile_dims.y = y;
		tile_dims.w = w;
		tile_dims.h = h;
		tile_id = tile_sprite_id;
		tile_id = tile_sprite_id;
		position_holder.x_pos = x;
		position_holder.y_pos = y;

	}

	void update() override {
		tile_dims.x = position_holder.x_pos - game_class::camera_display.x;
		tile_dims.y = position_holder.y_pos - game_class::camera_display.y;
	}

	void init() override {
		
		entity->add_component<trans_comp_class>(static_cast<float>(tile_dims.x), static_cast<float>(tile_dims.y), tile_dims.w , tile_dims.h, 1);
		transform = &entity->get_component<trans_comp_class>();
		entity->add_component<sprite_class>(tile_id);
		sprite_text = &entity->get_component<sprite_class>();
	}
};