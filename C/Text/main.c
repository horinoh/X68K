#include <stdio.h>
#include <iocslib.h>
#include <stdint.h>

#include "Common.h"
#include "Text.h"
#include "Interrupt.h"

//#define FILL16X16
#ifdef FILL16X16 
//0,0,0,0,0,1,1,1, 1,1,0,0,0,0,0,0,
//0,0,0,0,1,1,1,1, 1,1,1,1,1,0,0,0,
//0,0,0,0,3,3,3,2, 2,3,2,0,0,0,0,0,
//0,0,0,3,2,3,2,2, 2,3,2,2,2,0,0,0,
//0,0,0,3,2,3,3,2, 2,2,3,2,2,2,0,0,
//0,0,0,3,3,2,2,2, 2,3,3,3,3,0,0,0,
//0,0,0,0,0,2,2,2, 2,2,2,2,0,0,0,0,
//0,0,0,0,3,3,1,3, 3,3,0,0,0,0,0,0,

//0,0,0,3,3,3,1,3, 3,1,3,3,3,0,0,0,
//0,0,3,3,3,3,1,1, 1,1,3,3,3,3,0,0,
//0,0,2,2,3,1,2,1, 1,2,1,3,2,2,0,0,
//0,0,2,2,2,1,1,1, 1,1,1,2,2,2,0,0,
//0,0,2,2,1,1,1,1, 1,1,1,1,2,2,0,0,
//0,0,0,0,1,1,1,0, 0,1,1,1,0,0,0,0,
//0,0,0,3,3,3,0,0, 0,0,3,3,3,0,0,0,
//0,0,3,3,3,3,0,0, 0,0,3,3,3,3,0,0,

