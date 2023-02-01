################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/shared_data/shared_functions.c 

OBJS += \
./Core/Src/shared_data/shared_functions.o 

C_DEPS += \
./Core/Src/shared_data/shared_functions.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/shared_data/%.o Core/Src/shared_data/%.su: ../Core/Src/shared_data/%.c Core/Src/shared_data/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/OneDrive - Conestoga College/Term4/CapstoneProject/Source/Core/Src/decadriver" -I"D:/OneDrive - Conestoga College/Term4/CapstoneProject/Source/Core/Src/platform" -I"D:/OneDrive - Conestoga College/Term4/CapstoneProject/Source/Core/Src/shared_data" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-shared_data

clean-Core-2f-Src-2f-shared_data:
	-$(RM) ./Core/Src/shared_data/shared_functions.d ./Core/Src/shared_data/shared_functions.o ./Core/Src/shared_data/shared_functions.su

.PHONY: clean-Core-2f-Src-2f-shared_data

