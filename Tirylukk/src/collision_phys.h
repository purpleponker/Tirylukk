#pragma once
#include "SDL.h"

class comp_collider_class;

class collision_class {
public:
	static bool AABB_collision(const SDL_Rect & rect1, const SDL_Rect & rect2);
	static bool AABB_collision(const comp_collider_class & collider1, const comp_collider_class & collider2);
};