/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S 
 SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of MediaTek Inc. (C) 2008
 *
 *  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 *  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
 *  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 *  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 *  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 *  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
 *  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
 *  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
 *  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 *  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 *  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
 *  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
 *  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
 *  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
 *  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
 *  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
 *
 *****************************************************************************/

#include <linux/string.h>
#define LCM_DEBUG 1
#ifdef LCM_DEBUG
#if defined BUILD_UBOOT
    #include <common.h>
#if defined(MT6575)
    #include <asm/arch/mt6575_gpio.h>
#elif defined(CONFIG_ARCH_MT6573)
    #include <asm/arch/mt6573_gpio.h>
#endif
    #include "cust_gpio_usage.h"
#else
    #include <linux/kernel.h>
#if defined(MT6575)
    #include <mach/mt6575_gpio.h>
#elif defined(CONFIG_ARCH_MT6573)
    #include <mach/mt6573_gpio.h>
#endif
    #include <cust_gpio_usage.h>
   // #include <linux/delay.h>	
#endif
#endif

#include "lcm_drv.h"


// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (320)
#define FRAME_HEIGHT (480)

#define LCM_ID1 0x90
#define CHIP_ID_CMD 0xD0

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))
#ifdef TINNO_ANDROID_S8050
extern int flush_flag;
extern int ili9431_18bits;
#endif


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

static __inline void send_ctrl_cmd(unsigned int cmd)
{
	lcm_util.send_cmd(cmd);
}

static __inline void send_data_cmd(unsigned int data)
{
	lcm_util.send_data(data);
}

static __inline unsigned int read_data_cmd()
{
    return lcm_util.read_data();
}

static __inline void set_lcm_register(unsigned int regIndex,
		unsigned int regData)
{
	send_ctrl_cmd(regIndex);
	send_data_cmd(regData);
}

static void init_lcm_registers(void)
{
#if defined BUILD_UBOOT
printf("hx8357c init_lcm_registers\n");
#else
printk("hx8357c init_lcm_registers 0000\n");
#endif
	send_ctrl_cmd(0xB9);
	send_data_cmd(0xFF);
	send_data_cmd(0x83);
	send_data_cmd(0x57);
	MDELAY(5);

	send_ctrl_cmd(0xCC);
	send_data_cmd(0x09);

	//Set TE register
	send_ctrl_cmd(0x35);

;//	send_ctrl_cmd(0X0044);  // Set TE signal delay scanline
;//	send_data_cmd(0X0000);  // Set as 0-th scanline
;//	send_data_cmd(0X0000);

	send_ctrl_cmd(0x3A);
	send_data_cmd(0x06);  //06=18bit 262k; 05=16bit

	send_ctrl_cmd(0xB6); // VOMDX
	send_data_cmd(0x4B);
	send_ctrl_cmd(0xB1);
	send_data_cmd(0x00);
	send_data_cmd(0x14);
	send_data_cmd(0x1C);
	send_data_cmd(0x1C);
	send_data_cmd(0x83);
	send_ctrl_cmd(0xB4);
	send_data_cmd(0x02);
	send_data_cmd(0x40);
	send_data_cmd(0x00);
	send_data_cmd(0x2A);
	send_data_cmd(0x2A);
	send_data_cmd(0x0D);
	send_data_cmd(0x78);

	send_ctrl_cmd(0xC0);
	send_data_cmd(0x50);
	send_data_cmd(0x50);
	send_data_cmd(0x01);
	send_data_cmd(0x3C);
	send_data_cmd(0xC8);
	send_data_cmd(0x08);

	send_ctrl_cmd(0xE0);
	send_data_cmd(0x10);
	send_data_cmd(0x24);
	send_data_cmd(0x24);
	send_data_cmd(0x2B);
	send_data_cmd(0x32);
	send_data_cmd(0x40);
	send_data_cmd(0x4B);
	send_data_cmd(0x55);
	send_data_cmd(0x46);
	send_data_cmd(0x40);
	send_data_cmd(0x3B);
	send_data_cmd(0x33);
	send_data_cmd(0x2F);
	send_data_cmd(0x29);
	send_data_cmd(0x26);
	send_data_cmd(0x1E);
	send_data_cmd(0x10);
	send_data_cmd(0x24);
	send_data_cmd(0x24);
	send_data_cmd(0x2B);
	send_data_cmd(0x32);
	send_data_cmd(0x40);
	send_data_cmd(0x4B);
	send_data_cmd(0x55);
	send_data_cmd(0x46);
	send_data_cmd(0x40);
	send_data_cmd(0x3B);
	send_data_cmd(0x33);
	send_data_cmd(0x2F);
	send_data_cmd(0x29);
	send_data_cmd(0x26);
	send_data_cmd(0x1E);
	send_data_cmd(0x01);
	send_data_cmd(0x01);
	
	send_ctrl_cmd(0x11);
	MDELAY(150);

;//	send_ctrl_cmd(0x45);
;//	send_data_cmd(0x01);
;//	send_data_cmd(0xDF);

	send_ctrl_cmd(0xB0);
	send_data_cmd(0x8A); //68
	
        send_ctrl_cmd(0xB1);
	send_data_cmd(0x00);
	send_data_cmd(0x11);
	send_data_cmd(0x1C);
	send_data_cmd(0x1C);
	send_data_cmd(0x83);
	send_data_cmd(0xAA); 

	send_ctrl_cmd(0x29);
	MDELAY(25);

        
	send_ctrl_cmd(0x2C);
	
	send_ctrl_cmd(0x2A);
	send_data_cmd(0x00);
	send_data_cmd(0x00);
	send_data_cmd(0x01); 
	send_data_cmd(0x3F); 
	
	send_ctrl_cmd(0x2B);
	send_data_cmd(0x00);
	send_data_cmd(0x00);
	send_data_cmd(0x01); 
	send_data_cmd(0xDF);

}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
	memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
	memset(params, 0, sizeof(LCM_PARAMS));

	params->type   = LCM_TYPE_DBI;
	params->ctrl   = LCM_CTRL_PARALLEL_DBI;
	params->width  = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;
	params->io_select_mode = 3;	
	
	params->dbi.port                    = 0;
	params->dbi.clock_freq              = LCM_DBI_CLOCK_FREQ_104M;
	params->dbi.data_width              = LCM_DBI_DATA_WIDTH_18BITS;
	params->dbi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dbi.data_format.trans_seq   = LCM_DBI_TRANS_SEQ_MSB_FIRST;
	params->dbi.data_format.padding     = LCM_DBI_PADDING_ON_MSB;
	params->dbi.data_format.format      = LCM_DBI_FORMAT_RGB666;
	params->dbi.data_format.width       = LCM_DBI_DATA_WIDTH_18BITS;
	params->dbi.cpu_write_bits          = LCM_DBI_CPU_WRITE_32_BITS;
	params->dbi.io_driving_current      = LCM_DRIVING_CURRENT_8MA;

	params->dbi.parallel.write_setup    = 2;
	params->dbi.parallel.write_hold     = 2;
	params->dbi.parallel.write_wait     = 6;
	params->dbi.parallel.read_setup     = 3;
	params->dbi.parallel.read_latency   = 40;
	params->dbi.parallel.wait_period    = 0;

	// enable tearing-free
	params->dbi.te_mode                 = LCM_DBI_TE_MODE_VSYNC_ONLY;
	params->dbi.te_edge_polarity        = LCM_POLARITY_FALLING;
}

