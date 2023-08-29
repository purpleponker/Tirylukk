#pragma once
#include "SDL.h"
#include <map>
#include "vector2D.h"


class comp_collider_class;

class collision_class {
public:
	//consider making another AABB collision with a reduction of 1 rects size by an off set for less strict collision detection
	//thinking about player collision in future with weapon swings need a way to extend or reduce hit boxes for weapons with reach
	static bool AABB_collision(const SDL_Rect & rect1, const SDL_Rect & rect2);
	static bool AABB_collision(const comp_collider_class & collider1, const comp_collider_class & collider2);
	
	static void rebound_vector(const SDL_Rect& rect1, const SDL_Rect& rect2, vector_2D_class& pos_modifer);
	//new rebound might replace
	static void rebound_pos_vector(float rebound_angle, vector_2D_class& pos_modifer);
private:
	
};