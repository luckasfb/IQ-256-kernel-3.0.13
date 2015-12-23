




#ifndef _CFG_AUDIO_H
#define _CFG_AUDIO_H

#include "../cfgfileinc/CFG_AUDIO_File.h"
#include "../inc/sph_coeff_default.h"
#include "../inc/sph_coeff_record_mode_default.h"
#include "../inc/audio_custom.h"
#include "../inc/audio_hd_record_custom.h"
#include "../inc/audio_acf_default.h"
#include "../inc/audio_hcf_default.h"
#include "../inc/audio_effect_default.h"
#include "../inc/med_audio_default.h"
#include "../inc/audio_volume_custom_default.h"
#include "../inc/audio_gain_table_default.h"

AUDIO_CUSTOM_PARAM_STRUCT speech_custom_default =
{
    /* INT8 volume[MAX_VOL_CATE][MAX_VOL_TYPE] */
    /* Normal volume: TON, SPK, MIC, FMR, SPH, SID, MED */
    GAIN_NOR_TON_VOL, GAIN_NOR_KEY_VOL, GAIN_NOR_MIC_VOL, GAIN_NOR_FMR_VOL, GAIN_NOR_SPH_VOL, GAIN_NOR_SID_VOL, GAIN_NOR_MED_VOL
    ,
    /* Headset volume: TON, SPK, MIC, FMR, SPH, SID, MED */
    GAIN_HED_TON_VOL, GAIN_HED_KEY_VOL, GAIN_HED_MIC_VOL, GAIN_HED_FMR_VOL, GAIN_HED_SPH_VOL, GAIN_HED_SID_VOL, GAIN_HED_MED_VOL
    ,
    /* Handfree volume: TON, SPK, MIC, FMR, SPH, SID, MED */
    GAIN_HND_TON_VOL, GAIN_HND_KEY_VOL, GAIN_HND_MIC_VOL, GAIN_HND_FMR_VOL, GAIN_HND_SPH_VOL, GAIN_HND_SID_VOL, GAIN_HND_MED_VOL
    ,
    /* UINT16 speech_common_para[12] */
    DEFAULT_SPEECH_COMMON_PARA
    ,
    /* UINT16 speech_mode_para[8][16] */
    DEFAULT_SPEECH_NORMAL_MODE_PARA,
    DEFAULT_SPEECH_EARPHONE_MODE_PARA,
    DEFAULT_SPEECH_LOUDSPK_MODE_PARA,
    DEFAULT_SPEECH_BT_EARPHONE_MODE_PARA,
    DEFAULT_SPEECH_BT_CORDLESS_MODE_PARA,
    DEFAULT_SPEECH_CARKIT_MODE_PARA,
    DEFAULT_SPEECH_AUX1_MODE_PARA,
    DEFAULT_SPEECH_AUX2_MODE_PARA
    ,
    /* UINT16 speech_volume_para[4] */
    DEFAULT_SPEECH_VOL_PARA
    ,
    /* UINT16 debug_info[16] */
    DEFAULT_AUDIO_DEBUG_INFO
    ,
    /* INT16 sph_in_fir[6][45], sph_out_fir */
    SPEECH_INPUT_FIR_COEFF,
    SPEECH_OUTPUT_FIR_COEFF
    ,
    /* UINT16 DG_DL_Speech */
    DG_DL_Speech
    ,
    /* UINT16 DG_Microphone */
    DG_Microphone
    ,
    /* UINT16 FM record volume*/
    FM_Record_Vol
    ,
    /* UINT16 BT sync type and length*/
    DEFAULT_BLUETOOTH_SYNC_TYPE,
    DEFAULT_BLUETOOTH_SYNC_LENGTH
    ,
    /* UINT16 BT PCM in/out digital gain*/
    DEFAULT_BT_PCM_IN_VOL,
    DEFAULT_BT_PCM_OUT_VOL
    ,
    /* user mode : normal mode, earphone mode, loud speaker mode */
    /* UCHAR  user_mode             */
    VOL_NORMAL
    ,
    /* auto VM record setting */
    DEFAULT_VM_SUPPORT,
    DEFAULT_AUTO_VM,
    /* Micbais voltage 1900 --> 2200 */
    MICBAIS,
};

