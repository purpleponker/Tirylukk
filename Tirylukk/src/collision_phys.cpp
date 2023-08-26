#include "collision_phys.h"
#include "entities/comp_collider.h"


bool collision_class::AABB_collision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
	if (
		rect1.x + rect1.w >= rect2.x &&
		rect2.x + rect2.w >= rect1.x &&
		rect1.y + rect1.h >= rect2.y &&
		rect2.y + rect2.h >= rect1.y
		) {
		//collision has happened, return true
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

Uint32 collision_class::get_col_loc(const SDL_Rect& rect1, const SDL_Rect& rect2, int quad_count_1, int quad_count_2) {
	std::map<Uint32, SDL_Rect> grid_1;
	std::map<Uint32, SDL_Rect> grid_2;
	Uint32 loc_tag_1 = null_loc;
	Uint32 loc_tag_2 = null_loc;
		
	//matching quadrant sizes, speculated use for terrain/object/npc collisions, original implementation other cases are just for future proofing
	//rect.x and rect.y are top left of rect by SDL definition
	if (quad_count_1 = quad_count_2) {
		switch (quad_count_1)
		{
		//only 1 quad, whole rect
		case 1: {
			break;
		}
		//2 quads per side
		case 2: {
			//rect 1 is right/even of rect2
			if (rect1.x >= rect2.x) {
				//rect1 is below/even rect2
				if (rect1.y >= rect2.y) {
					loc_tag_1 = diag_left_top_tag; //rect1 is right and below rect2 so rect1 collision is top left, rect2 is bottom right
					loc_tag_2 = diag_right_bot_tag;
				}
				//rect1 is above rect2
				else {
					loc_tag_1 = diag_left_bot_tag; //rect1 is left and above rect2 so rect1 collision is top right, rect2 is bottom left
					loc_tag_2 = diag_right_top_tag;
				}
			}
			//rect1 is left of rect2
			else {
				//rect1 is below/even rect2
				if (rect1.y >= rect2.y) {
					loc_tag_1 = diag_right_top_tag;
					loc_tag_2 = diag_left_bot_tag;
				}
				//rect1 is above rect2
				else {
					loc_tag_1 = diag_right_bot_tag;
					loc_tag_2 = diag_left_top_tag;
				}
			}

			break;
		}
		//3 quads per side
		case 3: {
			break;
		}
		//5 quads per side
		case 5: {
			break;
		}
		default:
			break;
		}
	}
	//more quadrants in rect1, speculated use for projectile collisions on player or maybe location damage in the future
	else if (quad_count_1 > quad_count_2) {
		//since rect 1 has more quads base collision location detection on first rect
		switch (quad_count_1)
		{
			//only 1 quad, whole rect
		case 1: {
			break;
		}
			  //2 quads per side
		case 2: {
			break;
		}
			  //3 quads per side
		case 3: {
			break;
		}
			  //5 quads per side
		case 5: {
			break;
		}
		default:
			break;
		}

	}
	//last case: rect1 has less quadrants than rect2, speculated use for player attacks on others
	else {
		//since rect 2 has more quads base collision location detection on second rect
		switch (quad_count_2)
		{
			//only 1 quad, whole rect
		case 1: {
			break;
		}
			  //2 quads per side
		case 2: {
			break;
		}
			  //3 quads per side
		case 3: {
			break;
		}
			  //5 quads per side
		case 5: {
			break;
		}
		default:
			break;
		}

	}	
	return loc_tag_1;
}

//determine the rebound modifier for postion vector based on collision location
void collision_class::rebound_pos_vector(Uint32 collision_tag, vector_2D_class& pos_modifier) {
	switch (collision_tag)
	{		
	//5 quads per side tags
	case left_top_edge_tag: {
		break;
	}
	case top_mid_left_tag: {
		break;
	}
	case top_mid_tag: {
		break;
	}
	case top_mid_right_tag: {

	}
	case right_top_edge_tag: {
		break;
	}
	case left_mid_uppper_tag: {
		break;
	}
	case left_mid_tag: {
		break;
	}
	case left_mid_low_tag: {
		break;
	}
	case right_mid_upper_tag: {

	}
	case right_mid_tag: {
		break;
	}
	case right_mid_low_tag: {
		break;
	}
	case left_bot_edge_tag: {
		break;
	}
	case bot_mid_left_tag: {
		break;
	}
	case bot_mid_tag: {
		break;
	}
	case bot_mid_right_tag:{
		break;
	}
	case right_bot_edge_tag: {
		break;
	}
	//for 3 quadrants per side tags
	case left_tag: {
		break;
	}
	case right_tag: {
		break;
	}
	case top_tag: {
		break;
	}
	case bottom_tag: {
		break;
	}
	case left_top_tag: {
		break;
	}
	case left_bottom_tag: {
		break;
	}
	case right_top_tag: {
		break;
	}
	case right_bottom_tag: {
		break;
	}
	//for 2 quads per side tags
	case diag_left_top_tag: {
		pos_modifier.x_pos = 1;
		pos_modifier.y_pos = 1;
		break;
	}
	case diag_right_top_tag: {
		pos_modifier.x_pos = -1;
		pos_modifier.y_pos = 1;
		break;
	}
	case diag_left_bot_tag: {
		pos_modifier.x_pos = 1;
		pos_modifier.y_pos = -1;
		break;
	}
	case diag_right_bot_tag: {
		pos_modifier.x_pos = -1;
		pos_modifier.y_pos = -1;
		break;
	}
	//for 1 quad IE the whole rect tag
	case center_tag: {
		break;
	}

	default:
		break;
	}
}