#include <stdio.h>
#include <stdint.h>
#include <iocslib.h>

#include "../Common.h"
#include "../PCG.h"
#include "../Palette.h"
#include "../BG.h"
#include "../Joy.h"

#define ESC_ON (BITSNS(0) & (1 << 1))

uint64_t PALData[PAL_BLOCK_COUNT][PAL_COLOR_COUNT];
uint8_t	PCGData[PCG_COUNT][PCG_16X16_SIZE];

enum {
  SP_PRI_INVISIBLE,
  //!< Back of BG1
  SP_PRI_BACK,
  //!< Between BG0 and BG1
  SP_PRI_MIDDLE,
  //!< Front of BG0
  SP_PRI_FRONT,
};

#define NO_VSYNC 0
#define WITH_VSYNC (1 << 31)

void main()
{
  //!< CRT mode
  CRTMOD(6);
  //!< Cursor off
  B_CUROFF();
  //!< Clear graphics
  G_CLR_ON(); 
 
  //!< Load palette data
  {
    FILE* Fp = fopen("../../x68k_xsp/SAMPLE/PANEL.PAL", "rb");
      if(NULL != Fp) {
      puts("Loading palette...");
      fread(PALData, sizeof(PALData[0][0]), COUNTOF(PALData), Fp);
      fclose(Fp);
    }
  }
  //!< Load PCG data
  {
    FILE* Fp = fopen("../../x68k_xsp/SAMPLE/PANEL.SP", "rb");
    if(NULL != Fp) {
      puts("Loading pattern...");
      fread(PCGData, sizeof(PCGData[0][0]), COUNTOF(PCGData), Fp);
      fclose(Fp);
    }
  }

  int SpX = 128, SpY = 128;
  {
    SP_INIT();
    SP_ON();

    SP_CGCLR(0);
    for (int i = 0; i < COUNTOF(PCGData); ++i) {
      SP_DEFCG(i, PCG_PAT_16X16, PCGData[i]);
    }

    for (int i = 0; i < COUNTOF(PALData); ++i) {
      for (int j = 0; j < COUNTOF(PALData[0]); ++j) {
	  	  SPALET(WITH_VSYNC | j, i, PALData[i][j]);
      }
	  }

    SP_REGST(WITH_VSYNC | 0, SpX, SpY, CODE(FLIP_NONE, 0, 0), SP_PRI_FRONT);
  }

  int Bg0X = 0, Bg0Y = 0;
  int Bg1X = 0, Bg1Y = 0;
  {
    //!< BG0 PAGE0 ON
    BGCTRLST(0, 0, BG_ON);
    //!< BG1 PAGE1 ON
	  BGCTRLST(1, 1, BG_ON);

    BGTEXTCL(0, 0); 
    BGTEXTCL(1, 0);
    for (int i = 0; i < BG_HEIGHT; ++i) {
      for (int j = 0; j < BG_WIDTH; ++j) {
        BGTEXTST(0, j, i, CODE(FLIP_NONE, 0, 0)); 
        BGTEXTST(1, j, i, CODE(FLIP_NONE, 0, 1)); 
      }
    }

    //!< BG0 SCROLL
    BGSCRLST(WITH_VSYNC | 0, Bg0X, Bg0Y);
    //!M BG1 SCROLL 
    BGSCRLST(WITH_VSYNC | 1, Bg1X, Bg1Y);
  }
  
  while (1)
  {      
    if(ESC_ON) { break; }
      
    const int Joy = JOYGET(0);
    if(!(Joy & JOY_UP)) { --SpY; }
    if(!(Joy & JOY_DOWN)) { ++SpY; }
    if(!(Joy & JOY_LEFT)) { --SpX; }
    if(!(Joy & JOY_RIGHT)) { ++SpX; }
    if(!(Joy & JOY_A)) { break; }
    if(!(Joy & JOY_B)) { break; }
    SpX = MAX(MIN(SpX, 255), 0);
    SpY = MAX(MIN(SpY, 255), 0);
    SP_REGST(WITH_VSYNC | 0, SpX, SpY, CODE(FLIP_NONE, 0, 0), SP_PRI_FRONT);

    Bg0X = MIN(++Bg0X, 1024);
    Bg1Y = MIN(++Bg1Y, 1024);
    BGSCRLST(WITH_VSYNC | 0, Bg0X, Bg0Y);
    BGSCRLST(WITH_VSYNC | 1, Bg1X, Bg1Y);

    B_LOCATE(0, 2);
    printf("%03d, %03d\n", SpX, SpY);
    printf("%03d, %03d\n", Bg0X, Bg0Y);
    printf("%03d, %03d\n", Bg1X, Bg1Y);
  }
  
  SP_OFF();

  //!< Cursor on
  B_CURON();
  //!< CRT mode
  CRTMOD(0x10);
}
