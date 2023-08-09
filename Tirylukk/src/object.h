#pragma once

//game objects: player, npc etc.
class object_class {
public:
	object_class(const char* texture_sheet, int x, int y);
	~object_class();

	void update_obj();
	void render_obj();

private:
	int x_pos;
	int y_pos;

	SDL_Texture * obj_texture;
	SDL_Rect src_rect, dest_rect;
};