/*!
 * File generated by platform wizard. DO NOT MODIFY
 *
 */

metaonly module Platform inherits xdc.platform.IPlatform {

    config ti.platforms.generic.Platform.Instance CPU =
        ti.platforms.generic.Platform.create("CPU", {
            clockRate:      432,                                       
            catalogName:    "ti.catalog.c6000",
            deviceName:     "TMS320C6748",
            externalMemoryMap: 
           [          
                ["DDR2_RAM", 
                     {
                        name: "DDR2_RAM",
                        base: 0xC0200000,                    
                        len: 0x02D00000,                    
                        space: "code/data",
                        access: "RWX",
                     }
                ],
                ["DDR", 
                     {
                        name: "DDR",
                        base: 0xC3000400,                    
                        len: 0x000FF000,                    
                        space: "code/data",
                        access: "RWX",
                     }
                ],
           ],
          l2Mode:"128k",
          l1PMode:"32k",
          l1DMode:"32k",

    });
    
instance :
    
    override config string codeMemory  = "DDR2_RAM";   
    override config string dataMemory  = "DDR2_RAM";                                
    override config string stackMemory = "L3_CBA_RAM";
    
}
