#ifdef BUILD_LK
#else
#include <linux/string.h>
#if defined(BUILD_UBOOT)
#include <asm/arch/mt6575_gpio.h>
#else
#include <mach/mt6575_gpio.h>
#endif
#endif
#include "lcm_drv.h"

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (320)
#define FRAME_HEIGHT (480)
#define LCM_ID       (0x5310)

#ifdef BUILD_LK
#define LCM_PRINT printf
#else
#if defined(BUILD_UBOOT)
#define LCM_PRINT printf
#else
#define LCM_PRINT printk
#endif
#endif

#define LCM_PRINT_FUNC()  LCM_PRINT("LCM35310_TCL" "`%s:%d [%s] " "\n", __FILE__, __LINE__, __FUNCTION__)

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
    lcm_util.send_data(data&0xff);
}


static __inline unsigned int read_data_cmd()
{
    return lcm_util.read_data();
}


static __inline void set_lcm_register(unsigned int regIndex,
        unsigned int regData) {
    send_ctrl_cmd(regIndex);
    send_data_cmd(regData);
}

// LuckAs add Programming MTP
// Start
// Power On And Hardware Reset
//
// IInitialized Registers  (CMD1 or CMD2)for User Application
// ( If necessary )
//
// Sleep- Out
//
// Display- On
//
// Enter CMD2 and Optimize Register Setting
//
// Added external :7.5 V Power Source to MTP_PWR Pin
//
// Read NV Memory Flag Status (DDh)
// If (NVP _F =  1) then begin
// 
//
// (1) Enable MTP Write(Set reg DFh=01h)
// (2) EPWRITE Command(Set reg Deh parameter1 =
// 55h, parameter2 = AAh, parameter3 = 66h
// Read NV Memory Flag Status (DDh)
// if (NV_P = 1), then begin
//
// (1) Disable MTP Write (Set reg DFh = 00h)
// (2) Remove External : 7.5 V Power Source From_MTP_PWR Pin 
//
// Hardware Reset or Software Reset
//
// (1) Enter CMD2_P0 (Set EEDh=01h+FEh)
// (2) Margin read Set Register B8h = 02h
//
// Sleep- Out
//
// (1) Enter CMD2 and check all register are correct
// (2)Check Register DDh:
// NV_N0 = 1,NV_N1 = 0,NV_N2 = 0,NV_N3 = 0
//
// Re- excute MTP programming process
//
// LuckAs end

