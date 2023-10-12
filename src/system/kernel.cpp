#include <stdint.h>

#include "memory/mem.hpp"
#include "display/display.hpp"

void sleep() {
	int i = 0;

	for (int j = 0; j < 1000000; ++j) {
		++i;
	}
}

// please ignore this code it is for temporary testing
void demo(Display& display, Memory& memory) {
	display.clear_screen(0x00000000);
	
	for (int i = 0; i < 100; ++i) {
		sleep();
		display.draw_pixel(i, i, 0x00FF0000);
		display.swap_buffers();
	}

	int x = 100;
	for (int i = 100; i > 0; --i) {
		sleep();
		display.draw_pixel(x, i, 0x00FF0000);
		display.swap_buffers();
		x++;
	}
}

extern "C" void system_main() {
	Memory memory;
	Display display (&memory);

	demo(display, memory);
}
