# sharing basic makefile

PRO_DIR		:= .
PROJ_NAME	:= stm32f030r8t6_systick
OUTPUT_PATH := $(PRO_DIR)/output

INC_DIR		:= $(PRO_DIR)/inc
SRC_DIR 	:= $(PRO_DIR)/src
LINKER_FILE	:= $(PRO_DIR)/linker/stm32f0_discovery.ld

COMPILER_DIR 	:= D:/gcc_ARM

PREFIX_GCC_COMPILER	:= arm-none-eabi
CC				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-gcc.exe
OBJCPY			:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-objcopy
ASM				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-as
LD				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-ld

FILE_TO_LINK	:= $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/startup_ARMCM0.o $(OUTPUT_PATH)/gpio.o $(OUTPUT_PATH)/nvic.o $(OUTPUT_PATH)/clock.o $(OUTPUT_PATH)/uart.o	 

CC_OPT			:= -march=armv6-m -mcpu=cortex-m0 -c -O0 -g -w -Wall -mthumb -I$(INC_DIR)
ASM_OPT			:= -march=armv6-m -mcpu=cortex-m0 -c -mthumb
LD_OPT			:= -T $(LINKER_FILE) -Map $(OUTPUT_PATH)/$(PROJ_NAME).map $(FILE_TO_LINK)

$(OUTPUT_PATH)/main.o: $(SRC_DIR)/main.c
	@echo "compile $(SRC_DIR)/main.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/main.c -o $(OUTPUT_PATH)/main.o

$(OUTPUT_PATH)/gpio.o: $(SRC_DIR)/gpio.c
	@echo "compile $(SRC_DIR)/gpio.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/gpio.c -o $(OUTPUT_PATH)/gpio.o

$(OUTPUT_PATH)/nvic.o: $(SRC_DIR)/nvic.c
	@echo "compile $(SRC_DIR)/nvic.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/nvic.c -o $(OUTPUT_PATH)/nvic.o
	
$(OUTPUT_PATH)/clock.o: $(SRC_DIR)/clock.c
	@echo "compile $(SRC_DIR)/clock.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/clock.c -o $(OUTPUT_PATH)/clock.o

$(OUTPUT_PATH)/uart.o: $(SRC_DIR)/uart.c
	@echo "compile $(SRC_DIR)/uart.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/uart.c -o $(OUTPUT_PATH)/uart.o

$(OUTPUT_PATH)/startup_ARMCM0.o: $(SRC_DIR)/startup_ARMCM0.S
	@echo -e "compile $(SRC_DIR)/startup_ARMCM0.S file"
	$(ASM) $(ASM_OPT) $(SRC_DIR)/startup_ARMCM0.s -o $(OUTPUT_PATH)/startup_ARMCM0.o

	

build: $(FILE_TO_LINK) $(LINKER_FILE)
	@echo -e "link object files to create new binary image ($(PROJ_NAME).elf)"
	$(LD) $(LD_OPT) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf

hex: $(OUTPUT_PATH)/$(PROJ_NAME).elf
	$(OBJCPY) -O ihex $(OUTPUT_PATH)/$(PROJ_NAME).elf $(OUTPUT_PATH)/$(PROJ_NAME).hex

clean:
	@rm -rf $(OUTPUT_PATH)/*

