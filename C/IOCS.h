#pragma once

#include <iocslib.h>
#include <stdint.h>

enum {
  IOCS_PRIORITY = 0x92,
  IOCS_CRTMOD2 = 0x93,
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
void PRIORITY(const uint16_t lhs)
{
  struct REGS In = { .d0 = IOCS_PRIORITY, .d1 = lhs };
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
void CRTMOD2(const uint16_t lhs)
{
  struct REGS In = { .d0 = IOCS_CRTMOD2, .d1 = lhs };
  struct REGS Out;
  TRAP15(&In, &Out);
}
#pragma endregion

