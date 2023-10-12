#include "display.hpp"

Display::Display(Memory* memory) {
    regs16_t regs;

    // Is located at fixed location of [vbe_info_] in the heap
    vbe_info_ds* info = (vbe_info_ds*)vbe_info_;

    // calls interrupt 10h to get info on our video mode
    regs.ax = info_inst_;
	regs.es = 0x0000;
	regs.cx = mode_;
	regs.di = vbe_info_;
	int32(0x10, &regs);

    // calls interrupt 10h to set our video mode
	regs.ax = mode_inst_;
	regs.bx = mode_ | (1 << 14); // 14th bit is set to enable linear framebuffer
	int32(0x10, &regs);
    
    memory_ = memory;

    // sets the width, height, bpp, pitch, frontbuffer, and backbuffer from the info block
    width_ = info->width;
    height_ = info->height;
    bpp_ = info->bpp;
    pitch_ = info->pitch;

    // sets the frontbuffer and allocates the backbuffer
    frontbuffer_ = info->framebuffer;
    backbuffer_ = reinterpret_cast<uint32_t>(memory->malloc(width_ * height_ * (bpp_ / 8)));
}

void Display::clear_screen(uint32_t color) {
    for (int i = 0; i < width_ * height_; ++i) {
		uint32_t* loc = reinterpret_cast<uint32_t*>(backbuffer_ + (i * (bpp_ / 8)));
		*loc = color;
	}
}

void Display::draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
    // error checking absent in _r version
    if (x > width_ || y > height_) return;

    uint32_t* loc = reinterpret_cast<uint32_t*>(y * pitch_ + (x * (bpp_/8)) + backbuffer_);
    *loc = color;
}

void Display::draw_pixel_r(uint32_t x, uint32_t y, uint32_t color) {
    uint32_t* loc = reinterpret_cast<uint32_t*>(y * pitch_ + (x * (bpp_/8)) + backbuffer_);
    *loc = color;
}

void Display::swap_buffers() {
    // draws back buffer to front buffer
    memory_->memcpy(
        reinterpret_cast<uint32_t*>(frontbuffer_), // to
        reinterpret_cast<uint32_t*>(backbuffer_), // from
        width_ * height_ * (bpp_ / 8) // size
    );
}