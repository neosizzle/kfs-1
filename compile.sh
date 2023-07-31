nasm -f elf32 boot/boot.s -o build/boot.o
gcc -m32 -c src/entry.c -o build/entry.o -std=gnu99 -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs -Wall -Wextra
ld -m elf_i386 -T boot/linker.ld -o build/kfs.bin build/boot.o build/entry.o

if grub-file --is-x86-multiboot build/kfs.bin; then   echo multiboot confirmed; else   echo the file is not multiboot; fi

mkdir -p iso/boot/grub
cp build/kfs.bin iso/boot/kfs.bin
cp boot/grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o boot/kfs.iso iso
qemu-system-i386 -cdrom boot/kfs.iso