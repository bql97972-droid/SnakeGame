#include"data.h"

float floor_up[32] = {
	// positions          // color coords          // texture coords
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f
};
float floor_front[32] = {
	// positions          // color coords          // texture coords
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f
};
float floor_right[32] = {
	// positions          // color coords          // texture coords
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f
};
float floor_left[32] = {
	// positions          // color coords          // texture coords
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f
};

float cube_up[32] = {
	// positions              // color coords    // texture coords
	 0.05f, -0.05f,  0.05f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.05f, -0.05f,  0.05f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.05f,  0.05f,  0.05f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.05f,  0.05f,  0.05f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f
};
float cube_front[32] = {
	// positions              // color coords    // texture coords
	 0.05f, -0.05f,  0.05f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.05f, -0.05f, -0.05f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.05f, -0.05f, -0.05f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.05f, -0.05f,  0.05f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f
};
float cube_right[32] = {
	// positions              // color coords   // texture coords
	 0.05f, -0.05f, -0.05f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.05f, -0.05f,  0.05f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.05f,  0.05f,  0.05f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.05f,  0.05f, -0.05f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f
};
float cube_left[32] = {
	// positions              // color coords   // texture coords
	-0.05f, -0.05f,  0.05f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.05f, -0.05f, -0.05f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.05f,  0.05f, -0.05f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.05f,  0.05f,  0.05f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f
};

unsigned int cube[6] = {
	0, 1, 2,
	0, 2, 3
};