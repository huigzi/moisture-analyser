################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/c6000_7.4.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./src/app/boot/myboot.obj" \
"./src/app/main/fr_main.obj" \
"./src/app/main/evminit.obj" \
"./src/app/network/networkmain.obj" \
"./src/app/network/emacHooks.obj" \
"./src/app/tasks/taskUartMaster.obj" \
"./src/app/tasks/taskImageProcess.obj" \
"./src/app/tasks/taskImageInput.obj" \
"./src/app/uart/fr_uart.obj" \
"./src/driver/timer.obj" \
"./src/driver/sysdelay.obj" \
"./src/driver/rtc.obj" \
"./src/driver/hal_usbhost_timer.obj" \
"./src/driver/cslr_uart.obj" \
"./src/driver/cppi41dma.obj" \
"./src/driver/Upp_ioctl.obj" \
"./src/driver/Upp.obj" \
"./src/driver/Uart_edma.obj" \
"./src/driver/Uart.obj" \
"./src/driver/Spi_edma.obj" \
"./src/driver/Spi.obj" \
"./src/driver/Psc.obj" \
"./src/driver/I2c_edma.obj" \
"./src/driver/I2c.obj" \
"./src/driver/Gpio.obj" \
"./src/platform/scom.obj" \
"./src/platform/guao6748_Init.obj" \
-l"libc.a" \
-l"C:\ti\edma3_lld_02_11_04_01\packages\ti\sdo\edma3\drv\lib\674\debug\edma3_lld_drv.ae674" \
-l"C:\ti\edma3_lld_02_11_04_01\packages\ti\sdo\edma3\rm\sample\lib\c6748-evm\674\debug\edma3_lld_rm_sample.ae674" \
-l"C:\ti\edma3_lld_02_11_04_01\packages\ti\sdo\edma3\drv\sample\lib\c6748-evm\674\debug\edma3_lld_drv_sample.ae674" \
-l"C:\ti\edma3_lld_02_11_04_01\packages\ti\sdo\edma3\rm\lib\c6748-evm\674\debug\edma3_lld_rm.ae674" \
"../fr_c6748_drv.lib" \
"../gooao_c6748.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/platform/subdir_vars.mk
-include src/driver/subdir_vars.mk
-include src/app/uart/subdir_vars.mk
-include src/app/tasks/subdir_vars.mk
-include src/app/network/subdir_vars.mk
-include src/app/main/subdir_vars.mk
-include src/app/boot/subdir_vars.mk
-include subdir_rules.mk
-include src/platform/subdir_rules.mk
-include src/driver/subdir_rules.mk
-include src/app/uart/subdir_rules.mk
-include src/app/tasks/subdir_rules.mk
-include src/app/network/subdir_rules.mk
-include src/app/main/subdir_rules.mk
-include src/app/boot/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: fr_flir_cmos_c6748.out

# Tool invocations
fr_flir_cmos_c6748.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 -z -m"ndk_evm6748_elf_cfg_guao.map" -i"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/lib" -i"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --reread_libs --diag_warning=225 --warn_sections --rom_model -o "fr_flir_cmos_c6748.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_SRCS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(C6000_EXECUTABLE_OUTPUTS__QUOTED)$(GEN_OPTS__QUOTED)$(GEN_CMDS__QUOTED) "fr_flir_cmos_c6748.out"
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-$(RM) "src\platform\guao6748_Init.pp" "src\platform\scom.pp" "src\driver\Gpio.pp" "src\driver\I2c.pp" "src\driver\I2c_edma.pp" "src\driver\Psc.pp" "src\driver\Spi.pp" "src\driver\Spi_edma.pp" "src\driver\Uart.pp" "src\driver\Uart_edma.pp" "src\driver\Upp.pp" "src\driver\Upp_ioctl.pp" "src\driver\cppi41dma.pp" "src\driver\cslr_uart.pp" "src\driver\hal_usbhost_timer.pp" "src\driver\rtc.pp" "src\driver\sysdelay.pp" "src\driver\timer.pp" "src\app\uart\fr_uart.pp" "src\app\tasks\taskImageInput.pp" "src\app\tasks\taskImageProcess.pp" "src\app\tasks\taskUartMaster.pp" "src\app\network\emacHooks.pp" "src\app\network\networkmain.pp" "src\app\main\evminit.pp" "src\app\main\fr_main.pp" 
	-$(RM) "src\platform\guao6748_Init.obj" "src\platform\scom.obj" "src\driver\Gpio.obj" "src\driver\I2c.obj" "src\driver\I2c_edma.obj" "src\driver\Psc.obj" "src\driver\Spi.obj" "src\driver\Spi_edma.obj" "src\driver\Uart.obj" "src\driver\Uart_edma.obj" "src\driver\Upp.obj" "src\driver\Upp_ioctl.obj" "src\driver\cppi41dma.obj" "src\driver\cslr_uart.obj" "src\driver\hal_usbhost_timer.obj" "src\driver\rtc.obj" "src\driver\sysdelay.obj" "src\driver\timer.obj" "src\app\uart\fr_uart.obj" "src\app\tasks\taskImageInput.obj" "src\app\tasks\taskImageProcess.obj" "src\app\tasks\taskUartMaster.obj" "src\app\network\emacHooks.obj" "src\app\network\networkmain.obj" "src\app\main\evminit.obj" "src\app\main\fr_main.obj" "src\app\boot\myboot.obj" 
	-$(RM) "src\app\boot\myboot.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
