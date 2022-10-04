################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/src/ADC_config.c \
../Driver/src/LCD.c \
../Driver/src/gpio.c 

OBJS += \
./Driver/src/ADC_config.o \
./Driver/src/LCD.o \
./Driver/src/gpio.o 

C_DEPS += \
./Driver/src/ADC_config.d \
./Driver/src/LCD.d \
./Driver/src/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/src/%.o: ../Driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401CCUx -DDEBUG -DSTM32F401xx -I"C:/Users/Omar Mansour/workspace/FinalProject_ADC/Driver/inc" -I"C:/Users/Omar Mansour/workspace/FinalProject_ADC/inc" -I"C:/Users/Omar Mansour/workspace/FinalProject_ADC/CMSIS/device" -I"C:/Users/Omar Mansour/workspace/FinalProject_ADC/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


