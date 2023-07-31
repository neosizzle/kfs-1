#############
# CONSTANTS #
#############
NAME = kfs.bin
BOOT_SRCS = boot/boot.s
BOOT_FLAGS = -f elf32
KERNEL_SRCS = src/entry.c
KERNEL_FLAGS = -m32 -c -std=gnu99 -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs -Wall -Wextra
LINKER_SRC = boot/linker.ld
LINKER_FLAGS = -m elf_i386
BUILDDIR = build/
OBJS = ${KERNEL_SRCS:.c=.o} ${BOOT_SRCS:.s=.o}
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

dependencies : 
	@bash check_dependencies.sh 

build/%.o : ${OBJS}
	@echo "${GREEN}📇  $@ OK${NC}"

.c.o :
	@echo "${GREEN}📇  Compiling $<..${NC}"
	@gcc $< ${KERNEL_FLAGS} -o ${BUILDDIR}${subst /,_,$@}

.s.o :
	@echo "${GREEN}📇  Assembling $<..${NC}"
	@nasm ${BOOT_FLAGS} $< -o ${BUILDDIR}${subst /,_,$@}

clean: 
	@rm -rf build/*.o

fclean: clean 
	@rm -rf build/kfs.bin

re : fclean all