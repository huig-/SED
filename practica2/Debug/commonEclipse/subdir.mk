################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/usuario_local/Downloads/SED/practica2/commonEclipse/44blib.c 

ASM_SRCS += \
C:/Users/usuario_local/Downloads/SED/practica2/commonEclipse/44binit.asm 

OBJS += \
./commonEclipse/44binit.o \
./commonEclipse/44blib.o 

C_DEPS += \
./commonEclipse/44blib.d 

ASM_DEPS += \
./commonEclipse/44binit.d 


# Each subdirectory must supply rules for building sources it contributes
commonEclipse/44binit.o: C:/Users/usuario_local/Downloads/SED/practica2/commonEclipse/44binit.asm
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -I"C:\Users\usuario_local\Downloads\SED\practica2\commonEclipse" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

commonEclipse/44blib.o: C:/Users/usuario_local/Downloads/SED/practica2/commonEclipse/44blib.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\Users\usuario_local\Downloads\SED\practica2\commonEclipse" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

