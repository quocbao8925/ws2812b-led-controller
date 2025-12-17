################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS4/Source/CommonTables/arm_common_tables.c \
../Drivers/CMSIS4/Source/CommonTables/arm_const_structs.c 

OBJS += \
./Drivers/CMSIS4/Source/CommonTables/arm_common_tables.o \
./Drivers/CMSIS4/Source/CommonTables/arm_const_structs.o 

C_DEPS += \
./Drivers/CMSIS4/Source/CommonTables/arm_common_tables.d \
./Drivers/CMSIS4/Source/CommonTables/arm_const_structs.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS4/Source/CommonTables/%.o Drivers/CMSIS4/Source/CommonTables/%.su Drivers/CMSIS4/Source/CommonTables/%.cyclo: ../Drivers/CMSIS4/Source/CommonTables/%.c Drivers/CMSIS4/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/Progs/STM32CubeIDE_1.17.0/Workspace/leds/Drivers/CMSIS4/Include" -IC:/Users/ASUS/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/ASUS/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/ASUS/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/ASUS/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -I"D:/Progs/STM32CubeIDE_1.17.0/Workspace/leds/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS4-2f-Source-2f-CommonTables

clean-Drivers-2f-CMSIS4-2f-Source-2f-CommonTables:
	-$(RM) ./Drivers/CMSIS4/Source/CommonTables/arm_common_tables.cyclo ./Drivers/CMSIS4/Source/CommonTables/arm_common_tables.d ./Drivers/CMSIS4/Source/CommonTables/arm_common_tables.o ./Drivers/CMSIS4/Source/CommonTables/arm_common_tables.su ./Drivers/CMSIS4/Source/CommonTables/arm_const_structs.cyclo ./Drivers/CMSIS4/Source/CommonTables/arm_const_structs.d ./Drivers/CMSIS4/Source/CommonTables/arm_const_structs.o ./Drivers/CMSIS4/Source/CommonTables/arm_const_structs.su

.PHONY: clean-Drivers-2f-CMSIS4-2f-Source-2f-CommonTables

