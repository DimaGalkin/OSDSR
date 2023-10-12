#include "mem.hpp"

Memory::Memory() {
   mat = (memory_allocation_table*)mat_location;

   for (int i = 0; i < blocks; ++i) {
      mat->table[i] = true;
   }
}

uint32_t Memory::malloc(uint32_t size) {
   if (size == 0) {
      return 0;
   }

   double blocks_needed_fl = (double)size / block;
   uint32_t consecutive_blocks = 0;
   uint32_t start_block = 0;

   uint32_t blocks_needed;

   if (blocks_needed_fl > 0 && blocks_needed_fl < 1) {
      blocks_needed = 1;
   } else {
      double blocks_needed_rem = blocks_needed_fl - (uint32_t)blocks_needed_fl;
      if (blocks_needed_rem > 0) {
         blocks_needed = (uint32_t)blocks_needed_fl + 1;
      } else {
         blocks_needed = (uint32_t)blocks_needed_fl;
      }
   }

   for (int i = 0; i < blocks; ++i) {
      if (mat->table[i] == true) {
         if (consecutive_blocks == 0) {
            start_block = i;
         }

         ++consecutive_blocks;
      } else {
         consecutive_blocks = 0;
      }

      if (consecutive_blocks == blocks_needed) {
         for (int j = start_block; j < start_block + blocks_needed; ++j) {
            mat->table[j] = false;
         }

         return memory_start + (start_block * block);
      }
   }

   return 0;
}

void Memory::memcpy(uint32_t* dstptr, uint32_t* srcptr, uint32_t size) {
   for (int i = 0; i < size; ++i) {
      dstptr[i] = srcptr[i];
   }
}