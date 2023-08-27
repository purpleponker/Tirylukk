#pragma once

#include <SDL_ttf.h>
#include "entity_comps.h"
#include "UI_label.h"

//not sure if it should be derived or not
class menu_class : public component_class {

public:
	//not sure if this is perfect but just using it as a test for now
	menu_class(SDL_Surface* screen, TTF_Font* font, int num_buttons) {
		menu_font = font;
		test_surface = screen;
		//test vars for initial menu implementation
		test_menus[0] = TTF_RenderText_Solid(font, button_labels[0], highlight_color[0]);
		test_menus[1] = TTF_RenderText_Solid(font, button_labels[1], highlight_color[0]);
		//center the postion
		//harder to center with more buttons need height off all objects in menus and adjust based on the amount and an offset, x is prob the same with larger horizontal button layout
		test_pos[0].x = screen->clip_rect.w / 2 - test_menus[0]->clip_rect.w / 2;
		test_pos[0].y = screen->clip_rect.h / 2 - test_menus[0]->clip_rect.h;

		test_pos[1].x = screen->clip_rect.w / 2 - test_menus[1]->clip_rect.w / 2;
		test_pos[1].y = screen->clip_rect.h / 2 + test_menus[1]->clip_rect.h;

		//center a label postion
		//pos.x = (screen->clip_rect.w / 2) - (menus->clip_rect.w / 2);
	}

	~menu_class() {};

	//might be used for sub menus but might also just make another menu from the class and store the menus as a list in the engine cpp file
	void update() override {}

	//loop the menu display most likely done with the draw
	void draw() override {
		is_running = true;
		while (is_running) {
			//track framerate in menu
			menu_timer = SDL_GetTicks();
			//handle events mouse movement, clicks, etc.
			//might need to handle another variable for action done ie clicked continue or clicked exit either in a return or a class data member
			while (SDL_PollEvent(&event)) {
				switch (event.type)
				{
					//menu close
				case SDL_QUIT: {
					for (int i = 0; i < button_count; i++) {
						SDL_FreeSurface(test_menus[i]);
						test_button_id = 1; // this is quit in the test button array
					}
					break;
				}
							 //mouse movement
				case SDL_MOUSEMOTION: {
					mouse_pos.x_pos = event.motion.x;
					mouse_pos.y_pos = event.motion.y;
					//check if mouse is with in a menu button/label and highlight the text if it is
					for (int i = 0; i < button_count; i++) {
						if (mouse_pos.x_pos >= test_pos[i].x && mouse_pos.x_pos <= test_pos[i].x + test_pos[i].w
							&& mouse_pos.y_pos >= test_pos[i].y && mouse_pos.y_pos <= test_pos[i].y + test_pos[i].h) {
							if (!button_selected[i]) {
								button_selected[i] = true;
								SDL_FreeSurface(test_menus[i]);
								test_menus[i] = TTF_RenderText_Solid(menu_font, button_labels[i], highlight_color[1]);
							}
						}
						//mouse is not inside a button or label change to non highlight color
						else {
							if (button_selected[i]) {
								button_selected[i] = false;
								SDL_FreeSurface(test_menus[i]);
								test_menus[i] = TTF_RenderText_Solid(menu_font, button_labels[i], highlight_color[0]);
							}
						}
					}
					break;
				}

									//mouse clicks
				case SDL_MOUSEBUTTONDOWN: {
					mouse_pos.x_pos = event.button.x;
					mouse_pos.y_pos = event.button.y;
					for (int i = 0; i < button_count; i++) {
						//determine which button was clicked from list of menu buttons, using test button array for now
						if (mouse_pos.x_pos >= test_pos[i].x && mouse_pos.x_pos <= test_pos[i].x + test_pos[i].w
							&& mouse_pos.y_pos >= test_pos[i].y && mouse_pos.y_pos <= test_pos[i].y + test_pos[i].h) {
							for (int j = 0; j < button_count; j++) {
								SDL_FreeSurface(test_menus[j]);
							}
							test_button_id = i; //return index of the button clicked in the test button array
						}
					}
					break;
				}
										//escape key pressed in the menu
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						//free surfaces when leaving menu
						for (int i = 0; i < button_count; i++) {
							SDL_FreeSurface(test_menus[i]);
						}
						test_button_id = 0; //this is the continue in test buttons, IE continue back to game
					}

				default:
					break;
				}
			}
			for (int i = 0; i < button_count; i++) {
				SDL_BlitSurface(test_menus[i], NULL, test_surface, &test_pos[i]);
			}

			if (60 > (SDL_GetTicks() - menu_timer)) {
				SDL_Delay(60 - (SDL_GetTicks() - menu_timer));
			}
		}
	}

private:
	SDL_Event event;
	TTF_Font * menu_font;
	SDL_Rect * position;
	button_tag button_id;
	vector_2D_class mouse_pos;
	SDL_Color highlight_color[2] = { { 255,255,255 }, { 255, 0, 0 } }; //only need 2 colors for highlighted and non highlighted text//not sure if i need 1 or both
	SDL_Surface * menus;
	UI_label_class * menu_button_text; //consider passing a vector or array of ui_label classes which are texts to the menu class, assuming the menu class doesn't get merged into the label class
	std::vector<button_tag> button_list;
	Uint32 menu_timer;
	bool * button_selected; //might not be needed;
	bool is_running = false;
	static const int button_count = 2; //static const for testing purposes

	//using these for testing consider using UI_label_class for future iterations
	
	const char* button_labels[button_count] = { "Continue", "Exit" };
	SDL_Rect test_pos[button_count];
	SDL_Surface* test_menus[button_count];
	SDL_Surface* test_surface;
	bool text_selected[button_count] = { 0,0 };
	int test_button_id = -1;

	//call the draw function for the menu in input controls when escape is pressed for main menu
};
