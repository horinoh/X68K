#pragma once

#include <iocslib.h>
#include <stdint.h>

enum {
  IOCS_PRIORITY = 0x92,
  IOCS_CRTMOD2 = 0x93,

  IOCS_PENCOLOR = 0x95,

  IOCS_MASK_GPUT = 0x98,
  IOCS_GPUT = 0x99,

  IOCS_GPTRN = 0x9a,
  IOCS_BK_GPTRN = 0x9b,
  IOCS_X_GPTRN = 0x9c,
};

#pragma region PRIORITY
#define GP_PAGE_PRI0(_Page) (_Page & 0x3)
#define GP_PAGE_PRI1(_Page) (GP_PAGE_PRI0(_Page) << 2)
#define GP_PAGE_PRI2(_Page) (GP_PAGE_PRI0(_Page) << 4)
#define GP_PAGE_PRI3(_Page) (GP_PAGE_PRI0(_Page) << 6)

#define GP_4PAGE_PRI(_Pri0Page, _Pri1Page, _Pri2Page, _Pri3Page) (GP_PAGE_PRI0(_Pri0Page) | GP_PAGE_PRI1(_Pri1Page) | GP_PAGE_PRI2(_Pri2Page) | GP_PAGE_PRI3(_Pri3Page))
#define GP_3PAGE_PRI(_Pri0Page, _Pri1Page) 
#define GP_1PAGE_PRI() 

//!< �O���t�B�b�N���
//!<    1 ���̏ꍇ�͈ȉ����g�p���邱��
//!<      GP_PAGE_PRI(0, 1, 2, 3) 
//!<    2 ���̏ꍇ��(�ǂ��炪��O���ɂ��)�ȉ��̂����ꂩ���g�p���邱��
//!<      GP_PAGE_PRI(0, 1, 2, 3)
//!<      GP_PAGE_PRI(2, 3, 0, 1)

//!< �O���t�B�b�N(GP)�A�e�L�X�g(TX)�A�X�v���C�g(SPP) �̃v���C�I���e�B [0, 2]
#define GP_PRI(_Pri) ((_Pri & 0x3) << 8)
#define TX_PRI(_Pri) ((_Pri & 0x3) << 10)
#define SP_PRI(_Pri) ((_Pri & 0x3) << 12)

//!< ��) 
//!<    PRIORITY((GP_PRI(0) | TX_PRI(1) | SP_PRI(2)) | GP_PAGE_PRI(0, 1, 2, 3));
uint16_t PRIORITY(const uint16_t rhs)
{
  struct REGS In = { .d0 = IOCS_PRIORITY, .d1 = rhs };
  struct REGS Out;
  TRAP15(&In, &Out);
  return Out.d0; //!< �ύX�O�̒l
}

enum {
  GPUT_COLOR_16 = 0x000f,
  GPUT_COLOR_256 = 0x00ff,
  GPUT_COLOR_65536 = 0xffff,
};
struct GPUTPTR
{
  uint16_t x1;
  uint16_t y1;
  uint16_t color_mode;
  uint16_t buf_start;
};
uint16_t MASK_GPUT(const uint16_t x, const uint16_t y, const uint16_t TColor, const struct GPUTPTR* Ptr)
{
  struct REGS In = { .d0 = IOCS_MASK_GPUT, .d1 = x, .d2 = y, .d3 = TColor, .a1 = (int)Ptr };
  struct REGS Out;
  TRAP15(&In, &Out);
  return Out.d0; //!< 0:����I�� -1:�F���[�h���Ⴄ
}
uint16_t GPUT(const uint16_t x, const uint16_t y, const struct GPUTPTR* Ptr)
{
  struct REGS In = { .d0 = IOCS_GPUT, .d1 = x, .d2 = y, .a1 = (int)Ptr };
  struct REGS Out;
  TRAP15(&In, &Out);
  return Out.d0; //!< 0:����I�� -1:�F���[�h���Ⴄ
}

