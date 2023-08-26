#include "textures.h"
#include "object.h"
#include "engine.h"

object_class::object_class(const char * texture_sheet, int x, int y) {
	obj_texture = texture_class::load_texture(texture_sheet);
	x_pos = x;
	y_pos = y;

}

void object_class::update_obj() {
	x_pos++;
	y_pos++;

	src_rect.h = 32;
	src_rect.w = 32;
	src_rect.x = 0;
	src_rect.y = 0;

	dest_rect.x = x_pos;
	dest_rect.y = y_pos;
	dest_rect.w = src_rect.w * 2;
	dest_rect.h = src_rect.h * 2;

}

void object_class::render_obj() {
	SDL_RenderCopy(engine_class::renderer, obj_texture, &src_rect, &dest_rect);
}