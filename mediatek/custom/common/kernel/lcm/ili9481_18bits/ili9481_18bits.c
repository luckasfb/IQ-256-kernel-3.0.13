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
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
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


#define LCM_ID1 0x02
#define LCM_ID2 0x04

#define LCM_ID3 0x94
#define LCM_ID4 0x81
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (320)
#define FRAME_HEIGHT (480)

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))

#ifdef TINNO_ANDROID_S8050
int flush_flag = 0;
int ili9431_18bits = 0;
#endif

static unsigned int lcm_compare_id();

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

static __inline unsigned int HIGH_BYTE(unsigned int val)
{
    return (val >> 8) & 0xFF;
}

static __inline unsigned int LOW_BYTE(unsigned int val)
{
    return (val & 0xFF);
}

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

//edit by Magnum declare lcm_update
static void lcm_update(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

static void init_lcm_registers(void)
{
	send_ctrl_cmd(0xC0);
	send_data_cmd(0x13);
	send_data_cmd(0x13);

	send_ctrl_cmd(0xC1);
	send_data_cmd(0x42);

	send_ctrl_cmd(0xC2);
	send_data_cmd(0x33);

	send_ctrl_cmd(0XC5);
	send_data_cmd(0x00);
	send_data_cmd(0x29);//36

	send_ctrl_cmd(0xB1);
	send_data_cmd(0xA0);//B0
	send_data_cmd(0x11);

	send_ctrl_cmd(0xB4);
	send_data_cmd(0x02);//0x02 point inversion, 0x00 column inversion

	send_ctrl_cmd(0XB7);
	send_data_cmd(0x86);
	/*
	send_ctrl_cmd(0xE0);
	send_data_cmd(0x0F);//0F VP0[4:0] grey63
	send_data_cmd(0x24);//1F VP1[5:0] grey62
	send_data_cmd(0x1F);//1D VP2[5:0]   grey61
	send_data_cmd(0x0C);//VP4[3:0]   grey59
	send_data_cmd(0x10);//VP6[4:0]   grey57
	send_data_cmd(0x09);//VP13[3:0]    grey50
	send_data_cmd(0x4c);//4C VP20[6:0]//43 grey43
	send_data_cmd(0x97);//A8 VP36[3:0];VP27[3:0] grey27 grey36
	send_data_cmd(0x3B);//3D VP43[6:0]//31grey20
	send_data_cmd(0x0C);//0B VP50[3:0]    grey13
	send_data_cmd(0x1a);//1A VP57[4:0] grey6
	send_data_cmd(0x09);//05 VP59[3:0] grey4
	send_data_cmd(0x0B);//09 VP61[5:0] grey2
	send_data_cmd(0x08);//05 VP62[5:0] grey1
	send_data_cmd(0x00);//00 VP63[4:0] grey0

	send_ctrl_cmd(0XE1);
	send_data_cmd(0x1F);//0FVN0[4:0]1F
	send_data_cmd(0x3a);//3A VN1[5:0]3F
	send_data_cmd(0x34);//36 VN2[5:0]3F
	send_data_cmd(0x06);//0A VN4[3:0]F
	send_data_cmd(0x1F);//05 VN6[4:0]1F
	send_data_cmd(0x03);//04 VN13[3:0]F
	send_data_cmd(0x44);//42 VN20[6:0]7F//4E
	send_data_cmd(0x86);//75 VN36[3:0]FF;VP27[3:0]
	send_data_cmd(0x33);//33 VN43[6:0]7F//3C
	send_data_cmd(0x06);//06 VN50[3:0]F
	send_data_cmd(0x0F);//0f VN57[4:0]1F
	send_data_cmd(0x03);//03 VN59[3:0]F
	send_data_cmd(0x20);//22 VN61[5:0]3F
	send_data_cmd(0x17);//20 VN62[5:0]3F
	send_data_cmd(0x00);//00 VN63[4:0]1F
	*/
	send_ctrl_cmd(0xE0);
	send_data_cmd(0x0F);//0F VP0[4:0] grey63
	send_data_cmd(0x24);//1F VP1[5:0] grey62
	send_data_cmd(0x1F);//1D VP2[5:0]   grey61
	send_data_cmd(0x0C);//VP4[3:0]   grey59
	send_data_cmd(0x10);//VP6[4:0]   grey57
	send_data_cmd(0x09);//VP13[3:0]    grey50
	send_data_cmd(0x4c);//4C VP20[6:0]//43 grey43
	send_data_cmd(0x97);//A8 VP36[3:0];VP27[3:0] grey27 grey36
	send_data_cmd(0x3B);//3D VP43[6:0]//31grey20
	send_data_cmd(0x0C);//0B VP50[3:0]    grey13
	send_data_cmd(0x1a);//1A VP57[4:0] grey6
	send_data_cmd(0x0A);//05 VP59[3:0] grey4
	send_data_cmd(0x12);//09 VP61[5:0] grey2
	send_data_cmd(0x0F);//05 VP62[5:0] grey1
	send_data_cmd(0x00);//00 VP63[4:0] grey0

	send_ctrl_cmd(0XE1);
	send_data_cmd(0x1F);//0FVN0[4:0]1F
	send_data_cmd(0x30);//3A VN1[5:0]3F
	send_data_cmd(0x2D);//36 VN2[5:0]3F
	send_data_cmd(0x05);//0A VN4[3:0]F
	send_data_cmd(0x1F);//05 VN6[4:0]1F
	send_data_cmd(0x03);//04 VN13[3:0]F
	send_data_cmd(0x44);//42 VN20[6:0]7F//4E
	send_data_cmd(0x86);//75 VN36[3:0]FF;VP27[3:0]
	send_data_cmd(0x33);//33 VN43[6:0]7F//3C
	send_data_cmd(0x06);//06 VN50[3:0]F
	send_data_cmd(0x0F);//0f VN57[4:0]1F
	send_data_cmd(0x03);//03 VN59[3:0]F
	send_data_cmd(0x20);//22 VN61[5:0]3F
	send_data_cmd(0x17);//20 VN62[5:0]3F
	send_data_cmd(0x00);//00 VN63[4:0]1F

	send_ctrl_cmd(0XF2);
	send_data_cmd(0x18);
	send_data_cmd(0xA3);
	send_data_cmd(0x12);
	send_data_cmd(0x02);
	send_data_cmd(0xB2);
	send_data_cmd(0x12);
	send_data_cmd(0xFF);
	send_data_cmd(0x10);
	send_data_cmd(0x00);

	send_ctrl_cmd(0XF1);       
	send_data_cmd(0x36); 
	send_data_cmd(0x44); 
	send_data_cmd(0x00); 
	send_data_cmd(0x3C); 
	send_data_cmd(0X0F); 
	send_data_cmd(0x8F); 

	send_ctrl_cmd(0XF8);
	send_data_cmd(0x21);
	send_data_cmd(0x04);

	send_ctrl_cmd(0x35);
	send_data_cmd(0x00);//LCM_DBI_TE_MODE_VSYNC_ONLY

	send_ctrl_cmd(0x44);
	send_data_cmd(0x00);
	send_data_cmd(0xFF);//Jieve Liu

	send_ctrl_cmd(0x36);
	send_data_cmd(0x48);

	send_ctrl_cmd(0x3A);
	send_data_cmd(0x66);

	send_ctrl_cmd(0xF9);  
	send_data_cmd(0x00);  
	send_data_cmd(0x08); 
	 
	send_ctrl_cmd(0x11);
	MDELAY(120);
	send_ctrl_cmd(0x29);
	send_ctrl_cmd(0x2C);
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
    params->dbi.data_format.padding     = LCM_DBI_PADDING_ON_LSB;
    params->dbi.data_format.format      = LCM_DBI_FORMAT_RGB666;
    params->dbi.data_format.width       = LCM_DBI_DATA_WIDTH_18BITS;
    params->dbi.cpu_write_bits          = LCM_DBI_CPU_WRITE_32_BITS;
    params->dbi.io_driving_current      = LCM_DRIVING_CURRENT_8MA;

	//fmark
    params->dbi.te_mode                 = LCM_DBI_TE_MODE_VSYNC_ONLY;
    params->dbi.te_edge_polarity        = LCM_POLARITY_FALLING;
	//fmark

    params->dbi.parallel.write_setup    = 3;   // RS TO WR LOW
    params->dbi.parallel.write_hold     = 3;   // WR TO CS HOLD
    params->dbi.parallel.write_wait     = 8;    // 
	params->dbi.parallel.read_setup     = 3;
	params->dbi.parallel.read_latency   = 32;
	params->dbi.parallel.wait_period    = 4;



//    params->dbi.te_mode			= LCM_DBI_TE_MODE_DISABLED;
    
}


static void lcm_init(void)
{
// Eajum modified DATE20120614, START
//#ifdef LCM_DEBUG
//#if defined BUILD_UBOOT
//   printf("ili9481 LCD DRIVER INIT \n");		//0x0
//#else
//    printk("ili9481 LCD DRIVER INIT!!!!!!!!!!!!!!!! \n");		//0x0
//#endif
//#endif
//    SET_RESET_PIN(0);
//    MDELAY(200);
//    SET_RESET_PIN(1);
//    MDELAY(400);
	//lcm_reset();//move to lcm_compare_id()
// Eajum modified DATE20120614, END

    init_lcm_registers();

   lcm_update(0, 0, FRAME_WIDTH, FRAME_HEIGHT);
   int loop=0;
   while(loop<320*480)
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
    send_ctrl_cmd(0x11);
    MDELAY(120);
    send_ctrl_cmd(0x29);
	MDELAY(10);
}

static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
    unsigned int x0 = x;
    unsigned int y0 = y;
    unsigned int x1 = x0 + width - 1;
    unsigned int y1 = y0 + height - 1;
#ifdef TINNO_ANDROID_S8050
	ili9431_18bits = 1;
	flush_flag = 1;
#endif
	send_ctrl_cmd(0x2A);
	send_data_cmd(HIGH_BYTE(x0));
	send_data_cmd(LOW_BYTE(x0));
	send_data_cmd(HIGH_BYTE(x1));
	send_data_cmd(LOW_BYTE(x1));

	send_ctrl_cmd(0x2B);
	send_data_cmd(HIGH_BYTE(y0));
	send_data_cmd(LOW_BYTE(y0));
	send_data_cmd(HIGH_BYTE(y1));
	send_data_cmd(LOW_BYTE(y1));

	// Write To GRAM
	send_ctrl_cmd(0x2C);
}