void PENCOLOR(const uint16_t Color)
{
  struct REGS In = { .d0 = IOCS_PENCOLOR, .d1 = Color };
  struct REGS Out;
  TRAP15(&In, &Out);
}
struct GPTRNPTR
{
  uint16_t x1;
  uint16_t y1;
  uint16_t fill_patn;
};
//!< PENCOLOR() �Ŏw�肵���F�Ńp�^�[����`��
void GPTRN(const uint16_t x, const uint16_t y, const struct GPTRNPTR* Ptr)
{
  struct REGS In = { .d0 = IOCS_GPTRN, .d1 = x, .d2 = y, .a1 = (int)Ptr };
  struct REGS Out;
  TRAP15(&In, &Out);
}
//!< PENCOLOR() �Ŏw�肵���F�Ńp�^�[����`�� (�w�i�F���w��)
void BK_GPTRN(const uint16_t x, const uint16_t y, const uint16_t BColor, const struct GPTRNPTR* Ptr)
{
  struct REGS In = { .d0 = IOCS_BK_GPTRN, .d1 = x, .d2 = y, .d3 = BColor, .a1 = (int)Ptr };
  struct REGS Out;
  TRAP15(&In, &Out);
}
//!< PENCOLOR() �Ŏw�肵���F�Ńp�^�[����`�� (�g��w��[1, 1023])
void X_GPTRN(const uint16_t x, const uint16_t y, const uint16_t SclX, const uint16_t SclY, const struct GPTRNPTR* Ptr)
{
  struct REGS In = { .d0 = IOCS_X_GPTRN, .d1 = x, .d2 = y, .d3 = SclX, .d4 = SclY, .a1 = (int)Ptr };
  struct REGS Out;
  TRAP15(&In, &Out);
}
#pragma endregion


#pragma region A
enum {
  //!< ����� 512 ��
  GP_PAGE0_ON = 1 << 0,
  GP_PAGE1_ON = 1 << 1,
  GP_PAGE2_ON = 1 << 2,
  GP_PAGE3_ON = 1 << 3,
  //!< ����� 1024 ��
  GP_1024_PAGE_ON = 1 << 4,
  
  TEXT_ON = 1 << 5,
  
  SPRITE_ON = 1 << 6,

  //!< 1 << 7 �͏�� 0 ���w�肷�邱��

  //!< �e�L�X�g���(BG + �X�v���C�g)��֔�����
  TRNSP_ON_TX = 1 << 8,
  //!< �O���t�B�b�N��ʏ�֔�����
  TRNSP_ON_GP = 1 << 9, 

  //!< ����v���C�I���e�B(�������܂�)�̗̈�w����ŉ��ʃr�b�g�Ŏw�� (������̃p���b�g�ԍ��g�p�ӏ����Ώ�)
  SPCPRI_LSB = 1 << 10,
  //!< ���������L��
  TRNSP_ON = 1 << 11,
  //!< ����v���C�I���e�B(�������܂�)���L��
  SPCPRI_ON = 1 << 12,

  //!< �r�f�I��ʏ�֔�����
  TRNSP_ON_VD = 1 << 13,
  //!< �e�L�X�g�p���b�g0��֔�����
  TRNSP_ON_PAL = 1 << 14,
};

#define EN_SPCPRI SPCPRI_ON | SPCPRI_LSB
//!< TRNSP_ON_PAL �g�p���͒P�ƂŎw�肷�邱��
//!<    EN_TRNSP(TRNSP_ON_PAL)
//!< TRNSP_ON_VD �g�p���͒P�Ƃł͂Ȃ� TRNSP_ON_TX�ATRNSP_ON_GP �Ƒg�ݍ��킹�Ďg�p���邱��
//!<    EN_TRNSP(TRNSP_ON_VD | TRNSP_ON_TX), EN_TRNSP(TRNSP_ON_VD | TRNSP_ON_GP), EN_TRNSP(TRNSP_ON_VD | TRNSP_ON_TX | TRNSP_ON_GP)
#define EN_TRNSP(_Target) ((EN_SPCPRI | TRNSP_ON) | _Target)

//!< ��) 
//!<    CRTMOD2(EN_TRNSP(TRNSP_ON_TX | TRNSP_ON_GP) | (SP_ON | TX_ON | GP_PAGE1_ON | GP_PAGE0_ON));
uint16_t CRTMOD2(const uint16_t rhs)
{
  struct REGS In = { .d0 = IOCS_CRTMOD2, .d1 = rhs };
  struct REGS Out;
  TRAP15(&In, &Out);
  return Out.d0; //!< �ύX�O�̒l
}
#pragma endregion

