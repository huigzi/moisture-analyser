################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/app/tasks/taskImageInput.obj: ../src/app/tasks/taskImageInput.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/driver" --include_path="../include" --include_path="C:/Users/tysh0/git/store/Cloud_upp" --include_path="C:/ti/ndk_2_22_03_20/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_03_20/packages/ti/ndk/inc/tools" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/app/tasks/taskImageInput.pp" --obj_directory="src/app/tasks" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/app/tasks/taskImageProcess.obj: ../src/app/tasks/taskImageProcess.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/driver" --include_path="../include" --include_path="C:/Users/tysh0/git/store/Cloud_upp" --include_path="C:/ti/ndk_2_22_03_20/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_03_20/packages/ti/ndk/inc/tools" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/app/tasks/taskImageProcess.pp" --obj_directory="src/app/tasks" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/app/tasks/taskUartMaster.obj: ../src/app/tasks/taskUartMaster.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/driver" --include_path="../include" --include_path="C:/Users/tysh0/git/store/Cloud_upp" --include_path="C:/ti/ndk_2_22_03_20/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_03_20/packages/ti/ndk/inc/tools" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/app/tasks/taskUartMaster.pp" --obj_directory="src/app/tasks" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


