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
 
#include <linux/interrupt.h>
#include <cust_eint.h>
#include <linux/i2c.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/rtpm_prio.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/time.h>
 
#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif 

/*ergate-013*/
#include <linux/dma-mapping.h>

#include "tpd_custom_msg2133.h"
#include "tpd.h"

/*ergate-001*/
#include "cust_gpio_usage.h"

/*ergate-037*/
#include <linux/types.h>

#ifdef MT6575
#include <mach/mt6575_pm_ldo.h>
#include <mach/mt6575_typedefs.h>
#include <mach/mt6575_boot.h>
#endif

//zym 2011-12-26 for lcm_resume_in_lcd
#if defined(HQ_PROJECT_A16)
#include "lcm_drv.h"
#endif

#define LCT_ADD_TP_VERSION		1	//gpg add 
#ifdef LCT_DRV_PSSENSOR_USE_TP	// add by gpg
#include <linux/hwmsensor.h>
#include <linux/hwmsen_dev.h>
#include <linux/wakelock.h>

#define APS_TAG                  "[ALS/PS] "
#define APS_FUN(f)               printk(KERN_INFO APS_TAG"%s\n", __FUNCTION__)
#define APS_ERR(fmt, args...)    printk(KERN_ERR  APS_TAG"%s %d : "fmt, __FUNCTION__, __LINE__, ##args)
#define APS_LOG(fmt, args...)    printk(KERN_INFO APS_TAG fmt, ##args)
#define APS_DBG(fmt, args...)    printk(KERN_INFO APS_TAG fmt, ##args)   

static DEFINE_MUTEX(msg2133_sensor_mutex);

static int g_bPsSensorOpen = 0;
static int g_nPsSensorDate = 0;
static int g_bSuspend = 0;
static struct wake_lock ps_lock;

static int msg2133_enable_ps(int enable);
static void tpd_initialize_ps_sensor_function();
#endif

/*ergate-016 start*/
#if defined(HQ_PROJECT_A20)
#undef GPIO_CAPTOUCH_EINT_PIN
#undef GPIO_CAPTOUCH_EINT_PIN_M_EINT
#undef CUST_EINT_TOUCH_PANEL_NUM
#undef GPIO_CTP_EN_PIN

static int GPIO_CAPTOUCH_EINT_PIN,GPIO_CAPTOUCH_EINT_PIN_M_EINT,CUST_EINT_TOUCH_PANEL_NUM;
static int GPIO_CTP_EN_PIN;
#else // add for a16

#undef GPIO_CAPTOUCH_EINT_PIN
#undef GPIO_CAPTOUCH_EINT_PIN_M_EINT
#undef CUST_EINT_TOUCH_PANEL_NUM
//#undef GPIO_CTP_EN_PIN
static int GPIO_CAPTOUCH_EINT_PIN,GPIO_CAPTOUCH_EINT_PIN_M_EINT,CUST_EINT_TOUCH_PANEL_NUM;
//static int GPIO_CTP_EN_PIN;
#endif
/*ergate-016 end*/
#undef I2C_ENEXT_FLAG
#define I2C_ENEXT_FLAG 0

#define __FOR_TEST__ //add by zhaofei 2012-06-15 13:39:50
extern struct tpd_device *tpd;
 
static struct i2c_client *i2c_client = NULL;
static struct task_struct *thread = NULL;
 
static DECLARE_WAIT_QUEUE_HEAD(waiter);
 
static struct early_suspend early_suspend;
 
#ifdef CONFIG_HAS_EARLYSUSPEND
static void tpd_early_suspend(struct early_suspend *handler);
static void tpd_late_resume(struct early_suspend *handler);
#endif 
 
#define TPD_HAVE_BUTTON
extern void mt65xx_eint_unmask(unsigned int line);
extern void mt65xx_eint_mask(unsigned int line);
extern void mt65xx_eint_set_hw_debounce(kal_uint8 eintno, kal_uint32 ms);
extern kal_uint32 mt65xx_eint_set_sens(kal_uint8 eintno, kal_bool sens);
extern void mt65xx_eint_registration(kal_uint8 eintno, kal_bool Dbounce_En,
									  kal_bool ACT_Polarity, void (EINT_FUNC_PTR)(void),
									  kal_bool auto_umask);

 
static void tpd_eint_interrupt_handler(void);
static int tpd_get_bl_info(int show);
static int __devinit tpd_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int tpd_detect(struct i2c_client *client, int kind, struct i2c_board_info *info);
static int __devexit tpd_remove(struct i2c_client *client);
static int touch_event_handler(void *unused);
static int tpd_initialize(struct i2c_client * client);

extern int tpd_firmware_version[2];

#define HQ_PROJECT_A16
	
#if defined(HQ_PROJECT_A16)
static int pre_count =0;
static int pre_x1 =0;
static int pre_y1 =0;
static int pre_x2 =0;
static int pre_y2 =0;
#endif

#define TPD_OK 0

#define TPD_PACKET_HEAD_CMD    0x54
#define TPD_PACKET_HEAD_RSP    0x52

#define TPD_PACKET_CMD_VER    0x10

#define TPD_PACKET_CMD_MODE_READ    0x20
#define TPD_PACKET_CMD_MODE_WRITE   0x21
#define TPD_MODE_ACTIVE             0x10
#define TPD_MODE_FAST               0x20
#define TPD_MODE_FREEZE             0x90

#define TPD_PACKET_CMD_FORMAT_READ    0x60
#define TPD_PACKET_CMD_FORMAT_WRITE   0x61
#define TPD_PACKET_FORMAT_1           0x00
#define TPD_PACKET_FORMAT_2           0x01
#define TPD_PACKET_FORMAT_3           0x03

/*ergate-012 start*/
#ifdef TPD_HAVE_BUTTON 
static int tpd_keys_local[TPD_KEY_COUNT] = TPD_KEYS;
static int tpd_keys_dim_local[TPD_KEY_COUNT][4] = TPD_KEYS_DIM;
#endif
/*ergate-012 end*/
//wujinyou
struct TpdPacketT
{
    U8 head;
    U8 command;
    U8 data_1;
    U8 data_2;
};

struct TpdTouchDataT
{
	U8 packet_id;
	U8 x_h_y_h;
	U8 x_l;
	U8 y_l;
	U8 disx_h_disy_h;
	U8 disx_l;
	U8 disy_l;
    U8 checksum;
};

struct TouchInfoT
{
	int x1, y1;
	int x2, y2;
	int pressure;
	int count;
#ifdef TPD_HAVE_BUTTON 
    int key_id;
    int key_value;
#endif
};


static int tpd_flag = 0;

static struct TpdTouchDataT TpdTouchData;
#define TPD_DEVICE_MSG2133 "mtk-tpd-msg2133" 
static const struct i2c_device_id tpd_id[] = {{TPD_DEVICE,0},{}};
/*ergate-001*/
static unsigned short force[] = {0,0x4c,I2C_CLIENT_END,I2C_CLIENT_END};
static const unsigned short * const forces[] = { force, NULL };
static struct i2c_client_address_data addr_data = { .forces = forces, };
static struct i2c_driver tpd_driver = 
{
	.driver = 
	{
		.name = TPD_DEVICE,	//"msg2133",
		.owner = THIS_MODULE,
	},
	.probe = tpd_probe,
	.remove = __devexit_p(tpd_remove),
	.id_table = tpd_id,
	.detect = tpd_detect,
	.address_data = &addr_data,
};


/*FW UPDATE*/
#define DBG printk
#define FW_ADDR_MSG2133   0xc4 //device address of msg2133
#define FW_UPDATE_ADDR_MSG2133   0x92
static U8 temp[94][1024];   //
static int FwDataCnt;
//static int FwVersion;
struct class *firmware_class;
struct device *firmware_cmd_dev;
static  char *fw_version;


