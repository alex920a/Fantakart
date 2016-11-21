################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CameraHandler.cpp \
../GameControl_handler.cpp \
../Light_handler.cpp \
../Sound_handler.cpp \
../Texture_handler.cpp \
../main.cpp 

OBJS += \
./CameraHandler.o \
./GameControl_handler.o \
./Light_handler.o \
./Sound_handler.o \
./Texture_handler.o \
./main.o 

CPP_DEPS += \
./CameraHandler.d \
./GameControl_handler.d \
./Light_handler.d \
./Sound_handler.d \
./Texture_handler.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/alessandro/Scrivania/Workspace_graphics/Progetto_esame/Utils -I/home/alessandro/Scrivania/Workspace_graphics/Progetto_esame/baseclass -I/home/alessandro/Scrivania/Workspace_graphics/Progetto_esame/res/models -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


