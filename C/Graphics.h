#pragma once

//!< グラフィック画面
//!<    実画面 1024x1024
//!<        16色 x 1ページ
//!<    実画面 512x512
//!<        16色 x 4ページ
//!<        256色 x 2ページ
//!<        65536色 x 1ページ

enum {
  GP_PAGE0_BIT = 1 << 0,
  GP_PAGE1_BIT = 1 << 1,
  GP_PAGE2_BIT = 1 << 2,
  GP_PAGE3_BIT = 1 << 3,
  GP_ALL_PAGES_BIT = GP_PAGE0_BIT | GP_PAGE1_BIT | GP_PAGE2_BIT | GP_PAGE3_BIT,
};

//!< グラフィックVRAM
//!<    ページ0 [0xc00000, 0xc7fffe] 
//!<    ページ1 [0xc80000, 0xcffffe] 
//!<    ページ2 [0xd00000, 0xd7fffe] 
//!<    ページ3 [0xd80000, 0xcffffe] 
enum {
  GP_VRAM_PAGE0 = 0xc00000,
  GP_VRAM_PAGE1 = 0xc80000,
  GP_VRAM_PAGE2 = 0xd00000,
  GP_VRAM_PAGE3 = 0xd80000,
};

  //!< 実画面が 1024 (1 ページ) 
  //!<    GP_SCROLL_PAGE0_X, GP_SCROLL_PAGE0_X を使用
  //!< 実画面が 512
  //!<    16色 (4ページ) 
  //!<      1 対 1 なので直感的にやればよい
  //!<    236色 (2ページ)
  //!<      ページ0 : GP_SCROLL_PAGE0_X と GP_SCROLL_PAGE1_X に同じ値を入れる、 Yも同様
  //!<      ページ1 : GP_SCROLL_PAGE2_X と GP_SCROLL_PAGE3_X に同じ値を入れる、 Yも同様
  //!<    65536色 (1ページ)
  ///!<     GP_SCROLL_PAGE0_X, GP_SCROLL_PAGE1_X, GP_SCROLL_PAGE2_X, GP_SCROLL_PAGE3_X に同じ値を入れる、Yも同様
  // GP_SCROLL_PAGE0_X = 0xe80018, //!< & 0x3ffff
  // GP_SCROLL_PAGE0_Y = 0xe8001a, //!< & 0x3ffff

  // GP_SCROLL_PAGE1_X = 0xe8001c, //!< & 0x1ffff
  // GP_SCROLL_PAGE1_Y = 0xe8001e, //!< & 0x1ffff
  
  // GP_SCROLL_PAGE2_X = 0xe80020, //!< & 0x1ffff
  // GP_SCROLL_PAGE2_Y = 0xe80022, //!< & 0x1ffff
  
  // GP_SCROLL_PAGE3_X = 0xe80024, //!< & 0x1ffff
  // GP_SCROLL_PAGE3_Y = 0xe80026, //!< & 0x1ffff

enum {
  FONT12,
  FONT16,
  FONT24,
};
enum {
  ROT0,
  ROT90,
  ROT180,
  ROT270,
};