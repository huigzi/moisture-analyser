################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/app/flash/spi_flash.obj: ../src/app/flash/spi_flash.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/cslr" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/app/flash/spi_flash.pp" --obj_directory="src/app/flash" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

