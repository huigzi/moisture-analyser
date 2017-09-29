
MEMORY
{
    SN_PAR (RW) : org = 0xc0000000, len = 0x180000
    DDR2_SN_PAR4 (RW) : org = 0xc0180000, len = 0x80000
    App_Prog_START (RWX) : org = 0xc3000000, len = 0x400
    DDR_EXT (RW) : org = 0xc4000000, len = 0x4000000
}


SECTIONS
{
	 .SN_Par4	  > 	   DDR2_SN_PAR4
	.Image_Data	  >        DDR2_RAM
	.TImage_Data  >		   DDR_EXT

	my_boot_sect  >        App_Prog_START

}
