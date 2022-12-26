#pragma once

enum {
  PCG_PAT_8X8,
  PCG_PAT_16X16,
};

#define PCG_8X8_COUNT 256 //!< 計算上は 512 いけそうだが、PCG 番号を 8 ビットで指定する為、256 が上限
#define PCG_16X16_COUNT 128

#define PCG_8X8_SIZE 32
#define PCG_16X16_SIZE 128