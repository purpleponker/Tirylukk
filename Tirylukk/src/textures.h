#pragma once
#include "SDL.h"
class texture_class{

public:
	static SDL_Texture * load_texture(const char * file_name);
	static void draw_texture(SDL_Texture* text, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip_flag);
};


