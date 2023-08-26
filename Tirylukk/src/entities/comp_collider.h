#pragma once
#include <string>
#include "SDL.h"
#include "components.h"
#include "engine.h"
#include "../textures.h"
#include "../comp_tags.h"


//class for component collisions
class comp_collider_class : public component_class
{
public:
	SDL_Rect collider_dims = {};
	collider_comp_tag comp_tag;
	Uint32 collision_loc = null_loc;

	//display collision texutures 1 layer above map tile textures
	SDL_Texture * obj_texture = NULL;
	SDL_Rect src_rect, dest_rect = {};

	trans_comp_class* transform = NULL;

	//constructors for making colliders
	comp_collider_class(collider_comp_tag t) {
		comp_tag = t;
	}

	comp_collider_class(collider_comp_tag t, int x_pos, int y_pos, int obj_size) {
		comp_tag = t;
		collider_dims.x = x_pos;
		collider_dims.y = y_pos;
		collider_dims.w = collider_dims.h = obj_size;
	}

	void init() override {
		if (!entity->has_component<trans_comp_class>()) {
			entity->add_component<trans_comp_class>();
		}

		transform = &entity->get_component<trans_comp_class>();

		//load colliding world object and tile/terrain textures
		engine_class::asset_manager->add_texture(border_tag, "assets/border_marker_32x32.png");
		obj_texture = engine_class::asset_manager->get_texture(border_tag);
		src_rect = { 0,0,32,32 };
		dest_rect = { collider_dims.x, collider_dims.y, collider_dims.w, collider_dims.h };
		
	}

	void update() override {
		//skip over colliders with no transform component, otherwise they all stack at (0,0)
		if (comp_tag != terrain_tag) {
			collider_dims.x = static_cast<int>(transform->position.x_pos);
			collider_dims.y = static_cast<int>(transform->position.y_pos);
			collider_dims.w = transform->width * transform->scaler;
			collider_dims.h = transform->height * transform->scaler;
		}

		dest_rect.x = collider_dims.x - engine_class::camera_display.x;
		dest_rect.y = collider_dims.y - engine_class::camera_display.y;
	}

	//draw layer 1: object collider above layer 0: map tiles
	void draw() override {
		texture_class::draw_texture(obj_texture, src_rect, dest_rect, SDL_FLIP_NONE);

	}
};