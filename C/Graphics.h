#pragma once

//!< �O���t�B�b�N���
//!<    ����� 1024x1024
//!<        16�F x 1�y�[�W
//!<    ����� 512x512
//!<        16�F x 4�y�[�W
//!<        256�F x 2�y�[�W
//!<        65536�F x 1�y�[�W

enum {
  GP_PAGE0_BIT = 1 << 0,
  GP_PAGE1_BIT = 1 << 1,
  GP_PAGE2_BIT = 1 << 2,
  GP_PAGE3_BIT = 1 << 3,
  GP_ALL_PAGES_BIT = GP_PAGE0_BIT | GP_PAGE1_BIT | GP_PAGE2_BIT | GP_PAGE3_BIT,
};

//!< �O���t�B�b�NVRAM
//!<    �y�[�W0 [0xc00000, 0xc7fffe] 
//!<    �y�[�W1 [0xc80000, 0xcffffe] 
//!<    �y�[�W2 [0xd00000, 0xd7fffe] 
//!<    �y�[�W3 [0xd80000, 0xcffffe] 
enum {
  GP_VRAM_PAGE0 = 0xc00000,
  GP_VRAM_PAGE1 = 0xc80000,
  GP_VRAM_PAGE2 = 0xd00000,
  GP_VRAM_PAGE3 = 0xd80000,
};

  //!< ����ʂ� 1024 (1 �y�[�W) 
  //!<    GP_SCROLL_PAGE0_X, GP_SCROLL_PAGE0_X ���g�p
  //!< ����ʂ� 512
  //!<    16�F (4�y�[�W) 
  //!<      1 �� 1 �Ȃ̂Œ����I�ɂ��΂悢
  //!<    236�F (2�y�[�W)
  //!<      �y�[�W0 : GP_SCROLL_PAGE0_X �� GP_SCROLL_PAGE1_X �ɓ����l������A Y�����l
  //!<      �y�[�W1 : GP_SCROLL_PAGE2_X �� GP_SCROLL_PAGE3_X �ɓ����l������A Y�����l
  //!<    65536�F (1�y�[�W)
  ///!<     GP_SCROLL_PAGE0_X, GP_SCROLL_PAGE1_X, GP_SCROLL_PAGE2_X, GP_SCROLL_PAGE3_X �ɓ����l������AY�����l
  // GP_SCROLL_PAGE0_X = 0xe80018, //!< & 0x3ffff
  // GP_SCROLL_PAGE0_Y = 0xe8001a, //!< & 0x3ffff

  // GP_SCROLL_PAGE1_X = 0xe8001c, //!< & 0x1ffff
  // GP_SCROLL_PAGE1_Y = 0xe8001e, //!< & 0x1ffff
  
  // GP_SCROLL_PAGE2_X = 0xe80020, //!< & 0x1ffff
  // GP_SCROLL_PAGE2_Y = 0xe80022, //!< & 0x1ffff
  
  // GP_SCROLL_PAGE3_X = 0xe80024, //!< & 0x1ffff
  // GP_SCROLL_PAGE3_Y = 0xe80026, //!< & 0x1ffff

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