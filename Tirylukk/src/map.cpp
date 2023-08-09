#include "engine.h"
#include "map.h"
#include <fstream>
//temp map file
	

map_class::map_class() {
}


map_class::~map_class() {
}

void map_class::load_map(std::string file_path, int size_x, int size_y){
	char tile_name;
	std::fstream map_file;
	map_file.open(file_path);

	//tile_32 is used here for size of tiles since tile textures are 32 pixels, changes to tile size will be udpated thoughout the code but here is a note for future me.
	//could make golbal tile size var or something in future to reduce hard code confusion with game expansion
	for (int y = 0; y < size_y; y++) {
		for (int x = 0; x < size_x; x++) {
			map_file.get(tile_name);
			game_class::add_tile(atoi(&tile_name), x * tile_32, y * tile_32);
			map_file.ignore();
		}
	}

	map_file.close();

}



