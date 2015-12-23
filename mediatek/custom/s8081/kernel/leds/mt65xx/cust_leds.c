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

#include <cust_leds.h>
#include <mach/mt6575_pwm.h>

#include <linux/kernel.h>
#include <mach/pmic_mt6329_hw_bank1.h> 
#include <mach/pmic_mt6329_sw_bank1.h> 
#include <mach/pmic_mt6329_hw.h>
#include <mach/pmic_mt6329_sw.h>
#include <mach/upmu_common_sw.h>
#include <mach/upmu_hw.h>

// LuckAs add
#define ACER_Z1
// LuckAs end

#if defined(ACER_Z1)//LK@for backlight control
#include <mach/mt6575_gpio.h>
#include "cust_gpio_usage.h"
#endif

extern int mtkfb_set_backlight_level(unsigned int level);
extern int mtkfb_set_backlight_pwm(int div);

#define ERROR_BL_LEVEL 0xFFFFFFFF

unsigned int brightness_mapping(unsigned int level)
{
    #if 1//LK@6575
        return level/4;//[0-255] map to [0-63]
    #else
	if(level>=30 && level<=255) { // user changable by using Setting->Display->Brightness
		return (level-14)/16;
	}
	else if(level>0 && level<30) { // used to fade out for 7 seconds before shut down backlight
		return 0;
	}
    #endif
	return ERROR_BL_LEVEL;//use brightness_mappto64

}


static struct cust_mt65xx_led cust_led_list[MT65XX_LED_TYPE_TOTAL] = {
#ifdef SIMCOM_I3200
	{"red",               MT65XX_LED_MODE_PWM, -1},
	{"green",             MT65XX_LED_MODE_PWM, -1},
	{"blue",              MT65XX_LED_MODE_PWM, -1},
	{"jogball-backlight", MT65XX_LED_MODE_NONE, -1},
	{"keyboard-backlight",MT65XX_LED_MODE_NONE, -1},
	{"button-backlight",  MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_BUTTON},//LK@6575
	//{"lcd-backlight",     MT65XX_LED_MODE_GPIO, GPIO_PWM_1_PIN},
	{"lcd-backlight",     MT65XX_LED_MODE_PWM, PWM2},
#elif defined(SIMCOM_I706M)
	{"red",               MT65XX_LED_MODE_NONE, -1},
	{"green",             MT65XX_LED_MODE_NONE, -1},
	{"blue",              MT65XX_LED_MODE_NONE, -1},
	{"jogball-backlight", MT65XX_LED_MODE_NONE, -1},
	{"keyboard-backlight",MT65XX_LED_MODE_NONE, -1},
	{"button-backlight",  MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_BUTTON},
	{"lcd-backlight",     MT65XX_LED_MODE_PWM, PWM2},
#elif defined(ACER_Z1)
	{"red",               MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_NLED_ISINK5},
	{"green",             MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_NLED_ISINK4},
// orig
//	{"red",               MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_NLED_PRECHR},
//	{"green",             MT65XX_LED_MODE_NONE, -1},
	{"blue",              MT65XX_LED_MODE_NONE, -1},
	{"jogball-backlight", MT65XX_LED_MODE_NONE, -1},
	{"keyboard-backlight",MT65XX_LED_MODE_NONE, -1},
	{"button-backlight",  MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_BUTTON},
// LuckAs change
	{"lcd-backlight",     MT65XX_LED_MODE_GPIO, GPIO_PWM_2_PIN},
// orig
//	{"lcd-backlight",     MT65XX_LED_MODE_GPIO, GPIO_PWM_1_PIN},
	
#else
	{"red",               MT65XX_LED_MODE_PWM, PWM3},//LK@I3000
	{"green",             MT65XX_LED_MODE_PWM, PWM2},//
	{"blue",              MT65XX_LED_MODE_PWM, PWM4},//
	{"jogball-backlight", MT65XX_LED_MODE_NONE, -1},
	{"keyboard-backlight",MT65XX_LED_MODE_NONE, -1},
	{"button-backlight",  MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_BUTTON},//LK@6575
	{"lcd-backlight",     MT65XX_LED_MODE_PWM, PWM1},//LK@I3000,MT65XX_LED_PMIC_LCD_BOOST change to PWM0(PWM1 in code)
	//{"lcd-backlight",     MT65XX_LED_MODE_GPIO, GPIO_PWM_1_PIN},
	//{"lcd-backlight",     MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_LCD_BOOST},
#endif
};

struct cust_mt65xx_led *get_cust_led_list(void)
{
	return cust_led_list;
}

