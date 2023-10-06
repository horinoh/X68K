#pragma once

#include <stdint.h>

//!< BGSCRLST() 用
enum {
  BG_ON_VBLANK = 0,
  BG_IMMEDIATE = (1 << 31),
};

//!< 256 x 256 モード
//!<    8 x 8 タイル
//!<    表示画面 32 x 32 タイル = 256 x 256
//!<    実画面   64 x 64 タイル = 512 x 512

//!< 512 x 512 モード
//!<    16 x 16 タイル
//!<    表示画面 32 x 32 タイル = 512 x 512
//!<    実画面   64 x 64 タイル = 1024 x 1024
enum {
    BG_DISP_WIDTH = 32,
    BG_DISP_HEIGHT = 32,

    BG_WIDTH = 64,
    BG_HEIGHT = 64,
};

int16_t BG_SCR_VAL(int16_t rhs) {
  while(rhs < 0) { rhs += 1024; }
  while(rhs > 1023) { rhs -= 1024; }
  return rhs;
}
#define SCR_VAL_KEEP -1