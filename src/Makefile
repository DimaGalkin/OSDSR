asm_source := $(shell find i386/ -name *.asm)
asm_obj := $(patsubst i386/%.asm, build/i386/%.o, $(asm_source))

cpp_source := $(shell find system/ -name *.cpp)
cpp_obj := $(patsubst system/%.cpp, build/system/%.o, $(cpp_source))

object_files := $(cpp_obj) $(asm_obj)

$(asm_obj): build/i386/%.o : i386/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf32 $(patsubst  build/i386/%.o, i386/%.asm, $@) -o $@

$(cpp_obj): build/system/%.o : system/%.cpp
	mkdir -p $(dir $@) && \
	clang++ $(patsubst  build/system/%.o, system/%.cpp, $@) --target=i386 -std=c++2b -c -fPIC -ffreestanding -Wwritable-strings -fno-exceptions -fno-rtti -o $@

.PHONY: clean
clean:
	rm i386/kernel.iso

.PHONY: build
build: $(cpp_obj) $(asm_obj)
	ld -m elf_i386  -o i386/kernel.bin -T i386/linker.ld $(object_files) -nostdlib && \
	cp i386/kernel.bin i386/boot/kernel.bin && \
	grub-mkrescue -o i386/kernel.iso i386/ && \
	rm i386/boot/kernel.bin
	rm i386/kernel.bin
	rm -fr build
	qemu-system-i386 -cdrom i386/kernel.iso

run:
	make build
	make clean