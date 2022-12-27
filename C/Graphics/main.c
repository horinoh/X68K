#include <stdio.h>
#include <iocslib.h>

#include "Common.h"

void main()
{
  //!< CRT mode
  const int PrevCRT = CRTMOD(-1);
  //!< Cursor off
  B_CUROFF();
  //!< Clear graphics
  G_CLR_ON(); 

  {
    TPALET(1, COL_YELLOW);

    struct TBOXPTR Box = { .vram_page = 0, .x = 256, .y = 64, .x1 = 100, .y1 = 120, .line_style = 0xffff/*0xafaf*/ };
    TXBOX(&Box);

    struct TXFILLPTR Fill = { .vram_page = 0, .x = 256, .y = 256, .x1 = 100, .y1 = 100, .fill_patn = 0xffff/*0xfafa*/ };
    TXFILL(&Fill);

    struct XLINEPTR Xline = { .vram_page = 0, .x = 10, .y = 128, .x1 = 128, .line_style = 0xafaf };
    TXXLINE(&Xline);

    struct YLINEPTR Yline = { .vram_page = 0, .x = 10, .y = 256, .y1 = 128, .line_style = 0xfafa };
    TXYLINE(&Yline);
  }

  {
    GPALET(1, COL_RED);

    WIPE();

    struct LINEPTR Line = { .x1 = 10, .y1 = 20, .x2 = 20, .y2 = 120, .color = 1, .linestyle = 0xffff };
    LINE(&Line);

    struct BOXPTR Box = { .x1 = 50, .y1 = 20, .x2 = 100, .y2 = 120, .color = 1, .linestyle = 0xffff };
    BOX(&Box);
    struct FILLPTR Fill = { .x1 = 50 + 10, .y1 = 20 + 10, .x2 = 100 - 10, .y2 = 120 - 10, .color = 1 };
    FILL(&Fill);

    struct CIRCLEPTR Circle = { .x = 192, .y = 192, .radius = 100, .color = 1, .start = 0, .end = 360, .ratio = 256 };
    CIRCLE(&Circle);
    struct PSETPTR Pset = { .x = 192, .y = 192, .color = 1 };
    PSET(&Pset);

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
    struct SYMBOLPTR Symbol = { .x1 = 20, .y1 = 20, .string_address = "Hello", .mag_x = 1, .mag_y = 1, .color = 1, .font_type = FONT12, .angle = ROT0 };
  }

  while (1)
  {      
    if(ESC_ON) { break; }
  }

  //!< Cursor on
  B_CURON();
  //!< CRT mode
  CRTMOD(PrevCRT);
}

