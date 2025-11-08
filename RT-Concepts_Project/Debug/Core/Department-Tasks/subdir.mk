################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Department-Tasks/Department-Tasks.c 

OBJS += \
./Core/Department-Tasks/Department-Tasks.o 

C_DEPS += \
./Core/Department-Tasks/Department-Tasks.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Department-Tasks/%.o Core/Department-Tasks/%.su Core/Department-Tasks/%.cyclo: ../Core/Department-Tasks/%.c Core/Department-Tasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"/home/doomnuke/RT-Concepts/RT-Concepts_Project/Core/common" -I"/home/doomnuke/RT-Concepts/RT-Concepts_Project/Core/Department-Tasks" -I"/home/doomnuke/RT-Concepts/RT-Concepts_Project/Core/Dispatcher" -I"/home/doomnuke/RT-Concepts/RT-Concepts_Project/Core/Task_Generators" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Department-2d-Tasks

clean-Core-2f-Department-2d-Tasks:
	-$(RM) ./Core/Department-Tasks/Department-Tasks.cyclo ./Core/Department-Tasks/Department-Tasks.d ./Core/Department-Tasks/Department-Tasks.o ./Core/Department-Tasks/Department-Tasks.su

.PHONY: clean-Core-2f-Department-2d-Tasks