/*ergate-026 start*/
static int log_level = 0; //0-2(verbose)
#define TPD_LOGI(fmt, arg...)    if(log_level >= 1) \
        printk(KERN_ERR fmt, ##arg)

#define TPD_LOGV(fmt, arg...)    if(log_level >= 2) \
        printk(KERN_ERR fmt, ##arg)


static ssize_t show_loglevel(struct device_driver *ddri, char *buf);
static ssize_t store_loglevel(struct device_driver *ddri, char *buf, size_t count);
static DRIVER_ATTR(loglevel,   S_IWUSR | S_IRUGO, show_loglevel,      store_loglevel);
//extern int tpd_create_attr(struct driver_attribute *attr); 

static ssize_t show_loglevel(struct device_driver *ddri, char *buf)
{
	snprintf(buf,PAGE_SIZE,"level:%d\nrange:0-2(verbose)\n",log_level);
}


static ssize_t store_loglevel(struct device_driver *ddri, char *buf, size_t count)
{
	sscanf(buf,"%d",&log_level);
	return count;
}
/*ergate-026 end*/

#if defined(HQ_PROJECT_A18)
/*ergate-037 start*/
int state_down = 0;
int x_down,y_down,x_up,y_up;
struct timeval time_down,time_up;

int tpd_check_allow_key(void)
{
	int ret = 1;
	int64_t  delay;
	struct timeval now;

	do_gettimeofday(&now); 
	delay = (now.tv_sec*1000 + now.tv_usec/1000) - (time_up.tv_sec*1000 + time_up.tv_usec/1000);

	if((y_up-y_down > 100 && y_up > 300 && y_up < 400 && delay < (int64_t)80) ||
		(y_up-y_down > 100 && y_up >= 400 && y_up < 450 && delay < (int64_t)200) ||
		(y_up-y_down > 100 && y_up >= 450 && delay < (int64_t)300))
		ret = 0;

	TPD_LOGI("y_dis=%d,y_up=%d,delay=%lldms, ret:%d \n",y_up-y_down,y_up,delay,ret);

	return ret;
}
/*ergate-037 end*/
#endif

/*FW UPDATE*/
static int i2c_master_send_ext(struct i2c_client *client,const char *buf ,int count);
static int i2c_master_recv_ext(struct i2c_client *client, char *buf ,int count);


void HalTscrCDevWriteI2CSeq(u8 addr, u8* data, u16 size)
{
	u8 addr_bak;

	addr_bak = i2c_client->addr;
	i2c_client->addr = addr;
	i2c_client->addr |= I2C_ENEXT_FLAG;
	i2c_master_send_ext(i2c_client,data,size);
	i2c_client->addr = addr_bak;
}


void HalTscrCReadI2CSeq(u8 addr, u8* read_data, u8 size)
{
	u8 addr_bak;

	addr_bak = i2c_client->addr;
	i2c_client->addr = addr;
	i2c_client->addr |= I2C_ENEXT_FLAG;
	i2c_master_recv_ext(i2c_client,read_data,size);
	i2c_client->addr = addr_bak;
}


void Get_Chip_Version(void)
{

    unsigned char dbbus_tx_data[3];
    unsigned char dbbus_rx_data[2];

    dbbus_tx_data[0] = 0x10;
    dbbus_tx_data[1] = 0x1E;
    dbbus_tx_data[2] = 0xCE;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, &dbbus_tx_data[0], 3);
    HalTscrCReadI2CSeq(FW_ADDR_MSG2133, &dbbus_rx_data[0], 2);
    if (dbbus_rx_data[1] == 0)
    {
        // it is Catch2
        DBG("*** Catch2 ***\n");
        //FwVersion  = 2;// 2 means Catch2
    }
    else
    {
        // it is catch1
        DBG("*** Catch1 ***\n");
        //FwVersion  = 1;// 1 means Catch1
    }

}

void dbbusDWIICEnterSerialDebugMode()
{
    U8 data[5];

    // Enter the Serial Debug Mode
    data[0] = 0x53;
    data[1] = 0x45;
    data[2] = 0x52;
    data[3] = 0x44;
    data[4] = 0x42;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, data, 5);
}

void dbbusDWIICStopMCU()
{
    U8 data[1];

    // Stop the MCU
    data[0] = 0x37;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, data, 1);
}

void dbbusDWIICIICUseBus()
{
    U8 data[1];

    // IIC Use Bus
    data[0] = 0x35;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, data, 1);
}

void dbbusDWIICIICReshape()
{
    U8 data[1];

    // IIC Re-shape
    data[0] = 0x71;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, data, 1);
}

void dbbusDWIICIICNotUseBus()
{
    U8 data[1];

    // IIC Not Use Bus
    data[0] = 0x34;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, data, 1);
}

void dbbusDWIICNotStopMCU()
{
    U8 data[1];

    // Not Stop the MCU
    data[0] = 0x36;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, data, 1);
}

void dbbusDWIICExitSerialDebugMode()
{
    U8 data[1];

    // Exit the Serial Debug Mode
    data[0] = 0x45;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, data, 1);

    // Delay some interval to guard the next transaction
    //udelay ( 200 );        // delay about 0.2ms
}

void drvISP_EntryIspMode(void)
{
    U8 bWriteData[5] =
    {
        0x4D, 0x53, 0x54, 0x41, 0x52
    };

    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, bWriteData, 5);

    //udelay ( 1000 );        // delay about 1ms
}

U8 drvISP_Read(U8 n, U8* pDataToRead)    //First it needs send 0x11 to notify we want to get flash data back.
{
    U8 Read_cmd = 0x11;
    unsigned char dbbus_rx_data[2] = {0};
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &Read_cmd, 1);
    udelay(100);//10 zzf
    if (n == 1)
    {
        HalTscrCReadI2CSeq(FW_UPDATE_ADDR_MSG2133, &dbbus_rx_data[0], 2);
        *pDataToRead = dbbus_rx_data[0];
    }
    else
        HalTscrCReadI2CSeq(FW_UPDATE_ADDR_MSG2133, pDataToRead, n);

}

void drvISP_WriteEnable(void)
{
    U8 bWriteData[2] =
    {
        0x10, 0x06
    };
    U8 bWriteData1 = 0x12;
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, bWriteData, 2);
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &bWriteData1, 1);
}


void drvISP_ExitIspMode(void)
{
    U8 bWriteData = 0x24;
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &bWriteData, 1);
}

U8 drvISP_ReadStatus()
{
    U8 bReadData = 0;
    U8 bWriteData[2] =
    {
        0x10, 0x05
    };
    U8 bWriteData1 = 0x12;

    udelay(100);
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, bWriteData, 2);
    udelay(100);
    drvISP_Read(1, &bReadData);   
    mdelay(10);//3->10 zzf
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &bWriteData1, 1);
    return bReadData;
}


void drvISP_BlockErase(U32 addr)
{
    U8 bWriteData[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 };
    U8 bWriteData1 = 0x12;
    u32 timeOutCount=0;
    drvISP_WriteEnable();

    //Enable write status register
    bWriteData[0] = 0x10;
    bWriteData[1] = 0x50;
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, bWriteData, 2);
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &bWriteData1, 1);

    //Write Status
    bWriteData[0] = 0x10;
    bWriteData[1] = 0x01;
    bWriteData[2] = 0x00;
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, bWriteData, 3);
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &bWriteData1, 1);

    //Write disable
    bWriteData[0] = 0x10;
    bWriteData[1] = 0x04;
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, bWriteData, 2);
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &bWriteData1, 1);

    udelay(100);
    timeOutCount=0;
	while ( ( drvISP_ReadStatus() & 0x01 ) == 0x01 )
    {
		   timeOutCount++;
	     if ( timeOutCount >= 10000 ) 
            break; /* around 1 sec timeout */
    }
    drvISP_WriteEnable();

    drvISP_ReadStatus();//zzf

    bWriteData[0] = 0x10;
    bWriteData[1] = 0xc7;//0xD8;        //Block Erase
    //bWriteData[2] = ((addr >> 16) & 0xFF) ;
    //bWriteData[3] = ((addr >> 8) & 0xFF) ;
    //bWriteData[4] = (addr & 0xFF) ;
    //HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &bWriteData, 5);
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, bWriteData, 2);
    HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &bWriteData1, 1);

    udelay(100);
    timeOutCount=0;
    while ( ( drvISP_ReadStatus() & 0x01 ) == 0x01 )
    {
        timeOutCount++;
        if ( timeOutCount >= 50000 ) 
            break; /* around 5 sec timeout */
    }
}

void drvISP_Program(U16 k, U8* pDataToWrite)
{
    U16 i = 0;
    U16 j = 0;
    //U16 n = 0;
    U8 TX_data[133];
    U8 bWriteData1 = 0x12;
    U32 addr = k * 1024;
    U32 timeOutCount = 0;

    for (j = 0; j < 8; j++)   //256*4 cycle
    {
        TX_data[0] = 0x10;
        TX_data[1] = 0x02;// Page Program CMD
        TX_data[2] = (addr + 128 * j) >> 16;
        TX_data[3] = (addr + 128 * j) >> 8;
        TX_data[4] = (addr + 128 * j);
        for (i = 0; i < 128; i++)
        {
            TX_data[5 + i] = pDataToWrite[j * 128 + i];
        }

    udelay(100);
    timeOutCount=0;
	while ( ( drvISP_ReadStatus() & 0x01 ) == 0x01 )
    {
		   timeOutCount++;
	     if ( timeOutCount >= 10000 ) 
            break; /* around 1 sec timeout */
    }

        drvISP_WriteEnable();
        HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, TX_data, 133);   //write 256 byte per cycle
        HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &bWriteData1, 1);
    }
}


