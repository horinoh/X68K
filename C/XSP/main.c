#include <stdio.h>
#include <stdint.h>
#include <iocslib.h>

#include "../../x68k_xsp/XSP/XSP2lib.H"

#include "../Common.h"
#include "../Palette.h"
#include "../PCG.h"
#include "../Sprite.h"
#include "../BG.h"
#include "../Joy.h"

uint64_t PALData[PAL_BLOCK_COUNT][PAL_COLOR_COUNT];
uint8_t	PCGData[PCG_16X16_COUNT][PCG_16X16_SIZE];
uint8_t PCGWork[PCG_16X16_COUNT + 1];

void main()
{
  //!< CRT mode
  const int PrevCRT = CRTMOD(-1);
  CRTMOD(MODE_512_256X256_C16_P4_31KHZ);
  //!< Cursor off
  B_CUROFF();
  //!< Clear graphics
  G_CLR_ON(); 
  SP_INIT();

  //!< Load palette data
  {
    FILE* Fp = fopen("../../x68k_xsp/SAMPLE/PANEL.PAL", "rb");
      if(NULL != Fp) {
      const size_t Size = fread(PALData, sizeof(PALData[0]), COUNTOF(PALData), Fp);
      printf("Palette loaded (%d byte)\n", Size);
      fclose(Fp);
    }
  }
  //!< Load PCG data
  {
    FILE* Fp = fopen("../../x68k_xsp/SAMPLE/PANEL.SP", "rb");
    if(NULL != Fp) {
      const size_t Size = fread(PCGData, sizeof(PCGData[0]), COUNTOF(PCGData), Fp);
      printf("PCG loaded (%d byte)\n", Size);
      fclose(Fp);
    }
  }

  //!< Palette
  for (int i = 0; i < COUNTOF(PALData); ++i) {
    for (int j = 0; j < COUNTOF(PALData[0]); ++j) {
	  	SPALET(j, i, PALData[i][j]);
    }
	}

  //!< XSP  
  {
    xsp_on();

    xsp_pcgdat_set(PCGData, PCGWork, sizeof(PCGWork));

    //!< Metasprite
    XOBJ_FRM_DAT MetaSpriteData[] = {
      { .vx =  0, .vy =  0, .pt = 0, .rv = FLIP_NONE },
      { .vx =  0, .vy = 16, .pt = 1, .rv = FLIP_NONE },
      { .vx = 16, .vy =  0, .pt = 2, .rv = FLIP_NONE },
      { .vx = 16, .vy = 16, .pt = 3, .rv = FLIP_NONE },
    };
    XOBJ_REF_DAT MetaSprite = { .num = COUNTOF(MetaSpriteData), .ptr = MetaSpriteData };
    xsp_objdat_set(&MetaSprite);

    XSP_SET_ARG Sprites[] = {
      { .x = 128, .y = 128, .pt = 0, .info = CODE(FLIP_NONE, 0, 0) },
      // { .x = 128, .y = 128, .pt = 1, .info = CODE(FLIP_NONE, 0, 0) },
      // { .x = 128, .y = 128, .pt = 2, .info = CODE(FLIP_NONE, 0, 0) },
      // { .x = 128, .y = 128, .pt = 3, .info = CODE(FLIP_NONE, 0, 0) },
      // { .x = 128, .y = 128, .pt = 4, .info = CODE(FLIP_NONE, 0, 0) },
      // { .x = 128, .y = 128, .pt = 5, .info = CODE(FLIP_NONE, 0, 0) },`
    };

    while (1)
    {
      xsp_vsync(1);
      
      if(ESC_ON) { break; }
      
      XSP_SET_ARG* Sp = &Sprites[0];
      
      const int Joy = JOYGET(0);
      if(!(Joy & JOY_UP)) { --Sp->y; }
      if(!(Joy & JOY_DOWN)) { ++Sp->y; }
      if(!(Joy & JOY_LEFT)) { --Sp->x; }
      if(!(Joy & JOY_RIGHT)) { ++Sp->x; }
      if(!(Joy & JOY_A)) { break; }
      if(!(Joy & JOY_B)) { break; }
      if(UP_ON) { --Sp->y; }
      if(DOWN_ON) { ++Sp->y; }
      if(LEFT_ON) { --Sp->x; }
      if(RIGHT_ON) { ++Sp->x; }
      Sp->x = MAX(MIN(Sp->x, 0xff), 0);
      Sp->y = MAX(MIN(Sp->y, 0xff), 0);

      //!< Put as sprite
      //xsp_set_st(Sp);

      //!< Put as metasprite
      //xobj_set_st(Sp); 

      xsp_out();

      B_LOCATE(0, 2);
      printf("SP %03d, %03d\n", Sp->x, Sp->y);
    }

    xsp_off();
  }

  CRTMOD(0x10);
}
