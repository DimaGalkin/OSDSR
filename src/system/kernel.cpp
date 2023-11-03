#include <stdint.h>

#include "memory/mem.hpp"
#include "display/display.hpp"
#include "display/chars.hpp"
#include "dsr/renderer.hpp"

#include "scene.hpp"

constexpr double sin(int x) {
	double n = (4 * x) * (180 - x);
	double d = 40500 - (x * (180 - x));

	return n / d;
}

constexpr double cos(int x) {
	double n = 40500 - (x * x);
	double d = 40500 + (x * x);

	return n / d;
}

static constexpr double coses[10] = {cos(0), cos(10), cos(20), cos(30), cos(40), cos(50), cos(60), cos(70), cos(75), cos(80)};
static constexpr double sines[10] = {sin(0), sin(10), sin(20), sin(30), sin(40), sin(50), sin(60), sin(70), cos(75), sin(80)};

// entry point
extern "C" void system_main() {
	Memory memory;
	Display display (&memory);
	Renderer renderer (display);

	display.clear_screen(0x000000);

	int i = 0;
	int dir = 1;

	while (true) {
		display.clear_screen(0x000000);

		for (int i = 0; i < 12; ++i) {
			//bool draw = renderer.backfacecull(cube[i]);
			
			if (true) {
				renderer.drawtriangle(renderer.project(cube[i]));
			}
		}

		double coss = coses[i];
		double sinn = sines[i];

		renderer.calculate_camera_transform_matrix(cos(80) , sin(80));

		// i += dir;

		// if (i == 10) {
		// 	dir = -1;
		// 	--i;
		// } else if (i == -1) {
		// 	dir = 1;
		// 	++i;
		// }

		display.swap_buffers();
	}
}