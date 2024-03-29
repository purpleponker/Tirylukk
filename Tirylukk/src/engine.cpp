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

//prob need to change this for variable screen size to clamp proper
SDL_Rect engine_class::camera_display;//x,y,w,h

bool engine_class::is_running = false;
asset_man_class* engine_class::asset_manager = new asset_man_class(&entity_manager);

auto & player(entity_manager.add_entity());
auto & ui_label(entity_manager.add_entity());
auto & menu(entity_manager.add_entity());

engine_class::engine_class() {

}

engine_class::~engine_class() {

}

void engine_class::init(const char* title, int x_pos, int y_pos, int width, int height, bool is_fullscreen) {
	//initialize SDL window with API
	int screen_res_flag = 0;
	if (is_fullscreen) {
		screen_res_flag = SDL_WINDOW_FULLSCREEN;
	}
	else
		screen_res_flag = SDL_WINDOW_RESIZABLE;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL API Initialised." << std::endl;
		if (SDL_GetDesktopDisplayMode(0, &display_mode) != 0)
		{
			SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
			return;
		}
		window = SDL_CreateWindow(title, x_pos, y_pos, display_mode.w, display_mode.h, screen_res_flag);
		if (window) {
			std::cout << "window created." << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created." << std::endl;
		}
		is_running = true;
		camera_display.x = screen.x = x_pos;
		camera_display.y = screen.y = y_pos;
		camera_display.w = screen.w = display_mode.w;
		camera_display.h = screen.h = display_mode.h;
	}
	//********************UI and fonts ********************
	//SDL ttf for ui and fonts
	if (TTF_Init() == -1) {
		std::cout << "Error: SDL_TFF lib" << SDL_GetError() << std::endl;
	}

	//********************textures ********************
	//and map tile textures
	asset_manager->add_texture(dirt_tag, "assets/dirt_texture.png");
	asset_manager->add_texture(grass_tag, "assets/grass_texture.png");
	asset_manager->add_texture(water_tag, "assets/water_texture.png");
	//player textures
	asset_manager->add_texture(player_tag, "assets/temp_player_anims.png");
	//projectile textures
	asset_manager->add_texture(projectile_tag, "assets/test_projectile.png");
	//font textures
	asset_manager->add_font(font_1, "assets/vgafix.fon", 16); //font tag, path, size

	//******************** map ********************
	//load map from file
	game_map = new map_class("assets/pixel_map16x16.map", 16, 16, 32, 10);
	game_map->load_map();
	
	//******************** entity components ********************

	//add componets to corresponding managers
	player.add_component<trans_comp_class>(4);
	player.add_component<sprite_class>(player_tag, true); //true is the animation flag to use animation contructor and build animations, might make a var to use later
	player.add_component<input_controls_class>();
	player.add_component<comp_collider_class>(player_tag);

	player.add_to_group(players_group);

	//UI and font text
	SDL_Color white = { 255,255,255,255 };
	ui_label.add_component<UI_label_class>(10, 10, "test string", font_1, white);

	//main menu
	menu.add_component<menu_class>(main_menu, "assets/menu_box-128x128.png", font_1);
	

	//********************projectiles ********************
	//position vector, velocity vector, range, speed, asset id for texture
	asset_manager->generate_projectile(vector_2D_class(0, 0), vector_2D_class(2,2), 200, 1, projectile_tag); //position vector could use player or eneymy position vectors too in future for arrows/guns/etc
	asset_manager->generate_projectile(vector_2D_class(600,600), vector_2D_class(1, 1), 1000, 1, projectile_tag);
	asset_manager->generate_projectile(vector_2D_class(0, 500), vector_2D_class(5, 1), 20000, 1, projectile_tag);
}

