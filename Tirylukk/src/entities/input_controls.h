#pragma once

#include "../engine.h"
#include "transform_comps.h"
#include "menu.h"

class input_controls_class : public component_class {
public:
	trans_comp_class* transform;
	//temp solution for player animations allowing user input for animations on character
	sprite_class* sprite;
	void init() override {
		transform = &entity->get_component<trans_comp_class>();
		sprite = &entity->get_component<sprite_class>();
	}
	void update() override {
		if (engine_class::event.type == SDL_KEYDOWN) {
			switch (engine_class::event.key.keysym.sym)
			{
			
				case SDLK_w:
					transform->velocity.y_pos = -1;
					sprite->play_animation("walk");
					break;
				case SDLK_a:
					transform->velocity.x_pos = -1;
					sprite->play_animation("walk");
					sprite->sprite_flip = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_d:
					transform->velocity.x_pos = 1;
					sprite->play_animation("walk");
					break; 
				case SDLK_s:
					transform->velocity.y_pos = 1;
					sprite->play_animation("walk");
					break;
				default:
					break;
			}
		}

		if (engine_class::event.type == SDL_KEYUP) {
			switch (engine_class::event.key.keysym.sym)
			{

			case SDLK_w:
				transform->velocity.y_pos = 0;
				sprite->play_animation("idle");
				break;
			case SDLK_a:
				transform->velocity.x_pos = 0;
				sprite->play_animation("idle");
				sprite->sprite_flip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->velocity.x_pos = 0;
				sprite->play_animation("idle");
				break;
			case SDLK_s:
				transform->velocity.y_pos = 0;
				sprite->play_animation("idle");
				break;
			case SDLK_ESCAPE:
				engine_class::is_running = false;
			default:
				break;
			}
		}
	}
};