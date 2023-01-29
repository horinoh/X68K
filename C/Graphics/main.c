#include <stdio.h>
#include <iocslib.h>
#include <stdint.h>
#include <string.h>

#include "Common.h"
#include "Graphics.h"
#include "Interrupt.h"
#include "IOCS.h"

//!< 半透明を使用する場合は、カラーインデックスは奇数でないとならない
enum {
  ALPHA_IDX = 0,
  A_RED_IDX = 1, RED_IDX = 2,
  A_GREEN_IDX = 3, GREEN_IDX = 4,
  A_BLUE_IDX = 5, BLUE_IDX = 6,
  A_YELLOW_IDX = 7, YELLOW_IDX = 8,
  A_WHITE_IDX = 9, WHITE_IDX = 10,
};

#define A ALPHA_IDX
#define R RED_IDX
#define G GREEN_IDX
#define B BLUE_IDX
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
  DOT4U16(A,A,A,A), DOT4U16(A,R,R,R), DOT4U16(R,R,A,A), DOT4U16(A,A,A,A),
  DOT4U16(A,A,A,A), DOT4U16(R,R,R,R), DOT4U16(R,R,R,R), DOT4U16(R,A,A,A),
  DOT4U16(A,A,A,A), DOT4U16(B,B,B,G), DOT4U16(G,B,G,A), DOT4U16(A,A,A,A),
  DOT4U16(A,A,A,B), DOT4U16(G,B,G,G), DOT4U16(G,B,G,G), DOT4U16(G,A,A,A),
  DOT4U16(A,A,A,B), DOT4U16(G,B,B,G), DOT4U16(G,G,B,G), DOT4U16(G,G,A,A),
  DOT4U16(A,A,A,B), DOT4U16(B,G,G,G), DOT4U16(G,B,B,B), DOT4U16(B,A,A,A),
  DOT4U16(A,A,A,A), DOT4U16(A,G,G,G), DOT4U16(G,G,G,G), DOT4U16(A,A,A,A),
  DOT4U16(A,A,A,A), DOT4U16(B,B,R,B), DOT4U16(B,B,A,A), DOT4U16(A,A,A,A),

  DOT4U16(A,A,A,B), DOT4U16(B,B,R,B), DOT4U16(B,R,B,B), DOT4U16(B,A,A,A),
  DOT4U16(A,A,B,B), DOT4U16(B,B,R,R), DOT4U16(R,R,B,B), DOT4U16(B,B,A,A),
  DOT4U16(A,A,G,G), DOT4U16(B,R,G,R), DOT4U16(R,G,R,B), DOT4U16(G,G,A,A),
  DOT4U16(A,A,G,G), DOT4U16(G,R,R,R), DOT4U16(R,R,R,G), DOT4U16(G,G,A,A),
  DOT4U16(A,A,G,G), DOT4U16(R,R,R,R), DOT4U16(R,R,R,R), DOT4U16(G,G,A,A),
  DOT4U16(A,A,A,A), DOT4U16(R,R,R,A), DOT4U16(A,R,R,R), DOT4U16(A,A,A,A),
  DOT4U16(A,A,A,B), DOT4U16(B,B,A,A), DOT4U16(A,A,B,B), DOT4U16(B,A,A,A),
  DOT4U16(A,A,B,B), DOT4U16(B,B,A,A), DOT4U16(A,A,B,B), DOT4U16(B,B,A,A),
};
#undef A
#undef R
#undef G
#undef B

//0, 0, 0, 1, 1, 0, 0, 0,
//0, 0, 1, 1, 1, 1, 0, 0,
//0, 1, 1, 1, 1, 1, 1, 0,
//1, 1, 0, 1, 1, 0, 1, 1,
//1, 1, 1, 1, 1, 1, 1, 1,
//0, 0, 1, 0, 0, 1, 0, 0,
//0, 1, 0, 1, 1, 0, 1, 0,
//1, 0, 1, 0, 0, 1, 0, 1,
uint16_t BitPattern[] = {
  DOT8X2U16(0, 0, 0, 1, 1, 0, 0, 0,
            0, 0, 1, 1, 1, 1, 0, 0),
  DOT8X2U16(0, 1, 1, 1, 1, 1, 1, 0,
            1, 1, 0, 1, 1, 0, 1, 1),
  DOT8X2U16(1, 1, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 0, 0, 1, 0, 0),
  DOT8X2U16(0, 1, 0, 1, 1, 0, 1, 0,
            1, 0, 1, 0, 0, 1, 0, 1),
};

//!< 文字列表示用
char Str[8];
//!< ペイント系でバッファを必要とする機能がある (十分なサイズを用意しておけば大丈夫？)
uint8_t Buf[256];

