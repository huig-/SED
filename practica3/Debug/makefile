################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include commonEclipse/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
prac3.hex \

SECONDARY_LIST += \
prac3.lst \

SECONDARY_SIZE += \
prac3.siz \


# All Target
all: prac3.elf secondary-outputs

# Tool invocations
prac3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C++ Linker'
	arm-none-eabi-g++ -T"C:\hlocal\EclipseARMwspace\prac3\commonEclipse\ld_script_iic.ld" -L"C:\software\electronica\ARM\EclipseARM\eclipse\/../sourcery-g++-lite-arm-2011.03/arm-none-eabi/lib" -L"C:\hlocal\EclipseARMwspace\prac3\commonEclipse" -L"C:\software\electronica\ARM\EclipseARM\eclipse\/../sourcery-g++-lite-arm-2011.03/lib/gcc/arm-none-eabi/4.5.2" -Wl,-Map,prac3.map -mcpu=arm7tdmi -g3 -gdwarf-2 -o "prac3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

prac3.hex: prac3.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary prac3.elf  "prac3.hex"
	@echo 'Finished building: $@'
	@echo ' '

prac3.lst: prac3.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S prac3.elf > "prac3.lst"
	@echo 'Finished building: $@'
	@echo ' '

prac3.siz: prac3.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley prac3.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(SECONDARY_FLASH)$(CXX_DEPS)$(S_UPPER_DEPS)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS) prac3.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
