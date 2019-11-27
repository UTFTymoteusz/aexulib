CC = gcc
AS = nasm

MKDIR = mkdir -p

OBJ_DEST := obj/

CFILES   := $(shell find . -type f -wholename './aexulib/*.c')
ASMFILES := $(shell find . -type f -wholename './aexulib/*.asm')
OBJS     := $(patsubst %.o, $(OBJ_DEST)%.o, $(CFILES:.c=.o) $(ASMFILES:.asm=.o))
DEPENDS  := $(patsubst %.o, %.d, $(OBJS))

LIBDIR   := aexulib/
LIBODIR  := aexulib_out/

GCCFLAGS := -O2 -nostdlib -ffreestanding -no-pie -I./aexulib/ -mno-sse -mno-sse2
ASFLAGS  := -felf64

all: $(OBJS)
	@$(CC) $(OBJS) $(GCCFLAGS) -r -o $(LIBODIR)aexulib.o
	@cp -r $(LIBDIR)* $(LIBODIR)

-include $(DEPENDS)

$(OBJ_DEST)%.o: %.c
	@$(MKDIR) ${@D}
	@$(CC) $(GCCFLAGS) -c $< -o $@

$(OBJ_DEST)%.o: %.asm
	@$(MKDIR) ${@D}
	@$(AS) $(ASFLAGS) $< -o $@