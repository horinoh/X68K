#include <stdio.h>
#include <iocslib.h>
#include <stdint.h>
#include <string.h>

#include "Common.h"
#include "Graphics.h"
#include "Interrupt.h"
#include "IOCS.h"

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

//!< 16 色の場合は uint16_t に 4 ドット格納される
uint16_t PalPattern[] = {
  DOT4U16(0,0,0,0), DOT4U16(0,1,1,1), DOT4U16(1,1,0,0), DOT4U16(0,0,0,0),
  DOT4U16(0,0,0,0), DOT4U16(1,1,1,1), DOT4U16(1,1,1,1), DOT4U16(1,0,0,0),
  DOT4U16(0,0,0,0), DOT4U16(3,3,3,2), DOT4U16(2,3,2,0), DOT4U16(0,0,0,0),
  DOT4U16(0,0,0,3), DOT4U16(2,3,2,2), DOT4U16(2,3,2,2), DOT4U16(2,0,0,0),
  DOT4U16(0,0,0,3), DOT4U16(2,3,3,2), DOT4U16(2,2,3,2), DOT4U16(2,2,0,0),
  DOT4U16(0,0,0,3), DOT4U16(3,2,2,2), DOT4U16(2,3,3,3), DOT4U16(3,0,0,0),
  DOT4U16(0,0,0,0), DOT4U16(0,2,2,2), DOT4U16(2,2,2,2), DOT4U16(0,0,0,0),
  DOT4U16(0,0,0,0), DOT4U16(3,3,1,3), DOT4U16(3,3,0,0), DOT4U16(0,0,0,0),

  DOT4U16(0,0,0,3), DOT4U16(3,3,1,3), DOT4U16(3,1,3,3), DOT4U16(3,0,0,0),
  DOT4U16(0,0,3,3), DOT4U16(3,3,1,1), DOT4U16(1,1,3,3), DOT4U16(3,3,0,0),
  DOT4U16(0,0,2,2), DOT4U16(3,1,2,1), DOT4U16(1,2,1,3), DOT4U16(2,2,0,0),
  DOT4U16(0,0,2,2), DOT4U16(2,1,1,1), DOT4U16(1,1,1,2), DOT4U16(2,2,0,0),
  DOT4U16(0,0,2,2), DOT4U16(1,1,1,1), DOT4U16(1,1,1,1), DOT4U16(2,2,0,0),
  DOT4U16(0,0,0,0), DOT4U16(1,1,1,0), DOT4U16(0,1,1,1), DOT4U16(0,0,0,0),
  DOT4U16(0,0,0,3), DOT4U16(3,3,0,0), DOT4U16(0,0,3,3), DOT4U16(3,0,0,0),
  DOT4U16(0,0,3,3), DOT4U16(3,3,0,0), DOT4U16(0,0,3,3), DOT4U16(3,3,0,0),
};

//!< 文字列表示用
char Str[8];
//!< ペイント系でバッファを必要とする機能がある (十分なサイズを用意しておけば大丈夫？)
uint8_t Buf[256];

