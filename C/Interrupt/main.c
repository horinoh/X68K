#include <stdio.h>
#include <iocslib.h>
#include <stdint.h>
#include <math.h>

#include "Common.h"
#include "Interrupt.h"

volatile int HCount = 0;
void INTERRUPT_FUNC OnHBlank()
{
  //BGSCRLST(BG_IMMEDIATE | 0, ..., -1);
  //SCROLL(0, ..., -1);

	++HCount;
}
volatile int VCount = 0;
volatile int VWaitCount = 0;
void INTERRUPT_FUNC OnVBlank()
{
	  ++VCount;
    HCount = 0;

    ++VWaitCount;
}
void VWait(int Wait)
{
  while(VWaitCount < Wait) {}
  VWaitCount = 0;
}

void main()
{
  HSYNCST((uint8_t*)OnHBlank);
  VDISPST((uint8_t*)OnVBlank, ON_VBLANK, 1);

  int UP_PREV = 0, DOWN_PREV = 0;
  int Wait = 1;
  int Inc = 0;
  while(1) {
    if(ESC_ON) { break; }

    #pragma region CHANGE WAIT
    int UP_CUR = UP_ON;
    if(UP_PUSH(UP_PREV)){ ++Wait; Inc = 0; }
    UP_PREV = UP_CUR;

    int DOWN_CUR = DOWN_ON;
    if(DOWN_PUSH(DOWN_PREV)){ --Wait; Inc = 0; }
    DOWN_PREV = DOWN_CUR;

    Wait = CLAMP(Wait, 1, 10);
    #pragma endregion

    //!< Increment after wait
    VWait(Wait);
    ++Inc;
    
    B_LOCATE(0, 0);
    printf("VCount=0x%05x, HCount=%d, Sec=%d\n", VCount, HCount, VCount / 60);
    printf("Wait=%02d\n", Wait);
    printf("Inc=%03d\n", Inc);
  }

  G_CLR_ON();

  VDISPST(NULL, ON_VBLANK, 0);
  HSYNCST(NULL);
}

