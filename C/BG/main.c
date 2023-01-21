#include <stdio.h>
#include <stdint.h>
#include <iocslib.h>

#include "Common.h"
#include "Palette.h"
#include "PCG.h"
#include "BG.h"
#include "Joy.h"

//0, 0, 0, 1, 1, 0, 0, 0,
//0, 0, 1, 1, 1, 1, 0, 0,
//0, 1, 1, 1, 1, 1, 1, 0,
//1, 1, 0, 1, 1, 0, 1, 1,
//1, 1, 1, 1, 1, 1, 1, 1,
//0, 0, 1, 0, 0, 1, 0, 0,
//0, 1, 0, 1, 1, 0, 1, 0,
//1, 0, 1, 0, 0, 1, 0, 1,

//0, 0, 0, 0, 1, 1, 0, 0,
//0, 0, 0, 0, 1, 0, 0, 0,
//0, 1, 1, 1, 1, 1, 1, 0,
//1, 1, 1, 1, 1, 1, 1, 1,
//1, 0, 1, 1, 1, 1, 1, 1,
//1, 0, 1, 1, 1, 1, 1, 1,
//1, 1, 1, 1, 1, 1, 1, 1,
//0, 1, 1, 1, 1, 1, 1, 0,
uint8_t PCGData8X8[] = {
  //!< �C���x�[�_�[
  PIX2(0, 0), PIX2(0, 1), PIX2(1, 0), PIX2(0, 0),
  PIX2(0, 0), PIX2(1, 1), PIX2(1, 1), PIX2(0, 0),
  PIX2(0, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 0),
  PIX2(1, 1), PIX2(0, 1), PIX2(1, 0), PIX2(1, 1),
  PIX2(1, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(0, 0), PIX2(1, 0), PIX2(0, 1), PIX2(0, 0),
  PIX2(0, 1), PIX2(0, 1), PIX2(1, 0), PIX2(1, 0),
  PIX2(1, 0), PIX2(1, 0), PIX2(0, 1), PIX2(0, 1),
  //!< ���
  PIX2(0, 0), PIX2(0, 0), PIX2(1, 1), PIX2(0, 0),
  PIX2(0, 0), PIX2(0, 0), PIX2(1, 0), PIX2(0, 0),
  PIX2(0, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 0),
  PIX2(1, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(1, 0), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(1, 0), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(1, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 1),
  PIX2(0, 1), PIX2(1, 1), PIX2(1, 1), PIX2(1, 0),
  //!< �J���[�o�[0
  PIX2( 0,  0), PIX2( 0,  0), PIX2( 0,  0), PIX2( 0,  0),
  PIX2( 1,  1), PIX2( 1,  1), PIX2( 1,  1), PIX2( 1,  1),
  PIX2( 2,  2), PIX2( 2,  2), PIX2( 2,  2), PIX2( 2,  2),
  PIX2( 3,  3), PIX2( 3,  3), PIX2( 3,  3), PIX2( 3,  3),
  PIX2( 4,  4), PIX2( 4,  4), PIX2( 4,  4), PIX2( 4,  4),
  PIX2( 5,  5), PIX2( 5,  5), PIX2( 5,  5), PIX2( 5,  5),
  PIX2( 6,  6), PIX2( 6,  6), PIX2( 6,  6), PIX2( 6,  6),
  PIX2( 7,  7), PIX2( 7,  7), PIX2( 7,  7), PIX2( 7,  7),
  //!< �J���[�o�[1
  PIX2( 8,  8), PIX2( 8,  8), PIX2( 8,  8), PIX2( 8,  8),
  PIX2( 9,  9), PIX2( 9,  9), PIX2( 9,  9), PIX2( 9,  9),
  PIX2(10, 10), PIX2(10, 10), PIX2(10, 10), PIX2(10, 10),
  PIX2(11, 11), PIX2(11, 11), PIX2(11, 11), PIX2(11, 11),
  PIX2(12, 12), PIX2(12, 12), PIX2(12, 12), PIX2(12, 12),
  PIX2(13, 13), PIX2(13, 13), PIX2(13, 13), PIX2(13, 13),
  PIX2(14, 14), PIX2(14, 14), PIX2(14, 14), PIX2(14, 14),
  PIX2(15, 15), PIX2(15, 15), PIX2(15, 15), PIX2(15, 15),
};
enum {
  PCG0_DATA = 0,  //!< �C���x�[�_�[
  PCG1_DATA = 32, //!< ���
  PCG2_DATA = 64, //!< �J���[�o�[0
  PCG3_DATA = 96, //!< �J���[�o�[1
};
enum {
  //!< �f�t�H���g�ł� BG �p�f�[�^�� 64 ����?
  PCG0_ID = 64,  //!< �C���x�[�_�[
  PCG1_ID = 65,  //!< ���
  PCG2_ID = 66,  //!< �J���[�o�[0
  PCG3_ID = 67,  //!< �J���[�o�[1
};

uint64_t PALData[PAL_BLOCK_COUNT][PAL_COLOR_COUNT];
uint8_t	PCGData[PCG_16X16_COUNT][PCG_16X16_SIZE];

//#define DRAW_PALETTE

void main()
{
  //!< CRT mode
  const int PrevCRT = CRTMOD(-1);
  CRTMOD(CRT_MODE_HIGH_256X256_T16G16_512);
  //!< �J�[�\���I�t (Cursor off)
  B_CUROFF();
  //!< �O���t�B�b�N�N���A (Clear graphics)
  G_CLR_ON(); 
  SP_INIT();
  
  //!< �p���b�g (Palette)
  SPALET( 1, 1, COL_YELLOW);
  SPALET( 1, 2, COL_RED);
  #ifdef DRAW_PALETTE
  SPALET( 2, 2, COL_GREEN);
  SPALET( 3, 2, COL_BLUE);
  SPALET( 4, 2, COL_YELLOW);
  SPALET( 5, 2, COL_MAGENTA);
  SPALET( 6, 2, COL_WHITE);
  SPALET( 7, 2, COL_GRAY);
  SPALET( 8, 2, COL_PURPLE);
  SPALET( 9, 2, COL_BLACK);
  SPALET(10, 2, COL_NAVY);
  SPALET(11, 2, COL_AQUA);
  SPALET(12, 2, COL_MAROON);
  SPALET(13, 2, COL_LIME);
  SPALET(14, 2, COL_SILVER);
  SPALET(15, 2, COL_OLIVE);
  #endif

  //!< PCG
  SP_CGCLR(0);
  SP_DEFCG(PCG0_ID, PCG_PAT_8X8, &PCGData8X8[PCG0_DATA]);
  SP_DEFCG(PCG1_ID, PCG_PAT_8X8, &PCGData8X8[PCG1_DATA]);
  #ifdef DRAW_PALETTE
  SP_DEFCG(PCG2_ID, PCG_PAT_8X8, &PCGData8X8[PCG2_DATA]);
  SP_DEFCG(PCG3_ID, PCG_PAT_8X8, &PCGData8X8[PCG3_DATA]);
  #endif

  //!< �X�v���C�g (BG�݂̂ł��I���ɂ��Ȃ��ƃ_���݂���) (Sprite need SP_ON(), even if BG only)
  SP_ON(); 

  //!< BG
  int BG0Pal = 1, BG1Pal = 2;
  int Bg0X = 0, Bg0Y = 0;
  int Bg1X = 0, Bg1Y = 0;
  {
    //!< BG �R���g���[�����W�X�^0�A�e�L�X�g�y�[�W0 �I�� (BG0 ON)
    BGCTRLST(0, 0, BG_ON);
    //!< BG �R���g���[�����W�X�^1�A�e�L�X�g�y�[�W1 �I�� (BG1 ON)
	  BGCTRLST(1, 1, BG_ON);

    //!< �e�L�X�g�[�y�[�W���p�^�[���ŃN���A
    BGTEXTCL(0, CODE(FLIP_NONE, 0, 0)); 
    BGTEXTCL(1, CODE(FLIP_NONE, 0, 0));
    //!< BG �̃}�b�v���쐬
    for (int i = 0; i < BG_HEIGHT; ++i) {
      for (int j = 0; j < BG_WIDTH; ++j) {
        if((i + j) & 1)    BGTEXTST(0, j, i, CODE(FLIP_NONE, BG0Pal, PCG0_ID)); 
        if(!((i + j) & 1)) BGTEXTST(1, j, i, CODE(FLIP_NONE, BG1Pal, PCG1_ID)); 
      }
    }

    #ifdef DRAW_PALETTE
    //!< �p���b�g��`�� (Draw palette)
    for (int j = 0; j < BG_WIDTH; ++j) {
      BGTEXTST(0, j, 30, CODE(FLIP_NONE, 2, PCG2_ID)); 
      BGTEXTST(0, j, 31, CODE(FLIP_NONE, 2, PCG3_ID)); 
    }
    #endif
  }

  int TAB_PREV = 0;
  while (1)
  {      
    if(ESC_ON) { break; }
    
    Bg0X = ++Bg0X & 0x3ff;
    Bg1Y = ++Bg1Y & 0x3ff;
    BGSCRLST(BG_ON_VBLANK | 0, Bg0X, Bg0Y);
    BGSCRLST(BG_ON_VBLANK | 1, Bg1X, Bg1Y);

    //!< BG �ؑւ�
    int TAB_CUR = TAB_ON;
    if(TAB_PUSH(TAB_PREV)) {
      if(BGCTRLGT(0)){
        BGCTRLST(0, 0, BG_OFF);
	      BGCTRLST(1, 1, BG_ON);
      } else {
        BGCTRLST(0, 0, BG_ON);
	      BGCTRLST(1, 1, BG_OFF);
      }
    }
    TAB_PREV = TAB_CUR;

    //!< BG �S�\��
    if(SPACE_ON) {
      BGCTRLST(0, 0, BG_ON);
	    BGCTRLST(1, 1, BG_ON);
    }

    B_LOCATE(0, 0);
    printf("BG0 %03d, %03d\n", Bg0X, Bg0Y);
    printf("BG1 %03d, %03d\n", Bg1X, Bg1Y);
  }
  
  SP_OFF();

  //!< �J�[�\���I�� (Cursor on)
  B_CURON();
  //!< CRT ��߂�
  CRTMOD(PrevCRT);
}
