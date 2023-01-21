#pragma once

enum {
    ON_VBLANK,
    ON_VDISP,
};

#define INTERRUPT_FUNC __attribute__((interrupt))
//#define INTERRUPT_FUNC

volatile int HCount = 0;
void INTERRUPT_FUNC OnHBlank()
{
	++HCount;
}

volatile int VCount = 0;
volatile int VWaitCount = 0;
void INTERRUPT_FUNC OnVBlank()
{
	++VCount;
    ++VWaitCount;
}
void VWait(int Wait)
{
  while(VWaitCount < Wait) {}
  VWaitCount = 0;
}