int drvISP_Verify(U16 k, U8* pDataToVerify)
{
    U16 i = 0, j = 0, m = 0;
    U8 bWriteData[5] =
    {
        0x10, 0x03, 0, 0, 0
    };
    U8 RX_data[256];
    U8 bWriteData1 = 0x12;
    U32 addr = k * 1024;
    U32 timeOutCount = 0;
    u8 index=0;
    int result = -1;

    for (j = 0; j < 8; j++)   //128*8 cycle
    {
        bWriteData[2] = (U8)((addr + j * 128) >> 16);
        bWriteData[3] = (U8)((addr + j * 128) >> 8);
        bWriteData[4] = (U8)(addr + j * 128);
        //while ((drvISP_ReadStatus() & 0x01) == 0x01);     //wait until not in write operation
        udelay(100);
        timeOutCount=0;
	    while ( ( drvISP_ReadStatus() & 0x01 ) == 0x01 )
        {
		       timeOutCount++;
	         if ( timeOutCount >= 100000 ) 
                break; /* around 1 sec timeout */
        }

        HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, bWriteData, 5);    //write read flash addr
        udelay(100);
        drvISP_Read(128, &RX_data);
        HalTscrCDevWriteI2CSeq(FW_UPDATE_ADDR_MSG2133, &bWriteData1, 1);    //cmd end
        for (i = 0; i < 128; i++)   //log out if verify error
        {
            if((RX_data[i]!=0)&&index<10)
		    {
            //TP_DEBUG("j=%d,RX_data[%d]=0x%x\n",j,i,RX_data[i]);
                index++;
		    }
            if (RX_data[i] != pDataToVerify[128 * j + i])
            {
                //printk("k=%d,j=%d,i=%d===============Update Firmware Error================",k,j,i);
                result = i;
                break;
            }
        }
    }

    return result;
}

static ssize_t firmware_update_show(struct device *dev,
                                    struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%s\n", fw_version);
}


static void tpd_hw_enable(unsigned int on);
static void tpd_hw_power(unsigned int on);
static ssize_t firmware_update_store(struct device *dev,
                                     struct device_attribute *attr, const char *buf, size_t size)
{
    U8 i;
    U8 dbbus_tx_data[4];
    unsigned char dbbus_rx_data[2] = {0};
    int fd;
    int count = 0;
    //msctpc_LoopDelay ( 100 );        // delay about 100ms*****
    //add mask interrupt
    mt65xx_eint_mask(CUST_EINT_TOUCH_PANEL_NUM);
    mt65xx_eint_registration(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_DEBOUNCE_EN, CUST_EINT_TOUCH_PANEL_POLARITY, 			NULL, 1);

    tpd_hw_power(0);
    mdelay(10);
    tpd_hw_power(1);
    mdelay(300);
    drvISP_EntryIspMode();
    drvISP_BlockErase(0x00000);
    mdelay(300);
    tpd_hw_power(0);
    mdelay(10);
    tpd_hw_power(1);

    count = 0;
    mdelay(300);

#if 1
    // Enable slave's ISP ECO mode
    dbbusDWIICEnterSerialDebugMode();
    dbbusDWIICStopMCU();
    dbbusDWIICIICUseBus();
    dbbusDWIICIICReshape();

    dbbus_tx_data[0] = 0x10;
    dbbus_tx_data[1] = 0x08;
    dbbus_tx_data[2] = 0x0c;
    dbbus_tx_data[3] = 0x08;

    // Disable the Watchdog
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 4);


    //Get_Chip_Version();

        dbbus_tx_data[0] = 0x10;
        dbbus_tx_data[1] = 0x11;
        dbbus_tx_data[2] = 0xE2;
        dbbus_tx_data[3] = 0x00;

        HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 4);

    dbbus_tx_data[0] = 0x10;
    dbbus_tx_data[1] = 0x3C;
    dbbus_tx_data[2] = 0x60;
    dbbus_tx_data[3] = 0x55;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 4);
    dbbus_tx_data[0] = 0x10;
    dbbus_tx_data[1] = 0x3C;
    dbbus_tx_data[2] = 0x61;
    dbbus_tx_data[3] = 0xAA;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 4);

//Stop MCU
    dbbus_tx_data[0] = 0x10;
    dbbus_tx_data[1] = 0x0F;
    dbbus_tx_data[2] = 0xE6;
    dbbus_tx_data[3] = 0x01;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 4);

//Enable SPI Pad
    dbbus_tx_data[0] = 0x10;
    dbbus_tx_data[1] = 0x1E;
    dbbus_tx_data[2] = 0x02;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 3);
    HalTscrCReadI2CSeq(FW_ADDR_MSG2133, &dbbus_rx_data[0], 2);
    DBG("dbbus_rx_data[0]=0x%x", dbbus_rx_data[0]);
    dbbus_tx_data[3] = (dbbus_rx_data[0] | 0x20);  //Set Bit 5
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 4);

    dbbus_tx_data[0] = 0x10;
    dbbus_tx_data[1] = 0x1E;
    dbbus_tx_data[2] = 0x25;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 3);
    dbbus_rx_data[0] = 0;
    dbbus_rx_data[1] = 0;
    HalTscrCReadI2CSeq(FW_ADDR_MSG2133, &dbbus_rx_data[0], 2);
    DBG("dbbus_rx_data[0]=0x%x", dbbus_rx_data[0]);
    dbbus_tx_data[3] = dbbus_rx_data[0] & 0xFC;  //Clear Bit 1,0
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 4);

//WP overwrite
    dbbus_tx_data[0] = 0x10;
    dbbus_tx_data[1] = 0x1E;
    dbbus_tx_data[2] = 0x0E;
    dbbus_tx_data[3] = 0x02;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 4);

//set pin high
    dbbus_tx_data[0] = 0x10;
    dbbus_tx_data[1] = 0x1E;
    dbbus_tx_data[2] = 0x10;
    dbbus_tx_data[3] = 0x08;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 4);

//set FRO to 50M
    dbbus_tx_data[0] = 0x10;
    dbbus_tx_data[1] = 0x11;
    dbbus_tx_data[2] = 0xE2;
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 3);
    dbbus_rx_data[0] = 0;
    dbbus_rx_data[1] = 0;
    HalTscrCReadI2CSeq(FW_ADDR_MSG2133, &dbbus_rx_data[0], 2);
    //printk("dbbus_rx_data[0]=0x%x", dbbus_rx_data[0]);
    dbbus_tx_data[3] = dbbus_rx_data[0] & 0xF7;  //Clear Bit 1,0
    HalTscrCDevWriteI2CSeq(FW_ADDR_MSG2133, dbbus_tx_data, 4);

    dbbusDWIICIICNotUseBus();
    dbbusDWIICNotStopMCU();
    dbbusDWIICExitSerialDebugMode();

    ///////////////////////////////////////
    // Start to load firmware
    ///////////////////////////////////////
    drvISP_EntryIspMode();
    //drvISP_BlockErase(0x00000);//////zzf 
        //DBG("FwVersion=2");
    for (i = 0; i < 94; i++)   // total  94 KB : 1 byte per R/W
    {
        drvISP_Program(i, temp[i]);    // program to slave's flash
#if 0
        if(drvISP_Verify ( i, temp[i] ) != -1 && count < 3)//; //verify data
        {
            count++;
            if(count == 3)
            {
                count = 0;
                continue;
            }
            i--;
        }
        else
        {
            count = 0;
        }
#endif
        mdelay(1);
    }
#endif
    drvISP_ExitIspMode();
    FwDataCnt = 0;

	mt65xx_eint_registration(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_DEBOUNCE_EN, CUST_EINT_POLARITY_HIGH, tpd_eint_interrupt_handler,1);
	mt65xx_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM);


    return size;
}

static DEVICE_ATTR(update, 0775, firmware_update_show, firmware_update_store);

/*Add by Tracy.Lin for update touch panel firmware and get fw version*/

static ssize_t firmware_version_show(struct device *dev,
                                     struct device_attribute *attr, char *buf)
{
	unsigned char dbbus_tx_data[3];
    unsigned char dbbus_rx_data[4] ;
    unsigned short major=0, minor=0;
    fw_version = kzalloc(sizeof(char), GFP_KERNEL);

