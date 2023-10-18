#include <stdint.h>

#include "memory/mem.hpp"
#include "display/display.hpp"
#include "display/chars.hpp"

// entry point
extern "C" void system_main() {
	Memory memory;
	Display display (&memory);
}
