################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/C12832/C12832Port.c \
../Components/C12832/font.c \
../Components/C12832/graphic_lcd.c \
../Components/C12832/st7565r.c 

OBJS += \
./Components/C12832/C12832Port.o \
./Components/C12832/font.o \
./Components/C12832/graphic_lcd.o \
./Components/C12832/st7565r.o 

C_DEPS += \
./Components/C12832/C12832Port.d \
./Components/C12832/font.d \
./Components/C12832/graphic_lcd.d \
./Components/C12832/st7565r.d 


# Each subdirectory must supply rules for building sources it contributes
Components/C12832/C12832Port.o: ../Components/C12832/C12832Port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L443xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/NRF24L01p" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si7006" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si1133" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/C12832" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Board" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Components/C12832/C12832Port.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Components/C12832/font.o: ../Components/C12832/font.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L443xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/NRF24L01p" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si7006" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si1133" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/C12832" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Board" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Components/C12832/font.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Components/C12832/graphic_lcd.o: ../Components/C12832/graphic_lcd.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L443xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/NRF24L01p" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si7006" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si1133" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/C12832" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Board" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Components/C12832/graphic_lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Components/C12832/st7565r.o: ../Components/C12832/st7565r.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L443xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/NRF24L01p" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si7006" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si1133" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/C12832" -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Board" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Components/C12832/st7565r.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

