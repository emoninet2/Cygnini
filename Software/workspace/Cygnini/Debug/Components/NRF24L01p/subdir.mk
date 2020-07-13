################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/NRF24L01p/NRF24L01p.c \
../Components/NRF24L01p/NRF24L01pDriver.c 

OBJS += \
./Components/NRF24L01p/NRF24L01p.o \
./Components/NRF24L01p/NRF24L01pDriver.o 

C_DEPS += \
./Components/NRF24L01p/NRF24L01p.d \
./Components/NRF24L01p/NRF24L01pDriver.d 


# Each subdirectory must supply rules for building sources it contributes
Components/NRF24L01p/NRF24L01p.o: ../Components/NRF24L01p/NRF24L01p.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L443xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/NRF24L01p" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/C12832" -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Board" -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si7006" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Components/NRF24L01p/NRF24L01p.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Components/NRF24L01p/NRF24L01pDriver.o: ../Components/NRF24L01p/NRF24L01pDriver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L443xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_DEVICE/Target -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/NRF24L01p" -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/C12832" -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Board" -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I"C:/Users/hr193/STM32CubeIDE/workspace_1.3.0/Cygnini/Components/Si7006" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Components/NRF24L01p/NRF24L01pDriver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

