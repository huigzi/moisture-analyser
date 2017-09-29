/*
 *  ======== evminit.c ========
 *
 */
 
#include <xdc/std.h>

#include <ti/sysbios/family/c64p/Cache.h>

/*
 * ======== EVM_init ========
 */
void EVM_Init()
{
	Cache_Size cacheSize;
	
	cacheSize.l1pSize = Cache_L1Size_32K;
	cacheSize.l1dSize = Cache_L1Size_32K;
	cacheSize.l2Size = Cache_L2Size_256K;
	
	Cache_setSize(&cacheSize);
}

