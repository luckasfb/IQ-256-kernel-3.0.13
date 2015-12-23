/*
 * Generated by MTK Drv_CodeGen Version 04.08.0 for MT6575_NP. Copyright MediaTek Inc. (C) 2011.
 * Thu Oct 31 21:19:32 2013
 * Do Not Modify the File.
 */

#ifndef __CUST_GPIO_USAGE_H__
#define __CUST_GPIO_USAGE_H__


#define GPIO_GPS_PWREN_PIN         GPIO13
#define GPIO_GPS_PWREN_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_GPS_PWREN_PIN_M_EINT   GPIO_MODE_02
#define GPIO_GPS_PWREN_PIN_M_PWM   GPIO_MODE_03

#define GPIO_WIFI_EINT_PIN         GPIO15
#define GPIO_WIFI_EINT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_WIFI_EINT_PIN_M_EINT   GPIO_MODE_02
#define GPIO_WIFI_EINT_PIN_M_PWM   GPIO_MODE_03

#define GPIO_GPS_CLK_PIN         GPIO53
#define GPIO_GPS_CLK_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_GPS_CLK_PIN_M_CLK   GPIO_MODE_03
#define GPIO_GPS_CLK_PIN_M_I2S0_DAT   GPIO_MODE_01
#define GPIO_GPS_CLK_PIN_CLK     CLK_OUT4
#define GPIO_GPS_CLK_PIN_FREQ    CLK_SRC_F32K

#define GPIO_I2S0_WS_PIN         GPIO54
#define GPIO_I2S0_WS_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_I2S0_WS_PIN_M_CLK   GPIO_MODE_03
#define GPIO_I2S0_WS_PIN_M_I2S0_WS   GPIO_MODE_01
#define GPIO_I2S0_WS_PIN_CLK     CLK_OUT5
#define GPIO_I2S0_WS_PIN_FREQ    GPIO_CLKSRC_NONE

#define GPIO_BT_CLK_PIN         GPIO55
#define GPIO_BT_CLK_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_BT_CLK_PIN_M_CLK   GPIO_MODE_03
#define GPIO_BT_CLK_PIN_M_EINT   GPIO_MODE_02
#define GPIO_BT_CLK_PIN_M_I2S0_CK   GPIO_MODE_01
#define GPIO_BT_CLK_PIN_CLK     CLK_OUT3
#define GPIO_BT_CLK_PIN_FREQ    CLK_SRC_F32K

#define GPIO_BT_RESET_PIN         GPIO59
#define GPIO_BT_RESET_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_BT_RESET_PIN_M_EINT   GPIO_MODE_02
#define GPIO_BT_RESET_PIN_M_PWM   GPIO_MODE_03
#define GPIO_BT_RESET_PIN_M_DAIRSTB   GPIO_MODE_01

#define GPIO_ACCDET_EINT_PIN         GPIO60
#define GPIO_ACCDET_EINT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_ACCDET_EINT_PIN_M_EINT   GPIO_MODE_01
#define GPIO_ACCDET_EINT_PIN_M_PWM   GPIO_MODE_03

#define GPIO_PMIC_EINT_PIN         GPIO61
#define GPIO_PMIC_EINT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_PMIC_EINT_PIN_M_EINT   GPIO_MODE_01
#define GPIO_PMIC_EINT_PIN_M_PWM   GPIO_MODE_03

#define GPIO_PCM_DAIPCMOUT_PIN         GPIO62
#define GPIO_PCM_DAIPCMOUT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_PCM_DAIPCMOUT_PIN_M_EINT   GPIO_MODE_02
#define GPIO_PCM_DAIPCMOUT_PIN_M_PWM   GPIO_MODE_03
#define GPIO_PCM_DAIPCMOUT_PIN_M_DAIPCMOUT   GPIO_MODE_01

#define GPIO_PCM_DAICLK_PIN         GPIO63
#define GPIO_PCM_DAICLK_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_PCM_DAICLK_PIN_M_CLK   GPIO_MODE_01
#define GPIO_PCM_DAICLK_PIN_M_EINT   GPIO_MODE_02
#define GPIO_PCM_DAICLK_PIN_M_PWM   GPIO_MODE_03

#define GPIO_PCM_DAIPCMIN_PIN         GPIO64
#define GPIO_PCM_DAIPCMIN_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_PCM_DAIPCMIN_PIN_M_EINT   GPIO_MODE_02
#define GPIO_PCM_DAIPCMIN_PIN_M_PWM   GPIO_MODE_03
#define GPIO_PCM_DAIPCMIN_PIN_M_DAIPCMIN   GPIO_MODE_01

