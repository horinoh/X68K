#include <stdio.h>
#include <iocslib.h>

#include <stdlib.h>

#include "Common.h"
#include "Sound.h"

void main()
{
  //!< ADPCM  ... �����̎�荞�݁A�Đ�
  struct CHAIN Chain[] = {
    { .adr = (int)malloc(4096), .len = 4096 },
    { .adr = (int)malloc(4096), .len = 4096 },
    { .adr = (int)malloc(4096), .len = 4096 },
  };
  static char Buff[8192];
  struct CHAIN2 C = { .adr = (int)malloc(4096), .len = 4096, .next = NULL };
  struct CHAIN2 B = { .adr = (int)malloc(4096), .len = 4096, .next = &C };
  struct CHAIN2 A = { .adr = (int)malloc(4096), .len = 4096, .next = &B };

  //!< ����
  ADPCMAIN(Chain, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R), COUNTOF(Chain));
  ADPCMINP(Buff, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R), sizeof(Buff));
  ADPCMLIN(&A, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R));
  //!< �o��
  ADPCMAOT(Chain, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R), COUNTOF(Chain));
  ADPCMOUT(Buff, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R), sizeof(Buff));
  ADPCMLOT(&A, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R));

  //!< ���s����
  ADPCMMOD(ADPCM_RESTART);

  //!< ���s���[�h�𒲂ׂ�
  {
    int ADPCMStatus = ADPCMSNS();
    switch (ADPCMStatus)
    {
      case ADPCM_NONE:
      case ADPCM_OUT:
      case ADPCM_INP:
      case ADPCM_AOT:
      case ADPCM_AIN:
      case ADPCM_LOT:
      case ADPCM_LIN:
        break;
      default:
        break;
    }
  }

  //!< FM     ... �����g����{�Ƃ��ĉ��Z�����ŉ����쐬
  //!<    OPM*
  //!<    8 �`�����l��
  //!<      4 �̐����g���U��(�X���b�g) M[1,2](���W�����[�^), C[1,2](�L�����A)
  //!<      EG(EnvelopGenerator), LFO(LowFrequencyOscillator), Noise

  const int OPMStatus = OPMSNS();
  if(!(OPMStatus & OPM_BUSY)) {
    //!< (���쒆�Ŗ������)��������
    //OPMSET(Address, Data);
  }
  //!< ���荞�ݏ����A�h���X���w��
  //OPMINTST(IntAddress);
}

