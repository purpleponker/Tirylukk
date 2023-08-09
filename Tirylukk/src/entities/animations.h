#pragma once

struct animation
{
	int index;
	int num_frames;
	int animation_speed;

	animation() {

	}

	animation(int src_index, int src_frames, int src_speed) {
		index = src_index;
		num_frames = src_frames;
		animation_speed = src_speed;
	}
};