    Get_Chip_Version();
    dbbus_tx_data[0] = 0x53;
    dbbus_tx_data[1] = 0x00;
    dbbus_tx_data[2] = 0x74;
    HalTscrCDevWriteI2CSeq(0x4C, &dbbus_tx_data[0], 3);
    HalTscrCReadI2CSeq(0x4C, &dbbus_rx_data[0], 4);
    major = (dbbus_rx_data[1]<<8)+dbbus_rx_data[0];
    minor = (dbbus_rx_data[3]<<8)+dbbus_rx_data[2];
    DBG("***major = %d ***\n", major);
    DBG("***minor = %d ***\n", minor);
    sprintf(fw_version,"%03d%03d", major, minor);

 
    return sprintf(buf, "%s\n", fw_version);
}

static ssize_t firmware_version_store(struct device *dev,
                                      struct device_attribute *attr, const char *buf, size_t size)
{

    //dbbusDWIICEnterSerialDebugMode();
    //dbbusDWIICStopMCU();
    //dbbusDWIICIICUseBus();
    //dbbusDWIICIICReshape();

    unsigned char dbbus_tx_data[3];
    unsigned char dbbus_rx_data[4] ;
    unsigned short major=0, minor=0;
    fw_version = kzalloc(sizeof(char), GFP_KERNEL);

    Get_Chip_Version();
    dbbus_tx_data[0] = 0x53;
    dbbus_tx_data[1] = 0x00;
    dbbus_tx_data[2] = 0x74;
    HalTscrCDevWriteI2CSeq(0x4C, &dbbus_tx_data[0], 3);
    HalTscrCReadI2CSeq(0x4C, &dbbus_rx_data[0], 4);
    major = (dbbus_rx_data[1]<<8)+dbbus_rx_data[0];
    minor = (dbbus_rx_data[3]<<8)+dbbus_rx_data[2];
    DBG("***major = %d ***\n", major);
    DBG("***minor = %d ***\n", minor);
    sprintf(fw_version,"%03d%03d", major, minor);
    DBG("***fw_version = %s ***\n", fw_version);

    return size;
	
}
static DEVICE_ATTR(version, 0775, firmware_version_show, firmware_version_store);

static ssize_t firmware_data_show(struct device *dev,
                                  struct device_attribute *attr, char *buf)
{
    return FwDataCnt;
}

static ssize_t firmware_data_store(struct device *dev,
                                   struct device_attribute *attr, const char *buf, size_t size)
{
    DBG("***FwDataCnt = %d ***\n", FwDataCnt);
    int i;
    for (i = 0; i < 1024; i++)
    {
        memcpy(temp[FwDataCnt], buf, 1024);
    }
    FwDataCnt++;
    return size;
}
static DEVICE_ATTR(data, 0775, firmware_data_show, firmware_data_store);


/*ergate-001 start*/
static void tpd_hw_power(unsigned int on)
{
#if 0
	if(on)
	{
		if(TRUE != hwPowerOn(MT65XX_POWER_LDO_VGP, VOL_1800,"TP"))
		{
			printk("[1800] Fail to enable digital power\n");
		}
		if(TRUE != hwPowerOn(MT65XX_POWER_LDO_VCAM_AF, VOL_2800,"TP"))
		{
			printk("[2800] Fail to enable digital power\n");
		}
		msleep(100);
	}
	else
	{
		if(TRUE != hwPowerDown(MT65XX_POWER_LDO_VGP, "TP"))
		{
			printk("[1800] Fail to enable digital power\n");
		}
		if(TRUE != hwPowerDown(MT65XX_POWER_LDO_VCAM_AF, "TP"))
		{
			printk("[2800] Fail to enable digital power\n");
		}
		msleep(100);
	}
	msleep(30);
#endif

	printk("++++ctp_power_on = %d\n",on);	
	//return ;

	if(on == 1)
	{
		//mt_set_gpio_mode(GPIO_CTP_EN_PIN, GPIO_CTP_EN_PIN_M_GPIO);
  		//mt_set_gpio_dir(GPIO_CTP_EN_PIN, GPIO_DIR_OUT);
		//mt_set_gpio_out(GPIO_CTP_EN_PIN, GPIO_OUT_ONE);
#ifdef __LCT_AG701_DRIVER__
          if(TRUE != hwPowerOn(MT65XX_POWER_LDO_VGP2, VOL_2800,"TP"))
            {
                printk("[ctp_power_on] Fail to enable MT65XX_POWER_LDO_VGP power\n");
            }
#else
          if(TRUE != hwPowerOn(MT65XX_POWER_LDO_VCAM_AF, VOL_2800,"TP"))
            {
                printk("[ctp_power_on] Fail to enable MT65XX_POWER_LDO_VCAM_AF power\n");
            }
	      if(TRUE != hwPowerOn(MT65XX_POWER_LDO_VGP, VOL_1800,"TP"))
            {
                printk("[ctp_power_on] Fail to enable MT65XX_POWER_LDO_VGP power\n");
            }
     #endif
	}
	else
	{
#ifdef __LCT_AG701_DRIVER__
		if(TRUE != hwPowerDown(MT65XX_POWER_LDO_VGP2,"TP")) {
	                printk("[ctp_power_on] Fail to disable MT65XX_POWER_LDO_VGP power\n");
		    //return -EIO;
		}
#else
		if(TRUE != hwPowerDown(MT65XX_POWER_LDO_VCAM_AF,"TP")) {
	                printk("[ctp_power_on] Fail to disable MT65XX_POWER_LDO_VGP2 power\n");
		    //return -EIO;
		}
		if(TRUE != hwPowerDown(MT65XX_POWER_LDO_VGP,"TP"))
		{
			printk("[ctp_power_on] Fail to enable MT65XX_POWER_LDO_VGP power\n");
    	}
#endif		
	}

}


static void tpd_hw_reset(void)
{
}


static void tpd_hw_enable(unsigned int on)
{
	mt_set_gpio_mode(GPIO_CTP_RST_PIN,GPIO_MODE_00);
	mt_set_gpio_dir(GPIO_CTP_RST_PIN,GPIO_DIR_OUT);
  mdelay(10);

#if defined(LCT_TP_YEJI_MSG2133)
	printk("[ctp_power_on] __LCT_AG700A_001_DRIVER__ process\n");

	if(!on)//if(on) //gpg decided by FPC
	{
		mt_set_gpio_out(GPIO_CTP_RST_PIN,GPIO_OUT_ZERO);
	}
	else
	{
		mt_set_gpio_out(GPIO_CTP_RST_PIN,GPIO_OUT_ONE);
	}
#else
	printk("[ctp_power_on] default process\n");

	if(on)//if(on) //gpg decided by FPC
	{
		mt_set_gpio_out(GPIO_CTP_RST_PIN,GPIO_OUT_ZERO);
	}
	else
	{
		mt_set_gpio_out(GPIO_CTP_RST_PIN,GPIO_OUT_ONE);
	}
#endif
    mdelay(50);
}


/*
mode:
0: output 0
1: output 1
2: eint
*/
static void tpd_hw_config_eint_pin(int mode)
{
	switch(mode)
	{
	case 0:
		mt_set_gpio_mode(GPIO_CAPTOUCH_EINT_PIN,GPIO_MODE_00);
		mt_set_gpio_dir(GPIO_CAPTOUCH_EINT_PIN,GPIO_DIR_OUT);
		mt_set_gpio_out(GPIO_CAPTOUCH_EINT_PIN,GPIO_OUT_ZERO);
		break;
	case 1:
		mt_set_gpio_mode(GPIO_CAPTOUCH_EINT_PIN,GPIO_MODE_00);
		mt_set_gpio_dir(GPIO_CAPTOUCH_EINT_PIN,GPIO_DIR_OUT);
		mt_set_gpio_out(GPIO_CAPTOUCH_EINT_PIN,GPIO_OUT_ONE);
		break;
	case 2:
		mt_set_gpio_mode(GPIO_CAPTOUCH_EINT_PIN, GPIO_CAPTOUCH_EINT_PIN_M_EINT);
		mt_set_gpio_dir(GPIO_CAPTOUCH_EINT_PIN, GPIO_DIR_IN);
		mt_set_gpio_pull_enable(GPIO_CAPTOUCH_EINT_PIN, GPIO_PULL_ENABLE);
		mt_set_gpio_pull_select(GPIO_CAPTOUCH_EINT_PIN, GPIO_PULL_UP);
		break;
	default:
		break;			
	}
}
/*ergate-001 end*/


