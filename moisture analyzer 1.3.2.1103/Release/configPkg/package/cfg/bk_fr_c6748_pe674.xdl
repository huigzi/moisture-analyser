/*
 * Do not modify this file; it is automatically generated from the template
 * linkcmd.xdt in the ti.targets.elf package and will be overwritten.
 */

/*
 * put '"'s around paths because, without this, the linker
 * considers '-' as minus operator, not a file name character.
 */


-l"C:\Users\su\workspace\moisture analyzer 1.3.2.1103\Release\configPkg\package\cfg\bk_fr_c6748_pe674.oe674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\hal\timer_bios\lib\hal_timer_bios.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\os\lib\os.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\hal\userled_stub\lib\hal_userled_stub.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\hal\eth_stub\lib\hal_eth_stub.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\tools\cgi\lib\cgi.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\tools\hdlc\lib\hdlc.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\tools\console\lib\console_min.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\netctrl\lib\netctrl.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\nettools\lib\nettool.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\hal\ser_stub\lib\hal_ser_stub.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\tools\servers\lib\servers_min.ae674"
-l"C:\ti\ndk_2_22_00_06\packages\ti\ndk\stack\lib\stk6_ppp_pppoe.ae674"
-l"C:\ti\ipc_1_25_00_04\packages\ti\sdo\utils\lib\utils\instrumented\utils.ae674"
-l"C:\ti\bios_6_34_02_18\packages\ti\sysbios\lib\sysbios\instrumented\sysbios.ae674"
-l"C:\ti\xdctools_3_24_05_48\packages\ti\targets\rts6000\lib\ti.targets.rts6000.ae674"
-l"C:\ti\xdctools_3_24_05_48\packages\ti\targets\rts6000\lib\boot.ae674"

--retain="*(xdc.meta)"


--args 0x0
-heap  0x0
-stack 0x1000

MEMORY
{
    IROM (RX) : org = 0x11700000, len = 0x100000
    IRAM (RWX) : org = 0x11800000, len = 0x20000
    L3_CBA_RAM (RWX) : org = 0x80000000, len = 0x20000
    DDR2_RAM (RWX) : org = 0xc0200000, len = 0x2d00000
    DDR (RWX) : org = 0xc3000400, len = 0xff000
}

/*
 * Linker command file contributions from all loaded packages:
 */

/* Content from xdc.services.global (null): */

/* Content from xdc (null): */

/* Content from xdc.corevers (null): */

/* Content from xdc.shelf (null): */

/* Content from xdc.services.spec (null): */

/* Content from xdc.services.intern.xsr (null): */

/* Content from xdc.services.intern.gen (null): */

/* Content from xdc.services.intern.cmd (null): */

/* Content from xdc.bld (null): */

/* Content from ti.targets (null): */

/* Content from ti.targets.elf (null): */

/* Content from xdc.rov (null): */

/* Content from xdc.runtime (null): */

/* Content from ti.targets.rts6000 (null): */

/* Content from ti.sysbios.interfaces (null): */

/* Content from ti.sysbios.family (null): */

/* Content from ti.sysbios (null): */

/* Content from xdc.services.getset (null): */

/* Content from ti.sysbios.hal (null): */

/* Content from ti.sysbios.knl (null): */

/* Content from ti.sysbios.family.c64p (null): */

/* Content from xdc.runtime.knl (null): */

/* Content from ti.sysbios.io (null): */

/* Content from ti.sysbios.gates (null): */

/* Content from ti.sdo.utils (null): */

/* Content from ti.sysbios.heaps (null): */

/* Content from ti.ndk.rov (null): */

/* Content from ti.ndk.config (null): */

/* Content from ti.sysbios.xdcruntime (null): */

/* Content from ti.sysbios.timers.timer64 (null): */

/* Content from ti.sysbios.family.c64p.primus (null): */

/* Content from ti.sysbios.family.c62 (null): */

/* Content from ti.sysbios.utils (null): */

/* Content from ti.catalog.c6000 (null): */

/* Content from ti.catalog (null): */

/* Content from ti.catalog.peripherals.hdvicp2 (null): */

/* Content from xdc.platform (null): */

/* Content from xdc.cfg (null): */

/* Content from ti.platforms.generic (null): */

/* Content from fr_Board (null): */

/* Content from configPkg (null): */

/* Content from ti.sdo.ipc.interfaces (null): */

/* Content from ti.sysbios.syncs (null): */

/* Content from ti.sdo.ipc.family (null): */

/* Content from ti.sdo.ipc (ti/sdo/ipc/linkcmd.xdt): */

SECTIONS
{
}


/* Content from ti.sdo.io (null): */


/*
 * symbolic aliases for static instance objects
 */
xdc_runtime_Startup__EXECFXN__C = 1;
xdc_runtime_Startup__RESETFXN__C = 1;
TSK_idle = ti_sysbios_knl_Task_Object__table__V + 456;

SECTIONS
{
    .text: load >> DDR2_RAM
    .ti.decompress: load > DDR2_RAM
    .stack: load > L3_CBA_RAM
    GROUP: load > DDR2_RAM
    {
        .bss:
        .neardata:
        .rodata:
    }
    .cinit: load > DDR2_RAM
    .pinit: load >> DDR2_RAM
    .init_array: load > DDR2_RAM
    .const: load >> DDR2_RAM
    .data: load >> DDR2_RAM
    .fardata: load >> DDR2_RAM
    .switch: load >> DDR2_RAM
    .sysmem: load > DDR2_RAM
    .far: load >> DDR2_RAM
    .args: load > DDR2_RAM align = 0x4, fill = 0 {_argsize = 0x0; }
    .cio: load >> DDR2_RAM
    .ti.handler_table: load > DDR2_RAM
    .vecs: load >> DDR2_RAM
    xdc.meta: load >> DDR2_RAM, type = COPY

}
