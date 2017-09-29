################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/usbhost/USB_HCD.obj: ../src/usbhost/USB_HCD.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/cslr" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/usbhost/USB_HCD.pp" --obj_directory="src/usbhost" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/usbhost/USB_HOST_drv.obj: ../src/usbhost/USB_HOST_drv.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/cslr" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/usbhost/USB_HOST_drv.pp" --obj_directory="src/usbhost" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/usbhost/USB_IO.obj: ../src/usbhost/USB_IO.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/cslr" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/usbhost/USB_IO.pp" --obj_directory="src/usbhost" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/usbhost/USB_MSBulkOnly.obj: ../src/usbhost/USB_MSBulkOnly.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/cslr" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/usbhost/USB_MSBulkOnly.pp" --obj_directory="src/usbhost" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/usbhost/USB_MSHost.obj: ../src/usbhost/USB_MSHost.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/cslr" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/usbhost/USB_MSHost.pp" --obj_directory="src/usbhost" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/usbhost/USB_RBC.obj: ../src/usbhost/USB_RBC.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/cslr" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/usbhost/USB_RBC.pp" --obj_directory="src/usbhost" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/usbhost/USB_Transfer.obj: ../src/usbhost/USB_Transfer.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/cslr" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/usbhost/USB_Transfer.pp" --obj_directory="src/usbhost" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/usbhost/USB_USBD.obj: ../src/usbhost/USB_USBD.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.1/bin/cl6x" -mv6740 --abi=eabi -O2 --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.1/include" --include_path="../include/hw" --include_path="../include/usblib" --include_path="../include/ff9" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc" --include_path="C:/ti/ndk_2_22_00_06/packages/ti/ndk/inc/tools" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/cslr" --include_path="E:/work/faceR/project/baokang/ccs5/bk_fr_c6748/include/driver" --gcc --define=CHIP_C6748 --define=Spi_EDMA_ENABLE --define=c6748 --define=DMA_MODE --define=DMA_ENABLE --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/usbhost/USB_USBD.pp" --obj_directory="src/usbhost" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


