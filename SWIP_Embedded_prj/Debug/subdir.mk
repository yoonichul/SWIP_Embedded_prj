################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ASCLIN_Shell_UART.c \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../adc.c \
../button.c \
../interrupt.c \
../led.c \
../light_sensor.c \
../pwm.c \
../timer.c 

OBJS += \
./ASCLIN_Shell_UART.o \
./Cpu0_Main.o \
./Cpu1_Main.o \
./Cpu2_Main.o \
./adc.o \
./button.o \
./interrupt.o \
./led.o \
./light_sensor.o \
./pwm.o \
./timer.o 

COMPILED_SRCS += \
./ASCLIN_Shell_UART.src \
./Cpu0_Main.src \
./Cpu1_Main.src \
./Cpu2_Main.src \
./adc.src \
./button.src \
./interrupt.src \
./led.src \
./light_sensor.src \
./pwm.src \
./timer.src 

C_DEPS += \
./ASCLIN_Shell_UART.d \
./Cpu0_Main.d \
./Cpu1_Main.d \
./Cpu2_Main.d \
./adc.d \
./button.d \
./interrupt.d \
./led.d \
./light_sensor.d \
./pwm.d \
./timer.d 


# Each subdirectory must supply rules for building sources it contributes
%.src: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc27xd "-fC:/Users/user/Desktop/SWIP_Embedded_prj/SWIP_Embedded_prj/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.src subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


