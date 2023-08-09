#include "engine.h"
#include "textures.h"

SDL_Texture * texture_class::load_texture(const char * file_name) {
	SDL_Surface * temp_surface = IMG_Load(file_name);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(game_class::renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	return texture;
}

void texture_class::draw_texture(SDL_Texture* text, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip_flag) {
	//swapped src for null to render whole png take note if needs change in future
	SDL_RenderCopyEx(game_class::renderer, text, &src, &dest, NULL, NULL, flip_flag); //nulls are for rotation angle which are none for now
}