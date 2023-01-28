#pragma once

//!< 実画面 1024 x 1024
//!<      4 プレーン
enum {
  TEXT_WIDTH = 1024,
  TEXT_HEIGHT = 1024,
};


//!< テキスト面では円筒スクロール(上下) 
//!<    BGやグラフィック面では球面スクロール(上下左右)

//!< プレーン0 [0xe00000, 0xe1ffff]
//!< プレーン1 [0xe20000, 0xe3ffff]
//!< プレーン2 [0xe40000, 0xe5ffff]
//!< プレーン3 [0xe60000, 0xe7ffff]

enum {
  PL0 = 1,
  PL1 = 2,
  PL2 = 4,
  PL3 = 8,
};
#define IS_PL0(_Val) ((_Val & PL0) != 0)
#define IS_PL1(_Val) ((_Val & PL1) != 0)
#define IS_PL2(_Val) ((_Val & PL2) != 0)
#define IS_PL3(_Val) ((_Val & PL3) != 0)

//#define PLANE0(_15, _14, _13, _12, _11, _10, _09, _08, _07, _06, _05, _04, _03, _02, _01, _00) (IS_PL0(_15) << 15) | (IS_PL0(_14) << 14) | (IS_PL0(_13 & PL0) << 13) | (IS_PL0(_12) << 12) | (IS_PL0(_11) << 11) | (IS_PL0(_10) << 10) | (IS_PL0(_09) ) << 9 | (IS_PL0(_08) << 8) | (IS_PL0(_07) << 7) | (IS_PL0(_06) << 6) | (IS_PL0(_05) << 5) | (IS_PL0(_04) << 4) | (IS_PL0(_03) << 3) | (IS_PL0(_02) << 2) | (IS_PL0(_01) << 1) | (IS_PL0(_00) << 0)
//#define PLANE1(_15, _14, _13, _12, _11, _10, _09, _08, _07, _06, _05, _04, _03, _02, _01, _00) (IS_PL1(_15) << 15) | (IS_PL1(_14) << 14) | (IS_PL1(_13 & PL0) << 13) | (IS_PL1(_12) << 12) | (IS_PL1(_11) << 11) | (IS_PL1(_10) << 10) | (IS_PL1(_09) ) << 9 | (IS_PL1(_08) << 8) | (IS_PL1(_07) << 7) | (IS_PL1(_06) << 6) | (IS_PL1(_05) << 5) | (IS_PL1(_04) << 4) | (IS_PL1(_03) << 3) | (IS_PL1(_02) << 2) | (IS_PL1(_01) << 1) | (IS_PL1(_00) << 0)
//#define PLANE2(_15, _14, _13, _12, _11, _10, _09, _08, _07, _06, _05, _04, _03, _02, _01, _00) (IS_PL2(_15) << 15) | (IS_PL2(_14) << 14) | (IS_PL2(_13 & PL0) << 13) | (IS_PL2(_12) << 12) | (IS_PL2(_11) << 11) | (IS_PL2(_10) << 10) | (IS_PL2(_09) ) << 9 | (IS_PL2(_08) << 8) | (IS_PL2(_07) << 7) | (IS_PL2(_06) << 6) | (IS_PL2(_05) << 5) | (IS_PL2(_04) << 4) | (IS_PL2(_03) << 3) | (IS_PL2(_02) << 2) | (IS_PL2(_01) << 1) | (IS_PL2(_00) << 0)
//#define PLANE3(_15, _14, _13, _12, _11, _10, _09, _08, _07, _06, _05, _04, _03, _02, _01, _00) (IS_PL3(_15) << 15) | (IS_PL3(_14) << 14) | (IS_PL3(_13 & PL0) << 13) | (IS_PL3(_12) << 12) | (IS_PL3(_11) << 11) | (IS_PL3(_10) << 10) | (IS_PL3(_09) ) << 9 | (IS_PL3(_08) << 8) | (IS_PL3(_07) << 7) | (IS_PL3(_06) << 6) | (IS_PL3(_05) << 5) | (IS_PL3(_04) << 4) | (IS_PL3(_03) << 3) | (IS_PL3(_02) << 2) | (IS_PL3(_01) << 1) | (IS_PL3(_00) << 0)

#define PLANE0(_07, _06, _05, _04, _03, _02, _01, _00)  DOT8U8(IS_PL0(_07), IS_PL0(_06), IS_PL0(_05), IS_PL0(_04), IS_PL0(_03), IS_PL0(_02), IS_PL0(_01), IS_PL0(_00))
#define PLANE1(_07, _06, _05, _04, _03, _02, _01, _00)  DOT8U8(IS_PL1(_07), IS_PL1(_06), IS_PL1(_05), IS_PL1(_04), IS_PL1(_03), IS_PL1(_02), IS_PL1(_01), IS_PL1(_00))
#define PLANE2(_07, _06, _05, _04, _03, _02, _01, _00)  DOT8U8(IS_PL2(_07), IS_PL2(_06), IS_PL2(_05), IS_PL2(_04), IS_PL2(_03), IS_PL2(_02), IS_PL2(_01), IS_PL2(_00))
#define PLANE3(_07, _06, _05, _04, _03, _02, _01, _00)  DOT8U8(IS_PL3(_07), IS_PL3(_06), IS_PL3(_05), IS_PL3(_04), IS_PL3(_03), IS_PL3(_02), IS_PL3(_01), IS_PL3(_00))

//!< 単位は 4 ラスタ単位
#define RAS_SRC_DST(_Src, _Dst) ((_Src << 8) | _Dst)
enum {
  RAS_PLANE0 = 1 << 0,
  RAS_PLANE1 = 1 << 1,
  RAS_PLANE2 = 1 << 2,
  RAS_PLANE3 = 1 << 3,
  RAS_PLANE_ALL = RAS_PLANE0 | RAS_PLANE1 | RAS_PLANE2 | RAS_PLANE3,

  RAS_DIR_INC = 0,
  RAS_DIR_DEC = 1 << 15,
};

enum {
  TX_VRAM_PLANE0 = 0xe00000,
  TX_VRAM_PLANE1 = 0xe20000,
  TX_VRAM_PLANE2 = 0xe40000,
  TX_VRAM_PLANE3 = 0xe60000,

  TX_SCROLL_X = 0xe80014, //!< & 0x3ffff
  TX_SCROLL_Y = 0xe80016, //!< & 0x3ffff

  TX_MASK_PAT = 0xe8002e,
};

//  {
//     TPALET(1, COL_AQUA);

//     struct TBOXPTR Box = { .vram_page = 0, .x = 256, .y = 64, .x1 = 100, .y1 = 120, .line_style = 0xffff/*0xafaf*/ };
//     TXBOX(&Box);

//     struct TXFILLPTR Fill = { .vram_page = 0, .x = 256, .y = 256, .x1 = 100, .y1 = 100, .fill_patn = 0xffff/*0xfafa*/ };
//     TXFILL(&Fill);

//     struct XLINEPTR Xline = { .vram_page = 0, .x = 10, .y = 128, .x1 = 128, .line_style = 0xafaf };
//     TXXLINE(&Xline);

//     struct YLINEPTR Yline = { .vram_page = 0, .x = 10, .y = 256, .y1 = 128, .line_style = 0xfafa };
//     TXYLINE(&Yline);
//   }
