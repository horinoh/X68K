#include <stdio.h>
#include <stdint.h>
#include <iocslib.h>
#include <math.h>

#include "XSP2lib.H"
#include "PCG90.H"
#include "PCM8Afnc.H"

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
const uint8_t PCGDataBG[] = {
  //!< �C���x�[�_�[
  DOT2U16(0, 0), DOT2U16(0, 1), DOT2U16(1, 0), DOT2U16(0, 0),
  DOT2U16(0, 0), DOT2U16(1, 1), DOT2U16(1, 1), DOT2U16(0, 0),
  DOT2U16(0, 1), DOT2U16(1, 1), DOT2U16(1, 1), DOT2U16(1, 0),
  DOT2U16(1, 1), DOT2U16(0, 1), DOT2U16(1, 0), DOT2U16(1, 1),
  DOT2U16(1, 1), DOT2U16(1, 1), DOT2U16(1, 1), DOT2U16(1, 1),
  DOT2U16(0, 0), DOT2U16(1, 0), DOT2U16(0, 1), DOT2U16(0, 0),
  DOT2U16(0, 1), DOT2U16(0, 1), DOT2U16(1, 0), DOT2U16(1, 0),
  DOT2U16(1, 0), DOT2U16(1, 0), DOT2U16(0, 1), DOT2U16(0, 1),
};

//!< �T�C���e�[�u��
int16_t SinTable[256];
int16_t SinIndex = 0;

//!< ���荞��
int16_t VCount = 0;
int16_t HCount = 0;
void OnVInt()
{
  SinIndex = VCount % COUNTOF(SinTable);

  ++VCount;
  HCount = 0;
}
XSP_TIME_CHART TimeChart[COUNTOF(SinTable)];
void OnHInt()
{
  //!< BG �̃X�N���[�� [0, 1024]
  BGSCRLST(BG_IMMEDIATE | 0, BG_SCR_VAL(SinTable[SinIndex]), SCR_VAL_KEEP);
  //!< �O���t�B�b�N�ʂ̃X�N���[��
  SCROLL(0, SinTable[SinIndex], SCR_VAL_KEEP);

  SinIndex = ++SinIndex % COUNTOF(SinTable);

  ++HCount;
}

void main()
{
  const int PrevCRT = CRTMOD(-1);
  CRTMOD(CRT_MODE_HIGH_256X256_T16G16_512);
  G_CLR_ON();
  SP_INIT();
  SP_ON();
  BGCTRLST(0, 0, ON);
  BGCTRLST(1, 1, OFF);
  B_CUROFF();

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

  //!< �T�C���e�[�u���쐬
  const int16_t Radius = 64;
  for (uint16_t i = 0; i < COUNTOF(SinTable); ++i)
  {
    SinTable[i] = sin(PI * (double)(i << 1) / COUNTOF(SinTable)) * Radius;
  }

  xsp_on();

  //!< ���荞��
  xsp_vsyncint_on(OnVInt);
  //!< ���荞�݃��X�^�i���o�[�́A�f�B�X�v���C���[�h 31KHz ���� 8 �̔{���A15KHz ���� 4 �̔{�� �ł��邱��
  const uint16_t Cnt = COUNTOF(SinTable) / 4;
  for (uint16_t i = 0; i < Cnt; ++i)
  {
    TimeChart[i].ras_no = i * 8 + 32;
    TimeChart[i].proc = OnHInt;
  }
  TimeChart[Cnt].ras_no = -1;
  xsp_hsyncint_on(TimeChart);

  //!< ���X�^�X�N���[���m�F�p�ɃO���t�B�b�N��`���Ă���
  GPALET(1, 0xFFFF);
  WINDOW(0, 0, 511, 511);
  for (uint16_t i = 0; i < 512; i += 16)
  {
    struct LINEPTR Line = {.x1 = i, .y1 = 0, .x2 = i, .y2 = 511, .color = 1, .linestyle = 0xffff};
    LINE(&Line);
  }

  //!< ���X�^�X�N���[���m�F�p��BG��`���Ă���
  const uint8_t BG = 0;
  const uint16_t BGPCGID = 64;
  SP_DEFCG(BGPCGID, PCG_PAT_8X8, (uint8_t *)PCGDataBG);
  BGTEXTCL(BG, CODE(FLIP_NONE, 0, 0));
  for (int i = 0; i < BG_HEIGHT; ++i)
  {
    for (int j = 0; j < BG_WIDTH; ++j)
    {
      if (j & 1)
      {
        BGTEXTST(BG, j, i, CODE(FLIP_NONE, 0, BGPCGID));
      }
    }
  }

  xsp_pcgdat_set(PCGData, PCGWork, sizeof(PCGWork));

  const uint16_t Base = 64;
  const uint16_t Ofs = 16;
  XSP_SET_ARG Sprites[] = {
      {.x = Base, .y = Base, .pt = 0, .info = XSP_CODE(FLIP_NONE, 0, XSP_PRI(XSP_PRI_FRONT, 0))},
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
    Sp->x = CLAMP(Sp->x, 0x0, 0xff);
    Sp->y = CLAMP(Sp->y, 0x0, 0xff);

    for (uint8_t i = 0; i < COUNTOF(Sprites); ++i)
    {
      xsp_set_st(&Sprites[i]);
    }

    xsp_out();

    B_LOCATE(0, 10);
    printf("SP %03d, %03d\n", Sp->x, Sp->y);
    printf("Sin[%03d]=%03d\n", SinIndex, SinTable[SinIndex]);
  }

  xsp_off();

  CRTMOD(PrevCRT);
}
