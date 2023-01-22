#pragma once

//!< DMAMODE() 用
enum {
  DMA_MODE_NONE = 0x00,
  DMA_MODE_MOVE = 0x8a,
  DMA_MODE_MOVE_L = 0x8b,
  DMA_MODE_MOVE_A = 0x8c,
};

//!< DMAMOVE(), DMAMOV_A(), DMAMOV_L() 用
enum {
  DMA_NONE = 0,
  DMA_INC = (1 << 0),
  DMA_DEC = (1 << 1),

  DMA_INVERSE = (1 << 7),
};
#define DMA_SRC(_Mode) (_Mode << 2)
#define DMA_DST(_Mode) (_Mode << 0)

#define DMA_MODE(_Src, _Dst) (DMA_SRC(_Src) | DMA_DST(_Dst))
#define DMA_MODE_R(_Src, _Dst) (DMA_INVERSE | DMA_MODE(_Src, _Dst))
