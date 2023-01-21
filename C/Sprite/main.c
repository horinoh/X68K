#include <stdio.h>
#include <stdint.h>
#include <iocslib.h>

#include "Common.h"
#include "Palette.h"
#include "PCG.h"
#include "Sprite.h"
#include "BG.h"
#include "Joy.h"

//0,0,0,0,0,1,1,1, 1,1,0,0,0,0,0,0,
//0,0,0,0,1,1,1,1, 1,1,1,1,1,0,0,0,
//0,0,0,0,3,3,3,2, 2,3,2,0,0,0,0,0,
//0,0,0,3,2,3,2,2, 2,3,2,2,2,0,0,0,
//0,0,0,3,2,3,3,2, 2,2,3,2,2,2,0,0,
//0,0,0,3,3,2,2,2, 2,3,3,3,3,0,0,0,
//0,0,0,0,0,2,2,2, 2,2,2,2,0,0,0,0,
//0,0,0,0,3,3,1,3, 3,3,0,0,0,0,0,0,

//0,0,0,3,3,3,1,3, 3,1,3,3,3,0,0,0,
//0,0,3,3,3,3,1,1, 1,1,3,3,3,3,0,0,
//0,0,2,2,3,1,2,1, 1,2,1,3,2,2,0,0,
//0,0,2,2,2,1,1,1, 1,1,1,2,2,2,0,0,
//0,0,2,2,1,1,1,1, 1,1,1,1,2,2,0,0,
//0,0,0,0,1,1,1,0, 0,1,1,1,0,0,0,0,
//0,0,0,3,3,3,0,0, 0,0,3,3,3,0,0,0,
//0,0,3,3,3,3,0,0, 0,0,3,3,3,3,0,0,
uint8_t PCGData16X16[] = {
  //!< LT
  PIX2(0, 0), PIX2(0, 0), PIX2(0, 1), PIX2(1, 1),
  PIX2(0, 0), PIX2(0, 0), PIX2(1, 1), PIX2(1, 1),
  PIX2(0, 0), PIX2(0, 0), PIX2(3, 3), PIX2(3, 2),
  PIX2(0, 0), PIX2(0, 3), PIX2(2, 3), PIX2(2, 2),
  PIX2(0, 0), PIX2(0, 3), PIX2(2, 3), PIX2(3, 2),
  PIX2(0, 0), PIX2(0, 3), PIX2(3, 2), PIX2(2, 2),
  PIX2(0, 0), PIX2(0, 0), PIX2(0, 2), PIX2(2, 2),
  PIX2(0, 0), PIX2(0, 0), PIX2(3, 3), PIX2(1, 3),

  //!< LB
  PIX2(0, 0), PIX2(0, 3), PIX2(3, 3), PIX2(1, 3),
  PIX2(0, 0), PIX2(3, 3), PIX2(3, 3), PIX2(1, 1),
  PIX2(0, 0), PIX2(2, 2), PIX2(3, 1), PIX2(2, 1),
  PIX2(0, 0), PIX2(2, 2), PIX2(2, 1), PIX2(1, 1),
  PIX2(0, 0), PIX2(2, 2), PIX2(1, 1), PIX2(1, 1),
  PIX2(0, 0), PIX2(0, 0), PIX2(1, 1), PIX2(1, 0),
  PIX2(0, 0), PIX2(0, 3), PIX2(3, 3), PIX2(0, 0),
  PIX2(0, 0), PIX2(3, 3), PIX2(3, 3), PIX2(0, 0),
  
  //!< RT
  PIX2(1, 1), PIX2(0, 0), PIX2(0, 0), PIX2(0, 0),
  PIX2(1, 1), PIX2(1, 1), PIX2(1, 0), PIX2(0, 0),
  PIX2(2, 3), PIX2(2, 0), PIX2(0, 0), PIX2(0, 0),
  PIX2(2, 3), PIX2(2, 2), PIX2(2, 0), PIX2(0, 0),
  PIX2(2, 2), PIX2(3, 2), PIX2(2, 2), PIX2(0, 0),
  PIX2(2, 3), PIX2(3, 3), PIX2(3, 0), PIX2(0, 0),
  PIX2(2, 2), PIX2(2, 2), PIX2(0, 0), PIX2(0, 0),
  PIX2(3, 3), PIX2(0, 0), PIX2(0, 0), PIX2(0, 0),

  //!< RB
  PIX2(3, 1), PIX2(3, 3), PIX2(3, 0), PIX2(0, 0),
  PIX2(1, 1), PIX2(3, 3), PIX2(3, 3), PIX2(0, 0),
  PIX2(1, 2), PIX2(1, 3), PIX2(2, 2), PIX2(0, 0),
  PIX2(1, 1), PIX2(1, 2), PIX2(2, 2), PIX2(0, 0),
  PIX2(1, 1), PIX2(1, 1), PIX2(2, 2), PIX2(0, 0),
  PIX2(0, 1), PIX2(1, 1), PIX2(0, 0), PIX2(0, 0),
  PIX2(0, 0), PIX2(3, 3), PIX2(3, 0), PIX2(0, 0),
  PIX2(0, 0), PIX2(3, 3), PIX2(3, 3), PIX2(0, 0),
};

