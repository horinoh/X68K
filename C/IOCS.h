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

//!< グラフィック画面
//!<    1 枚の場合は以下を使用すること
//!<      GP_PAGE_PRI(0, 1, 2, 3) 
//!<    2 枚の場合は(どちらが手前かにより)以下のいずれかを使用すること
//!<      GP_PAGE_PRI(0, 1, 2, 3)
//!<      GP_PAGE_PRI(2, 3, 0, 1)

//!< グラフィック(GP)、テキスト(TX)、スプライト(SPP) のプライオリティ [0, 2]
#define GP_PRI(_Pri) ((_Pri & 0x3) << 8)
#define TX_PRI(_Pri) ((_Pri & 0x3) << 10)
#define SP_PRI(_Pri) ((_Pri & 0x3) << 12)

//!< 例) 
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
  //!< 実画面 512 時
  GP_PAGE0_ON = 1 << 0,
  GP_PAGE1_ON = 1 << 1,
  GP_PAGE2_ON = 1 << 2,
  GP_PAGE3_ON = 1 << 3,
  //!< 実画面 1024 時
  GP_1024_PAGE_ON = 1 << 4,
  
  TEXT_ON = 1 << 5,
  
  SPRITE_ON = 1 << 6,

  //!< 1 << 7 は常に 0 を指定すること

  //!< テキスト画面(BG + スプライト)上へ半透明
  TRNSP_ON_TX = 1 << 8,
  //!< グラフィック画面上へ半透明
  TRNSP_ON_GP = 1 << 9, 

  //!< 特殊プライオリティ(半透明含む)の領域指定を最下位ビットで指定 (即ち奇数のパレット番号使用箇所が対象)
  SPCPRI_LSB = 1 << 10,
  //!< 半透明が有効
  TRNSP_ON = 1 << 11,
  //!< 特殊プライオリティ(半透明含む)が有効
  SPCPRI_ON = 1 << 12,

  //!< ビデオ画面上へ半透明
  TRNSP_ON_VD = 1 << 13,
  //!< テキストパレット0上へ半透明
  TRNSP_ON_PAL = 1 << 14,
};

#define EN_SPCPRI SPCPRI_ON | SPCPRI_LSB
//!< TRNSP_ON_PAL 使用時は単独で指定すること
//!<    EN_TRNSP(TRNSP_ON_PAL)
//!< TRNSP_ON_VD 使用時は単独ではなく TRNSP_ON_TX、TRNSP_ON_GP と組み合わせて使用すること
//!<    EN_TRNSP(TRNSP_ON_VD | TRNSP_ON_TX), EN_TRNSP(TRNSP_ON_VD | TRNSP_ON_GP), EN_TRNSP(TRNSP_ON_VD | TRNSP_ON_TX | TRNSP_ON_GP)
#define EN_TRNSP(_Target) ((EN_SPCPRI | TRNSP_ON) | _Target)

//!< 例) 
//!<    CRTMOD2(EN_TRNSP(TRNSP_ON_TX | TRNSP_ON_GP) | (SP_ON | TX_ON | GP_PAGE1_ON | GP_PAGE0_ON));
void CRTMOD2(const uint16_t lhs)
{
  struct REGS In = { .d0 = IOCS_CRTMOD2, .d1 = lhs };
  struct REGS Out;
  TRAP15(&In, &Out);
}
#pragma endregion

