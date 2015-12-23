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

#include "lcm_drv.h"

#ifndef BUILD_UBOOT
#include <linux/kernel.h>       ///for printk
#endif

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (320)
#define FRAME_HEIGHT (480)

#define LCM_ID       (0x9486)

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


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

static __inline unsigned int read_data_cmd(void)
{
    return 0xFF&lcm_util.read_data();
}

static __inline void set_lcm_register(unsigned int regIndex,
		unsigned int regData)
{
	send_ctrl_cmd(regIndex);
	send_data_cmd(regData);
}

static void init_lcm_registers(void)
{

	send_ctrl_cmd(0xF1); 
	send_data_cmd(0x36);
	send_data_cmd(0x04);  
	send_data_cmd(0x00);
	send_data_cmd(0x3C);
	send_data_cmd(0x0F);  
	send_data_cmd(0x8F);
/*
	send_ctrl_cmd(0xF2); 
	send_data_cmd(0x18);
	send_data_cmd(0xA3);  
	send_data_cmd(0x12);
	send_data_cmd(0x02);
	send_data_cmd(0xB2);  
	send_data_cmd(0x12);
	send_data_cmd(0xFF);
	send_data_cmd(0x10);  
	send_data_cmd(0x00);

	send_ctrl_cmd(0xF4); 
	send_data_cmd(0x00);
	send_data_cmd(0x00);  
	send_data_cmd(0x08);
	send_data_cmd(0x91);
	send_data_cmd(0x04);  
*/
	send_ctrl_cmd(0xF8); 
	send_data_cmd(0x21);
	send_data_cmd(0x04);  



	send_ctrl_cmd(0xF9); 
	send_data_cmd(0x00);
	send_data_cmd(0x08);  

	send_ctrl_cmd(0xC0); 
	send_data_cmd(0x0D);
	send_data_cmd(0x0D);  


	send_ctrl_cmd(0xC1); 
	send_data_cmd(0x42);

/*
	send_ctrl_cmd(0XC2); 
	send_data_cmd(0x00);
*/

	send_ctrl_cmd(0xC5); 
	send_data_cmd(0x00);
	send_data_cmd(0x4A);  


	send_ctrl_cmd(0xB1); 
	send_data_cmd(0x80); //0xB0
	send_data_cmd(0x11);  


	send_ctrl_cmd(0xB4); 
	send_data_cmd(0x02);


	send_ctrl_cmd(0x36); 
	send_data_cmd(0x08);

	send_ctrl_cmd(0x3A); 
	send_data_cmd(0x66); 

	send_ctrl_cmd(0xB7); 
	send_data_cmd(0xC6);


	send_ctrl_cmd(0xB6); 
	send_data_cmd(0x02);
	send_data_cmd(0x22);
	send_data_cmd(0x3B);
	
	
	send_ctrl_cmd(0xE0); 
	send_data_cmd(0x0F);
	send_data_cmd(0x17);  
	send_data_cmd(0x15);
	send_data_cmd(0x0B);
	send_data_cmd(0x10);  
	send_data_cmd(0x08);
	send_data_cmd(0x4A);
	send_data_cmd(0x75);  
	send_data_cmd(0x3E);
	send_data_cmd(0x07);
	send_data_cmd(0x13);  
	send_data_cmd(0x06);
	send_data_cmd(0x1E);
	send_data_cmd(0x03);  
	send_data_cmd(0x00);


	send_ctrl_cmd(0xE1); 
	send_data_cmd(0x0F);
	send_data_cmd(0x32);  
	send_data_cmd(0x29);
	send_data_cmd(0x07);
	send_data_cmd(0x09);  
	send_data_cmd(0x03);
	send_data_cmd(0x44);
	send_data_cmd(0x54);  
	send_data_cmd(0x34);
	send_data_cmd(0x04);
	send_data_cmd(0x10);  
	send_data_cmd(0x03);
	send_data_cmd(0x21);
	send_data_cmd(0x21);  
	send_data_cmd(0x00);

	send_ctrl_cmd(0x11); 
	MDELAY(120);
	send_ctrl_cmd(0x29);    
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


static void lcm_init(void)
{
    SET_RESET_PIN(1);
    MDELAY(1);
    SET_RESET_PIN(0);
    MDELAY(10);
    SET_RESET_PIN(1);
    MDELAY(120);
//    config_gpio();
    init_lcm_registers();
}


static void lcm_suspend(void)
{
    send_ctrl_cmd(0x28);
    MDELAY(10);
    send_ctrl_cmd(0x10);
    MDELAY(120);
}


static void lcm_resume(void)
{
    send_ctrl_cmd(0x11);
    MDELAY(120);
	send_ctrl_cmd(0x29);
}

static void lcm_update(unsigned int x, unsigned int y,
		unsigned int width, unsigned int height)
{
	unsigned short x0, y0, x1, y1;
	unsigned short h_X_start,l_X_start,h_X_end,l_X_end,h_Y_start,l_Y_start,h_Y_end,l_Y_end;

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


/*
void lcm_setbacklight(unsigned int level)
{
	if(level > 255) level = 255;
	send_ctrl_cmd(0x51);
	send_data_cmd(level);	
}
*/
static unsigned int lcm_compare_id(void)
{
	char id_high=0;
	char id_low=0;
	int id=0;

	SET_RESET_PIN(1);
	MDELAY(1);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(120);

	send_ctrl_cmd(0xD3);
	read_data_cmd();
	read_data_cmd();
	id_high = read_data_cmd(); //0x94
	id_low = read_data_cmd(); //0x86

	id = (id_high<<8)|id_low;  //ox9486

#if defined(BUILD_UBOOT)
	printf("%s ili9486  id = 0x%08x \n", __func__, id);
#else
	printk("%s ili9486 id = 0x%08x \n", __func__, id);
#endif
    	return (LCM_ID == id)?1:0;
 }

LCM_DRIVER ili9486_hvga_lcm_drv = 
{
    .name			= "ili9486_hvga",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.update         = lcm_update,

	.compare_id     = lcm_compare_id,
};
