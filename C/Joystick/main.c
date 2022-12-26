#include <stdio.h>
#include <iocslib.h>

#define ESC_ON (BITSNS(0) & (1 << 1))

#define JOY_UP (1 << 0)
#define JOY_DOWN (1 << 1)
#define JOY_LEFT (1 << 2)
#define JOY_RIGHT (1 << 3)
#define JOY_A (1 << 5)
#define JOY_B (1 << 6)

void main()
{
  const short PrevCRTMode = CRTMOD(-1);
  {
    //!< �X�[�p�[�o�C�U�[���[�h
    B_SUPER(0);
    //!< �}�E�X�J�[�\���I�t
    B_CUROFF();
    //!< �O���t�B�b�N�X�N���A
    G_CLR_ON();
  }

  while(1) {
    B_LOCATE(0, 0);
    puts("Press ESC to exit");
    
     //!< ESC (�O���[�v0, �r�b�g (1 << 1)) �������ꂽ
    if(ESC_ON) { break; }
   
    //!< 0 �̎��� ON �Ȃ̂Œ���
    const int Joy = JOYGET(0);
    printf(" %s\n", (Joy & JOY_UP) ? "-" : "o");
    printf("%s  %s\n", (Joy & JOY_LEFT) ? "-" : "o", (Joy & JOY_RIGHT) ? "-" : "o");
    printf(" %s      %s %s\n", (Joy & JOY_DOWN) ? "-" : "o", (Joy & JOY_B) ? "-" : "o", (Joy & JOY_A) ? "-" : "o");
  }

  {
    //!< �}�E�X�J�[�\���I��
    B_CURON();
    //!< CRT ���[�h
    CRTMOD(PrevCRTMode);
  }
}

