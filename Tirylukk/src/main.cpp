#include "SDL.h"
#include "engine.h"

game_class* game = nullptr;

int main(int argc, char** argv) {
	game = new game_class();
	//frame rates and game speed
	const int fps = 60;
	const int frame_delay = 1000 / fps;
	Uint32 frame_start;
	int frame_time;

	game->init("Tiyrlukk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	while (game->loop_display()) {
		//manage game time in frames
		frame_start = SDL_GetTicks();

		//render and display game
		game->manage_events();
		game->update_display();
		game->render_display();

		//update frame time based on change from frame start
		//delay frame update based on ratio of delay to frame time
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time) {
			SDL_Delay(frame_delay - frame_time);
		}
	}
	return 0;
}