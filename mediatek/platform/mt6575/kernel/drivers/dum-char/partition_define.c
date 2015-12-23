#include <linux/module.h>
#include "partition_define.h"
struct excel_info PartInfo[PART_NUM]={
			{"preloader",262144,0x0, NAND},
			{"dsp_bl",786432,0x40000, NAND},
			{"nvram",3145728,0x100000, NAND},
			{"seccfg",131072,0x400000, NAND},
			{"uboot",393216,0x420000, NAND},
			{"bootimg",5242880,0x480000, NAND},
			{"recovery",5242880,0x980000, NAND},
			{"sec_ro",1179648,0xe80000, NAND},
			{"misc",393216,0xfa0000, NAND},
			{"logo",3145728,0x1000000, NAND},
			{"expdb",655360,0x1300000, NAND},
			{"android",262144000,0x13a0000, NAND},
			{"cache",62914560,0x10da0000, NAND},
			{"usrdata",0,0x149a0000, NAND},
			{"bmtpool",10485760,0xFFFF0050, NAND},
 };
EXPORT_SYMBOL(PartInfo);
