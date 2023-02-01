################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/decadriver/deca_device.c 

OBJS += \
./Core/Src/decadriver/deca_device.o 

C_DEPS += \
./Core/Src/decadriver/deca_device.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/decadriver/%.o Core/Src/decadriver/%.su: ../Core/Src/decadriver/%.c Core/Src/decadriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/OneDrive - Conestoga College/Term4/CapstoneProject/Source/Core/Src/decadriver" -I"D:/OneDrive - Conestoga College/Term4/CapstoneProject/Source/Core/Src/platform" -I"D:/OneDrive - Conestoga College/Term4/CapstoneProject/Source/Core/Src/shared_data" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-decadriver

clean-Core-2f-Src-2f-decadriver:
	-$(RM) ./Core/Src/decadriver/deca_device.d ./Core/Src/decadriver/deca_device.o ./Core/Src/decadriver/deca_device.su

.PHONY: clean-Core-2f-Src-2f-decadriver