static void init_lcm_registers(void)
{
LCM_PRINT_FUNC();
send_ctrl_cmd(0xED); 	// CMD2UNLOCK
send_data_cmd(0x01);
send_data_cmd(0xFE);

send_ctrl_cmd(0xEE); 	// PAGE_CTRL Into CMD3 
send_data_cmd(0xDE);
send_data_cmd(0x21); 

send_ctrl_cmd(0xF1); 	// NONE!!!
send_data_cmd(0x01); 

send_ctrl_cmd(0xDF); 	// MTPPWR (DFh): MTP Write function enable
send_data_cmd(0x10); 	// only 00h, 01h have!!!

//  VCOM voltage //
send_ctrl_cmd(0xC4); 	// PWR_CTRL6 VCOM (set the VCOM voltage)
send_data_cmd(0x90); //94//90 // only 50h default have!!!! maybe 90/16bit=144=-1,8000

send_ctrl_cmd(0xB7); 	// CTRLEDPWM: Set the States for LED Control (B7h)
			// LEDPWPOL: Set the PWM active polarity for external LED driver control 
send_data_cmd(0x00);    // In other words, LEDPWPOL = “1” is suitable setting for “Low-Active” LED driver IC.
			// DD_C: This bit is usesd to enable / disable dimming function of CABC when DMCT = ‘1’
			// 05h default FIXME!!!

//  2 dot inversion  //
send_ctrl_cmd(0xB4); 	// NVCTR (B4h): Inversion Control, Display inversion mode set 
send_data_cmd(0x0D);	// NONE, 04h only have

//  GVDDP/N = 5V  //
send_ctrl_cmd(0xC0); 	// PWR_CTRL1 ADJ GVDDP/N, Set the GVDD regulator output voltage, 4st params
send_data_cmd(0x58);	// 58h have (think 58h = 4.25V)
send_data_cmd(0x58);    // 58h have
send_data_cmd(0x20);	// 08h have (think 20h = 3.3V)
send_data_cmd(0x20);	// 08h have

send_ctrl_cmd(0xC2);	// PWR_CTRL3 VGH & VGL, VGH charge pump circuit selection in full colors normal mode.(Normal mode on) 
send_data_cmd(0x44);	// 44h default 
send_data_cmd(0x44);	// 44h default
send_data_cmd(0x44);	// 44h default

send_ctrl_cmd(0xC6);	// PWR_CTRL6 VGH&VGL. VGL clamp voltage selection in full colors normal mode.(Normal mode on) CLAMP 
send_data_cmd(0x00);	// 1Bh default only have
send_data_cmd(0xE2);
send_data_cmd(0xE2);
send_data_cmd(0xE2);

send_ctrl_cmd(0xBF);	// PAGE_LOCK (BFh)：Set the Register to command2. This command is used for goto CMD2_P1 register access.
send_data_cmd(0xAA);	// AAh default

send_ctrl_cmd(0xB1);	// PORCH_CTRL: Front & Back Porch Setting (B1h). Determines the number of lines for internal display back porch period (in normal mode and idle mode)
send_data_cmd(0x80);	// 3-parameters 01h -2 lines, FFh=510 lines
send_data_cmd(0x00);
send_data_cmd(0x8B);
send_data_cmd(0x00);
send_data_cmd(0x96);
send_data_cmd(0x00);  


// LuckAs opisalovo
// - RTNA[7：0] / RTNB[7：0] / RTNC[7：0] are used to determine the 1H (line) period when NT35310 is under internal clock 
// synchronized display operation.   
// - The RTNA[7：0] / RTNB[7：0] / RTNC[7：0] are set depending on the panel resolution for frame rate adjustment. 
// The following table is the setting example of RTNA[7：0] / RTNB[7：0] / RTNC[7：0] for different panel resolutions 
// according to the frame frequency calculation formula below. 
// H Line no.  RTNA/B/C [7:0] Fosc (MHz) BP + FP Frame rate (Hz) 
// 480 141  12 32  60 
// 480 211  12 32  40 
// - The frame frequency can be changed by modifying the RTNA[7：0] / RTNB[7：0] / RTNC[7：0] setting. 
// - Make sure to set the proper frame frequency whenever the number of lines to drive the liquid crystal panel is changed.
send_ctrl_cmd(0xB2);	// DISPLAY_CTRL1 (B2h). Frame rate control in full colors normal mode (Normal mode on) 
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);

send_ctrl_cmd(0xB7);	// Povtor!!! CTRLEDPWM: Set the States for LED Control (B7h). LEDPWPOL:
			// Set the PWM active polarity for external LED driver control
send_data_cmd(0x3E);
send_data_cmd(0x00);
send_data_cmd(0x5E);
send_data_cmd(0x00);
send_data_cmd(0x9E);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x8C);
send_data_cmd(0x00);
send_data_cmd(0xAC);
send_data_cmd(0x00);
send_data_cmd(0xDC);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0xB9);
send_data_cmd(0x00);
send_data_cmd(0xEC);
send_data_cmd(0x00);
send_data_cmd(0xDC);
send_data_cmd(0x00);

send_ctrl_cmd(0xB8);	// MTP Selection (B8h). PTM:MTP margin read mode select. MTP_W_GMA: Used to enable/disable MTP write gamma
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00); 

send_ctrl_cmd(0xC2);	// PWR_CTRL3 (C2h). VGHA[2:0]: VGH charge pump circuit selection in full colors normal mode.(Normal mode on) 
			// VGHL_CLKA[2:0]: Set the operating frequency of the step-up circuit2 (VGH) in full colors normal mode.(Normal mode on)
send_data_cmd(0x0A);	// 3 parameters 44h only!!!
send_data_cmd(0x00);
send_data_cmd(0x04);
send_data_cmd(0x00); 

send_ctrl_cmd(0xC7);	// NONE!!!
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00); 

send_ctrl_cmd(0xC9);	// NONE!!!
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00); 


send_ctrl_cmd(0xE0);	// (E000~E017h) Sunlight Hysteresis Curve. 
			// - These registers are used to define hysteresis filter function. 
			// ALS_I1[15:0] ~ ALS_I3[15:0] define increment values, and ALS_D1[15:0]  ~ ALS_D3[15:0] define 
			// decrement values. Don’t care about the parameter values larger than “65535 (FFFFh)”. 
