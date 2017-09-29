################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/network/emacHooks.obj: ../src/network/emacHooks.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/driver" --include_path="../include" --include_path="C:/Users/tysh0/workspace/Hyeta_camtest" --include_path="C:/ti/ndk_2_22_03_20/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_03_20/packages/ti/ndk/inc/tools" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/network/emacHooks.pp" --obj_directory="src/network" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/network/networkmain.obj: ../src/network/networkmain.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/driver" --include_path="../include" --include_path="C:/Users/tysh0/workspace/Hyeta_camtest" --include_path="C:/ti/ndk_2_22_03_20/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_03_20/packages/ti/ndk/inc/tools" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/network/networkmain.pp" --obj_directory="src/network" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


