################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/color_values.c \
../src/ws2812.c \
../src/ws2812_demos.c 

OBJS += \
./src/color_values.o \
./src/ws2812.o \
./src/ws2812_demos.o 

C_DEPS += \
./src/color_values.d \
./src/ws2812.d \
./src/ws2812_demos.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o src/%.su src/%.cyclo: ../src/%.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -IC:/Users/ASUS/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/ASUS/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/ASUS/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/ASUS/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -I"D:/Progs/STM32CubeIDE_1.17.0/Workspace/leds/src" -I"D:/Progs/STM32CubeIDE_1.17.0/Workspace/leds/Drivers/STM32F4xx_HAL_Driver" -IC:/Users/ASUS/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-ALGOBUILD/1.4.0/Middlewares/Third_Party/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src

clean-src:
	-$(RM) ./src/color_values.cyclo ./src/color_values.d ./src/color_values.o ./src/color_values.su ./src/ws2812.cyclo ./src/ws2812.d ./src/ws2812.o ./src/ws2812.su ./src/ws2812_demos.cyclo ./src/ws2812_demos.d ./src/ws2812_demos.o ./src/ws2812_demos.su

.PHONY: clean-src