send_data_cmd(0x01);
send_data_cmd(0x00);
send_data_cmd(0x0A);
send_data_cmd(0x00);
send_data_cmd(0x22);
send_data_cmd(0x00);
send_data_cmd(0x43);
send_data_cmd(0x00);
send_data_cmd(0x56);
send_data_cmd(0x00);
send_data_cmd(0x66);
send_data_cmd(0x00);
send_data_cmd(0x7A);
send_data_cmd(0x00);
send_data_cmd(0x90);
send_data_cmd(0x00);
send_data_cmd(0xA1);
send_data_cmd(0x00);
send_data_cmd(0xAE);
send_data_cmd(0x00);
send_data_cmd(0xBA);
send_data_cmd(0x00);
send_data_cmd(0xC8);
send_data_cmd(0x00);
send_data_cmd(0xD0);
send_data_cmd(0x00);
send_data_cmd(0xD5);
send_data_cmd(0x00);
send_data_cmd(0xDB);
send_data_cmd(0x00);
send_data_cmd(0xE0);
send_data_cmd(0x00);
send_data_cmd(0xE7);
send_data_cmd(0x00);
send_data_cmd(0xF3);
send_data_cmd(0x00); 

// LuckAs opisalovo
// These registers are used for gamma correction. 
// ※  Note1: Please access this command in command2_P1. 
// ※  Note2: This command only can be read on display off. 
// ※  Note3: Please access all gamma table at 1 time.   
send_ctrl_cmd(0xE1);	// 3GAMAR_CTRL _RED_N (E1h). 36 parameters. 
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x0A);
send_data_cmd(0x00);
send_data_cmd(0x22);
send_data_cmd(0x00);
send_data_cmd(0x43);
send_data_cmd(0x00);
send_data_cmd(0x56);
send_data_cmd(0x00);
send_data_cmd(0x66);
send_data_cmd(0x00);
send_data_cmd(0x7A);
send_data_cmd(0x00);
send_data_cmd(0x90);
send_data_cmd(0x00);
send_data_cmd(0xA1);
send_data_cmd(0x00);
send_data_cmd(0xAE);
send_data_cmd(0x00);
send_data_cmd(0xBA);
send_data_cmd(0x00);
send_data_cmd(0xC8);
send_data_cmd(0x00);
send_data_cmd(0xD0);
send_data_cmd(0x00);
send_data_cmd(0xD5);
send_data_cmd(0x00);
send_data_cmd(0xDB);
send_data_cmd(0x00);
send_data_cmd(0xE0);
send_data_cmd(0x00);
send_data_cmd(0xE7);
send_data_cmd(0x00);
send_data_cmd(0xF3);
send_data_cmd(0x00);  

send_ctrl_cmd(0xE2);	// 3GAMMAR_CTRL _GREEN_P (E2h). These registers are used for gamma correction.
send_data_cmd(0x01);
send_data_cmd(0x00);
send_data_cmd(0x0A);
send_data_cmd(0x00);
send_data_cmd(0x22);
send_data_cmd(0x00);
send_data_cmd(0x43);
send_data_cmd(0x00);
send_data_cmd(0x56);
send_data_cmd(0x00);
send_data_cmd(0x66);
send_data_cmd(0x00);
send_data_cmd(0x79);
send_data_cmd(0x00);
send_data_cmd(0x90);
send_data_cmd(0x00);
send_data_cmd(0xA1);
send_data_cmd(0x00);
send_data_cmd(0xAE);
send_data_cmd(0x00);
send_data_cmd(0xBA);
send_data_cmd(0x00);
send_data_cmd(0xC8);
send_data_cmd(0x00);
send_data_cmd(0xD0);
send_data_cmd(0x00);
send_data_cmd(0xD5);
send_data_cmd(0x00);
send_data_cmd(0xDB);
send_data_cmd(0x00);
send_data_cmd(0xE0);
send_data_cmd(0x00);
send_data_cmd(0xE7);
send_data_cmd(0x00);
send_data_cmd(0xF3);
send_data_cmd(0x00); 