#if 1
/*ergate-009 start*/
static ssize_t show_calibrate(struct device_driver *ddri, char *buf);
static ssize_t store_calibrate(struct device_driver *ddri, char *buf, size_t count);
static DRIVER_ATTR(calibrate,   S_IWUSR | S_IRUGO, show_calibrate,      store_calibrate);
//extern int tpd_create_attr(struct driver_attribute *attr); 

static int tpd_hw_calibrate(void)
{
	int retval = TPD_OK;

	return 0;
}

static ssize_t show_calibrate(struct device_driver *ddri, char *buf)
{
    TPD_LOGI("tpd show_calibrate\n");

    snprintf(buf,PAGE_SIZE,"%s\n","tpd show_calibrate");
}


static ssize_t store_calibrate(struct device_driver *ddri, char *buf, size_t count)
{
    int retval = TPD_OK;
    TPD_LOGI("tpd store_calibrate:%s\n",buf);
    if(!strncmp(buf,"cali",4))
    {
        TPD_LOGI("tpd begin calibration...\n");
        retval = tpd_hw_calibrate();
        TPD_LOGI("tpd end calibration=%d\n",retval);
    }
    else
    {
        TPD_LOGI("Invalid format\n");
    }
}
/*ergate-009 end*/
#endif


/*ergate-013 start*/
#define MAX_CMD_LEN 255
static int i2c_master_send_ext(struct i2c_client *client,const char *buf ,int count)
{
	u8 *buf_dma = NULL;
	u32 old_addr = 0; 
	int ret = 0; 
	int retry = 3; 

	if (count > MAX_CMD_LEN) {
		printk("[i2c_master_send_ext] exceed the max write length \n"); 
		return -1; 
	}
	
	buf_dma= kmalloc(count,GFP_KERNEL);
	
	old_addr = client->addr; 
	client->addr |= I2C_ENEXT_FLAG ; 
	
	memcpy(buf_dma, buf, count); 
	
	do {
		ret = i2c_master_send(client, (u8*)buf_dma, count); 	
		retry --; 
		if (ret != count) {
			printk("[i2c_master_send_ext] Error sent I2C ret = %d\n", ret); 
		}
	}while ((ret != count) && (retry > 0)); 

	client->addr = old_addr; 
	kfree(buf_dma);
	
	return ret; 

}


static int i2c_master_recv_ext(struct i2c_client *client, char *buf ,int count)
{
    u32 phyAddr = 0; 
    u8  buf_dma[8] = {0};
    u32 old_addr = 0; 
    int ret = 0; 
    int retry = 3; 
    int i = 0; 
    u8  *buf_test ;
	buf_test = &buf_dma[0];

    old_addr = client->addr; 
    client->addr |= I2C_ENEXT_FLAG ;
	
	TPD_LOGI("[i2c_master_recv_ext] client->addr = %x\n", client->addr); 
    do {
        ret = i2c_master_recv(client, buf_dma, count);   
        retry --; 
        if (ret != count) {
            TPD_LOGI("[i2c_master_recv_ext] Error sent I2C ret = %d\n", ret); 
        }
    }while ((ret != count) && (retry > 0)); 
    
    memcpy(buf, buf_dma, count); 
	
    client->addr = old_addr; 

    return ret; 
}
/*ergate-013 end*/


static int tpd_switch_mode(U8 mode)
{
	int retval = TPD_OK;
    struct TpdPacketT packet = 
    {
        TPD_PACKET_HEAD_CMD,
        TPD_PACKET_CMD_MODE_WRITE,
        0x00,
        mode
    };
 
    retval = i2c_master_send(i2c_client, &packet, sizeof(packet));
    msleep(5);
    if(mode != TPD_MODE_FREEZE)
        retval = i2c_master_recv(i2c_client, &packet, sizeof(packet));

	if(retval < TPD_OK)
		return -1;

	return 0;
}


static void tpd_down(int x, int y, int p)
{
	input_report_abs(tpd->dev, ABS_PRESSURE, 128);
	input_report_key(tpd->dev, BTN_TOUCH, 1);
	input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, 128);
	input_report_abs(tpd->dev, ABS_MT_POSITION_X, x);
	input_report_abs(tpd->dev, ABS_MT_POSITION_Y, y);
	TPD_LOGV("######tpd_down[%4d %4d %4d] ", x, y, p);
	input_mt_sync(tpd->dev);
	TPD_DOWN_DEBUG_TRACK(x,y);
}

#if defined(HQ_PROJECT_A16)
static int tpd_up(int x, int y,int p)
{
	input_report_abs(tpd->dev, ABS_PRESSURE, 0);
	input_report_key(tpd->dev, BTN_TOUCH, 0);
	input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, 0);
	input_report_abs(tpd->dev, ABS_MT_POSITION_X, x);
	input_report_abs(tpd->dev, ABS_MT_POSITION_Y, y);
	TPD_LOGV("######UP[%4d %4d %4d] ", x, y, p);
	input_mt_sync(tpd->dev);
	TPD_UP_DEBUG_TRACK(x,y);
}
#else
static int tpd_up(int x, int y,int *count)
{
	if(*count>0) 
	{
		input_report_abs(tpd->dev, ABS_PRESSURE, 0);
		input_report_key(tpd->dev, BTN_TOUCH, 0);
		input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, 0);
		input_report_abs(tpd->dev, ABS_MT_POSITION_X, x);
		input_report_abs(tpd->dev, ABS_MT_POSITION_Y, y);
		//TPD_LOGV("U[%4d %4d %4d] ", x, y, 0);
		input_mt_sync(tpd->dev);
		TPD_UP_DEBUG_TRACK(x,y);
		(*count)--;
		return 1;
	} 
	return 0;
}
#endif
static void tpd_button_msg2133(U8 key_value)
{
	U8 cust_key=0, key=0;
	static U8 last_key=0;
	
	if(key_value == 0)
	{
   		input_report_key(tpd->dev, last_key, 0);
		return;
	}
	key_value >>= 1;
	key =  tpd_keys_local[key_value];
    input_report_key(tpd->dev, key, 1);

	last_key = key;
}

