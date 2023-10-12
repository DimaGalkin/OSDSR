#pragma once

#include <stdint.h>

#define BLOCKS 917503 // how many blocks of memory can be given out


//TODO: cant be bool: needs to be int to allow for ids so FREE dosent free all memory.
// needs to be in heap as it will overflow the stack and write over the bootsector
struct memory_allocation_table {
   bool table[BLOCKS];
};

class Memory {
   public:
      Memory();
      ~Memory() = default;

      uint32_t malloc(uint32_t size);
      void free(uint32_t addr);
      void memcpy(uint32_t* dstptr, uint32_t* srcptr, uint32_t size);

   private:
      memory_allocation_table* mat;

      static constexpr uint32_t mat_location = 0x01000000;
      static constexpr uint32_t blocks = BLOCKS;
      static constexpr uint32_t memory_start = mat_location + sizeof(memory_allocation_table); // place straight after MAT
      static constexpr uint32_t memory_length = 0x00E00000; // 14 MiB
      static constexpr uint32_t memory_size = memory_length * 32;
      static constexpr uint32_t block = (uint32_t)(memory_size / blocks);
};