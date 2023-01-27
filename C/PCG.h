#pragma once

#define PCG_8X8_COUNT 256 //!< 計算上は 512 いけそうだが、PCG 番号を 8 ビットで指定する為、256 が上限
#define PCG_16X16_COUNT 128

#define PCG_8X8_SIZE 32
#define PCG_16X16_SIZE 128

//!< SP_DEFCG() 用
enum {
  PCG_PAT_8X8,
  PCG_PAT_16X16,
};

//!< SP_REGST(), BGTEXTST() 用
enum {
  FLIP_NONE = 0,
  FLIP_H = (1 << 14),
  FLIP_V = (1 << 15),
  FLIP_HV = FLIP_H | FLIP_V,
};
#define PAL_NO(_No) ((_No & 0xf) << 8)
#define PCG_NO(_No) (_No & 0xff)
#define CODE(_Flip, _Pal, _PCG) (_Flip | PAL_NO(_Pal) | PCG_NO(_PCG))

/*
[0xeb8000, 0xeb9fff] A(8K) 
[0xeba000, 0xebbfff] B(8K)
[0xebc000, 0xebdfff] C(8K)
[0xebe000, 0xebffff] D(8K)
とする、以下のような利用ケースがある

[ BG x 2 ] PCG が BG:8x8、SP:16x16 になるので注意 (A:BG(上限256個), B:SP とするのが無難？)
A PCG ... 16x16 なら 64個、8x8 なら 256個 入る
B PCG
C BG0
D BG1

[ BG x 1 ]
A PCG 
B PCG
C PCG
D BG1

[ BG x 0 ]
A PCG 
B PCG
C PCG
D PCG
*/