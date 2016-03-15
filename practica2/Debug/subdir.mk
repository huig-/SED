################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/usuario_local/Downloads/SED/practica2/8led.c \
C:/Users/usuario_local/Downloads/SED/practica2/button.c \
C:/Users/usuario_local/Downloads/SED/practica2/keyboard.c \
C:/Users/usuario_local/Downloads/SED/practica2/led.c \
C:/Users/usuario_local/Downloads/SED/practica2/main.c \
C:/Users/usuario_local/Downloads/SED/practica2/timer.c 

OBJS += \
./8led.o \
./button.o \
./keyboard.o \
./led.o \
./main.o \
./timer.o 

C_DEPS += \
./8led.d \
./button.d \
./keyboard.d \
./led.d \
./main.d \
./timer.d 


# Each subdirectory must supply rules for building sources it contributes
8led.o: C:/Users/usuario_local/Downloads/SED/practica2/8led.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\Users\usuario_local\Downloads\SED\practica2\commonEclipse" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

button.o: C:/Users/usuario_local/Downloads/SED/practica2/button.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\Users\usuario_local\Downloads\SED\practica2\commonEclipse" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

keyboard.o: C:/Users/usuario_local/Downloads/SED/practica2/keyboard.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\Users\usuario_local\Downloads\SED\practica2\commonEclipse" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

led.o: C:/Users/usuario_local/Downloads/SED/practica2/led.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\Users\usuario_local\Downloads\SED\practica2\commonEclipse" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.o: C:/Users/usuario_local/Downloads/SED/practica2/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\Users\usuario_local\Downloads\SED\practica2\commonEclipse" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer.o: C:/Users/usuario_local/Downloads/SED/practica2/timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\Users\usuario_local\Downloads\SED\practica2\commonEclipse" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


