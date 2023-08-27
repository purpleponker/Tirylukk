#pragma once

#include "../asset_manager.h"
#include "../textures.h"
#include "entity_comps.h"
#include "../engine.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


class UI_label_class : public component_class {

public:
	UI_label_class(int src_x_pos, int src_y_pos, std::string src_text, font_tag src_id, SDL_Color& src_color) : label_text(src_text), font_id(src_id), text_color(src_color) {
		position.x = src_x_pos;
		position.y = src_y_pos;
		set_label_text(label_text, font_id);
	}
	~UI_label_class() {}

	void set_label_text(std::string text, font_tag id) {
		SDL_Surface* surface = TTF_RenderText_Blended(engine_class::asset_manager->get_font(id), text.c_str(), text_color);
		label_texture = SDL_CreateTextureFromSurface(engine_class::renderer, surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(label_texture, nullptr, nullptr, &position.w, &position.h);
	}
	void draw() override {
		SDL_RenderCopy(engine_class::renderer, label_texture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string label_text;
	font_tag font_id;
	SDL_Color text_color;
	SDL_Texture * label_texture;
};

