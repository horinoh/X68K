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
#define GP_PAGE_PRI(_Pri0Page, _Pri1Page, _Pri2Page, _Pri3Page) (GP_PAGE_PRI0(_Pri0Page) | GP_PAGE_PRI1(_Pri1Page) | GP_PAGE_PRI2(_Pri2Page) | GP_PAGE_PRI3(_Pri3Page))

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
void PRIORITY(const uint16_t Pri)
{
  struct REGS In = { .d0 = IOCS_PRIORITY, .d1 = Pri };
  struct REGS Out;
  TRAP15(&In, &Out);
}
#pragma endregion
