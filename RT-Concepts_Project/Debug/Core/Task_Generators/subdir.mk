################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Task_Generators/Task_Generator.c 

OBJS += \
./Core/Task_Generators/Task_Generator.o 

C_DEPS += \
./Core/Task_Generators/Task_Generator.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Task_Generators/%.o Core/Task_Generators/%.su Core/Task_Generators/%.cyclo: ../Core/Task_Generators/%.c Core/Task_Generators/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"/home/doomnuke/RT-Concepts/RT-Concepts_Project/Core/common" -I"/home/doomnuke/RT-Concepts/RT-Concepts_Project/Core/Department-Tasks" -I"/home/doomnuke/RT-Concepts/RT-Concepts_Project/Core/Dispatcher" -I"/home/doomnuke/RT-Concepts/RT-Concepts_Project/Core/Task_Generators" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Task_Generators

clean-Core-2f-Task_Generators:
	-$(RM) ./Core/Task_Generators/Task_Generator.cyclo ./Core/Task_Generators/Task_Generator.d ./Core/Task_Generators/Task_Generator.o ./Core/Task_Generators/Task_Generator.su

.PHONY: clean-Core-2f-Task_Generators

