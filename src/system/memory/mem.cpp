#include "mem.hpp"

Memory::Memory() {
   mat_ = reinterpret_cast<memory_allocation_table*>(mat_location_);

   // set all blocks to avaliable
   for (int i = 0; i < blocks_; ++i) {
      mat_->table[i] = true;
   }
}

uint32_t* Memory::malloc_r(uint32_t size) {
   if (size == 0) {
      return 0;
   }

   const uint32_t blocks_needed = (size + block_ - 1) / block_;
   uint32_t consecutive_blocks = 0;
   uint32_t start_block = 0;

   for (int i = 0; i < blocks_; ++i) {
      if (mat_->table[i] == true) {
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
            mat_->table[j] = false;
         }

         // return the address of the first block
         return reinterpret_cast<uint32_t*>(memory_start_ + (start_block * block_));
      }
   }


   return 0;
}

void Memory::free_r(uint32_t* addr, uint32_t size) {
   if (size == 0) {
      return;
   }

   const uint32_t blocks_needed = (size + block_ - 1) / block_;

   // work out where the first block is
   uint32_t start = (reinterpret_cast<uint32_t>(addr) - memory_start_) / block_;

   // mark blocks as avaliable
   for (uint32_t i = start; i < start + blocks_needed; ++i) {
      mat_->table[i] = true;
   }
}

void Memory::memcpy_r(uint32_t* dstptr, uint32_t* srcptr, uint32_t size) {
   // copy size bytes from srcptr to dstptr

   int i = 0;


   for (; i < (size / 4); i+=4) {
      dstptr[i] = srcptr[i];
      dstptr[i+1] = srcptr[i+1];
      dstptr[i+2] = srcptr[i+2];
      dstptr[i+3] = srcptr[i+3];
   }

   for (; i < size; ++i) {
      dstptr[i] = srcptr[i];
   }
}