#pragma once

#include "UI_label.h"


//not sure if it should be derived or not
class menu_class : public component_class {

public:
	menu_class(menu_tag menu_tag_id, std::string file_path, font_tag font_id) {
		menu_id = menu_tag_id;
		src_surface = IMG_Load(file_path.c_str());
		text_color = { 255,255,255,255 }; //white text
		button_offset.x_pos = 100.f;
		button_offset.y_pos = 100.f;
		build_menu();
	};
	~menu_class() {};
	void build_menu() {
		switch (menu_id) {
			case main_menu:	{
				for (auto& i : text)
				button_count++;
				//code to get text for menu items

				//lay menu surface first
				menu_rect.x = engine_class::camera_display.x / 2 - src_surface->w;
				menu_rect.y = engine_class::camera_display.y / 2 - src_surface->h;
				menu_rect.w = src_surface->w;
				menu_rect.h = src_surface->h;
				/*if (SDL_BlitSurface(src_surface, nullptr, combined_surf, &menu_rect) != 0) {
					SDL_GetError();
				}
				SDL_FreeSurface(src_surface);
				*/
				//layer buttons down over menu border surface
				for (int i = 0; i < button_count; i++) {
					x_offset_counter++;
					y_offset_counter++;
					//button_text = text[i];
					//DL_Surface* surface = TTF_RenderText_Blended(engine_class::asset_manager->get_font(font_id), button_text.c_str(), text_color);
					//dest_rect.x = engine_class::camera_display.x / 2 + button_offset.x_pos * x_offset_counter;
					//dest_rect.y = engine_class::camera_display.y / 2 + button_offset.y_pos * y_offset_counter;
					/*
					if (SDL_BlitSurface(surface, nullptr, combined_surf, &dest_rect) != 0) {
						SDL_GetError();
					}
					SDL_FreeSurface(surface);
					*/
				}

				//menu_texture = SDL_CreateTextureFromSurface(engine_class::renderer, combined_surf);
				//SDL_QueryTexture(menu_texture, nullptr, nullptr, &menu_rect.w, &menu_rect.h);
				//SDL_FreeSurface(combined_surf);
				break;
			}

		case party_inventory:
			break;
		case settings:
			break;
		case controls:
			break;
		case map:
			break;
		case player_inventory:
			break;
		default:
			break;
		}
	//set text for buttons
	//generate surfaces from buttons and menu png or other source of pixel configureation
	//convert surfaces to textures
	//free old surfaces

	};

	//update text hightlight, probably also for inventory management, in general all updates to menu textures
	void update() override {

	}

	void draw() override {
		//SDL_RenderCopy(engine_class::renderer, menu_texture, nullptr, &menu_rect);
	};
private:
	//*************menu item variables*************
	menu_tag menu_id;
	SDL_Rect dest_rect;
	SDL_Rect menu_rect;
	vector_2D_class mouse_pos;
	vector_2D_class button_offset;
	std::string button_text;
	font_tag font_id;
	SDL_Color text_color;
	SDL_Color high_light_color;
	bool text_selected = false;
	int button_count;
	int x_offset_counter = 0;
	int y_offset_counter = 0;

	//***********surfaces and textures**************
	//load menu background surface to src_surface
	SDL_Surface* src_surface;
	SDL_Surface* combined_surf;
	
	//using SDL_blitsurface to combine all surfaces and then use SDL_CreateTextureFromSurface to get the entire menu texture
	SDL_Texture* menu_texture;

	//testing menu text
	const char* text[2] = { "continue", "exit" };
};
