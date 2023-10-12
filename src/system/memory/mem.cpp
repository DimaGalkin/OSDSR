#include "mem.hpp"

Memory::Memory() {
   mat = reinterpret_cast<memory_allocation_table*>(mat_location);

   // set all blocks to avaliable
   for (int i = 0; i < blocks; ++i) {
      mat->table[i] = true;
   }
}

uint32_t Memory::malloc(uint32_t size) {
   if (size == 0) {
      return 0;
   }

   // some dodgy math to get the number of blocks without ceil()
   double blocks_needed_fl = static_cast<double>(size) / block;
   uint32_t consecutive_blocks = 0;
   uint32_t start_block = 0;

   uint32_t blocks_needed;

   if (blocks_needed_fl > 0 && blocks_needed_fl < 1) {
      blocks_needed = 1;
   } else {
      double blocks_needed_rem = blocks_needed_fl - static_cast<uint32_t>(blocks_needed_fl);
      if (blocks_needed_rem > 0) {
         blocks_needed = static_cast<uint32_t>(blocks_needed_fl) + 1;
      } else {
         blocks_needed = static_cast<uint32_t>(blocks_needed_fl);
      }
   }

   for (int i = 0; i < blocks; ++i) {
      if (mat->table[i] == true) {
         if (consecutive_blocks == 0) {
            // set this as the start block if it's the first block in the sequence
            start_block = i;
         }

         ++consecutive_blocks;
      } else {
         // if block is taken end sequence
         consecutive_blocks = 0;
      }

      if (consecutive_blocks == blocks_needed) {
         // mark blocks as taken
         for (int j = start_block; j < start_block + blocks_needed; ++j) {
            mat->table[j] = false;
         }

         // return the address of the first block
         return memory_start + (start_block * block);
      }
   }

   return 0;
}

void Memory::free(uint32_t* addr, uint32_t size) {
   if (size == 0) {
      return;
   }

   // more funky math as we don't have ceil()
   double blocks_needed_fl = (double)size / block;
   uint32_t blocks_needed;

   if (blocks_needed_fl > 0 && blocks_needed_fl < 1) {
      blocks_needed = 1;
   } else {
      double blocks_needed_rem = blocks_needed_fl - static_cast<uint32_t>(blocks_needed_fl);
      if (blocks_needed_rem > 0) {
         blocks_needed = static_cast<uint32_t>(blocks_needed_fl) + 1;
      } else {
         blocks_needed = static_cast<uint32_t>(blocks_needed_fl);
      }
   }

   // workout where the first block is
   uint32_t start = (reinterpret_cast<uint32_t>(addr) - memory_start) / block;

   // mark blocks as avaliable
   for (uint32_t i = start; i < start + blocks_needed; ++i) {
      mat->table[i] = true;
   }
}

void Memory::memcpy(uint32_t* dstptr, uint32_t* srcptr, uint32_t size) {
   // copy size bytes from srcptr to dstptr
   for (int i = 0; i < size; ++i) {
      dstptr[i] = srcptr[i];
   }
}