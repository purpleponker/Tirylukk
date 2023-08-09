#pragma once
#include <string>
#include "SDL.h"
#include "components.h"
#include "engine.h"

//class for component collisions
class comp_collider_class : public component_class
{
public:
	SDL_Rect collider_dims;
	std::string comp_tag;

	trans_comp_class* transform;

	comp_collider_class(std::string t) {
		comp_tag = t;
	}

	void init() override {
		if (!entity->has_component<trans_comp_class>()) {
			entity->add_component<trans_comp_class>();
		}
		transform = &entity->get_component<trans_comp_class>();
		game_class::collider_list.push_back(this);
	}

	void update() override {
		collider_dims.x = static_cast<int>(transform->position.x_pos);
		collider_dims.y = static_cast<int>(transform->position.y_pos);
		collider_dims.w = transform->width * transform->scaler;
		collider_dims.h = transform->height * transform->scaler;
	}
};