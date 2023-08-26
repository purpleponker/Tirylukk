#pragma once

#include "entity_comps.h"
#include "components.h"
#include "../vector2D.h"

class projectile_class : public component_class {
public:
	projectile_class(int src_range, int src_speed, vector_2D_class src_velocity) : range(src_range), speed(src_speed), velocity(src_velocity) {
		displacement = 0;
	}

	~projectile_class() {}

	void init() override{
		transform = &entity->get_component<trans_comp_class>();
		transform->velocity = velocity;
	}

	void update() override{
		//update projitile distance traveled
		displacement += speed;
		//destroy projectile after reaching end of range or exceeding a certain distance from camera display using 2 time witch atm
		if (displacement > range) {
			entity->destroy();
		}
		else if (transform->position.x_pos > engine_class::camera_display.x + (engine_class::camera_display.w * 2) || transform->position.x_pos < engine_class::camera_display.x ||
				 transform->position.y_pos > engine_class::camera_display.y + (engine_class::camera_display.h * 2) || transform->position.y_pos < engine_class::camera_display.y) {
			entity->destroy();
		}
		
	}

private:
	trans_comp_class* transform;
	vector_2D_class velocity;
	int range, speed, displacement;
};