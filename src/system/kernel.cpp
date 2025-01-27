#include <stdint.h>

#include "display/chars.hpp"
#include "keyboard/keyboard.hpp"
#include "memory/mem.hpp"
#include "memory/memglobs.hpp"
#include "display/display.hpp"
#include "display/displayglobs.hpp"

// entry point
extern "C" void system_main() {
    Memory memory;
	GLOBAL_MEMORY_MANAGER = &memory;

    Display display;
    GLOBAL_DISPLAY_MANAGER = &display;

	display.clear_screen(0x000000);

	initKeyboard();

	run:
		printf(chr(scanf()));

		display.swap_buffers();

		goto run;
}