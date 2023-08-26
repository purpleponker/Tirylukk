#include "entities/comp_collider.h"
#include "map.h"
#include "collision_phys.h"
#include "textures.h"
#include "vector2D.h"
#include "asset_manager.h"


//game vars for entities, comps and objects
map_class* game_map;
ent_man_class entity_manager;

SDL_Renderer* engine_class::renderer = nullptr;
SDL_Event engine_class::event;
SDL_Rect engine_class::camera_display = { 0,0,800,640 }; //x,y,w,h

bool engine_class::is_running = false;
asset_man_class* engine_class::asset_manager = new asset_man_class(&entity_manager);

auto & player(entity_manager.add_entity());

engine_class::engine_class() {

}

engine_class::~engine_class() {

}

void engine_class::init(const char* title, int x_pos, int y_pos, int width, int height, bool is_fullscreen) {
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
	asset_manager->add_texture(dirt_tag, "assets/dirt_texture.png");
	asset_manager->add_texture(grass_tag, "assets/grass_texture.png");
	asset_manager->add_texture(water_tag, "assets/water_texture.png");
	asset_manager->add_texture(player_tag, "assets/temp_player_anims.png");
	game_map = new map_class("assets/pixel_map16x16.map", 16, 16, 32, 4);
	game_map->load_map();
	
	//implement entity components render processing
	
	//add componets to corresponding managers
	player.add_component<trans_comp_class>(3);
	player.add_component<sprite_class>(player_tag, true); //true is the animation flag to use animation contructor and build animations, might make a var to use later
	player.add_component<input_controls_class>();
	player.add_component<comp_collider_class>(player_tag);
	player.add_to_group(players_group);
}

//make groupings using entity manager prior to rendering display this allows rendering order based on groups,
//IE render map tiles, then render players, then enemies etc depending on preference.
auto& tiles_list(entity_manager.get_group(map_group));
auto& players_list(entity_manager.get_group(players_group));
auto& enemies_list(entity_manager.get_group(enemies_group));
auto& npcs_list(entity_manager.get_group(npcs_group));
auto& collider_list(entity_manager.get_group(colliders_group));

//handles in game actions
void engine_class::manage_events() {
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
void engine_class::update_display() {
	//temp for player collision hold player old position to stop them from moving through the object
	SDL_Rect player_col = player.get_component<comp_collider_class>().collider_dims;
	vector_2D_class player_pos = player.get_component<trans_comp_class>().position;

	entity_manager.refresh();
	entity_manager.update();

	//detect object/entity collisions
	for (auto cl : collider_list) {
		SDL_Rect obj_col = cl->get_component<comp_collider_class>().collider_dims;
		if (collision_class::AABB_collision(player_col, obj_col)) {
			Uint32 collision_loc = collision_class::get_col_loc(player_col, obj_col, 2, 2);// 2 quads per side, corners shared
			vector_2D_class rebound_vector;
			collision_class::rebound_pos_vector(collision_loc, rebound_vector);
			player_pos.x_pos = player_pos.x_pos + rebound_vector.x_pos;
			player_pos.y_pos = player_pos.y_pos + rebound_vector.y_pos;
			player.get_component<trans_comp_class>().position = player_pos;
		}
	}
	//display for moving player around the map
	camera_display.x = player.get_component<trans_comp_class>().position.x_pos - (camera_display.w / 2); //half width
	camera_display.y = player.get_component<trans_comp_class>().position.y_pos - (camera_display.h / 2); //half height

	//testing the camera on scaled map 
	//clap camera to screen
	if (camera_display.x < 0)
		camera_display.x = 0;
	if (camera_display.y < 0)
		camera_display.y = 0;
	if (camera_display.x * 2 > (camera_display.w * game_map->get_scaler()) - (camera_display.w / 2)) //crazy calcs just to offset camera overreach over map
		camera_display.x = ((camera_display.w * game_map->get_scaler() / 2) - (camera_display.w  / 2));
	if (camera_display.y * 2 > camera_display.h * game_map->get_scaler() + camera_display.y / 2)
		camera_display.y = (camera_display.h * game_map->get_scaler() /2) + (camera_display.y / 2);
}


//renders the players/world/npcs to the diplay
void engine_class::render_display() {
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

	//render collider objects
	for (auto& colliders : collider_list) {
		colliders->draw();
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
void engine_class::clean_display() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game closed, thank you for playing!" << std::endl;
}

//helper func to loop display
bool engine_class::loop_display() {
	return is_running;
}
