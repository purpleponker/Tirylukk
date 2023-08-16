#include "engine.h"
#include "map.h"
#include <fstream>
#include "entities/entity_comps.h"
#include "entities/components.h"

extern ent_man_class entity_manager;
	

map_class::map_class(const char * file_path, int x_size, int y_size , int t_size, int t_scaler) : map_file_path(file_path),
	map_length(x_size), map_height(y_size), map_tile_size(t_size), tile_scaler_val(t_scaler){
	scaled_tile = map_tile_size * tile_scaler_val;
}


map_class::~map_class() {
}

void map_class::load_map(){
	char f_input;
	std::fstream map_file;
	map_file.open(map_file_path);

	//tile_32 is used here for size of tiles since tile textures are 32 pixels, changes to tile size will be udpated thoughout the code but here is a note for future me.
	//could make golbal tile size var or something in future to reduce hard code confusion with game expansion
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_length; x++) {
			map_file.get(f_input);
			switch (atoi(&f_input))
			{
			case 0: {
				add_tile(dirt_tag, x * scaled_tile, y * scaled_tile);
				break;
			}				
			case 1: {
				  add_tile(grass_tag, x * scaled_tile, y * scaled_tile);
				  break;
			}
			case 2: {
				add_tile(water_tag, x * scaled_tile, y * scaled_tile);
				break;
			}
			default:
				break;
			}
			map_file.ignore();
		}
	}
	
	//ignore the line between map layers in map file
	map_file.ignore();

	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_length; x++) {
			map_file.get(f_input);
			if (f_input != 0) {
				auto& col_tag(entity_manager.add_entity());
				switch (atoi(&f_input)){
				//terrain collision
				case 1:
				{
					col_tag.add_component<comp_collider_class>(terrain_tag, x * scaled_tile, y * scaled_tile, scaled_tile);
					col_tag.add_to_group(colliders_group);
					break;
				}
				//object collision
				case 2:
				{
					col_tag.add_component<comp_collider_class>(terrain_tag, x * scaled_tile, y * scaled_tile, scaled_tile);
					col_tag.add_to_group(colliders_group);
					break;
				}
				default:
					break;
				}
			}
			map_file.ignore();
		}
	}

	map_file.close();

}

void map_class::add_tile(Uint32 tile_id, int x, int y) {
	auto& tile(entity_manager.add_entity());
	tile.add_component<tile_comp_class>(x, y, scaled_tile, scaled_tile, tile_id);
	tile.add_to_group(map_group);
}

int map_class::get_scaler() {
	int scale_val = tile_scaler_val;
	return scale_val;
}


