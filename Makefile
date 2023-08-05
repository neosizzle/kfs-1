#############
# CONSTANTS #
#############
NAME = kfs.bin
BOOT_SRCS = boot/boot.s
BOOT_FLAGS = -f elf32
KERNEL_SRCS += src/entry.c src/interrupts/interrupts.c src/interrupts/idt.c \
			src/io/io.c src/string/string.c src/video/video.c
KERNEL_SRCS_ASM += src/interrupts/asm/handler-defs.s 
KERNEL_FLAGS = -m32 -c -std=gnu99 -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti  -nostdlib -nodefaultlibs -Wall -Wextra
KERNEL_INCS += -I src/ -I src/interrupts/ -I src/io/ -I src/string/ -I src/video/
LINKER_SRC = boot/linker.ld
LINKER_FLAGS = -m elf_i386
BUILDDIR = build/
OBJS = ${KERNEL_SRCS:.c=.o} ${KERNEL_SRCS_ASM:.s=.o} ${BOOT_SRCS:.s=.o}
OBJS_TARGET=${addprefix ${BUILDDIR},${subst /,_,${OBJS}}}

##########
# COLORS #
##########
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
NC=\033[0m # No Color

######################
# PLATFORM DEPENDENT #
######################
UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
    GDB = gdb
endif

ifeq ($(UNAME),Darwin)
    GDB = lldb
endif

all : dependencies multiboot kernel
	@echo "${GREEN}😏  Linking..${NC}"
	@ld ${LINKER_FLAGS} -T ${LINKER_SRC} -o ${BUILDDIR}${NAME} ${OBJS_TARGET}

iso : all
	@mkdir -p iso/boot/grub
	@cp build/kfs.bin iso/boot/kfs.bin
	@cp boot/grub.cfg iso/boot/grub/grub.cfg
	@grub-mkrescue -o boot/kfs.iso iso
	@qemu-system-i386 -cdrom boot/kfs.iso

kernel : ${OBJS_TARGET}
	@echo "${GREEN}📇  Kernel complete${NC}"

multiboot : ${OBJS_TARGET}
	@echo "${GREEN}📇  Boot complete${NC}"

debug: all
	@mkdir -p iso/boot/grub
	@cp build/kfs.bin iso/boot/kfs.bin
	@cp boot/grub.cfg iso/boot/grub/grub.cfg
	@grub-mkrescue -o boot/kfs.iso iso 
	@qemu-system-i386  -gdb tcp::1234  -cdrom boot/kfs.iso &
	@${GDB} -ex "target remote localhost:1234" -ex "symbol-file build/kfs.bin"

dependencies : 
	@ echo ${OBJS}
	@bash check_dependencies.sh 

build/%.o : ${OBJS}
	@echo "${GREEN}📇  $@ OK${NC}"

.c.o :
	@echo "${GREEN}📇  Compiling $<..${NC}"
	@gcc $< ${KERNEL_FLAGS} ${KERNEL_INCS} -o ${BUILDDIR}${subst /,_,$@}

.s.o :
	@echo "${GREEN}📇  Assembling $<..${NC}"
	@nasm ${BOOT_FLAGS} $< -o ${BUILDDIR}${subst /,_,$@}

clean: 
	@rm -rf build/*.o

fclean: clean 
	@rm -rf build/kfs.bin

re : fclean all