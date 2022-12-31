#pragma once

enum {
    SAMPLING_3_9KHZ,
    SAMPLING_5_2KHZ,
    SAMPLING_7_8KHZ,
    SAMPLING_10_4KHZ,
    SAMPLING_15_6KHZ,
};
enum {
    ADPCM_MODE_CUT,
    ADPCM_MODE_L,
    ADPCM_MODE_R,
    ADPCM_MODE_LR,
};
#define ADPCM_MODE(_Samp, _Mode) ((_Samp << 8) + _Mode)

enum {
    ADPCM_FINISH,
    ADPCM_ABORT,
    ADPCM_RESTART,
};

enum {
    ADPCM_NONE = 0x0,
    ADPCM_OUT = 0x2,
    ADPCM_INP = 0x4,
    ADPCM_AOT = 0x12,
    ADPCM_AIN = 0x14,
    ADPCM_LOT = 0x22,
    ADPCM_LIN = 0x24,
};

enum {
    OPM_TIMER_B_OVERFLOW = 1 << 0,
    OPM_TIMER_A_OVERFLOW = 1 << 1,
    OPM_BUSY = 1 << 7,
};

//!< ZMUSIC
#define ZM_HOUR(_Time) ((_Time & 0x00ff0000) >> 16)
#define ZM_MiNUTE(_Time) ((_Time & 0x0000ff00) >> 8)
#define ZM_SECOND(_Time) (_Time & 0x000000ff)

#define ZM_DEV_FM    0x0000
#define ZM_DEV_ADPCM 0x0001
#define ZM_DEV_MIDI1 0x8000
#define ZM_DEV_MIDI2 0x8001
#define ZM_DEV_MIDI3 0x8002
#define ZM_DEVICE(_Dev, _Ch) (((_Dev & 0xffff) << 16) | (_Ch & 0xffff))
#define ZM_DEV(_ChId) ((_ChId & 0xffff0000) >> 16)
#define ZM_CHANNEL(_ChId) (_ChId & 0xffff)

//!< Return value of zm_tempo(), zm_set_timer_value(), ...
#define ZM_TIMER(_Val) ((_Val & 0xffff0000) >> 16)
#define ZM_TEMPO(_Val) (_Val & 0x0000ffff)
