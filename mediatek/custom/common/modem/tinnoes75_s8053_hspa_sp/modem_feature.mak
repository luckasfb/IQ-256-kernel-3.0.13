MODEM_SIM_RECOVERY_ENHANCEMENT = FALSE     # TRUE : Enable this feature
MODEM_RVCT_VERSION      =  V31       # NONE, V22, V31
MODEM_RVCT_PARTIAL_LINK = FALSE    # TRUE :  Always do partial link in linking process
MODEM_CUSTOM_CFLAGS = #--debug --no_debug_macros         # custom flag
MODEM_FEATURE_OVERLOAD = FALSE  # TRUE, FALSE
MODEM_ACCDET_SUPPORT		= FALSE   # TRUE or FALSE
MODEM_BOARD_VER         = TINNOES75_NAND_BB # Baseband main board description, SHOULD BE ONE OF THE FOLLOWINGS
MODEM_SUB_BOARD_VER     =  PCB01       # MT6218_MW001 Baseband main board subversion, SHOULD BE ONE OF THE FOLLOWINGS
MODEM_CHIP_VERSION_CHECK    = TRUE       #  TRUE, FALSE
MODEM_RF_MODULE         =  MT6162_CUSTOM      # SKY74045, AERO, FOUNTAIN2, SPRING,
MODEM_PHONE_TYPE 		=  BAR      # BAR, CLAMSHELL, SLIDE
MODEM_VENDOR = NONE     # NONE: non-vendor project
MODEM_LCD_MODULE        = TINNOES75_NAND_LCM  # Based on the LCM solutions (even multiple LCM modules for this project)
MODEM_DISPLAY_TYPE        = COLOR      # BW, COLOR
MODEM_MAIN_LCD_SIZE = 240X320                               # To distinguish the main lcd size.
MODEM_MAIN_LCM_PHYSICAL_SIZE = BY_LCD_SIZE_SETTING    # NONE: No main LCM is attached
MODEM_MAIN_MEDIA_LAYER_BITS_PER_PIXEL = DEFAULT  # DEFAULT, 24
MODEM_SUB_LCD_SIZE = NONE    # NONE, 128X128
MODEM_SUB_LCM_PHYSICAL_SIZE = BY_LCD_SIZE_SETTING    # NONE: No main LCM is attached
MODEM_LCM_ROTATE_SUPPORT   = FALSE     # TRUE, FALSE
MODEM_TOUCH_PANEL_SUPPORT = NONE    # NONE,MT6301,MT6301B,TP_INTERNAL,CTP_IT_7250,CTP_CYPRESS_TMA340
MODEM_TOUCH_PANEL_SHORTCUT_SUPPORT   = FALSE         # FALSE, TRUE
MODEM_MMI_VERSION 		= 	EMPTY_MMI  	# FCB_MMI, PLUTO_MMI, BW_MMI, EMPTY_MMI, CHICAGO_MMI, KLM_MMI
MODEM_VENUS_MMI = NONE   # NONE, VENUS_LEVEL1
MODEM_FINGER_TOUCH_SUPPORT = NONE    #  NONE, FTE
MODEM_REDUCE_PLUTO_HEADER_DEPTH = FALSE    # TRUE, FALSE
MODEM_HAND_WRITING 		= 	NONE   	# NONE, MMI_HANWANG, MMI_PENPOWER, MMI_PENPOWER_DEMO, MMI_HANWANG_DEMO, MMI_DECUMA, MMI_DECUMA_DEMO
MODEM_INPUT_METHOD 		= 	NONE        	 # Input methods: NONE, MMI_T9, MMI_ZI, MMI_T9_V7, MMI_T9_V7_4
MODEM_KEYPAD_TYPE             = NORMAL_KEYPAD  # NORMAL_KEYPAD, REDUCED_KEYPAD, QWERTY_KEYPAD
MODEM_BACKGROUND_CALL_SUPPORT = FALSE  # TRUE, FALSE
MODEM_MMS_FEATURES = NONE  # NONE, SLIM, FULL
MODEM_MMS_SUPPORT =  NONE  # OBIGO_Q05A, OBIGO_Q03C_MMS_V01, OBIGO_Q03C_MMS_V02, NONE
MODEM_DA_MEMORY_CUT_SUPPORT = FALSE    # TRUE, FALSE
MODEM_DOWNLOADABLE_THEME = FALSE  # TRUE, FALSE
MODEM_DLT_ALWAYS_LOAD_BUFFER_SIZE = 0
MODEM_DLT_LOAD_ON_DEMAND_BUFFER_SIZE = 0
MODEM_EMAIL_SUPPORT           =  NONE   # NONE or  SMTP_POP3 or ALL
MODEM_PUSH_MAIL = NONE    # FLYFOT: turn on this feature and with flyfot 139 solution
MODEM_WCDMA_PREFERRED = TRUE     #
MODEM_SIM_HOT_SWAP = NONE     #
MODEM_GEMINI = 2    # FALSE, 2, 3, 4
MODEM_SENDKEY_MODE = SINGLE_KEY_SELECT_MENU # SINGLE_KEY_SELECT_MENU   SENDKEY2_SUPPORT
MODEM_IMPS_SUPPORT            =  FALSE  # TRUE or FALSE, IMPS Feature Support
MODEM_PHB_LN_ENTRY	=	10	# Call log; Last Number Entry Number: 10, 20, 50
MODEM_PHB_PHONE_ENTRY	=	10	# Phonebook Entry Number in NVRAM: 100, 200
MODEM_PHB_SIM_ENTRY = 1000     # Phonebook Entry Number in SIM: 100, 200
MODEM_PHB_SYNC = ON
MODEM_SIM_PROVISIONING = MMSICP  # NONE, MMSICP
MODEM_SMS_PHONE_ENTRY = 10  # SMS Entry Number in NVRAM: 450
MODEM_SMS_SIM_ENTRY = 50
MODEM_SMS_TOTAL_ENTRY = 500  # SMS Entry Number in NVRAM and SIM(reserve 50): 500 (>=SMS_PHONE_ENTRY)
MODEM_BACKGROUND_SMS_SUPPORT = FALSE		     # TRUE or FALSE
MODEM_MSG_SMS_EMAIL_SUPPORT = FALSE  # TRUE, FALSE
MODEM_QOS_PROFILE_SUPPORT = ALL  # NONE, STATIC, DYNAMIC, ALL
MODEM_UNIFIED_MESSAGE_ADVANCE_FEATURE  = NONE  	# Unified message advance feture:
MODEM_UNIFIED_MESSAGE_FOLDER = FALSE   # TRUE or FALSE, To support unified message folder of multiple message types
MODEM_UNIFIED_MESSAGE_MARK_SEVERAL_FEATURE = FALSE  # TRUE, FALSE
MODEM_UNIFIED_MESSAGE_SIMBOX_SUPPORT = FALSE  # TRUE, FALSE
MODEM_UNIFIED_MESSAGE_SORT_MESSAGE_LIST = FALSE  # TRUE, FALSE
MODEM_WBXML_SUPPORT   = FALSE		# TRUE or FALSE
MODEM_XML_SUPPORT             = FALSE    # TRUE or FALSE
MODEM_BLUETOOTH_SUPPORT = NONE    # NONE, BTMTK, BTMTK_MT6601, BTMTK_MT6611, BTMTK_MT6612, BTMTK_MT6236, BTMTK_MT6616, BTMTK_MT6622, BTMTK_MT6626, BTMTK_MT6612_22_26
MODEM_BT_BPP_PROFILE = FALSE  # TRUE, FALSE
MODEM_BT_DUN_PROFILE       = FALSE      # TRUE, FALSE
MODEM_UDX_SUPPORT = FALSE    # TRUE, FALSE
MODEM_BT_FTC_PROFILE       = FALSE      # TRUE, FALSE
MODEM_BT_FTS_PROFILE       = FALSE      # TRUE, FALSE
MODEM_BT_HFG_PROFILE       = FALSE      # TRUE, FALSE
MODEM_BT_HIDD_PROFILE = FALSE  # TRUE, FALSE
MODEM_BT_OPP_PROFILE       = FALSE      # TRUE, FALSE
MODEM_BT_PBAP_PROFILE = FALSE
MODEM_SMS_R8_TABLE_MECHANISM = SMS_R8_DEFAULT   #SMS_R8_DEFAULT or SMS_R8_LOCKING or SMS_R8_SINGLE or SMS_R8_BOTH or SMS_R8_AUTO
MODEM_BT_SPP_PROFILE       = FALSE     # TRUE, FALSE
MODEM_GPS_UART_PORT = UART3
MODEM_USB_HS_SUPPORT = FALSE  # TRUE, FALSE
MODEM_USB_MULTIPLE_COMPORT_ENABLE = FALSE  # TRUE/FALSE. To enable USB multiple com port feature
MODEM_USB_HIGH_SPEED_COM_PORT_SUPPORT  =  FALSE     #TRUE : Enable USB high speed com port interface
MODEM_USB_IN_NORMAL_MODE_SUPPORT =  FALSE  # TRUE,FALSE
MODEM_USB_MASS_STORAGE_SUPPORT = FALSE  # TRUE, FALSE
MODEM_USB_DOWNLOAD_IN_BL = NONE    # Support USB Download in bootloader or not.
MODEM_USB_MULTI_CHARGE_CURRENT_SUPPORT = FALSE  # TRUE, FALSE
MODEM_EXTERNAL_ACCESSORY_DETECTION = NONE        # NONE, MAX14526, TS5USBA33402
MODEM_EXTERNAL_CHARGER_DETECTION   = NONE        # NONE, MAX14526, TS5USBA33402
MODEM_GENERAL_EXTERNAL_CHARGER = NONE    # NONE, BQ25040, RT9505_BQ24020, ISL9221
MODEM_MTP_SUPPORT = FALSE  # TRUE : enable MTP protocol feature
MODEM_IRDA_SUPPORT      =  FALSE       # IRDA support feature
MODEM_FLASHLIGHT_TYPE         = NONE           # NONE, LED_ONOFF_SUPPORT, LED_FLASHLIGHT_SUPPORT
MODEM_AUDIO_CLIPPER_SUPPORT = FALSE    # TRUE: If on, MMI could use the audio clipper to clip part of mp3 as ringtone.
MODEM_CONTOUR_IMPROVEMENT_SUPPORT = FALSE
MODEM_INTERGRAFX_SUPPORT = NONE    # NONE: disable  intergrafx wallpaper and game
MODEM_MELODY_BUFFER_LEN = 20480  # 102400, 307200, 20480, 1300, 1024, 512
MODEM_EXT_DAC_SUPPORT      = FALSE     # TRUE, FALSE
MODEM_GAIN_TABLE_SUPPORT = FALSE
MODEM_PGDL_SUPPORT  =  FALSE          # TRUE or FALSE
MODEM_MJPG_DECODE = FALSE    # TRUE/FALSE
MODEM_MJPG_ENCODE = FALSE    # TRUE/FALSE
MODEM_RM_DECODE  = FALSE  # TRUE, FALSE
MODEM_RM_DECODE_MODE = NORMAL    # SLIM, NORMAL
MODEM_STREAM_SUPPORT   =   FALSE   # TRUE or FALSE
MODEM_AF_AUXI_LED_SUPPORT = FALSE    # TRUE, FALSE
MODEM_AF_SUPPORT           = FALSE	  # TRUE/FALSE
MODEM_BACKUP_SENSOR_SUPPORT = FALSE  # TRUE, FALSE
MODEM_CAMCORDER_SUPPORT = NONE  # NONE, FULL, SLIM, STANDARD, CUSTOM
MODEM_CAMCORDER_FACE_DETECTION_MODE_SUPPORT = FALSE  # TRUE, FALSE
MODEM_CAMCORDER_SMILE_SHUTTER_MODE_SUPPORT = FALSE
MODEM_DUAL_CAMERA_SUPPORT = FALSE  # TRUE: enable dual camera support
MODEM_CMOS_SENSOR 		= NONE	# MT9D011,
MODEM_CMOS_SENSOR_BAK1 = NONE        # NONE: not support backup sensor feature in main camera
MODEM_SENSOR_TYPE = NONE    # RAW, YUV, DIRECT, NONE
MODEM_CMOS_SENSOR_SUB = NONE       # NONE: no sub camera sensor module
MODEM_CMOS_SENSOR_SUB_BAK1 = NONE    # NONE: not support backup sensor feature in sub camera
MODEM_SENSOR_SUB_ROTATE = SENSOR_ROTATE_0
MODEM_SENSOR_TYPE_SUB = NONE       # RAW: raw type sub camera sensor module
MODEM_CAPTURE_SCENARIO = OFFLINE
MODEM_HORIZONTAL_CAMERA = FALSE       # FALSE, TRUE
MODEM_LENS_MODULE = NONE  # NONE, ABICO_VQ26A10_OV2640_AD5398, ABICO_WZ36A333_OV3640_MD118B, ACME_900_0043_00_OV3640_AD5398,
MODEM_LENS_MODULE_BAK1 = NONE        # NONE:  not support AF lens backup sensor feature in main camera
MODEM_PANORAMA_VIEW_SUPPORT = FALSE  # TRUE, FALSE
MODEM_WEBCAM_SUPPORT       = FALSE      # TRUE, FALSE for WEB CAMERA support
MODEM_YUVCAM_ENCODE_DIRECT_WRITE_FILE = FALSE  # TRUE, FALSE
MODEM_YUVCAM_INTERPOLATION = NONE    # NONE, HW, SW
MODEM_GDI_BLT_WITH_DOUBLE_BUF_SUPPORT = FALSE
MODEM_GDI_SCREEN_SHOT_BUFFER = ON
MODEM_GIF_DECODE = FALSE    # TRUE:  turn on hw and sw gif decoder
MODEM_SCALADO_SUPPORT = FALSE    # TRUE,FALSE
MODEM_SECURE_VERSION      = 1          #
MODEM_SECURE_CUSTOM_NAME  = MTK        # MTK (6227C/6225 EVB) or JRD (JRD_06A)
MODEM_SECURE_JTAG_ENABLE = TRUE    #
MODEM_BIP_SCWS_SUPPORT = FALSE  # TRUE, FALSE
MODEM_ECC_RETRY_ENHANCEMENT = TRUE
MODEM_GPRS_MAX_PDP_SUPPORT = 6     # 1, 2, 3, 4, 5, 6 or 7  Maximum simultaneous PDP contexts (1~7)
MODEM_RSAT_SUPPORT = MODEM_WITH_RSAT  # NONE, MODEM_WITH_RSAT, MMI_WITH_RSAT
MODEM_UMTS_BAND_I    = TRUE  # TRUE, FALSE
MODEM_UMTS_BAND_II   = TRUE  # TRUE, FALSE
MODEM_UMTS_BAND_III  = FALSE  # TRUE, FALSE
MODEM_UMTS_BAND_IV   = FALSE  # TRUE, FALSE
MODEM_UMTS_BAND_V    = TRUE  # TRUE, FALSE
MODEM_UMTS_BAND_VI   = FALSE  # TRUE, FALSE
MODEM_UMTS_BAND_VII  = FALSE  # TRUE, FALSE
MODEM_UMTS_BAND_VIII = TRUE  # TRUE, FALSE
MODEM_UMTS_BAND_IX   = FALSE  # TRUE, FALSE
MODEM_UMTS_BAND_X    = FALSE  # TRUE, FALSE
MODEM_KAL_TRACE_OUTPUT = FULL    # FULL: Default, Enable Trace Output
MODEM_PARTIAL_TRACE_LIB = NONE    # NONE
MODEM_KAL_RECORD_BOOTUP_LOG = FALSE
MODEM_DRV_DEBUG_MEMORY_TRACE_SUPPORT = TRUE  # TRUE, FALSE
MODEM_MULTIPLE_BINARY_FILES = FALSE  # FALSE, TRUE
MODEM_ZIMAGE_SUPPORT = FALSE    # TRUE, FALSE
MODEM_NAND_FLASH_BOOTING   = NONE        # Indicate if this project ROM binary shadow from NAND Flash and inherit mechanisms.
MODEM_NOR_SUPPORT_RAW_DISK = FALSE
MODEM_OTP_SUPPORT         = FALSE      # TRUE, FALSE
MODEM_COMBO_MEMORY_SUPPORT = FALSE    # TRUE :  Enable Combo Memory feature
MODEM_TST_WRITE_TO_FILE  =  FALSE
MODEM_DRV_CUSTOM_TOOL_SUPPORT  = TRUE # TRUE or FALSE, To enable using driver customization tool for GPIO/EINT/ADC/UEM/Keypad setting.
MODEM_J2ME_SUPPORT = NONE    #  NONE: Java dont be support
MODEM_J2ME_VM = NONE    #  NONE: Java dont be support or MTK_DUMMY_MVM
MODEM_J2ME_MAX_LAUNCH_NUM = 0    #  MAX number can be supported by multiple vm
MODEM_J2ME_SHARE_MED_EXT_MEM = FALSE    # TRUE, FALSE
MODEM_SUPPORT_BACKGROUND_JAVA = FALSE    # TRUE, FALSE
MODEM_SUPPORT_JAVA_NOKIA_UI = FALSE    # TRUE, FALSE
MODEM_SUPPORT_JSR_75_PIM = FALSE
MODEM_SUPPORT_JSR_75_PIM_MSA = FALSE    # TRUE, FALSE
MODEM_SUPPORT_JSR_179 = FALSE
MODEM_SUPPORT_JSR_205 = FALSE
MODEM_WIFI_PREFER_SUPPORT = FALSE
MODEM_MMI_HIDE_WAPI = FALSE    # TRUE,FALSE
MODEM_DCD_SUPPORT = NONE    # INFRAWARE, NONE
MODEM_COMPILER          =  RVCT      # RVCT or ADS
MODEM_RVCT_MULTI_FILE   =  NONE      # NONE for ADS compiler
MODEM_RTOS              =  NUCLEUS_V2   # NUCLEUS or THREADX
MODEM_RTOS_DEBUG        =  TRUE        # RTOS Debug Support
MODEM_MCU_CLOCK			=	MCU_520M		# MCU clock setting, MCU_13M, MCU_26M, MCU_39M, MCU_52M, MCU_104M
MODEM_MCU_DCM           =  DCM_ENABLE  # DCM_ENABLE, DCM_DISABLE
MODEM_CHIP_VER          =  S01         # Chip version code of Platform MT6218B, SHOULD BE ONE OF THE FOLLOWINGS
MODEM_PLATFORM          =  MT6575      # Hardware Platform, MT6208, FPGA, MT6218, MT6218B, MT6219, MT6226, MT6227, MT6228, MT6229 ...etc.
MODEM_DEMO_PROJECT		= FALSE   # TRUE, FALSE. TRUE for internal demo project.
MODEM_FLAVOR = NONE    # FLAVOR = NONE/$(FLAVOR)
MODEM_UART_CHARGER_THE_SAME_INTERFACE  = NONE  # NONE, not exist any UART port use the same interface with charger
MODEM_FM_RADIO_CHIP = NONE    # NONE
MODEM_FM_INTERFACE_TYPE = I2C     # NONE, I2C, HCI
MODEM_FM_RADIO_I2S_PATH = FALSE  # TRUE, FALSE
MODEM_FM_RADIO_HW_SEARCH = FALSE    # TRUE, FALSE
MODEM_FM_RADIO_RECORD = FALSE  # TRUE, FALSE
MODEM_AFC_VCXO_TYPE     = VCTCXO		  # VCTCXO     : VCTCXO
MODEM_EXT_CLOCK			=	EXT_26M		# External clock source setting, EXT_13M, EXT_26M
MODEM_PRODUCTION_RELEASE	= TRUE	  # Production release feature includs autoreset when system hang
MODEM_TDD_RF_CUSTOM_TOOL_SUPPORT = FALSE     #
MODEM_DSP_SOLUTION = DUALMACDSP    # NONE, DUALMACDSP
MODEM_MMF_DECODE 		=  FALSE   # TRUE, FALSE   MMF_DECODE support in MT6218B, MT6217, MT6219 and later chip
MODEM_DSPIRDBG             = FALSE      # IRDBG interface for dsp debugging
MODEM_BT_FAX_PROFILE = FALSE    # TRUE, FALSE
MODEM_BT_SIM_PROFILE = FALSE  # TRUE, FALSE
MODEM_BT_SPP_CLIENT        = NONE       # NONE, BT_SPP_CLI_NO_SCO or BT_SPP_CLI_WITH_SCO (default: NONE)
MODEM_HW_PFC_SUPPORT    =  TRUE        # TRUE/FALSE
MODEM_IC_TEST_TYPE = NONE  # NONE, IC_MODULE_TEST, IC_BURNIN_TEST
MODEM_INTERNAL_ANTENNAL_SUPPORT = FALSE  # TRUE, FALSE
MODEM_LOW_COST_SUPPORT = NONE  # NONE, COMMON, ULC
MODEM_MTK_DSP_DEBUG     =  FALSE       # DSP Debugging Feature
MODEM_MTK_SLEEP_ENABLE  =  TRUE       # Sleep Mode Support
MODEM_PMIC              =  MT6329       # Charge Function, NONE, MT6305 or MT6318
MODEM_PMU_WITH_EXTERNL_CHARGER = FALSE  # TRUE, FALSE
MODEM_NOT_BENEFIT_FROM_BATTERY_CONSUMPTION_OPTIMISATION = FALSE    # TRUE, FALSE
MODEM_MDP_LCD_FW_UPDATE = FALSE
MODEM_MAIN_LCM_SCANLINE_ROTATION = BY_LCD_SIZE_SETTING    # LCM_SCANLINE_ROTATION_0: The LCM scanline is from left to right and from top to bottom
MODEM_BT_SPP_SERVER        = NONE       # NONE, BT_SPP_SRV_NO_SCO or BT_SPP_SRV_WITH_SCO (default:BT_SPP_SRV_NO_SCO)
MODEM_SUB_LCM_SCANLINE_ROTATION = BY_LCD_SIZE_SETTING    # LCM_SCANLINE_ROTATION_0: The LCM scanline is from left to right and from top to bottom
MODEM_SUBLCD_SYNC_LCM_METHOD = NONE    # NONE:  Sub LCD SYNC mode not exist
MODEM_SUBLCD_DEDICATED_KEYS_SUPPORT = FALSE  # TRUE, FALSE
MODEM_LANDSCAPE_UI_ON_PORTRAIT_LCM = FALSE
MODEM_LANDSCAPE_UI_ON_PORTRAIT_LCM_CCW_ROTATION_ANGLE = 270
MODEM_LANDSCAPE_UI_ON_PORTRAIT_LCM_SLIM_VERSION = FALSE
MODEM_SPATIAL_DITHERING       = FALSE   # TRUE or FALSE
MODEM_SYNC_LCM_SUPPORT = FALSE  # TRUE, FALSE
MODEM_MMI_BASE  =  PLUTO_MMI    # PLUTO_MMI, NEPTUNE_MMI
MODEM_MMI_FEATURES_SWITCH = FALSE       # TRUE or FALSE   It's for the internal usage only.
MODEM_EMPTY_RESOURCE    =  TRUE       #
MODEM_FONT_ENGINE = NONE  # NONE, FONT_ENGINE_MONOTYPE, FONT_ENGINE_MONOTYPE_DEMO, FONT_ENGINE_FREETYPE, FONT_ENGINE_FREETYPE_DEMO, FONT_ENGINE_WTLE
MODEM_FONT_RESOURCE         = OFFICIAL   # DEMO, OFFICIAL
MODEM_AOC_SUPPORT = TRUE
MODEM_APP_STORAGE_IN_SYS_DRV = FALSE   # To put Email and MMS message to NOR or NAND flash
MODEM_BROWSER_SUPPORT          = NONE  # NONE, OBIGO_Q03C, OBIGO_Q05A
MODEM_OBIGO_FEATURE    =  NONE    # WAP, WAP2, WAP_SEC, WAP2_SEC, NONE
MODEM_WAP_MEM_DEBUG = TRUE    # FALSE, FALSE. Works only for WAP_SUPPORT is OBIGO_Q03C
MODEM_UNIFIED_PUSH_FEATURES = NONE      # FULL, STANDARD, SLIM, NONE
MODEM_HTTP_INTERFACE_SUPPORT = FALSE   # TRUE or FALSE
MODEM_E_COMPASS_SENSOR_SUPPORT = NONE  # NONE, AMI304_I2C
MODEM_USB_IN_META_SUPPORT = FALSE    # TRUE, FALSE
MODEM_MOTION_SENSOR_SUPPORT = NONE  # NONE, KXP84_SPI, KXP84_I2C, KXP74_SPI, MXC6202_I2C, MMA7660_I2C, KXTF9_I2C
MODEM_CUST_KEYPAD_TONE_SUPPORT = FALSE  # TRUE or FALSE
MODEM_DRM_SUPPORT = NONE #DRM VENDOR: NONE, MTK, BSCI
MODEM_DRM_VERSION = NONE # DRM VERSION: NONE, V01, V02, ALL
MODEM_DRM_SECURE_CLOCK = FALSE    # TRUE  : Secure clock enabled
MODEM_DRM_SUPPORT_DB_SIZE = NONE  # NONE/DEFAULT/64/256/512/1024 (DRM database size cnfiguration)
MODEM_DRM_SUPPORT_SCAN_DISK = FALSE  # TRUE/FALSE (DRM supports scan disk or not)
MODEM_FOTA_ENABLE = NONE   # Enable the feature of "Firmware update Over The Air",
MODEM_FOTA_UPDATE_PACKAGE_ON_NAND = FALSE  # TRUE, FALSE
MODEM_GAME_ENGINE          = NONE      # NONE, GE_BROGENT
MODEM_SUPPORT_INFUSIO     = FALSE
MODEM_GADGET_SUPPORT = NONE
MODEM_MERCURY_SLAVE_BT_SUPPORT = FALSE # TRUE or FALSE
MODEM_GPS_SUPPORT = MT3326    # NONE, MT3318, MT3316, MT3326
MODEM_QQMOVIE_SUPPORT = FALSE  # TRUE, FALSE
MODEM_IMAGE_VIEWER_VER = STANDARD    # SLIM, STANDARD, EX, EX_DB, EX_SHARE_MEDMEM, EX_DB_SHARE_MEDMEM, NONE
MODEM_JOGBALL_SUPPORT = FALSE  # TRUE, FALSE
MODEM_EMS_SUPPORT          = EMS_NONE   # EMS_40 support only EMS 4.0
MODEM_SQLITE3_SUPPORT = FALSE  # TRUE, FALSE
MODEM_TCPIP_LOOP_SUPPORT  = FALSE   # TRUE, FALSE
MODEM_TCPIP_SUPPORT     =  NONE    # UDP_TCP, UDP, TCP, or NONE
MODEM_DHCPD_SUPPORT = FALSE    # TRUE, FALSE
MODEM_EXTERNAL_AMPLIFIER_ROUTE_CONFIGURATION = FALSE  # TRUE or FALSE
MODEM_UNIFIED_MESSAGE_LOW_MEMORY_SUPPORT = FALSE  # TRUE, FALSE
MODEM_NVRAM_AFE_DIGITAL_GAIN_SUPPORT = FALSE
MODEM_HOTSPOT_SUPPORT = FALSE    # TRUE, FALSE
MODEM_XDM_SUPPORT    = FALSE          # TRUE or FALSE
MODEM_SUPPORT_SURFKITCHEN = FALSE
MODEM_BLUETOOTH_VERSION       = NONE    # NONE, BT_VER_PRE21, BT_VER_21, BT_VER_30
MODEM_BT_A2DP_PROFILE      = FALSE     # TRUE, FALSE
MODEM_BT_AVRCP_PROFILE     = FALSE     # TRUE, FALSE
MODEM_TWOMICNR_SUPPORT    =  NONE        # NONE, FORTEMEDIA_FM2018
MODEM_BT_CONNECT_TO_UART2   = FALSE      # TRUE, FALSE
MODEM_3G_VIDEO_CALL       = FALSE    #  TRUE or FALSE
MODEM_PHB_ADDITIONAL_SUPPORT = FALSE    # TRUE, FALSE
MODEM_BT_SEQ_SUPPORT = FALSE  # FALSE, TRUE
MODEM_BT_AUDIO_VIA_SCO = FALSE  # TRUE, FALSE
MODEM_BT_FM_RADIO_VIA_SCO = FALSE  # TRUE, FALSE
MODEM_MAUI_SDK_TEST = FALSE    # TRUE: MAUI SDK AVK test is open
MODEM_L1_GPS_REF_TIME_SUPPORT = TRUE    # TRUE, FALSE
MODEM_AGPS_SUPPORT = CONTROL_PLANE    # NONE, USER_PLANE, CONTROL_PLANE, BOTH
MODEM_OMA_ULP_SUPPORT = NONE    # NONE, V1
MODEM_RRLP_VER_SUPPORT = R5    # NONE, R5
MODEM_AGPS_UP_CP_CONFLICT_HANDLING_SUPPORT = TRUE    # TRUE, FALSE
MODEM_AGPS_CP_SIB15_SUPPORT = TRUE    # TRUE, FALSE
MODEM_GPS_HS_SUPPORT = FALSE
MODEM_RFC2507_SUPPORT     = TRUE    # TRUE/FALSE, Enable/Disable RFC2507 IP header compression support
MODEM_USB_SUPPORT      =  FALSE       # MT6218B and MT6219 chip support USB
MODEM_USB_COM_PORT_SUPPORT = FALSE  # TRUE, FALSE
MODEM_USB_COMPORT_PC_DRIVER_SUPPORT = MS    # TC01, MS, MTK, MAC
MODEM_USB_TETHERING = FALSE    # TRUE, FALSE
MODEM_BATTERY_CHARGING_SUPPORT = FALSE
MODEM_OTG_SUPPORT      = FALSE       #  TRUE, FALSE
MODEM_PICTBRIDGE_SUPPORT = FALSE    # TRUE or FALSE, IMPS Feature Support
MODEM_UART3_SUPPORT		= FALSE   # TRUE or FALSE,  SUPPORT UART 3
MODEM_FLASHLIGHT_MODULE       = NONE     # NONE, IMCR3603_S010AO
MODEM_DMA_UART_VFIFO_TUNNEL_SUPPORT = FALSE
MODEM_DMA_UART_VIRTUAL_FIFO   = TRUE   # TRUE or FALSE
MODEM_SENSOR_ROTATE = SENSOR_ROTATE_0
MODEM_FAX_SUPPORT = FALSE    # TRUE, FALSE
MODEM_SYNCML_DM_SUPPORT = FALSE    # INSIGNIA_DM,FALSE
MODEM_SYNCML_DM_VERSION = NONE  # NONE, DM11, DM12, DM12_SCTS
MODEM_TTL_SUPPORT = LIB
MODEM_A8BOX_SUPPORT = FALSE  # TRUE, FALSE
MODEM_ATV_SUPPORT = FALSE   # TRUE, FALSE
MODEM_ATV_CHIP = VER00
MODEM_ATV_I2S_PATH = FALSE
MODEM_ATV_RECORD_SUPPORT = FALSE    # TRUE/FALSE
MODEM_ATV_SMS_SUPPORT = FALSE    # TRUE/FALSE
MODEM_BACKGROUND_SOUND	   = TRUE	  # TRUE/FALSE
MODEM_DIGIT_TONE_SUPPORT      = FALSE   # TRUE or FALSE
MODEM_LQT_SUPPORT = FALSE  # FALSE, TRUE
MODEM_JTONE_SUPPORT = FALSE  # TRUE, FALSE
MODEM_MEDIA_PLAYER_VER = SEPARATED    # SEPARATED, INTEGRATED, INTEGRATED_DB, INTEGRATED_FTE_DB
MODEM_M3GPMP4_FILE_FORMAT_SUPPORT  =  FALSE    # TRUE, FALSE
MODEM_PURE_AUDIO_SUPPORT      = FALSE         # TRUE or FALSE
MODEM_AAC_DECODE 			= FALSE		# TRUE/FALSE
MODEM_AAC_PLUS_DECODE      =  FALSE		# TRUE/FALSE
MODEM_AAC_PLUS_PS_DECODE = FALSE  # TRUE, FALSE
MODEM_AIFF_DECODE = FALSE  # TRUE, FALSE
MODEM_AMR_CODEC = FALSE  # TRUE, FALSE
MODEM_AMRWB_DECODE 		= FALSE		# TRUE/FALSE
MODEM_AMRWB_ENCODE 		= FALSE		# TRUE/FALSE
MODEM_DEDI_AMR_REC      =  FALSE      # AMR recording in GSM traffic mode. This function requires more than 50%MCU computing power.
MODEM_APE_DECODE = FALSE    # TRUE
MODEM_AU_DECODE = FALSE  # TRUE, FALSE
MODEM_BSAC_DECODE =  FALSE  # TRUE, FALSE
MODEM_COOK_DECODE  = FALSE  # TRUE, FALSE
MODEM_DAF_DECODE 			= FALSE		# TRUE/FALSE
MODEM_DAF_ENCODE = FALSE  # TRUE, FALSE
MODEM_DRA_DECODE = FALSE    # TRUE, FALSE
MODEM_M4A_DECODE = FALSE   # TRUE or FALSE
MODEM_SYNC_LCM_METHOD = BY_CHIP    # BY_CHIP:legacy chip-dependence method,SW: SW sync mode,HW: HW sync mode
MODEM_MUSICAM_DECODE  = FALSE   # TRUE, FALSE
MODEM_WAV_CODEC = TRUE  # TRUE, FALSE
MODEM_WAVETABLE_VER = WT600K    # Wavetable version, Please choose one among:
MODEM_WMA_DECODE = FALSE              # MT6228 support WMA DECODE
MODEM_AUDIO_COMPENSATION_DSP_IIR_SUPPORT = FALSE    # TRUE, FALSE
MODEM_AUDIO_COMPENSATION_ENABLE = FALSE  # TRUE, FALSE
MODEM_AUD_RECORD = TRUE          # TRUE, FALSE : Turn on audio record feature, olny set to FALSE for very low cost project
MODEM_BITSTREAM_SUPPORT = FALSE  # TRUE, FALSE
MODEM_BES_BASS_SUPPORT = FALSE  # TRUE, FALSE
MODEM_BES_EQ_SUPPORT           = FALSE # TRUE, FALSE
MODEM_BES_LIVE_SUPPORT    = FALSE	  # TRUE, FALSE
MODEM_BES_LOUDNESS_SUPPORT = FALSE    # TRUE, FALSE
MODEM_BES_SURROUND_SUPPORT     = NONE  # NONE, MODE_LSPK, MODE_EARP, MODE_BOTH
MODEM_BES_TS_SUPPORT    = FALSE	  # TRUE, FALSE
MODEM_CTM_SUPPORT          = TRUE    # TRUE, FALSE
MODEM_DSP_COMPRESS = NONE    #  ZIP, 7Z, NONE
MODEM_DUAL_MIC_SUPPORT = TRUE    # TRUE, FALSE    only MT6256 and MT6276 or later chip can set the value as TRUE
MODEM_SYNCML_SUPPORT                   = FALSE        # TRUE or FALSE
MODEM_SYNCML_DEVICE_SYNC_SUPPORT = FALSE  # TRUE, FALSE
MODEM_I2S_INPUT_MODE_SUPPORT = FALSE  # TRUE, FALSE
MODEM_IP_COMMON_SUPPORT = FALSE    # TRUE, FALSE
MODEM_LARGE_MIDI_FILE_SUPPORT  =  FALSE    # TRUE, FALSE
MODEM_MED_PROFILE             = MED_MODEM  # MED_LOW, MED_NORMAL, MED_HIGH
MODEM_MELODY_VER = NONE    # NONE, DSP_WT_SYN
MODEM_RICH_AUDIO_PROFILE = TRUE
MODEM_AEC_ENABLE              =  TRUE  # Acoustic Echo Cancellation (AEC)
MODEM_AMRWB_LINK_SUPPORT = TRUE    # TRUE, FALSE
MODEM_EES_ENABLE              =  TRUE  # Enhanced Echo Suppression (EES)
MODEM_SYNCML_PC_SYNC_SUPPORT = FALSE  # TRUE, FALSE
MODEM_TTS = NONE    # SIMPLE_TTS, NONE
MODEM_CMMB_SUPPORT = NONE  # NONE, INNOFIDEI_IF201, INNOFIDEI_IF202, TELEPATH_TP3001B
MODEM_CMMB_CAS_FULL_CARD_SUPPORT = FALSE  # TRUE, FALSE
MODEM_CMMB_CAS_MBBMS_SUPPORT = FALSE
MODEM_CMMB_CAS_SMD_SUPPORT = FALSE   # TRUE, FALSE
MODEM_H264_DECODE = FALSE   # TRUE, FALSE
MODEM_H264_DECODE_MODE = NORMAL    # NORMAL,SLIM
MODEM_H264_OPEN_API = FALSE  # TRUE, FALSE
MODEM_MP4_DECODE = FALSE    # FALSE, TRUE
MODEM_MP4_DECODE_MODE = NONE  # NORMAL, SLIM, NONE
MODEM_MP4_ENCODE = FALSE    # FALSE, TRUE
MODEM_MP4_ENCODE_MODE = NORMAL    # NORMAL: normal setting for encoder (default setting)
MODEM_MJPG_DECODE_MODE = NORMAL    # NORMAL: Normal segment (Default setting)
MODEM_SUPPORT_VIDEO_RECORD_ROTATE = FALSE  # TRUE, FALSE
MODEM_STREAM_REC_SUPPORT = FALSE    # TRUE, FALSE
MODEM_RTSP_SUPPORT = FALSE            # TRUE or FALSE
MODEM_TDMB_SUPPORT            = NONE       # NONE, TELECHIP_TDMB, FRONTIER_TDMB
MODEM_TV_OUT_SUPPORT 		= FALSE		# TRUE, FALSE  only MT6228 and MT6229 support TV OUT
MODEM_VDOEDT_SUPPORT = FALSE  # TRUE, FALSE
MODEM_OCSP_SUPPORT  = FALSE  # TRUE, FALSE
MODEM_JPEG_SENSOR_SUPPORT = FALSE    # TRUE,FALSE
MODEM_SOCKET_SSL_SUPPORT = FALSE  # TRUE, FALSE
MODEM_SSL_SUPPORT             = NONE   # NONE, SSL_CIC_LIB, MTK_SSL_CIC, OPENSSL, OPENSSL_MTK
MODEM_ISO_PRIORITY_MODE_SUPPORT = FALSE   # FALSE, TRUE
MODEM_ISP_SUPPORT 		= FALSE		# TRUE/FALSE
MODEM_MSHUTTER_SUPPORT = FALSE  # TRUE, FALSE
MODEM_SENSOR_LOCATION = SENSOR_ON_BODY    # SENSOR_ON_BODY, SENSOR_ON_CLAM, SENSOR_INSIDE_CLAM
MODEM_JPG_DECODE = FALSE    # TRUE, FALSE
MODEM_JPG_ENCODE = FALSE    # TRUE, FALSE
MODEM_EXIF_SUPPORT = FALSE  # TRUE, FALSE
MODEM_PNG_DECODE = FALSE    # TRUE, FALSE
MODEM_SW_FLASH           = NONE    # NONE, NEOMTEL
MODEM_OPENGL               =  NONE     # COMMON_LITE, NONE
MODEM_BOOT_CERT_SUPPORT = FALSE    # TRUE, FALSE
MODEM_CHE_SUPPORT          = FALSE    # CHE support
MODEM_CHE_INPUT_FROM_FSAL = FALSE  # TRUE or FALSE
MODEM_IPSEC_SUPPORT = FALSE  # FALSE, IPSEC_IKEv1
MODEM_CBM_ALWAYS_ASK_SUPPORT = FALSE  # TRUE or FALSE
MODEM_RC5_SUPPORT          = TRUE      # TRUE or FALSE, RC5 feature support
MODEM_SECURE_SUPPORT      = FALSE       #
MODEM_SECURE_RO_ENABLE    = FALSE       # TRUE, FALSE
MODEM_CBM_BEARER_FALLBACK_SUPPORT = FALSE  # TRUE or FALSE
MODEM_CBM_CONNECTION_MANAGER_SUPPORT = FALSE  # TRUE or FALSE
MODEM_RES_PROT = FALSE
MODEM_SW_BINDING_SUPPORT = NONE
MODEM_BAND_SUPPORT	    =  QUAD	             # support of designated band: PGSM900, EGSM900, RGSM900, DCS1800, PCS1900, GSM850, GSM450, GSM480, DUAL900, TRIPLE, QUAD, DUAL850
MODEM_EDGE_SUPPORT			= TRUE	  # EDGE support
MODEM_SMS_R8_NATION_LANGUAGE = FALSE    # TRUE/FALSE, to support Turkish letter in SMS
MODEM_USIM_SUPPORT = TRUE  # TRUE or FALSE
MODEM_UMTS_MODE_SUPPORT = UMTS_FDD_MODE_SUPPORT  # NONE, UMTS_FDD_MODE_SUPPORT, UMTS_TDD128_MODE_SUPPORT
MODEM_IPV6_PDP_SUPPORT = TRUE      # FALSE, not support IPv6 PDP Context
MODEM_UMTS_RF_MODULE    =  CUSTOM_MT6162
MODEM_HSDPA_SUPPORT = TRUE    # TRUE, FALSE
MODEM_HSUPA_SUPPORT = TRUE    # TRUE, FALSE
MODEM_R99_SUPPORT	    		= TRUE	  # Release 99 support
MODEM_R4_SUPPORT      = TRUE   # Release 4 support
MODEM_R5_SUPPORT      = TRUE   # Release 5 support
MODEM_3SET_F8F9_ENABLE = TRUE  # TRUE, FALSE
MODEM_AMR_LINK_SUPPORT        = TRUE    # TRUE or FALSE
MODEM_AT_COMMAND_SET = FULL    # FULL ,SLIM ,ULC
MODEM_CCBS_SUPPORT = FALSE  # TRUE, FALSE
MODEM_CENTRALIZED_SLEEP_MANAGER = TRUE   # TRUE, FALSE
MODEM_CMUX_SUPPORT	        = TRUE   #
MODEM_CNAP_SUPPORT = FALSE  # TRUE, FALSE
MODEM_CSD_SUPPORT = NONE    # CSD Feature,   NONE : NOT support CSD feature
MODEM_EMLPP_SUPPORT = FALSE  # TRUE, FALSE
MODEM_EXT_MODEM_SUPPORT = FALSE  # TRUE, FALSE
MODEM_DISABLE_A5_2 = TRUE  # TRUE, FALSE
MODEM_FDD_EDCH_PHYSICAL_CATEGORY = 6
MODEM_FDD_HSDSCH_PHYSICAL_CATEGORY = 8
MODEM_GERAN_RELEASE_SUPPORT = GERAN_R6_SUPPORT # GERAN_R6_SUPPORT for GSM/GPRS/EDGE support version of release 6
MODEM_GPRS_DIALUP_PPP_DROP_PACKETS_WHEN_2G_PS_SUSPEND = TRUE  # TRUE, FALSE
MODEM_GPRS_DIALUP_PPP_SUPPORT_ESCAPE_ATO = TRUE  # TRUE, FALSE
MODEM_GPRS_DIALUP_PPP_SUPPORT_SPEED_UP_DIALUP = TRUE  # TRUE, FALSE
MODEM_L1_3GSOLUTION     =  MTK_UL1_FDD       # MA_L1 or MTK_UL1_FDD
MODEM_L1_EGPRS          =  TRUE
MODEM_L1_EPSK_TX        =  TRUE        # EDGE TX
MODEM_L1_GPRS           =  TRUE        # L1 GPRS Funtion, Notice: MT6205 don't support that
MODEM_L1_WCDMA          =  TRUE        # L1_WCDMA ............................ this option may not be necessary when project=umts
MODEM_L1L2_TX_NEW_ARCH = TRUE    # TRUE, FALSE
MODEM_L2_HSDPA_COPRO = TRUE    # TRUE: Use L2 HSDPA Coprocessor
MODEM_L2_HSUPA_COPRO = TRUE    # TRUE: Use L2 HSUPA Coprocessor
MODEM_MAX_NUM_OF_NDIS_SUPPORT = 6      # 2,3
MODEM_MCD_CODESET_SHIFT_SUPPORT = NONE  # NONE, 440000
MODEM_MCD_SUPPORT       =  TRUE       # MCD support feature
MODEM_MODEM_3G_LOGGING = FALSE  # TRUE, FALSE
MODEM_MULTIPLE_NDIS_SUPPORT = TRUE    # TRUE/FALSE, Enable/Disable Multiple PPP GPRS Dialup support
MODEM_MULTIPLE_TBF = FALSE    # TRUE, FALSE
MODEM_PLMN_LIST_PREF_SUPPORT = DEFAULT     # ON, OFF
MODEM_PPP_TYPE_PDP_DIALUP_SUPPORT = FALSE  # TRUE, FALSE
MODEM_RRC_PAYLOAD_FOR_3G_UP_SUPPORT  =  FALSE   # TRUE, FALSE
MODEM_SMART_PHONE_CORE = ANDROID_MODEM     # Determine software load role playing and exectuion processor on dual-core smart phone platforms (ex. MT6516),
MODEM_SMART_PHONE_MODEM = FALSE  # TRUE, FALSE
MODEM_SP_VIDEO_CALL_SUPPORT = TRUE    # TRUE, FALSE
MODEM_SML_SUPPORT = TRUE
MODEM_SMS_OVER_PS_SUPPORT  = TRUE   # TRUE, FALSE
MODEM_ULCS_ASN_SUPPORT_VERSION = ULCS_ASN_SUPPORT_R99  #ULCS_ASN_SUPPORT_R99, ULCS_ASN_SUPPORT_R6
MODEM_UMTS_RELEASE_SUPPORT	= UMTS_R6_SUPPORT	    # NONE means for UMTS FDD protocol stack support version of release 99
MODEM_UUS_SUPPORT = FALSE  # TRUE, FALSE
MODEM_FS_CHECKDRIVE_SUPPORT	= FALSE	  # In Engineering Mode, there will be an option to check and fix drives.
MODEM_FS_MOVE_SUPPORT		=  TRUE	  # Both file system and file manager will support move/copy function
MODEM_FS_QM_SUPPORT		=  TRUE  # Quota management mechanism for system drive.
MODEM_FS_SORT_MAX_ENTRY = 256  # 64 ~ 256 or 20000
MODEM_FS_SORT_SUPPORT		=  TRUE  # After this feature is enabled, FMGR will have file sorting option for each folders.
MODEM_FS_TRACE_SUPPORT	=  FALSE  # File system trace feature.
MODEM_FS_ASYNC_SUPPORT = FALSE    # TRUE :  to enable Async I/F
MODEM_NVRAM_PSEUDO_MERGE = OFF    # ON, OFF
MODEM_KAL_ASSERT_SHRINKING = FALSE
MODEM_KAL_DEDUG_AND_TRACE_LEVEL = NORMAL_DEBUG_KAL
MODEM_SECURE_PORT_SUPPORT = FALSE  # TRUE, FALSE
MODEM_KEYPAD_DEBUG_TRACE = FALSE
MODEM_RESOURCE_MANAGER = FALSE  # TRUE, FALSE
MODEM_SSS_SUPPORT      = SSS_LIB     # SSS_LIB, SSS_SOURCE
MODEM_SWDBG_SUPPORT        = FALSE     # MT6228 support software debug
MODEM_NAND_SUPPORT     =  FALSE      # Enable/disable NAND flash memory support
MODEM_SYSTEM_DRIVE_ON_NAND = FALSE   # System drive location
MODEM_NAND_SUPPORT_RAW_DISK = FALSE
MODEM_ENHANCED_SINGLE_BANK_NOR_FLASH_SUPPORT = FALSE  # TRUE, FALSE
MODEM_SYSDRV_BACKUP_DISK_SUPPORT = NONE
MODEM_MSDC_CARD_SUPPORT_TYPE = NONE      #  MSDC_SD_MMC      for SD/MMC card support
MODEM_CARD_DOWNLOAD = FALSE
MODEM_L1_CATCHER        =  TRUE        # L1 Catcher Support
MODEM_M3D_MMI_SUPPORT      = FALSE     # TRUE, FALSE
MODEM_NDIS_SUPPORT = UPS  # NONE, NDIS , UPS
MODEM_TST_SUPPORT			=	TRUE			# TST task Support
MODEM_TST_LOGACC_SUPPORT = TRUE  # TRUE, FALSE
MODEM_TST_SET_LOG_BUF_SIZ = NONE
MODEM_TST_DNT_LOGGING = FALSE
MODEM_DT_SUPPORT = FALSE    # TRUE, FALSE
MODEM_MODIS_ON_VC9      =  TRUE     # TRUE, FALSE
MODEM_MODIS_FDM = OFF    # ON, to enable target File System (mcu\fs\fat) on MoDIS
MODEM_SPLIT_SYSTEM      =  FALSE       # Split system feature
MODEM_J2ME_DEFAULT_GAME	 =   DEMO	# DEMO(For reference only), PRODUCTION(production default game), MP (non-default game)
MODEM_J2ME_FEATURE_SET = NONE    # J2ME_FEATURE_SET: NONE, BASIC, JTWI
MODEM_J2ME_SLIM_MEMORY_SUPPORT = FALSE    # TRUE, FALSE
MODEM_J2ME_SLIM_SCREEN_MEMORY_SUPPORT = FALSE    # TRUE, FALSE
MODEM_SUPPORT_JSR_82 = FALSE    # TRUE, FALSE
MODEM_SUPPORT_JSR_184 = FALSE
MODEM_TFTP_SUPPORT         = FALSE  	 #  TRUE, FALSE
MODEM_SDP_SUPPORT 	        = FALSE        # TRUE or FALSE
MODEM_SIP_SUPPORT 	= FALSE        # TRUE or FALSE
MODEM_VOIP_SUPPORT            = FALSE     # TRUE, FALSE
MODEM_WIFI_SUPPORT = NONE  # NONE, MT5911, MT5921
MODEM_WAPI_SUPPORT = FALSE   # TRUE, FALSE
MODEM_WNDRV_SUPPORT = LIB
MODEM_DUAL_MEMORY_CARD_SUPPORT = NONE    # NONE : no dual card support,SWITCH :use single msdc controller + switch to support dual card
MODEM_IPERF_SUPPORT        = NONE 	 #  SINGLE, DUAL, TRIPLE, QUAD, NONE
MODEM_IPERF_WMM_PS_TEST_SUPPORT = FALSE    # TRUE,FALSE
MODEM_WIFI_BT_SINGLE_ANTENNA_SUPPORT = FALSE  # TRUE, FALSE
MODEM_OPTR_SPEC = NONE
MODEM_DM_MO_SUPPORT       = NONE     # LAW_SCO, LAW, SCO, or NONE
MODEM_MOBILE_VIDEO_SUPPORT = NONE    # WONDER: define this feature.
MODEM_TC01_OAEP_SUPPORT = FALSE
MODEM_CUSTOMER_SPECIFIC_FACTORY_DETECTION = NONE        # NONE, CS_FAC_DET_TYPE_1
MODEM_CLASSAB_LOW_VOLTAGE_VOLUME_PROTECTION = FALSE    # TRUE,FALSE
MODEM_FAST_DORMANCY_SUPPORT = TRUE     # TRUE: GEMINI_VERSION = V2
MODEM_DISABLE_EGSM_CAP = FALSE     # TRUE  : Disable EGSM band capability
MODEM_2G_RF_CUSTOM_TOOL_SUPPORT = TRUE        # TRUE, FALSE
MODEM_LG_VOICE_ENGINE = FALSE   # TRUE, FALSE
MODEM_PBCCH_SUPPORT = TRUE     # TRUE  : Enable  PBCCH support
MODEM_LGE_BT_SYSTEM_SUPPORT = FALSE
MODEM_GEMINI_VERSION = V2     # V1: Gemini 1.0
MODEM_FDD_RF_CUSTOM_TOOL_SUPPORT = TRUE        # TRUE, FALSE
MODEM_DSPIRDBG_SP          = FALSE      # IRDBG(FCore usb logging) for smart phone
MODEM_RELEASE_PACKAGE = REL_CR_MMI_hspa # REL_CR_MMI_GPRS, REL_CR_MMI_GSM, REL_CR_L4_GPRS, REL_CR_L4_GSM
MODEM_RELEASE_INPUT_METHODS_SRC =		# MMI_ZI, MMI_T9, MMI_ITAP,
MODEM_RELEASE_TYPE = NONE           # NONE, INTERNAL
MODEM_COM_DEFS_FOR_CUSTOM_MT6162 = MT6162_RF CUSTOM_MT6162
MODEM_COM_DEFS_FOR_TINNOES75_NAND_LCM = TINNOES75_NAND_LCM