#define GPIO_PCM_DAISYNC_PIN         GPIO65
#define GPIO_PCM_DAISYNC_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_PCM_DAISYNC_PIN_M_EINT   GPIO_MODE_02
#define GPIO_PCM_DAISYNC_PIN_M_PWM   GPIO_MODE_03
#define GPIO_PCM_DAISYNC_PIN_M_BTSYNC   GPIO_MODE_01

#define GPIO_PWM_2_PIN         GPIO66
#define GPIO_PWM_2_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_PWM_2_PIN_M_EINT   GPIO_MODE_02
#define GPIO_PWM_2_PIN_M_PWM   GPIO_MODE_01

#define GPIO_GSE_2_EINT_PIN         GPIO69
#define GPIO_GSE_2_EINT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_GSE_2_EINT_PIN_M_CLK   GPIO_MODE_04
#define GPIO_GSE_2_EINT_PIN_M_EINT   GPIO_MODE_01
#define GPIO_GSE_2_EINT_PIN_M_PWM   GPIO_MODE_02
#define GPIO_GSE_2_EINT_PIN_CLK     CLK_OUT2
#define GPIO_GSE_2_EINT_PIN_FREQ    GPIO_CLKSRC_NONE

#define GPIO_UART_UTXD3_PIN         GPIO71
#define GPIO_UART_UTXD3_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_UTXD3_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_UTXD3_PIN_M_PWM   GPIO_MODE_04
#define GPIO_UART_UTXD3_PIN_M_UTXD   GPIO_MODE_01

#define GPIO_GSE_1_EINT_PIN         GPIO72
#define GPIO_GSE_1_EINT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_GSE_1_EINT_PIN_M_CLK   GPIO_MODE_04
#define GPIO_GSE_1_EINT_PIN_M_EINT   GPIO_MODE_01
#define GPIO_GSE_1_EINT_PIN_M_PWM   GPIO_MODE_02
#define GPIO_GSE_1_EINT_PIN_CLK     CLK_OUT1
#define GPIO_GSE_1_EINT_PIN_FREQ    GPIO_CLKSRC_NONE

#define GPIO_OTG_DRVVBUS_PIN         GPIO73
#define GPIO_OTG_DRVVBUS_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_OTG_DRVVBUS_PIN_M_CLK   GPIO_MODE_02
#define GPIO_OTG_DRVVBUS_PIN_M_EINT   GPIO_MODE_01
#define GPIO_OTG_DRVVBUS_PIN_M_USB_DRVVBUS   GPIO_MODE_05
#define GPIO_OTG_DRVVBUS_PIN_CLK     CLK_OUT0
#define GPIO_OTG_DRVVBUS_PIN_FREQ    GPIO_CLKSRC_NONE

#define GPIO_UART_UTXD2_PIN         GPIO74
#define GPIO_UART_UTXD2_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_UTXD2_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_UTXD2_PIN_M_PWM   GPIO_MODE_04
#define GPIO_UART_UTXD2_PIN_M_UTXD   GPIO_MODE_01

#define GPIO_BT_EINT_PIN         GPIO76
#define GPIO_BT_EINT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_BT_EINT_PIN_M_CLK   GPIO_MODE_04
#define GPIO_BT_EINT_PIN_M_EINT   GPIO_MODE_01
#define GPIO_BT_EINT_PIN_M_PWM   GPIO_MODE_02
#define GPIO_BT_EINT_PIN_CLK     CLK_OUT4
#define GPIO_BT_EINT_PIN_FREQ    GPIO_CLKSRC_NONE

#define GPIO_UART_URXD2_PIN         GPIO77
#define GPIO_UART_URXD2_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_URXD2_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_URXD2_PIN_M_PWM   GPIO_MODE_04
#define GPIO_UART_URXD2_PIN_M_URXD   GPIO_MODE_01

#define GPIO_MSE_EINT_PIN         GPIO78
#define GPIO_MSE_EINT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_MSE_EINT_PIN_M_EINT   GPIO_MODE_01
#define GPIO_MSE_EINT_PIN_M_PWM   GPIO_MODE_02

#define GPIO_UART_URXD3_PIN         GPIO79
#define GPIO_UART_URXD3_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_URXD3_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_URXD3_PIN_M_PWM   GPIO_MODE_04
#define GPIO_UART_URXD3_PIN_M_URXD   GPIO_MODE_01

#define GPIO_UART_UCTS2_PIN         GPIO80
#define GPIO_UART_UCTS2_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_UCTS2_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_UCTS2_PIN_M_PWM   GPIO_MODE_04
#define GPIO_UART_UCTS2_PIN_M_UCTS   GPIO_MODE_01

