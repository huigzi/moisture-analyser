#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_34_02_18/packages;C:/ti/ccsv5/ccs_base;C:/ti/edma3_lld_02_11_04_01/packages;C:/Users/tysh0/workspace/Hyeta_release/packages;C:/ti/ipc_1_25_00_04/packages;C:/ti/ndk_2_22_00_06/packages;C:/ti/nsp_1_10_01_06/packages
override XDCROOT = C:/ti/xdctools_3_24_05_48
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_34_02_18/packages;C:/ti/ccsv5/ccs_base;C:/ti/edma3_lld_02_11_04_01/packages;C:/Users/tysh0/workspace/Hyeta_release/packages;C:/ti/ipc_1_25_00_04/packages;C:/ti/ndk_2_22_00_06/packages;C:/ti/nsp_1_10_01_06/packages;C:/ti/xdctools_3_24_05_48/packages;..
HOSTOS = Windows
endif