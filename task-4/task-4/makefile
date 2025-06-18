CC = gcc
CFLAGS = -ffreestanding -nostdlib -fno-builtin -Wall -Wextra -Iinclude

Src_DIR = src
Bin_DIR = bin
Obj_DIR = obj

KERNEL_SRCS = $(Src_DIR)/kernel.c $(Src_DIR)/std_lib.c
KERNEL_OBJS = $(patsubst $(Src_DIR)/%.c,$(Obj_DIR)/%.o,$(KERNEL_SRCS))

all: prepare kernel

prepare:
	mkdir -p $(Bin_DIR) $(Obj_DIR)

kernel: $(KERNEL_OBJS)
	$(CC) $(CFLAGS) -T linker.ld -o $(Bin_DIR)/kernel.bin $^

$(OBJ_DIR)/%.o: $(Src_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(Bin_DIR) $(Obj_DIR)
