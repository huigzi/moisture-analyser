################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
include/edma3/edma3_drv_adv.obj: ../include/edma3/edma3_drv_adv.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/cslr" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/driver" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/edma3" --define=CHIP_C6748 --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="include/edma3/edma3_drv_adv.pp" --obj_directory="include/edma3" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/edma3/edma3_drv_basic.obj: ../include/edma3/edma3_drv_basic.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/cslr" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/driver" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/edma3" --define=CHIP_C6748 --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="include/edma3/edma3_drv_basic.pp" --obj_directory="include/edma3" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/edma3/edma3_drv_init.obj: ../include/edma3/edma3_drv_init.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/cslr" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/driver" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/edma3" --define=CHIP_C6748 --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="include/edma3/edma3_drv_init.pp" --obj_directory="include/edma3" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/edma3/edma3_rm_gbl_data.obj: ../include/edma3/edma3_rm_gbl_data.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/cslr" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/driver" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/edma3" --define=CHIP_C6748 --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="include/edma3/edma3_rm_gbl_data.pp" --obj_directory="include/edma3" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/edma3/edma3resmgr.obj: ../include/edma3/edma3resmgr.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/cslr" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/driver" --include_path="E:/work/faceR/project/guao/ccs5.3/ndk_evm6748_elf_cfg_guao_20130715/ndk_evm6748_elf_cfg_guao/include/edma3" --define=CHIP_C6748 --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="include/edma3/edma3resmgr.pp" --obj_directory="include/edma3" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


