global start
extern system_main ; c++ kernel
extern switch_to_real_mode ; real mode switch

; setup interrupts: GDT & IDT
; setup switch to real
; setup vesa

section .text

start: ; bootloader entry point
    mov esp, stack_top

    call system_main

    hlt

section .bss
align 4096

stack_bottom:
    resb 4096 * 4 ; stack size (4096 -> 2kb) 
stack_top:
