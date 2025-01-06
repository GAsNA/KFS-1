# CONSTANTS
NAME = kernel-kfs.1.rleseur

BUILD_DIR = build/
SRC_DIR = src/

BOOT_DIR = ${SRC_DIR}boot/
KERNEL_DIR = ${SRC_DIR}kernel/
LD_DIR = ${SRC_DIR}

BOOT_FILES = boot.asm
KERNEL_FILES = kernel.c keyboard.c
LD_FILES = link.ld

BOOT_SRC = ${addprefix ${BOOT_DIR}, ${BOOT_FILES}}
KERNEL_SRC = ${addprefix ${KERNEL_DIR}, ${KERNEL_FILES}}
LD_SRC = ${addprefix ${LD_DIR}, ${LD_FILES}}

OBJS = ${BOOT_FILES:.asm=.o} ${KERNEL_FILES:.c=.o}
BUILD_OBJS = ${addprefix ${BUILD_DIR}, ${OBJS}}

AS = nasm
CC = gcc
LD = ld
QEMU = qemu-system-i386

AS_FLAGS = -f elf32
CC_FLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
LD_FLAGS = -m elf_i386 -z noexecstack

# RULES
all: ${BUILD_OBJS}
	${LD} ${LD_FLAGS} -T ${LD_SRC} -o ${NAME} ${BUILD_OBJS}

run: all
	${QEMU} -kernel ${NAME}

${BUILD_DIR}%.o: ${BOOT_DIR}%.asm
	mkdir -p ${BUILD_DIR}
	${AS} ${AS_FLAGS} ${BOOT_SRC} -o $@

${BUILD_DIR}%.o: ${KERNEL_DIR}%.c
	mkdir -p ${BUILD_DIR}
	${CC} ${CC_FLAGS} -c $< -o $@

clean:
	rm -rf ${BUILD_DIR}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all run clean fclean re
