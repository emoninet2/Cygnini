################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/Si1133/Si1133.c 

OBJS += \
./Components/Si1133/Si1133.o 

C_DEPS += \
./Components/Si1133/Si1133.d 


# Each subdirectory must supply rules for building sources it contributes
Components/Si1133/Si1133.o: ../Components/Si1133/Si1133.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L443xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/NRF24L01p" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si7006" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si1133" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/C12832" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Board" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Components/Si1133/Si1133.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