AUDIO_CUSTOM_WB_PARAM_STRUCT wb_speech_custom_default =
{
    /* unsigned short speech_mode_wb_para[8][16] */
    DEFAULT_WB_SPEECH_NORMAL_MODE_PARA,
    DEFAULT_WB_SPEECH_EARPHONE_MODE_PARA,
    DEFAULT_WB_SPEECH_LOUDSPK_MODE_PARA,
    DEFAULT_WB_SPEECH_BT_EARPHONE_MODE_PARA,
    DEFAULT_WB_SPEECH_BT_CORDLESS_MODE_PARA,
    DEFAULT_WB_SPEECH_CARKIT_MODE_PARA,
    DEFAULT_WB_SPEECH_AUX1_MODE_PARA,
    DEFAULT_WB_SPEECH_AUX2_MODE_PARA,
    /* short sph_wb_in_fir[6][90] */
    WB_Speech_Input_FIR_Coeff,
    /* short sph_wb_out_fir[6][90] */
    WB_Speech_Output_FIR_Coeff,
};

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_custom_default =
{
    /* Compensation Filter HSF coeffs: default all pass filter       */
    /* BesLoudness also uses this coeffs    */
    BES_LOUDNESS_HSF_COEFF,
    /* Compensation Filter BPF coeffs: default all pass filter      */
    BES_LOUDNESS_BPF_COEFF,
    BES_LOUDNESS_DRC_FORGET_TABLE,
    BES_LOUDNESS_WS_GAIN_MAX,
    BES_LOUDNESS_WS_GAIN_MIN,
    BES_LOUDNESS_FILTER_FIRST,
    BES_LOUDNESS_GAIN_MAP_IN,
    BES_LOUDNESS_GAIN_MAP_OUT,
};

AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_hcf_custom_default =
{
    /* Compensation Filter HSF coeffs: default all pass filter       */
    /* BesLoudness also uses this coeffs    */
    BES_LOUDNESS_HCF_HSF_COEFF,
    /* Compensation Filter BPF coeffs: default all pass filter      */
    BES_LOUDNESS_HCF_BPF_COEFF,
    BES_LOUDNESS_HCF_DRC_FORGET_TABLE,
    BES_LOUDNESS_HCF_WS_GAIN_MAX,
    BES_LOUDNESS_HCF_WS_GAIN_MIN,
    BES_LOUDNESS_HCF_FILTER_FIRST,
    BES_LOUDNESS_HCF_GAIN_MAP_IN,
    BES_LOUDNESS_HCF_GAIN_MAP_OUT,
};


AUDIO_EFFECT_CUSTOM_PARAM_STRUCT audio_effect_custom_default =
{
    // DSRD parameters
    BSRD_LEVEL,
    BSRD_DISTANCE1,
    BSRD_DISTANCE2,
    BSRD_BAND_SELECT,

    // BASS
    BASS_CUTOFF_FREQ,
    BASS_ISVB,

    //EQ effect
    NORMAL_GAIN_LEVEL,
    DANCE_GAIN_LEVEL,
    BASS_GAIN_LEVEL,
    CLASSICAL_GAIN_LEVEL,
    TREBLE_GAIN_LEVEL,
    PARTY_GAIN_LEVEL,
    POP_GAIN_LEVEL,
    ROCK_GAIN_LEVEL,

    //loudness mode
    LOUDENHANCEMODE,

    //TS
    TIME_TD_TF,
    TIME_TS_RATIO
};

AUDIO_PARAM_MED_STRUCT audio_param_med_default =
{
    SPEECH_INPUT_MED_FIR_COEFF,
    SPEECH_OUTPUT_MED_FIR_COEFF,
    FIR_output_index,
    FIR_input_index,
    MED_SPEECH_NORMAL_MODE_PARA,
    MED_SPEECH_EARPHONE_MODE_PARA,
    MED_SPEECH_BT_EARPHONE_MODE_PARA,
    MED_SPEECH_LOUDSPK_MODE_PARA,
    MED_SPEECH_CARKIT_MODE_PARA,
    MED_SPEECH_BT_CORDLESS_MODE_PARA,
    MED_SPEECH_AUX1_MODE_PARA,
    MED_SPEECH_AUX2_MODE_PARA
};


AUDIO_VOLUME_CUSTOM_STRUCT audio_volume_custom_default =
{
    AUD_VOLUME_RING,
    AUD_VOLUME_KEY,
    AUD_VOLUME_MIC,
    AUD_VOLUME_FMR,
    AUD_VOLUME_SPH,
    AUD_VOLUME_SID,
    AUD_VOLUME_MEDIA,
    AUD_VOLUME_MATV
};

