################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Utils/GLText.cpp \
../Utils/Timer.cpp \
../Utils/mesh.cpp \
../Utils/polygons.cpp 

OBJS += \
./Utils/GLText.o \
./Utils/Timer.o \
./Utils/mesh.o \
./Utils/polygons.o 

CPP_DEPS += \
./Utils/GLText.d \
./Utils/Timer.d \
./Utils/mesh.d \
./Utils/polygons.d 


# Each subdirectory must supply rules for building sources it contributes
Utils/%.o: ../Utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/alessandro/Scrivania/Workspace_graphics/Progetto_esame/Utils -I/home/alessandro/Scrivania/Workspace_graphics/Progetto_esame/baseclass -I/home/alessandro/Scrivania/Workspace_graphics/Progetto_esame/res/models -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


