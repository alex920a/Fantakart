################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../baseclass/GameStatus.cpp \
../baseclass/Handler.cpp \
../baseclass/Model3D.cpp 

OBJS += \
./baseclass/GameStatus.o \
./baseclass/Handler.o \
./baseclass/Model3D.o 

CPP_DEPS += \
./baseclass/GameStatus.d \
./baseclass/Handler.d \
./baseclass/Model3D.d 


# Each subdirectory must supply rules for building sources it contributes
baseclass/%.o: ../baseclass/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


