#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_34_02_18/packages;C:/ti/ccsv5/ccs_base;C:/ti/edma3_lld_02_11_04_01/packages;C:/Users/tysh0/WORKSP~1/MOISTU~1.110/packages;C:/ti/ipc_1_25_00_04/packages;C:/ti/ndk_2_22_00_06/packages;C:/ti/nsp_1_10_01_06/packages;C:/ti/imglib_c64Px_3_1_1_0/packages;C:/ti/mathlib_c674x_3_1_2_1/packages;C:/ti/biospsp_03_01_01_00/drivers;C:/ti/framework_components_3_30_00_06/packages;C:/ti/framework_components_3_30_00_06/examples;C:/ti/framework_components_3_30_00_06/fctools/packages
override XDCROOT = C:/ti/xdctools_3_24_05_48
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_34_02_18/packages;C:/ti/ccsv5/ccs_base;C:/ti/edma3_lld_02_11_04_01/packages;C:/Users/tysh0/WORKSP~1/MOISTU~1.110/packages;C:/ti/ipc_1_25_00_04/packages;C:/ti/ndk_2_22_00_06/packages;C:/ti/nsp_1_10_01_06/packages;C:/ti/imglib_c64Px_3_1_1_0/packages;C:/ti/mathlib_c674x_3_1_2_1/packages;C:/ti/biospsp_03_01_01_00/drivers;C:/ti/framework_components_3_30_00_06/packages;C:/ti/framework_components_3_30_00_06/examples;C:/ti/framework_components_3_30_00_06/fctools/packages;C:/ti/xdctools_3_24_05_48/packages;..
HOSTOS = Windows
endif
