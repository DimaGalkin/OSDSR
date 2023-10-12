#include <stdint.h>

#include "memory/mem.hpp"
#include "display/display.hpp"

void demo(Memory& memory, Display& display) {
	int x = 0;
	int y = 0;

	int x_dir = 2;
	int y_dir = 2;

	while (true) {
		display.clear_screen(0x00ffffff);

		if (x > display.width_ - 100) {
			x_dir = -2;
		} else if (x < 0) {
			x_dir = 2;
		}

		if (y > display.height_ - 100) {
			y_dir = -2;
		} else if (y < 0) {
			y_dir = 2;
		}

		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 100; j++) {
				display.draw_pixel_r(x + i, y + j, 0x00000000);
			}
		}

		display.swap_buffers();

		x = x + x_dir;
		y = y + y_dir;
	}
}

// entry point
extern "C" void system_main() {
	Memory memory;
	Display display (&memory);
	
	demo(memory, display);
}
