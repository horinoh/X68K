#pragma once

#define PCG_8X8_COUNT 256 //!< �v�Z��� 512 �������������APCG �ԍ��� 8 �r�b�g�Ŏw�肷��ׁA256 �����
#define PCG_16X16_COUNT 128

#define PCG_8X8_SIZE 32
#define PCG_16X16_SIZE 128

//!< SP_DEFCG() �p
enum {
  PCG_PAT_8X8,
  PCG_PAT_16X16,
};

//!< SP_REGST(), BGTEXTST() �p
enum {
  FLIP_NONE = 0,
  FLIP_H = (1 << 14),
  FLIP_V = (1 << 15),
  FLIP_HV = FLIP_H | FLIP_V,
};
#define PAL_NO(_No) ((_No & 0xf) << 8)
#define PCG_NO(_No) (_No & 0xff)
#define CODE(_Flip, _Pal, _PCG) (_Flip | PAL_NO(_Pal) | PCG_NO(_PCG))

/*
[0xeb8000, 0xeb9fff] A(8K) 
[0xeba000, 0xebbfff] B(8K)
[0xebc000, 0xebdfff] C(8K)
[0xebe000, 0xebffff] D(8K)
�Ƃ���A�ȉ��̂悤�ȗ��p�P�[�X������

[ BG x 2 ] PCG �� BG:8x8�ASP:16x16 �ɂȂ�̂Œ��� (A:BG(���256��), B:SP �Ƃ���̂�����H)
A PCG ... 16x16 �Ȃ� 64�A8x8 �Ȃ� 256�� ����
B PCG
C BG0
D BG1

[ BG x 1 ]
A PCG 
B PCG
C PCG
D BG1

[ BG x 0 ]
A PCG 
B PCG
C PCG
D PCG
*/