################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
configPkg/compiler.opt: ../gooao_fr_c6748.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_24_05_48/xs" --xdcpath="C:/ti/bios_6_34_02_18/packages;C:/ti/ndk_2_22_03_20/packages;C:/ti/nsp_1_10_02_09/packages;C:/ti/ccsv5/ccs_base;C:/ti/edma3_lld_02_11_04_01/packages;C:/Users/tysh0/git/store/Cloud_upp/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C674 -p fr_Board -r release -b "C:/Users/tysh0/git/store/Cloud_upp/packages/fr_Board/config.bld" -c "C:/ti/ccsv5/tools/compiler/c6000_7.4.1" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: C:/Users/tysh0/git/store/Cloud_upp/packages/fr_Board/config.bld
configPkg/linker.cmd: configPkg/compiler.opt C:/Users/tysh0/git/store/Cloud_upp/packages/fr_Board/config.bld
configPkg/: configPkg/compiler.opt C:/Users/tysh0/git/store/Cloud_upp/packages/fr_Board/config.bld


