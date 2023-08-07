[TOC]

# Week 1
## Memory management reading
Precceding the completion of a custom syscall project, I went thorugh some of the unfinished material about memory management in computers and learnt about : 
- Memory addressing 
- Segmentation in hardware
- Segmentation in linux
- Linux GDT
- Linux LDTs
- Paging in hardware
- Regular and extended Paging
- Hardware Cache
- TLS (Translation lookaside buffers)

## QEMU and KVM setup
QEMU is a virtualbox on linux, and KVM is the program that turns your host machine into a hypervisor

On a MAC, I had to install qemu from source 
```
git clone https://gitlab.com/qemu-project/qemu.git
cd qemu
git submodule init
git submodule update --recursive
./configure
make
```

turns out `pkg-config`, `glib-2.0` was not installed on the mac machine, so I had to install it using homebrew 

Turns out you can install qemu from brew aswell...
by the time of writing this, the nasm official website is down..

Installing qemu on wsl is quite straightforward, 
```
sudo apt install qemu-system-x86 qemu-utils
sudo chown root:kvm /dev/kvm
sudo chmod 660 /dev/kvm
```

## Boot sector
A boot sector is the first 512 (usually) bytes of a disk that contains the code to boot the system.

The last 2 bytes will contain the magic number 0xaa55 to tell the BIOS that this sector is indeed the boot sector.

I got this simple boot sector from [this book](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf) and used `nasm -f bin boot_sect_simple.asm -o boot_sect_simple.bin` to compile a raw binary that can be executed by qemu using `qemu boot_sect_simple.bin`

I found out that boot sector coding is quite similar to normal assemblly coding, which is nice

There are also some minor differences such as different Interrupt tables and Segmentation offset since we are interacting with physical memory

## Disk drives
One new thing that I have learnt here is to interact with disk drives. I was introduced with the mechanics of it and its functions being carried out via magnets

