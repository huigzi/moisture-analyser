################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/platform/fr6748_Init.obj: ../src/platform/fr6748_Init.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="C:/Users/tysh0/git/store/moisture analyzer 1.3.2.1103" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="C:/Users/tysh0/git/store/moisture analyzer 1.3.2.1103/include" --include_path="C:/Users/tysh0/git/store/moisture analyzer 1.3.2.1103/include/cslr" --include_path="C:/Users/tysh0/git/store/moisture analyzer 1.3.2.1103/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/platform/fr6748_Init.pp" --obj_directory="src/platform" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/platform/scom.obj: ../src/platform/scom.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="C:/Users/tysh0/git/store/moisture analyzer 1.3.2.1103" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="C:/Users/tysh0/git/store/moisture analyzer 1.3.2.1103/include" --include_path="C:/Users/tysh0/git/store/moisture analyzer 1.3.2.1103/include/cslr" --include_path="C:/Users/tysh0/git/store/moisture analyzer 1.3.2.1103/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/platform/scom.pp" --obj_directory="src/platform" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

