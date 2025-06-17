################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Device_Startup/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../../../../src/VMEX.c \
../Device_Startup/startup_samd21.c \
../Device_Startup/system_samd21.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
VMEX.o \
Device_Startup/startup_samd21.o \
Device_Startup/system_samd21.o

OBJS_AS_ARGS +=  \
VMEX.o \
Device_Startup/startup_samd21.o \
Device_Startup/system_samd21.o

C_DEPS +=  \
VMEX.d \
Device_Startup/startup_samd21.d \
Device_Startup/system_samd21.d

C_DEPS_AS_ARGS +=  \
VMEX.d \
Device_Startup/startup_samd21.d \
Device_Startup/system_samd21.d

OUTPUT_FILE_PATH +=VMEX_ARM.elf

OUTPUT_FILE_PATH_AS_ARGS +=VMEX_ARM.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+=  \
../Device_Startup/samd21g17d_flash.ld \
../Device_Startup/samd21g17d_sram.ld


# AVR32/GNU C Compiler
./VMEX.o: ../../../../src/VMEX.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)D:\~app\~tools\~hw-dev\atmel\studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAMD21G17D__ -DDEBUG  -I"D:\~app\~tools\~hw-dev\atmel\studio\7.0\Packs\arm\CMSIS\5.4.0\CMSIS\Core\Include" -I"D:\~app\~tools\~hw-dev\atmel\studio\7.0\Packs\atmel\SAMD21_DFP\1.3.395\samd21d\include"  -Og -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m0plus -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Device_Startup/startup_samd21.o: ../Device_Startup/startup_samd21.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)D:\~app\~tools\~hw-dev\atmel\studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAMD21G17D__ -DDEBUG  -I"D:\~app\~tools\~hw-dev\atmel\studio\7.0\Packs\arm\CMSIS\5.4.0\CMSIS\Core\Include" -I"D:\~app\~tools\~hw-dev\atmel\studio\7.0\Packs\atmel\SAMD21_DFP\1.3.395\samd21d\include"  -Og -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m0plus -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Device_Startup/system_samd21.o: ../Device_Startup/system_samd21.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.3.1
	$(QUOTE)D:\~app\~tools\~hw-dev\atmel\studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAMD21G17D__ -DDEBUG  -I"D:\~app\~tools\~hw-dev\atmel\studio\7.0\Packs\arm\CMSIS\5.4.0\CMSIS\Core\Include" -I"D:\~app\~tools\~hw-dev\atmel\studio\7.0\Packs\atmel\SAMD21_DFP\1.3.395\samd21d\include"  -Og -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m0plus -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: ARM/GNU Linker : 6.3.1
	$(QUOTE)D:\~app\~tools\~hw-dev\atmel\studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mthumb -Wl,-Map="VMEX_ARM.map" -Wl,--start-group -lm  -Wl,--end-group -L"..\\Device_Startup"  -Wl,--gc-sections -mcpu=cortex-m0plus -Tsamd21g17d_flash.ld  
	@echo Finished building target: $@
	"D:\~app\~tools\~hw-dev\atmel\studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O binary "VMEX_ARM.elf" "VMEX_ARM.bin"
	"D:\~app\~tools\~hw-dev\atmel\studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "VMEX_ARM.elf" "VMEX_ARM.hex"
	"D:\~app\~tools\~hw-dev\atmel\studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O binary "VMEX_ARM.elf" "VMEX_ARM.eep" || exit 0
	"D:\~app\~tools\~hw-dev\atmel\studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objdump.exe" -h -S "VMEX_ARM.elf" > "VMEX_ARM.lss"
	"D:\~app\~tools\~hw-dev\atmel\studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "VMEX_ARM.elf" "VMEX_ARM.srec"
	"D:\~app\~tools\~hw-dev\atmel\studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-size.exe" "VMEX_ARM.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "VMEX_ARM.elf" "VMEX_ARM.a" "VMEX_ARM.hex" "VMEX_ARM.bin" "VMEX_ARM.lss" "VMEX_ARM.eep" "VMEX_ARM.map" "VMEX_ARM.srec"
	