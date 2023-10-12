#include "display.hpp"

Display::Display(Memory* memory) {
    regs16_t regs;

    vbe_info_ds* info = (vbe_info_ds*)vbe_info;

    regs.ax = info_inst;
	regs.es = 0x0000;
	regs.cx = mode;
	regs.di = vbe_info;
	int32(0x10, &regs);

	regs.ax = mode_inst;
	regs.bx = mode | (1 << 14); // 14th bit is set to enable linear framebuffer
	int32(0x10, &regs);
    
    memory_ = memory;

    width_ = info->width;
    height_ = info->height;
    bpp_ = info->bpp;
    pitch_ = info->pitch;

    frontbuffer_ = info->framebuffer;
    backbuffer_ = memory->malloc(width_ * height_ * (bpp_ / 8));
}

void Display::clear_screen(uint32_t color) {
    for (int i = 0; i < width_ * height_; ++i) {
		uint32_t* loc = (uint32_t*)(backbuffer_ + (i * (bpp_ / 8)));
		*loc = color;
	}
}

void Display::draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (x > width_ || y > height_) return;

    uint32_t* loc = (uint32_t*)(y * pitch_ + (x * (bpp_/8)) + backbuffer_);
    *loc = color;
}

void Display::draw_pixel_r(uint32_t x, uint32_t y, uint32_t color) {
    uint32_t* loc = (uint32_t*)(y * pitch_ + (x * (bpp_/8)) + backbuffer_);
    *loc = color;
}

void Display::swap_buffers() {
    memory_->memcpy((uint32_t*)frontbuffer_, (uint32_t*)backbuffer_, width_ * height_ * (bpp_ / 8));
}