enum {
  RED_IDX = 1,
  GREEN_IDX = 2,
  BLUE_IDX = 3,
  YELLOW_IDX = 4,
  WHITE_IDX = 5,
};
void DrawPage(int Page, int x, int y, int Color)
{
  //!< アクティブページを変更
  if(0 == APAGE(Page)) {
    //!< クリア
    WIPE();

    //!< 円
    struct CIRCLEPTR Circle = { .x = x, .y = y, .radius = 32, .color = Color, .start = 0, .end = 360, .ratio = 256 };
    CIRCLE(&Circle);
    //!< 点
    struct PSETPTR Pset = { .x = Circle.x, .y = Circle.y, .color = Circle.color };
    PSET(&Pset);

    //!< 塗りつぶし
    struct FILLPTR Fill = { .x1 = Circle.x - Circle.radius, .y1 = Circle.y + Circle.radius, .x2 = Circle.x + Circle.radius * 3 / 2, .y2 = Circle.y + Circle.radius * 3, .color = Circle.color  };
    FILL(&Fill);

    //!< 指定座標のパレット番号を調べる
    struct POINTPTR Point = { .x = Circle.x, .y = Circle.y };
    POINT(&Point);
    sprintf(Str, "%03d", Point.color);
    //!< パレット番号(文字列) を表示
    struct SYMBOLPTR Symbol = { .x1 = Circle.x - Circle.radius, .y1 = Circle.y + Circle.radius * 4, .string_address = Str, .mag_x = 1, .mag_y = 1, .color = Circle.color , .font_type = FONT12, .angle = ROT0 };
    SYMBOL(&Symbol);

    //!< 線
    struct LINEPTR Line = { .x1 = Circle.x - Circle.radius, .y1 = Circle.y + Circle.radius * 5 + 5, .x2 = Circle.x + Circle.radius, .y2 = Circle.y + Circle.radius * 6, .color = Circle.color, .linestyle = 0x5555 };
    LINE(&Line);

    //!< (境界線内側を)ペイント (バッファを使用)
    struct PAINTPTR Paint = { .x = Circle.x + 1, .y = Circle.y, .color = Color + 1, .buf_start = (UBYTE *)&Buf, .buf_end = (UBYTE *)&Buf[COUNTOF(Buf) - 1] };
    PAINT(&Paint);

    //!< #TODO
    // struct GETPTR Get = { .x1 = 32, .y1 = 32, .x2 = 64, .y2 = 64, .buf_start = (UBYTE *)&Buf, .buf_end = (UBYTE *)&Buf[COUNTOF(Buf) - 1] };
    // GETGRM(&Get);

    //!< #TODO
    // struct PUTPTR Put = { .x1 = 0, .y1 = 0, .x2 = 32, .y2 = 32, .buf_start = (UBYTE *)&Buf, .buf_end = (UBYTE *)&Buf[COUNTOF(Buf) - 1] };
    // PUTGRM(&Put);

    //!< (ペンカラーによる) ビットパターン描画
    {
      uint16_t Data[] = {
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,

        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
      };
      struct GPTRNPTR Pattern = { .x1 = 16, .y1 = 16, .fill_patn = 0xffff };
   
      //!< 「赤」でパターン描画
      PENCOLOR(RED_IDX);
      GPTRN(0, 128, &Pattern);

      //!< 「緑」でパターン描画 (バックカラー「白」指定)
      PENCOLOR(GREEN_IDX);
      BK_GPTRN(32, 128, WHITE_IDX, &Pattern);

      //!< 「青」でパターン描画 (拡大表示)
      PENCOLOR(BLUE_IDX);
      X_GPTRN(64, 128, 2, 2, &Pattern);
    }

    //!< (パレット使用による) パターン描画
    {
      //!< ヘッダ + データ分メモリを確保
      void* Top = malloc(sizeof(GPUTHEADER) + sizeof(PalPattern));
      //!< ヘッダ
      GPUTHEADER* Header = (GPUTHEADER*)Top;
      //!< ヘッダ作成
      Header->x1 = 16, Header->y1 = 16, Header->color_mode = GPUT_COLOR_16;
      //!< データ
      void* Data = Top + sizeof(GPUTHEADER);
      //!< データ作成
      memcpy(Data, PalPattern, sizeof(PalPattern));
      
      //!< パターンを描画
      GPUT(0, 64, Header);

      //!< パレット 0 を抜き色扱いとして、パターンを描画
      MASK_GPUT(16, 64, 0, Header);

      free(Top);
    }
  }
}
void ClearAllPage()
{
  APAGE(3); WIPE();
  APAGE(2); WIPE();
  APAGE(1); WIPE();
  APAGE(0); WIPE();
}
void DrawAllPage()
{
  DrawPage(0, 32, 32, 1);
  DrawPage(1, 32 + 32 * 2, 32, 2);
  DrawPage(2, 32 + 32 * 4, 32, 3);
  DrawPage(3, 32 + 32 * 6, 32, 4);
}
void DrawWindow(int LTx, int LTy, int RBx, int RBy, int Col)
{
  struct BOXPTR Box = { .x1 = LTx, .y1 = LTy, .x2 = RBx, .y2 = RBy, .color = Col, .linestyle = 0x9999 };
  BOX(&Box);
}

