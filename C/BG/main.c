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
  //!< インベーダー
  PIX2(0, 0), PIX2(0, 1), PIX2(1, 0), PIX2(0, 0),
  PIX2(0, 0), PIX2(1, 1), PIX2(1, 1), PIX2(0, 0),
  PIX2(0, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 0),
  PIX2(1, 1), PIX2(0, 1), PIX2(1, 0), PIX2(1, 1),
  PIX2(1, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(0, 0), PIX2(1, 0), PIX2(0, 1), PIX2(0, 0),
  PIX2(0, 1), PIX2(0, 1), PIX2(1, 0), PIX2(1, 0),
  PIX2(1, 0), PIX2(1, 0), PIX2(0, 1), PIX2(0, 1),
  //!< りんご
  PIX2(0, 0), PIX2(0, 0), PIX2(1, 1), PIX2(0, 0),
  PIX2(0, 0), PIX2(0, 0), PIX2(1, 0), PIX2(0, 0),
  PIX2(0, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 0),
  PIX2(1, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(1, 0), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(1, 0), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(1, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(0, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 0),
  //!< カラーバー0
  PIX2( 0,  0), PIX2( 0,  0), PIX2( 0,  0), PIX2( 0,  0),
  PIX2( 1,  1), PIX2( 1,  1), PIX2( 1,  1), PIX2( 1,  1),
  PIX2( 2,  2), PIX2( 2,  2), PIX2( 2,  2), PIX2( 2,  2),
  PIX2( 3,  3), PIX2( 3,  3), PIX2( 3,  3), PIX2( 3,  3),
  PIX2( 4,  4), PIX2( 4,  4), PIX2( 4,  4), PIX2( 4,  4),
  PIX2( 5,  5), PIX2( 5,  5), PIX2( 5,  5), PIX2( 5,  5),
  PIX2( 6,  6), PIX2( 6,  6), PIX2( 6,  6), PIX2( 6,  6),
  PIX2( 7,  7), PIX2( 7,  7), PIX2( 7,  7), PIX2( 7,  7),
  //!< カラーバー1
  PIX2( 8,  8), PIX2( 8,  8), PIX2( 8,  8), PIX2( 8,  8),
  PIX2( 9,  9), PIX2( 9,  9), PIX2( 9,  9), PIX2( 9,  9),
  PIX2(10, 10), PIX2(10, 10), PIX2(10, 10), PIX2(10, 10),
  PIX2(11, 11), PIX2(11, 11), PIX2(11, 11), PIX2(11, 11),
  PIX2(12, 12), PIX2(12, 12), PIX2(12, 12), PIX2(12, 12),
  PIX2(13, 13), PIX2(13, 13), PIX2(13, 13), PIX2(13, 13),
  PIX2(14, 14), PIX2(14, 14), PIX2(14, 14), PIX2(14, 14),
  PIX2(15, 15), PIX2(15, 15), PIX2(15, 15), PIX2(15, 15),
};
enum {
  PCG0_DATA = 0,  //!< インベーダー
  PCG1_DATA = 32, //!< りんご
  PCG2_DATA = 64, //!< カラーバー0
  PCG3_DATA = 96, //!< カラーバー1
};
enum {
  //!< デフォルトでは BG 用データは 64 から?
  PCG0_ID = 64,  //!< インベーダー
  PCG1_ID = 65,  //!< りんご
  PCG2_ID = 66,  //!< カラーバー0
  PCG3_ID = 67,  //!< カラーバー1
};

uint64_t PALData[PAL_BLOCK_COUNT][PAL_COLOR_COUNT];
uint8_t	PCGData[PCG_16X16_COUNT][PCG_16X16_SIZE];

//#define DRAW_PALETTE

void main()
{
  //!< CRT mode
  const int PrevCRT = CRTMOD(-1);
  CRTMOD(CRT_MODE_HIGH_256X256_T16G16_512);
  //!< カーソルオフ (Cursor off)
  B_CUROFF();
  //!< グラフィッククリア (Clear graphics)
  G_CLR_ON(); 
  SP_INIT();
  
  //!< パレット (Palette)
  SPALET( 1, 1, COL_YELLOW);
  SPALET( 1, 2, COL_RED);
  #ifdef DRAW_PALETTE
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
  #endif

  //!< PCG
  SP_CGCLR(0);
  SP_DEFCG(PCG0_ID, PCG_PAT_8X8, &PCGData8X8[PCG0_DATA]);
  SP_DEFCG(PCG1_ID, PCG_PAT_8X8, &PCGData8X8[PCG1_DATA]);
  #ifdef DRAW_PALETTE
  SP_DEFCG(PCG2_ID, PCG_PAT_8X8, &PCGData8X8[PCG2_DATA]);
  SP_DEFCG(PCG3_ID, PCG_PAT_8X8, &PCGData8X8[PCG3_DATA]);
  #endif

  //!< スプライト (BGのみでもオンにしないとダメみたい) (Sprite need SP_ON(), even if BG only)
  SP_ON(); 

  //!< BG
  int BG0Pal = 1, BG1Pal = 2;
  int Bg0X = 0, Bg0Y = 0;
  int Bg1X = 0, Bg1Y = 0;
  {
    //!< BG コントロールレジスタ0、テキストページ0 オン (BG0 ON)
    BGCTRLST(0, 0, BG_ON);
    //!< BG コントロールレジスタ1、テキストページ1 オン (BG1 ON)
	  BGCTRLST(1, 1, BG_ON);

    //!< テキストーページをパターンでクリア
    BGTEXTCL(0, CODE(FLIP_NONE, 0, 0)); 
    BGTEXTCL(1, CODE(FLIP_NONE, 0, 0));
    //!< BG のマップを作成
    for (int i = 0; i < BG_HEIGHT; ++i) {
      for (int j = 0; j < BG_WIDTH; ++j) {
        if((i + j) & 1)    BGTEXTST(0, j, i, CODE(FLIP_NONE, BG0Pal, PCG0_ID)); 
        if(!((i + j) & 1)) BGTEXTST(1, j, i, CODE(FLIP_NONE, BG1Pal, PCG1_ID)); 
      }
    }

    #ifdef DRAW_PALETTE
    //!< パレットを描画 (Draw palette)
    for (int j = 0; j < BG_WIDTH; ++j) {
      BGTEXTST(0, j, 30, CODE(FLIP_NONE, 2, PCG2_ID)); 
      BGTEXTST(0, j, 31, CODE(FLIP_NONE, 2, PCG3_ID)); 
    }
    #endif
  }

  int TAB_PREV = 0;
  while (1)
  {      
    if(ESC_ON) { break; }
    
    Bg0X = ++Bg0X & 0x3ff;
    Bg1Y = ++Bg1Y & 0x3ff;
    BGSCRLST(BG_ON_VBLANK | 0, Bg0X, Bg0Y);
    BGSCRLST(BG_ON_VBLANK | 1, Bg1X, Bg1Y);

    //!< BG 切替え
    int TAB_CUR = TAB_ON;
    if(TAB_PUSH(TAB_PREV)) {
      if(BGCTRLGT(0)){
        BGCTRLST(0, 0, BG_OFF);
	      BGCTRLST(1, 1, BG_ON);
      } else {
        BGCTRLST(0, 0, BG_ON);
	      BGCTRLST(1, 1, BG_OFF);
      }
    }
    TAB_PREV = TAB_CUR;

    //!< BG 全表示
    if(SPACE_ON) {
      BGCTRLST(0, 0, BG_ON);
	    BGCTRLST(1, 1, BG_ON);
    }

    B_LOCATE(0, 0);
    printf("BG0 %03d, %03d\n", Bg0X, Bg0Y);
    printf("BG1 %03d, %03d\n", Bg1X, Bg1Y);
  }
  
  SP_OFF();

  //!< カーソルオン (Cursor on)
  B_CURON();
  //!< CRT を戻す
  CRTMOD(PrevCRT);
}
