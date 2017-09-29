################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
configPkg/compiler.opt: ../bk_fr_c6748.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_24_05_48/xs" --xdcpath="C:/ti/bios_6_34_02_18/packages;C:/ti/ndk_2_22_00_06/packages;C:/ti/nsp_1_10_01_06/packages;C:/ti/ccsv5/ccs_base;C:/ti/biospsp_03_01_01_00/drivers;C:/Users/tysh0/workspace/Hyeta_release/packages;C:/ti/edma3_lld_02_11_04_01/packages;C:/ti/ipc_1_25_00_04/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C674 -p fr_Board -r release -b "C:/Users/tysh0/workspace/Hyeta_release/packages/fr_Board/config.bld" -c "C:/ti/ccsv5/tools/compiler/c6000_7.4.1" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: C:/Users/tysh0/workspace/Hyeta_release/packages/fr_Board/config.bld
configPkg/linker.cmd: configPkg/compiler.opt C:/Users/tysh0/workspace/Hyeta_release/packages/fr_Board/config.bld
configPkg/: configPkg/compiler.opt C:/Users/tysh0/workspace/Hyeta_release/packages/fr_Board/config.bld


