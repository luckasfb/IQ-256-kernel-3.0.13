#ifndef TOUCHPANEL_H  
#define TOUCHPANEL_H  
  
// LuckAs add VGP2
//#define TPD_POWER_SOURCE         MT6575_POWER_VGP2
//#define TPD_POWER_SOURCE       MT65XX_POWER_LDO_VGP2 // 2800
//#define TPD_POWER_SOURCE_CUSTOM       MT65XX_POWER_LDO_VGP // 1800

#define TPD_RES_X                320  
#define TPD_RES_Y                480  
  
// LuckAs 
// try buttons
//#define TPD_HAVE_BUTTON
// orig
//#define TPD_HAVE_BUTTON
  
  
// LuckAs disable
//#define TPD_BUTTON_HEIGHT       480
//#define TPD_KEY_COUNT           3
//#define TPD_KEYS                {KEY_MENU, KEY_HOME, KEY_BACK}  
// try now
//#define TPD_KEYS_DIM            {{40,508,80,38},{140,508,80,38},{240,508,80,38}}
// 
//#define TPD_KEYS_DIM            {{40,522,80,38},{140,522,80,38},{240,522,80,38}}
// not have buttons
//#define TPD_KEYS_DIM            {{20,508,80,38},{120,508,80,38},{230,508,80,38}}  
//
//#define TPD_KEYS_DIM            {{20,500,60,50},{120,500,100,50},{240,500,60,50}}  
// not work
//#define TPD_KEYS_DIM            {{20,576,80,50},{120,576,80,50},{220,576,80,50}}  
// orig not worked
//#define TPD_KEYS_DIM            {{40,505,80,50},{120,505,80,50},{200,505,80,50}}  
  
#endif
// LuckAs add for errors
#define REPORT_PACKET_LENGTH 8
#define MS_TS_MSG21XX_X_MAX 320
// try
#define MS_TS_MSG21XX_Y_MAX 480
// 15mm
//#define MS_TS_MSG21XX_Y_MAX 600
// not have
//#define MS_TS_MSG21XX_Y_MAX 485
// 15mm
//#define MS_TS_MSG21XX_Y_MAX 546
// more
//#define MS_TS_MSG21XX_Y_MAX 560
// orig my
//#define MS_TS_MSG21XX_Y_MAX 480
#define MAX_TOUCH_FINGER 2

