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

Uint32 collision_class::get_col_loc(const SDL_Rect& rect1, const SDL_Rect& rect2, int cell_count_1, int cell_count_2, int quad_count_1, int quad_count_2) {
	std::map<Uint32, SDL_Rect> grid_1;
	std::map<Uint32, SDL_Rect> grid_2;
	Uint32 loc_tag_1 = null_loc;
	Uint32 loc_tag_2 = null_loc;
	
	//populate vector for grid 1
	build_quad_grid(grid_1, rect1, cell_count_1, quad_count_1);
	//populate vector for grid 2
	build_quad_grid(grid_2, rect2, cell_count_2, quad_count_2);
	
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

void collision_class::build_quad_grid(std::map<Uint32, SDL_Rect> & grid, const SDL_Rect& rect, const int cell_count, const int quad_count) {
	int cell_per_quad = sqrt(cell_count) / quad_count; //sqrt(cell_count) ie cell units per side divided by quad count shows cells per quad per side
	int grid_cell_height = (rect.h) / (cell_count); //height of a single grid cell
	int grid_cell_width = (rect.w) / (cell_count); //width of single grid cell

	SDL_Rect temp_rect;

	for (int i = 1; i < cell_count + 1; i++) {
		//is quads per side, note that corners are shared
		switch (quad_count)
		{
			//1 quad for whole rect, used for small rects like projectiles
		case 1: {
			//emplace to vector 1 rect of size and position of the src rect, skip the rest
			switch (i) {
			case 0: {
				grid.emplace(center_tag, rect);
				break;
			}
			default:
				break;
			}
			break;
		}
			  //2 quads per side, EX: diag_top_left, diag_top_right
		case 2: {
			//determine which quad the cell is in
			switch (i) {
			//quad 1
			case 1: {
				temp_rect.x = rect.x;
				temp_rect.y = rect.y;
				temp_rect.w = grid_cell_width;			//consider removing all temp_rect.w and temp_rect.h assignments from switchs and do it below when declared as it never changes, at least for now
				temp_rect.h = grid_cell_height;
				grid.emplace(diag_left_top_tag, temp_rect);
				break;
			}
			//qaud2
			case 2: {
				temp_rect.x = rect.x + grid_cell_width;
				temp_rect.y = rect.y;
				temp_rect.w = grid_cell_width;
				temp_rect.h = grid_cell_height;
				grid.emplace(diag_right_top_tag, temp_rect);
				break;
			}
			//quad 3
			case 3: {
				temp_rect.x = rect.x;
				temp_rect.y = rect.y + grid_cell_height;
				temp_rect.w = grid_cell_width;
				temp_rect.h = grid_cell_height;
				grid.emplace(diag_left_bot_tag, temp_rect);
				break;
			}
			//quad 4
			case 4: {
				temp_rect.x = rect.x + grid_cell_width;
				temp_rect.y = rect.y + grid_cell_height;
				temp_rect.w = grid_cell_width;
				temp_rect.h = grid_cell_height;
				grid.emplace(diag_right_bot_tag, temp_rect);
				break;
			}
			default:
				break;
			}
			break;
		}
		//for cases 3 and 5 cells in center of src rect are ignored for now, only interesteed in the border cells
		/*
			quad break downfor 3 and 5, can be expanded if I decide its worth adding more quads configs greater than 5

			EX: 3		EX5:
			*1,*2,*3	*01,*02,*03,*04,*05
			*4,05,*6	*06, 07, 08, 09,*10
			*7,*8,*9	*11, 12, 13, 14,*15
						*16, 17, 18, 19,*20
						*21,*22,*23,*24,*25
		quads with* are border quads we care about
		 determine which quad a cell is in by taking (quad_per_side * quad_number)
		*/
		//3 quads per side, EX: top_left, top, top_right
		case 3: {
			//determine which quad the cell is in
			switch (i) {
			//quad 1
			case 1: {

				temp_rect.x = rect.x;
				temp_rect.y = rect.y;
				temp_rect.w = grid_cell_width;
				temp_rect.h = grid_cell_height;
				grid.emplace(left_top_tag, temp_rect);
				break;
			}
			//qaud2
			case 2: {

				temp_rect.x = rect.x + grid_cell_width;
				temp_rect.y = rect.y;
				temp_rect.w = grid_cell_width;
				temp_rect.h = grid_cell_height;
				grid.emplace(top_tag, temp_rect);
				break;
			}
			//quad 3
			case 3: {
				temp_rect.x = rect.x + (2 * grid_cell_height);
				temp_rect.y = rect.y;
				temp_rect.w = grid_cell_width;
				temp_rect.h = grid_cell_height;
				grid.emplace(right_top_tag, temp_rect);
				break;
			}
			//quad 4
			case 4: {
				temp_rect.x = rect.x;
				temp_rect.y = rect.y + grid_cell_height;
				temp_rect.w = grid_cell_width;
				temp_rect.h = grid_cell_height;
				grid.emplace(left_tag, temp_rect);
				break;
			}
			 //qaud6
			case 6: {
				temp_rect.x = rect.x + (2 * grid_cell_width);
				temp_rect.y = rect.y + grid_cell_height;
				temp_rect.w = grid_cell_width;
				temp_rect.y = grid_cell_height;
				grid.emplace(right_tag, temp_rect);
				break;
			}
			 //quad 7
			case 7: {
				temp_rect.x = rect.x;
				temp_rect.y = rect.y + (2 * grid_cell_height);
				temp_rect.w = grid_cell_width;
				temp_rect.h = grid_cell_height;
				grid.emplace(left_bottom_tag, temp_rect);
				break;
			}
			 //quad 8
			case 8: {
				temp_rect.x = rect.x + grid_cell_width;
				temp_rect.y = rect.y + (2 * grid_cell_height);
				temp_rect.w = grid_cell_width;
				temp_rect.h = grid_cell_height;
				grid.emplace(bottom_tag, temp_rect);
				break;
			}
			//quad 9
			case 9: {
				temp_rect.x = rect.x + (2 * grid_cell_width);
				temp_rect.y = rect.y + (2 * grid_cell_height);
				temp_rect.w = grid_cell_width;
				temp_rect.h = grid_cell_height;
				grid.emplace(right_bottom_tag, temp_rect);
				break;
			}
			default:
				break;
		}

			break;
		}

		//5 quads per side. EX: 1 edge, 3 middle, 1 edge
		case 5: {
			//determine which quad the cell is in
			switch (i) {
			//quad 1
			case 1: {
				break;
			}
			//qaud2
			case 2: {
				break;
			}
			//quad 3
			case 3: {
				break;
			}
			//quad 4
			case 4: {
				break;
			}
			//quad 5
			case 5: {
				break;
			}
			//qaud6
			case 6: {
				break;
			}
			//quad 10
			case 10: {
				break;
			}
			//quad 11
			case 11: {
				break;
			}
			//quad 15
			case 15: {
				break;
			}
			//qaud16			
			case 16: {
				break;
			}
			//quad 20
			case 20: {
				break;
			}
			//quad 21
			case 21: {
				break;
			}
			//quad 22
			case 22: {
				break;
			}
			//qaud 23
			case 23: {
				break;
			}
			//quad 24
			case 24: {
				break;
			}
			//quad 25
			case 25: {
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
	}
}