AUDIO_CUSTOM_EXTRA_PARAM_STRUCT dual_mic_custom_default =
{
    DEFAULT_SPEECH_DUAL_MIC_ABF_PARA,
    DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA
};

AUDIO_GAIN_TABLE_STRUCT Gain_control_table_default ={
    DEFAULT_VOICE_GAIN_TABLE_PARA,
    DEFAULT_SYSTEM_GAIN_TABLE_PARA,
    DEFAULT_RINGTONE_GAIN_TABLE_PARA,
    DEFAULT_MUSIC_GAIN_TABLE_PARA,
    DEFAULT_ALARM_GAIN_TABLE_PARA,
    DEFAULT_NOTIFICATION_GAIN_TABLE_PARA,
    DEFAULT_BLUETOOTH_SCO_GAIN_TABLE_PARA,
    DEFAULT_ENFORCEAUDIBLE_GAIN_TABLE_PARA,
    DEFAULT_DTMF_GAIN_TABLE_PARA,
    DEFAULT_TTS_GAIN_TABLE_PARA,
    DEFAULT_FM_GAIN_TABLE_PARA,
    DEFAULT_MATV_GAIN_TABLE_PARA,
    DEFAULT_MICROPHONE_GAIN_TABLE_PARA,
    DEFAULT_SIDETONE_GAIN_TABLE_PARA,
    DEFAULT_SPEECH_GAIN_TABLE_PARA
};

AUDIO_HD_RECORD_PARAM_STRUCT Hd_Recrod_Par_default = {
    //hd_rec mode num & fir num
    HD_REC_MODE_INDEX_NUM,
    HD_REC_FIR_INDEX_NUM,
    //hd_rec_speech_mode_para (max 30 sets, 30 - 24 = 18)
    DEFAULT_HD_RECORD_SPH_MODE_PAR,
    DUMMY_HD_RECORD_SPH_MODE_PAR_FOR_6_MODE,
    //hd_rec_fir (max 4 sets, 4 - 1 = 3)
    DEFAULT_HD_RECORD_FIR_Coeff,
    DUMMY_HD_RECORD_FIR_Coeff_FOR_3_FIR,
    //hd_rec fir mapping - ch1
    DEFAULT_HD_RECORD_MODE_FIR_MAPPING_CH1,
    DUMMY_HD_RECORD_MODE_FIR_MAPPING_CH1_FOR_6_MODE,
    //hd_rec fir mapping - ch2
    DEFAULT_HD_RECORD_MODE_FIR_MAPPING_CH2,
    DUMMY_HD_RECORD_MODE_FIR_MAPPING_CH2_FOR_6_MODE,
    //hd_rec device mode mapping
    DEFAULT_HD_RECORD_MODE_DEV_MAPPING,
    DUMMY_HD_RECORD_MODE_DEV_MAPPING_FOR_6_MODE,
    //hd_rec_map_to_input_src
    DEFAULT_HD_RECORD_MODE_INPUT_SRC_MAPPING,
    DUMMY_HD_RECORD_MODE_INPUT_SRC_MAPPING_FOR_6_MODE,
    //hd_rec_map_to_stereo_flag
    DEFAULT_HD_RECORD_MODE_STEREO_FLAGS,
    DUMMY_HD_RECORD_MODE_STEREO_FLAGS_FOR_6_MODE
};

AUDIO_HD_RECORD_SCENE_TABLE_STRUCT Hd_Recrod_Scene_Table_default = {
    DEFAULT_HD_RECORD_NUM_VOICE_SCENES,
    DEFAULT_HD_RECORD_NUM_VIDEO_SCENES,
    DEFAULT_HD_RECORD_VOICE_SCENE_MODE_0,
    DEFAULT_HD_RECORD_VOICE_SCENE_MODE_1,
    DEFAULT_HD_RECORD_VOICE_SCENE_MODE_2,
    DEFAULT_HD_RECORD_VIDEO_SCENE_MODE_0,
    DEFAULT_HD_RECORD_VIDEO_SCENE_MODE_1,
    DEFAULT_HD_RECORD_VIDEO_SCENE_MODE_2,
    DEFAULT_HD_RECORD_VIDEO_SCENE_MODE_3,
    DUMMY_HD_RECORD_SCENE_MODE,
    DUMMY_HD_RECORD_SCENE_MODE,
    DUMMY_HD_RECORD_SCENE_MODE
};
#endif


