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
  //!< XSP は 256 x 256 モードのみ
  CRTMOD(CRT_MODE_HIGH_256X256_T16G16_512);
  G_CLR_ON();
  SP_INIT();
  SP_ON();
  BGCTRLST(0, 0, 0);
  BGCTRLST(1, 1, 0);
  B_CUROFF();

  //!< パレットデータ読込 (Load palette data)
  {
    FILE *Fp = fopen("../../x68k_xsp/SAMPLE/PANEL.PAL", "rb");
    if (NULL != Fp)
    {
      const size_t Size = fread(PALData, 1, sizeof(PALData), Fp);
      fclose(Fp);

      printf("Palette loaded (%d byte)\n", Size);
    }
  }

  //!< PCG データ読込 (Load PCG data)
  {
    FILE *Fp = fopen("../../x68k_xsp/SAMPLE/PANEL.SP", "rb");
    if (NULL != Fp)
    {
      const size_t Size = fread(PCGData, 1, sizeof(PCGData), Fp);
      fclose(Fp);

      printf("PCG loaded (%d byte)\n", Size);
    }
  }

  //!< パレット (Set palette)
  for (int i = 0; i < COUNTOF(PALData); ++i)
  {
    for (int j = 0; j < COUNTOF(PALData[0]); ++j)
    {
      SPALET(j, i, PALData[i][j]);
    }
  }

  //!< XSP
  xsp_on();

  //!< PCG データ、管理テーブルを XSP へ設定
  xsp_pcgdat_set(PCGData, PCGWork, sizeof(PCGWork));

  //!< スプライト定義
  //!<    .pt = パターン, .info = XSP_CODE(反転, パレット, プライオリティ)
  const uint16_t Base = 64;
  const uint16_t Ofs = 16;
  XSP_SET_ARG Sprites[] = {
      {.x = Base, .y = Base, .pt = 0, .info = XSP_CODE(FLIP_NONE, 0, XSP_PRI(XSP_PRI_MIDDLE, 0))},
      {.x = Base + Ofs * 1, .y = Base + Ofs * 1, .pt = 1, .info = XSP_CODE(FLIP_H, 1, XSP_PRI(XSP_PRI_FRONT, 15))},
      {.x = Base + Ofs * 2, .y = Base + Ofs * 2, .pt = 2, .info = XSP_CODE(FLIP_H, 2, XSP_PRI(XSP_PRI_FRONT, 0))},
      {.x = Base + Ofs * 3, .y = Base + Ofs * 3, .pt = 3, .info = XSP_CODE(FLIP_V, 3, XSP_PRI(XSP_PRI_MIDDLE, 15))},
      {.x = Base + Ofs * 4, .y = Base + Ofs * 4, .pt = 4, .info = XSP_CODE(FLIP_V, 4, XSP_PRI(XSP_PRI_MIDDLE, 0))},
      {.x = Base + Ofs * 5, .y = Base + Ofs * 5, .pt = 5, .info = XSP_CODE(FLIP_HV, 5, XSP_PRI(XSP_PRI_BACK, 15))},
      {.x = Base + Ofs * 6, .y = Base + Ofs * 6, .pt = 6, .info = XSP_CODE(FLIP_HV, 6, XSP_PRI(XSP_PRI_BACK, 0))},
  };

  while (1)
  {
    xsp_vsync2(1);

    if (ESC_ON)
    {
      break;
    }

    //!< 最初のスプライトを移動操作
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

    //!< スプライトを登録
    for (uint8_t i = 0; i < COUNTOF(Sprites); ++i)
    {
      xsp_set_st(&Sprites[i]);
    }

    //!< スプライトの表示
    xsp_out();

    B_LOCATE(0, 10);
    printf("SP %03d, %03d\n", Sp->x, Sp->y);
  }

  xsp_off();

  CRTMOD(PrevCRT);
}
