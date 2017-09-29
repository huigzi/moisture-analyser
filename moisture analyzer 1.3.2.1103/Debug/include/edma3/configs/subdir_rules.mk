################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
include/edma3/configs/edma3_c6748_cfg.obj: ../include/edma3/configs/edma3_c6748_cfg.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/driver" --include_path="../include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --define=CHIP_C6748 --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="include/edma3/configs/edma3_c6748_cfg.pp" --obj_directory="include/edma3/configs" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