void main()
{
  const int PrevCRT = CRTMOD(-1);
  //!< グラフィック面 (ここでは 4面)
  //!<    4 面 512x512 16色
  //!<    2 面 512x512 256色
  CRTMOD(CRT_MODE_HIGH_256X256_T16G16_512);
  //CRTMOD(CRT_MODE_HIGH_256X256_T16G256_512);
  
  B_CUROFF();
  G_CLR_ON(); 

  //!< 全ページ表示
  if(0 == VPAGE(GP_ALL_PAGES_BIT)) {}
  
  HOME(0, 0, 0);

  //!< パレット番号
  //!<    16色モード [0, 15]
  //!<    256色モード [0, 255]
  //!<    65536色モード [0, 65535]
  GPALET(RED_IDX, COL_RED);
  GPALET(GREEN_IDX, COL_GREEN);
  GPALET(BLUE_IDX, COL_BLUE);
  GPALET(YELLOW_IDX, COL_YELLOW);
  GPALET(WHITE_IDX, COL_WHITE); 

  DrawAllPage();

  int WinX = 0, WinY = 0;
  int WinW = 255, WinH = 255;
  int UP_PREV = 0, DOWN_PREV = 0, LEFT_PREV = 0, RIGHT_PREV = 0;
  int SPACE_PREV = 0;
  int TAB_PREV = 0;
  int P_PREV = 0;

  //!< ページ毎のオンオフ切替え
  int TogglePages[] = { GP_ALL_PAGES_BIT, GP_PAGE0_BIT, GP_PAGE1_BIT, GP_PAGE2_BIT, GP_PAGE3_BIT };
  int TogglePageIndex = 0;

  //!< ページ毎のプライオリティ切替え
  int TogglePris[] = { GP_4PAGE_PRI(0, 1, 2, 3), GP_4PAGE_PRI(0, 2, 1, 3), GP_4PAGE_PRI(0, 3, 1, 2), GP_4PAGE_PRI(3, 0, 1, 2), GP_4PAGE_PRI(3, 2, 1, 0), };
  int TogglePriIndex = 0;

  //!< 垂直同期
  VDISPST((uint8_t*)OnVBlank, ON_VBLANK, 1);
  
  while (1)
  {      
    VWait(1);

    if(ESC_ON) { break; }

    if(S_ON) {
      //!< A 押しながらでウインドウサイズ変更
      if(UP_ON) { --WinH;}
      if(DOWN_ON) { ++WinH; }
      if(LEFT_ON) { --WinW; }
      if(RIGHT_ON) { ++WinW; }
    } else {
      //!< ウインドウ移動
      if(UP_ON) { --WinY;}
      if(DOWN_ON) { ++WinY; }
      if(LEFT_ON) { --WinX; }
      if(RIGHT_ON) { ++WinX; }
    }
    int UP_CUR = UP_ON, DOWN_CUR = DOWN_ON, LEFT_CUR = LEFT_ON, RIGHT_CUR = RIGHT_ON;
    int SPACE_CUR = SPACE_ON;
    int TAB_CUR = TAB_ON;
    int P_CUR = P_ON;
    WinX = CLAMP(WinX, 0, 255);
    WinY = CLAMP(WinY, 0, 255);
    WinW = CLAMP(WinW, 1, 255);
    WinH = CLAMP(WinH, 1, 255);

    //!< スペースで再描画
    if(SPACE_PUSH(SPACE_PREV)) {
      ClearAllPage();
      
      WINDOW(WinX, WinY, WinX + WinW, WinY + WinH);
      DrawAllPage();
      
      DrawWindow(WinX, WinY, WinX + WinW, WinY + WinH, 5); 
    }
    
    //!< ウインドウ領域表示
    if(UP_PUSH(UP_PREV) | DOWN_PUSH(DOWN_PREV) | LEFT_PUSH(LEFT_PREV) | RIGHT_PUSH(RIGHT_PREV)) {
      ClearAllPage();
      WINDOW(0, 0, 512, 512);
    }
    if(UP_ON | DOWN_ON | LEFT_ON | RIGHT_ON) {
      APAGE(0); WIPE();
      DrawWindow(WinX, WinY, WinX + WinW, WinY + WinH, 5); 
    }

    //!< ページ毎のオンオフ切替え
    if(TAB_PUSH(TAB_PREV)) {
      ++TogglePageIndex; 
      TogglePageIndex %= COUNTOF(TogglePages);
      VPAGE(TogglePages[TogglePageIndex]);
    }
    //!< ページ毎のプライオリティ切替え
    if(P_PUSH(P_PREV)) {
      ++TogglePriIndex; 
      TogglePriIndex %= COUNTOF(TogglePris);
      PRIORITY(TogglePris[TogglePriIndex]);
    }
    UP_PREV = UP_CUR; DOWN_PREV = DOWN_CUR; LEFT_PREV = LEFT_CUR, RIGHT_PREV = RIGHT_CUR;
    SPACE_PREV = SPACE_CUR;
    TAB_PREV = TAB_CUR;
    P_PREV = P_CUR;

    //!< ページ毎のスクロール (現状何もしてない)
    SCROLL(0, 0, 0);
    SCROLL(1, 0, 0);
    SCROLL(2, 0, 0);
    SCROLL(3, 0, 0);
  }

  G_CLR_ON(); 
  B_CURON();
  CRTMOD(PrevCRT);
}

