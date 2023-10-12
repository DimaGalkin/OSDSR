#include <stdint.h>

#include "memory/mem.hpp"
#include "display/display.hpp"

// ignore this. please.
void sleep() {
	int i = 0;

	for (int j = 0; j < 1000000; ++j) {
		++i;
	}
}

void demo(Memory& memory, Display& display) {
	display.clear_screen(0xffffff);
	display.swap_buffers();
}

// entry point
extern "C" void system_main() {
	Memory memory;
	Display display (&memory);
	
	demo(memory, display);
}