send_ctrl_cmd(0xE3);	// 3GAMMAR_CTRL _GREEN_N (E3h). These registers are used for gamma correction. 
			// To avoid contection during register accessing, please make sure that the CABC functions are disabled
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x0A);
send_data_cmd(0x00);
send_data_cmd(0x22);
send_data_cmd(0x00);
send_data_cmd(0x43);
send_data_cmd(0x00);
send_data_cmd(0x56);
send_data_cmd(0x00);
send_data_cmd(0x66);
send_data_cmd(0x00);
send_data_cmd(0x79);
send_data_cmd(0x00);
send_data_cmd(0x90);
send_data_cmd(0x00);
send_data_cmd(0xA1);
send_data_cmd(0x00);
send_data_cmd(0xAE);
send_data_cmd(0x00);
send_data_cmd(0xBA);
send_data_cmd(0x00);
send_data_cmd(0xC8);
send_data_cmd(0x00);
send_data_cmd(0xD0);
send_data_cmd(0x00);
send_data_cmd(0xD5);
send_data_cmd(0x00);
send_data_cmd(0xDB);
send_data_cmd(0x00);
send_data_cmd(0xE0);
send_data_cmd(0x00);
send_data_cmd(0xE7);
send_data_cmd(0x00);
send_data_cmd(0xF3);
send_data_cmd(0x00);  

send_ctrl_cmd(0xE4);	// 3GAMMAR_CTRL _BLUE_P (E4h). These registers are used for gamma correction.
send_data_cmd(0x01);
send_data_cmd(0x00);
send_data_cmd(0x0A);
send_data_cmd(0x00);
send_data_cmd(0x22);
send_data_cmd(0x00);
send_data_cmd(0x43);
send_data_cmd(0x00);
send_data_cmd(0x56);
send_data_cmd(0x00);
send_data_cmd(0x66);
send_data_cmd(0x00);
send_data_cmd(0x7A);
send_data_cmd(0x00);
send_data_cmd(0x90);
send_data_cmd(0x00);
send_data_cmd(0xA1);
send_data_cmd(0x00);
send_data_cmd(0xAE);
send_data_cmd(0x00);
send_data_cmd(0xBA);
send_data_cmd(0x00);
send_data_cmd(0xC8);
send_data_cmd(0x00);
send_data_cmd(0xD0);
send_data_cmd(0x00);
send_data_cmd(0xD5);
send_data_cmd(0x00);
send_data_cmd(0xDB);
send_data_cmd(0x00);
send_data_cmd(0xE0);
send_data_cmd(0x00);
send_data_cmd(0xE7);
send_data_cmd(0x00);
send_data_cmd(0xF3);
send_data_cmd(0x00); 


send_ctrl_cmd(0xE5);	// 3GAMMAR_CTRL _BLUE_N (E5h). These registers are used for gamma correction.
			// To avoid contection during register accessing, please make sure that the CABC functions are disabled.
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x0A);
send_data_cmd(0x00);
send_data_cmd(0x22);
send_data_cmd(0x00);
send_data_cmd(0x43);
send_data_cmd(0x00);
send_data_cmd(0x56);
send_data_cmd(0x00);
send_data_cmd(0x66);
send_data_cmd(0x00);
send_data_cmd(0x7A);
send_data_cmd(0x00);
send_data_cmd(0x90);
send_data_cmd(0x00);
send_data_cmd(0xA1);
send_data_cmd(0x00);
send_data_cmd(0xAE);
send_data_cmd(0x00);
send_data_cmd(0xBA);
send_data_cmd(0x00);
send_data_cmd(0xC8);
send_data_cmd(0x00);
send_data_cmd(0xD0);
send_data_cmd(0x00);
send_data_cmd(0xD5);
send_data_cmd(0x00);
send_data_cmd(0xDB);
send_data_cmd(0x00);
send_data_cmd(0xE0);
send_data_cmd(0x00);
send_data_cmd(0xE7);
send_data_cmd(0x00);
send_data_cmd(0xF3);
send_data_cmd(0x00); 


// LuckAs opislovo
// These registers are used for gamma correction. 
// ※  Note1: Please access this command in command2_P1. 
// ※  Note2: This command only can be read on display off. 
// ※  Note3: Please access all gamma table at 1 time.   
// To avoid contection during register accessing, please make sure that the CABC functions are disabled
send_ctrl_cmd(0xE6);	// CABC GAMMA offset (E6h). 
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x55);
send_data_cmd(0x00);
send_data_cmd(0x66);
send_data_cmd(0x00);
send_data_cmd(0x99);
send_data_cmd(0x00);
send_data_cmd(0x88);
send_data_cmd(0x00);
send_data_cmd(0x77);
send_data_cmd(0x00);
send_data_cmd(0x77);
send_data_cmd(0x00);
send_data_cmd(0x99);
send_data_cmd(0x00);
send_data_cmd(0xAA);
send_data_cmd(0x00);
send_data_cmd(0x88);
send_data_cmd(0x00);
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x33);
send_data_cmd(0x00);
send_data_cmd(0x33);
send_data_cmd(0x00);
send_data_cmd(0x22);
send_data_cmd(0x00); 