#define GPIO_ALS_EINT_PIN         GPIO81
#define GPIO_ALS_EINT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_ALS_EINT_PIN_M_CLK   GPIO_MODE_04
#define GPIO_ALS_EINT_PIN_M_EINT   GPIO_MODE_01
#define GPIO_ALS_EINT_PIN_M_PWM   GPIO_MODE_02
#define GPIO_ALS_EINT_PIN_CLK     CLK_OUT3
#define GPIO_ALS_EINT_PIN_FREQ    GPIO_CLKSRC_NONE

#define GPIO_UART_URTS2_PIN         GPIO82
#define GPIO_UART_URTS2_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_URTS2_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_URTS2_PIN_M_PWM   GPIO_MODE_04
#define GPIO_UART_URTS2_PIN_M_URTS   GPIO_MODE_01

#define GPIO_GPS_RST_PIN         GPIO83
#define GPIO_GPS_RST_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_GPS_RST_PIN_M_EINT   GPIO_MODE_02

#define GPIO_BT_WAKEUP_PIN         GPIO84
#define GPIO_BT_WAKEUP_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_BT_WAKEUP_PIN_M_EINT   GPIO_MODE_02

#define GPIO_WIFI_LDO_EN_PIN         GPIO85
#define GPIO_WIFI_LDO_EN_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_WIFI_LDO_EN_PIN_M_CLK   GPIO_MODE_03
#define GPIO_WIFI_LDO_EN_PIN_M_EINT   GPIO_MODE_02
#define GPIO_WIFI_LDO_EN_PIN_CLK     CLK_OUT5
#define GPIO_WIFI_LDO_EN_PIN_FREQ    GPIO_CLKSRC_NONE

#define GPIO_BT_POWREN_PIN         GPIO86
#define GPIO_BT_POWREN_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_BT_POWREN_PIN_M_CLK   GPIO_MODE_01
#define GPIO_BT_POWREN_PIN_M_EINT   GPIO_MODE_02

#define GPIO_I2C0_SCA_PIN         GPIO87
#define GPIO_I2C0_SCA_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_I2C0_SCA_PIN_M_CLK   GPIO_MODE_03
#define GPIO_I2C0_SCA_PIN_M_EINT   GPIO_MODE_02
#define GPIO_I2C0_SCA_PIN_M_SCL   GPIO_MODE_01
#define GPIO_I2C0_SCA_PIN_CLK     CLK_OUT4
#define GPIO_I2C0_SCA_PIN_FREQ    GPIO_CLKSRC_NONE

#define GPIO_I2C0_SDA_PIN         GPIO88
#define GPIO_I2C0_SDA_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_I2C0_SDA_PIN_M_CLK   GPIO_MODE_03
#define GPIO_I2C0_SDA_PIN_M_EINT   GPIO_MODE_02
#define GPIO_I2C0_SDA_PIN_M_SDA   GPIO_MODE_01
#define GPIO_I2C0_SDA_PIN_CLK     CLK_OUT3
#define GPIO_I2C0_SDA_PIN_FREQ    GPIO_CLKSRC_NONE

#define GPIO_KPD_KROW0_PIN         GPIO98
#define GPIO_KPD_KROW0_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_KPD_KROW0_PIN_M_CLK   GPIO_MODE_03
#define GPIO_KPD_KROW0_PIN_M_EINT   GPIO_MODE_02
#define GPIO_KPD_KROW0_PIN_M_KP_ROW   GPIO_MODE_01
#define GPIO_KPD_KROW0_PIN_CLK     CLK_OUT4
#define GPIO_KPD_KROW0_PIN_FREQ    GPIO_CLKSRC_NONE

#define GPIO_KPD_KCOL0_PIN         GPIO103
#define GPIO_KPD_KCOL0_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_KPD_KCOL0_PIN_M_EINT   GPIO_MODE_02
#define GPIO_KPD_KCOL0_PIN_M_PWM   GPIO_MODE_03
#define GPIO_KPD_KCOL0_PIN_M_KP_COL   GPIO_MODE_01

#define GPIO_KPD_KCOL1_PIN         GPIO108
#define GPIO_KPD_KCOL1_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_KPD_KCOL1_PIN_M_EINT   GPIO_MODE_02
#define GPIO_KPD_KCOL1_PIN_M_PWM   GPIO_MODE_03
#define GPIO_KPD_KCOL1_PIN_M_KP_COL   GPIO_MODE_01

#define GPIO_COMBO_PMU_EN_PIN         GPIO120
#define GPIO_COMBO_PMU_EN_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_COMBO_PMU_EN_PIN_M_EINT   GPIO_MODE_02

#define GPIO_COMBO_RST_PIN         GPIO121
#define GPIO_COMBO_RST_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_COMBO_RST_PIN_M_EINT   GPIO_MODE_02