void DrawPage(int Page, int x, int y, int Color, int AColor)
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
    struct FILLPTR Fill = { .x1 = Circle.x - Circle.radius, .y1 = Circle.y + Circle.radius, .x2 = Circle.x + Circle.radius * 3 / 2, .y2 = Circle.y + Circle.radius * 3, .color = AColor  };
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
    struct PAINTPTR Paint = { .x = Circle.x + 1, .y = Circle.y, .color = Color + 2, .buf_start = (UBYTE *)&Buf, .buf_end = (UBYTE *)&Buf[COUNTOF(Buf) - 1] };
    PAINT(&Paint);

    //!< #TODO
    // struct GETPTR Get = { .x1 = 32, .y1 = 32, .x2 = 64, .y2 = 64, .buf_start = (UBYTE *)&Buf, .buf_end = (UBYTE *)&Buf[COUNTOF(Buf) - 1] };
    // GETGRM(&Get);

    //!< #TODO
    // struct PUTPTR Put = { .x1 = 0, .y1 = 0, .x2 = 32, .y2 = 32, .buf_start = (UBYTE *)&Buf, .buf_end = (UBYTE *)&Buf[COUNTOF(Buf) - 1] };
    // PUTGRM(&Put);

    //!< (パレットによる) パターン描画
    {
      //!< ヘッダ + データ分メモリを確保
      void* Top = malloc(sizeof(GPUTHEADER) + sizeof(PalPattern));
      //!< ヘッダ
      GPUTHEADER* Header = (GPUTHEADER*)Top;
      //!< ヘッダ作成
      Header->x1 = 16; Header->y1 = 16; Header->color_mode = GPUT_COLOR_16;
      //!< データ作成
      memcpy(Top + sizeof(GPUTHEADER), PalPattern, sizeof(PalPattern));
      {
        //!< パターンを描画
        GPUT(Circle.x - Circle.radius + 8, Circle.y + Circle.radius, Header);

        //!< パレット 0(ALPHA_IDX) を抜き色扱いとして、パターンを描画
        MASK_GPUT(Circle.x - Circle.radius + 8 + 16, Circle.y + Circle.radius , ALPHA_IDX, Header);
      }
     
      free(Top);
    }

    //!< (ペンカラーによる) ビットパターン描画
    {
      //!< ヘッダ + データ分メモリを確保
      void* Top = malloc(sizeof(GPTRNHEADER) + sizeof(BitPattern));
      //!< ヘッダ
      GPTRNHEADER* Header = (GPTRNHEADER*)Top;
      //!< ヘッダ作成
      Header->x1 = 8; Header->y1 = 8;
      //!< データ作成
      memcpy(Top + sizeof(GPTRNHEADER), BitPattern, sizeof(BitPattern));

      {
        //!< 「緑」でパターン描画
        PENCOLOR(A_GREEN_IDX);
        GPTRN(Circle.x - Circle.radius + 12, Circle.y + Circle.radius + 16, Header);

        //!< 「青」でパターン描画 (バックカラー「白」)
        PENCOLOR(A_BLUE_IDX);
        BK_GPTRN(Circle.x - Circle.radius + 12 + 8, Circle.y + Circle.radius + 16, A_WHITE_IDX, Header);

        //!< 「黄」でパターン描画 (拡大表示)
        PENCOLOR(A_YELLOW_IDX);
        X_GPTRN(Circle.x - Circle.radius + 12 + 8 + 8, Circle.y + Circle.radius + 16, 7, 7, Header);
      }

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
  //!< #TODO 半透明
  //CRTMOD2(EN_TRNSP(TRNSP_ON_GP) | GP_ALL_PAGES_ON);

  DrawPage(0, 32, 32, RED_IDX, A_RED_IDX);
  DrawPage(1, 32 + 32 * 2, 32, GREEN_IDX, A_GREEN_IDX);
  DrawPage(2, 32 + 32 * 4, 32, BLUE_IDX, A_BLUE_IDX);
  DrawPage(3, 32 + 32 * 6, 32, YELLOW_IDX, A_YELLOW_IDX);
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
  
  B_SUPER(0);
  B_CUROFF();
  G_CLR_ON(); 

  //!< 全ページ表示
  if(0 == VPAGE(GP_ALL_PAGES_BIT)) {}
  
  HOME(0, 0, 0);

  //!< パレット番号 (半透明を使用する場合は、カラーインデックスは奇数でないとならない)
  //!<    16色モード [0, 15]
  //!<    256色モード [0, 255]
  //!<    65536色モード [0, 65535]
  GPALET(A_RED_IDX, COL_RED); GPALET(RED_IDX, COL_RED);
  GPALET(A_GREEN_IDX, COL_GREEN); GPALET(GREEN_IDX, COL_GREEN);
  GPALET(A_BLUE_IDX, COL_BLUE); GPALET(BLUE_IDX, COL_BLUE);
  GPALET(A_YELLOW_IDX, COL_YELLOW); GPALET(YELLOW_IDX, COL_YELLOW);
  GPALET(A_WHITE_IDX, COL_WHITE); GPALET(WHITE_IDX, COL_WHITE); 

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

