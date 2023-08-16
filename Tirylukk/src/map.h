#pragma once

class map_class {
public:
	map_class(const char * file_path, int len, int height, int t_size, int t_scaler);
	~map_class();
	void load_map(); // size here is not 32 pixels for tile size but for map file size in dimensions, if map is multiple files for different zones use zone file size dims
	void add_tile(Uint32 tile_id, int x, int y);
	int get_scaler();
	
private:
	const char * map_file_path;
	int map_length, map_height, map_tile_size, tile_scaler_val;
	int scaled_tile;
	const static int tile_32 = 32;
	const static int tile_64 = 64;

};