#define GPIO_OTG_IDDIG_EINT_PIN         GPIO141
#define GPIO_OTG_IDDIG_EINT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_OTG_IDDIG_EINT_PIN_M_EINT   GPIO_MODE_02
#define GPIO_OTG_IDDIG_EINT_PIN_M_IDDIG   GPIO_MODE_01

#define GPIO_UART_UTXD1_PIN         GPIO157
#define GPIO_UART_UTXD1_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_UTXD1_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_UTXD1_PIN_M_UTXD   GPIO_MODE_01

#define GPIO_UART_UTXD4_PIN         GPIO158
#define GPIO_UART_UTXD4_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_UTXD4_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_UTXD4_PIN_M_UTXD   GPIO_MODE_01

#define GPIO_UART_URXD4_PIN         GPIO159
#define GPIO_UART_URXD4_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_URXD4_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_URXD4_PIN_M_URXD   GPIO_MODE_01

#define GPIO_UART_URXD1_PIN         GPIO160
#define GPIO_UART_URXD1_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_URXD1_PIN_M_URXD   GPIO_MODE_01

#define GPIO_UART_URTS1_PIN         GPIO161
#define GPIO_UART_URTS1_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_URTS1_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_URTS1_PIN_M_URTS   GPIO_MODE_01

#define GPIO_UART_UCTS1_PIN         GPIO162
#define GPIO_UART_UCTS1_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_UART_UCTS1_PIN_M_EINT   GPIO_MODE_02
#define GPIO_UART_UCTS1_PIN_M_UCTS   GPIO_MODE_01

#define GPIO_MATV_N_RST         GPIO175
#define GPIO_MATV_N_RST_M_GPIO   GPIO_MODE_00
#define GPIO_MATV_N_RST_M_EINT   GPIO_MODE_02
#define GPIO_MATV_N_RST_M_MSDC0_DAT   GPIO_MODE_01
#define GPIO_MATV_N_RST_M_NLD   GPIO_MODE_03

#define GPIO_ALS_EN_PIN         GPIO183
#define GPIO_ALS_EN_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_ALS_EN_PIN_M_EINT   GPIO_MODE_02

#define GPIO_CTP_RST_PIN         GPIO184
#define GPIO_CTP_RST_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_CTP_RST_PIN_M_EINT   GPIO_MODE_02

#define GPIO_CTP_EINT_PIN         GPIO185
#define GPIO_CTP_EINT_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_CTP_EINT_PIN_M_EINT   GPIO_MODE_02
#define GPIO_CTP_EINT_PIN_M_MSDC2_DAT   GPIO_MODE_01

#define GPIO_CTP_EN_PIN         GPIO187
#define GPIO_CTP_EN_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_CTP_EN_PIN_M_CLK   GPIO_MODE_04
#define GPIO_CTP_EN_PIN_M_EINT   GPIO_MODE_02

#define GPIO_CAMERA_CMPDN1_PIN         GPIO220
#define GPIO_CAMERA_CMPDN1_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_CAMERA_CMPDN1_PIN_M_EINT   GPIO_MODE_02
#define GPIO_CAMERA_CMPDN1_PIN_M_PWM   GPIO_MODE_01

#define GPIO_I2C1_SCA_PIN         GPIO222
#define GPIO_I2C1_SCA_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_I2C1_SCA_PIN_M_EINT   GPIO_MODE_02
#define GPIO_I2C1_SCA_PIN_M_SCL   GPIO_MODE_01

#define GPIO_I2C1_SDA_PIN         GPIO224
#define GPIO_I2C1_SDA_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_I2C1_SDA_PIN_M_EINT   GPIO_MODE_02
#define GPIO_I2C1_SDA_PIN_M_SDA   GPIO_MODE_01

#define GPIO_CAMERA_CMPDN_PIN         GPIO228
#define GPIO_CAMERA_CMPDN_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_CAMERA_CMPDN_PIN_M_EINT   GPIO_MODE_02
#define GPIO_CAMERA_CMPDN_PIN_M_CMPDN   GPIO_MODE_01

#define GPIO_CAMERA_CMRST1_PIN         GPIO230
#define GPIO_CAMERA_CMRST1_PIN_M_GPIO   GPIO_MODE_00
#define GPIO_CAMERA_CMRST1_PIN_M_CLK   GPIO_MODE_03
#define GPIO_CAMERA_CMRST1_PIN_M_EINT   GPIO_MODE_02
#define GPIO_CAMERA_CMRST1_PIN_M_CMFLASH   GPIO_MODE_01


/*Output for default variable names*/
/*@XXX_XX_PIN in gpio.cmp          */



#endif /* __CUST_GPIO_USAGE_H__ */



