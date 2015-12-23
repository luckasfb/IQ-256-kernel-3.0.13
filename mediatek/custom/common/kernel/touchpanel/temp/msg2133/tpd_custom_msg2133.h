#ifndef TOUCHPANEL_H  
#define TOUCHPANEL_H  
  
// LuckAs add VGP2
//#define TPD_POWER_SOURCE         MT6575_POWER_VGP2
//#define TPD_POWER_SOURCE       MT65XX_POWER_LDO_VGP2 // 2800
//#define TPD_POWER_SOURCE_CUSTOM       MT65XX_POWER_LDO_VGP // 1800

#define TPD_RES_X                320  
#define TPD_RES_Y                480  
  
#define TPD_HAVE_BUTTON  
  
  
#define TPD_BUTTON_HEIGHT   480  
#define TPD_KEY_COUNT           3  
#define TPD_KEYS                {KEY_MENU, KEY_HOME, KEY_BACK}  
#define TPD_KEYS_DIM            {{40,505,80,50},{120,505,80,50},{200,505,80,50}}  
  
#endif
// LuckAs add for errors
#define REPORT_PACKET_LENGTH 8
#define MS_TS_MSG21XX_X_MAX 320
#define MS_TS_MSG21XX_Y_MAX 480
#define MAX_TOUCH_FINGER 2

