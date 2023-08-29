#pragma once
#include "entity_comps.h"
#include "../vector2D.h"
class trans_comp_class : public component_class {
public:

	vector_2D_class position;
	vector_2D_class velocity;
	vector_2D_class acceleration;
	
	//speed was replace by acceleration vector hold for furture in case
	int speed = 5;
	
	//all component texture/sprite assets must be 32x32 pixels canvas to redner properly, scaler helps make them larger
	//this might change later but for now 32x32 is required to display properly, adding vars which can read file dims could help in future
	//for larger images
	int height = 32;
	int width = 32;
	int scaler = 1;

	//initialize position values
	trans_comp_class() {
		position.zero();
	}
	//add entity default position with scaler
	trans_comp_class(int scale_val) {
		position.x_pos = 2500;
		position.y_pos = 2500;
		scaler = scale_val;
	}

	//add entity position
	trans_comp_class(float x, float y) {
		position.x_pos = x;
		position.y_pos = y;
	}

	//add entity with size and position and scaler
	trans_comp_class(float x, float y, int h, int w, int scale_val) {
		position.x_pos = x;
		position.y_pos = y;
		width = w;
		height = h;
		scaler = scale_val;
	}

	//initialize override
	void init() override {
		velocity.zero();
		acceleration.x_pos = acceleration.y_pos = 5;
	}

	//update player position based on velocity and acceleration
	void update() override {
		position.x_pos += velocity.x_pos * acceleration.x_pos;
		position.y_pos += velocity.y_pos * acceleration.y_pos;
	}
	

private:


};
