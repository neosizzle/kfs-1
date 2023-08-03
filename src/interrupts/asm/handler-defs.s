; Defined in interrupts.c
[extern isr_handler]

%macro no_error_code_isr_handler 1
	global isr_handler_%1
		isr_handler_%1:
		push dword 0 ; push 0 as error code
		push dword %1 ; push the interrupt number
		jmp common_isr_handler ; jump to the common handler
%endmacro

%macro error_code_isr_handler 1
	global isr_handler_%1
		isr_handler_%1:
		push dword %1 ; push the parameter as error code & interrupt number
		jmp common_isr_handler ; jump to the common handler
%endmacro

; handles isrs (software interrupts)
common_isr_handler:
	; save registers
	pusha

	; call c function
	call isr_handler

	; restores stacks
	popa

	; restore esp, removing the interrupt number
	add	esp, 8

	; iret call
	iret

no_error_code_isr_handler 0 ; create handler for interrupt 0