//make groupings using entity manager prior to rendering display this allows rendering order based on groups,
//IE render map tiles, then render players, then enemies etc depending on preference.
auto& tile_list(entity_manager.get_group(map_group));
auto& player_list(entity_manager.get_group(players_group));
auto& enemy_list(entity_manager.get_group(enemies_group));
auto& npc_list(entity_manager.get_group(npcs_group));
auto& collider_list(entity_manager.get_group(colliders_group));
auto& projectile_list(entity_manager.get_group(projectile_group));

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
	//update window size
	
	//temp for player collision hold player old position to stop them from moving through the object
	comp_collider_class player_col = player.get_component<comp_collider_class>();
	vector_2D_class player_pos = player.get_component<trans_comp_class>().position;

	//initial UI update with player position using string stream
	std::string player_ui;
	std::string player_x = std::to_string(static_cast<int>(player_pos.x_pos));
	std::string player_y = std::to_string(static_cast<int>(player_pos.y_pos));
	player_ui = "Player position: " + player_x + ", " + player_y;
	ui_label.get_component<UI_label_class>().set_label_text(player_ui, font_1);

	entity_manager.refresh();
	entity_manager.update();

	//detect object/entity collisions
	for (auto cl : collider_list) {
		comp_collider_class obj_col = cl->get_component<comp_collider_class>();
			if (collision_class::AABB_collision(player_col, obj_col)){
				vector_2D_class vector_modifer;
				collision_class::rebound_vector(player_col.collider_dims, obj_col.collider_dims, vector_modifer);
				player_pos.x_pos = player_pos.x_pos + vector_modifer.x_pos;
				player_pos.y_pos = player_pos.y_pos + vector_modifer.y_pos;
				player.get_component<trans_comp_class>().position = player_pos;
			}
	}
	//detect projectile hits
	for (auto& projectile : projectile_list) {
		if (collision_class::AABB_collision(player.get_component<comp_collider_class>().collider_dims, projectile->get_component<comp_collider_class>().collider_dims)) {
			projectile->destroy();
		}
	}

	//display for moving player around the map
	camera_display.x = player.get_component<trans_comp_class>().position.x_pos - (camera_display.w / 2); //half width
	camera_display.y = player.get_component<trans_comp_class>().position.y_pos - (camera_display.h / 2); //half height

	//testing the camera on scaled map 
	//clap camera to screen and map size doesnt work on variable size widows for now prob due to camera rect values being hard coded
	//min side
	if (camera_display.x < 0)
		camera_display.x = 0;
	if (camera_display.y < 0)
		camera_display.y = 0;
	//max side
	if (camera_display.x > game_map->scaled_map_width() - camera_display.w) {
		camera_display.x = game_map->scaled_map_width() - camera_display.w;
	}
	if (camera_display.y > game_map->scaled_map_height() - camera_display.h) {
		camera_display.y = game_map->scaled_map_height() - camera_display.h;
	}
}


//renders the players/world/npcs to the diplay
void engine_class::render_display() {
	SDL_RenderClear(renderer);
	//using groupings render in objects in order to display
	//render tiles
	for (auto& tile : tile_list) {
		tile->draw();
	}

	//render player
	for (auto& player : player_list) {
		player->draw();
	}

	//render collider objects
	for (auto& colliders : collider_list) {
		colliders->draw();
	}

	//render npcs
	for (auto & npc : npc_list) {
		npc->draw();
	}

	//render enemies
	for (auto & enemy : enemy_list) {
		enemy->draw();
	}

	//render projectiles
	for (auto& projectile : projectile_list) {
		projectile->draw();
	}

	//ui: fonts and labels
	ui_label.draw();
	menu.draw();

	//end of render order
	SDL_RenderPresent(renderer);

}

void engine_class::open_menu() {
	
}

//clean display and destroy memory when game loop ends
void engine_class::clean_display() {
	delete[] asset_manager;
	delete[] game_map;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game closed, thank you for playing!" << std::endl;
}

//helper func to loop display
bool engine_class::loop_display() {
	return is_running;
}
