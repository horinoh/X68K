#include <stdio.h>
#include <iocslib.h>

#include <stdlib.h>

#include "Common.h"
#include "Sound.h"

void main()
{
  //!< ADPCM  ... 音声の取り込み、再生
  struct CHAIN Chain[] = {
    { .adr = (int)malloc(4096), .len = 4096 },
    { .adr = (int)malloc(4096), .len = 4096 },
    { .adr = (int)malloc(4096), .len = 4096 },
  };
  static char Buff[8192];
  struct CHAIN2 C = { .adr = (int)malloc(4096), .len = 4096, .next = NULL };
  struct CHAIN2 B = { .adr = (int)malloc(4096), .len = 4096, .next = &C };
  struct CHAIN2 A = { .adr = (int)malloc(4096), .len = 4096, .next = &B };

  //!< 入力
  ADPCMAIN(Chain, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R), COUNTOF(Chain));
  ADPCMINP(Buff, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R), sizeof(Buff));
  ADPCMLIN(&A, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R));
  //!< 出力
  ADPCMAOT(Chain, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R), COUNTOF(Chain));
  ADPCMOUT(Buff, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R), sizeof(Buff));
  ADPCMLOT(&A, ADPCM_MODE(SAMPLING_3_9KHZ, ADPCM_MODE_R));

  //!< 実行制御
  ADPCMMOD(ADPCM_RESTART);

  //!< 実行モードを調べる
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

  //!< FM     ... 正弦波を基本として演算処理で音を作成
  //!<    OPM*
  //!<    8 チャンネル
  //!<      4 つの正弦波発振器(スロット) M[1,2](モジュレータ), C[1,2](キャリア)
  //!<      EG(EnvelopGenerator), LFO(LowFrequencyOscillator), Noise

  const int OPMStatus = OPMSNS();
  if(!(OPMStatus & OPM_BUSY)) {
    //!< (動作中で無ければ)書き込み
    //OPMSET(Address, Data);
  }
  //!< 割り込み処理アドレスを指定
  //OPMINTST(IntAddress);
}