// LuckAs opislovo
// These registers are used for gamma correction. 
// ※  Note1: Please access this command in command2_P1. 
// ※  Note2: This command only can be read on display off. 
// ※  Note3: Please access all gamma table at 1 time.   
// To avoid contection during register accessing, please make sure that the CABC functions are disabled
send_ctrl_cmd(0xE7);	// CABC GAMMA offset (E7h). These registers are used for gamma correction
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x55);
send_data_cmd(0x00);
send_data_cmd(0x66);
send_data_cmd(0x00);
send_data_cmd(0x99);
send_data_cmd(0x00);
send_data_cmd(0x88);
send_data_cmd(0x00);
send_data_cmd(0x77);
send_data_cmd(0x00);
send_data_cmd(0x77);
send_data_cmd(0x00);
send_data_cmd(0x99);
send_data_cmd(0x00);
send_data_cmd(0xAA);
send_data_cmd(0x00);
send_data_cmd(0x88);
send_data_cmd(0x00);
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x33);
send_data_cmd(0x00);
send_data_cmd(0x33);
send_data_cmd(0x00);
send_data_cmd(0x22);
send_data_cmd(0x00);  


// LuckAs opislovo
// These registers are used for gamma correction. 
// ※  Note1: Please access this command in command2_P1. 
// ※  Note2: This command only can be read on display off. 
// ※  Note3: Please access all gamma table at 1 time.   
// To avoid contection during register accessing, please make sure that the CABC functions are disabled
send_ctrl_cmd(0xE8);	// CABC GAMMA offset (E8h).
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x55);
send_data_cmd(0x00);
send_data_cmd(0x66);
send_data_cmd(0x00);
send_data_cmd(0x99);
send_data_cmd(0x00);
send_data_cmd(0x88);
send_data_cmd(0x00);
send_data_cmd(0x77);
send_data_cmd(0x00);
send_data_cmd(0x77);
send_data_cmd(0x00);
send_data_cmd(0x99);
send_data_cmd(0x00);
send_data_cmd(0xAA);
send_data_cmd(0x00);
send_data_cmd(0x88);
send_data_cmd(0x00);
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x44);
send_data_cmd(0x00);
send_data_cmd(0x33);
send_data_cmd(0x00);
send_data_cmd(0x33);
send_data_cmd(0x00);
send_data_cmd(0x22);
send_data_cmd(0x00);  

send_ctrl_cmd(0xE9);	// NONE!!!
send_data_cmd(0xAA);
send_data_cmd(0x00);
send_data_cmd(0x00);
send_data_cmd(0x00);  

send_ctrl_cmd(0x00);	// PAGE_LOCK (00h)：Set the Register to command2 Page 0. This command is used for goto CMD2_P0 register access. 
send_data_cmd(0xAA);	// AAh default

send_ctrl_cmd(0xF3);	// NONE!!!
send_data_cmd(0x00);

send_ctrl_cmd(0xF9);	// NONE!!!
send_data_cmd(0x06);
send_data_cmd(0x10);
send_data_cmd(0x29);
send_data_cmd(0x00); 


// Luckas opisalovo 05-65K, 06-262K (may be need)
// - This command is used to define the format of RGB picture data, which is to be transferred via the MPU Interface. The
// formats are shown in the table: 
// IFPF[2 : 0]: Set the pixel format on MCU I/F 
// 101 5  16-bits / pixel 
// 110 6  18-bits / pixel 
// VIPF[2 : 0] : Set the pixel format on RGB I/F
// 101 5  16 bits / pixel (1-time transfer) 
// 110 6  18 bits / pixel (1-time transfer) 
// - There is no visible effect until the Frame Memory is written to.
send_ctrl_cmd(0x3A);	// SET_PIXEL_FORMAT (3Ah): Set the Interface Pixel Format.
send_data_cmd(0x66);

send_ctrl_cmd(0xB3);	// 
send_data_cmd(0x20);//mcu mipi
//send_ctrl_cmd(0xB3);
//send_data_cmd(0x21);//rgb interface

// LuckAs adaptive brightness (may be need)
send_ctrl_cmd(0x55);
send_data_cmd(0x00);
// LuckAs end

send_ctrl_cmd(0x11);
MDELAY(120);
send_ctrl_cmd(0x29);
// LuckAs tearing (may be need)
send_ctrl_cmd(0x35);
send_data_cmd(0x00); 
// LuckAs end

}


// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    LCM_PRINT_FUNC();    
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
    LCM_PRINT_FUNC();    

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


    /* params->dbi.parallel.write_setup    = 2; */
    /* params->dbi.parallel.write_hold     = 2; */
    /* params->dbi.parallel.write_wait     = 10; */
    /* params->dbi.parallel.read_setup     = 2; */
    /* params->dbi.parallel.read_hold      = 2; */
    /* params->dbi.parallel.read_latency   = 10; */
    /* params->dbi.parallel.wait_period    = 1; */

    params->dbi.parallel.write_setup    = 1;
    params->dbi.parallel.write_hold     = 1;
    params->dbi.parallel.write_wait     = 3;
    params->dbi.parallel.read_setup     = 4;
    params->dbi.parallel.read_hold      = 0;
    params->dbi.parallel.read_latency   = 18;
    params->dbi.parallel.wait_period    = 1;

// LuckAs disable tearing

//	// enable tearing-free
    params->dbi.te_mode                 = LCM_DBI_TE_MODE_VSYNC_ONLY;
    params->dbi.te_edge_polarity        = LCM_POLARITY_FALLING;
// LuckAs end
}

static unsigned int lcm_compare_id(void)
{
	LCM_PRINT_FUNC();
    MDELAY(50); 
    SET_RESET_PIN(1);
    MDELAY(1);
    SET_RESET_PIN(0);
    MDELAY(10);
    SET_RESET_PIN(1);
    MDELAY(50);
  
    unsigned int id = 0;
    unsigned int id1 = 0;
    unsigned int id2 = 0;
    unsigned int id3 = 0;
    unsigned int id4 = 0;
// LuckAs change
    send_ctrl_cmd(0xD4);
// orig
//    send_ctrl_cmd(0xd4);
// LuckAs end
    id1 = read_data_cmd();
    id2 = read_data_cmd();
    id3 = read_data_cmd();
    id4 = read_data_cmd();
    id = ((id3 << 8) | id4);
    LCM_PRINT("%s, id=0x%x, id1=0x%x, id2=0x%x, id3=0x%x, id4=0x%x\n", __func__, id, id1, id2, id3, id4);

    return (LCM_ID == id)?1:0;
}

static void lcm_init(void)
{
    LCM_PRINT_FUNC();
    MDELAY(50); 
    SET_RESET_PIN(1);
    MDELAY(1);
    SET_RESET_PIN(0);
    MDELAY(10);
    SET_RESET_PIN(1);
    MDELAY(50);

    init_lcm_registers();
}

static void lcm_suspend(void) {
    LCM_PRINT_FUNC();	
// LuckAs add
// brigthness off
//    send_ctrl_cmd(0x51);
//    send_data_cmd(0x00);
// LuckAs end
    send_ctrl_cmd(0x10);
    MDELAY(120);
// LuckAs add
// display off
//    send_ctrl_cmd(0x28);
// LuckAs end

}

static void lcm_resume(void) {
    LCM_PRINT_FUNC();	
    send_ctrl_cmd(0x11);
    MDELAY(120);
}

static void lcm_update(unsigned int x, unsigned int y,
        unsigned int width, unsigned int height) {
    unsigned short x0, y0, x1, y1;
    unsigned short h_X_start, l_X_start, h_X_end, l_X_end, h_Y_start, l_Y_start, h_Y_end, l_Y_end;

    x0 = (unsigned short) x;
    y0 = (unsigned short) y;
    x1 = (unsigned short) x + width - 1;
    y1 = (unsigned short) y + height - 1;

    h_X_start = ((x0 & 0xFF00) >> 8);
    l_X_start = (x0 & 0x00FF);
    h_X_end = ((x1 & 0xFF00) >> 8);
    l_X_end = (x1 & 0x00FF);

    h_Y_start = ((y0 & 0xFF00) >> 8);
    l_Y_start = (y0 & 0x00FF);
    h_Y_end = ((y1 & 0xFF00) >> 8);
    l_Y_end = (y1 & 0x00FF);

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


LCM_DRIVER nt35310_boe_lt3526_lcm_drv = 
{
    .name			= "nt35310_boe_lt3526",
    .set_util_funcs = lcm_set_util_funcs,
    .get_params     = lcm_get_params,
    .init           = lcm_init,
    .suspend        = lcm_suspend,
    .resume         = lcm_resume,
    .update         = lcm_update,
    .compare_id     = lcm_compare_id
};