static int cust_key_define = 0;
static void cust_tpd_button_msg2133(U8 key_value, U8 flag)
{
	U8 cust_key=0, key=0;
	static U8 last_key=0;
	static U8 last_key_value=0;
// no use 	add comment by gpg
	if(key_value == 0)
	{
		tpd_up(tpd_keys_dim_local[last_key_value][0],tpd_keys_dim_local[last_key_value][1],1); //add by zhaofei 2012-07-09 09:42:45
		input_sync(tpd->dev);
		//printk("<<<zhaofei release x = %d, y = %d, \n",tpd_keys_dim_local[last_key_value][0],tpd_keys_dim_local[last_key_value][1]);
   		//input_report_key(tpd->dev, last_key, 0);
		return;
	}
// no use end	
	key_value >>= 1;
	key =  tpd_keys_local[key_value];
    //input_report_key(tpd->dev, key, 1);

	// add by gpg for release
	pre_x1 = tpd_keys_dim_local[key_value][0];	
	pre_y1 = tpd_keys_dim_local[key_value][1];
	// end by gpg

	tpd_down(tpd_keys_dim_local[key_value][0],tpd_keys_dim_local[key_value][1],1); //add by zhaofei 2012-07-09 09:42:45
	input_sync(tpd->dev);
	//printk("<<<zhaofei down   x = %d, y = %d, \n",tpd_keys_dim_local[key_value][0],tpd_keys_dim_local[key_value][1]);

	last_key = key;
	last_key_value = key_value;
}					
static int tpd_touchinfo(struct TouchInfoT *cinfo, struct TouchInfoT *pinfo)
{
	u32 retval;
    u8 key;

	//pinfo->count = cinfo->count;
    memcpy(pinfo, cinfo, sizeof(struct TouchInfoT));
    
    //add for sure addr correct
    //i2c_client->addr = 0x4c;
    retval = i2c_master_recv_ext(i2c_client, (u8 *)&TpdTouchData, sizeof(TpdTouchData));
	{
//		int i;
//		for(i=0; i<sizeof(TpdTouchData); i++)
//			printk("%02x ",*((u8 *)((u8 *)(&TpdTouchData)+i)));
//		printk("\n");
	}

	if(TpdTouchData.packet_id != 0x52 )
       {
		return 0;
       }
	/*touch*/
	if(TpdTouchData.packet_id == 0x52)
	{
#ifdef LCT_DRV_PSSENSOR_USE_TP
		if(TpdTouchData.disx_l == 0x80) // close Panel
		{
			printk(TPD_DEVICE"TP_PROXIMITY_SENSOR111 msg21xx_do_work g_bPsSensorOpen = %d,g_nPsSensorDate=%d\n",g_bPsSensorOpen,g_nPsSensorDate );
			if((g_bPsSensorOpen == 1) && (g_nPsSensorDate == 1))
			{
				mutex_lock(&msg2133_sensor_mutex);
				g_nPsSensorDate = 0;
				mutex_unlock(&msg2133_sensor_mutex);
			}
			return 0;
								
		}
		else if(TpdTouchData.disx_l == 0x40) // Open Panel
		{			
			printk(TPD_DEVICE"TP_PROXIMITY_SENSOR222 msg21xx_do_work g_bPsSensorOpen = %d,g_nPsSensorDate=%d\n",g_bPsSensorOpen,g_nPsSensorDate );
			if(/*(g_bPsSensorOpen == 1) && */(g_nPsSensorDate == 0))
			{
				mutex_lock(&msg2133_sensor_mutex);
				g_nPsSensorDate = 1;
				mutex_unlock(&msg2133_sensor_mutex);
			}
			return 0;
		}
		else
#endif
	
		if(TpdTouchData.x_h_y_h == 0xFF 
			&& TpdTouchData.x_l == 0xFF 
			&& TpdTouchData.y_l == 0xFF 
			&& TpdTouchData.disx_h_disy_h == 0xFF 
          )
        {
#ifdef TPD_HAVE_BUTTON
		 {
			U8 *p = &TpdTouchData;
			cinfo->key_value = 0;
			cinfo->key_value = *(p+5);			
			TPD_LOGV("p1: (%3d)\n",cinfo->key_value);
			cust_key_define = cinfo->key_value; //add by zhaofei 2012-07-09 09:42:45

			if(cust_key_define > 0)	// not release, key event 
			{
				if (FACTORY_BOOT == get_boot_mode()||RECOVERY_BOOT == get_boot_mode() )
				{   
					printk("cust_key_define is %d\n",cust_key_define);
					TPD_DMESG("222 cust_key_define is %d\n",cust_key_define);
					tpd_button_msg2133(cust_key_define);
					cinfo->count = 0;
				}
				else
				{
					cust_tpd_button_msg2133(cust_key_define, 1);
					// add by gpg for release;
					cinfo->count = 1;		
					return 0;
					// end by gpg
				}
				
			}
			else
			{
				cinfo->count = 0;
			}
			
		 }
#endif
			
			return 1; //add by zhaofei 2012-06-15 13:39:50 return from key event
        }
		else if(TpdTouchData.disx_h_disy_h == 0
			&& TpdTouchData.disx_l == 0 
			&& TpdTouchData.disy_l == 0)
			cinfo->count = 1;
		else
			cinfo->count = 2;
		
		TPD_LOGV("cinfo: count=%d\n",cinfo->count);
		if(cinfo->count > 0)
		{
			int tmp_x,tmp_y;
			/*point1*/
			cinfo->x1 = (((TpdTouchData.x_h_y_h&0xF0)<<4) | (TpdTouchData.x_l));
			cinfo->y1 = (((TpdTouchData.x_h_y_h&0x0F)<<8) | (TpdTouchData.y_l));

			if(cinfo->count >1)
			{	
				/*point2*/
				short disx,disy;
	
				disx = (((TpdTouchData.disx_h_disy_h&0xF0)<<4) | (TpdTouchData.disx_l));
				disy = (((TpdTouchData.disx_h_disy_h&0x0F)<<8) | (TpdTouchData.disy_l));
				disy = (disy<<4);
				disy = disy/16;
				if(disx >= 2048)
					disx -= 4096;
				if(disy >= 2048)
					disy -= 4096;
				cinfo->x2 = cinfo->x1 + disx;
				cinfo->y2 = cinfo->y1 + disy;				
			#ifdef LCT_MSG2133_SWAP_XY
				tmp_y= cinfo->x2;
				tmp_x = cinfo->y2;
			#else
				tmp_y= cinfo->y2;
				tmp_x = cinfo->x2;				
			#endif
				cinfo->y2 = tmp_y * (TPD_RES_Y - 1)/ 2047;
				//cinfo->x2 = TPD_RES_X - 1 - tmp_x * (TPD_RES_X - 1) / 2047;		
				cinfo->x2 =  tmp_x * (TPD_RES_X - 1) / 2047;		
			}
			#ifdef LCT_MSG2133_SWAP_XY
				tmp_y = cinfo->x1;
				tmp_x = cinfo->y1;
			#else
				tmp_y = cinfo->y1;
				tmp_x = cinfo->x1;
			#endif
			cinfo->y1 = tmp_y * (TPD_RES_Y - 1) / 2047;
//			cinfo->x1 = TPD_RES_X - 1 - tmp_x * (TPD_RES_X - 1) / 2047;
			cinfo->x1 =  tmp_x * (TPD_RES_X - 1) / 2047;
//#ifdef __FOR_TEST__ //add by zhaofei 2012-06-15 13:39:50
//			cinfo->x1 = 480-(cinfo->x1);
//#endif
			TPD_LOGV("p1: (%3d,%3d)(%3d,%3d)\n",cinfo->x1,cinfo->y1,TPD_RES_X,TPD_RES_Y);
	        cinfo->pressure = 1;
	        TPD_LOGV("pressure: %d\n",cinfo->pressure);
		}
	}
	else
	{
		cinfo->count = 0;
	}

    /*ergate-012 start*/
    /*ergate-012 end*/

	return 1;
}

static int touch_event_handler(void *unused)
{
	int pending = 0;
	struct TouchInfoT cinfo, pinfo;
	struct sched_param param = { .sched_priority = RTPM_PRIO_TPD };
	sched_setscheduler(current, SCHED_RR, &param);

    memset(&cinfo, 0, sizeof(struct TouchInfoT));
    memset(&pinfo, 0, sizeof(struct TouchInfoT));
	
	do
	{
		set_current_state(TASK_INTERRUPTIBLE); 
		if(!kthread_should_stop())
		{
			TPD_DEBUG_CHECK_NO_RESPONSE;
			do
			{
				if (pending) 
					wait_event_interruptible_timeout(waiter, tpd_flag != 0, HZ/10);
				else 
					wait_event_interruptible_timeout(waiter,tpd_flag != 0, HZ*2);
				 
			}while(0);
			 
			if (tpd_flag == 0 && !pending) 
				continue; // if timeout for no touch, then re-wait.
			 
			if (tpd_flag != 0 && pending > 0)	
				pending = 0;
			 
			tpd_flag = 0;
			TPD_DEBUG_SET_TIME; 
		}
		set_current_state(TASK_RUNNING);

		if (tpd_touchinfo(&cinfo, &pinfo))
		{
			if(cinfo.count >0)
			{
			    #if defined(HQ_PROJECT_A16)
			    pre_count =cinfo.count;
				pre_x1 =cinfo.x1;
			    pre_y1 =cinfo.y1;
				#endif

				tpd_down(cinfo.x1, cinfo.y1, cinfo.pressure);
				if(cinfo.count>1)
             	{
             	
                 #if defined(HQ_PROJECT_A16)
					pre_x2 =cinfo.x2;
					pre_y2 =cinfo.y2;
				 #endif	
					tpd_down(cinfo.x2, cinfo.y2, cinfo.pressure);
				}
				input_sync(tpd->dev);
	#if defined(HQ_PROJECT_A18)
				/*ergate-037 start*/
				if(state_down == 0)
				{
					x_down = cinfo.x1;
					y_down = cinfo.y1;
					do_gettimeofday(&time_down);
				}
				if(state_down == 1)
				{
					x_up = cinfo.x1;
					y_up = cinfo.y1;
					do_gettimeofday(&time_up);
				}
				state_down = 1;
				/*ergate-037 end*/
	#endif				
				TPD_LOGV("press  --->\n");
			}
			else if(cinfo.count==0 && pinfo.count!=0)
			{
			
             #if defined(HQ_PROJECT_A16)
				tpd_up(pre_x1, pre_y1, cinfo.pressure);
				if(pre_count > 1)
				{
					tpd_up(pre_x2, pre_y2, cinfo.pressure);
				}				
				input_sync(tpd->dev);
			 #else
			 input_mt_sync(tpd->dev);
			 input_sync(tpd->dev);
			 #endif
	#if defined(HQ_PROJECT_A18)
				/*ergate-037*/
				state_down = 0;
	#endif
				TPD_LOGV("release --->\n"); 
			}
		}		   
	}while(!kthread_should_stop());

	return 0;
}

 
static int tpd_detect (struct i2c_client *client, int kind, struct i2c_board_info *info) 
{
	strcpy(info->type, TPD_DEVICE);
	return 0;
}

 
static void tpd_eint_interrupt_handler(void)
{
	TPD_LOGV("TPD interrupt has been triggered\n");
	tpd_flag = 1;
	wake_up_interruptible(&waiter);
}

