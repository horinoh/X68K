#pragma once

enum {
  ON_VBLANK,
  ON_VDISP,
};

#if 1
#define INTERRUPT_FUNC __attribute__((interrupt))
#else
#define INTERRUPT_FUNC
#endif
