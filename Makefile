# CONSTANTS
NAME = kernel-kfs.1.rleseur

BUILD_DIR = build/

AS_SRCS = boot.asm
CC_SRCS = kernel.c
LD_SRCS = link.ld

OBJS = ${AS_SRCS:.asm=.o} ${CC_SRCS:.c=.o}
BUILD_OBJS = ${addprefix ${BUILD_DIR}, ${OBJS}}

AS = nasm
CC = gcc
LD = ld

CC_FLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
AS_FLAGS = -f elf32
LD_FLAGS = -m elf_i386

all: ${BUILD_OBJS}
	${LD} ${LD_FLAGS} -T ${LD_SRCS} -o ${NAME} ${BUILD_OBJS}

${BUILD_DIR}%.o: %.asm
	mkdir -p ${BUILD_DIR}
	${AS} ${AS_FLAGS} ${AS_SRCS} -o $@

${BUILD_DIR}%.o: %.c
	mkdir -p ${BUILD_DIR}
	${CC} ${CC_FLAGS} -c ${CC_SRCS} -o $@

clean:
	rm -rf ${BUILD_DIR}

fclean: clean
	rm -rf ${NAME}

# nasm -f elf32 boot.asm -o boot.o
# gcc -m32 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -c kernel.c -o kernel.o
# ld -m elf_i386 -T link.ld -o kernel-kfs.1.rleseur.2 boot.o kernel.o
