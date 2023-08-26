#pragma once
#include "SDL.h"
#include <map>
#include "vector2D.h"


class comp_collider_class;

class collision_class {
public:
	static bool AABB_collision(const SDL_Rect & rect1, const SDL_Rect & rect2);
	static bool AABB_collision(const comp_collider_class & collider1, const comp_collider_class & collider2);
	
	//considered makin it private but not sure if better as public and called from engine as opposed to bein called within AABB_coll func
	//if hit box reg gets wacky check to make sure quad count and cell count are resonable to contruct a grid in this func
	static Uint32 get_col_loc(const SDL_Rect& rect1, const SDL_Rect& rect2, int quadrant_1, int quadrant_2); //cell count is total, quad is per side
	static void rebound_pos_vector(Uint32 collision_tag, vector_2D_class& pos_modifer);
private:
	
};