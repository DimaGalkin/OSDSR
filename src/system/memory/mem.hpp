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

        uint32_t* malloc_r (uint32_t size);
        void free_r (uint32_t* addr, uint32_t size);
        void memcpy_r (uint32_t* dstptr, uint32_t* srcptr, uint32_t size);

    private:
        memory_allocation_table* mat_; // located in the heap

        static constexpr uint32_t mat_location_ = 0x01000000;
        static constexpr uint32_t blocks_ = BLOCKS;
        static constexpr uint32_t memory_start_ = mat_location_ + sizeof(memory_allocation_table); // place straight after MAT
        static constexpr uint32_t memory_length_ = 0x00E00000; // 14 MiB
        static constexpr uint32_t memory_size_ = memory_length_ * 32;
        static constexpr uint32_t block_ = static_cast<uint32_t>(memory_size_ / blocks_);
};

extern Memory* GLOBAL_MEMORY_MANAGER;
extern uint32_t* malloc (const uint32_t size);
extern void free (uint32_t* addr, uint32_t size);
extern void memcpy (uint32_t* dstptr, uint32_t* srcptr, uint32_t size);