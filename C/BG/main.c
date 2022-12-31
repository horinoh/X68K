#include <stdio.h>
#include <stdint.h>
#include <iocslib.h>

#include "Common.h"
#include "Palette.h"
#include "PCG.h"
#include "BG.h"
#include "Joy.h"

//0, 0, 0, 1, 1, 0, 0, 0,
//0, 0, 1, 1, 1, 1, 0, 0,
//0, 1, 1, 1, 1, 1, 1, 0,
//1, 1, 0, 1, 1, 0, 1, 1,
//1, 1, 1, 1, 1, 1, 1, 1,
//0, 0, 1, 0, 0, 1, 0, 0,
//0, 1, 0, 1, 1, 0, 1, 0,
//1, 0, 1, 0, 0, 1, 0, 1,

//0, 0, 0, 0, 1, 1, 0, 0,
//0, 0, 0, 0, 1, 0, 0, 0,
//0, 1, 1, 1, 1, 1, 1, 0,
//1, 1, 1, 1, 1, 1, 1, 1,
//1, 0, 1, 1, 1, 1, 1, 1,
//1, 0, 1, 1, 1, 1, 1, 1,
//1, 1, 1, 1, 1, 1, 1, 1,
//0, 1, 1, 1, 1, 1, 1, 0,
uint8_t PCGData8X8[] = {
  PIX2(0, 0), PIX2(0, 1), PIX2(1, 0), PIX2(0, 0),
  PIX2(0, 0), PIX2(1, 1), PIX2(1, 1), PIX2(0, 0),
  PIX2(0, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 0),
  PIX2(1, 1), PIX2(0, 1), PIX2(1, 0), PIX2(1, 1),
  PIX2(1, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(0, 0), PIX2(1, 0), PIX2(0, 1), PIX2(0, 0),
  PIX2(0, 1), PIX2(0, 1), PIX2(1, 0), PIX2(1, 0),
  PIX2(1, 0), PIX2(1, 0), PIX2(0, 1), PIX2(0, 1),

  PIX2(0, 0), PIX2(0, 0), PIX2(1, 1), PIX2(0, 0),
  PIX2(0, 0), PIX2(0, 0), PIX2(1, 0), PIX2(0, 0),
  PIX2(0, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 0),
  PIX2(1, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(1, 0), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(1, 0), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(1, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(0, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 0),

  PIX2( 0,  0), PIX2( 0,  0), PIX2( 0,  0), PIX2( 0,  0),
  PIX2( 1,  1), PIX2( 1,  1), PIX2( 1,  1), PIX2( 1,  1),
  PIX2( 2,  2), PIX2( 2,  2), PIX2( 2,  2), PIX2( 2,  2),
  PIX2( 3,  3), PIX2( 3,  3), PIX2( 3,  3), PIX2( 3,  3),
  PIX2( 4,  4), PIX2( 4,  4), PIX2( 4,  4), PIX2( 4,  4),
  PIX2( 5,  5), PIX2( 5,  5), PIX2( 5,  5), PIX2( 5,  5),
  PIX2( 6,  6), PIX2( 6,  6), PIX2( 6,  6), PIX2( 6,  6),
  PIX2( 7,  7), PIX2( 7,  7), PIX2( 7,  7), PIX2( 7,  7),

  PIX2( 8,  8), PIX2( 8,  8), PIX2( 8,  8), PIX2( 8,  8),
  PIX2( 9,  9), PIX2( 9,  9), PIX2( 9,  9), PIX2( 9,  9),
  PIX2(10, 10), PIX2(10, 10), PIX2(10, 10), PIX2(10, 10),
  PIX2(11, 11), PIX2(11, 11), PIX2(11, 11), PIX2(11, 11),
  PIX2(12, 12), PIX2(12, 12), PIX2(12, 12), PIX2(12, 12),
  PIX2(13, 13), PIX2(13, 13), PIX2(13, 13), PIX2(13, 13),
  PIX2(14, 14), PIX2(14, 14), PIX2(14, 14), PIX2(14, 14),
  PIX2(15, 15), PIX2(15, 15), PIX2(15, 15), PIX2(15, 15),
};

uint64_t PALData[PAL_BLOCK_COUNT][PAL_COLOR_COUNT];
uint8_t	PCGData[PCG_16X16_COUNT][PCG_16X16_SIZE];

void main()
{
  //!< CRT mode
  const int PrevCRT = CRTMOD(-1);
  CRTMOD(MODE_512_256X256_C16_P4_31KHZ);
  //!< Cursor off
  B_CUROFF();
  //!< Clear graphics
  G_CLR_ON(); 
  SP_INIT();
  
  //!< Palette
  SPALET(1, 1, COL_YELLOW);

  SPALET( 1, 2, COL_RED);
  SPALET( 2, 2, COL_GREEN);
  SPALET( 3, 2, COL_BLUE);
  SPALET( 4, 2, COL_YELLOW);
  SPALET( 5, 2, COL_MAGENTA);
  SPALET( 6, 2, COL_WHITE);
  SPALET( 7, 2, COL_GRAY);
  SPALET( 8, 2, COL_PURPLE);
  SPALET( 9, 2, COL_BLACK);
  SPALET(10, 2, COL_NAVY);
  SPALET(11, 2, COL_AQUA);
  SPALET(12, 2, COL_MAROON);
  SPALET(13, 2, COL_LIME);
  SPALET(14, 2, COL_SILVER);
  SPALET(15, 2, COL_OLIVE);

  //!< PCG
  SP_CGCLR(0);
  SP_DEFCG(128, PCG_PAT_8X8, &PCGData8X8[0]);
  SP_DEFCG(129, PCG_PAT_8X8, &PCGData8X8[32]);
  SP_DEFCG(130, PCG_PAT_8X8, &PCGData8X8[64]);
  SP_DEFCG(131, PCG_PAT_8X8, &PCGData8X8[96]);

  //!< Sprite (Need SP_ON(), even if BG only)
  SP_ON(); 

  //!< BG
  int BG0PCG = 128, BG1PCG = 129;
  int BG0Pal = 1, BG1Pal = 2;
  int Bg0X = 0, Bg0Y = 0;
  int Bg1X = 0, Bg1Y = 0;
  {
    //!< BG0 PAGE0 ONOFF
    BGCTRLST(0, 0, BG_ON);
    //!< BG1 PAGE1 ONOFF
	  BGCTRLST(1, 1, BG_ON);

    //!< Clear map
    BGTEXTCL(0, 0); 
    BGTEXTCL(1, 0);
    //!< Set map
    for (int i = 0; i < BG_HEIGHT; ++i) {
      for (int j = 0; j < BG_WIDTH; ++j) {
        if(i & 1) BGTEXTST(0, j, i, CODE(FLIP_NONE, BG0Pal, BG0PCG)); 
        if(j & 1) BGTEXTST(1, j, i, CODE(FLIP_NONE, BG1Pal, BG1PCG)); 
      }
    }

    #if 0
    //!< Draw palette
    for (int j = 0; j < BG_WIDTH; ++j) {
      BGTEXTST(0, j, 30, CODE(FLIP_NONE, 2, 130)); 
      BGTEXTST(0, j, 31, CODE(FLIP_NONE, 2, 131)); 
    }
    #endif

    //!< BG0 SCROLL
    BGSCRLST(0, Bg0X, Bg0Y);
    //!M BG1 SCROLL 
    BGSCRLST(1, Bg1X, Bg1Y);
  }

  while (1)
  {      
    if(ESC_ON) { break; }
      
    const int Joy = JOYGET(0);
    if(!(Joy & JOY_UP)) { }
    if(!(Joy & JOY_DOWN)) { }
    if(!(Joy & JOY_LEFT)) { }
    if(!(Joy & JOY_RIGHT)) { }
    if(UP_ON) { }
    if(DOWN_ON) { }
    if(LEFT_ON) { }
    if(RIGHT_ON) { }

    Bg0X = ++Bg0X & 0x3ff;
    Bg1Y = ++Bg1Y & 0x3ff;
    BGSCRLST(ON_VSYNC | 0, Bg0X, Bg0Y);
    BGSCRLST(ON_VSYNC | 1, Bg1X, Bg1Y);

    if(TAB_ON) {
      if(BGCTRLGT(0)){
        BGCTRLST(0, 0, BG_OFF);
	      BGCTRLST(1, 1, BG_ON);
      } else {
        BGCTRLST(0, 0, BG_ON);
	      BGCTRLST(1, 1, BG_OFF);
      }
    }
    if(SPACE_ON) {
      BGCTRLST(0, 0, BG_ON);
	    BGCTRLST(1, 1, BG_ON);
    }

    //SPALET(ON_VSYNC | 0, 0, XXX);

    B_LOCATE(0, 0);
    printf("BG0 %03d, %03d\n", Bg0X, Bg0Y);
    printf("BG1 %03d, %03d\n", Bg1X, Bg1Y);
  }
  
  SP_OFF();

  //!< Cursor on
  B_CURON();
  //!< CRT mode
  CRTMOD(PrevCRT);
}
