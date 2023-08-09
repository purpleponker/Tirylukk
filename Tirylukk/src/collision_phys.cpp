#include "collision_phys.h"
#include "entities/comp_collider.h"

bool collision_class::AABB_collision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
	if (
		rect1.x + rect1.w >= rect2.x &&
		rect2.x + rect2.w >= rect1.x &&
		rect1.y + rect1.h >= rect2.y &&
		rect2.y + rect2.h >= rect1.y
		) {
		//add collision has happened
		return true;
	}
	else {
		return false;
	}
		
}

bool collision_class::AABB_collision(const comp_collider_class & collider1, const comp_collider_class & collider2) {
	if (AABB_collision(collider1.collider_dims, collider2.collider_dims)) {
		if (collider1.comp_tag != collider2.comp_tag) {
			std::cout << collider1.comp_tag << " collision with: " << collider2.comp_tag << std::endl;
		}
		
		return true;
	}
	else {
		return false;
	}
		
}