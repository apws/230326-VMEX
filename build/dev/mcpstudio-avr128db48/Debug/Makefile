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
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../../../../src/VMEX.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
VMEX.o

OBJS_AS_ARGS +=  \
VMEX.o

C_DEPS +=  \
VMEX.d

C_DEPS_AS_ARGS +=  \
VMEX.d

OUTPUT_FILE_PATH +=VMEX.elf

OUTPUT_FILE_PATH_AS_ARGS +=VMEX.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./VMEX.o: ../../../../src/VMEX.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.36
	$(QUOTE)D:\~app\~tools\~hw-dev\microchip\xc8\bin\xc8-cc.exe$(QUOTE)  -mcpu=AVR128DB48  -mdfp="D:\~app\~tools\~hw-dev\atmel\studio\7.0\Packs\atmel\AVR-Dx_DFP\1.10.114\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__AVR128DB48__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g3 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	@echo Invoking:  XC8 C Linker : 2.36
	$(QUOTE)D:\~app\~tools\~hw-dev\microchip\xc8\bin\xc8-cc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mcpu=AVR128DB48  -mdfp="D:\~app\~tools\~hw-dev\atmel\studio\7.0\Packs\atmel\AVR-Dx_DFP\1.10.114\xc8"  -Wl,-Map="VMEX.map" -funsigned-char -funsigned-bitfields -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums --memorysummary,memoryfile.xml  
	@echo Finished building target: $@
	"D:\~app\~tools\~hw-dev\microchip\xc8\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "VMEX.elf" "VMEX.hex"
	"D:\~app\~tools\~hw-dev\microchip\xc8\bin\avr-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "VMEX.elf" "VMEX.eep" || exit 0
	"D:\~app\~tools\~hw-dev\microchip\xc8\bin\avr-objdump.exe" -h -S "VMEX.elf" > "VMEX.lss"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "VMEX.elf" "VMEX.hex" "VMEX.eep" "VMEX.map" "VMEX.usersignatures" "VMEX.a"  "VMEX.lss"
	