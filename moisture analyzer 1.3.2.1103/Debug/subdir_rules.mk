################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
configPkg/compiler.opt: ../bk_fr_c6748.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_24_05_48/xs" --xdcpath="C:/ti/bios_6_34_02_18/packages;C:/ti/ccsv5/ccs_base;C:/ti/edma3_lld_02_11_04_01/packages;C:/Users/tysh0/git/store/moisture analyzer 1.3.2.1103/packages;C:/ti/ipc_1_25_00_04/packages;C:/ti/ndk_2_22_00_06/packages;C:/ti/nsp_1_10_01_06/packages;C:/ti/imglib_c64Px_3_1_1_0/packages;C:/ti/mathlib_c674x_3_1_2_1/packages;C:/ti/biospsp_03_01_01_00/drivers;C:/ti/framework_components_3_30_00_06/packages;C:/ti/framework_components_3_30_00_06/examples;C:/ti/framework_components_3_30_00_06/fctools/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C674 -p fr_Board -r release -b "C:/Users/tysh0/git/store/moisture analyzer 1.3.2.1103/packages/fr_Board/config.bld" -c "C:/ti/ccsv5/tools/compiler/c6000_7.4.1" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: C:/Users/tysh0/git/store/moisture\ analyzer\ 1.3.2.1103/packages/fr_Board/config.bld
configPkg/linker.cmd: configPkg/compiler.opt C:/Users/tysh0/git/store/moisture\ analyzer\ 1.3.2.1103/packages/fr_Board/config.bld
configPkg/: configPkg/compiler.opt C:/Users/tysh0/git/store/moisture\ analyzer\ 1.3.2.1103/packages/fr_Board/config.bld


