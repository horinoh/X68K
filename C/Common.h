#pragma once
#include <stdlib.h>

#define COUNTOF(_Array) sizeof(_Array) / sizeof(_Array[0])
#define MIN(_Lhs, _Rhs) (_Lhs < _Rhs ? _Lhs : _Rhs)
#define MAX(_Lhs, _Rhs) (_Lhs > _Rhs ? _Lhs : _Rhs)
#define CLAMP(_Val, _Min, _Max) MAX(MIN(_Val, _Max), _Min)

//#define PI 4.0f * atan(1.0f)
#define TO_RADIAN(_Deg) ((_Deg) * PI / 180.0f)
#define TO_DEGREE(_Rad) ((_Rad) * 180.0f / PI)

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

enum {
  OFF = 0,
  ON = 1,
};

//!< CRTMOD() —p
enum {
  CRT_MODE_HIGH_512X512_T16G16_1024,
  CRT_MODE_LOW_512X512_T16G16_1024,
  CRT_MODE_HIGH_256X256_T16G16_1024,
  CRT_MODE_LOW_256X256_T16G16_1024,
  CRT_MODE_HIGH_512X512_T16G16_512,
  CRT_MODE_LOW_512X512_T16G16_512,
  CRT_MODE_HIGH_256X256_T16G16_512,
  CRT_MODE_LOW_256X256_T16G16_512,
  CRT_MODE_HIGH_512X512_T16G256_512,
  CRT_MODE_LOW_512X512_T16G256_512,
  CRT_MODE_HIGH_256X256_T16G256_512,
  CRT_MODE_LOW_256X256_T16G256_512,
  CRT_MODE_HIGH_512X512_T16G65536_512,
  CRT_MODE_LOW_512X512_T16G65536_512,
  CRT_MODE_HIGH_256X256_T16G65536_512,
  CRT_MODE_LOW_256X256_T16G65536_512,
  CRT_MODE_HIGH_768X512_T16G16_1024,
};

#pragma region COLOR
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
#pragma endregion

#pragma region KEY_INPUT
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
#define IS_PUSH(_Grp, _Bit, _Prev) (IS_ON(_Grp, _Bit) && !_Prev)

#define ESC_ON IS_ON(0, 1)
#define TAB_ON IS_ON(2, 0)
#define TAB_PUSH(_Prev) IS_PUSH(2, 0, _Prev)
#define SPACE_ON IS_ON(6, 5)
#define SPACE_PUSH(_Prev) IS_PUSH(6, 5, _Prev)
#define SHIFT_ON IS_ON(14, 0)
#define CTRL_ON IS_ON(15, 0)
#define CTRL_PUSH(_Prev) IS_PUSH(15, 0, _Prev)

#define LEFT_ON IS_ON(7, 3)
#define LEFT_PUSH(_Prev) IS_PUSH(7, 3, _Prev)
#define UP_ON IS_ON(7, 4)
#define UP_PUSH(_Prev) IS_PUSH(7, 4, _Prev)
#define RIGHT_ON IS_ON(7, 5)
#define RIGHT_PUSH(_Prev) IS_PUSH(7, 5, _Prev)
#define DOWN_ON IS_ON(7, 6)
#define DOWN_PUSH(_Prev) IS_PUSH(7, 6, _Prev)

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
#define P_PUSH(_Prev) IS_PUSH(3, 2, _Prev)
#define A_ON IS_ON(3, 6)
#define A_PUSH(_Prev) IS_PUSH(3, 6, _Prev)
#define S_ON IS_ON(3, 7)
#define Z_ON IS_ON(5, 2)
#define X_ON IS_ON(5, 3)
#define C_ON IS_ON(5, 4)
#define C_PUSH(_Prev) IS_PUSH(5, 4, _Prev)
#define B_ON IS_ON(5, 6)
#define B_PUSH(_Prev) IS_PUSH(5, 6, _Prev)
#pragma endregion