static unsigned int lcm_compare_id()
{
//Ivan modified
    int para1,para2,para3,para4,para5,para6;
#if 0
    send_ctrl_cmd(0xBF);
    para1 = read_data_cmd();	//Dummy
    para2 = read_data_cmd();
    para3 = read_data_cmd();
    para4 = read_data_cmd();
    para5 = read_data_cmd();
    para6 = read_data_cmd();
    send_ctrl_cmd(0xBF);
    para1 = read_data_cmd();	//Dummy
    para2 = read_data_cmd();
    para3 = read_data_cmd();
    para4 = read_data_cmd();
    para5 = read_data_cmd();
    para6 = read_data_cmd();
#else
    send_ctrl_cmd(0xD3);
    para1 = read_data_cmd();	//Dummy
    para2 = read_data_cmd();
    para3 = read_data_cmd();
    para4 = read_data_cmd();
    //para5 = read_data_cmd();
   // para6 = read_data_cmd();
#endif
#ifdef LCM_DEBUG
#if defined BUILD_UBOOT
    printf("il9481 LCD read id1 = %x \n",para1);		//0x00
    printf("il9481 LCD read id2 = %x \n",para2);		//0x02
    printf("il9481 LCD read id3 = %x \n",para3);		//0x04
    printf("il9481 LCD read id4 = %x \n",para4);		//0x94
    printf("il9481 LCD read id5 = %x \n",para5);		//0x81
    printf("il9481 LCD read id6 = %x \n",para6);		//0xff
#else
    printk("il9481 LCD read id1 = %x \n",para1);		//0x00
    printk("il9481 LCD read id2 = %x \n",para2);		//0x02
    printk("il9481 LCD read id3 = %x \n",para3);		//0x04
    printk("il9481 LCD read id4 = %x \n",para4);		//0x94
    printk("il9481 LCD read id5 = %x \n",para5);		//0x81
    printk("il9481 LCD read id6 = %x \n",para6);		//0xff
#endif
#endif


    para1 = para1 & 0xFF;
    para2 = para2 & 0xFF;
    para3 = para3 & 0xFF;
    para4 = para4 & 0xFF;
    para5 = para5 & 0xFF;
    para6 = para6 & 0xFF;
	
    if ( (para2 == 0x00) && (para3 == 0x94) && (para4 == 0x86)/* && (para5 == LCM_ID4)*/)
	return 1;
    else
	return 0;
}

// ---------------------------------------------------------------------------
//  Get LCM Driver Hooks
// ---------------------------------------------------------------------------
LCM_DRIVER ili9481_18bits_lcm_drv =
{
    .name           = "ili9481(18-bits)",
    .set_util_funcs = lcm_set_util_funcs,
    .get_params     = lcm_get_params,
    .init           = lcm_init,
    .suspend        = lcm_suspend,
    .resume         = lcm_resume,
    .update         = lcm_update,
    .compare_id     = lcm_compare_id,
};
