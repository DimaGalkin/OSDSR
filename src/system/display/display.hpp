#pragma once

#include <stdint.h>

#include "../memory/mem.hpp"

typedef struct {
	unsigned short di, si, bp, sp, bx, dx, cx, ax;
	unsigned short gs, fs, es, ds, eflags;
} regs16_t;

extern "C" void int32(unsigned char intnum, regs16_t *regs); // calls interrupt

struct vbe_info_ds {
	uint16_t attributes;
	uint8_t window_a;
	uint8_t window_b;
	uint16_t granularity;
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;		// height in pixels
	uint8_t w_char;
	uint8_t y_char;
	uint8_t planes;
	uint8_t bpp;	// bits per pixel in this mode
	uint8_t banks;
	uint8_t memory_model;
	uint8_t bank_size;
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer; // linear framebuffer address
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;
	uint8_t reserved1[206];
};

class Display {
    public:
        Display(Memory* memory);
        ~Display() = default;

        void clear_screen(uint32_t color);
        void draw_pixel(uint32_t x, uint32_t y, uint32_t color);
        void draw_pixel_r(uint32_t x, uint32_t y, uint32_t color);
		void swap_buffers();
    
        uint16_t width_;
        uint16_t height_;
        uint16_t bpp_;
        uint16_t pitch_;

    private:
		uint32_t frontbuffer_;
		uint32_t backbuffer_;

        static constexpr uint16_t mode = 0x0118;
        static constexpr uint16_t info_inst = 0x4F01;
        static constexpr uint16_t mode_inst = 0x4F02;

        static constexpr uint32_t vbe_info = 0x8000;

		Memory* memory_;
};