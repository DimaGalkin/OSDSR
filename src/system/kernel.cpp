#include <stdint.h>

#include "display/chars.hpp"
#include "display/display.hpp"
#include "display/displayglobs.hpp"
#include "keyboard/keyboard.hpp"
#include "memory/mem.hpp"
#include "memory/memglobs.hpp"

// entry point
extern "C" void system_main() {
  Memory memory;
  GLOBAL_MEMORY_MANAGER = &memory;

  Display display;
  GLOBAL_DISPLAY_MANAGER = &display;

  display.clear_screen(0x222222);

  initKeyboard();

run:
  printf(chr(scanf()));

  display.swap_buffers();

  goto run;
}
