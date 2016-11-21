################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Objects3D/Bomb.cpp \
../Objects3D/Crystal.cpp \
../Objects3D/Hole.cpp \
../Objects3D/Hourglass.cpp \
../Objects3D/Kart.cpp \
../Objects3D/MiniMap.cpp \
../Objects3D/PhotoId.cpp \
../Objects3D/Player.cpp \
../Objects3D/Speedometer.cpp \
../Objects3D/World.cpp 

OBJS += \
./Objects3D/Bomb.o \
./Objects3D/Crystal.o \
./Objects3D/Hole.o \
./Objects3D/Hourglass.o \
./Objects3D/Kart.o \
./Objects3D/MiniMap.o \
./Objects3D/PhotoId.o \
./Objects3D/Player.o \
./Objects3D/Speedometer.o \
./Objects3D/World.o 

CPP_DEPS += \
./Objects3D/Bomb.d \
./Objects3D/Crystal.d \
./Objects3D/Hole.d \
./Objects3D/Hourglass.d \
./Objects3D/Kart.d \
./Objects3D/MiniMap.d \
./Objects3D/PhotoId.d \
./Objects3D/Player.d \
./Objects3D/Speedometer.d \
./Objects3D/World.d 


# Each subdirectory must supply rules for building sources it contributes
Objects3D/%.o: ../Objects3D/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


