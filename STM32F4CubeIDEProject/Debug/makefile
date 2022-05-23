################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := ASD_FFT_F4
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ASD_FFT_F4.elf \

MAP_FILES += \
ASD_FFT_F4.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ASD_FFT_F4.list \


# All Target
all: main-build

# Main-build Target
main-build: ASD_FFT_F4.elf secondary-outputs

# Tool invocations
ASD_FFT_F4.elf ASD_FFT_F4.map: $(OBJS) $(USER_OBJS) C:\Users\Lenovo\Documents\_Moje\Piotr\Pyrograf\Spectrum_audio_display_v2\Audio_Spectrum_Display_V2\Spectrum_Audio_Display_V2\STM32F4CubeIDEProject\STM32F446RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ASD_FFT_F4.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Lenovo\Documents\_Moje\Piotr\Pyrograf\Spectrum_audio_display_v2\Audio_Spectrum_Display_V2\Spectrum_Audio_Display_V2\STM32F4CubeIDEProject\STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ASD_FFT_F4.map" -Wl,--gc-sections -static -L"C:\Users\Lenovo\Documents\_Moje\Piotr\Pyrograf\Spectrum_audio_display_v2\Audio_Spectrum_Display_V2\Spectrum_Audio_Display_V2\STM32F4CubeIDEProject\Drivers\CMSIS\Lib\GCC" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ASD_FFT_F4.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ASD_FFT_F4.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ASD_FFT_F4.elf ASD_FFT_F4.list ASD_FFT_F4.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
