#pragma once

//!< SP_REGST() �p
enum {
  SP_ON_VBLANK = 0,
  SP_IMMEDIATE = 0x80,
};
//!< SP_REGST() �p
enum {
  //!< ��\��
  SP_PRI_INVISIBLE,
  //!< BG1 �������
  SP_PRI_BACK,
  //!< BG0 �� BG1 �̊�
  SP_PRI_MIDDLE,
  //!< BT0 ������O
  SP_PRI_FRONT,
};

enum {
  //!< ��\��
  XSP_PRI_INVISIBLE = 0x0,
  //!< BG1 �������
  XSP_PRI_BACK = 0x10,
  //!< BG0 �� BG1 �̊�
  XSP_PRI_MIDDLE = 0x20,
  //!< BT0 ������O
  XSP_PRI_FRONT = 0x30,
};
//!< XSP_PRI(XSP_PRI_FRONT, [0, 15]) �̂悤�Ɏg��
#define XSP_PRI(_MainPri, _SubPri) (_MainPri + _SubPri)

enum {
  //!< �X�v���C�g���W��(0, 0) �ɂ���ƁA����ʂ̍���ɃX�v���C�g�̉E�������Ē��x��ʂ��狎�銴���ɂȂ��Ă���
  SP_COORD_OFFSET = 16,
};