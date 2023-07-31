%define MULTIBOOT_FLAGS   0  
%define MAGIC    0x1BADB002       
%define CHECKSUM -(MAGIC + MULTIBOOT_FLAGS)

section .multiboot
	dd MAGIC	; Magic number
	dd MULTIBOOT_FLAGS			; Flags
	dd CHECKSUM ; Checksum

section .text
	global _entry

	extern kernel_main
	_entry:
		mov esp, stack_top
		call kernel_main
		hlt

section .bss
	align 16
	; stack_bottom: times 16384 db 0 ; 16 KiB
	; stack_top: 
	stack_bottom:
	resb 16384			; reserve 16KB for stack
	stack_top: