#pragma once
#include "transform_comps.h"
#include "SDL.h"
#include "../textures.h"
#include "animations.h"
#include "../engine.h"
#include <map>
#include "../asset_manager.h"

class game_class;

class sprite_class : public component_class {
public:

	//animation public members
	int animation_index = 0;
	SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;	
	std::map<const char*, animation> animations;

	sprite_class() = default;
	
	//static sprites
	sprite_class(Uint32 asset_tag) {
		set_texture(asset_tag);
	}

	//animated sprites
	sprite_class(Uint32 asset_tag, bool src_is_animated) {
		is_animated = src_is_animated;
		animation idle_anim = animation(0, 3, 100); //index 0, 3 frames, 100 ms speed delay
		animation walk_anim = animation(1, 8, 100);

		animations.emplace("idle", idle_anim);
		animations.emplace("walk", walk_anim);
		set_texture(asset_tag);
	}

	~sprite_class() {
	}

	//functions to change texture of component
	void set_texture(Uint32 asset_tag) {
		texture = engine_class::asset_manager->get_texture(asset_tag);
	}

	//initialize texture size and position
	void init() override {

		transform = &entity->get_component<trans_comp_class>();
		src_rect.x = src_rect.y = 0;
		src_rect.w = transform->width;
		src_rect.h = transform->height;

	}

	//update texture postion
	void update() override {
		//animate sprites if needed
		if (is_animated) {
			src_rect.x = src_rect.w * static_cast<int>((SDL_GetTicks() / animation_speed_delay) % animation_frames);
		}

		src_rect.y = animation_index * transform->height;
		//then update position vectors
		dest_rect.x = static_cast<int>(transform->position.x_pos) - engine_class::camera_display.x;
		dest_rect.y = static_cast<int>(transform->position.y_pos) - engine_class::camera_display.y;
		dest_rect.w = transform->width * transform->scaler;
		dest_rect.h = transform->height * transform->scaler;
	}

	//draw texture for rendering to in game display 
	void draw() override {
		texture_class::draw_texture(texture, src_rect, dest_rect, sprite_flip);
	}

	//animated sprites
	void play_animation(const char* animation_name) {
		animation_frames = animations[animation_name].num_frames;
		animation_index = animations[animation_name].index;
		animation_speed_delay = animations[animation_name].animation_speed;
	}

private:
	trans_comp_class * transform;
	SDL_Texture* texture;
	SDL_Rect src_rect, dest_rect;
	
	//for animated sprites, default vals
	bool is_animated = false;
	int animation_frames = 1;
	int animation_speed_delay = 100; //measured in ms
};
