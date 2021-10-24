TARGET = make103
BUILD_DIR = build

C_SOURCES2 =  \
FWLIB/src/misc.c  \
FWLIB/src/stm32f4xx_gpio.c  \
FWLIB/src/stm32f4xx_usart.c  \
FWLIB/src/stm32f4xx_rcc.c  \
FWLIB/src/stm32f4xx_exti.c  \
FWLIB/src/stm32f4xx_syscfg.c  \
FWLIB/src/stm32f4xx_dma.c  \
FWLIB/src/stm32f4xx_tim.c  \
FWLIB/src/stm32f4xx_fsmc.c  \
FWLIB/src/stm32f4xx_dcmi.c  \
system/delay/delay.c  \
system/sys/sys.c  \
system/usart/usart.c  \
user/main.c  \
user/stm32f4xx_it.c  \
user/system_stm32f4xx.c  \
hardware/src/key.c  \
hardware/src/led.c  \
hardware/src/inout.c  \
hardware/src/exti.c  \
hardware/src/lcd.c  \
hardware/src/timer.c  \
hardware/src/ov2640.c  \
hardware/src/sccb.c  \
hardware/src/dcmi.c  \

# C includes
C_INCLUDES =  \
-ICORE \
-IFWLIB/inc  \
-Ihardware/inc  \
-Isystem/delay  \
-Isystem/sys  \
-Isystem/usart  \
-Iuser

C_SOURCES= $(sort $(C_SOURCES2))

# LDSCRIPT = STM32F103C8Tx_FLASH.ld
# LDSCRIPT = STM32F103ZETx_FLASH.ld
# LDSCRIPT = STM32F407VETx_FLASH.ld
LDSCRIPT = STM32F407ZGTx_FLASH.ld

# ASM sources
ASM_SOURCES =  \
startup_stm32f407xx.s
# startup_stm32f407xx.s
# startup_stm32f103xe.s
# startup_stm32f103xb.s 

# CFLAGS= -mcpu=cortex-m3 -mthumb -DSTM32F103xB -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DAPP_DEBUG=0 $(C_INCLUDES)  -Wall -fdata-sections -ffunction-sections -lc -lm -lnosys  -g -gdwarf-2 -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"
# CFLAGS= -mcpu=cortex-m3 -mthumb -DSTM32F103xE -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DAPP_DEBUG=0 $(C_INCLUDES)  -Wall -fdata-sections -ffunction-sections -lc -lm -lnosys  -g -gdwarf-2 -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"
CFLAGS= -mcpu=cortex-m4 -mthumb -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DAPP_DEBUG=0 $(C_INCLUDES)  -Wall -fdata-sections -ffunction-sections -lc -lm -lnosys  -g -gdwarf-2 -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"
# STM32F40_41xxx,USE_STDPERIPH_DRIVER  in keil
# -DSTM32F407xx  in cubemx

# ASFLAGS= -mcpu=cortex-m3 -mthumb -DSTM32F103xB -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DAPP_DEBUG=0 $(C_INCLUDES)  -Wall -fdata-sections -ffunction-sections -lc -lm -lnosys  -g -gdwarf-2   -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" 
# ASFLAGS= -mcpu=cortex-m3 -mthumb -DSTM32F103xE -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DAPP_DEBUG=0 $(C_INCLUDES)  -Wall -fdata-sections -ffunction-sections -lc -lm -lnosys  -g -gdwarf-2   -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" 
ASFLAGS= -mcpu=cortex-m4 -mthumb -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DAPP_DEBUG=0 $(C_INCLUDES)  -Wall -fdata-sections -ffunction-sections -lc -lm -lnosys  -g -gdwarf-2   -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" 

# LDFLAGS = -mcpu=cortex-m3  -mthumb -specs=nano.specs -T$(LDSCRIPT)  -lc -lm -lnosys -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
LDFLAGS = -mcpu=cortex-m4  -mthumb -specs=nano.specs -T$(LDSCRIPT)  -lc -lm -lnosys -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
  
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

PREFIX = arm-none-eabi-
CC = $(BINPATH) $(PREFIX)gcc
AS = $(BINPATH) $(PREFIX)gcc -x assembler-with-cpp
CP = $(BINPATH) $(PREFIX)objcopy
AR = $(BINPATH) $(PREFIX)ar
SZ = $(BINPATH) $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

all:   $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).elf  $(BUILD_DIR)/$(TARGET).bin  $(BUILD_DIR)/$(TARGET).hex  
	 
$(BUILD_DIR)/%.o: %.c    
	$(CC) -c $(CFLAGS) $^ -o $@
	@echo Building $@
$(BUILD_DIR)/%.o:%.s   
	$(AS) -c $(CFLAGS) $^ -o $@
	
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) build/led.o  
	$(CC) $^ $(LDFLAGS) -o $@
	$(SZ) $@
	
$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf 
	$(HEX) $^ $@ 
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf 
	$(BIN) $^ $@	
	
$(BUILD_DIR):
	mkdir $@
clean:
	-rm -fR .dep $(BUILD_DIR)
