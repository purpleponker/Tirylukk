#include "collision_phys.h"
#include "entities/comp_collider.h"
#include <algorithm>
#include <math.h>

//uses rects to determine if collision happened
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

//used on the collider compoent of an entity less used that rect version, potentially redundant
bool collision_class::AABB_collision(const comp_collider_class & collider1, const comp_collider_class & collider2) {
	if (AABB_collision(collider1.collider_dims, collider2.collider_dims)) {
		//to avoid object collision with itself, tho this might case collision dection issues in the future with things like
		//projectiles colliding with other projectiles as they likely both have the same comp_tag
		//AABB collision method with rects call about might be sufficient for such cases
		//avoid player collision with self
		if (collider1.comp_tag == collider2.comp_tag && collider1.comp_tag == player_tag) {
			return false;
		}
		else if (collider1.comp_tag != collider2.comp_tag) {
			std::cout << collider1.comp_tag << " collision with: " << collider2.comp_tag << std::endl;
			return true;
		}	
	}
	else {
		return false;
	}
		
}

//angle is based on rect1 frame of reference collision angle into rect2 assuming rect2 center point is (0,0) on cartesian plane
//and rect1 is in one of the 4 cartesian quadrants
void collision_class::rebound_vector(const SDL_Rect& rect1, const SDL_Rect& rect2, vector_2D_class& pos_modifer) {
	double x_radians; //angle to x axis
	double y_radians; //angle to y axis

	//find mid_points of rects for finding impact angle for a better rebound from center of rects
	double rect1_x = static_cast<double>(rect1.x) + (static_cast<double>(rect1.w) / 2);
	double rect1_y = static_cast<double>(rect1.y) + (static_cast<double>(rect1.h) / 2);
	double rect2_x = static_cast<double>(rect2.x) + (static_cast<double>(rect2.w) / 2);
	double rect2_y = static_cast<double>(rect2.y) + (static_cast<double>(rect2.h) / 2);

	double intersect_x;
	double intersect_y;

	collision_loc_tag quad = null_loc;

	//collision projection to a cartesian system has 4 quadrants for angular collision in the x,y system, IE quad 1, quad 2, quad3 or quad 4
	//quad 1 is (+,+), quad 2 is(-,+) quad 3 is (-,-) and quad 4 is (+,-)
	//quad 1 is rect1_x >= rect2_x and rect1_y <= rect2_y
	if (rect1_x >= rect2_x && rect1_y <= rect2_y) {
		intersect_x = rect1_x - rect2_x;
		intersect_y = rect2_y - rect1_y;
		quad = quad_1;
	}
	//quad 2 is rect1_x <= rect2_x and rect1_y <= rect2_y
	else if (rect1_x <= rect2_x && rect1_y <= rect2_y) {
		intersect_x = rect2_x - rect1_x;
		intersect_y = rect2_y - rect1_y;
		quad = quad_2;
	}
	//quad 3 is rect1_x <= rect2_x and rect1_y >= rect2_y
	else if (rect1_x <= rect2_x && rect1_y >= rect2_y) {
		intersect_x = rect2_x - rect1_x;
		intersect_y = rect1_y - rect2_y;
		quad = quad_3;
	}
	//quad 4 is rect1_x >= rect2_x and rect1_y >= rect2_y
	else if (rect1_x >= rect2_x && rect1_y >= rect2_y) {
		intersect_x = rect1_x - rect2_x;
		intersect_y = rect1_y - rect2_y;
		quad = quad_4;
	}


	//rect 1 and rect2 x any y values equaling each other is very unlikely and kind of irrelevant as the rebound will depend on the other value IE is x1=x2,
	//the y's will determine the rebound direction, in the odd event that x1=x2 and y1=y2 then the objects are directly on top of each other and rebound direction 
	// would only matter to avoid clipping through objects  such as clipping outside map bounds or something
	//as for other situation the rebound could be a random direction and still be acceptable
	x_radians = atan(intersect_x / intersect_y);
	y_radians = atan(intersect_y / intersect_x);
	
	//hold these for now might be usefule for other things like ricochet or forking projectiles in future
	double x_theta = x_radians * (180 / 3.14);
	double y_theta = y_radians * (180 / 3.14);
	
	//rebound values scale based on angler to center of mass
	float x_ratio = static_cast<float>(x_theta) / 90.f;
	float y_ratio = static_cast<float>(y_theta) / 90.f;

	switch (quad){
		//determing rebound modifer values based on cartesian quadrant of collision	
		//increase x value decrease y value
		case quad_1:{
			pos_modifer.x_pos = 10.f * x_ratio;
			pos_modifer.y_pos = 10.f * -y_ratio;
			break;
		}
		//decrease x and y values
		case quad_2: {
			pos_modifer.x_pos = 10.f * -x_ratio;
			pos_modifer.y_pos = 10.f * -y_ratio;
			break;
		}
		//decrease x value increase y value
		case quad_3: {
			pos_modifer.x_pos = 10.f * -x_ratio;
			pos_modifer.y_pos = 10.f * y_ratio;
			break;
		}
		//increase x and y values
		case quad_4: {
			pos_modifer.x_pos = 10.f * x_ratio;
			pos_modifer.y_pos = 10.f * y_ratio;
			break;
		}
		default:
			break;
	}
	//test collision detection in game
	//std::cout << "x radians: " << x_radians << ", x degree: "<< x_theta << ", y radians: " << y_radians << ", y degrees: "<< y_theta << std::endl;
}

//old grid collision code
/*
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


*/