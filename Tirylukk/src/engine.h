#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "vector2D.h"

class comp_collider_class;
class asset_man_class;

class engine_class {
public:
	engine_class();
	~engine_class();

	//building
	void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
	void manage_events();
	void update_display();
	void render_display();
	void clean_display();
	static void open_menu();
	
	bool loop_display();

	static SDL_Renderer* renderer;
	static SDL_Event event;

	static bool is_running;
	static SDL_Rect camera_display;
	static const int tile_size_32 = 32;
	static const int tile_size_64 = 64;
	static asset_man_class * asset_manager;

private:
	int counter = 0;
	SDL_Window * window;
	SDL_Rect screen;
	SDL_DisplayMode display_mode;
};
