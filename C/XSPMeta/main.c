#include <stdio.h>
#include <stdint.h>
#include <iocslib.h>

#include "XSP2lib.H"

#include "Common.h"
#include "Palette.h"
#include "PCG.h"
#include "Sprite.h"
#include "BG.h"
#include "Joy.h"

#define PCG_MAX 256
uint8_t PCGWork[PCG_MAX + 1];
uint8_t PCGData[PCG_MAX][PCG_16X16_SIZE];
uint16_t PALData[PAL_BLOCK_COUNT][PAL_COLOR_COUNT];

void main()
{
  const int PrevCRT = CRTMOD(-1);
  CRTMOD(CRT_MODE_HIGH_256X256_T16G16_512);
  B_CUROFF();
  G_CLR_ON();
  SP_INIT();
  SP_ON();
  BGCTRLST(0, 0, 0);
  BGCTRLST(1, 1, 0);

  {
    FILE *Fp = fopen("../../x68k_xsp/SAMPLE/PANEL.PAL", "rb");
    if (NULL != Fp)
    {
      const size_t Size = fread(PALData, 1, sizeof(PALData), Fp);
      fclose(Fp);
      printf("Palette loaded (%d byte)\n", Size);
    }
  }

  {
    FILE *Fp = fopen("../../x68k_xsp/SAMPLE/PANEL.SP", "rb");
    if (NULL != Fp)
    {
      const size_t Size = fread(PCGData, 1, sizeof(PCGData), Fp);
      fclose(Fp);
      printf("PCG loaded (%d byte)\n", Size);
    }
  }

  for (int i = 0; i < COUNTOF(PALData); ++i)
  {
    for (int j = 0; j < COUNTOF(PALData[0]); ++j)
    {
      SPALET(j, i, PALData[i][j]);
    }
  }

  xsp_on();

  xsp_pcgdat_set(PCGData, PCGWork, sizeof(PCGWork));

  //!< メタスプライト (Metasprite)
  //!< オフセットは前要素からの相対で指定
  const XOBJ_FRM_DAT MetaSprite3x3[] = {
      {.vx = 0, .vy = 0, .pt = 0, .rv = FLIP_NONE},    //!< LT
      {.vx = 16, .vy = 0, .pt = 1, .rv = FLIP_NONE},   //!< CT
      {.vx = 16, .vy = 0, .pt = 2, .rv = FLIP_NONE},   //!< RT
      {.vx = -32, .vy = 16, .pt = 3, .rv = FLIP_NONE}, //!< LC
      {.vx = 16, .vy = 0, .pt = 4, .rv = FLIP_NONE},   //!< CC
      {.vx = 16, .vy = 0, .pt = 5, .rv = FLIP_NONE},   //!< RC
      {.vx = -32, .vy = 16, .pt = 6, .rv = FLIP_NONE}, //!< LB
      {.vx = 16, .vy = 0, .pt = 7, .rv = FLIP_NONE},   //!< CB
      {.vx = 16, .vy = 0, .pt = 8, .rv = FLIP_NONE},   //!< RB
  };
  const XOBJ_FRM_DAT MetaSprite2x2[] = {
      {.vx = 0, .vy = 0, .pt = 0, .rv = FLIP_NONE},    //!< LT
      {.vx = 16, .vy = 0, .pt = 1, .rv = FLIP_NONE},   //!< RT
      {.vx = -16, .vy = 16, .pt = 2, .rv = FLIP_NONE}, //!< LB
      {.vx = 16, .vy = 0, .pt = 3, .rv = FLIP_NONE},   //!< RB
  };
  const XOBJ_FRM_DAT MetaSprite3x1[] = {
      {.vx = 0, .vy = 0, .pt = 0, .rv = FLIP_NONE},  //!< L
      {.vx = 16, .vy = 0, .pt = 1, .rv = FLIP_NONE}, //!< C
      {.vx = 16, .vy = 0, .pt = 2, .rv = FLIP_NONE}, //!< R
  };
  const XOBJ_FRM_DAT MetaSprite1x3[] = {
      {.vx = 0, .vy = 0, .pt = 0, .rv = FLIP_NONE},  //!< T
      {.vx = 0, .vy = 16, .pt = 1, .rv = FLIP_NONE}, //!< C
      {.vx = 0, .vy = 16, .pt = 2, .rv = FLIP_NONE}, //!< B
  };
  //!< メタスプライトの列挙
  const XOBJ_REF_DAT MetaSprites[] = {
      {.num = COUNTOF(MetaSprite3x3), .ptr = (XOBJ_FRM_DAT *)MetaSprite3x3},
      {.num = COUNTOF(MetaSprite2x2), .ptr = (XOBJ_FRM_DAT *)MetaSprite2x2},
      {.num = COUNTOF(MetaSprite3x1), .ptr = (XOBJ_FRM_DAT *)MetaSprite3x1},
      {.num = COUNTOF(MetaSprite1x3), .ptr = (XOBJ_FRM_DAT *)MetaSprite1x3},
  };
  xsp_objdat_set(MetaSprites);

  //!< スプライト (Sprite)
  //!< (xobj_set_st() の引数として使う場合は) .pt = 何番目のメタスプライトか (MetaSprites[i] の 添え字i)
  const uint16_t Base = 0;
  const uint16_t Ofs = 32;
  XSP_SET_ARG Sprites[] = {
      {.x = Base, .y = Base, .pt = 0, .info = XSP_CODE(FLIP_NONE, 0, XSP_PRI(XSP_PRI_MIDDLE, 0))},
      {.x = Base + Ofs * 1, .y = Base + Ofs * 1, .pt = 1 % COUNTOF(MetaSprites), .info = XSP_CODE(FLIP_H, 1, XSP_PRI(XSP_PRI_FRONT, 15))},
      {.x = Base + Ofs * 2, .y = Base + Ofs * 2, .pt = 2 % COUNTOF(MetaSprites), .info = XSP_CODE(FLIP_H, 2, XSP_PRI(XSP_PRI_FRONT, 0))},
      {.x = Base + Ofs * 3, .y = Base + Ofs * 3, .pt = 3 % COUNTOF(MetaSprites), .info = XSP_CODE(FLIP_V, 3, XSP_PRI(XSP_PRI_MIDDLE, 15))},
      {.x = Base + Ofs * 4, .y = Base + Ofs * 4, .pt = 4 % COUNTOF(MetaSprites), .info = XSP_CODE(FLIP_V, 4, XSP_PRI(XSP_PRI_MIDDLE, 0))},
      {.x = Base + Ofs * 5, .y = Base + Ofs * 5, .pt = 5 % COUNTOF(MetaSprites), .info = XSP_CODE(FLIP_HV, 5, XSP_PRI(XSP_PRI_BACK, 15))},
      {.x = Base + Ofs * 6, .y = Base + Ofs * 6, .pt = 6 % COUNTOF(MetaSprites), .info = XSP_CODE(FLIP_HV, 6, XSP_PRI(XSP_PRI_BACK, 0))},
  };

  while (1)
  {
    xsp_vsync2(1);

    if (ESC_ON)
    {
      break;
    }

    XSP_SET_ARG *Sp = &Sprites[0];
    const int Joy = JOYGET(0);
    if (!(Joy & JOY_UP))
    {
      --Sp->y;
    }
    if (!(Joy & JOY_DOWN))
    {
      ++Sp->y;
    }
    if (!(Joy & JOY_LEFT))
    {
      --Sp->x;
    }
    if (!(Joy & JOY_RIGHT))
    {
      ++Sp->x;
    }
    if (!(Joy & JOY_A))
    {
      break;
    }
    if (!(Joy & JOY_B))
    {
      break;
    }
    if (UP_ON)
    {
      --Sp->y;
    }
    if (DOWN_ON)
    {
      ++Sp->y;
    }
    if (LEFT_ON)
    {
      --Sp->x;
    }
    if (RIGHT_ON)
    {
      ++Sp->x;
    }
    Sp->x = MAX(MIN(Sp->x, 0xff), 0);
    Sp->y = MAX(MIN(Sp->y, 0xff), 0);

    //!< メタスプライトの登録
    for (uint8_t i = 0; i < COUNTOF(Sprites); ++i)
    {
      xobj_set_st(&Sprites[i]);
    }

    xsp_out();

    B_LOCATE(0, 10);
    printf("SP %03d, %03d\n", Sp->x, Sp->y);
  }

  xsp_off();

  CRTMOD(PrevCRT);
}