#if LCT_ADD_TP_VERSION
#define CTP_PROC_FILE "ctp_version"
static struct proc_dir_entry *g_ctp_proc = NULL;
static int g_major = 0;
static int g_minor = 0;

static int ctp_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{

	int cnt= 0;
	printk("Enter ctp_proc_read.\n");
	if(off != 0)
		return 0;
	cnt = sprintf(page, "vid:0x%04x,firmware:0x%04x\n",g_major, g_minor);
	
	*eof = 1;
	printk("vid:0x%04x,firmware:0x%04x\n",g_major, g_minor);
	printk("Leave ctp_proc_read. cnt = %d\n", cnt);
	return cnt;
}
#endif

static int __devinit tpd_probe(struct i2c_client *client, const struct i2c_device_id *id)
{	 
	int error;
	int retval = TPD_OK;

	i2c_client = client;

    /*ergate-dbg*/
    i2c_client->addr |= I2C_ENEXT_FLAG; //I2C_HS_FLAG;
	i2c_client->timing = 100;

	extern int tpd_load_status;

	/*ergate-016 start*/

#ifdef MT6575
	//power on, need confirm with SA
	//hwPowerOn(MT65XX_POWER_LDO_VGP2, VOL_2800, "TP");
#endif
#if 0 //gpg
	printk("probe tpd_probe msg2133");	
	mt_set_gpio_mode(GPIO_CTP_EN_PIN, GPIO_CTP_EN_PIN_M_GPIO);
  	mt_set_gpio_dir(GPIO_CTP_EN_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_CTP_EN_PIN, GPIO_OUT_ONE);
#endif
    msleep(50);  

   // set deep sleep off
    mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
    mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
    mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);  

    msleep(10);  
   // set deep sleep off
    mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
    mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
    mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);  
    msleep(10);  
	
	//eint
	GPIO_CAPTOUCH_EINT_PIN = GPIO75;
	GPIO_CAPTOUCH_EINT_PIN_M_EINT = GPIO_MODE_01;
	CUST_EINT_TOUCH_PANEL_NUM = 6;

	/*ergate-016 end*/ 
	error = tpd_initialize(client);
	if(error)
	{
		TPD_LOGI("tpd_initialize error\n");
		tpd_load_status = 0;
		return -1;
	}

    /*ergate-009*/
    //tpd_create_attr(&driver_attr_calibrate);
    /*ergate-026*/
    //tpd_create_attr(&driver_attr_loglevel);
 
#ifdef CONFIG_HAS_EARLYSUSPEND
	if(!(retval < TPD_OK)) 
	{
		early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1;
		early_suspend.suspend = tpd_early_suspend;
		early_suspend.resume = tpd_late_resume;
		register_early_suspend(&early_suspend);
	}
#endif

	/*ergate-001*/
	/*skip wrong EINT during init*/
	//msleep(500);  

	thread = kthread_run(touch_event_handler, 0, TPD_DEVICE);
	if(IS_ERR(thread))
	{ 
		TPD_DMESG(TPD_DEVICE " failed to create kernel thread\n");
	}

	mt65xx_eint_set_sens(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_SENSITIVE);
	mt65xx_eint_set_hw_debounce(CUST_EINT_TOUCH_PANEL_NUM, 1);
	mt65xx_eint_registration(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_DEBOUNCE_EN, CUST_EINT_POLARITY_HIGH, tpd_eint_interrupt_handler, 1); 
	mt65xx_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM);
 
	TPD_DMESG("Touch Panel Device Probe %s\n", (retval < TPD_OK) ? "FAIL" : "PASS");

	tpd_load_status = 1;

	/*FW UPDATE*/
    /* set sysfs for frimware */
    firmware_class = class_create(THIS_MODULE, "ms-touchscreen-msg20xx");
    if (IS_ERR(firmware_class))
        pr_err("Failed to create class(firmware)!\n");

    firmware_cmd_dev = device_create(firmware_class,
                                     NULL, 0, NULL, "device");
    if (IS_ERR(firmware_cmd_dev))
        pr_err("Failed to create device(firmware_cmd_dev)!\n");

    // version
    if (device_create_file(firmware_cmd_dev, &dev_attr_version) < 0)
        pr_err("Failed to create device file(%s)!\n", dev_attr_version.attr.name);
    // update
    if (device_create_file(firmware_cmd_dev, &dev_attr_update) < 0)
        pr_err("Failed to create device file(%s)!\n", dev_attr_update.attr.name);
    // data
    if (device_create_file(firmware_cmd_dev, &dev_attr_data) < 0)
        pr_err("Failed to create device file(%s)!\n", dev_attr_data.attr.name);

    dev_set_drvdata(firmware_cmd_dev, NULL);

#if LCT_ADD_TP_VERSION

	// get fw version
		unsigned char dbbus_tx_data[3];
		unsigned char dbbus_rx_data[4] ;
		unsigned short major=0, minor=0;
	
	//	Get_Chip_Version();
		dbbus_tx_data[0] = 0x53;
		dbbus_tx_data[1] = 0x00;
		dbbus_tx_data[2] = 0x74;
		HalTscrCDevWriteI2CSeq(0x4C, &dbbus_tx_data[0], 3);
		HalTscrCReadI2CSeq(0x4C, &dbbus_rx_data[0], 4);
		g_major = (dbbus_rx_data[1]<<8)+dbbus_rx_data[0];
		g_minor = (dbbus_rx_data[3]<<8)+dbbus_rx_data[2];
	// end get fw

		g_ctp_proc = create_proc_entry(CTP_PROC_FILE, 0444, NULL);
		if (g_ctp_proc == NULL) {
			printk("create_proc_entry failed\n");
		} else {
			g_ctp_proc->read_proc = ctp_proc_read;
			g_ctp_proc->write_proc = NULL;
			//g_ctp_proc->owner = THIS_MODULE;
			printk("create_proc_entry success\n");
		}
#endif

#ifdef LCT_DRV_PSSENSOR_USE_TP
	tpd_initialize_ps_sensor_function();
#endif

	return 0;	  
}
 

static int tpd_power_on ()
{
	int retval = TPD_OK;
	int tries = 0;
	u8 host_reg;
   
	TPD_LOGI("Power on\n");
#if 0 //gpg
	mt_set_gpio_mode(GPIO_CTP_EN_PIN, GPIO_CTP_EN_PIN_M_GPIO);
  	mt_set_gpio_dir(GPIO_CTP_EN_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_CTP_EN_PIN, GPIO_OUT_ONE);
#endif
	/*ergate-001 start*/
//	tpd_hw_power(0);
	tpd_hw_power(1);
	tpd_hw_enable(1);
    tpd_hw_config_eint_pin(2);
	/*ergate-001 end*/
 
	return retval;
}
static int tpd_initialize(struct i2c_client * client)
{
	int retval = TPD_OK;
    struct TpdPacketT packet = 
    {
        TPD_PACKET_HEAD_CMD,
        TPD_PACKET_CMD_FORMAT_WRITE,
        0x00,
        0x00
    };
    struct TpdPacketT pr;
    char buf[4];
    buf[0] = 0x53;
    buf[1] = (0x74>>8)&0xFF;        
    buf[2] = (0x74)&0xFF;   

    memset(&tpd_firmware_version,0, sizeof(tpd_firmware_version));
	retval = tpd_power_on();
	
	msleep(200);
	retval = i2c_master_send(i2c_client, buf, 3);
	retval = i2c_master_recv(i2c_client, buf, 4);
	tpd_firmware_version[0]=buf[0];
	tpd_firmware_version[1]=buf[1];
	printk("msg2133+++,tpd_initialize:0x%02x,0x%02x\n",buf[0],buf[1]);
	

	if(retval > TPD_OK)
		TPD_LOGI("Firmware Version:0x%02x,0x%02x\n",buf[0],buf[1]);
	else
		TPD_LOGI("Firmware Version:error\n");

	if(retval > TPD_OK)
		retval = TPD_OK;
	return retval;
}