void main()
{
  const int PrevCRT = CRTMOD(-1);
  CRTMOD(CRT_MODE_HIGH_256X256_T16G16_512);
  B_CUROFF();
  G_CLR_ON(); 
  SP_INIT();

  //!< パレット 1
  //SPALET(0, 1, ); //!< 透明色 (Transparent) ?
  SPALET(1, 1, COL_RED);
  SPALET(2, 1, COL_YELLOW);
  SPALET(3, 1, COL_GRAY);
  //!< パレット 2
  SPALET(1, 2, COL_WHITE);
  SPALET(2, 2, COL_YELLOW);
  SPALET(3, 2, COL_GREEN);

  //!< PCG
  SP_CGCLR(0);
  SP_DEFCG(0, PCG_PAT_16X16, &PCGData16X16[0]);

  //!< Sprite
  int SpPCG = 0;
  int SpPal0 = 1, SpPal1 = 2;
  int SpX = 128, SpY = 128;
  {
    SP_ON();
    //!< Set sprite
    SP_REGST(0, SpX, SpY, CODE(FLIP_NONE, SpPal0, SpPCG), SP_PRI_FRONT);
    SP_REGST(1, SpX + 16, SpY, CODE(FLIP_NONE, SpPal1, SpPCG), SP_PRI_FRONT);
  }

  //!< BG
  {
    BGCTRLST(0, 0, BG_OFF);
    BGCTRLST(1, 1, BG_OFF);
  }

  while (1)
  {      
    if(ESC_ON) { break; }
      
    const int Joy = JOYGET(0);
    if(!(Joy & JOY_UP)) { --SpY; }
    if(!(Joy & JOY_DOWN)) { ++SpY; }
    if(!(Joy & JOY_LEFT)) { --SpX; }
    if(!(Joy & JOY_RIGHT)) { ++SpX; }
    if(UP_ON) { --SpY; }
    if(DOWN_ON) { ++SpY; }
    if(LEFT_ON) { --SpX; }
    if(RIGHT_ON) { ++SpX; }
    SpX = CLAMP(SpX, 0, 0xff + SP_COORD_OFFSET);
    SpY = CLAMP(SpY, 0, 0xff + SP_COORD_OFFSET);
    SP_REGST(SP_ON_VBLANK | 0, SpX, SpY, CODE(FLIP_NONE, SpPal0, SpPCG), SP_PRI_FRONT);
    SP_REGST(SP_ON_VBLANK | 1, SpX + 16, SpY, CODE(FLIP_HV, SpPal1, SpPCG), SP_PRI_FRONT);

    B_LOCATE(0, 0);
    printf("SP  %03d, %03d\n", SpX, SpY);
  }
  
  SP_OFF();

  //!< Cursor on
  B_CURON();
  //!< CRT mode
  CRTMOD(PrevCRT);
}
