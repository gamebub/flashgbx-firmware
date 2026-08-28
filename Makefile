CC = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy
OBJDUMP = riscv64-unknown-elf-objdump

ARCH = rv32imc
ABI = ilp32

CFLAGS = -march=$(ARCH) -mabi=$(ABI) -ffreestanding -nostdlib -O3 -Wall -Iinclude -Iexternal/FlashGBX_LK_Firmware -DLK_DEVICE_HEADER=\"LK_GameBub.h\"
LDFLAGS = -T linker.ld -nostdlib -Wl,--no-warn-rwx-segments

BUILD_DIR = build
TARGET = $(BUILD_DIR)/firmware

SRC_DIR = src
EXTERNAL_DIR = external
LK_DIR = $(EXTERNAL_DIR)/FlashGBX_LK_Firmware
SRCS = $(SRC_DIR)/start.S $(SRC_DIR)/main.c $(LK_DIR)/LK.c
OBJS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(notdir $(SRCS)))))

all: $(TARGET).elf $(TARGET).bin $(TARGET).asm

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LK_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).asm: $(TARGET).elf
	$(OBJDUMP) -d $< > $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean