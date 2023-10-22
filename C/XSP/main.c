#include <stdio.h>
#include <stdint.h>
#include <iocslib.h>

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

void main()
{
  const int PrevCRT = CRTMOD(-1);
  //!< XSP �� 256 x 256 ���[�h�̂�
  CRTMOD(CRT_MODE_HIGH_256X256_T16G16_512);
  G_CLR_ON();
  SP_INIT();
  SP_ON();
  BGCTRLST(0, 0, OFF);
  BGCTRLST(1, 1, OFF);
  B_CUROFF();

  //!< �p���b�g�f�[�^�Ǎ� (Load palette data)
  {
    FILE *Fp = fopen("../../x68k_xsp/SAMPLE/PANEL.PAL", "rb");
    if (NULL != Fp)
    {
      const size_t Size = fread(PALData, 1, sizeof(PALData), Fp);
      fclose(Fp);

      printf("Palette loaded (%d byte)\n", Size);
    }
  }

  //!< PCG �f�[�^�Ǎ� (Load PCG data)
  {
    FILE *Fp = fopen("../../x68k_xsp/SAMPLE/PANEL.SP", "rb");
    if (NULL != Fp)
    {
      const size_t Size = fread(PCGData, 1, sizeof(PCGData), Fp);
      fclose(Fp);

      printf("PCG loaded (%d byte)\n", Size);
    }
  }

  //!< �p���b�g (Set palette)
  for (int i = 0; i < COUNTOF(PALData); ++i)
  {
    for (int j = 0; j < COUNTOF(PALData[0]); ++j)
    {
      SPALET(j, i, PALData[i][j]);
    }
  }

  //!< XSP
  xsp_on();

  {
    //!< 0 128 ���_�ŕ\���ő� 384 ��
    //!< 1 �ő� 512 �� (�f�t�H���g)
    //!< 2 �ő� 512 ���D��x�j�]�y��
    xsp_mode(2);

    //!< ���������̊Ԋu
    xsp_vsync_interval_set(1);

    //!< �X�v���C�g�]�����X�^�̃I�t�Z�b�g�l��ݒ肵�܂�
    //!< �ʏ�̓f�t�H���g�l�̂܂ܕύX����K�v�͂���܂���
    xsp_raster_ofs_for31khz_set(xsp_raster_ofs_for31khz_get());
    xsp_raster_ofs_for15khz_set(xsp_raster_ofs_for15khz_get());

    //!< �A�����Ԋ��荞�݂�������悤�APCM8A �̊��荞�݃}�X�N��ύX���܂�
    //!< ZMUSIC �ł͏풓���ɃX�C�b�` -M ���w�肵�ă��X�^���荞�݂������ĉ�����
    pcm8a_vsyncint_on();

    //!< 1 �̂Ƃ��A�c��ʃ��[�h on
    //!< 0 �̂Ƃ��A�c��ʃ��[�h off
    xsp_vertical(OFF);
    for (uint16_t i = 0; i < COUNTOF(PCGData); i++) {
        //!< 16x16 �h�b�g�� PCG �f�[�^�ւ̃|�C���^ 
	      //!<  1 �̂Ƃ��E 90 �x��]
        //!< -1 �̂Ƃ��� 90 �x��]
    	  pcg_roll90(PCGData[i], 0);
	  }
    //!< 8x8 �h�b�g�� PCG �f�[�^�ւ̃|�C���^
    //bgpcg_roll90(BGPCGData, 1);

    //!< BG �� PCG �G���A�ɏ������܂Ȃ��悤�ɂ���
    xsp_pcgmask_on(128, 255);
  }

  //!< PCG �f�[�^�A�Ǘ��e�[�u���� XSP �֐ݒ�
  xsp_pcgdat_set(PCGData, PCGWork, sizeof(PCGWork));

  //!< �X�v���C�g��`
  //!<    .pt = �p�^�[��, .info = XSP_CODE(���], �p���b�g, �v���C�I���e�B)
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

    //!< �ŏ��̃X�v���C�g���ړ�����
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

    //!< �X�v���C�g��o�^
    for (uint8_t i = 0; i < COUNTOF(Sprites); ++i)
    {
      xsp_set_st(&Sprites[i]);
    }

    //!< �X�v���C�g�̕\��
    xsp_out();

    B_LOCATE(0, 10);
    printf("SP %03d, %03d\n", Sp->x, Sp->y);
  }

  xsp_off();

  CRTMOD(PrevCRT);
}
