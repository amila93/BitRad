################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/platform/deca_mutex.c \
../Core/Src/platform/deca_sleep.c \
../Core/Src/platform/deca_spi.c \
../Core/Src/platform/port.c 

OBJS += \
./Core/Src/platform/deca_mutex.o \
./Core/Src/platform/deca_sleep.o \
./Core/Src/platform/deca_spi.o \
./Core/Src/platform/port.o 

C_DEPS += \
./Core/Src/platform/deca_mutex.d \
./Core/Src/platform/deca_sleep.d \
./Core/Src/platform/deca_spi.d \
./Core/Src/platform/port.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/platform/%.o Core/Src/platform/%.su: ../Core/Src/platform/%.c Core/Src/platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/OneDrive - Conestoga College/Term4/CapstoneProject/Source/Core/Src/decadriver" -I"D:/OneDrive - Conestoga College/Term4/CapstoneProject/Source/Core/Src/platform" -I"D:/OneDrive - Conestoga College/Term4/CapstoneProject/Source/Core/Src/shared_data" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-platform

clean-Core-2f-Src-2f-platform:
	-$(RM) ./Core/Src/platform/deca_mutex.d ./Core/Src/platform/deca_mutex.o ./Core/Src/platform/deca_mutex.su ./Core/Src/platform/deca_sleep.d ./Core/Src/platform/deca_sleep.o ./Core/Src/platform/deca_sleep.su ./Core/Src/platform/deca_spi.d ./Core/Src/platform/deca_spi.o ./Core/Src/platform/deca_spi.su ./Core/Src/platform/port.d ./Core/Src/platform/port.o ./Core/Src/platform/port.su

.PHONY: clean-Core-2f-Src-2f-platform

