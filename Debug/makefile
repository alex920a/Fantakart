################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include res/models/Oxide/subdir.mk
-include res/models/KartOxide/subdir.mk
-include res/models/KartCrash/subdir.mk
-include res/models/KartCortex/subdir.mk
-include res/models/Crash/subdir.mk
-include res/models/Cortex/subdir.mk
-include res/models/subdir.mk
-include baseclass/subdir.mk
-include Utils/subdir.mk
-include Objects3D/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Progetto_esame

dependents:
	-cd /home/alessandro/Scrivania/Workspace_graphics/Progetto_esame/Release && $(MAKE) all

# Tool invocations
Progetto_esame: $(OBJS) $(USER_OBJS) /home/alessandro/Scrivania/Workspace_graphics/Progetto_esame/Release/Progetto_esame
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "Progetto_esame" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) Progetto_esame
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/home/alessandro/Scrivania/Workspace_graphics/Progetto_esame/Release/Progetto_esame:

-include ../makefile.targets