![](https://i.imgur.com/jE5rYf8.png)

We can also index disk positions like memory using the CHS (Cylinder, Head, Sector) notation
- Cylinder - Distance between head and edge of plate
- Head - Top surface or bottom surface
- Sector - Segments of circular tracks

We may use the interrupt 0x13 (Low level disk services) and setting al to 0x02 (Read sectors) to read disk data and store them in RAM.

## Fuckup 1
I realized that we are writing a bootloader at this point, nothing to do with the grub multiboot header, I should be reading [this](https://wiki.osdev.org/Bare_Bones#Booting_the_Operating_System) since grub is already doing the things I wrote above.. I need to tell grub that im runnig this as multiboot...

## Multiboot specification
The multiboot specification is a standard that describes how a bootloader can load an x86 kernel. It applies for all kernels and all bootloaders (LILO and GRUB included), because they want to make all things :sparkle: compatible :sparkle:

The big part of this standard is the configuration. Apart from setting some flags (memory bounds, boot devices etc) and some magic bytes, the features such as Global descriptor tables and paging are also initialized here.

It also contains an entry point that will run the kernels main function.

## Virtual disk
Since we want to create a virtual disk (.iso) for testing, 
I installed grub-common, grub-pc-bin (because my machine tries to build an [EFI image](https://github.com/phil-opp/blog_os/issues/309)) and xorriso on ubuntu so I can use its commands, not so sure how to do it on mac though..

The command that was ran was 
```
grub-mkrescue -o myos.iso isodir
```

Which generates myos.iso and the contents of it will be the contents inside isodir.

The iso can be mounted in the host machine using the `mount` command to inspect the contents. It can also be booted using qemu like so 

```
qemu-system-i386 -cdrom myos.iso
```


## Link script 
Apparently you can tell the linker how to link your object files using a script file that controls object file combinations, libraries, and other resources to create the final executable or shared library. The syntax to write the file can be seen [here](https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_3.html) For now not so much needed here, just some basic positioning

## Testing Multiboot header file
To test if anything works so far, I have c/ped an example kernel in C and adjusted by multiboot header to load it. I then compile them and link them, then proceed to generate an iso file and booted it with qemu. And viola, it works

![](https://i.imgur.com/iCgngCo.png)

## Video memory
When I was making the boot sector script earlier, they mentioned a specific address `0xB8000` I needed to manipulate
to print characters on the screen. I was curious to find out why and I found [this forum](https://retrocomputing.stackexchange.com/questions/3061/who-decides-what-is-the-memory-address-that-the-cga-video-buffer-will-be-mapped), which explains that the reason `0xB8000` was chosen because of mainly historical reasons, the IBM PC just somehow used that address to read and write a buffer that affects what is being dislayed on the screen with a video card.


## Kernel compilation
I also read up on the flags used for kernel compimation, so here are what they do:

- -fno-builtin - Disable builtin functions provided by the compiler
-  -fno-exception - Disables exception handling
-  -fno-stack-protector - Disables stack protection from compiler, since we may need to manipulate physical addresses
-  -fno-rtti - Disable RunTimeTypeInformation for dynamic type identification and safe typecasting at runtime
-  -nostdlib - Tells linker to not use any standard libraries when linking the program
-  -nodefaultlibs - Tells linker to not include default system libraries during linking

## I/O Busses reading 
I read about hardware I/O and that they have a thing called controller chips that are like mini CPUs that live on the external hardware. The said hardware will read and write from the registers inside the chips to determine hardware state as well as inform the software about any changes.

On the software side, to read and write to these registers, we need to use the assembly instruction `in` and `out` to perform I/O operations. We can also locate these chips via static memory-mapping which is done by the BIOS (0xB8000 for example).

For plug and play devices, its more complicated than that since there will be dynamic allocation involved and the devices will send configuration information over the bus upon connecting.

To interact with IO ports in C, we need to use inline assembly (supported by GCC).

```c
int port_byte_in(int port)
{
    char result;
    __asm__("in %%dx, %% al": "=a"(result): "d"(port));
    return result;
}
```


The code above reads from an I/O port and stores it in result and returns it. The syntax they use is GAS, which may seem foreign to nasm users.

## DMA reading
I also sidetracked and read about Direct memory access, which is a mechanism to offload the operations of transferring data between disk and memory which slows the CPU down. An analogy from the os-dev book : 

> A good analogy of DMA is that of an architect wanting to move a wall from one place to another. The architect knows eactly what is to be done but has other important things to consider other than shifting each brick, and so instructs a builder to move the bricks, one by one, and to alert (i.e. interrupt) him when either the wall is finished or if there was some error that is stopping the wall from being finished.

## Frame Buffer
Turns out the special IO memory mapped address that we reflects whats displayed on the screen is called a frame buffer. It has 80 columns and 25 rows for standard VGA text mode (might be different for other modes).

Each cell is made of 2 characters (bytes), the highest one will be the fore and background color, the next one will be the ascii of the character to display.

The color can be refrenced from [here](http://www.brackeen.com/vga/basics.html) under mode 0x13 memory. 

I made some changes to the kernel source I have earlier, and it did print out color, just like I expected.

![](https://i.imgur.com/dQDVLCs.png)

![](https://i.imgur.com/HWn4Zhr.png)


## Frame Buffer Cursor
Unlike the frame buffer which is memory mapped, The cursor can only communicate through IO ports, which goes back to the IO hardware section using the `in` and `out` instructions.

There are 2 IO ports used for the cursor, `0x3D4` is the port used to describe the data being sent (high bits or low bits) and `0x3D5` will contain the actual data.

The cursor is represented by a 16 bit integer and since the `in` and `out` instructions can only transfer 8 bits at a time, we need to send the bits in 2 parts, hence the low and high bit indicator.

With some amendments from the kernel source (and I forgot that GAS switches the instruction operands, and custom type definitions) I made relocated the cursor to (1, 0)

![](https://i.imgur.com/236MuYZ.png)

# Week 2

## Debugger integration and repo creation
By launching the qemu vm with `qemu-system-i386  -gdb tcp::1234  -cdrom boot/kfs.iso`, we are able to expose the port 1234 for the debugger to probe. To start debugging using gdb, we can launch it like so `gdb -ex "target remote localhost:1234" -ex "symbol-file build/kfs.bin"`

The makefile was also created, hopefully it wont break 

![](https://i.imgur.com/fF60nbV.png)


## IDT implementation and PIC configuration
I have implemented the handling of ISRs and IRQs of the kernel and had also configured the PIC to map hardware signals to interrupts. Its not fully interactive but I do get a response on a keystroke.


![](https://s11.gifyu.com/images/Sc0dl.gif)


I couldnt get it to work for a long time because i did not do the `sti` instruction for enabling hardware interrupts..

## Scroll and console implementation
The scroll was implemented by clearing the screen once the limits have been reached, I also added a pseudo console that memoriezes what had been typed and prints the memorized buffer that after enter had been typed.

![](https://i.imgur.com/GhFfhZr.gif)


## Screen switch and screen context
Screen switching was implemented by storing copies of the video array in memory, and cloning the data of the video array in storage to the frame buffer on switch. The console also needs to be amended accordingly to fit work around several screens. The fotkeys f1 - f3 are bound to switch the screen.

![](https://i.imgur.com/e7h2Ra7.gif)

