#pragma once

//!< ����� 1024 x 1024
//!<      4 �v���[��

//!< �e�L�X�g�ʂł͉~���X�N���[��(�㉺) 
//!<    BG��O���t�B�b�N�ʂł͋��ʃX�N���[��(�㉺���E)

//!< �v���[��0 [0xe00000, 0xe1ffff]
//!< �v���[��1 [0xe20000, 0xe3ffff]
//!< �v���[��2 [0xe40000, 0xe5ffff]
//!< �v���[��3 [0xe60000, 0xe7ffff]

enum {
  TX_VRAM_PLANE0 = 0xe00000,
  TX_VRAM_PLANE1 = 0xe20000,
  TX_VRAM_PLANE2 = 0xe40000,
  TX_VRAM_PLANE3 = 0xe60000,

  TX_SCROLL_X = 0xe80014, //!< & 0x3ffff
  TX_SCROLL_Y = 0xe80016, //!< & 0x3ffff

  TX_MASK_PAT = 0xe8002e,
};

//  {
//     TPALET(1, COL_AQUA);

//     struct TBOXPTR Box = { .vram_page = 0, .x = 256, .y = 64, .x1 = 100, .y1 = 120, .line_style = 0xffff/*0xafaf*/ };
//     TXBOX(&Box);

//     struct TXFILLPTR Fill = { .vram_page = 0, .x = 256, .y = 256, .x1 = 100, .y1 = 100, .fill_patn = 0xffff/*0xfafa*/ };
//     TXFILL(&Fill);

//     struct XLINEPTR Xline = { .vram_page = 0, .x = 10, .y = 128, .x1 = 128, .line_style = 0xafaf };
//     TXXLINE(&Xline);

//     struct YLINEPTR Yline = { .vram_page = 0, .x = 10, .y = 256, .y1 = 128, .line_style = 0xfafa };
//     TXYLINE(&Yline);
//   }
