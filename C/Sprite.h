#pragma once

enum {
  SP_ON_VBLANK = 0,
  SP_IMMEDIATE = 0x80,
};

enum {
  //!< �X�v���C�g���W��(0, 0) �ɂ���ƁA����ʂ̍���ɃX�v���C�g�̉E�������Ē��x��ʂ��狎�銴���ɂȂ��Ă���
  SP_COORD_OFFSET = 16,
};

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