const uint8_t TextData[][16][2] = {
  {
    { PLANE0(0,0,0,0,0,1,1,1), PLANE0(1,1,0,0,0,0,0,0) },
    { PLANE0(0,0,0,0,1,1,1,1), PLANE0(1,1,1,1,1,0,0,0) },
    { PLANE0(0,0,0,0,3,3,3,2), PLANE0(2,3,2,0,0,0,0,0) },
    { PLANE0(0,0,0,3,2,3,2,2), PLANE0(2,3,2,2,2,0,0,0) },
    { PLANE0(0,0,0,3,2,3,3,2), PLANE0(2,2,3,2,2,2,0,0) },
    { PLANE0(0,0,0,3,3,2,2,2), PLANE0(2,3,3,3,3,0,0,0) },
    { PLANE0(0,0,0,0,0,2,2,2), PLANE0(2,2,2,2,0,0,0,0) },
    { PLANE0(0,0,0,0,3,3,1,3), PLANE0(3,3,0,0,0,0,0,0) },

    { PLANE0(0,0,0,3,3,3,1,3), PLANE0(3,1,3,3,3,0,0,0) },
    { PLANE0(0,0,3,3,3,3,1,1), PLANE0(1,1,3,3,3,3,0,0) },
    { PLANE0(0,0,2,2,3,1,2,1), PLANE0(1,2,1,3,2,2,0,0) },
    { PLANE0(0,0,2,2,2,1,1,1), PLANE0(1,1,1,2,2,2,0,0) },
    { PLANE0(0,0,2,2,1,1,1,1), PLANE0(1,1,1,1,2,2,0,0) },
    { PLANE0(0,0,0,0,1,1,1,0), PLANE0(0,1,1,1,0,0,0,0) },
    { PLANE0(0,0,0,3,3,3,0,0), PLANE0(0,0,3,3,3,0,0,0) },
    { PLANE0(0,0,3,3,3,3,0,0), PLANE0(0,0,3,3,3,3,0,0) },
  },
  {
    { PLANE1(0,0,0,0,0,1,1,1), PLANE1(1,1,0,0,0,0,0,0) },
    { PLANE1(0,0,0,0,1,1,1,1), PLANE1(1,1,1,1,1,0,0,0) },
    { PLANE1(0,0,0,0,3,3,3,2), PLANE1(2,3,2,0,0,0,0,0) },
    { PLANE1(0,0,0,3,2,3,2,2), PLANE1(2,3,2,2,2,0,0,0) },
    { PLANE1(0,0,0,3,2,3,3,2), PLANE1(2,2,3,2,2,2,0,0) },
    { PLANE1(0,0,0,3,3,2,2,2), PLANE1(2,3,3,3,3,0,0,0) },
    { PLANE1(0,0,0,0,0,2,2,2), PLANE1(2,2,2,2,0,0,0,0) },
    { PLANE1(0,0,0,0,3,3,1,3), PLANE1(3,3,0,0,0,0,0,0) },

    { PLANE1(0,0,0,3,3,3,1,3), PLANE1(3,1,3,3,3,0,0,0) },
    { PLANE1(0,0,3,3,3,3,1,1), PLANE1(1,1,3,3,3,3,0,0) },
    { PLANE1(0,0,2,2,3,1,2,1), PLANE1(1,2,1,3,2,2,0,0) },
    { PLANE1(0,0,2,2,2,1,1,1), PLANE1(1,1,1,2,2,2,0,0) },
    { PLANE1(0,0,2,2,1,1,1,1), PLANE1(1,1,1,1,2,2,0,0) },
    { PLANE1(0,0,0,0,1,1,1,0), PLANE1(0,1,1,1,0,0,0,0) },
    { PLANE1(0,0,0,3,3,3,0,0), PLANE1(0,0,3,3,3,0,0,0) },
    { PLANE1(0,0,3,3,3,3,0,0), PLANE1(0,0,3,3,3,3,0,0) },
  },
  {
    { PLANE2(0,0,0,0,0,1,1,1), PLANE2(1,1,0,0,0,0,0,0) },
    { PLANE2(0,0,0,0,1,1,1,1), PLANE2(1,1,1,1,1,0,0,0) },
    { PLANE2(0,0,0,0,3,3,3,2), PLANE2(2,3,2,0,0,0,0,0) },
    { PLANE2(0,0,0,3,2,3,2,2), PLANE2(2,3,2,2,2,0,0,0) },
    { PLANE2(0,0,0,3,2,3,3,2), PLANE2(2,2,3,2,2,2,0,0) },
    { PLANE2(0,0,0,3,3,2,2,2), PLANE2(2,3,3,3,3,0,0,0) },
    { PLANE2(0,0,0,0,0,2,2,2), PLANE2(2,2,2,2,0,0,0,0) },
    { PLANE2(0,0,0,0,3,3,1,3), PLANE2(3,3,0,0,0,0,0,0) },

    { PLANE2(0,0,0,3,3,3,1,3), PLANE2(3,1,3,3,3,0,0,0) },
    { PLANE2(0,0,3,3,3,3,1,1), PLANE2(1,1,3,3,3,3,0,0) },
    { PLANE2(0,0,2,2,3,1,2,1), PLANE2(1,2,1,3,2,2,0,0) },
    { PLANE2(0,0,2,2,2,1,1,1), PLANE2(1,1,1,2,2,2,0,0) },
    { PLANE2(0,0,2,2,1,1,1,1), PLANE2(1,1,1,1,2,2,0,0) },
    { PLANE2(0,0,0,0,1,1,1,0), PLANE2(0,1,1,1,0,0,0,0) },
    { PLANE2(0,0,0,3,3,3,0,0), PLANE2(0,0,3,3,3,0,0,0) },
    { PLANE2(0,0,3,3,3,3,0,0), PLANE2(0,0,3,3,3,3,0,0) },
  },
  {
    { PLANE3(0,0,0,0,0,1,1,1), PLANE3(1,1,0,0,0,0,0,0) },
    { PLANE3(0,0,0,0,1,1,1,1), PLANE3(1,1,1,1,1,0,0,0) },
    { PLANE3(0,0,0,0,3,3,3,2), PLANE3(2,3,2,0,0,0,0,0) },
    { PLANE3(0,0,0,3,2,3,2,2), PLANE3(2,3,2,2,2,0,0,0) },
    { PLANE3(0,0,0,3,2,3,3,2), PLANE3(2,2,3,2,2,2,0,0) },
    { PLANE3(0,0,0,3,3,2,2,2), PLANE3(2,3,3,3,3,0,0,0) },
    { PLANE3(0,0,0,0,0,2,2,2), PLANE3(2,2,2,2,0,0,0,0) },
    { PLANE3(0,0,0,0,3,3,1,3), PLANE3(3,3,0,0,0,0,0,0) },

    { PLANE3(0,0,0,3,3,3,1,3), PLANE3(3,1,3,3,3,0,0,0) },
    { PLANE3(0,0,3,3,3,3,1,1), PLANE3(1,1,3,3,3,3,0,0) },
    { PLANE3(0,0,2,2,3,1,2,1), PLANE3(1,2,1,3,2,2,0,0) },
    { PLANE3(0,0,2,2,2,1,1,1), PLANE3(1,1,1,2,2,2,0,0) },
    { PLANE3(0,0,2,2,1,1,1,1), PLANE3(1,1,1,1,2,2,0,0) },
    { PLANE3(0,0,0,0,1,1,1,0), PLANE3(0,1,1,1,0,0,0,0) },
    { PLANE3(0,0,0,3,3,3,0,0), PLANE3(0,0,3,3,3,0,0,0) },
    { PLANE3(0,0,3,3,3,3,0,0), PLANE3(0,0,3,3,3,3,0,0) },
  },
};
#else
//0, 0, 0, 1, 1, 0, 0, 0,
//0, 0, 1, 1, 1, 1, 0, 0,
//0, 1, 1, 1, 1, 1, 1, 0,
//1, 1, 0, 1, 1, 0, 1, 1,
//1, 1, 1, 1, 1, 1, 1, 1,
//0, 0, 1, 0, 0, 1, 0, 0,
//0, 1, 0, 1, 1, 0, 1, 0,
//1, 0, 1, 0, 0, 1, 0, 1,
const uint8_t TextData[][8] = {
  {
    PLANE0(0, 0, 0, 1, 1, 0, 0, 0),
    PLANE0(0, 0, 1, 1, 1, 1, 0, 0),
    PLANE0(0, 1, 1, 1, 1, 1, 1, 0),
    PLANE0(1, 1, 0, 1, 1, 0, 1, 1),
    PLANE0(1, 1, 1, 1, 1, 1, 1, 1),
    PLANE0(0, 0, 1, 0, 0, 1, 0, 0),
    PLANE0(0, 1, 0, 1, 1, 0, 1, 0),
    PLANE0(1, 0, 1, 0, 0, 1, 0, 1),
  },
  {
    PLANE1(0, 0, 0, 1, 1, 0, 0, 0),
    PLANE1(0, 0, 1, 1, 1, 1, 0, 0),
    PLANE1(0, 1, 1, 1, 1, 1, 1, 0),
    PLANE1(1, 1, 0, 1, 1, 0, 1, 1),
    PLANE1(1, 1, 1, 1, 1, 1, 1, 1),
    PLANE1(0, 0, 1, 0, 0, 1, 0, 0),
    PLANE1(0, 1, 0, 1, 1, 0, 1, 0),
    PLANE1(1, 0, 1, 0, 0, 1, 0, 1),
 },
  {
    PLANE2(0, 0, 0, 1, 1, 0, 0, 0),
    PLANE2(0, 0, 1, 1, 1, 1, 0, 0),
    PLANE2(0, 1, 1, 1, 1, 1, 1, 0),
    PLANE2(1, 1, 0, 1, 1, 0, 1, 1),
    PLANE2(1, 1, 1, 1, 1, 1, 1, 1),
    PLANE2(0, 0, 1, 0, 0, 1, 0, 0),
    PLANE2(0, 1, 0, 1, 1, 0, 1, 0),
    PLANE2(1, 0, 1, 0, 0, 1, 0, 1),
 },
 {
    PLANE3(0, 0, 0, 1, 1, 0, 0, 0),
    PLANE3(0, 0, 1, 1, 1, 1, 0, 0),
    PLANE3(0, 1, 1, 1, 1, 1, 1, 0),
    PLANE3(1, 1, 0, 1, 1, 0, 1, 1),
    PLANE3(1, 1, 1, 1, 1, 1, 1, 1),
    PLANE3(0, 0, 1, 0, 0, 1, 0, 0),
    PLANE3(0, 1, 0, 1, 1, 0, 1, 0),
    PLANE3(1, 0, 1, 0, 0, 1, 0, 1),
 },
};
#endif

