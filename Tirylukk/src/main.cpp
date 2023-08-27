#include "SDL.h"
#include "engine.h"
//global 

engine_class* game_engine = nullptr;

int main(int argc, char** argv) {
	game_engine = new engine_class();
	//frame rates and game speed
	const int fps = 60;
	const int frame_delay = 1000 / fps;
	Uint32 frame_start;
	int frame_time;
	int screen_height;
	int screen_width;

	screen_width = 1920;
	screen_height = 1080;

	game_engine->init("Tiyrlukk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, false);
	while (game_engine->loop_display()) {
		//manage game time in frames
		frame_start = SDL_GetTicks();

		//render and display game
		game_engine->manage_events();
		game_engine->update_display();
		game_engine->render_display();

		//update frame time based on change from frame start
		//delay frame update based on ratio of delay to frame time
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time) {
			SDL_Delay(frame_delay - frame_time);
		}
	}
	return 0;
}