#!/bin/sh

function 	is_installed {
	printf "Testing $1 ...";
	RESULT=`whereis $1`
	TOTAL=$((TOTAL+1))
	for ((x = `echo $1 | wc -c`; x < 50; x++)) do printf %s ' '; done;
	if test "$RESULT" = "$1:";
	then
		printf "\e[1;31mNot found !\e[0m\n";
	else
		printf "\e[1;32mFound !\e[0m\n";
		SUCCESS=$((SUCCESS+1))
	fi
}

export	TOTAL=0
export	SUCCESS=0

is_installed "gcc"
is_installed "nasm"
is_installed "ld"
is_installed "grub-mkrescue"
is_installed "qemu-system-i386"

if test "$TOTAL" = "$SUCCESS";
	then
		exit 0
	else
		printf "\e[1;31mPlease fix dependencies !\e[0m\n";
		exit 1
	fi