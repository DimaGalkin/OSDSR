#pragma once

#include "mem.hpp"

Memory* GLOBAL_MEMORY_MANAGER;

uint32_t* malloc (const uint32_t size) {
    return GLOBAL_MEMORY_MANAGER->malloc_r(size);
}

void free (uint32_t* addr, uint32_t size) {
    GLOBAL_MEMORY_MANAGER->free_r(addr, size);
}

void memcpy (uint32_t* dstptr, uint32_t* srcptr, uint32_t size) {
    GLOBAL_MEMORY_MANAGER->memcpy_r(dstptr, srcptr, size);
}