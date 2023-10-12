#pragma once

#include <stdint.h>

#define BLOCKS 917503 // how many blocks of memory can be given out

// needs to be in heap as it will overflow the stack and write over the bootsector
struct memory_allocation_table {
   bool table[BLOCKS];
};

/*
* Memory class
* This class is used to manage memory. It uses a memory allocation table (MAT) to keep track of which blocks of memory are avaliable.
* The MAT is located at a fixed location in memory. The MAT is a struct of bools, each bool represents a block of memory.
* The MAT is followed by the memory, which is split into blocks.
*/
class Memory {
   public:
      Memory();
      ~Memory() = default;

      uint32_t malloc(uint32_t size);
      void free(uint32_t* addr, uint32_t size);
      void memcpy(uint32_t* dstptr, uint32_t* srcptr, uint32_t size);

   private:
      memory_allocation_table* mat; // located in the heap

      static constexpr uint32_t mat_location = 0x01000000;
      static constexpr uint32_t blocks = BLOCKS;
      static constexpr uint32_t memory_start = mat_location + sizeof(memory_allocation_table); // place straight after MAT
      static constexpr uint32_t memory_length = 0x00E00000; // 14 MiB
      static constexpr uint32_t memory_size = memory_length * 32;
      static constexpr uint32_t block = static_cast<uint32_t>(memory_size / blocks);
};