static int __devexit tpd_remove(struct i2c_client *client) 
{
	int error;
 
  #ifdef CONFIG_HAS_EARLYSUSPEND
	 unregister_early_suspend(&early_suspend);
  #endif /* CONFIG_HAS_EARLYSUSPEND */
   
	TPD_LOGI("TPD removed\n");
 
	return 0;
}
 
 
static int tpd_local_init(void)
{
	int retval;
 
	TPD_DMESG("msg2133 I2C Touchscreen Driver (Built %s @ %s)\n", __DATE__, __TIME__);
 
	retval = i2c_add_driver(&tpd_driver);

    /*ergate-012*/
#ifdef TPD_HAVE_BUTTON     
    tpd_button_setting(TPD_KEY_COUNT, tpd_keys_local, tpd_keys_dim_local);// initialize tpd button data
#endif 

    /*ergate-001*/
	tpd_type_cap = 1;
	return 0; 
}

static int tpd_resume(struct i2c_client *client)
{
	int retval = TPD_OK;

#ifdef LCT_DRV_PSSENSOR_USE_TP
	if(g_bPsSensorOpen == 0 && (!g_bSuspend))
	{
		TPD_LOGI("msg sensor resume in calling tp no need to resume\n");
		return 0;
	}
	g_bSuspend = 0;
#endif
	
#if 1//!defined(HQ_PROJECT_A16)
	TPD_LOGI("TPD wake up\n");
	/*ergate-001*/
	tpd_hw_power(1);
	//tpd_initialize(i2c_client);
	msleep(1);
	tpd_hw_enable(1);
    //tpd_hw_config_eint_pin(2);
	msleep(200);
	
	/*wait for CTP stablity like init*/
	//msleep(500);
	/*match with tpd_suspend()*/
	mt65xx_eint_registration(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_DEBOUNCE_EN, CUST_EINT_TOUCH_PANEL_POLARITY, tpd_eint_interrupt_handler,1);
	mt65xx_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM);  
#endif
	return retval;
}

 
static int tpd_suspend(struct i2c_client *client, pm_message_t message)
{
	int retval = TPD_OK;

#ifdef LCT_DRV_PSSENSOR_USE_TP
	if(g_nPsSensorDate == 0)
	{
		TPD_LOGI("msg suspend in calling tp no need to suspend\n");
		return 0;
	}
	g_bSuspend = 1;
#endif

	TPD_LOGI("TPD enter sleep\n");
	mt65xx_eint_mask(CUST_EINT_TOUCH_PANEL_NUM);
	/*mt65xx_eint_mask cann't stop EINT, so doing following*/
	mt65xx_eint_registration(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_DEBOUNCE_EN, CUST_EINT_TOUCH_PANEL_POLARITY, 			NULL, 1);
	/*ergate-001*/
    tpd_hw_enable(0);
    msleep(10);
    tpd_hw_power(0);

    return retval;
}

void tpd_uniform_ctp(char *buf,int strlen)
{
    int retval = TPD_OK;
    char result = buf[strlen-1] + 1;
    int i = 0;


    for(i = 0;i < 5 && (result != buf[strlen-1]);i++)
    {
        i2c_client->addr = 0xc4 | I2C_ENEXT_FLAG;
        retval = i2c_master_send(i2c_client, buf, strlen);
        udelay(100);
        retval = i2c_master_send(i2c_client, buf, strlen-1);
        i2c_client->addr = 0xc5 | I2C_ENEXT_FLAG;
        retval = i2c_master_recv(i2c_client, &result, 1);
    }
}

#ifdef LCT_DRV_PSSENSOR_USE_TP
static int msg2133_enable_ps(int enable)
{
	u8 ps_store_data[4];

	mutex_lock(&msg2133_sensor_mutex);

	printk("msg2133 do enable: %d, current state: %d\n", enable, g_bPsSensorOpen);
	if(enable == 1)
	{
		if(g_bPsSensorOpen == 0)
		{
			ps_store_data[0] = 0x52;
			ps_store_data[1] = 0x00;
			ps_store_data[2] = 0x62;
			ps_store_data[3] = 0xa0;		
			printk("msg2133 do enable: %d, current state: %d\n", enable, g_bPsSensorOpen);
			HalTscrCDevWriteI2CSeq(0x4C, &ps_store_data[0], 4);
			g_bPsSensorOpen = 1;
		}
	}
	else
	{	
		if(g_bPsSensorOpen == 1)
		{
			ps_store_data[0] = 0x52;
			ps_store_data[1] = 0x00;
			ps_store_data[2] = 0x62;
			ps_store_data[3] = 0xa1;
			HalTscrCDevWriteI2CSeq(0x4C, &ps_store_data[0], 4);	
			g_bPsSensorOpen = 0;			
		}
		g_nPsSensorDate = 1;
	}
	mutex_unlock(&msg2133_sensor_mutex);
	return 0;
}

int msg2133_ps_operate(void* self, uint32_t command, void* buff_in, int size_in,
		void* buff_out, int size_out, int* actualout)
{
	int err = 0;
	int value;
	hwm_sensor_data* sensor_data;

	//APS_FUN(f);
	switch (command)
	{
		case SENSOR_DELAY:
			if((buff_in == NULL) || (size_in < sizeof(int)))
			{
				APS_ERR("Set delay parameter error!\n");
				err = -EINVAL;
			}
			// Do nothing
			break;

		case SENSOR_ENABLE:
			if((buff_in == NULL) || (size_in < sizeof(int)))
			{
				APS_ERR("Enable sensor parameter error!\n");
				err = -EINVAL;
			}
			else
			{				
				value = *(int *)buff_in;
				if(value)
				{
					printk("msg2133_ps_operate++++++++1\n");
					wake_lock(&ps_lock);		//wujinyou
					if(err = msg2133_enable_ps(1))
					{
						APS_ERR("enable ps fail: %d\n", err); 
						return -1;
					}
					g_bPsSensorOpen = 1;
				}
				else
				{
					printk("msg2133_ps_operate++++++++0\n");
					wake_unlock(&ps_lock);		//wujinyou
					if(err = msg2133_enable_ps(0))
					{
						APS_ERR("disable ps fail: %d\n", err); 
						return -1;
					}
					g_bPsSensorOpen = 0;
				}
			}
			break;

		case SENSOR_GET_DATA:
			printk("msg2133_ps get date: %d\n", g_nPsSensorDate);
			if((buff_out == NULL) || (size_out< sizeof(hwm_sensor_data)))
			{
				APS_ERR("get sensor data parameter error!\n");
				err = -EINVAL;
			}
			else
			{
				sensor_data = (hwm_sensor_data *)buff_out;	
				sensor_data->values[0] = g_nPsSensorDate;
				sensor_data->value_divide = 1;
				sensor_data->status = SENSOR_STATUS_ACCURACY_MEDIUM;			
			}
			break;
		default:
			APS_ERR("proxmy sensor operate function no this parameter %d!\n", command);
			err = -1;
			break;
	}
	
	return err;
}


static void tpd_initialize_ps_sensor_function()
{
	struct hwmsen_object obj_ps = {0};
	int err = 0;
	
	g_nPsSensorDate = 1;

	obj_ps.self = NULL;	// no use
	obj_ps.polling = 1;
	obj_ps.sensor_operate = msg2133_ps_operate;

	wake_lock_init(&ps_lock,WAKE_LOCK_SUSPEND,"ps wakelock"); //shaohui add
		
	if(err = hwmsen_attach(ID_PROXIMITY, &obj_ps))
	{
		TPD_LOGI("attach fail = %d\n", err);
		return;
	}
}
#endif


#ifdef CONFIG_HAS_EARLYSUSPEND
static void tpd_early_suspend(struct early_suspend *handler)
{
	//tpd_suspend(i2c_client, PMSG_SUSPEND);	
}


static void tpd_late_resume(struct early_suspend *handler)
{
	//tpd_resume(i2c_client);
}
#endif
 

static struct tpd_driver_t tpd_device_driver = 
{
		.tpd_device_name = TPD_DEVICE,
		.tpd_local_init = tpd_local_init,
		.suspend = tpd_suspend,
#if 0//defined(HQ_PROJECT_A18) || defined(HQ_PROJECT_A16)
		.resume = NULL,
#else
		.resume = tpd_resume,
#endif
#ifdef TPD_HAVE_BUTTON
		.tpd_have_button = 1,
#else
		.tpd_have_button = 0,
#endif		
};


/* called when loaded into kernel */
static int __init tpd_driver_init(void)
{
	TPD_DMESG("msg2133 touch panel driver init\n");
	if(tpd_driver_add(&tpd_device_driver) < 0)
		TPD_DMESG("add tpd driver failed\n");
	return 0;
}


/* should never be called */
static void __exit tpd_driver_exit(void)
{
	TPD_DMESG("MediaTek msg2133 touch panel driver exit\n");
	//input_unregister_device(tpd->dev);
	tpd_driver_remove(&tpd_device_driver);
}


module_init(tpd_driver_init);
module_exit(tpd_driver_exit);
