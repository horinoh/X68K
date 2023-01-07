#pragma once
#include <stdlib.h>

#define COUNTOF(_Array) sizeof(_Array) / sizeof(_Array[0])
#define MIN(_Lhs, _Rhs) (_Lhs < _Rhs ? _Lhs : _Rhs)
#define MAX(_Lhs, _Rhs) (_Lhs > _Rhs ? _Lhs : _Rhs)
#define CLAMP(_Val, _Min, _Max) MAX(MIN(_Val, _Max), _Min)

static fpos_t  GetFileSize(FILE* Fp)
{
  fpos_t Size = 0;
  if(NULL != Fp) {
    if (0 == fseek(Fp, 0, SEEK_END)) {
        if (0 == fgetpos(Fp, &Size)) {
          if (0 != fseek(Fp, 0, SEEK_SET)) { puts("fseek(SEEK_SET) failed"); }
        }
        else { puts("fgetpos failed"); }
      }
      else { puts("fseek(SEEK_END) failed"); }
  }
  return Size;
}
static fpos_t LoadFile(FILE* Fp)
{
  const fpos_t Size = GetFileSize(Fp);
  if(Size) {

  }
  return Size;
}

enum 
{
  MODE_1024_512X512_C16_P1_31KHZ,
  MODE_1024_512X512_C16_P1_15KHZ,

  MODE_1024_256X256_C16_P1_31KHZ,
  MODE_1024_256X256_C16_P1_15KHZ,

  MODE_512_512X512_C16_P4_31KHZ,
  MODE_512_512X512_C16_P4_15KHZ,

  MODE_512_256X256_C16_P4_31KHZ,
  MODE_512_256X256_C16_P4_15KHZ,

  MODE_512_512X512_C256_P2_31KHZ,
  MODE_512_512X512_C256_P2_16KHZ,

  MODE_512_256X256_C256_P2_31KHZ,
  MODE_512_256X256_C256_P2_15KHZ,

  MODE_512_512X512_C65536_P1_31KHZ,
  MODE_512_512X512_C65536_P1_15KHZ,

  MODE_512_256X256_C65536_P1_31KHZ,
  MODE_512_256X256_C65536_P1_15KHZ,

  MODE_1024_768X512_C16_P1_31KHZ,
  MODE_1024_1024X424_C16_P1_24KHZ,
  MODE_1024_1024X848_C16_P1_24KHZ,

  MODE_1024_640X480_C16_P1_24KHZ,

  MODE_1024_768X512_C256_P2_31KHZ,
  MODE_1024_1024X848_C256_P2_24KHZ,
  MODE_1024_1024X424_C256_P2_24KHZ,
  MODE_1024_640X480_C256_P2_24KHZ,

  MODE_1024_768X512_C65536_P1_31KHZ,
  MODE_1024_1024X848_C65536_P1_24KHZ,
  MODE_1024_1024X424_C65536_P1_24KHZ,
  MODE_1024_640X480_C65536_P1_24KHZ,
};

#define PIX2(_L, _R) ((_L & 0xf) << 4) | (_R & 0xf)

 //!< GGGG GRRR RRBB BBB0
#define RGB(_R, _G, _B) (((_G & 0x1f) << 11) | ((_R & 0x1f) << 6) | ((_B & 0x1f) << 1))
#define COL_TRANSPARENT RGB(0, 0, 0)
#define COL_BLACK RGB(1, 1, 1)
#define COL_RED RGB(31, 0, 0)
#define COL_GREEN RGB(0, 31, 0)
#define COL_BLUE RGB(0, 0, 31)
#define COL_WHITE RGB(31, 31, 31)
#define COL_YELLOW RGB(31, 31, 0)
#define COL_GRAY RGB(15, 15, 15)
#define COL_MAGENTA RGB(31, 0, 31)
#define COL_PURPLE RGB(15, 0, 15)
#define COL_NAVY RGB(0, 0, 15)
#define COL_AQUA RGB(0, 31, 31)
#define COL_MAROON RGB(15, 0, 0)
#define COL_LIME RGB(0, 31, 0)
#define COL_SILVER RGB(23, 23, 23)
#define COL_OLIVE RGB(15, 15, 0)

//!<  H
//!<    [  0,  31] Red - Yellow
//!<    [ 32,  63] Yellow - Green
//!<    [ 64,  95] Green - Cyan
//!<    [ 96, 127] Cyan - Blue
//!<    [128, 159] Blue - Magenta
//!<    [160, 191] Magenta - Red
//!< S 
//!<    White level
//!< V
//!<    Black level
//!< int HSVTORGB(H, S, V);

enum {
  FLIP_NONE = 0x0 << 8,
  FLIP_H = 0x4 << 8,
  FLIP_V = 0x8 << 8,
};

#define PAL_NO(_No) ((_No & 0xf) << 8)
#define PCG_NO(_No) (_No & 0xff)
#define CODE(_Flip, _Pal, _PCG) (_Flip | PAL_NO(_Pal) | PCG_NO(_PCG))

#define ON_VSYNC (1 << 31)

/*
        0   1   2   3   4   5   6   7 (BIT)
    0      ESC  1   2   3   4   5   6     
    1   7   8   9   0   -       \   BS  
    2   TAB q   w   e   r   t   y   u
    3   i   o   p   @   [   CR  a   s
    4   d   f   g   h   j   k   l   ;
    5   :   ]   z   x   c   v   b   n
    6   m   ,   .   /   _   SP  HM  DEL
    7   RUP RDN UND L   U   R   D   CLR
    8   /   *   -   7   8   9   +   4
    9   5   6   =   1   2   3   ENT 0
    a   ,   .
    b
    c       BRK CPY F1  F2  F3  F4  F5
    d   F6  F7  F8  F9  F10
    e   SFT CTL OPT OPT2
    f
    (GROUP)
  */
#define TO_SCANODE(_Group, _Bit) ((_Group << 3) | _Bit)
#define TO_GROUP(_ScanCode) ((_ScanCode & 0xf8) >> 3)
#define TO_BIT(_ScanCode) (_ScanCode & 0x07)

#define TO_SCANCODE(_KeyCode) ((_KeyCode & 0xff00) >> 8)
#define TO_INTERNALCODE(_KeyCode) (_KeyCode & 0xff)

#define IS_ON(_Grp, _Bit) (BITSNS(_Grp) & (1 << _Bit))

#define ESC_ON IS_ON(0, 1)

#define LEFT_ON IS_ON(7, 3)
#define UP_ON IS_ON(7, 4)
#define RIGHT_ON IS_ON(7, 5)
#define DOWN_ON IS_ON(7, 6)

#define ONE_ON IS_ON(0, 2)
#define TWO_ON IS_ON(0, 3)
#define THREE_ON IS_ON(0, 4)
#define FOUR_ON IS_ON(0, 5)
#define FIVE_ON IS_ON(0, 6)
#define SIX_ON IS_ON(0, 7)
#define SEVEN_ON IS_ON(1, 0)
#define EIGHT_ON IS_ON(1, 1)
#define NINE_ON IS_ON(1, 2)
#define ZERO_ON IS_ON(1, 3)

#define E_ON IS_ON(2, 3)
#define T_ON IS_ON(2, 5)
#define P_ON IS_ON(3, 2)
#define A_ON IS_ON(3, 6)
#define S_ON IS_ON(3, 7)
#define Z_ON IS_ON(5, 2)
#define X_ON IS_ON(5, 3)
#define C_ON IS_ON(5, 4)

#define TAB_ON IS_ON(2, 0)
#define SPACE_ON IS_ON(6, 5)
