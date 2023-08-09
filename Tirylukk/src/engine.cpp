
#include "entities/comp_collider.h"
#include "map.h"
#include "collision_phys.h"
#include "textures.h"
#include "vector2D.h"


//game vars for entities, comps and objects
map_class* game_map;
ent_man_class entity_manager;

SDL_Renderer* game_class::renderer = nullptr;
SDL_Event game_class::event;
SDL_Rect game_class::camera_display = { 0,0,800,640 }; //x,y,w,h

std::vector<comp_collider_class*> game_class::collider_list;

bool game_class::is_running = false;

auto & player(entity_manager.add_entity());
auto & wall(entity_manager.add_entity());
auto & temp_man(entity_manager.add_entity());

enum group_ids : std::size_t {
	map_group,
	players_group,
	npcs_group,
	enemies_group,
	coliiders_group,
	equipment_group,
	object_group,
	placeable_group,
	resource_group
};

//make groupings using entity manager prior to rendering display this allows rendering order based on groups,
//IE render map tiles, then render players, then enimies etc depending on situation.
auto& tiles_list(entity_manager.get_group(map_group));
auto& players_list(entity_manager.get_group(players_group));
auto& enemies_list(entity_manager.get_group(enemies_group));
auto& npcs_list(entity_manager.get_group(npcs_group));

game_class::game_class() {

}

game_class::~game_class() {

}

void game_class::init(const char* title, int x_pos, int y_pos, int width, int height, bool is_fullscreen) {
	//initialize SDL window with API
	int fullscreen_flag = 0;
	if (is_fullscreen) {
		fullscreen_flag = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL API Initialised." << std::endl;
		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, fullscreen_flag);
		if (window) {
			std::cout << "window created." << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created." << std::endl;
		}
		is_running = true;
	}
	//set player texture and map txtures for rendering
	game_map = new map_class();
	
	//implement entity components render processing
	map_class::load_map("assets/pixel_map64x64.txt", 64, 64);

	//add componets to corresponding managers
	player.add_component<trans_comp_class>(8);
	player.add_component<sprite_class>("assets/temp_player_anims.png", true); //true is the animation flag to use animation contructor and build animations, might make a var to use later
	player.add_component<input_controls_class>();
	player.add_component<comp_collider_class>("player");
	player.add_to_group(players_group);
}

//handles in game actions
void game_class::manage_events() {
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		default:
			break;

	}
}


//update players/nps/world entities and components to display for game loop
void game_class::update_display() {
	entity_manager.refresh();
	entity_manager.update();

	//detect object/entity collisions
	for (auto cl : collider_list) {
		collision_class::AABB_collision(player.get_component<comp_collider_class>(), *cl);
	}
	//display for moving player around the map
	camera_display.x = player.get_component<trans_comp_class>().position.x_pos - (camera_display.w / 2); //half width
	camera_display.y = player.get_component<trans_comp_class>().position.y_pos - (camera_display.h / 2); //half height

	//clap camera to screen
	if (camera_display.x < 0)
		camera_display.x = 0;
	if (camera_display.y < 0)
		camera_display.y = 0;
	if (camera_display.x > camera_display.w)
		camera_display.x = camera_display.w;
	if (camera_display.y > camera_display.h)
		camera_display.y = camera_display.h;
	
	//-----------scrolls all tiles around player bad efficiency------------
	/*
	//scrolls all tiles not good
	for (auto t : tiles_list) {
		t->get_component<trans_comp_class>().position.x_pos += -(player.get_component<trans_comp_class>().velocity.x_pos * player.get_component<trans_comp_class>().speed);
		t->get_component<trans_comp_class>().position.y_pos += -(player.get_component<trans_comp_class>().velocity.y_pos * player.get_component<trans_comp_class>().speed);
	}
	*/
}

//renders the players/world/npcs to the diplay
void game_class::render_display() {
	SDL_RenderClear(renderer);
	//using groupings render in objects in order to display
	//render tiles
	for (auto& tile : tiles_list) {
		tile->draw();
	}

	//render player
	for (auto& player : players_list) {
		player->draw();
	}

	//render npcs
	for (auto & npc : npcs_list) {
		npc->draw();
	}

	//render enemies
	for (auto & enemy : enemies_list) {
		enemy->draw();
	}
	SDL_RenderPresent(renderer);

}
//clean displayer and destroy memory when game loop ends
void game_class::clean_display() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game closed, thank you for playing!" << std::endl;
}

void game_class::add_tile(int tile_id, int x, int y) {
	auto & tile(entity_manager.add_entity());
	tile.add_component<tile_comp_class>(x, y, tile_size_32, tile_size_32, tile_id);
	tile.add_to_group(map_group);
}

//helper func to loop display
bool game_class::loop_display() {
	return is_running;
}