void main()
{ 
  const int PrevCRT = CRTMOD(-1);
  CRTMOD(CRT_MODE_HIGH_512X512_T16G16_1024);
  B_CUROFF();
  B_CLR_AL();

  //TPALET2(0, COL_WHITE);
  TPALET2(1, COL_RED);
  TPALET2(2, COL_YELLOW);
  TPALET2(3, COL_GRAY);

  //!< ライン
  struct XLINEPTR XLine = { .vram_page = 0, .x = 32, .y = 32, .x1 = 32+8, .line_style = 0xf7f7 };
  TXXLINE(&XLine);
  struct YLINEPTR YLine = { .vram_page = 0, .x = 32 + 16, .y = 32 + 8, .y1 = 32+8, .line_style = 0xf7f7 };
  TXYLINE(&YLine);
  //struct TLINEPTR Line = { .vram_page = 0, .x = 32, .y = 32, .x1 = 32+8, .y1 = 32+8, .line_style = 0xf7f7 };
  //TXLINE(&Line);
  //!< ボックス
  struct TBOXPTR Box = { .vram_page = 0, .x = 64, .y = 64, .x1 = 32, .y1 = 32, .line_style = 0x7f7f };
  TXBOX(&Box);

  //!< フィル
#ifdef FILL16X16
  const int Count = TEXT_WIDTH / 16;
  for(int i = 0;i < COUNTOF(TextData);++i) {
    for(int j = 0; j < COUNTOF(TextData[0]);++j) {
      for(int k = 0; k < COUNTOF(TextData[0][0]);++k) {
        for(int l = 0; l < Count;++l) {
          struct TXFILLPTR Fill = { .vram_page = i, .x = k * 8 + l * 16, .y = j, .x1 = 8, .y1 = 1, .fill_patn = TextData[i][j][k] };
          TXFILL(&Fill);
        }
      }
    }
  }
  const uint8_t Height = 16;
#else
  for(int i = 0;i < COUNTOF(TextData);++i) {
    for(int j = 0; j < COUNTOF(TextData[0]);++j) {
      struct TXFILLPTR Fill = { .vram_page = i, .x = 0, .y = j, .x1 = 512, .y1 = 1, .fill_patn = TextData[i][j] };
      TXFILL(&Fill);
    }
  }
  const uint8_t Height = 8;
#endif

  const uint8_t RasterUnitCount = Height / 4;
  //!< ラスタコピー
  //!<    単位は 4 ラスタ単位
  TXRASCPY(RAS_SRC_DST(0, 32 + RasterUnitCount * 0), RasterUnitCount, RAS_PLANE_ALL | RAS_DIR_INC);
  TXRASCPY(RAS_SRC_DST(0, 32 + RasterUnitCount * 1), RasterUnitCount, RAS_PLANE0 | RAS_DIR_INC);
  TXRASCPY(RAS_SRC_DST(0, 32 + RasterUnitCount * 2), RasterUnitCount, RAS_PLANE1 | RAS_DIR_INC);
  TXRASCPY(RAS_SRC_DST(0, 32 + RasterUnitCount * 3), RasterUnitCount, RAS_PLANE2 | RAS_DIR_INC);
  TXRASCPY(RAS_SRC_DST(0, 32 + RasterUnitCount * 4), RasterUnitCount, RAS_PLANE3 | RAS_DIR_INC);
  for(int i = 0;i<20;++i){
    TXRASCPY(RAS_SRC_DST(0, 32 + RasterUnitCount * (i + 5)), RasterUnitCount, RAS_PLANE_ALL | RAS_DIR_INC);
  }

 VDISPST((uint8_t*)OnVBlank, ON_VBLANK, 1);

  int TAB_PREV = 0;
  while (1)
  {      
    VWait(1);

    if(ESC_ON) { break; }

    int TAB_CUR = TAB_ON;
    if(TAB_PUSH(TAB_PREV)) {
      //!< 色が反転される
      struct TREVPTR Rev = { .vram_page = 0, .x = 0, .y = 0, .x1 = 512, .y1 = 512 };
      TXREV(&Rev);
    }
    TAB_PREV = TAB_CUR;
  }
  
  B_CLR_AL();
  B_CURON();
  CRTMOD(PrevCRT);
}

