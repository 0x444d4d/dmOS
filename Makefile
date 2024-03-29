C_SOURCES = $(wildcard kernel/*.c drivers/*.c functions/*.c)

HEADERS = $(wildcard kernel/*.h drivers/*.h functions/*.h)

# Nice syntax for file extension replacement

OBJ = ${C_SOURCES:.c=.o}



# Change this if your cross-compiler is somewhere else

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc

GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb

# -g: Use debugging symbols in gcc

CFLAGS = -g



# First rule is run by default

os-image.bin: boot/boot.bin bin/kernel.bin

	cat $^ > bin/os-image.bin



# '--oformat binary' deletes all symbols as a collateral, so we don't need

# to 'strip' them manually on this case

bin/kernel_op.bin: boot/kernel_ep.asm
	nasm -f elf $@ -o kernel_ep.o
		

bin/kernel.bin: boot/kernel_ep.o ${OBJ}

	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary



# Used for debugging purposes

kernel.elf: boot/kernel_ep.o ${OBJ}

	i386-elf-ld -o $@ -Ttext 0x1000 $^ 



#run: os-image.bin

    #qemu-system-i386 -fda os-image.bin



# Open the connection to qemu and load our kernel-object file with symbols

debug: bin/os-image.bin kernel.elf

	qemu-system-i386 -s -fda bin/os-image.bin &

	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"



# Generic rules for wildcards

# To make an object, always compile from its .c

%.o: %.c ${HEADERS}

	${CC} ${CFLAGS} -ffreestanding -c $< -o $@



%.o: %.asm

	nasm $< -f elf -o $@



%.bin: %.asm

	nasm $< -f bin -o $@



clean:

	rm -rf *.bin *.dis *.o bin/*.bin *.elf

	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o