static void lcm_update(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

static void lcm_reset(void)
{
	SET_RESET_PIN(1);	//add test tcp
	MDELAY(10);	//add test tcp
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(150);
}

static void lcm_init(void)
{
	//lcm_reset();//move to lcm_compare_id()
	init_lcm_registers();

	lcm_update(0, 0, FRAME_WIDTH, FRAME_HEIGHT);
	int loop=0;

   	while(loop<FRAME_WIDTH*FRAME_HEIGHT)
	{
		send_data_cmd(0x00);
		loop++;
	}
}

static void lcm_suspend(void)
{
	send_ctrl_cmd(0x28);
	send_ctrl_cmd(0x10);
	MDELAY(120);
#ifdef TINNO_ANDROID_S8050
	flush_flag = 0;
#endif
}

static void lcm_resume(void)
{
#if defined BUILD_UBOOT	
	printf("hx8357c lcm_resume\n");
#else
	printk("hx8357c lcm_resume\n");
#endif	
	send_ctrl_cmd(0x11);
	MDELAY(120);
	send_ctrl_cmd(0x29);
	MDELAY(10);
}

static void lcm_update(unsigned int x, unsigned int y,
		unsigned int width, unsigned int height)
{
	unsigned short x0, y0, x1, y1;
	unsigned short h_X_start,l_X_start,h_X_end,l_X_end,h_Y_start,l_Y_start,h_Y_end,l_Y_end;
#ifdef TINNO_ANDROID_S8050
	ili9431_18bits = 1;
	flush_flag = 1;
#endif

	x0 = (unsigned short)x;
	y0 = (unsigned short)y;
	x1 = (unsigned short)x+width-1;
	y1 = (unsigned short)y+height-1;
	
	h_X_start=((x0&0xFF00)>>8);
	l_X_start=(x0&0x00FF);
	h_X_end=((x1&0xFF00)>>8);
	l_X_end=(x1&0x00FF);

	h_Y_start=((y0&0xFF00)>>8);
	l_Y_start=(y0&0x00FF);
	h_Y_end=((y1&0xFF00)>>8);
	l_Y_end=(y1&0x00FF);

	send_ctrl_cmd(0x2A);
	send_data_cmd(h_X_start); 
	send_data_cmd(l_X_start); 
	send_data_cmd(h_X_end); 
	send_data_cmd(l_X_end); 

	send_ctrl_cmd(0x2B);
	send_data_cmd(h_Y_start); 
	send_data_cmd(l_Y_start); 
	send_data_cmd(h_Y_end); 
	send_data_cmd(l_Y_end); 
	
	send_ctrl_cmd(0x29); 

	send_ctrl_cmd(0x2C);
}

#if defined BUILD_UBOOT	
#include "cust_adc.h"
#define LCM_MAX_VOLTAGE 1600 
#define LCM_MIN_VOLTAGE 1200 

extern int IMM_GetOneChannelValue_Ext(int dwChannel, int data[4], int* rawdata);

static unsigned int lcm_adc_read_chip_id()
{
	int data[4] = {0, 0, 0, 0};
	int tmp = 0, rc = 0, iVoltage = 0;

	rc = IMM_GetOneChannelValue_Ext(AUXADC_LCD_ID_CHANNEL, data, &tmp);

	if(rc < 0) {
		printf("hx8357 read LCD_ID vol error--Liu\n");
		return 0;
	}
	else {
		iVoltage = (data[0]*1000) + (data[1]*10) + (data[2]);
		printf("hx8357 read LCD_ID success, data[0]=%d, data[1]=%d, data[2]=%d, data[3]=%d, iVoltage=%d\n", 
			data[0], data[1], data[2], data[3], iVoltage);
		if(	LCM_MIN_VOLTAGE < iVoltage &&
			iVoltage < LCM_MAX_VOLTAGE)
			return 1;
		else
			return 0;
	}
	return ;
}
#endif	

#if defined BUILD_UBOOT
//#include <asm/arch/mtk_wdt.h>
#include <asm/arch/mt6575_pmic6329.h>
extern void mtk_wdt_hw_reset_lcdissue(void);
extern void mtk_wdt_sw_reset(void);
#endif

static unsigned int lcm_compare_id()
{
	int para0 = 0, para1 = 0;
#if defined BUILD_UBOOT
printf("hx8357c lcm_compare_id\n");
#else
printk("hx8357c lcm_compare_id\n");
#endif
	lcm_reset();//must be ahead of this function.

#if defined BUILD_UBOOT
	if(lcm_adc_read_chip_id())
		//return 1;		//mask by tcp
#else
	if(1)	//for kernel
#endif
	{
		send_ctrl_cmd(0xB9);
		send_data_cmd(0xFF);   
		send_data_cmd(0x83);   
		send_data_cmd(0x57); 
	
		send_ctrl_cmd(0xC2);  // delay
		send_data_cmd(0x30); 
	
		send_ctrl_cmd(CHIP_ID_CMD);
		para0 = read_data_cmd();
		para1 = read_data_cmd();

#if defined BUILD_UBOOT	
		printf("hx8357c LCD_test read id0 = %x id1 = %x,count_boot=%d\n",para0, para1);
		//add tcp
		para1 = para1 & 0xFF;
		if (para1 != LCM_ID1)
		{
			printf("hx8357c lcm_compare_id error\n");
			//Tinno:CJ
			pmic_config_interface((U8)( BANK0_LDO_VIO28 + LDO_CON1_OFFSET), 
		                            (U8)(0),
		                            (U8)(
		                            BANK_0_LDO_EN_MASK),
		                            (U8)(
		                            BANK_0_LDO_EN_SHIFT)
		                            );
			MDELAY(5000);
			//Tinno:CJ
			pmic_config_interface((U8)( BANK0_LDO_VIO28 + LDO_CON1_OFFSET), 
		                            (U8)(1),
		                            (U8)(
		                            BANK_0_LDO_EN_MASK),
		                            (U8)(
		                            BANK_0_LDO_EN_SHIFT)
		                            );
			mtk_wdt_sw_reset();
			//mtk_wdt_hw_reset_lcdissue();
		}
		//mtk_wdt_hw_reset_lcdissue();
		//add end
#else
		printk("hx8357c LCD read id0 = %x id1 = %x\n",para0, para1);
#endif

		para1 = para1 & 0xFF;
		if (para1 == LCM_ID1)
		{
			return 1;
		}
	}

	return 0;

}
LCM_DRIVER hx8357c_lcm_drv = 
{
    .name			= "hx8357c",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.update         = lcm_update,
    .compare_id     = lcm_compare_id,
};
