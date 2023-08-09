#pragma once

class map_class {
public:
	map_class();
	~map_class();
	static void load_map(std::string, int size_x, int size_y); // size here is not 32 pixels for tile size but for map file size in dimensions, if map is multiple files for different zones use zone file size dims
private:
	const static int tile_32 = 32;
	const static int tile_64 = 64;
	int tile_var = 0;

};
