
# cross compilation tools
XTOOLS_DIR = /opt/gcc-arm-none-eabi-4_8-2014q1
X_LIBC_DIR = $(XTOOLS_DIR)/arm-none-eabi/lib/armv7e-m/fpu
X_LIBGCC_DIR = $(XTOOLS_DIR)/lib/gcc/arm-none-eabi/4.8.3/armv7e-m/fpu
X_CC = $(XTOOLS_DIR)/bin/arm-none-eabi-gcc
X_OBJCOPY = $(XTOOLS_DIR)/bin/arm-none-eabi-objcopy
X_AR = $(XTOOLS_DIR)/bin/arm-none-eabi-ar
X_LD = $(XTOOLS_DIR)/bin/arm-none-eabi-ld
X_GDB = $(XTOOLS_DIR)/bin/arm-none-eabi-gdb

OUTPUT = tetris_stm32f4

# hal sources
HAL_DIR = ./hal/src
SRC += $(HAL_DIR)/stm32f4xx_hal.c \
       $(HAL_DIR)/stm32f4xx_hal_rcc.c \
       $(HAL_DIR)/stm32f4xx_hal_pwr_ex.c \
       $(HAL_DIR)/stm32f4xx_hal_cortex.c \
       $(HAL_DIR)/stm32f4xx_hal_gpio.c \

# game sources
GAME_DIR = ./game
SRC += $(GAME_DIR)/main.c \
       $(GAME_DIR)/system_stm32f4xx.c \
       $(GAME_DIR)/stm32f4xx_it.c \
       $(GAME_DIR)/gpio.c \
       $(GAME_DIR)/debounce.c \

OBJ = $(patsubst %.c, %.o, $(SRC))
OBJ += $(GAME_DIR)/start.o

# include files
INC = .
INC += ./cmsis
INC += ./hal/inc
INC += $(GAME_DIR)

INCLUDE = $(addprefix -I,$(INC))

# compiler flags
CFLAGS = -Wall
CFLAGS += -O
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

# linker flags
LDSCRIPT = stm32f429zi_flash.ld
LDFLAGS = -T$(LDSCRIPT) -Wl,-Map,$(OUTPUT).map -Wl,--gc-sections

DEFINES = -DSTM32F429xx

.S.o:
	$(X_CC) $(INCLUDE) $(DEFINES) $(CFLAGS) -c $< -o $@
.c.o:
	$(X_CC) $(INCLUDE) $(DEFINES) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	$(X_CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -lm -o $(OUTPUT)
	$(X_OBJCOPY) -O binary $(OUTPUT) $(OUTPUT).bin

.PHONY: program
program: 
	st-flash write $(OUTPUT).bin 0x08000000

clean:
	-rm $(OBJ)	
	-rm $(OUTPUT)
	-rm $(OUTPUT).map	
	-rm $(OUTPUT).bin	
